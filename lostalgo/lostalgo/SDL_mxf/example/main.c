#include<SDL.h>
#include<SDL_mxf.h>

int main(int argc, char **argv) {
	SDL_Surface *front = 0;
	SDL_Event e;
	int active = 1;
	struct SDL_Font *the_font = 0;

	SDL_Init(SDL_INIT_VIDEO);
	front = SDL_SetVideoMode(480,272,0,0);
	if(!front)
		return -1;

	the_font = SDL_InitFont("font.mxf");

	while(active == 1) {

		SDL_FillRect(front, 0, 0);
		SDL_PrintText(front, the_font, 0, 0, SDL_MapRGB(front->format,255,255,255), "Hello World in mxf");

		if(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = 0;
					break;
			}
		}

		SDL_UpdateRect(front, 0,0,480,272);
	}

	SDL_FreeSurface(front);
	SDL_FreeFont(the_font);
	SDL_Quit();

	return 0;
}