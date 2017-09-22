/* MasterPiece 3D using MasterOGL
written by Jared Bruni
with help from the tutorials at nehe.gamedev.net
Thank You  Nehe! you site r0x
everyone else please 
visit my site
http://www.lostsidedead.com

this part of the game was recoded from scratch

written by Jared Bruni
   for free
   you may use this for whatever you want free of charge
   just dont sell it =)
*/



#include "mogl.h"
#include "credits.h"
#include "game.h"


#include "resource.h"


MasterOGLHWND mohwnd;
MasterFont    font;
MasterTexture game_textures[11];

Credits credits;

bool rt_pressed = false, playing = false;
float rt_x = 0.0f, rt_y = 0.0f, rt_z = 0.0f, rt_zz = -2.7f;




void init_intro() {
	rt_x = 0.0f;
	rt_y = 0;
	rt_z = 0;
	rt_zz = -2.7f;
	mohwnd.setScreen(ID_INTRO);
}


void render_intro() { 
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,rt_zz);

	if(rt_pressed == true) {

		glTranslatef(0.0f,0.0f,.3f);
		glRotatef(rt_x,1.0f,0.0f,0.0f);
		glRotatef(rt_z,0.0f,0.0f,1.0f);
	}


	game_textures[0].bindTexture();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

	
	if(getSync()) {
	rt_x += 0.5f;

	if(rt_x > 200) {
		rt_z += -0.5;
		rt_y += 0.5f;
		rt_x += 0.5f;
		rt_zz -= 0.2f;
	}
	}

	if(rt_zz < -80) {
		rt_pressed = false;
		mohwnd.setScreen(ID_START);
		return;
	}
	

	if(rt_pressed == false) {
		glPushMatrix();
		glLoadIdentity();
		game_textures[1].bindTexture();
		glTranslatef(-0.3f,0.3f,-1.0f);
		font.printtextf(0.0f,0.0f,"Press Enter to Continue.\n");
		glPopMatrix();
	}
}

static int cursor = 0;
static float qrotate = 0.0f;
int i = 0, z  = 0;
int intro_count = 5;

void render_start() {
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(-10.0f,15.0f,-55.0f);
	game_textures[1].bindTexture();
	font.printtextf(1.5f,2.0f,"MasterPiece 3D");
	if(playing == true)
		font.printtextf(3.5,-9.0f,"Resume Game");
	else
		font.printtextf(3.5,-9.0f,"Start");
	font.printtextf(3.5,-12.0f,"Highscores");
	font.printtextf(3.5,-15.0f,"Credits");
	font.printtextf(3.5,-18.0f,"Exit");
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
	case 3: 
		y = -18.0f;
		break;
	}
	font.printtextf(-1.0,y,"=)>");
	glPopMatrix();


	if(rt_zz < -55.0f && intro_count != 0) {
		glTranslatef(-10.0f,15.0f,rt_zz);
	
		rt_zz += 0.5f;
				static bool odd = true;
		if(!(odd = !odd)) {
			intro_count -= 1;
		}
	}
	else {
		glTranslatef(-10.0f,15.0f,-55.0f);
	}
	glTranslatef(0.0f,0.0f,-20.0f);
	glRotatef(qrotate,1.0f,1.0f,1.0f);


	if(getSync()) {
	
	qrotate -= .5f;
	if(qrotate < -1080)
		qrotate = 0;
	}


	for(i = 0; i < 17-intro_count; i++)
	{
		for(z = 0; z < 8-intro_count; z++)
		{
			static int sw = 0;
			sw = !sw;
			game_textures[sw == 0 ? 0 : 2].bindTexture();

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
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

void render_credits() {

	credits.render_credits();


}

void render(int screen) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	switch(screen) {
		case ID_INTRO:
			render_intro();
			break;
		case ID_START:
			render_start();
			break;
		case ID_GAME:
			render_game();
			break;
		case ID_CREDITS:
			render_credits();
			break;
		case ID_HIGHSCORES:
			render_scores();
			break;
	}
	SwapBuffers(g_hDC);
}

bool keyed_up = false;

void keydown(int key) {
	switch(mohwnd.getScreen()) {
		case ID_INTRO:
			switch(key) {
		case VK_RETURN:
			rt_pressed = true;
			break;
			}
			break;
		case ID_CREDITS: {
			if(key == VK_ESCAPE)
				mohwnd.setScreen(ID_START);
						 }
						 break;
		case ID_START: {
			switch(key) {
		case VK_UP:

			if(keyed_up == true) {
				if(cursor > 0)
					cursor--;
				keyed_up = false;
			}
			return;
			break;
		case VK_DOWN:

			if(keyed_up == true) {
				if(cursor < 3) 
					cursor++;
			}
			keyed_up = false;
			return;
			break;
		case VK_RETURN:
			switch(cursor) {
		case 0:
			if(playing == true) {
				mohwnd.setScreen(ID_GAME);
			}
			else {
				playing = false;
				mohwnd.setScreen(ID_GAME);
				clearboard();
			}
			break;
		case 1: 
			mohwnd.setScreen(ID_HIGHSCORES);
			return;
			break;
		case 2:
			mohwnd.setScreen(ID_CREDITS);
			credits.initFlash(false);
			break;
		case 3:
			mohwnd.kill();
			break;
			}
			break;
			}

					   }
					   break;
		case ID_GAME: {
			if(key == VK_ESCAPE) {
				mohwnd.setScreen(ID_START);
				playing = true;
			}
					  }
					  break;
	}

	if(enter == 0 && keyed_up == true) {
		keydown(key,0,0);
		keyed_up = false;
	}
	else
		keydown(key,0,0);


	specialkey(key,0,0);
}

void keyup(int key) {
	keyed_up = true;

}

void mousedown(int button, int x, int y) {


}

void mousemove(int x, int y) {


}

void cleanup() {
	exit(0);
}



void init_() {
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	font.BindFont("Courier New", -24);
	loadTextures();
	for(int i = 0; i <= 5; i++) {
		game_textures[i].loadTexture(i);
	}
	game_textures[5+1].loadTexture(textures[5+1]);
	game_textures[5+2].loadTexture(textures[5+2]);
	game_textures[5+3].loadTexture(textures[5+3]);
	credits.initFont(&font);
	credits.initTextures(game_textures);
	init_intro();
	mohwnd.initTimerCallback(1,timerfunc);
}


int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR line , int cmdShow) {

	mohwnd.createMasterOGL("MasterPiece 3D 2.1",640,480,false,LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)), LoadCursor(NULL, IDC_ARROW));
	mohwnd.initCallBacks(keydown,keyup,mousemove,mousedown);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	init_();
	mohwnd.initLoop(render);
	cleanup();
	return 0;
}

int getSync() { 
	static unsigned int count = GetTickCount();
	if(count < GetTickCount()) {
	count = GetTickCount();
	return 1;
 }
return 0;
}

