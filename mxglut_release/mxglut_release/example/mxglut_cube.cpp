#include "mxglut.h"


class mpIntro : public mx::mxEvent {
protected:
	float spin_x, spin_y, spin_z;
	float dist;
	mx::mxTexture tex;
	GLuint tex_name[1];

public:

	mpIntro() : tex("img\\logo.bmp") {
		spin_x = 0.0f;
		spin_y = 0.0f;
		spin_z = 0.0f;
		dist = -2.8f;
		axis = 0;
		mx::global_glut->GenerateTextures(1, tex_name);
		mx::global_glut->BindTextures(tex, tex_name, 0);
		start = going = false;
	}

	virtual void render()  {

		glLoadIdentity();

		glTranslatef(0.0f, 0.0f, dist);
		switch(axis) {
			case 0:
				glRotatef(spin_x, 0.0f, 0.0f, 1.0f);
				break;
			case 1:
				glRotatef(spin_x, 1.0f, 0.0f, 0.0f);
				break;
			case 2:
				glRotatef(spin_x, 1.0f, 1.0f, 0.0f);
				break;
			case 3:
				glRotatef(spin_x, 1.0f, 1.0f, 1.0f);
				break;
		}
		glBindTexture(GL_TEXTURE_2D, tex_name[0]);
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

	}

	virtual void keydown(int key, int x, int y) {


		switch(key) {
			case 27:
				exit(0);
				break;
			case 13:
				start = true;
				break;
			case 101:
				axis = 1;
				break;
			case 103:
				axis = 2;
				break;
			case 102:
				axis = 3;
				break;
			case 100:
				axis = 0;
				break;
		}

	}

	virtual void idle() {

		if(start == true) {
			spin_x += 1.0f;
			dist -= 0.001f;

			if(dist <= -20.0f) {
				going = true;
				start = false;
			}
		}
		else if(going == true) {
			dist += 0.01f;
			spin_x -= 1.0f;
			if(dist > 1.0f) {
				going = false;
				start = true;
			}
		}
		glutPostRedisplay();
	}

private:
	bool start,going;
	int axis;

};


int main(int argc, char **argv) {
	mx::mxGlut mxg(&argc, argv, "mxGlut_cubeapp [ press enter to begin ]", 0,0,640,480);
	mxg.SetEventHandler( new mpIntro );
	mxg.EventLoop();
	return 0;
}