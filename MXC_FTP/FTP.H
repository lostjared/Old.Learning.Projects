/*Lee Trager
This is for FTP transfer. Most funtions return a bool. If a funtion returns 0 then it didnt 
work.
link WinInet.lib*/
#include <WININet.h>

class FTP {

private:

	HINTERNET ftp;
	BOOL bResult;

public:

	//opens ftp connection.
	FTP(){
		ftp = InternetOpen("Microsoft Internet Explorer", INTERNET_OPEN_TYPE_PROXY, "ftp-gw", NULL, 0);
	}

	//closes the connection.
	~FTP(){
		InternetCloseHandle(ftp);
	}

	//open a web site. UserName and PassWord can be NULL.
	void Open(char Site[_MAX_PATH], char UserName[_MAX_PATH], char PassWord[_MAX_PATH]){
		ftp = ::InternetConnect(ftp, Site, INTERNET_INVALID_PORT_NUMBER, UserName, PassWord, INTERNET_SERVICE_FTP,  0, (DWORD)0);
	}

	//send a file.
	BOOL SendFile(char ServerFile[_MAX_PATH], char LocalFile[_MAX_PATH]){

		HANDLE search;
		WIN32_FIND_DATA a;
		search = FindFirstFile(LocalFile,&a);
		
		if(search!=INVALID_HANDLE_VALUE)
		{
			bResult = ::FtpPutFile(ftp, LocalFile, ServerFile, FTP_TRANSFER_TYPE_BINARY, 0);
			return bResult;
		}else{
			return 0;
		}
	}

	//get file off a server.
	BOOL GetFile(char ServerFile[_MAX_PATH], char LocalFile[_MAX_PATH]){
		bResult = ::FtpGetFile(ftp, ServerFile, LocalFile, FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY, 0);
		return bResult;
	}

	//create new directory
	BOOL NewDir(char DirName[_MAX_PATH]){
		bResult = FtpCreateDirectory(ftp, DirName);
		return bResult;
	}

	//delete a directory
	BOOL KillDir(char Dir[_MAX_PATH]){
		bResult = FtpRemoveDirectory(ftp, Dir);
		return bResult;
	}

	//change server directory.
	BOOL GoToDir(char Dir[_MAX_PATH]){
		bResult = FtpSetCurrentDirectory(ftp, Dir);
		return bResult;
	}

	//get current directory.
	char *CurrentDir(){
		char dir[_MAX_PATH];
		DWORD size = _MAX_PATH;
		bResult = FtpGetCurrentDirectory(ftp, dir, &size);
		if (bResult == 0){
			return 0;
		}else{
			return dir;
		}
	}

	//delete a file
	BOOL KillFile(char File[_MAX_PATH]){
		bResult = ::FtpDeleteFile(ftp, File);
		return bResult;
	}

	//rename a file.
	BOOL Rename(char File[_MAX_PATH], char Name[_MAX_PATH]){
		bResult = ::FtpRenameFile(ftp, File, Name);
		return bResult;
	}
};