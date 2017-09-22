#ifndef MASTERGRAPHICEX_H
#define MASTERHRAPHICEX_H

#include "masterx.h"

/////////////////////////////////////////////////////////////////////
//Author: Danny Anderson
//contact: garageguy@garagegaming.com
//
//This is a MasterGraphicEx. It adds more functionality to MasterGraphic.
//You can scale your image, flip it vertically & horizontally (very slow),
//You can clip your blit to the screen. There are also filters that can
//be applied to the graphic on the fly, such as grayscale, darken, brighten, etc.
//These filters should be applied during initialization. They require heavy
//calculations and can be slow if put into the drawing loop. Calling ReLoadGraphic
//will restore your graphic to the original state. Works for 15, 16, 24, 32 bit
//color spaces.
//
//Note: In the original MasterGraphic, the private members need to be
//		declared as protected in order for MasterGraphicEx to work.
//
//Bugs: This is still in testing phase. There are a few problems, such
//		as the 15/16 bit transparency color getting filtered. Also, if
//		you apply a filter it could theoretically change that pixel to
//		the transparency color. apply_balance has not been thoroughly
//		tested. Otherwise this class is rocking and rolling!
////////////////////////////////////////////////////////////////////

class MasterGraphicEx : public MasterGraphic
{
protected:
	//bit conversion masks
	enum {BIT_5_MASK = 0x1F, BIT_6_MASK = 0x3F, BIT_8_MASK = 0xFF};
	//internal filter constants
	enum {GRAYSCALE, BRIGHTEN, DARKEN, COMPLEMENT, BALANCE};
	//used by flip specifically and the Blt method
	DDBLTFX	m_ddbltfx;

	COLORREF color_key;
protected:
	//generic drawing routines
	void generic_draw (const int x, const int y, const int dest_w, const int dest_h, DWORD blt_flags);
	void generic_draw_clip (const int x, const int y, const int dest_w, const int dest_h, const RECT* clip_rect, DWORD blt_flags);

	//get this graphic's surface description
	DDSURFACEDESC get_surface_desc ();
	//changes r, g, b acording to the filter type
	void filter (const int type, int& r, int& g, int& b, const float r_amount = 0.0f, const float g_amount = 0.0f, const float b_amount = 0.0f);
	//cycles through the pixels and applies a filter to each
	void apply_filter_to_pixels (const int type, const float r_amount = 0.0f, const float g_amount = 0.0f, const float b_amount = 0.0f);
	//get the bits per pixel of environment
	int get_bit_count ();
	//constains a float amount
	void constrain_amount (float& amount, const float low, const float high);
public:
	MasterGraphicEx ();

	//### draw methods ###

	//same as DisplayGraphic, but should not give errors
	void DisplayGraphic_draw (const int x, const int y);
	//scale the graphic to new width & height, no clipping
	void DisplayGraphic_scale (const int x, const int y, const int dest_w, const int dest_h);
	//flip a graphic horizontally or vertically (slow)
	void DisplayGraphic_flip (const int x, const int y, const bool horizontal);

	//### clipping version of draw methods ###

	//draw the graphic clipped
	void DisplayGraphic_clip (const int x, const int y, const RECT* clip_rect);
	//scale the graphic with clipping
	void DisplayGraphic_scale_clip (const int x, const int y, const int dest_w, const int dest_h, const RECT* clip_rect);
	//scale the graphic to new width & height, no clipping (slow)
	void DisplayGraphic_flip_clip (const int x, const int y, const bool horizontal, const RECT* clip_rect);

	//### filters ###

	void apply_grayscale ();
	void apply_complement ();
	//range 0 to 1
	void apply_brighten (float amount);
	//range 0 to 1 
	void apply_darken (float amount);
	//range -1 to 1
	void apply_balance (float r_amount, float g_amount, float b_amount);

	//this is overloaded because i cant get the ColorKey by
	//using DDSURFACE::GetColorKey (...)
	void SetColorKey (COLORREF r);
};


#endif