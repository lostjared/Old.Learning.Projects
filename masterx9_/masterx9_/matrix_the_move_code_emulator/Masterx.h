

#ifndef __MASTERX__H_
#define __MASTERX__H_

#include "mx3d.h"
extern mxHwnd __mxhwnd;
#define FAST __fastcall
#define XSTD __stdcall
// Main function
int __stdcall MasterMain(HINSTANCE hInst, char *line);
HFONT MakeFont(char* ftype, int size);


class MasterGameObject 
{
public:
	virtual void load() = 0;
	virtual void update() = 0;
};


struct MasterScreen {
	mxScreen mxscr;
};

class MasterText
{
public:
	MasterScreen*  scr;
	COLORREF bk;
	COLORREF text;
	inline void MasterText::init(MasterScreen *scr) {
		this->scr = scr;
	}

	inline void MasterText::printtext(char *str, int x, int y) {
		__mxhwnd.text.printtextf(x,y,str);
	}

	inline void MasterText::sprinttext(int x, int y, char *str, ...) {
		char text[5000];
		va_list list;
		va_start(list, str);
		vsprintf((char*)text,str,list);
		va_end(list);
		__mxhwnd.text.printtextf(x,y,str);
	}

	inline void MasterText::printtextrect(char *str, int x, int y, int w, int h) {
		__mxhwnd.text.printtextf(x,y,str);
	}

	inline void MasterText::printtextunderline(char *str, int x, int y) {
		__mxhwnd.text.printtextf(x,y,str);
	}

	inline void MasterText::setbkcolor(COLORREF color) {
		// removed only left here for backwards compatbility
	}

	inline void MasterText::settextcolor(COLORREF color) {
		__mxhwnd.text.settextcolor(D3DCOLOR_XRGB(GetRValue(color),GetGValue(color),GetBValue(color)));
	}

	inline void MasterText::setfont(HFONT font) {
		__mxhwnd.text.setfont(font);
	}

	inline void MasterText::setdefaultfont() {
		// to do
	}

	inline void MasterText::setunderfont(HFONT font) {
		// to do
	}
};

typedef class MasterGraphic
{
	MasterScreen* scr;
	//LPDIRECTDRAWSURFACE surf;
	mxSprite surf;
	char  filename[50];
	bool ckey;
public:
	int w;
	int h;
	inline void MasterGraphic::init(MasterScreen* scr) {
		this->scr = scr;
	}
	inline bool MasterGraphic::LoadGraphic(char* filename) {
		this->surf.init(&__mxhwnd.screen);
		this->surf.load(filename);
		w = surf.w;
		h = surf.h;
		return true;
	}
	inline bool MasterGraphic::LoadGraphic(char* filename,MasterScreen* scr) {
		this->surf.init(&__mxhwnd.screen);
		this->surf.load(filename);
		w = surf.w;
		h = surf.h;
		return true;
	}
	inline void MasterGraphic::ReLoadGraphic() {
		// left for backwards compatiblity
	}
	inline void MasterGraphic::SetColorKey(COLORREF r) {
		this->surf.setcolorkey(D3DCOLOR_XRGB(GetRValue(r),GetGValue(r),GetBValue(r)));
	}
	inline void MasterGraphic::DisplayGraphic(int x, int y) {
		__mxhwnd.screen.pd3d_dev->BeginScene();
		this->surf.display((float)x,(float)y);
		__mxhwnd.screen.pd3d_dev->EndScene();
	}
	inline void MasterGraphic::DisplayGraphicEx(int bx, int by, int bw, int bh,int image_x, int image_y) {
		__mxhwnd.screen.pd3d_dev->BeginScene();
		this->surf.display_ex((float)image_x,(float)image_y,bx,by,bw,bh,1.0f,1.0f,0.0f);
		__mxhwnd.screen.pd3d_dev->EndScene();
	}
	MasterGraphic::~MasterGraphic() {}
	MasterGraphic::MasterGraphic() {}
	inline void MasterGraphic::Release() {
		this->surf.~mxSprite();
	}
}MasterSprite;

extern mxSound dxsound;

class MasterSound
{
public:
	mxWave pSound;
	inline bool MasterSound::LoadSound(IDirectSound* pds,LPCTSTR name) {
		/*if(m_pDS == 0)
		dxsound.Init(__mxhwnd.hwnd);
		this->pSound.load(name);*/
		return true;
	}

	inline bool MasterSound::LoadSoundEx(char filename[]) {
		if(m_pDS == 0)
			dxsound.Init(__mxhwnd.hwnd);
		this->pSound.load(filename);
		return true;
	}
	inline void MasterSound::Play() {
		this->pSound.Play();
	}
	inline bool MasterSound::PlayStatus() {
		return this->pSound.is_playing();
	}
	inline void MasterSound::Release() {
		this->pSound.~mxWave();
	}
	MasterSound::MasterSound() {}
	MasterSound::~MasterSound() {}
};

class MasterPaint
{
	MasterScreen* scr;
public:

	void MasterPaint::init(MasterScreen *scr) {
		this->scr = scr;
	}

	void MasterPaint::mxanglearc(int x, int y, long radius, float startangle, float sweepangle, COLORREF outline) {
		__mxhwnd.paint.drawanglearc (x,y,radius,startangle,sweepangle,outline,outline);
	}

	void FAST MasterPaint::mxdrawrect(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline) {
		__mxhwnd.paint.drawrect(x,y,x2,y2,D3DCOLOR_XRGB(GetRValue(fill),GetGValue(fill),GetBValue(fill)));
	}
	void FAST MasterPaint::mxdrawroundrect(int x, int y, int x2, int y2,int cw, int ch, COLORREF fill,COLORREF outline) {
		__mxhwnd.paint.drawroundrect(x,y,x2,y2,cw,ch,fill,outline);
	}
	void FAST MasterPaint::mxdrawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,COLORREF fill, COLORREF outline) {
		__mxhwnd.paint.drawpie(x,y,x2,y2,nx,ny,nx2,ny2,fill,outline);
	}
	void FAST MasterPaint::mxdrawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, COLORREF fill, COLORREF outline) {
		__mxhwnd.paint.drawchord(x,y,x2,y2,nx,ny,nx2,ny2,fill,outline);
	}
	void FAST MasterPaint::mxdrawellipse(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline) {
		__mxhwnd.paint.drawellipse(x,y,x2,y2,fill,outline);
	}
	void FAST MasterPaint::mxsetpixel(int x, int y, COLORREF rgbval) {
		__mxhwnd.paint.drawpixel(x,y,rgbval);
	}
	COLORREF FAST MasterPaint::mxgetpixel(int x, int y) {
		return __mxhwnd.paint.drawgetpixel(x,y);
	}
	void FAST MasterPaint::mxarc(int x1,int x2, int x3, int x4, int x5, int x6, int x7, int x8,COLORREF fill,COLORREF outline) {
		__mxhwnd.paint.drawarc(x1,x2,x3,x4,x5,x6,x7,x8,fill,outline);
	}
	void FAST MasterPaint::mxpolygon(CONST POINT* point,int n_points,COLORREF fill,COLORREF outline) {
		__mxhwnd.paint.drawpolygon(point,n_points,fill,outline);
	}
	void FAST MasterPaint::mxlineto(int x, int y,COLORREF fill,COLORREF outline) {
		__mxhwnd.paint.drawlineto(x,y,fill,outline);
	}
	void FAST MasterPaint::mxhorizontalline(int x, int x2, int y,COLORREF color) {
		__mxhwnd.paint.drawrect(x,y,x2,y+1,D3DCOLOR_XRGB(GetRValue(color),GetGValue(color),GetBValue(color)));
	}
	void FAST MasterPaint::mxverticalline(int y1,int y2,int x,COLORREF color) {
		__mxhwnd.paint.drawrect(x,y1,x+1,y2,D3DCOLOR_XRGB(GetRValue(color),GetGValue(color),GetBValue(color)));
	}
	void FAST MasterPaint::mxline(int start_x, int start_y, int stop_x, int stop_y,COLORREF color) {
		__mxhwnd.paint.drawline(start_x,start_y,stop_x,stop_y,color);
	}
};

class MasterMedia {

private:

	//gets error number
	long a;
	//for getshortpath
	char finname[1000];
	//to put string together
	char todo[2000];

	//error code
	void error(long what){
		mciGetErrorString(what, err, 128);
	}

public:

	char cfile[255];
	//this is where the error is stored
	char err[10000];
	//this is the alias name of the file ex. mpeg
	char alias[100];
	//tells u the status of a file
	TCHAR statuss[40];
	//tells u the position number(millisec)
	TCHAR p[40];
	//tells u the lenght number(millisec)
	TCHAR l[40];

	//opens files and dose not put them in a window
	void open(char file[1000]){
		if(GetShortPathName(file, finname, 1000) != 0){
			strcpy(cfile,file);
			fopen(finname);
		}
	}

	// get a pointer to the name of the currently opened file
	char* openedfile()
	{
		return (char*) cfile;
	}


	// open mp3
	void openmp3(char file[1000])
	{ 
		strcpy(alias,"mpeg");
		open(file);
	}

	/*if you have the short path name call to this
	by doing this the file will load faster
	opens files and dose not put them in a window*/
	void fopen(char file[1000]){
		close();
		sprintf(todo, "open %s type mpegvideo Alias %s", file, alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
	}

	//open files and puts them in a parent space
	void vidopen(char file[1000], HWND parent){
		if(GetShortPathName(file, finname, 1000) != 0){
			fvidopen(finname, parent);
		}
	}

	/*if you have the short path name call to this
	by doing this the file will load faster
	open files and puts them in a parent space*/
	void fvidopen(char file[1000], HWND parent){
		close();
		sprintf(todo, "open %s type mpegvideo Alias %s parent %s Style 1073741824", file, alias, parent);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
	}

	//play file
	void play(){
		sprintf(todo, "Play %s from 0", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	//stop file
	void stop(){
		sprintf(todo, "Stop %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	//pause file
	void pause(){
		sprintf(todo, "Pause %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	//resume file
	void resume(){
		sprintf(todo, "Resume %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	//close file
	void close(){
		sprintf(todo, "Close %s", alias);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	/*for poistion and lenght error code will now work winmm.dll returns too big of a char
	to ask for the error code it has to be an int but since we cannt use a int we cannt use
	error code here*/
	//get the poistion of a file

	unsigned long poistion(){
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0 ,0, 0);
		sprintf(todo, "status %s position", alias);
		mciSendString (todo, p, 40, 0);

		return ( unsigned long ) atol(p);
	}

	//gets the length of a file
	unsigned long length(){
		sprintf(todo, "set %s time format milliseconds", alias);
		mciSendString (todo, 0, 0, 0);
		sprintf(todo, "status %s length", alias);
		mciSendString (todo, l, 40, 0);
		return ( unsigned long ) atol (p);
	}

	//changes volume sp = speaker vol = what the volume should be set at
	void volume(char sp[6], long vol){
		vol = vol * 10;
		sprintf(todo, "setaudio %s %s Volume to %d", alias, sp, vol);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	//resize the video
	void resizevid(int left, int top, int width, int height){
		sprintf(todo, "put %s window at %i %i %i %i", alias, left, top, width, height);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	//seek somewhere with in the file
	void seekto(int where){
		where = where * 1000;
		sprintf(todo, "set %s time format milliseconds", alias);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
		sprintf(todo, "play %s from %i", alias, where);
		a = mciSendString(todo, 0, 0, 0);
		error(a);
	}

	//finds out the status of whats being played
	void status(){
		sprintf(todo, "status %s mode", alias);
		a = mciSendString(todo, statuss, 40, 0);
	}

	//set the speed of a file 1000 = normal below 1000 = slower above 1000 = faster
	//changes speed will make audio only come out the frount 2 speakers
	void speed(int spe){
		sprintf(todo, "set %s speed %i", alias, spe);
		a = mciSendString (todo, 0, 0, 0);
		error(a);
	}

	//auto repeat the file repeat [t] = true then repeat file false it wont or will stop
	void repeat(bool repeatt){
		if (repeatt == true){
			sprintf(todo, "play %s notify repeat", alias);
			a = mciSendString(todo, 0, 0, 0);
			error(a);
		}
		else{
			sprintf(todo, "play %s", alias);
			a = mciSendString(todo, 0, 0, 0);
			error(a);
		}
	}
};

typedef int MASTERSCREEN;
enum DisplayColor { COLOR_8, COLOR_16,COLOR_24,COLOR_32,COLOR_DEFAULT };

class MasterXHWND
{
	MASTERSCREEN mscr;

	int pre_time;
	int timer_count;

	bool time_flag;
	bool full_flag;

public:
	HWND hwnd;
	MasterScreen scr;
	MasterText   text;
	MasterPaint  paint;
	MasterMedia  media;
	bool alive;
	UINT activeapp;
	MasterXHWND() { full_flag = true; }
	void setfullflag(bool flag) {
		this->full_flag = flag;
	}
	inline bool MasterXHWND::CreateMasterX(char* mytitle,int width,int height,DisplayColor color,WNDPROC proc,HINSTANCE hInst,HICON icon,HCURSOR cursor) {
		if(__mxhwnd.Init(mytitle,full_flag,CW_USEDEFAULT,CW_USEDEFAULT,width,height,proc,icon)) {
			int bpp;
			switch(color) {
			case COLOR_8:
			bpp = 8;
			break;
			case COLOR_16:
			bpp = 16;
			break;
			case COLOR_24:
			bpp = 24;
			break;
			case COLOR_32:
			bpp = 32;
			break;
			case COLOR_DEFAULT:
			bpp = 24;
			break;
			}
			return __mxhwnd.InitDX(full_flag,bpp);
		}

		return false;
	}
	inline WPARAM MasterXHWND::InitLoop( void (* render) (int xscr)) {
		return __mxhwnd.InitLoop(render);
	}
	inline void MasterXHWND::Kill() {
		__mxhwnd.Kill();
	}
	inline MASTERSCREEN  MasterXHWND::GetScreen() {
		return this->mscr;
	}
	inline void MasterXHWND::SetScreen(MASTERSCREEN xmscr) {
		this->mscr = xmscr;
	}
	inline LRESULT MasterXHWND::SendMasterMessage(UINT msg,WPARAM wParam,LPARAM lParam) {
		return SendMessage(__mxhwnd.hwnd,msg,wParam,lParam);
	}
	inline void MasterXHWND::clear() {}
	inline void MasterXHWND::mx_update() {}

	inline bool MasterXHWND::LoadGraphic(MasterGraphic* g, char* filename) {
		return g->LoadGraphic(filename,&scr);
	}
	inline bool MasterXHWND::LoadSound(MasterSound* s,LPCSTR resourceID) {
		return s->LoadSound(NULL,resourceID);
	}
	inline bool MasterXHWND::KeyCheck(int key) {
		return __mxhwnd.input.key.KeyCheck(key);
	}
	inline bool MasterXHWND::AsyncKeyCheck(int key) {
		if(GetAsyncKeyState(key))
			return true;
		return false;
	}
	inline void MasterXHWND::InitTimer(int id, int interval) {
		SetTimer(__mxhwnd.hwnd,id,interval,NULL);
	}
	inline void MasterXHWND::DestroyTimer(int id) {
		KillTimer(__mxhwnd.hwnd,id);
	}
	inline void MasterXHWND::GetMousePosWin(long& x, long& y) {
		x = __mxhwnd.input.mouse.cur_pos.x;
		y = __mxhwnd.input.mouse.cur_pos.y;
	}
	inline void MasterXHWND::HideCursor() {
		ShowCursor(FALSE);
	}
	inline void MasterXHWND::RestoreCursor() {
		ShowCursor(TRUE);
	}
	inline bool MasterXHWND::TimeChange() {
		if(pre_time == timer_count) {
			return false;
		}
		pre_time = timer_count;
		return true;
	}
	inline void MasterXHWND::ChangeTime() {
		timer_count++;

		if(timer_count > 100)
		{
			timer_count = 0;
		}

	}
	inline void MasterXHWND::SetTimeFlag() {
		time_flag = TimeChange();
	}
	inline bool MasterXHWND::SyncChange() {
		return time_flag;
	}

	inline HFONT CreateMasterFont(char* font_name,int size) {
		return MakeFont(font_name,size);
	}
};

class MasterJoyStick {
public:
	mxJoystick stick;

	bool JoyExisit() {
		return joy_exisits;

	}
	bool SetupJoystick()  {
		stick.Init(__mxhwnd.hwnd,__mxhwnd.input.pdi);
	}
	int JoyButtonDown() {

		stick.Update();
		for(int i = 0; i < 128; i++)
		if(stick.joy_st.rgbButtons[i] & 0x80)
			return i;

		return -1;
	}

};

struct ScreenObject
{
	MASTERSCREEN sub_screen;
	MasterXHWND* mxhwnd;
	
	inline Init(MasterXHWND* mxhwndx)
	{
		mxhwnd = mxhwndx;
	}
	
	inline MASTERSCREEN getscreen()
	{
		return sub_screen;
	}
	
	inline void setscreen(MASTERSCREEN xscreen)
	{
		sub_screen = xscreen;
	}
};


#endif
