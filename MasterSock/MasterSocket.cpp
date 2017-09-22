// master socket
// written by jared bruni

#include "mastersocket.h"

// initilze windows sockets
void initwinsock()
{
	
WORD wVersionRequested;
WSADATA wsaData;
int err;

wVersionRequested = MAKEWORD( 1, 1 );

err = WSAStartup( wVersionRequested, &wsaData );
if ( err != 0 ) {
 	MessageBox(0,"Error Couldnt Init Winsock!","Aborting",MB_ICONINFORMATION);
	PostQuitMessage(0);
    return;
}


if ( LOBYTE( wsaData.wVersion ) != 1 ||
         HIBYTE( wsaData.wVersion ) != 1 ) {
    WSACleanup( );
    return;   

}
}

// killwinsock, on lcose
void killwinsock()
{
	WSACleanup();
}

// the master socket data structure
void MasterSocket::CreateSocket(HWND hwndx, UINT SOCKET_IDx)
{
	hwnd = hwndx;
	SOCKET_ID = SOCKET_IDx;
	socketx = socket(AF_INET,SOCK_STREAM,0);
	WSAAsyncSelect(socketx,hwnd,SOCKET_ID,FD_CONNECT|FD_READ|FD_CLOSE|FD_ACCEPT);
}

// begin listening
void MasterSocket::Listen(UINT port)
{
	if(port == DEFAULT_PORT) { port = 7; }
     struct sockaddr_in addy;
	// begin watching on port 7
  	addy.sin_family = AF_INET;
	addy.sin_port = htons(port);
	addy.sin_addr.s_addr = INADDR_ANY; //inet_addr("172.129.243.252");
   	bind(socketx,(struct sockaddr*)&addy,sizeof(addy));
	listen(socketx,5);
}
// connect to a remote socket
void MasterSocket::Connect(char* ipaddress,UINT port)
{
	struct sockaddr_in addy2;
	if(port == DEFAULT_PORT) { port = 7; }

	addy2.sin_family = AF_INET;
	addy2.sin_port = htons(port);
	addy2.sin_addr.s_addr = inet_addr(ipaddress);
	connect(socketx,(struct sockaddr*)&addy2,sizeof(addy2));
}
// accept a request from remote socket
void MasterSocket::Accept()
{
	struct sockaddr cli_addr;
    int clilen;
	clilen = sizeof(cli_addr);
	socketx = accept(socketx,(struct sockaddr*)&cli_addr,&clilen);
}

// send data once socket is connected
void MasterSocket::Send(char* buff, int len)
{
	send(socketx,buff,len,0);
}
// recive data from a connected socket
int MasterSocket::Recive(char* buff,int len)
{
	return recv(socketx,buff,len,0);
}
// get the ID of a given socket, for the wndproc callback
const UINT MasterSocket::GetID()
{
	return (const UINT)SOCKET_ID;
}
// close an open socket
void MasterSocket::Close()
{
	closesocket(socketx);
}