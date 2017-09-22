
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<math.h>
#include<string.h>
#include<fstream>
#include<time.h>
#include "image.h"
#include"glut.h"
#include<GL/gl.h>
#include<GL/glu.h>

#include"font.h"
#define sync if(xchange == true)
using namespace std;


void initgl(int width, int height);
void resize(int width, int height);
void render();
void render_start();
void render_scores();
void render_gameover();
void render_game();
void keydown(unsigned char key, int x, int y);
void specialkey(int key, int x, int y);
void releaseblock();
void moveleft();
void moveright();
void movedown();
void shiftup();
void shiftdown();
void procblocks();
void checkformovedown();
void clearboard();
void setscreen(int screen);
void timerfunc(int value);
void addline(int type);



enum COLOR { BLACK = 0, WHITE, RED, GREEN, BLUE, GRAY };


struct block {

  float r,g,b;
  COLOR color;

  block()    
  {
    color = BLACK;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
  }
  
  inline void copyblock(struct block *g_block )
  {
    color = g_block->color;
    r = g_block->r;
    g = g_block->g;
    b = g_block->b;
  }

  inline void clear()
  {
    color = BLACK;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
  }

};

struct gameblock : block {

  int x,y;

  gameblock()
  {
    color = BLACK;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    x = 0;
    y = 0;
  }
  
  inline void randcolor()
  {
    switch(rand()%5)
    {
      case 0:
      r = 1.0f;
      g = 0.0f;
      b = 0.0f;
      color = RED;
      break;
      case 1:
      r = 0.0f;
      g = 1.0f;
      b = 0.0f;
      color = GREEN;
      break;      
      case 2:
      r = 0.0f;
      g = 0.0f;
      b = 1.0f;
      color = BLUE;
      break;
      case 3:
      r = 1.0f;
      g = 1.0f;
      b = 1.0f;
      color = WHITE;
      break;
      case 4:
      case 5:
      r = .5f;
      g = .5f;
      b = .5f;
      color = GRAY;
      break;
    }
  }

};



class highscores {

struct scores {
       char userid[100];
       int score;

       scores()
       {
         strcpy(userid,"Default User");
         score = 0;
       }
};


public:

struct scores thescores[11];

    inline highscores()
    {
      load();
    }

    inline void load()
    {
      ifstream fin("scores.dat",ios::binary);
      if(fin.is_open())
      {
      fin.read((char*)&thescores,sizeof(thescores));
      fin.close();
      }
    }

    inline void save()
    {
      ofstream fout("scores.dat",ios::binary);
      fout.write((char*)&thescores,sizeof(thescores));
      fout.close();
    }

    inline void add(char *user, int score)
    {
      strcpy(thescores[10].userid,user);
      thescores[10].score = score;
      int max = 11;
      int pa,c;
      for(pa = 0; pa < max - 1; pa ++)
      {
        for(c = 0; c < max - 1; c++)
        {
          if(thescores[c].score < thescores[c+1].score)
          {
            struct scores tscore;
            tscore = thescores[c];
            thescores[c] = thescores[c+1];
            thescores[c+1] = tscore;
           }
        }
      }
    }

    inline void clear()
    {
      for(int p = 0; p < 12; p++)
      {
        strcpy(thescores[p].userid,"Default User");
        thescores[p].score = 0;
      }
    }
                                    
};

struct block tiles[17][8];
struct gameblock gblock[3];
class highscores hscores;

float rquad = 0.0f, r_quad = 0.0f,qrotate = 0.0f;
int wnd = 0, i = 0,z = 0, p = 0,score = 0,lines = 0, screen = 0,cursor =  0,pos = 0,enter = 0,xspeed = 10;
bool paused = false,xchange = false;
char userid[100];


enum { ID_START = 0 , ID_GAME, ID_HIGHSCORES, ID_GAMEOVER };

int main(int argc, char * argv[])
{
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    wnd = glutCreateWindow("MasterPiece 3D");
    glutDisplayFunc(&render);
    //glutFullScreen();
    glutTimerFunc(1,&timerfunc,1);
    glutIdleFunc(&render);
    glutReshapeFunc(&resize);
    glutKeyboardFunc(&keydown);
    glutSpecialFunc(&specialkey);
	initgl(640, 480);
	
    releaseblock();
    glutMainLoop();
    return (0);
}

void initgl(int width, int height)
{
  LoadGLTextures();
  glEnable ( GL_COLOR_MATERIAL );
   glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
   glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0);
  glEnable(GL_TEXTURE_2D);	
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  					
  glEnable(GL_DEPTH_TEST);						
  glDepthFunc(GL_LEQUAL);							
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  gluPerspective(45.0f,(float)width/(float)height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
  buildfont();
  setscreen(ID_START);
}


void resize(int width, int height)
{
    if (height==0)
    height=1;
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(float)width/(float)height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    switch(screen)
    {
      case ID_START:
      render_start();
      break;
      case ID_HIGHSCORES:
      render_scores();
      break;
      case ID_GAMEOVER:
      render_gameover();
      break;
      case ID_GAME:
      render_game();
      break;
    }

     glutSwapBuffers();
}

void render_start()
{
  glLoadIdentity();

  glTranslatef(-10.0f,15.0f,-55.0f);
  glLoadIdentity();
  
  glTranslatef(-10.0f,15.0f,-55.0f);
   
  
  printtextf(1.5f,2.0f,"MasterPiece 3D");
  printtextf(3.5,-9.0f,"Start");
  printtextf(3.5,-12.0f,"Highscores");
  printtextf(3.5,-15.0f,"Exit");
  float y = 0;
  switch(cursor)
  {
    case 0:
    y = -9.0f;
    break;
    case 1:
    y = -12.0f;
    break;
    case 2:
    y = -15.0f;
    break;
  }
  printtextf(-1.0,y,"=)>");
  glTranslatef(0.0f,0.0f,-20.0f);
  glRotatef(qrotate,1.0f,1.0f,1.0f);
  

  qrotate -= .5f;
  if(qrotate < -1080)
  qrotate = 0;
  
 
 
  for(i = 0; i < 17; i++)
  {
    for(z = 0; z < 8; z++)
    {
	  glBindTexture(GL_TEXTURE_2D, texture[rand()%4]);
      glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

       glTranslatef(3.0f,0.0f,0.0f);
    }

     glTranslatef(-24.0,-2.0,0.0f);
 }



  glPopMatrix();
 
}

void render_game()
{
    if(paused == false)
    checkformovedown();

    for(p = 0; p < 3; p++)
    {
      if(gblock[p].color == BLACK)
      {
       releaseblock();
      }
    }
    procblocks();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();



    glTranslatef(-10.0f,15.0f,-45.0f);

    //glColor3f(1.0f,0.0f,0.0f);
    printtextf(19.0f,2.0f,"Score: %i ", score);


    glRotatef(rquad,1.0f,0.0f,0.0f);
    glRotatef(r_quad,0.0f,1.0f,0.0f);

    //draw the board
    for(i = 0; i < 17; i++)
    {

      for(z = 0; z < 8; z++)
      {
        for(p = 0; p < 3; p++)
        {

        // draw the current game block
        if(gblock[p].x == z && gblock[p].y == i)
        {
            
	  glBindTexture(GL_TEXTURE_2D, texture[gblock[p].color]);
      glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glEnd();

            glEnd();
        }

      }

        // draw the rest of the blocks
        if(tiles[i][z].color != BLACK)
        {
            
	  glBindTexture(GL_TEXTURE_2D, texture[tiles[i][z].color]);
      glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glEnd();

          }
          glTranslatef(3.0f,0.0f,0.0f);
       }

      glTranslatef(-24.0,-2.0,0.0f);

    }

   
}

void render_scores()
{

  glLoadIdentity();
  glColor3f(1.0f,0.0f,0.0f);
  glTranslatef(-10.0f,15.0f,-55.0f);
  printtextf(1.0f,5.0f,"Highscores");
  float y = 0.0f;
  for(p = 0; p < 11; p++)
  {
    printtextf(1.0f,y,"(%i) %s : %i ", p, hscores.thescores[p].userid, hscores.thescores[p].score);
    y -= 3.0f;
  }
  if(enter == 1)
  {
    
    glColor3f(0.0f,0.0f,1.0f);
    printtextf(20.0f,-5.0f,"enter your name");
    glColor3f(0.0f,1.0f,0.0f);
    printtextf(20.0f,-8.0f,"%s%s",userid, rand()%5 > 2  ? "" : "_" );

  }

}

void render_gameover()
{

}

void keydown(unsigned char key, int x, int y)
 {
     if(key == 27)
     {
       killfont();
       glutDestroyWindow(wnd);
       exit(0);
     }

     switch(screen)
     {
       case ID_START:

       switch(key)
       {
         case 13:
         switch(cursor)
         {
           case 0:
           clearboard();
           score = 0;
           lines = 0;
           xspeed = 15;
           setscreen(ID_GAME);
           break;
           case 1:
           setscreen(ID_HIGHSCORES);
           enter = 0;
           break;
           case 2:
           keydown(27,0,0);
           break;
         }
         break;
       }
       
       
       break;

       case ID_HIGHSCORES:

       switch(enter)
       {
         case 0:
         switch(key)
         {
           case 13:
           setscreen(ID_START);
           break;
         }
         break;
         case 1:

         if(key == 8)
          {
            if(pos > 0)
            {
              pos--;
              userid[pos] = 0;
            }
          }
          else
          {
          
           if(strlen(userid) < 11)
           {
              userid[pos] = key;
              userid[pos+1] = 0;
              pos++;
           }

          }

          if(key == 13)
          {
            if(pos == 0)
            {
              enter = 0;
              return;
            }
            else
            {
              hscores.add(userid,score);
              hscores.save();
              enter = 0;
            }
          }
          
         break;
       }

       break;

       
       case ID_GAME:
       
     switch(key)
     {
     case 27:
     {
      killfont();
 	    glutDestroyWindow(wnd);
 	    exit(0);
 	   }
     break;
     case 'a':
     case 'A':
     shiftup();
     break;
     case 's':
     case 'S':
     shiftdown();
     break;
     case 'h':
     case 'H':
     rquad = 0.0f;
     r_quad = 0.0f;
     break;
     case 'd':
     case 'D':
     rquad = -45.0f;
     r_quad = 0.0f;
     break;
     case 'v':
     case 'V':
     rquad = 1.5f;
     r_quad = 67.0f;
     break;
     case 'p':
     case 'P':
     paused = !paused;
     break;
     
     }

     break;

     }

     
 }

void specialkey(int key, int x, int y)
{

  switch(screen)
  {
    case ID_START:
    {
      switch(key)
      {
        case GLUT_KEY_DOWN:
        if(cursor < 2)
        cursor++;
        
        break;
        case GLUT_KEY_UP:
        if(cursor >  0)
        cursor--;
        break;
      }
    }
    break;
    case ID_GAMEOVER:
    break;
    case ID_HIGHSCORES:
   
    
    break;
    case ID_GAME:
    {
      


     switch(key)
     {
     case 104:
	   {
	       rquad += 0.5;
	   }
	   break;
     case 105:
	   {

	       rquad -= 0.5;
	   }
	   break;
     case 106:
	   {
	       r_quad -= 0.5f;
     }
	   break;
     case 107:
	   {
	       r_quad += 0.5f;
	   }
	   break;
     case GLUT_KEY_UP:
     {
       releaseblock();
     }
     break;
     case GLUT_KEY_DOWN:
     {
       movedown();
     }
     break;
     case GLUT_KEY_LEFT:
     {
       moveleft();
     }
     break;
     case GLUT_KEY_RIGHT:
     {
       moveright();
     }
     break;
     }

     }

     break;
     }
}

void setscreen(int screenx)
{
  screen = screenx;
}

void releaseblock()
{
do
{
  gblock[0].randcolor();
  gblock[1].randcolor();
  gblock[2].randcolor();
}
while(gblock[0].color == gblock[1].color && gblock[0].color == gblock[2].color);

  gblock[0].x = 3;
  gblock[0].y = 0;
  gblock[1].x = 3;
  gblock[1].y = 1;
  gblock[2].x = 3;
  gblock[2].y = 2;
  
}

void moveleft()
{
  if(gblock[0].x > 0 && tiles[gblock[0].y][gblock[0].x-1].color == BLACK && tiles[gblock[1].y][gblock[1].x-1].color == BLACK && tiles[gblock[2].y][gblock[2].x-1].color == BLACK)
  {
     gblock[0].x--;
     gblock[1].x--;
     gblock[2].x--;
  }
}

void moveright()
{
  if(gblock[0].x < 7 && tiles[gblock[0].y][gblock[0].x+1].color == BLACK && tiles[gblock[1].y][gblock[1].x+1].color == BLACK && tiles[gblock[2].y][gblock[2].x+1].color == BLACK)
  {
    gblock[0].x++;
    gblock[1].x++;
    gblock[2].x++;
  }
}

void movedown()
{
  if(gblock[2].y < 16)
  {
    if(tiles[gblock[2].y+1][gblock[2].x].color != BLACK)
    {
      tiles[gblock[2].y][gblock[2].x].copyblock(&gblock[2]);
      tiles[gblock[1].y][gblock[1].x].copyblock(&gblock[1]);
      tiles[gblock[0].y][gblock[0].x].copyblock(&gblock[0]);
      if(gblock[2].y < 3)
      {
        clearboard();
        printf("game over\nyour score: %i\n", score);
        setscreen(ID_HIGHSCORES);
        if(hscores.thescores[10].score < score)
        {
          enter = 1;
          strcpy(userid,"");
          pos = 0;
        }
        else
        enter = 0;
      }
      else
      releaseblock();
      
    }  
    else
    {
      gblock[0].y++;
      gblock[1].y++;
      gblock[2].y++;
    }
  }
  else
  {
    tiles[gblock[2].y][gblock[2].x].copyblock(&gblock[2]);
    tiles[gblock[1].y][gblock[1].x].copyblock(&gblock[1]);
    tiles[gblock[0].y][gblock[0].x].copyblock(&gblock[0]);
    releaseblock();
  }
}

void shiftup()
{
  struct gameblock g_block;
  g_block = gblock[0];
  gblock[0].copyblock(&gblock[1]);
  gblock[1].copyblock(&gblock[2]);
  gblock[2].copyblock(&g_block);
}

void shiftdown()
{
  struct gameblock g_block;
  g_block = gblock[0];
  gblock[0].copyblock(&gblock[2]);
  gblock[2].copyblock(&gblock[1]);
  gblock[1].copyblock(&g_block);
}

void procblocks()
{

  for(i = 0; i < 17; i++)
  {
    for(z = 0; z < 8; z++)
    {
      COLOR cur_color = tiles[i][z].color;

      if(cur_color != BLACK)
      {
        if(z+2 < 8)
        {
          if(tiles[i][z+1].color == cur_color && tiles[i][z+2].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i][z+1].clear();
            tiles[i][z+2].clear();
            addline(0);
            return;
          }
        }

        if(z+3 < 8)
        {
          if(tiles[i][z+1].color == cur_color && tiles[i][z+2].color == cur_color && tiles[i][z+3].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i][z+1].clear();
            tiles[i][z+2].clear();
            tiles[i][z+3].clear();
            addline(1);
            return;
          }
       }

        if(i+2 < 17)
        {
          if(tiles[i+1][z].color == cur_color && tiles[i+2][z].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i+1][z].clear();
            tiles[i+2][z].clear();
            addline(0);
            return;
          }
        }
        
        if(i+3 < 17)
        {
          if(tiles[i+1][z].color == cur_color && tiles[i+2][z].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i+1][z].clear();
            tiles[i+2][z].clear();
            tiles[i+3][z].clear();
            addline(1);
            return;
          }
        }
      }
      
    }
  }

  for(z = 0; z < 8; z++)
  {
    for(i = 0; i < 17; i++)
    {
      COLOR cur_color = tiles[i][z].color;
      if(cur_color != BLACK)
      {
        if(i+2 < 17 && z+2 < 8)
        {
          
          if(tiles[i+1][z+1].color == cur_color && tiles[i+2][z+2].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i+1][z+1].clear();
            tiles[i+2][z+2].clear();
            addline(2);
            return;
          }

        }
        if(i-2 >= 0 && z-2 >= 0)
        {
          if(tiles[i-1][z-1].color == cur_color && tiles[i-2][z-2].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i-1][z-1].clear();
            tiles[i-2][z-2].clear();
            addline(1);
            return;
          }
        }

        if(i-2 >= 0)
        {
          if(tiles[i-1][z+1].color == cur_color && tiles[i-2][z+2].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i-1][z+1].clear();
            tiles[i-2][z+2].clear();
            addline(1);
            return;
          }
        }

        if(z-2 >= 0)
        {
          if(tiles[i+1][z-1].color == cur_color && tiles[i+2][z-2].color == cur_color)
          {
            tiles[i][z].clear();
            tiles[i+1][z-1].clear();
            tiles[i+2][z-2].clear();
            addline(1);
            return;            
          }
        }
            
      }
    }
  }
  
  for(z = 0; z < 8; z++)
  {
    for(i = 0; i < 16; i++)
    {
      if(tiles[i][z].color != BLACK && tiles[i+1][z].color == BLACK)
      {
        tiles[i+1][z] = tiles[i][z];
        tiles[i][z].clear();
      }
    }
  }
  
   
}

void checkformovedown()
{
  sync
  {
    static int q = 0;
    if(++q > xspeed)
    {
       movedown();
       q = 0;
    }
  }
}

void clearboard()
{
  for(i = 0; i < 17; i++)
  {
    for(z = 0; z < 8; z++)
    {
      tiles[i][z].clear();
    }
  }
}

void addline(int type)
{
  switch(type)
  {
    case 0:
    score += 5;
    break;
    case 1:
    score += 7;
    break;
    case 2:
    score += 10;
    break;
  }

  lines ++;


  if(lines > 30)
  {
    xspeed = 5;
    return;
  }  

  if(lines > 20)
  {
    xspeed  = 7;
    return;
  }
  
  if(lines > 10)
  {
    xspeed = 10;
    return;
  }
}



void timerfunc(int value)
{

  static int val = 0;
  val++;
  if(val > 5)
  {
    xchange = true;
    val = 0;
  }
  else
  {
    xchange = false;
  }
  glutTimerFunc(1,&timerfunc,value);
}



