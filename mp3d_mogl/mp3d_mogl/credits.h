/*
   The Credits class 
   shout outs to my friends and family
   easy to use and understand
   written by Jared Bruni
   for free
   you may use this for whatever you want free of charge
   just dont sell it =)
*/

#ifndef __CREDITS__H_
#define __CREDITS__H_
#include "mogl.h"
#include "game.h"


struct Credit {
	float x;
	float y;
	char str[255];
};

struct Credit creditz[] = { {0,0,"LostSideDead Presents [press esc to exit]"}, {0,0, "A Jared Bruni Production"}, {0,0," MasterPiece 3D 2.1"}, {0,0, "Shout outs goto Peeps at PSC"}, {0,0, "My family"}, {0,0,"The girls I got my eye on ;]"}, {0,0,"Thanks goes out to"}, {0,0, "OpcodeVoid, EmuPaul for the mirrors"}, {0,0, "thepiratebay.org for the awesome tracker"}, {0,0,"And everyone else I know"} };
extern int getSync();


class Credits {
	MasterFont *font;
	MasterTexture *textures;
public:

	Credits() {
		font = 0;
		prev_credit = 0;
		pos = 1;
		release_credit();
		already = false;
	}

	Credits(MasterFont *font) {
		initFont(font);
		release_credit();
	}

	void initFont(MasterFont *font) {
		this->font = font;
		prev_credit = 0;
		pos = 1;
		already = false;
	}

	void initTextures(MasterTexture *textures) {
		this->textures = textures;
	}
	int pos;
	int prev_credit;
	float rt_x, rt_y, rt_z, rt_zz;
	bool already;

	void render_credits() {

		glPushMatrix();
		glLoadIdentity();
		glTranslatef(0.0f,0.0f,-5.0f);
		glRotatef(rt_x,1.0f,0.0f,0.0f);
		glRotatef(rt_y,0.0f,1.0f,0.0f);
		glRotatef(rt_z,0.0f,0.0f,1.0f);
		if(already == true) {
		 static int sw = 0;
		 sw = !sw;
		 game_textures[sw == 0 ? 6 : 8].bindTexture();
		}
		else
			game_textures[2].bindTexture();
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
		rt_x += 0.5f;
		rt_y += 0.5f;
		rt_z += 0.5f;

		glPopMatrix();
		glPushMatrix();
		glLoadIdentity();
		
		game_textures[1].bindTexture();
		glTranslatef(-0.5f,0.3f,-1.0f);
		font->printtextf(0.0f,0.0f,creditz[0].str);
		glLoadIdentity();
		for(int i = 1; i <= pos; i++) {
			game_textures[rand()%8].bindTexture();
			if(creditz[i].x != 1) {
				glTranslatef(-0.5f,-0.3f+creditz[i].y,-1.0f);
				font->printtextf(0.0f,0.0f,creditz[i].str);

				if(getSync())
				creditz[i].y += .001f;


				if(creditz[i].y > .5f) {
					creditz[i].x = 1;
					release_credit();
			}
			}

		}
		glPopMatrix();
	}

	void release_credit() {
		if(pos < 9)
			pos++;
		else {
			pos = 1;
			for(int i = 0; i < 9; i++) {
				creditz[i].y = 0;
				creditz[i].x = 0;
			}
			already = true;
		}
	}

	void initFlash(bool flash) {
		this->already = flash;
	}

};



#endif
