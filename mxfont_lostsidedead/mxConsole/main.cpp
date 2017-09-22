#include "mx.h"

mxHwnd mxhwnd;

void mid(const char *source, char *output, int start, int stop) {
     int pos = 0;
     for(int i = start; i < stop; i++)
     output[pos++] = source[i];
     
     output[pos] = 0;
}

int findsecondn(char *source) {
    int count = 0;
    for(int i = 0; i < strlen(source); i++) {
            if(source[i] == '\n')
            count++;
            
            if(count > 1)
            return i;        
    }   
}

enum { ECHO = 0, EXIT, FLUSH, SETFONT };
static char *cmdarray[] = {"echo","exit","flush","setfont",0};

class mxConsole {
      mxFont mxf;
      char textbuffer[5000];
      int pos,start_pos;
      bool input_on;
      mxSprite bg;
      public:
      ~mxConsole() {
          free_font(&mxf);
      }
      void init() {
                  read_font(&mxf,"arial.mxf");
                  strcpy(textbuffer,"=)>");
                  pos = (int)strlen(textbuffer);
                  start_pos = pos;
                  input_on = true;
                  key_down = false;
                  cur_key = 0;
                  bg.load(&mxhwnd,"logo1.bmp");
      }
             
      void render() {
           char tmp[5000];
           bg.display(0,0);
           if(input_on == true)
           sprintf(tmp,"%s%s", textbuffer, rand()%10 > 5 ? "_" : "");
           else
           sprintf(tmp,"%s", textbuffer);
           if(SDL_printtextf(&mxf,&mxhwnd,0,0,tmp)) return;
           else {
                mid(textbuffer,tmp,findsecondn(textbuffer), strlen(textbuffer));
                strcpy(textbuffer,tmp);
                printf("%s\n HERE",tmp);
                pos = strlen(textbuffer);
                start_pos = pos;
           }
       }
       
       
       bool key_down;
       int cur_key;
       
       void keyup(int key) {     
            key_down = false;      
       }
       
       void keypress(int key) {
            
            key_down = true;
            this->cur_key = key;
            switch(key) {
                        case 8:
                             if(pos > start_pos)
                             textbuffer[--pos] = 0;
                             break;
                        case 13:
                             proccess();
                              break;
                             default:
                             if(key == ' ' || key >= '!' && key <= '@' || key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key >= '[' && key <= '`' || key  >= '{' && key <= '~') {
                            textbuffer[pos++] = key;
                            textbuffer[pos] = 0;
                            }
                            
            }
       }
       
       void printtextf(const char *source, ...) {
                char text[5000];
                va_list list;
                va_start(list, source);
                vsprintf((char*)text,source,list);
                va_end(list);
                sprintf(textbuffer,"%s%s", textbuffer, text);
       }
       
       void proccess() {
            // mid the string from start_pos to pos
            char tmp[5000];
            mid(textbuffer,tmp,start_pos,pos);
            tokenize(tmp);
            printtextf("\n=)>");
            start_pos = (int)strlen(textbuffer);
            pos = strlen(textbuffer);
            
       }
       
       struct Token {
              char text[5000];     
       };
       
       Token tokens[100];

       void tokenize(char *str) {
            char *ptr = str;
            int chpos ,tpos,cpos;       
            cpos =  tpos = chpos = 0;
            while(ptr[cpos] != 0) {
                 if(ptr[cpos] != '\"') {
                              
                            tokens[tpos].text[chpos++] = ptr[cpos++];             
                            if(ptr[cpos] == ' ') {
                                        tpos++;
                                        chpos = 0;  
                                        cpos++;
                            }
                 }   
                 else {
                      cpos++;
                 while(ptr[cpos] != '\"' && ptr[cpos] != 0) {
                        tokens[tpos].text[chpos++] = ptr[cpos++];                
                 }
                 tokens[tpos].text[chpos] = 0;
                 chpos = 0;
                 cpos+=2;
                 tpos++;
                 }
                           
            }
            tpos++;
            tokens[tpos].text[0] = 0;
            print_Tokens(tpos);
            proc_Tokens(tpos);
       }
       
       int cmdtoint(char *pstr) {
           for(int i = 0; cmdarray[i] != 0; i++) {
                   if(strcmp(cmdarray[i],pstr) == 0)      
                   return i;
           }
           
           return -1;
       }
       
       void proc_Tokens(int pos) {
            switch(cmdtoint(tokens[0].text)) {
                case ECHO:
                     if(pos >= 1)
                     printtextf("\n%s", tokens[1].text);
                     break; 
               case EXIT:
                     mxhwnd.kill();
                    break; 
                    case FLUSH:
                    strcpy(textbuffer,"");
                      break;   
                case SETFONT:
                     FILE *pfile;
                     if(pos >= 1)
                     if((pfile = fopen(tokens[1].text,"r")) == 0)
                     printtextf("\nError couldnt open file %s.",tokens[1].text);
                     else {
                          fclose(pfile);
                          free_font(&mxf);
                          read_font(&mxf,tokens[1].text);     
                     }
                     break; 
                    default:
                    printtextf("\nUnknown command ;[");              
            }
       }
       
       void print_Tokens(int len) {
            for(int i = 0; i < len; i++)
                    if(strlen(tokens[i].text) != 0)
                    printf("token passed %s\n", tokens[i].text);
                    
       }
};

mxConsole mxc;

void keypress(int key) {
     mxc.keypress(key);    
}
void keyup(int key) {
     mxc.keyup(key);
}
void render(int screen) {
     mxc.render();
     SDL_UpdateRect(mxhwnd.pscr, 0,0,640,480);
}

int main(int argc, char *argv[]) {
    if(!mxhwnd.init("mxConsole",640,480,16,false)) {
                mxc.init();
                mxhwnd.setKeydown(keypress);
                mxhwnd.setKeyup(keyup);
                return mxhwnd.initLoop(render);                                               
    }
    else
    printf("Error on initlization.\n");
    
    return 0;
}

