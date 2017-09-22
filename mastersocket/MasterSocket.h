// mastersocket 1.0
// written by jared bruni
// www.lostsidedead.com

#include <windows.h>
#include <winsock.h>


#define DEFAULT_PORT -1

// initilize and kill winsock
void initwinsock();
void killwinsock();

// structure to automaticly initlize and kill winsock
struct AutoWinSockHandle
{
	inline AutoWinSockHandle()
	{
		initwinsock();
	}

	inline ~AutoWinSockHandle()
	{
		killwinsock();
	}
};

static AutoWinSockHandle sock_handle; // automaticly construct, and deconstruct
// winsock with this static structure

struct MasterSocket
{
	SOCKET socketx; // the socket structure
	HWND  hwnd; // handle of the window the socket is attached to
	UINT  SOCKET_ID; // socket ID
	void CreateSocket(HWND hwndx,UINT SOCKET_IDx);// create the socket
	void Listen(UINT port);// listen on the socket
	void Connect(char* ipaddress,UINT port);// connect with the socket
	void Send(char* buff, int len); // send data with a connected socket
	int Recive(char* buff,int len);// recive data
	void Accept(); // accept a incomin socket
	const UINT GetID();// get the ID of this socket
	void Close();// close the socket
};