#include "MasterGraphicEx.h"
#include <fstream>

///////////////////////////////////////////////////////////////
//Name: MasterGraphicEx ()
//Info: Constructor just clears ddblyfx variable
//Params: none
//Returns: 0L - failure
//		   else - a pointer to the pixels of this graphic
///////////////////////////////////////////////////////////////
MasterGraphicEx::MasterGraphicEx ()
{
	ZeroMemory (&m_ddbltfx, sizeof (m_ddbltfx));
	m_ddbltfx.dwSize = sizeof (m_ddbltfx);
	color_key = RGB (0, 0, 0);
}

///////////////////////////////////////////////////////////////
//Name: generic_draw ()
//Info: Basically uses Blt () to display the surface
//Params: x, y - position
//			dest_w, dest_h - new size of graphic (for scaling)
//			blt_flags - flags for Blt function
//Returns: none
///////////////////////////////////////////////////////////////

void MasterGraphicEx::generic_draw (const int x, const int y, 
									const int dest_w, const int dest_h, 
									DWORD blt_flags)
{
	DWORD flags = DDBLT_WAIT | blt_flags;
	
	//add color key flag if necessary
	if (ckey)
	{
		flags|=DDBLT_KEYSRC; 
	}

	RECT dest, source;
	//rect of image
	source.left=0;
	source.top=0;
	source.right=w;
	source.bottom=h;

	//destination rect
	dest.left = x;
	dest.top = y;
	dest.right = x + dest_w;
	dest.bottom = y + dest_h;

	if (surf)
	{
	//blit the surface to the screen (it will scale automatically)
	HRESULT ddrval= scr->lpBack->Blt(&dest, surf, &source, flags, &m_ddbltfx);
	
	//if there is a problem, reload the graphic
	if(ddrval != DD_OK)
	{
		ReLoadGraphic();
	}
	}
}

///////////////////////////////////////////////////////////////
//Name: generic_draw_clip ()
//Info: Basically uses Blt () to display the surface but
//		also adds support for clipping
//Params: x, y - position
//			dest_w, dest_h - new size of graphic (for scaling)
//			clip_rect - clips graphic to this rect
//			blt_flags - flags for Blt function
//Returns: none
///////////////////////////////////////////////////////////////

void MasterGraphicEx::generic_draw_clip (const int x, const int y, 
										 const int dest_w, const int dest_h, 
										 const RECT* clip_rect, 
										 DWORD blt_flags)
{

	DWORD flags = DDBLT_WAIT | blt_flags;

	//add flages for colorkey
	if (ckey)
	{
		flags|=DDBLT_KEYSRC; 
	}

	RECT dest, source;

	//image rect
	source.left=0;
	source.top=0;
	source.right=w;
	source.bottom=h;
	
	//destination rect
	dest.left = x;
	dest.top = y;
	dest.right = x + dest_w;
	dest.bottom = y + dest_h;

	//this is basic clipping math...
	if (dest.left < clip_rect->left)
	{
		source.left = clip_rect->left-dest.left;
		dest.left = clip_rect->left;
	}

	if (dest.top < clip_rect->top)
	{
		source.top = clip_rect->top-dest.top;
		dest.top = clip_rect->top;
	}

	if (dest.right > clip_rect->right)
	{
		source.right -= dest.right-clip_rect->right;
		
		dest.right = clip_rect->right;
	}

	if (dest.bottom > clip_rect->bottom)
	{
		source.bottom -= dest.bottom-clip_rect->bottom;
		dest.bottom = clip_rect->bottom;
	}

	// Out of clipping borders
	if (dest.right<dest.left || dest.bottom<dest.top) return; 

	if (surf)
	{
	//now we are ready to Blt...
	HRESULT ddrval = scr->lpBack->Blt(&dest, surf, &source, flags, &m_ddbltfx);
	
	if(ddrval != DD_OK)
	{
		ReLoadGraphic();
	}
	}
}

///////////////////////////////////////////////////////////////
//Name: filter ()
//Info: Applies various filters to an RGB value.
//Params: type - type of filter
//			r - assigns new red value to this param
//			g - "		"	green	"	"	"   "
//			b - "		'	blue	"	"	"	"
//			amount - some filters have different intensities (range 0-1)
//Returns: applies a filter of type to r, g, b. On failure, r, g, b stay 
//			the same
///////////////////////////////////////////////////////////////
void MasterGraphicEx::filter (const int type, int& r, int& g, int& b, const float r_amount, const float g_amount, const float b_amount)
{
	switch (type)
	{
	//grayscale
	case GRAYSCALE:
		{
			//just average the 3 rgb values
			int s = (r + g + b) / 3;
			r = g = b = s;
		}
		break;

	//darken
	case DARKEN:
		{
			//darken each rgb value
			r = (int)((1.0f - r_amount)*r);
			g = (int)((1.0f - g_amount)*g);
			b = (int)((1.0f - b_amount)*b);
		}
		break;

	//brighten
	case BRIGHTEN:
		{
			//brighten each rgb value
			r = (int)(r + r_amount*(float)(255-r));
			g = (int)(g + g_amount*(float)(255-g));
			b = (int)(b + b_amount*(float)(255-b));
		}
		break;
	
	//complement (inverting colors)
	case COMPLEMENT:
		{
			//invert each rgb value
			r = 255 - r;
			g = 255 - g;
			b = 255 - b;
		}
		break;

	//color balance (basically, controls the brighten/darken for each
	// rgb component
	case BALANCE:
		{
			if (r_amount < 0)
			{
				r = (int)((1.0f - r_amount)*r);
			}
			else
			{
				r = (int)(r + r_amount*(float)(255-r));
			}

			if (g_amount < 0)
			{
				g = (int)((1.0f - g_amount)*g);
			}
			else
			{
				g = (int)(g + g_amount*(float)(255-g));
			}

			if (b_amount < 0)
			{
				b = (int)((1.0f - b_amount)*b);
			}
			else
			{
				b = (int)(b + b_amount*(float)(255-b));
			}
		}
		break;

	}
}

///////////////////////////////////////////////////////////////
//Name: apply_filter_to_pixels ()
//Info: This does all the work for the filters. It gets the pixels
//	from the surface. Then it gets the bits per pixel of the current
//	DirectDraw environment. It goes through each pixel, ripping
//	the rgb components. Next, it applies the filter and rebuilds
//	the pixel. Calling ReLoadImage will restore the surface to its
//	original state.
//Params:	type - filter type
//			r_amount, g_amount, b_amount - amount of intensity of filter
//Returns: none
///////////////////////////////////////////////////////////////

void MasterGraphicEx::apply_filter_to_pixels (const int type, const float r_amount, const float g_amount, const float b_amount)
{
	//check for a valid surface before we do anything
	if (surf == 0L)
	{
		//check surf->IsLost () also would be a good idea!
		return;
	}
	//get the bit count
	int bit_count = get_bit_count ();
	//amount of bytes between end of scanline and start of next
	int pitch;
	//temporary place holders for color information
	int r, g, b, a;

	//temporary position variable
	int x;
	//verify the bit count
	if (bit_count == -1)
	{
		return;
	}
	
	//get the pixels of this graphic
	DDSURFACEDESC surface_desc = get_surface_desc ();

	//verify we have any pixels at all
	if (surface_desc.lpSurface == 0L)
	{
		return;
	}


	//i only support 15, 16, 24 & 32 bit conversions
	switch (bit_count)
	{
		////////////////////////////////////////////////////////////////
		//15/16 bit case:
		//This is a nice bit pattern to work with, small (2 bytes) and
		//it has good color. Basically, we rip the color, apply filter
		//and reassemble image. The 15/16 pixel reading is a little 
		//buggy (not comparing color keys properly and reading pixels
		// a little off)
		///////////////////////////////////////////////////////////////
		case 15:
		{
			//get pixels from surface
			unsigned short* pixels_2_bytes = 
				(unsigned short*)surface_desc.lpSurface;
			
			//get extra bytes
			pitch = surface_desc.lPitch - w*2;
			//convert bytest to pixels
			pitch /= 2;
			
			//go through pixel by pixel
			for (int i = 0; i < h; i++)
			{
				//go to beginning of next line
				x = i*w + i*pitch;

				for (int j = 0; j < w; j++)
				{
				//extract color (we are ORing with 7 for a higher intensity
				//conversion
				r = ((pixels_2_bytes[x + j]>>10)&BIT_5_MASK)<<3;
				if (r)
					r |= 0x7;
				g = ((pixels_2_bytes[x + j]>>5)&BIT_5_MASK)<<3;
				if (g)
					g |= 0x7;
				b = (pixels_2_bytes[x + j]&BIT_5_MASK)<<3;
				if (b)
					b |= 0x7;

				//dont apply the color filter to the transparent color
				if (!ckey || (RGB (r, g, b) != (color_key)))
				{		
					//apply filter
					filter (type, r, g, b, r_amount, g_amount, b_amount);
					//rebuild pixel
					pixels_2_bytes[x + j] = (unsigned short) (((r&0xF8)<<7) | ((g&0xF8)<<2) | (b>>3));
				}
				}
			}
		}
		break;

		case 16:
		{
			//get extra bytes
			pitch = surface_desc.lPitch - w*2;
			//convert bytest to pixels
			pitch /= 2;
			
			//get pixels from surface
			unsigned short* pixels_2_bytes = 
				(unsigned short*)surface_desc.lpSurface;

			for (int i = 0; i < h; i++)
			{
				//get beginning position of scanline
				x = i*w + i*pitch;
				for (int j = 0; j < w; j++)
				{
					
					//extract colors
					r = ((pixels_2_bytes[x + j]>>11)&BIT_5_MASK)<<3;
					if (r)
						r |= 7;
					g = ((pixels_2_bytes[x + j]>>5)&BIT_6_MASK)<<2;
					if (g)
						g |= 7;
					b = (pixels_2_bytes[x + j]&BIT_5_MASK)<<3;
					if (b)
						b |= 7;

					if (!ckey || (RGB (r, g, b) != (color_key)))
					{
					filter (type, r, g, b, r_amount, g_amount, b_amount);

					//rebuild pixel
					pixels_2_bytes[x + j] = (unsigned short) (((r&0xF8)<<8) | ((g&0xF8)<<3) | (b>>3));
					}
			
				}
			}


		}
		break;

		////////////////////////////////////////////////////////////////
		//24 bit case:
		//This is usually the worst one to deal with because 24 bit 
		//color is stored as 3 bytes, too big for a short, too small 
		//for an int. In addition, as a 24 bit DirectDraw surface,
		//there are 8 (DDSURFACE->lPitch / 2) bytes appended to each
		//image scanline. So we have to skip operation on these unused
		//bytes. Note, there can be optimizations here, this was a 
		//first attempt
		///////////////////////////////////////////////////////////////
		
		case 24:
		{

			//cast surface_pixels as a byte array
			unsigned char* pixels_1_byte 
				= (unsigned char*)surface_desc.lpSurface;

			//this formula took a while to figure out,
			//but it works (pitch is the amount of bytes
			//from the end a scanline, to the beginning
			//of the next
			pitch = surface_desc.lPitch - 3*w;


			//cycle through the byte array, 3(rgb) at a time
			
			//go 1 scanline at a time
			for (int i = 0; i < h; i++)
			{
				//go through each 3 byte pixel of the scanline
				//WARNING: there is extra crap appended to each
				//scanline and we cant apply the filter to those!
				
				x = (i*3*w) + (i*pitch);

				for (int j = 0; j < (w*3); j+=3)
				{
				//get current position in pixel array
				//pitch is the amount of extra bytes 
				//3*w is the width of actual image in bytes
				//j is the position in current line

				
				//get rgb values
				r = pixels_1_byte[x + j];
				g = pixels_1_byte[x + j + 1];
				b = pixels_1_byte[x + j + 2];
				
				if (!ckey || (RGB (r, g, b) != color_key))
				{				
				//apply filter
				filter (type, r, g, b, r_amount, g_amount, b_amount);

				//reassign the rgb values
				pixels_1_byte[x + j]= r;
				pixels_1_byte[x + j + 1] = g;
				pixels_1_byte[x + j + 2] = b;
				}
				}

			}

		}
		break;

		////////////////////////////////////////////////////////////////
		//32 bit case:
		//32 bit color is stored as 4 bytes, so it fits into an int.
		//In 32 bit, I read the pixel then extract the ARGB color components
		//from it. (a is the alpha channel, for translucency). Then, I apply
		//the filter and recreate the pixel. I am preserving the original
		//a value and not applying it to the filter.
		///////////////////////////////////////////////////////////////

		case 32:
		{

			char d[100];
			wsprintf (d, "pitch: %i\n", surface_desc.lPitch);
			OutputDebugString (d);
			
			//get extra bytes at end of line
			pitch = surface_desc.lPitch - (w*4);
			//convert bytes to pixels
			pitch /= 4;

			//4 bytes per pixel
			unsigned int* pixels_4_bytes = (unsigned int*)surface_desc.lpSurface;
			//go to each pixel
			for (int i = 0; i < h; i++)
			{	
				x = (i*w) + (i*pitch);
				for (int j = 0; j < w; j++)
				{

					//get color components
					a = pixels_4_bytes[x + j]>>24;
					r = (pixels_4_bytes[x + j]>>16)&BIT_8_MASK;
					g = (pixels_4_bytes[x + j]>>8)&BIT_8_MASK;
					b = pixels_4_bytes[x + j]&BIT_8_MASK;

					if (!ckey || (RGB (r, g, b) != color_key))
					{
					//apply filter
					filter (type, r, g, b, r_amount, g_amount, b_amount);

					//construct pixel and assign it to array
					pixels_4_bytes[x + j] = (unsigned int)((a<<24) | (r<<16) | ((g) << 8) | b);
					}
				}
			}

		}
		break;

	}


}

///////////////////////////////////////////////////////////////
//Name: get_bit_count ()
//Info: This method attempts to get a point to the pixels
//		of this graphic's DirectDraw Surface. This is a pointer
//		right to the video memory. Reading/Writing to video
//		memory is very slow. But, these filters are intended to
//		be applied only once to the graphic.
//Params: none
//Returns: -1 - failure
//		   15, 16, 24, 32 - bits per pixel of the DirectDraw environment
///////////////////////////////////////////////////////////////
int MasterGraphicEx::get_bit_count ()
{
	int bit_count;
	DDSURFACEDESC ddsd;
	ddsd.dwSize = sizeof (ddsd);

	//get display mode, I am using the DirectDraw object 
	//rather than the surface on purpose (they both should be the same)
	scr->lpDD->GetDisplayMode (&ddsd);
	//get the bit count
	bit_count = ddsd.ddpfPixelFormat.dwRGBBitCount;

	if (bit_count == 16)
	{
		//find out which 16 bit we have (5x5x5 or 5x6x5)
		if (ddsd.ddpfPixelFormat.dwGBitMask == (BIT_5_MASK<<5))
		{
			bit_count = 15;
		}
		else if (ddsd.ddpfPixelFormat.dwGBitMask == (BIT_6_MASK<<5))
		{
			bit_count = 16;
		}		
	}
	//we only support 15, 16, 24 & 32
	else if ((bit_count != 24) && (bit_count != 32))
	{
		bit_count = -1;
	}

	return bit_count;
}

///////////////////////////////////////////////////////////////
//Name: get_surface_pixels ()
//Info: This method attempts to get a point to the pixels
//		of this graphic's DirectDraw Surface. This is a pointer
//		right to the video memory. Reading/Writing to video
//		memory is very slow. But, these filters are intended to
//		be applied only once to the graphic.
//Params: none
//Returns: 0L - failure
//		   else - a pointer to the pixels of this graphic
///////////////////////////////////////////////////////////////
DDSURFACEDESC MasterGraphicEx::get_surface_desc ()
{
	DDSURFACEDESC OffSurfaceDescription;
	HRESULT rval;	

	//clear the offsurface description structure
	ZeroMemory (&OffSurfaceDescription, sizeof (OffSurfaceDescription));
	OffSurfaceDescription.dwSize = sizeof (OffSurfaceDescription);
	
	//get the surface description
	rval = surf->Lock (NULL,&OffSurfaceDescription,
											DDLOCK_SURFACEMEMORYPTR, NULL);
	
	
	//check if lock did its job
	if (rval != DD_OK)
	{
		//we have a problem, return NULL
		ZeroMemory (&OffSurfaceDescription, sizeof (OffSurfaceDescription));
	}


	//unlock the surface, or DX will crash
	surf->Unlock (0L);

	return (OffSurfaceDescription);
}

///////////////////////////////////////////////////////////////
//Name: constrain_amount ()
//Info: Constrains amount to the range low to high
//Params: amount - changes amount to the specified range
//			low - floor of range
//			high - ceiling of range
//Returns: none
///////////////////////////////////////////////////////////////

void MasterGraphicEx::constrain_amount (float& amount, const float low, const float high)
{
	if (amount < low)
	{
		amount = low;
	}

	if (amount > high)
	{
		amount = high;
	}
}

void MasterGraphicEx::SetColorKey (COLORREF r)
{
	color_key = r;
	MasterGraphic::SetColorKey (color_key);
}

///////////////////////////////////////////////////////////////
//Client interface for drawing methods
///////////////////////////////////////////////////////////////

void MasterGraphicEx::DisplayGraphic_draw (const int x, const int y)
{
	generic_draw (x, y, w, h, 0);
}

void MasterGraphicEx::DisplayGraphic_clip (const int x, const int y, 
										   const RECT* clip_rect)
{
	generic_draw_clip (x, y, w, h, clip_rect, 0);
}

void MasterGraphicEx::DisplayGraphic_scale (const int x, const int y, 
											const int dest_w, const int dest_h)
{

	generic_draw (x, y, dest_w, dest_h, 0);
}

void MasterGraphicEx::DisplayGraphic_flip (const int x, const int y, 
										   const bool horizontal)
{
	m_ddbltfx.dwDDFX = horizontal?DDBLTFX_MIRRORLEFTRIGHT:DDBLTFX_MIRRORUPDOWN;

	generic_draw (x, y, w, h, DDBLT_DDFX);
}

//it turns out that scaling and clipping requires a little 
//extra math... =(
void MasterGraphicEx::DisplayGraphic_scale_clip (const int x, const int y, const int dest_w, const int dest_h, const RECT* clip_rect)
{

	DWORD flags = DDBLT_WAIT;

	//flag for color key
	if (ckey)
	{
		flags|=DDBLT_KEYSRC; 
	}

	RECT dest, source;

	//image rect
	source.left=0;
	source.top=0;
	source.right=w;
	source.bottom=h;

	//destination rect
	dest.left = x;
	dest.top = y;
	dest.right = x + dest_w;
	dest.bottom = y + dest_h;

	//scaling and clipping math ... 
	float dx = float(w)/dest_w;
	float dy = float(h)/dest_h;

	if (dest.left < clip_rect->left)
	{
		source.left = int((clip_rect->left-dest.left)*dx+0.5);
		dest.left = clip_rect->left;
	}

	if (dest.top < clip_rect->top)
	{
		source.top = int((clip_rect->top-dest.top)*dy+0.5);
		dest.top = clip_rect->top;
	}

	if (dest.right > clip_rect->right)
	{
		source.right -= int((dest.right-clip_rect->right)*dx+0.5);
		dest.right = clip_rect->right;
	}

	if (dest.bottom > clip_rect->bottom)
	{
		source.bottom -= int((dest.bottom-clip_rect->bottom)*dy+0.5);
		dest.bottom = clip_rect->bottom;
	}

	if (dest.right<dest.left || dest.bottom<dest.top) return; // Out of clipping borders

	if (surf)
	{
	//Blt to screen
	HRESULT ddrval= scr->lpBack->Blt(&dest, surf, &source, flags, &m_ddbltfx);

	if(ddrval != DD_OK)
	{
		ReLoadGraphic();
	}
	}
}

void MasterGraphicEx::DisplayGraphic_flip_clip (const int x, const int y, const bool horizontal, const RECT* clip_rect)
{

	m_ddbltfx.dwDDFX = horizontal?DDBLTFX_MIRRORLEFTRIGHT:DDBLTFX_MIRRORUPDOWN;

	generic_draw_clip (x, y, w, h, clip_rect, DDBLT_DDFX);
}

///////////////////////////////////////////////////////////////
//Client interfaces to filters (self expanatory)
///////////////////////////////////////////////////////////////
void MasterGraphicEx::apply_grayscale ()
{
	apply_filter_to_pixels (GRAYSCALE);
}

void MasterGraphicEx::apply_complement ()
{
	apply_filter_to_pixels (COMPLEMENT);
}

void MasterGraphicEx::apply_brighten (float amount)
{
	constrain_amount (amount, 0.0f, 1.0f);
	apply_filter_to_pixels (BRIGHTEN, amount, amount, amount);
}

void MasterGraphicEx::apply_darken (float amount)
{	
	constrain_amount (amount, 0.0f, 1.0f);
	apply_filter_to_pixels (DARKEN, amount, amount, amount);
}

void MasterGraphicEx::apply_balance (float r_amount, float g_amount, float b_amount)
{
	constrain_amount (r_amount, -1.0f, 1.0f);
	constrain_amount (g_amount, -1.0f, 1.0f);
	constrain_amount (b_amount, -1.0f, 1.0f);

	apply_filter_to_pixels (BALANCE, r_amount, g_amount, b_amount);
}
