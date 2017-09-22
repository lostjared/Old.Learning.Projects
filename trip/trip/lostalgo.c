

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include<SDL.h>
#include<SDL_mxf.h>
#include<math.h>

SDL_Surface *front = 0, *img;

void lostalgo(SDL_Surface *surf, int direction, float speed, long trip) {

	unsigned int i,z;
	void *buf;
	buf = lock(surf, surf->format->BitsPerPixel);
	for(i = 0; i < surf->w; i++) {
		for(z = 0; z < surf->h; z++) {
			Uint32 color;
			SDL_Color col;
			color = getpixel(surf, i,z,surf->format->BitsPerPixel, surf->pitch, &col);
			trip++;
			if(trip > 3) 
			color += sinf(speed), trip = 0;
			
			setpixel(buf,i,z,color+direction,surf->format->BitsPerPixel, surf->pitch);
		}
	}
	unlock(surf);

}

void alpha_blend(SDL_Surface *one, SDL_Surface *two, float alpha) {

	unsigned int i,z;
	static float dist = 0.01f;

	void *buf,*buf2;
	buf = lock(one, one->format->BitsPerPixel);
	buf2 = lock(two, two->format->BitsPerPixel);
	for(i = 0; i < one->w; i++) {
		for(z = 0; z < one->h; z++) {
			Uint32 color;
			SDL_Color col,col2;
			dist += 0.1f;
			getpixel(one,i,z,one->format->BitsPerPixel, one->pitch, &col);
			getpixel(two, i,z,two->format->BitsPerPixel, two->pitch, &col2);
			color = SDL_MapRGB(one->format, (Uint8)col.r + col2.r * alpha, (Uint8)col.g + col2.g * alpha, (Uint8)col.b + col2.b * alpha);
			color = (Uint32) floor(color) - sqrt(color);
			color += dist;
			if(color >= SDL_MapRGB(one->format, 255, 255, 255)) color = SDL_MapRGB(one->format, 255, 255, 255);
			setpixel(buf,i,z,color,one->format->BitsPerPixel, one->pitch);
		}
	}
	unlock(one);
	unlock(two);

}

int main(int argc, char *argv[])
{
	SDL_Event e;
	int active = 1;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) return -1;
	front = SDL_SetVideoMode(480,272,0,0);
	if(argc == 2)
	img = SDL_LoadBMP(argv[1]);
	else
	img = SDL_LoadBMP("lostalgo.bmp");
	
	if(!img || !front) return -1;
	SDL_BlitSurface(img, 0, front, 0);
	
	while(active == 1) {
		static float alpha = 1.0f;

		lostalgo(front, 1, 25, 0);
		lostalgo(img, 2, 0xFF, 0);
		alpha_blend(front, img, (alpha+=0.3f));
		if(SDL_PollEvent(&e)) {
			switch(e.type) {
			case SDL_QUIT:
			active = 0;
			break;

			}

		}
		SDL_UpdateRect(front, 0, 0, 480, 272);
	}

	SDL_FreeSurface(front);
	SDL_Quit();


  return 0;
}
