#include "mxglut.h"

namespace mx {

	mxEvent *global_event = 0;
	mxGlut  *global_glut = 0;

	void mxEvent::glut_render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		global_event->render();
		glutSwapBuffers();
	}

	void mxEvent::glut_keydown(unsigned char key, int x, int y) {
		global_event->keydown(int(key),x,y);
	}

	void mxEvent::glut_special(int key, int x, int y) {
		global_event->keydown(key,x,y);
	}

	void mxEvent::glut_idle() {
		global_event->idle();
	}

	mxGlut::mxGlut(int *argc, char **argv, std::string title, int x, int y, int w, int h) {

		glutInit(argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
		glutInitWindowSize(w,h);
		glutInitWindowPosition(x,y);
		glutCreateWindow(title.c_str());
		this->init();
		glutDisplayFunc(mxEvent::glut_render);
		glutReshapeFunc(mxEvent::glut_reshape);
		glutKeyboardFunc(mxEvent::glut_keydown);
		glutSpecialFunc(mxEvent::glut_special);
		glutIdleFunc(mxEvent::glut_idle);
		global_glut = this;
	}

	mxGlut::~mxGlut() {
		if(global_event != 0)
			delete global_event;
	}

	void mxGlut::init() {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
	}

	
	void mxGlut::GenerateTextures(GLuint num, GLuint *tex_array) {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(num, tex_array);
	}

	bool mxGlut::BindTextures(mxTexture tex, GLuint *tex_array, GLuint index)  {
		glBindTexture(GL_TEXTURE_2D, tex_array[index]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.raw_data);
		glEnable(GL_TEXTURE_2D);
		return true;
	}

	int mxGlut::EventLoop() {

		glutMainLoop();

		return 0;
	}

	bool mxGlut::SetEventHandler(mxEvent *event) {
		if(global_event != 0)
			delete global_event;
		global_event = event;
		return true;
	}

	mxTexture::mxTexture(std::string fname) {
		raw_data = 0;
		if(!this->LoadBMP(fname))
			std::cout << "Error loading texture!\n";
	}

	mxTexture::~mxTexture() {
		if(raw_data)
			free(raw_data);
	}

	bool mxTexture::LoadBMP(std::string source) {
				FILE *fptr = 0;
			long offset, size;
			short type, bitcount;
			if(raw_data) {
				free(raw_data);
				raw_data = 0;
			}

			fptr = fopen(source.c_str(),"rb");
			if(!fptr)
				return false;
			fread(&type, sizeof(short), 1, fptr);
			if(type != 0x4D42) {
				fclose(fptr);
				return false;
			}

			fseek(fptr, 10, SEEK_SET);
			fread(&offset, sizeof(long), 1, fptr);
			fseek(fptr, 4, SEEK_CUR);
			fread(&width, sizeof(long), 1, fptr);
			fread(&height, sizeof(long), 1, fptr);
			fseek(fptr, 2, SEEK_CUR);
			fread(&bitcount, sizeof(short), 1, fptr);
			if(bitcount != 24) {
				fclose(fptr);
				return false;
			}
			fseek(fptr, 4, SEEK_CUR);
			fread(&size, sizeof(long), 1, fptr);
			fseek(fptr,16,SEEK_CUR);
			
			raw_data = (GLubyte*) malloc ( (width * height) * 4 );

			GLubyte *ptr = raw_data;

			if(!raw_data) {
				fclose(fptr);
				return false;
			}
			int i = 0;
			int x, y,q;

			for(y = height-1; y > -1; y--)
			{
				for(x = 0; x < width; x++)
				{
					q = x + y * width;
					GLubyte b,g,r,w;
					b = fgetc(fptr);
					g = fgetc(fptr);
					r = fgetc(fptr);
					w = 255;
					*ptr = r;
					ptr++;
					*ptr = g;
					ptr++;
					*ptr = b;
					ptr++;
					*ptr = 255;
					ptr++;
				}
				for(i = 0; i < width % 4; i++)
					fgetc(fptr);
			}

			fclose(fptr);
			return true;
	}

}