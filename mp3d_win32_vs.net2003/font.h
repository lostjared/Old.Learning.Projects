/***************************************************************************
                          font.h  -  description
                             -------------------
    begin                : Sat Aug 23 2003
    written by           : Jared Bruni
    email                : jared@lostsidedead.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
void buildfont();
void killfont();
void printtextf(float x, float y, const char *str, ...);

#ifdef _WIN32

#include<windows.h>

unsigned int base = 0;
 HDC hDC = GetDC(FindWindow(NULL,"MasterPiece 3D"));

void buildfont()
{
  HFONT font;
  HFONT oldfont;
 
  base = glGenLists(96);
  font = CreateFont(-15,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,FF_DONTCARE|DEFAULT_PITCH,"Courier New");
  oldfont = (HFONT)SelectObject(hDC, font);
  wglUseFontBitmaps(hDC, 32, 96, base);
  SelectObject(hDC, oldfont);
  DeleteObject(font);
}

void killfont()
{
  glDeleteLists(base, 96);
}

void printtextf(float x, float y, const char *str, ...)
{
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

#else
#include<GL/glx.h>

unsigned int base = 0;

void buildfont()
{
  Display *dp;
  XFontStruct *font_info;
  base = glGenLists(96);
  dp = XOpenDisplay(0);

  font_info = XLoadQueryFont(dp, "-adobe-helvetica-medium-r-normal--18-*-*-*-p-*-iso8859-1");
    if (font_info == 0)
    {
      font_info = XLoadQueryFont(dp, "fixed");
      if (font_info == 0)
      {
        printf("no X font available?\n");
      }
    }

   glXUseXFont(font_info->fid, 32, 96, base);
   XFreeFont(dp, font_info);
   XCloseDisplay(dp);
}

void killfont()
{
  glDeleteLists(base, 96);
}

void printtextf(float x, float y, const char *str, ...)
{
  glRasterPos2f(x,y);
  va_list list;
  char string[5000];
  va_start(list, str);
  vsprintf((char*)string,str,list);
  va_end(list);
  glPushAttrib(GL_LIST_BIT);
  glListBase(base - 32);
  glCallLists(strlen(string), GL_UNSIGNED_BYTE, string);
  glPopAttrib();
}

#endif

