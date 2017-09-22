#include "mxSDL.h"
#include"complex.h"
#include<cmath>

int StepX = 1;
int StepY = 1;
double paramA = 0.519;
double paramB = 0.688;
float zoom = 0;
double red_color = 3.3;
double green_color = 3.3;
float mod_x = 0.5;
float mod_y = 0.5;




class mxFractal : public EventHandler {
public:
	mxFractal() {
		if(!(img1.LoadBMP("lsd.bmp")))
			throw ErrorMsg("Couldnt load Bitmap");
		img2.LoadBMP("lsd2.bmp");
		if(!(img2.LoadBMP("lsd2.bmp")))
			throw ErrorMsg("Couldnt Load Bitmap");

	}
	virtual void Render() {
		static float scale = 0;//1.0;
		FractalBlend(&img1,&img2,0,0,640,480,scale);
		scale += 0.5f;
	}

	virtual void FractalBlend(mxSurface *one, mxSurface *two, int x, int y, int w, int h, float alpha){
		// Fractal limits
	float x1=mod_x-1.0f*zoom;
	float x2=mod_x+1.0f*zoom;
	float y1=mod_y-1.0f*zoom;
	float y2=mod_y+1.0f*zoom;
	static float fr,fg,fb;
	// Form properties
	int Xfrm=0; int Yfrm=0;
	int Width=320; int Height=240;
	// Init
	//Complex C ((double)-0.0519, (double)0.688); default
	Complex C ((double)-paramA, (double)+paramB);
	Complex Z, Z0, Zt;
	int i;
	bool Fini;

	paramA += 0.1f;
	if(paramA > 10) {
		paramA = 0;
		paramB += 0.1f;
		if(paramB > 5)
			paramB = 0;
	}
	// Draw Fractal
	for (int x=0; x<Width; x+=StepX) 
	{
		for (int y=0; y<Height; y+=StepY) 
		{
			// Init Z to position (x,y) in space z([x1,y1],[x2,y2])
			Z=Z0=Complex((double)(x*(x2-x1)/Width+x1), (double)(y*(y2-y1)/Height+y1));
			Fini=false;

			// Find ecart
			for (i=0; i<100 && (!Fini); i++) 
			{
				Z=Z*Z+C;
				Zt=Z-Z0;				
				if (Zt.modulus()>4.0) Fini=true;
			}

			mxRGB color = mxRGB(mx->GetFront(),(int)sin(i*red_color/100)*255,(int)sin(i*green_color/100)*200,255-i*2).color;
			mxRGB color1 = mx->GetPixel(one,x,y);
			mxRGB color2 = mx->GetPixel(two,x,y);

				if((fr = float ( (color1.r * alpha) + (1- alpha) * color2.r) * color.color) > 255) fr = 255;
				if((fg = float ( (color1.g * alpha) + (1- alpha) * color2.g) * color.color)  > 255) fg = 255;
				if((fb = float ( (color1.b * alpha) + (1- alpha) * color2.b) * color.color) > 255) fb = 255;
				color = mxRGB(mx->GetFront(),int(fr),int(fg),int(fb));
				red_color = fr;
				green_color = fg;
				
			
			if (StepX==1 && StepY==1)
			{
				mx->SetPixel(mx->GetFront(), x+Xfrm,y+Yfrm,color);
			}
		}
	}

	 zoom += 0.5f;
	 if(zoom > 4)
		 zoom = 0;
	}


	virtual void KeyDown(int key) {


	}
protected:
	mxSurface img1, img2;
};

int main(int argc, char **argv) {
	try {
		mxSDL mxsdl("Fractals", 320,240,0,false);
		mxsdl.SetEvents( new mxFractal );
		mxsdl.MessagePump();
	} catch( ErrorMsg& e ) {
		e.PrintLastError();
	}
	return 0;
}