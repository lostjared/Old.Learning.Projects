/*Master Console FTP by Lee Trager
to run this program put this program and
MasterX Console in the same directory then
go into MasterX Console and type 'call ftp'*/

#include "masterstream.h"
#include "FTP.h"

inline void mnu();
int CmdCompare(char *item);

enum {OPEN = 0x1, SEND = 0x2, GET = 0x3, RENAME = 0x4, KILL = 0x5, CD = 0x6, NEWDIR = 0x7, KILLDIR = 0x8, DIR = 0x9, HELP = 0x10, FLUSH = 0x11, ABOUT = 0x12, EXIT = 0x13};

int mastermain(char* argument)
{
	FTP ftp;
	bool on = true;
	char Server[_MAX_PATH];
	char Local[_MAX_PATH];
	char User[_MAX_PATH];
	char Pass[_MAX_PATH];
	char Site[_MAX_PATH];
	char ReName[_MAX_PATH];
	char cmd[10];

	console << "FTP by Lee Trager\n\n";
	mnu();

	while(on == true)
	{

		console << "Command: ";
		console >> cmd;
		console << endl;

		switch(CmdCompare(cmd))
		{

		case OPEN:
			console << "    Site: ";
			console >> Site;
			console << endl;

			console << "    UserName: ";
			console >> User;
			console << endl;

			console << "    PassWord: ";
			console >> Pass;
			console << endl;

			ftp.Open(Site, User, Pass);

			break;

		case SEND:
			console << "    Send file: ";
			console >> Local;
			console << endl;

			console << "    Save file as: ";
			console >> Server;
			console << endl;

			if(ftp.SendFile(Server, Local) == 0)
			{
				console << "Error! File was not sent!\n";
			}
			
			break;

		case GET:
			console << "    Get file: ";
			console >> Server;
			console << endl;

			console << "    Save file as: ";
			console >> Local;
			console << endl;

			if(ftp.GetFile(Server, Local) == 0)
			{
				console << "Error! File was not Received!\n";
			}

			break;

		case RENAME:
			console << "    File: ";
			console >> Server;
			console << endl;

			console << "    Rename file: ";
			console >> ReName;
			console << endl;

			if(ftp.Rename(Server, ReName) == 0)
			{
				console << "Error! File was not renamed!\n";
			}

			break;

		case KILL:
			console << "    Kill: ";
			console >> Server;
			console << endl;

			if(ftp.KillFile(Server) == 0)
			{
				console << "Error! File was not killed!\n";
			}

			break;

		case CD:
			console << "    CD: ";
			console >> Server;
			console << endl;

			if (ftp.GoToDir(Server) == 0)
			{
				console << "Error! Your in the same directory\n";
			}

			break;

		case NEWDIR:
			console << "    Name of new directory: ";
			console >> Server;
			console << endl;

			if (ftp.NewDir(Server) == 0)
			{
				console << "Error! Directory was not created!\n";
			}

			break;

		case KILLDIR:
			console << "    Kill: ";
			console >> Server;
			console << endl;

			if(ftp.KillDir(Server) == 0)
			{
				console << "Error! Directory was not deleted!\n";
			}

			break;

		case DIR:
			if(ftp.CurrentDir() == 0)
			{
				console << "Error! You are not connected to server!\n";
			}else{
				char DIRR[_MAX_PATH];
				strcpy(DIRR, ftp.CurrentDir());
				console << DIRR << endl;
			}

			break;

		case HELP:
			mnu();

			break;

		case FLUSH:
			console.clear();

			break;

		case ABOUT:
			console << "FTP by Lee Trager\nE-mail: L_Trager@hotmail.com\nAIM: Nukem996\nMSN: Nukem996@hotmail.com\n";
			console << "MasterX Console by Jared Bruni\n";
			console << "www.LostSideDead.com\n";

			break;

		case EXIT:
			on = false;
			
			break;

		default:
			console << "Invald command!\n";
			mnu();
			
			break;
		}
	}
	return (0);
}

inline void mnu()
{
	console << "        FTP Commands\n";
	console << "Open    Connect to a web site\n";
	console << "Send    Send a file to server\n";
	console << "Get     Get a file from server\n";
	console << "Rename  Rename file on server\n";
	console << "Kill    Delete file from server\n";
	console << "CD      Change Directory\n";
	console << "NewDir  Create new directory on server\n";
	console << "KillDir Delete Directory from server\n";
	console << "Dir     Current Directory\n";
	console << "Help    Display this menu\n";
	console << "Flush   Clear Screen\n";
	console << "About   About the program\n";
	console << "Exit    Exit program\n";
}

int CmdCompare(char *item)
{
	if(strcmp(item, "Open") == 0)
	{
		return OPEN;
	}

	if(strcmp(item, "open") == 0)
	{
		return OPEN;
	}

	if(strcmp(item, "Send") == 0)
	{
		return SEND;
	}

	if(strcmp(item, "send") == 0)
	{
		return SEND;
	}

	if(strcmp(item, "Get") == 0)
	{
		return GET;
	}

	if(strcmp(item, "get") == 0)
	{
		return GET;
	}

	if(strcmp(item, "Rename") == 0)
	{
		return RENAME;
	}

	if(strcmp(item, "rename") == 0)
	{
		return RENAME;
	}

	if(strcmp(item, "Kill") == 0)
	{
		return KILL;
	}

	if(strcmp(item, "kill") == 0)
	{
		return KILL;
	}

	if(strcmp(item, "CD") == 0)
	{
		return CD;
	}

	if(strcmp(item, "Cd") == 0)
	{
		return CD;
	}
	
	if(strcmp(item, "cd") == 0)
	{
		return CD;
	}

	if(strcmp(item, "NewDir") == 0)
	{
		return NEWDIR;
	}

	if(strcmp(item, "newdir") == 0)
	{
		return NEWDIR;
	}

	if(strcmp(item, "KillDir") == 0)
	{
		return KILLDIR;
	}

	if(strcmp(item, "killdir") == 0)
	{
		return KILLDIR;
	}

	if(strcmp(item, "Dir") == 0)
	{
		return DIR;
	}

	if(strcmp(item, "dir") == 0)
	{
		return DIR;
	}

	if(strcmp(item, "Help") == 0)
	{
		return HELP;
	}

	if(strcmp(item, "help") == 0)
	{
		return HELP;
	}

	if(strcmp(item, "Flush") == 0)
	{
		return FLUSH;
	}

	if(strcmp(item, "flush") == 0)
	{
		return FLUSH;
	}

	if(strcmp(item, "About") == 0)
	{
		return ABOUT;
	}

	if(strcmp(item, "about") == 0)
	{
		return ABOUT;
	}

	if(strcmp(item, "Exit") == 0)
	{
		return EXIT;
	}

	if(strcmp(item, "exit") == 0)
	{
		return EXIT;
	}

	return NULL;
}