#include"mx.h"

mxHwnd mxhwnd; 
mxSprite images[3];


int odd(int x) {
    return ( x & 1 );
}

void draw_map() {
     SDL_Rect rect;
     for(int i = 0; i < 640/124*2+4; i++) {
             for(int z = 0; z < 480/64+2; z++) {
                     rect.x = (i * 124/2)-124;
                     rect.y = (z * 64 + odd(i) * 64/2)-64;
                     images[rand()%2].display(&mxhwnd,rect.x,rect.y);
             }        
     }
}
void render(int scr) {
     int tlen = 30;
     draw_map();
}


void onEvent(SDL_Event *evnt) {
     
     
}

void onLoad() {

     images[0].load("tile1.bmp",0,0,0);
     images[1].load("tile2.bmp",0,0,0);
     images[2].load("tile3.bmp",0,0,0);
}

int main(int argc, char *argv[]) 
{
	if(mxhwnd.init("IsoMetric",640,480,32,false) == 0)
	{     
        onLoad();  
		mxhwnd.setEventHandler(onEvent);
		mxhwnd.initLoop(render);
	}
	
	return 0;
}

