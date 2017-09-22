#pragma comment(lib,"comctl32.lib")

#include<windows.h>
#include<string>
#include<fstream>
#include<richedit.h>
#include"resource.h"
#include"browser.h"
#include"mxsocket.h"
#include"cpptok.h"
#include"dlg.h"


HWND hwnd,hlist,about,hcon,hlog,hpw,hb,chat_win,chat_view,chat_edit,hsn,hsn_list;
mxBrowser browser(L"http://www.lostsidedead.com/ip2ip_fserv/");
HFONT fnt;
mxSocket the_socket;
HBRUSH hbr = CreateSolidBrush(RGB(236,233,216));
HBITMAP the_bitmap = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP1));
WNDPROC OldProc;
char screen_name[14];
bool chat_enabled = true;
bool wel_enabled = true;
bool browser_started = false;
bool transfering = false;
HMENU hMenu = 0;

std::vector<std::string> sn_vec;
std::fstream *file = 0;

class Error {
public:
	Error(std::string str) {
		err_str = str;
	}
	const char *toString() const {
		return err_str.c_str();
	}
private:
	std::string err_str;
};

void StartConnect(std::string ip, int port);
void ProcDir(std::string &dir);
void SaveSettings();
void LoadSettings();
void SetTitle(const char *str);
void Log(const char *src, ...);



void OnConnect() {


}

void OnDisconnect() {
	int rt_val = 0;
	if(the_socket.s) {
		char qdata[256];
		memset(qdata,0,sizeof(qdata));
		sprintf(qdata,"**&&^^++--057MasterHost: %s has left the room", screen_name);
		rt_val = send(the_socket.s, qdata, sizeof(qdata), 0);
		memset(qdata,0,sizeof(qdata));
		sprintf(qdata,"exit.");
		rt_val = send(the_socket.s, qdata, sizeof(qdata),0);
		closesocket(the_socket.s);
		the_socket.s = 0;
	}
	if(file) {
		file->close();
		delete file;
	}

	SetTitle("IP2IP - FServ GUI - Disconnected.");
	Log("Disconnected!.");
	EnableWindow(hb,TRUE);
	SendMessage(hlist,LB_RESETCONTENT,0,0);
	ShowWindow(chat_win,SW_HIDE);
	EnableMenuItem(hMenu,ID_OPTIONS_ENABLECHAT, MF_ENABLED);
	ShowWindow(about,SW_HIDE);
	EnableWindow(hsn_list,FALSE);
	SendMessage(hsn_list,LB_RESETCONTENT,0,0);
}

void Log(const char *src, ...) {
	char data[5000];
	va_list l;
	va_start(l,src);
	vsprintf(data, src, l);
	va_end(l);
	LRESULT len = SendMessage(hlog,WM_GETTEXTLENGTH,0,0);
	sprintf(data,"%s\r\n", data);
	SendMessage(hlog,EM_SETSEL,len,len);
	SendMessage(hlog,EM_REPLACESEL, strlen(data), (LPARAM)(LPCSTR)data);
	len = SendMessage(hlog,WM_GETTEXTLENGTH,0,0);
	SendMessage(hlog,EM_SETSEL,len,len);

}

void Concat(HWND hlog, const char *src, ...) {
	char data[5000];
	va_list l;
	va_start(l,src);
	vsprintf(data, src, l);
	va_end(l);
	LRESULT len = SendMessage(hlog,WM_GETTEXTLENGTH,0,0);
	sprintf(data,"%s\r\n", data);
	SendMessage(hlog,EM_SETSEL,len,len);
	SendMessage(hlog,EM_REPLACESEL, strlen(data), (LPARAM)(LPCSTR)data);
	len = SendMessage(hlog,WM_GETTEXTLENGTH,0,0);
	SendMessage(hlog,EM_SETSEL,len,len);
	CHARRANGE sel;
	sel.cpMax = long(len);
	sel.cpMin = long(len);
	SendMessage(hlog,EM_EXSETSEL,0,(LPARAM)&sel);
	POINT p;
	SendMessage(hlog,EM_GETSCROLLPOS,0,(LPARAM)&p);
	p.y++;
	SendMessage(hlog,EM_SETSCROLLPOS,0,(LPARAM)&p);
}

void ConcatWOLB(HWND hlog, const char *src, ...) {
	char data[5000];
	va_list l;
	va_start(l,src);
	vsprintf(data, src, l);
	va_end(l); 
	LRESULT len = SendMessage(hlog,WM_GETTEXTLENGTH,0,0);
	SendMessage(hlog,EM_SETSEL,len,len);
	SendMessage(hlog,EM_REPLACESEL, strlen(data), (LPARAM)(LPCSTR)data);
	len = SendMessage(hlog,WM_GETTEXTLENGTH,0,0);
	SendMessage(hlog,EM_SETSEL,len,len);
	CHARRANGE sel;
	sel.cpMax = long(len);
	sel.cpMin = long(len);
	SendMessage(hlog,EM_EXSETSEL,0,(LPARAM)&sel);
}


void SetCharFormat(HWND hwnd, char *face_name, COLORREF color, bool bold, int height) {
	CHARFORMAT format;
	memset(&format, 0, sizeof(format));
	format.cbSize = sizeof(CHARFORMAT);
	format.crTextColor = color;
	format.dwMask = bold == true ? CFM_BOLD | CFM_COLOR | CFM_SIZE | CFM_FACE : CFM_SIZE | CFM_FACE | CFM_COLOR;
	format.dwEffects = bold == true ? CFM_BOLD : 0;
	format.yHeight = height;
	strcpy(format.szFaceName,face_name);
	SendMessage(hwnd,EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&format);
}


void SetTitle(const char *str) {
	SendMessage(hwnd,WM_SETTEXT,strlen(str),(LPARAM)(LPCSTR)str);
}

int lenspace(std::string src) {
	int len = 0;
	for(unsigned int i = 0; i < src.length(); i++)
	{
		if(src[i] != ' ' && src[i] != '\n' && src[i] != '\t')
			len++;
	}
	return len;
}

void AddRmvSnFromList(std::string &sn, std::string msg) {
	LRESULT len = SendMessage(hsn_list,LB_GETCOUNT,0,0), i = 0;
	EnableWindow(hsn_list,TRUE);
	if(sn == "MasterHost") {
		std::string user_sn = msg.substr(1, msg.find(" has"));
		if(msg.find("left") !=  -1 || msg.find("disconnected") != -1) {
			for(i = 0; i < len; i++) {
				char sn_buff[256];
				SendMessage(hsn_list,LB_GETTEXT,(WPARAM)i,(LPARAM)(LPCSTR)sn_buff);
				if(user_sn == sn_buff) {
					SendMessage(hsn_list,LB_DELETESTRING,(WPARAM)i,0);
				}
			}

		}
		else {
			bool add_ok = true;
			for(i = 0; i < len; i++) {
				char sn_buff[256];
				SendMessage(hsn_list,LB_GETTEXT,(WPARAM)i,(LPARAM)(LPCSTR)sn_buff);
				if(sn_buff == user_sn) {
					add_ok = false;
					break;

				}
			}

			if(add_ok == true)
				SendMessage(hsn_list,LB_ADDSTRING,user_sn.length(), (LPARAM)(LPCSTR)user_sn.c_str());
		}
	}
}

LRESULT CALLBACK ChatProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	switch(msg) {
		case WM_CLOSE:
			ShowWindow(hwnd,SW_HIDE);
			break;
		case WM_CREATE:
			{
				if(!(chat_view = CreateWindowEx(WS_EX_STATICEDGE,"RichEdit","",ES_AUTOVSCROLL | ES_DISABLENOSCROLL | ES_MULTILINE | WS_VSCROLL | WS_CHILD | WS_VISIBLE  |ES_READONLY, 10,10,615,400,hwnd,(HMENU)1,GetModuleHandle(0),0)))
					throw Error("Couldnt create chat view ! ");

				if(!(chat_edit = CreateWindowEx(WS_EX_STATICEDGE,"Edit","",ES_NOHIDESEL | WS_CHILD | WS_VISIBLE | ES_WANTRETURN | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, 10,410,615,25,hwnd,(HMENU)2,GetModuleHandle(0),0)))
					throw Error("Couldnt create chat edit! ");

				SendMessage(chat_view,WM_SETFONT,(WPARAM)(HFONT)fnt,0);
				SendMessage(chat_edit,WM_SETFONT,(WPARAM)(HFONT)fnt,0);
				SetCharFormat(chat_view,"Verdana", RGB(255,0,0), true, 250);
				Concat(chat_view," Echo room started.");
			}
			break;
		case WM_COMMAND:
			{
				switch(HIWORD(wParam)) 
				{
				case EN_CHANGE:
					switch(LOWORD(wParam)) 
					{
					case 2:
						{
							LRESULT len = SendMessage(chat_edit,WM_GETTEXTLENGTH,0,0);

							char *buffer = new char [ len + 1 ];
							SendMessage(chat_edit,WM_GETTEXT,len,(LPARAM)(LPCSTR)buffer);
							if(buffer[strlen(buffer)-1] == 13 ) {
								buffer[strlen(buffer)-1] = 0;
								SendMessage(chat_edit,WM_SETTEXT,1,(LPARAM)(LPCSTR)"");
								static char send_buffer[256];
								if(strlen(buffer) > 200)
									buffer[200] = '\0';
								sprintf(send_buffer,"**&&^^++--057%s: %s", screen_name, buffer);
								if(lenspace(buffer) != 0) {
									int rt_val = send(the_socket.s, send_buffer, sizeof(send_buffer), 0);
									if(rt_val < 0)
										ShowWindow(chat_win,SW_HIDE);
								}

							}
							delete [] buffer;
						}
						break;
					}
				}
			}
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

LRESULT CALLBACK FServProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	static HWND tip;
	static int recv_mode = -1;
	static int rt_val = 0;
	static std::string file_name = "";
	static unsigned long total_bytes = 0;
	static double prog = 0;
	static unsigned long bytes_read = 0, len = 0;
	static HWND hwnd_prog = 0;

	switch(msg) {
		case WM_CLOSE:
			if(MessageBox(hwnd,"Are you sure you wish to Exit?", "Quit?", MB_YESNO | MB_ICONQUESTION) == IDYES)
				return DefWindowProc(hwnd,msg,wParam,lParam);
			break;
		case WM_DESTROY:

			OnDisconnect();
			DestroyMenu(hMenu);
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			{
				hMenu = GetMenu(hwnd);
				if(!(hlist = CreateWindowEx(WS_EX_STATICEDGE,"ListBox", "", WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_NOTIFY, 10,10,250,250,hwnd,(HMENU)1,GetModuleHandle(0),0)))
					throw Error("Error couldnt create listbox");	

				if(!(hlog = CreateWindowEx(WS_EX_STATICEDGE,"Edit", "", WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | ES_READONLY, 10,280,615,125,hwnd,0,GetModuleHandle(0),0)))
					throw Error("Error couldnt create Logging Window");

				if(!(hsn_list = CreateWindowEx(WS_EX_STATICEDGE,"ListBox","",LBS_SORT | WS_CHILD | WS_VISIBLE | LBS_STANDARD | LBS_NOTIFY, 280, 175, 640-280-20, 100, hwnd,(HMENU)4,GetModuleHandle(0),0)))
					throw Error("Couldnt create sn listbox!");


				SendMessage(hlog,WM_SETFONT,(WPARAM)(HFONT)fnt,0);
				SendMessage(hlist,WM_SETFONT,(WPARAM)(HFONT)fnt,0);
				SendMessage(hsn_list,WM_SETFONT,(WPARAM)(HFONT)fnt,0);

				tip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,hwnd, NULL, GetModuleHandle(0), NULL);
				TOOLINFO toolz;
				unsigned int id = 0;
				toolz.cbSize = sizeof(TOOLINFO);
				toolz.uFlags = TTF_SUBCLASS;
				toolz.hwnd = hlist;
				toolz.hinst = GetModuleHandle(0);
				toolz.uId = id;
				toolz.lpszText = "Double click to download a file!";
				GetClientRect(hlist,&toolz.rect);
				SendMessage(tip,TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO) &toolz);
				toolz.hwnd = hlog;
				toolz.uId = ++id;
				toolz.lpszText = "Program Log Window";
				GetClientRect(hlog,&toolz.rect);
				SendMessage(tip,TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO) &toolz);
				toolz.hwnd = hsn_list;
				toolz.uId = ++id;
				toolz.lpszText = "Currently Connected Users List!";
				GetClientRect(hsn_list,&toolz.rect);
				SendMessage(tip,TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO) &toolz);
				EnableWindow(hlist,FALSE);
				EnableWindow(hsn_list,FALSE);
				Log("Successfully Initalized Window.\r\n->Waiting for Winsock Initalization...");
				if(InitWinsock())
					Log("Winsock Successfully initalized.");

				RECT rcClient;
				SetTimer(hwnd,1,1,0);
				InitCommonControls(); 
				GetClientRect(hwnd, &rcClient); 
				int cyVScroll = int(GetSystemMetrics(SM_CYVSCROLL));
				if(!(hwnd_prog = CreateWindowEx(0, PROGRESS_CLASS,(LPSTR) NULL, WS_CHILD | WS_VISIBLE,rcClient.left, rcClient.bottom-cyVScroll, rcClient.right, cyVScroll,hwnd, (HMENU) 0, GetModuleHandle(0), NULL)))
					throw Error("Error Creating Progress Bar!");

			}
			break;
		case WM_TIMER:
			{
				RECT rc = { 270,10, 270+320,10+135 };
				InvalidateRect(hwnd,&rc,FALSE);
			}
			break;
		case WM_COMMAND:
			{
				switch(wParam) 
				{
				case ID_Menu:
					SendMessage(hwnd,WM_CLOSE,0,0);
					break;
				case ID_HELP_ABOUT:
					{
						SendMessage(about,WM_SETTEXT,255,(LPARAM)(LPCSTR)"About IP2IP FServ - by Jared Bruni");

						ShowWindow(about,SW_SHOW);
						UpdateWindow(about);

						if(browser_started == false) {
							browser.startBrowser();
							browser_started = true;
							Log("Browser started...");
						}

						browser.ViewSite(L"http://www.lostsidedead.com/ip2ip_fserv/");

					}
					break;
				case ID_FILE_CONNECTTOREMOTEIP:
					ShowWindow(hcon,SW_SHOW);
					UpdateWindow(hcon);
					break;
				case ID_FILE_DISCONNECT:
					{
						OnDisconnect();
					}
					break;
				case ID_OPTIONS_ENABLECHAT: 
					{
						chat_enabled = !chat_enabled;
						CheckMenuItem(hMenu,ID_OPTIONS_ENABLECHAT, chat_enabled == true ? MF_CHECKED : MF_UNCHECKED);
						if(chat_enabled == true) {
							if(the_socket.s != 0)
								ShowWindow(chat_win,SW_SHOW);
						}
					}
					break;
				case ID_OPTIONS_SHOWWELCOMEWINDOW:
					{
						wel_enabled = !wel_enabled;
						CheckMenuItem(hMenu,ID_OPTIONS_SHOWWELCOMEWINDOW, wel_enabled == true ? MF_CHECKED : MF_UNCHECKED);

					}
					break;
				}

				switch(HIWORD(wParam)) 
				{
				case LBN_DBLCLK:
					switch(LOWORD(wParam))
					{
					case 1:
						{
							LRESULT pos = SendMessage(hlist,LB_GETCURSEL,0,0);
							char dir_in[MAX_PATH];
							SendMessage(hlist,LB_GETTEXT,pos,(LPARAM)(LPCSTR)dir_in);
							std::string file_dir = dir_in;
							if(file_dir.find("[") != -1) {
								std::string dirz = file_dir.substr(file_dir.find("[")+1, file_dir.rfind("]")-1);
								recv_mode = -1;
								char sdata[256];
								memset(sdata,0,sizeof(sdata));
								sprintf(sdata,"cd %s", dirz.c_str());
								rt_val = send(the_socket.s, sdata, sizeof(sdata), 0);
								memset(sdata,0,sizeof(sdata));
								sprintf(sdata,"ls");
								rt_val = send(the_socket.s, sdata, sizeof(sdata), 0);
							}
							else if(file_dir.find("..") != -1) {
								recv_mode = -1;
								char sdata[256];
								memset(sdata,0,sizeof(sdata));
								sprintf(sdata,"cd ..");
								rt_val = send(the_socket.s, sdata, sizeof(sdata), 0);
								memset(sdata,0,sizeof(sdata));
								sprintf(sdata,"ls");
								rt_val = send(the_socket.s, sdata, sizeof(sdata), 0);
							}
							else {
								char GetFileNamez[255];
								if(savefile(GetFileNamez,dir_in)) {
									file_name = GetFileNamez;
									recv_mode = -1;
									char sdata[256];
									memset(sdata,0,sizeof(sdata));
									sprintf(sdata,"get %s", dir_in);
									rt_val = send(the_socket.s, sdata, sizeof(sdata), 0);
								}
							}
						}
						break;
					}
					break;
				}
			}
			break;
		case ON_SOCKET:
			{
				static char data[256];
				memset(data,0,sizeof(data));
				static std::string dir_buffer = "";
				static int frt_val = 0;

				switch (WSAGETSELECTEVENT(lParam)) 
				{
				case FD_READ: 
					{
						ShowWindow(hcon,SW_HIDE);
						memset(data,0,sizeof(data));
						do {
							rt_val = recv(the_socket.s, data, sizeof(data), 0);
						} while(rt_val == 0);

						frt_val = rt_val;
						if(strstr(data,"**&&^^++--057")) {
							std::string chat_get = data;
							chat_get = chat_get.substr(chat_get.find("**&&^^++--057")+13, chat_get.length());
							std::string sn, msg;
							msg = chat_get.substr(chat_get.find(": ")+1, chat_get.length());
							sn = chat_get.substr(0,chat_get.find(":"));
							if(sn == "MasterHost")
							AddRmvSnFromList(sn, msg);
							if(sn == screen_name)
								SetCharFormat(chat_view,"FixedSys", RGB(255,0,0), true, 200);
							else if(sn == "MasterHost") {
								SetCharFormat(chat_view,"FixedSys", RGB(150,150,150), true, 200);
								// master host echoed
							}
							else {
								SetCharFormat(chat_view,"Arial", RGB(0,0,255), true, 200);
							}
							ConcatWOLB(chat_view,sn.c_str());
							SetCharFormat(chat_view,"FixedSys", RGB(0,255,0), true, 200);
							ConcatWOLB(chat_view,":");
							SetCharFormat(chat_view,"Verdana", RGB(0,0,0), false, 200);
							Concat(chat_view,msg.c_str());
							return 0;
						}
						else if(strstr(data,"&&**")) { // list current users
							std::string leftOf = data;
							leftOf = leftOf.substr(leftOf.find("&&**")+strlen("&&**"), leftOf.length());
							std::vector<std::string> v;
							token::tokenize<std::string>(leftOf, "\n", v);
							for(unsigned int p = 0; p < v.size(); p++)
								AddRmvSnFromList(std::string("MasterHost"),std::string(" ") + v[p] + std::string(" has entered"));


							return 0;
						}
						std::string buf_cmd = data;
						switch(recv_mode) 
						{
						case -1:
							{			
								if(strstr(data,"password:")) {
									Log("Sending password info...");
									memset(data, 0, sizeof(data));
									SendMessage(hpw,WM_GETTEXT,255,(LPARAM)(LPCSTR)data);
									rt_val = send(the_socket.s,data, sizeof(data), 0);
									recv_mode = 0;
									break;
								}
								else if(strstr(data,"@")) {
									if(file) {
										file->close();
										delete file;
										file = 0;
									}
									Log("File %s successfully transfered!.", file_name.c_str());
									SendMessage(hwnd_prog, PBM_SETPOS, (WPARAM) 0, 0); 
									EnableWindow(hlist,TRUE);
									transfering = false;

								}
								else if(strstr(data,"#")) {
									std::string s = data;
									std::string cur_dir = s.substr(s.find("#")+1,s.length());
									Log("CD Directory to %s", cur_dir.c_str());
									recv_mode = -1;
								}
								else if(strstr(data,"<")) {
									std::string fname, ts;
									bytes_read = 0;
									fname = buf_cmd.substr(0, buf_cmd.find("<"));
									ts = buf_cmd.substr(buf_cmd.find("<")+1, buf_cmd.length());
									total_bytes = atol(ts.c_str());
									Log("Creating file %s of size %d", fname.c_str(), total_bytes);
									file = new std::fstream;
									file->open(file_name.c_str(), std::ios::out | std::ios::binary );
									recv_mode = 2;
									SendMessage(hwnd_prog, PBM_SETRANGE, 0,MAKELPARAM(0, (total_bytes / 256))); 
									SendMessage(hwnd_prog, PBM_SETSTEP, (WPARAM) 1, 0); 
									EnableWindow(hlist,FALSE);
								}
								else if(strstr(data,":")) {
									std::string rightof;
									rightof = buf_cmd.substr(buf_cmd.rfind(":")+1, buf_cmd.length());
									len = atoi(rightof.c_str()),bytes_read = 0;
									Log("Listing Directory of Length of %d", len);
									dir_buffer = "";
									recv_mode = 1;
									bytes_read = 0;
									break;
								}

								else if(strstr(data,"{")) {
									Log(data);
								}
							}
							break;
						case 0:
							if(strstr(data,"{ Error Screen Name")) {
								MessageBox(hwnd,"Error Screen Name already in use on server", "Error", MB_ICONERROR);
								closesocket(the_socket.s);
								ShowWindow(chat_win,SW_HIDE);
								SendMessage(hlist,LB_RESETCONTENT,0,0);
								SetTitle(" IP2IP FServ - Disconnected.");

								return 0;
							}
							if(MessageBox(hwnd,data,"Do you accept the agreement?", MB_YESNO | MB_ICONQUESTION) == IDYES) {
								Log("Accepted Agreement Listing Directory.");
								memset(data, 0, sizeof(data));
								sprintf(data,"ls");
								rt_val = send(the_socket.s, data, sizeof(data), 0);
								recv_mode = -1;
								break;
							}

							closesocket(the_socket.s);
							Log("Agreement not accepted closing connection..");
							break;
						case 1:
							bytes_read += frt_val;
							dir_buffer += data;
							if(bytes_read >= len)
							{
								// Proccess Directory Info
								ProcDir(dir_buffer);
							}
							recv_mode = -1;

							break;
						case 2:
							{
								transfering = true;
								// write data to file
								bytes_read += frt_val;
								if(bytes_read >= total_bytes-1 )
								{
									file->write((char*)data, frt_val);
									recv_mode = -1;
								}
								else {
									file->write((char*)data,frt_val);
									SendMessage(hwnd_prog, PBM_STEPIT, 0, 0); 
								}
							}
							break;
						}
					}
					break;
				case FD_CONNECT:
					EnableMenuItem(hMenu,ID_OPTIONS_ENABLECHAT, MF_DISABLED);
					if(chat_enabled == true)
						sprintf(data,"ip2ip:%s", screen_name);
					else 
						sprintf(data,"ip2ip");
					rt_val = send(the_socket.s, data, sizeof(data), 0);
					if(rt_val < 0) {
						Log("Error couldnt connect Error Number %d", WSAGetLastError());
						EnableWindow(hb,TRUE);
						SendMessage(hcon,WM_SETTEXT,255,(LPARAM)(LPCSTR)"Connection Couldnt be Established");
						break;
					}

					SendMessage(hsn,WM_GETTEXT,13,(LPARAM)(LPCSTR)screen_name);
					Log("Succesfully Connected Sending Handshake");
					if(chat_enabled == true)
						ShowWindow(chat_win,SW_SHOW);

					if(wel_enabled == true)
					{
						SendMessage(about,WM_SETTEXT,255,(LPARAM)(LPCSTR)"Welcome to IP2IP FServ!!!");
						ShowWindow(about,SW_SHOW);
						if(browser_started == false) 
						{
							browser.startBrowser();
							browser_started = true;
						}
						browser.ViewSite(L"http://www.lostsidedead.com/ip2ip_fserv/welcome.php");
						SetFocus(about);
					}

					SetCharFormat(chat_view,"FixedSys", RGB(0,0,255), false, 200);
					Concat(chat_view," Echoing as %s", screen_name);

					SetTitle("IP2IP FServ GUI - Connected.");
					EnableWindow(hsn_list,TRUE);
					if(recv_mode != 2)
						recv_mode = -1;
					else
						Log("Already reciving a file cannot connect!");

					break;
				case FD_CLOSE:
					OnDisconnect();
					break;
				}

			}
			break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC dc = BeginPaint(hwnd,&ps);
				HBITMAP tbmp = CreateCompatibleBitmap(dc,320,135);
				HDC cdc = CreateCompatibleDC(dc);
				SelectObject(cdc,tbmp);
				RECT rc = { 0,0, 320,250 };
				FillRect(cdc,&rc,hbr);
				SetBkMode(cdc,TRANSPARENT);
				SetTextColor(cdc,RGB(255,0,0));
				static char str[256];
				memset(str,0,sizeof(str));
				if(total_bytes != 0 && transfering == true) {
					double percentage = 0.0f;
					if(bytes_read != 0 && total_bytes != 0)
						percentage = (double(bytes_read)/double(total_bytes))*100;
					if(percentage > 100)
						percentage = 100;

					sprintf(str,"Bytes Completed: %d/%d (%d%%)",bytes_read,total_bytes, int(percentage));
					TextOut(cdc, 10,110, str, int(strlen(str)));
				}
				HDC ccdc = CreateCompatibleDC(dc);
				SelectObject(ccdc,the_bitmap);
				StretchBlt(cdc,0,0,320,108,ccdc,0,0,340,100,SRCCOPY);
				BitBlt(dc,270,0,320,125,cdc,0,0,SRCCOPY);
				EndPaint(hwnd,&ps);
				DeleteObject(tbmp);
				DeleteDC(cdc);
				DeleteDC(ccdc);
			}
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

LRESULT CALLBACK AboutProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	switch(msg) {
		case WM_CLOSE:
			ShowWindow(hwnd,SW_HIDE);
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

LRESULT CALLBACK ConnectProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	static HWND hip,tip, hport;
	switch(msg) {
		case WM_CLOSE:
			SendMessage(hsn, WM_GETTEXT, 12, (LPARAM)(LPCSTR)screen_name);
			ShowWindow(hwnd,SW_HIDE);
			break;
		case WM_CREATE:
			{
				if(! (hip = CreateWindowEx(WS_EX_STATICEDGE,WC_IPADDRESS,"192.168.1.101",WS_CHILD | WS_VISIBLE, 10,10,180,25,hwnd,(HMENU)1,GetModuleHandle(0),0)))
					throw Error("Couldnt create editbox for connect window");

				if(! (hb = CreateWindowEx(WS_EX_STATICEDGE,"Button","Connect!", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 255,10,80,25,hwnd,(HMENU)3,GetModuleHandle(0),0)))
					throw Error("Couldnt create pushbutton for connection window!.");

				if(! (hport = CreateWindowEx(WS_EX_STATICEDGE,"Edit","1024", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 195,10,50,25,hwnd,0,GetModuleHandle(0),0)))
					throw Error("Couldnt create Port Edit Box!");

				if(! (hpw = CreateWindowEx(WS_EX_STATICEDGE,"Edit","lol", WS_CHILD | WS_VISIBLE | ES_PASSWORD, 10,45,100,20,hwnd,0,GetModuleHandle(0),0)))
					throw Error("Couldnt create password editbox!");

				if(! (hsn = CreateWindowEx(WS_EX_STATICEDGE,"Edit",screen_name,WS_CHILD | WS_VISIBLE , 130,45, 100, 20,hwnd,0,GetModuleHandle(0),0)))
					throw Error("Couldnt create screen name box!");

				SendMessage(hb,WM_SETFONT,(WPARAM)(HFONT)fnt,0);
				SendMessage(hip,WM_SETFONT,(WPARAM)(HFONT)fnt,0);
				SendMessage(hport,WM_SETFONT,(WPARAM)(HFONT)fnt,0);
				SendMessage(hpw,WM_SETFONT,(WPARAM)(HFONT)fnt,0);
				SendMessage(hsn,WM_SETFONT,(WPARAM)(HFONT)fnt,0);
				if(!(tip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP,CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, CW_USEDEFAULT,hwnd, NULL, GetModuleHandle(0), NULL)))
					throw Error("Couldnt create tooltip!");

				TOOLINFO toolz;
				unsigned int id = 0;
				toolz.cbSize = sizeof(TOOLINFO);
				toolz.uFlags = TTF_SUBCLASS;
				toolz.hwnd = hip;
				toolz.hinst = GetModuleHandle(0);
				toolz.uId = id;
				toolz.lpszText = "Enter IP Address here.";
				GetClientRect(hip,&toolz.rect);
				SendMessage(tip,TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO) &toolz);
				++id;
				toolz.hwnd = hpw;
				GetClientRect(hpw,&toolz.rect);
				toolz.lpszText = "Enter FServ Password here.";
				SendMessage(tip,TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO) &toolz);
			}
			break;
		case WM_COMMAND:
			{
				switch(HIWORD(wParam)) 
				{
				case BN_CLICKED:
					switch(LOWORD(wParam)) 
					{
					case 3:
						char data[256];
						SendMessage(hip,WM_GETTEXT,255,(LPARAM)(LPCSTR)data);
						// first check if its a valid ip address
						unsigned long addy = inet_addr(data);
						if(addy == INADDR_NONE || strlen(data) == 0) {
							MessageBox(hwnd,"Error Invalid IP Address Try Agian", "Invalid IP", MB_OK | MB_ICONERROR);
							SendMessage(hip,WM_SETTEXT,255,(LPARAM)(LPCSTR)"");
							break;
						}

						std::string ip_addy = data;

						SendMessage(hport,WM_GETTEXT,10,(LPARAM)(LPCSTR)data);
						int port_num = atoi(data);
						if(port_num == 0) {
							MessageBox(hwnd,"Error invalid port number try agian", "Invalid Port",MB_OK | MB_ICONERROR);
							SendMessage(hport,WM_SETTEXT,1,(LPARAM)(LPCSTR)"");
							break;
						}
						SendMessage(hsn,WM_GETTEXT,13,(LPARAM)(LPCSTR)screen_name);
						if(strlen(screen_name) == 0) {
							MessageBox(hwnd,"Error invalid screen name!", "Invalid Screen Name", MB_OK  | MB_ICONERROR);
							break;
						}
						for(unsigned int i = 0; i < strlen(screen_name); i++)
							if(!isalpha(screen_name[i]) && !isdigit(screen_name[i])) {
								MessageBox(hwnd,"Error screen name contains invalid characters!", "error" , MB_ICONERROR | MB_OK);
								return 0;
							}

							if(strstr(screen_name,"MasterHost")) {
								MessageBox(hwnd,"Your not the MasterHost durr try lowercasing it!.", "Error Invalid Screen Name", MB_OK | MB_ICONERROR);
								return 0;
							}
							SendMessage(hcon,WM_SETTEXT,255,(LPARAM)(LPCSTR)"Connecting...");
							EnableWindow(hb,FALSE);
							StartConnect(ip_addy,port_num);
							SendMessage(chat_win,WM_SETTEXT,255,(LPARAM)(LPCSTR)std::string(std::string("Echo Room on ") + ip_addy).c_str());

							break;
					}
					break;
				}
			}
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}


HMODULE the_lib = 0;

int Init() {
	LoadSettings();
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
	iccx.dwICC=ICC_INTERNET_CLASSES;
	InitCommonControlsEx(&iccx);

	the_lib = LoadLibrary("RichEd32.Dll");


	if(!(fnt = CreateFont(17,0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,VARIABLE_PITCH,"Verdana")))
		throw Error("Couldnt Create Font!.");

	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) hbr;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = LoadIcon(GetModuleHandle(0),MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = 0;
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = (WNDPROC) FServProc;
	wc.lpszClassName = "ip2ip";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClassEx(&wc))
		throw Error("Class (ip2ip) successfully Registered!");

	wc.lpszClassName = "ip2ip_about";
	wc.lpszMenuName = 0;
	wc.lpfnWndProc = (WNDPROC) AboutProc;

	if(!RegisterClassEx(&wc))
		throw Error("Class (ip2ip_about) Was not successfully Registered!");

	wc.lpszClassName = "ip2ip_connect";
	wc.lpfnWndProc = (WNDPROC) ConnectProc;

	if(!RegisterClassEx(&wc))
		throw Error("Class (ip2ip_connect) Was not successfully Registered!");

	wc.lpszClassName = "ip2ip_chat";
	wc.lpfnWndProc = (WNDPROC) ChatProc;

	if(!RegisterClassEx(&wc))
		throw Error("Class (ip2ip_chat) was not successfully registered!");

	if(!(hwnd = CreateWindowEx(0,"ip2ip","IP2IP - FServ GUI Client", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,CW_USEDEFAULT,640,480,0,0,GetModuleHandle(0),0)))
		throw Error("Window was not successfully Created!");

	if(!(about = CreateWindowEx(0,"ip2ip_about", "About IP2IP - FServ GUI", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,0,0,640,480,0,0,GetModuleHandle(0),0)))
		throw Error("About window was not successfully created!");

	if(!(hcon = CreateWindowEx(0,"ip2ip_connect", "Connect To IP", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,CW_USEDEFAULT,350,115,0,0,GetModuleHandle(0),0)))
		throw Error("About window was not successfully created!");

	if(!(chat_win = CreateWindowEx(0,"ip2ip_chat", "Echo Room", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,CW_USEDEFAULT,640,480,0,0,GetModuleHandle(0),0)))
		throw Error("Chat Window was not successfully created!");


	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	return 1;
}

void Cleanup() {
	if (iBrowser)
		iBrowser->Release();	
	if (mpWebObject)
	{
		mpWebObject->Close(OLECLOSE_NOSAVE); 
		mpWebObject->Release();
	}
	OleUninitialize();
	DeleteObject(fnt);
	DeleteObject(hbr);
	DeleteObject(the_bitmap);
	WSACleanup();
	FreeLibrary(the_lib);
	SaveSettings();
}

int Loop() {
	MSG msg;
	while(GetMessage(&msg,0,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Cleanup();
	return int(msg.wParam);
}

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR lpszLine, int iCmdShow) {

	OleInitialize(0);

	try {
		if(Init())
			return Loop();
	}
	catch ( Error &err ) {
		MessageBox(0,err.toString(),"Error", MB_OK | MB_ICONERROR);
	}
	Cleanup();
	return 0;
}

void StartConnect(std::string ip, int port) {
	memset(the_socket.ip_addy, 0, sizeof(the_socket.ip_addy));
	sprintf(the_socket.ip_addy,"%s", ip.c_str());
	the_socket.port = port;
	struct sockaddr_in addy;
	if(!mxConnect(&the_socket,addy)) {
		Log("A Error has occoured during connection proccess!");
	}
}

void ProcDir(std::string &dir) {
	std::vector<std::string> tok_vec;
	token::tokenize<std::string>(dir,"\n",tok_vec);
	SendMessage(hlist,LB_RESETCONTENT,0,0);
	EnableWindow(hlist,TRUE);
	EnableWindow(hsn_list,TRUE);
	SendMessage(hlist,LB_ADDSTRING,255,(LPARAM)(LPCSTR)"..");
	for(unsigned int i = 0; i < tok_vec.size(); i++) 
		SendMessage(hlist,LB_ADDSTRING,tok_vec[i].length(), (LPARAM)(LPCSTR)tok_vec[i].c_str());
}

void SaveSettings() {
	std::fstream info;
	info.open("ip2ip_client.conf", std::ios::out);
	info << screen_name << "\n";
	info.close();
}

void LoadSettings() {

	std::fstream info;
	std::string sn;
	info.open("ip2ip_client.conf", std::ios::in);
	if(info.is_open()) {
		std::getline(info, sn);
		memset(screen_name, 0, sizeof(screen_name));
		if(sn.length() != 0)
			strncpy(screen_name, sn.c_str(), sn.length());
		else
			strcpy(screen_name,"Anonymous");
	}
	else {
		strcpy(screen_name,"Anonymous");
	}
	info.close();
}
