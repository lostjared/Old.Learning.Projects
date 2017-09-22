// AOL Mail Box Fwder Object

#include "appHead.h"

// constructor
AOLFwder::AOLFwder()
{
	isend = 0;
}

// push a Item into the Que
void AOLFwder::pushList(int index)
{
	sendlist[off_index].index = index;
	off_index++;
}

// pop a item Out of the Que
int AOLFwder::popList()
{
	return pop_index;
	pop_index++;
}

// send mail
void AOLFwder::send(char* sn, char* body)
{
	// go thru each and send
	strcpy(sendsn,sn);
	strcpy(sendtag,body);
	ShowWindow(FindWindow("SendingMain",NULL),SW_SHOW);
	ShowWindow(FindWindow("MailMain",NULL),SW_HIDE);
	pop_index = 0;
	fwdx = true;
	isend = 1;

	MessageBox(0,"test",0,0);
}

void AOLFwder::on()
{
	isend = 1;
}


// stop forwarding
void AOLFwder::stop()
{
	ShowWindow(FindWindow("SendingMain",NULL),SW_HIDE);
	ShowWindow(FindWindow("MailMain",NULL),SW_SHOW);
	fwdx = false;
	clear();
	isend = 0;
}

// clear the qoe
void AOLFwder::clear()
{
	ZeroMemory(&sendlist,sizeof(sendlist));
	off_index = 0;
	pop_index = 0;
	fwdx = false;
}

void AOLFwder::update()
{
	if(fwd_send == true)
	{

	HWND snd;
	snd =FindWindow("SendingMain",NULL);
	LostString lsd;
	lsd = "lsd:";
	lsd += isend;
	SendMessage(snd,WM_SETTEXT,255,(LPARAM)(LPCSTR)lsd.getstr());

	sendthemail();
	openandfwd();

	}

}

// the proccess to actual send a email

void AOLFwder::sendmail()
{

}

// check if we should send agian, if so reset the code
void AOLFwder::checkifrepeat()
{

}

// send the mail
void AOLFwder::sendthemail()
{

}

// openandfwd
void AOLFwder::openandfwd()
{

}


