// from nehe.gamedev.net


#include <gl\glaux.h>
GLuint	texture[10];


AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}
static char *images[] = {"block_black.bmp","block_ltblue.bmp", "block_red.bmp", "block_green.bmp", "block_dblue.bmp", "block_gray.bmp" };

int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;									// Status Indicator

	AUX_RGBImageRec *TextureImage[7];					// Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*7);           	// Set The Pointer To NULL

	for (int q = 0; q < 6; q++) {
	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[q]=LoadBMP(images[q]))
	{
		Status=TRUE;									// Set The Status To TRUE

		glGenTextures(1, &texture[q]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[q]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[q]->sizeX, TextureImage[q]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[q]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}

	if (TextureImage[q])									// If Texture Exists
	{
		if (TextureImage[q]->data)							// If Texture Image Exists
		{
			free(TextureImage[q]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[q]);								// Free The Image Structure
	}
	}

	return Status;										// Return The Status
}
