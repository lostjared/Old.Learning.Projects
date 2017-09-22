#include<string>
#include<iostream>
#include<glut.h>
#include<memory.h>


namespace mx {

	class mxEvent {
	public:
		virtual void render()  {}
		virtual void keydown(int key, int x, int y) {}
		virtual void reshape(int x, int y) {}
		virtual void mousemove(int x, int y, int button) {}
		virtual void mouseclick(int x, int y, int button) {}
		virtual void idle() {}

		static void glut_render();
		static void glut_idle();

		static void glut_reshape(int w, int h) {
			if(h == 0) h = 1;
			glViewport(0,0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
			glMatrixMode(GL_MODELVIEW);							
			glLoadIdentity();
		}
		static void  glut_keydown(unsigned char key, int x, int y);
		static void  glut_special(int key, int x, int y);
	};

	class mxGlut;

	class mxTexture {
	public:
		int width, height;
		mxTexture(std::string fname);
		~mxTexture();
		bool LoadBMP(std::string fname);
	protected:
		GLubyte *raw_data;
		friend class mxGlut;
	};

	class mxGlut {
	public:
		mxGlut( int *argc, char **argv, std::string title, int x, int y, int w, int h );
		~mxGlut();
		bool SetEventHandler(mxEvent *event);
		int  EventLoop();
		void GenerateTextures(GLuint num, GLuint *tex_array);
		bool BindTextures(mxTexture tex, GLuint *tex_array, GLuint index);
	protected:
		void init();
	};

	extern mxEvent *global_event;
	extern mxGlut  *global_glut;

}