#include<SDL.h>
#include "SDL_font.h"

int main(int argc, char **argv)  {
	SDL_Surface *front;
	SDL_Font    font;
	atexit(SDL_Quit);
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error Initalizing SDL!\n";
		return 0;
	}

	if(!(front = SDL_SetVideoMode(640,480,0,0))) {
		std::cerr << "Error Setting Display Mode!\n";
		return 0;
	}

	if(!(SDL_read_font(&font,"arial.mxf"))) {
		std::cerr << " Error reading font arial.mxf ! \n";
		return 0;
	}

	SDL_Event e;
	bool active = true;
	while(active == true) {
		SDL_Rect rc = { 0,0,640,480 };
		SDL_FillRect(front, &rc, 0x0);
		SDL_PrintText(front, &font, 0,0,SDL_MapRGB(front->format, rand()%255, rand()%255, rand()%255), "This is a test of the font \n function!\n =)");
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					active = false;
					break;
			}
		}
		SDL_UpdateRect(front,0,0,640,480); 
	}
	
	SDL_FreeSurface(front);

	return 0;
}