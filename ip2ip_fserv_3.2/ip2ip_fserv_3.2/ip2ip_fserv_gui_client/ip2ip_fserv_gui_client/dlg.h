#pragma once
#include<windows.h>
#include<commdlg.h>

bool savefile(char* cFile, const char *file_name)
{

	char szFile[MAX_PATH];
	char szTitle[MAX_PATH];

	OPENFILENAME ofn;// common dialog box structure
	sprintf(szTitle,"Save File");
	strcpy(szFile, file_name);

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetForegroundWindow();
	ofn.lpstrFile = szFile;
	ofn.hInstance = GetModuleHandle(0);
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "*.*\0*.*\0ALL\0*.*\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = szTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	if (GetSaveFileName(&ofn)==TRUE)
	{
		strcpy(cFile, ofn.lpstrFile);
		return true;
	}
	else
	{
		return false;
	}


}