#include<SDL.h>
#include "mxfont.h"
#include<stdlib.h>
#include<stdio.h>


int main(int argc, char **argv) {

	SDL_Surface *front = 0;
	SDL_Event e;
	int active = 0;
	struct SDL_Font *fnt = 0;

	if(argc != 2) {
		printf("Error arguments are the following\n sdl-mxf fnt.mxf\n");
		return 1;
	}

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return -1;

	front = SDL_SetVideoMode(640,480,0,0);
	if(!front)
		return -2;

	atexit(SDL_Quit);

	fnt = SDL_InitFont(argv[1]);
	if(!fnt)
	{
		printf("Error loading font\n");
		return -3;
	}

	active = 1;

	while(active == 1) {

		SDL_FillRect(front, 0, 0);

		SDL_PrintTextScaled(front, fnt, 0,0,20,25, SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "Hello World!");

		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = 0;
					break;
			}
		}

		SDL_UpdateRect(front, 0, 0, 640, 480);
	}

	SDL_FreeSurface(front);
	SDL_FreeFont(fnt);

	return 0;
}

