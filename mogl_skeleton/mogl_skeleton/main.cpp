/* Basic OpenGL App Skeleton using MasterOGL 
  written by Jared Bruni
 */

#include "mogl.h"


MasterOGLHWND mohwnd;

void render(int screen) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	// draw here
	SwapBuffers(g_hDC);
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszLine, int nCmdShow) {
	mohwnd.createMasterOGL("Test Window", 640,480, false, LoadIcon(NULL,IDI_APPLICATION), LoadCursor(NULL,IDC_ARROW));
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	return mohwnd.initLoop(render);
}
   