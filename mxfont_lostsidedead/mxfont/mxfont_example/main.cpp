#include "mx.h"
#include "mxfont.h"

mxHwnd mxhwnd;

mxFont m;
int val = 0xFF;
mxSprite sprite;

void render(int scr) {
  sprite.display(0,0);
  SDL_printtextf(&m,&mxhwnd,0,0,"Hello PSC!\nThis is printed using mxFont ;]");   
  SDL_printtextf(&m,&mxhwnd,100,100, "TEST of SDL_printtextf\na integer value is %d in hex %x in octal %o",val,val,val);
  SDL_UpdateRect(mxhwnd.pscr,0,0,640,480);
}

int main(int argc, char *argv[]) {
    if(mxhwnd.init("mxFont_Test",640,480,16,false) == 0) {
           read_font(&m,"arial.mxf");
           sprite.load(&mxhwnd,"logo1.bmp");
           mxhwnd.initLoop(render);
           free_font(&m);                                               
    }
    
}

