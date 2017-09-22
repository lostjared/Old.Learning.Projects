#pragma once
#define WIN32_LEAN_AND_MEAN
#include<winsock.h>
#include<windows.h>
#pragma comment(lib,"wsock32.lib")
#define ON_SOCKET WM_USER+1

WSADATA ws;
extern HWND hwnd;

inline bool InitWinsock() {
	WSAStartup(MAKEWORD(1,1),&ws);
	if(ws.wVersion != MAKEWORD(1,1)) {
		MessageBox(GetForegroundWindow(),"Error Initalizing Winsock!","Error!",MB_OK | MB_ICONERROR);
		WSACleanup();
		return false;
	}
	return true;
}


struct mxSocket {
	SOCKET s;
	unsigned int port;
	char ip_addy[256];
	struct sockaddr_in *addy;
	mxSocket() {
		s = 0;
	}
};

void mxListen(mxSocket *s, struct sockaddr_in &addr) {
	s->s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    addr.sin_family = AF_INET;
	addr.sin_port = htons(s->port);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(s->s, (struct sockaddr*)&addr, sizeof(addr));
	WSAAsyncSelect (s->s, hwnd, ON_SOCKET, (FD_READ | FD_CONNECT | FD_CLOSE | FD_ACCEPT));
	listen(s->s,1);
}

bool mxConnect(mxSocket *s, struct sockaddr_in &addr) {
	s->s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(s->port);
	addr.sin_addr.s_addr = inet_addr(s->ip_addy);
	s->addy = &addr;
	WSAAsyncSelect (s->s, hwnd, ON_SOCKET, (FD_READ | FD_CONNECT | FD_CLOSE));
	connect(s->s,(struct sockaddr*)&addr,sizeof(addr));
	return true;
}