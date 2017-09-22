/* Master OpenGL Wrapper
   written by Jared Bruni
   for free
   you may use this for whatever you want free of charge
   just dont sell it =)

*/


#ifndef __MOGL__H_
#define __MOGL__H_

#include<windows.h>
#include<gl/gl.h>
#include<gl/glu.h>
#include<gl/glaux.h>

#include<stdio.h>
#include<stdlib.h>


#define LBUTTON 1
#define RBUTTON 2
#define DEFAULT_PORT 02
#define JOY_DEADZONE 20 

LRESULT _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam, unsigned long lparam);
inline void SetupPixelFormat(HDC hDC);

struct HWND__* hwnd;
struct HDC__* g_hDC;
static int width,height;

void (*xkeypress)(int key);
void (*xkeyup) (int key);
void (*xmousemove)(int x, int y);
void (*xmouseclick)(int x, int y, int button);
void (*xtimerfunc)(int value);
bool Keys[255];


LRESULT _stdcall event(struct HWND__* hwnd, unsigned int msg, unsigned int wparam, unsigned long lparam)
{
	static HGLRC hRC; // rendering context
	static struct HDC__* hDC; // device context
	
	static int x,y;
	
	switch(msg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		wglMakeCurrent(hDC,NULL);
		wglDeleteContext(hRC);
		PostQuitMessage(0);
		break;
	case WM_CREATE:
		{
			hDC = GetDC(hwnd);
			g_hDC = hDC;
			SetupPixelFormat(hDC);
			// create the reendering contest
			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC,hRC);
		}
		break;
	case WM_SIZE:
		{
			width = LOWORD(lparam);
			height= HIWORD(lparam);
			
			if(height == 0)
			{
				height = 1;
			}
			
			glViewport(0,0,width,height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			
			gluPerspective(45.0f,(float)width/(float)height,0.1f,100.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			return 0;
		}
		break;
	case WM_KEYDOWN:
		{
			if(xkeypress)
			xkeypress(wparam);
			Keys[wparam] = true;
		}
		break;
	case WM_KEYUP:
		{
			Keys[wparam] = false; // trick I learned from nehe's tutorials
			if(xkeyup)
			xkeyup(wparam);
		}
		break;
	case WM_MOUSEMOVE:
		{
			x = LOWORD(lparam);
			y = HIWORD(lparam);
			if(xmousemove)
			xmousemove(x,y);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			x = LOWORD(lparam);
			y = HIWORD(lparam);
			if(xmouseclick)
			xmouseclick(x,y,LBUTTON);
		}
		break;
	case WM_RBUTTONDOWN:
		{
			x = LOWORD(lparam);
			y = HIWORD(lparam);
			if(xmouseclick)
			xmouseclick(x,y,RBUTTON);
		}
		break;
	case WM_TIMER: {
			if(xtimerfunc)
			xtimerfunc(wparam);
		}
		break;
	default: return DefWindowProc(hwnd,msg,wparam,lparam);
	}
	
	return (0);
}

class MasterOGLHWND
{
public:
	void createMasterOGL(char* title,int width, int height, bool fullscreen,HICON icon,HCURSOR cursor)
	{
		
		WNDCLASS wc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hbrBackground = NULL;
		wc.hCursor = cursor;//LoadCursor(NULL,IDC_ARROW);
		wc.hIcon = icon;//LoadIcon(NULL,IDI_APPLICATION);
		wc.hInstance = GetModuleHandle(NULL);
		wc.lpfnWndProc = (WNDPROC) event;
		wc.lpszClassName = "MasterOGL";
		wc.lpszMenuName = NULL;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		
		RegisterClass(&wc);
		if(fullscreen == false)
		{

		hwnd = CreateWindow("MasterOGL",title,WS_OVERLAPPEDWINDOW,0,0,width,height,0,0,GetModuleHandle(NULL),0);

		}
		else
		{
		    init_fullscreen(width,height);
			hwnd = CreateWindow("MasterOGL",title,WS_POPUPWINDOW,0,0,width,height,0,0,GetModuleHandle(NULL),0);
		}

		ShowWindow(hwnd,SW_SHOW);
		UpdateWindow(hwnd);
		glLoadIdentity();
		xkeyup = 0;
		xkeypress = 0;
		xmousemove = 0;
		xmouseclick = 0;
		xtimerfunc = 0;
		
	}

	void (*updatex)(int screen);
	bool done;
	int cur_screen;

	int initLoop(void(*update)(int screen))
	{
		updatex = update;
		MSG msg;
		done = false;
		
		while(done == false)
		{
			PeekMessage(&msg,hwnd,NULL,NULL,PM_REMOVE);
			if(msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				// render
				updatex(cur_screen);
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			
		}

		return (int)msg.wParam;
	}

	void setScreen(int x)
	{
		cur_screen = x;
	}

	int getScreen()
	{
		return cur_screen;
	}

	void kill()
	{
		done = true;
		PostQuitMessage(0);
	}

	void initCallBacks(void(*keypressx)(int key),void(*keyupx)(int key), void (*mousemovex)(int x,int y),void (*mouseclickx)(int x,int y, int button))
	{
		xkeypress = keypressx;
		xmousemove = mousemovex;
		xmouseclick = mouseclickx;
		xkeyup = keyupx;
	}

	void initMatrixMode(GLenum mode) {
		gluPerspective(45.0f,(float)width/(float)height,0.1f,100.0f);
		glMatrixMode(mode);
	}

	void initTimerCallback(int time_in_between,void (*timerfunc)(int) ) {
		SetTimer(hwnd,1,time_in_between,NULL);
		xtimerfunc = timerfunc;
	}

private:
	// initilize OpenGL, setup the pixel format
	inline void init_fullscreen(int w, int h)
	{
		DEVMODE dev;
		memset(&dev,0,sizeof(dev));
		
		dev.dmSize = sizeof(dev);
		dev.dmPelsWidth = w;
		dev.dmPelsHeight = h;
		dev.dmBitsPerPel = GetDeviceCaps(GetDC(NULL),BITSPIXEL);
		dev.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
		
		if(ChangeDisplaySettings(&dev,CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			MessageBox(NULL,"Error couldnt change display mode","Error",MB_ICONERROR);
		}
	}
	
};
// set the pixel format
inline void SetupPixelFormat(HDC hDC)
{
	int nPixelFormat;
	int bits = GetDeviceCaps(GetDC(NULL),BITSPIXEL);
	
	
	static	PIXELFORMATDESCRIPTOR pfd=					{
		sizeof(PIXELFORMATDESCRIPTOR),					
			1,								
			PFD_DRAW_TO_WINDOW |						
			PFD_SUPPORT_OPENGL |						
			PFD_DOUBLEBUFFER,						
			PFD_TYPE_RGBA,							
			bits,								
			0, 0, 0, 0, 0, 0,						
			0,								
			0,								
			0,								
			0, 0, 0, 0,							
			bits,								
			0,								
			0,								
			PFD_MAIN_PLANE,							
			0,								
			0, 0, 0								
	};
	
	
	nPixelFormat = ChoosePixelFormat(hDC,&pfd);
	
	SetPixelFormat(hDC,nPixelFormat,&pfd);
}

AUX_RGBImageRec *load_img(char *filename) {
	FILE *file = 0;					

	if (!filename)						
	{
		return NULL;					
	}

	file=fopen(filename,"r");			

	if (file)							
	{
		fclose(file);								
		return auxDIBImageLoad(filename);			
	}

	return 0;									
}

GLuint textures[11];
int tex_offset = 0;

AUX_RGBImageRec *TextureImage[11];

int loadTextures() {
	int Status=FALSE;	

	memset(TextureImage,0,sizeof(void *)*11);
	Status=TRUE;
	static char *images[] = {"block_black.bmp","block_ltblue.bmp", "block_red.bmp", "block_green.bmp", "block_dblue.bmp", "block_gray.bmp" };
	TextureImage[0] = load_img("img/logo.bmp");
	TextureImage[1] = load_img("img/block_clear.bmp");
	TextureImage[2] = load_img("img/credits.bmp");
	for(int p = 0; p <= 5; p++) {
		char buf[255];
		sprintf(buf,"img/%s", images[p]);
		TextureImage[p+3] = load_img(buf);
	}
	
	glGenTextures(9, textures);		
	for(int q = 0;q <= 8; q++) {
		glBindTexture(GL_TEXTURE_2D, textures[q]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[q]->sizeX, TextureImage[q]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[q]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}

	tex_offset = 0;

	for(int i = 0; i <= 8; i++) {
		if (TextureImage[tex_offset])									
		{
			if (TextureImage[tex_offset]->data)							
			{
				free(TextureImage[tex_offset]->data);					
			}

			free(TextureImage[tex_offset]);								
		}

		tex_offset++;
	}

	return Status;
}
	


class MasterTexture {
	
	int index;
public:
	int loadTexture(int off) {
		this->index = off;
		return 1;
	}
	void bindTexture() {
		glBindTexture(GL_TEXTURE_2D, textures[index]);
	}

};


unsigned int base = 0;


class MasterFont {

	void killfont()
	{
		glDeleteLists(base, 96);
	}
public:
	~MasterFont() {
		killfont();
	}
	void BindFont(const char *font_name, int size) {
		HFONT font;
		HFONT oldfont;
		base = glGenLists(96);
		font = CreateFont(size,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,FF_DONTCARE|DEFAULT_PITCH,font_name);
		if(!font) {
			MessageBox(hwnd,"Couldnt Create Font", "Error", MB_ICONERROR);
		}
		HDC hDC = GetDC(hwnd);
		if(!hDC) {
			MessageBox(hwnd,"Couldnt get the hDC handle", "Error", MB_ICONERROR);
		}
		oldfont = (HFONT)SelectObject(hDC, font);
		wglUseFontBitmaps(hDC, 32, 96, base);
		SelectObject(hDC, oldfont);
		DeleteObject(font);
	}

	void printtextf(float x, float y, const char *str, ...) {
		glRasterPos2f(x,y);
		va_list list;
		char string[5000];
		va_start(list, str);
		vsprintf((char*)string,str,list);
		va_end(list);
		glPushAttrib(GL_LIST_BIT);
		glListBase(base - 32);
		glCallLists((GLsizei)strlen(string), GL_UNSIGNED_BYTE, string);
		glPopAttrib();
	}

};

#endif