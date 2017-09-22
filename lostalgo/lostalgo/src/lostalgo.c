

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include<SDL.h>
#include<SDL_mxf.h>

SDL_Surface *front = 0, *img;

void lostalgo(SDL_Surface *surf) {

	unsigned int i,z;
	void *buf;
	buf = lock(surf, surf->format->BitsPerPixel);
	for(i = 0; i < surf->w; i++) {
		for(z = 0; z < surf->h; z++) {
			Uint32 color;
			SDL_Color col;
			color = getpixel(surf, i,z,surf->format->BitsPerPixel, surf->pitch, &col);
			setpixel(buf,i,z,color+1,surf->format->BitsPerPixel, surf->pitch);
		}
	}
	unlock(surf);

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
		lostalgo(front);
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
