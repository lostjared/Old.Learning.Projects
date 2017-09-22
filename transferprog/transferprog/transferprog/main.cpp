#include<iostream>
#include<fstream>
#include<winsock2.h>
#include<cctype>
#include<stdlib.h>
#include<windows.h>


using namespace std;

SOCKET s,sock_cnt;
HANDLE thandle = 0;
DWORD thread_id = 0;

bool thread_run = false;
BOOL PASCAL Listen_Proc(VOID *ptr);
bool listening = false, sending = false,transfering = false;
bool recvd = false;
DWORD bytes_sent = 0, total_bytes = 0;
HANDLE hStdIn;
HANDLE hStdOut;
CONSOLE_SCREEN_BUFFER_INFO cb;
fstream file;

void goto_xy ( WORD x, WORD y)
{
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleScreenBufferInfo( hStdOut, &cb);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hStdOut, coord);
}

void sock_listen() {

	if(listening == true)
		return;
	    s = socket(AF_INET,SOCK_STREAM,0);
		if(s == INVALID_SOCKET)  {
			fprintf(stderr,"Invalid socket!\n");
			return;
		}
		sockaddr_in addr; 
		addr.sin_family = AF_INET;      
		addr.sin_port = htons (5001);   
		addr.sin_addr.s_addr = htonl (INADDR_ANY);  
		if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
		{ 
			fprintf(stderr,"Couldnt bind socket!\n");
			WSACleanup ();  
			return;        
		}
		if (listen(s,5)==SOCKET_ERROR)
		{
			fprintf(stderr,"Unable to Listen!.\n");
			WSACleanup ();
			return;
		}
	
    	thandle = CreateThread( NULL,0,(LPTHREAD_START_ROUTINE)Listen_Proc,0, 0, (LPDWORD)&thread_id );
		if( thandle == 0) {
           printf("Thread creation failed!.\n");
		   thread_run = false;
		}
		thread_run = true;
		listening = true;
}

void sock_stoplisten() {
	if(thandle != 0) {
		thread_run = false;
		WaitForSingleObject( thandle, 50 );
		CloseHandle(thandle);
		thandle = 0;
	}
}

void sock_connect(char *ip) {
	sockaddr_in target;

	s = socket(AF_INET,SOCK_STREAM,0);
	target.sin_family = AF_INET;          
	target.sin_port = htons (5001);  
	hostent* localHost;
	char *localIP;
	if(strlen(ip) == 0) {
	localHost = gethostbyname("");
	localIP = inet_ntoa (*(struct in_addr *)*localHost->h_addr_list);
	}
	target.sin_addr.s_addr = inet_addr(strlen(ip) == 0 ? localIP : ip);  

	if (connect(s, (SOCKADDR*)&target, sizeof(target)) == SOCKET_ERROR)
	{ 
		fprintf(stderr, "Error on connect!\n");
		WSACleanup ();
		return;
	}
	sending = true;
}
 
void procdata(char *buffer, int rt, unsigned short val, size_t tick_count) {
	if(total_bytes > bytes_sent)
	file.write((char*)buffer,rt);
}

BOOL PASCAL Listen_Proc(VOID *ptr) {

	while(listening == true) {
	    sockaddr addr;
		sock_cnt = accept (s, &addr, 0); 
		if(sock_cnt == INVALID_SOCKET) {
			continue;
		}
		else { 
			transfering = true;
			break;
		}
	}
	char file_name[MAX_PATH];

		while(total_bytes-1 > bytes_sent || total_bytes == 0) {
			static char buffer[1025]; 
			memset(buffer,0,1024);
			int rt = recv (sock_cnt, buffer, 1024,0);
			if(rt == 0)
				continue;
			if(total_bytes == 0) {
				buffer[rt] = 0;
				char *ptr = strstr(buffer,":");
				char *tptr = ptr;
				tptr++;
				total_bytes = atol(tptr);
				*ptr = 0;
				strcpy(file_name,buffer);
				CreateDirectory("recvd_files",0);
				char fname[MAX_PATH];
				sprintf(fname,"./recvd_files/%s", file_name);
				file.open(fname, ios::binary | ios::out );
				continue;
			}
			procdata(buffer,rt,0,GetTickCount());
			bytes_sent += (DWORD)rt;
			
		}
		file.close();
		return FALSE;
}

int main(int argc, char *argv[]) {


	WSADATA ws;
	int err = WSAStartup(0x0202,&ws);
	if(!err){

		char c;
		do {
		cout << "Would you like to listen or connect? (L/C): ";
		cin >> c;
		} while (toupper(c) != 'L' && toupper(c) != 'C');
		switch(toupper(c)) {
		case 'L': {
			sock_listen();
			system("CLS");
			int x_counter = 0,y_counter = 0;
			while(total_bytes == 0 || total_bytes-1 > bytes_sent) { 
				if(transfering == true) {
					goto_xy(0,0);
					cout << "Transfering File "  << bytes_sent << "/" << total_bytes  << endl;
				}
				else {
					goto_xy(0,0);
					cout << "Waiting for connection.";
				}
				if(y_counter++ > 1000)
					goto_xy(x_counter,4),
					cout << ".",
					y_counter = 0,
					x_counter++;
				if (x_counter > 5) x_counter = 0, system("CLS"); 
			}
			system("CLS");
			cout << "\nTransfer Finished " <<  total_bytes << " bytes Recv'd " << endl;
			shutdown(sock_cnt, FD_READ);
			closesocket(sock_cnt);
		}
		break;
		case 'C':
			char ip_buf[255];
			char file_name[MAX_PATH];
			printf("Enter ip address: ");
			cin >> ip_buf;
			printf("Enter file name: ");
			cin >> file_name;
			file.open(file_name,ios::binary | ios::in );
			if(file.is_open()) {
			sock_connect(ip_buf);
			char buf[1025];
			file.seekg(0,ios::end);
			int size = file.tellg();
			file.seekg(0, ios::beg);
			memset(buf, 0, sizeof(buf));
			if(size == 0) 
				file.close()
				,closesocket(s);
			else {
			sprintf(buf, "%s:%d", file_name, size);
			send(s,buf,1024,0);
			cout << "Size of file in bytes: " << size << endl;
			while(!file.eof()) {
				memset(buf,0,sizeof(buf));
				file.read((char*)buf,sizeof(char) * 1024);
				send(s,buf,1024,0);
				//cout << "Sent " << buf << "\n";
			}
			file.close();
			closesocket(s);
			}
			}
			else
				cout << "invalid file name\n";
			break;

		}
		WSACleanup();
	}
	else
		fprintf(stderr,"Error initalizing winsock library!.\n");
	
	system("PAUSE");
	return 0;
}