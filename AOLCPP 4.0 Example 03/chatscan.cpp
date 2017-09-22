// jared bruni
// www.lostsidedead.com

#include "thehead.h"


// process incoming chat messages (callback function from aolcpp4)
void chatscan(char* sn,char* msg)
{
	if(isOn())
	{


	char mysn[100];
	aol4.GetScreenName(mysn);

	if(mstrcmp(mysn,sn) == true)
	{
		return; // i dont want to record messages from myself
	}

	// they typed /afk
	if(findstr(msg,"/afk") != -1)
	{
		char rebuff[100];
		strcpy(rebuff, " - ");
		strcat(rebuff,sn);
		strcat(rebuff," , your message has been recorded");
		aol4.SendText(rebuff);
		int afk_pos;
		afk_pos = findstr(msg,"/afk") + 3;
		char themsg[200];
		rightcopy(msg,themsg,afk_pos);
		char xthemsg[200];
		strcpy(xthemsg,sn);
		strcat(xthemsg,"                                                                                                ¿");
		strcat(xthemsg,themsg);
		SendMessage(FindWindowEx(FindWindow("MasterMain",NULL),0,"ListBox",0),LB_ADDSTRING,255,(LPARAM)(LPCSTR)xthemsg);
	}

	}

}
