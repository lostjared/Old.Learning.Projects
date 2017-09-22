// master console
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"


// update the console
void MasterConsole::update()
{
	drawinput();
	drawdata();
}

// keypress to console
void MasterConsole::keypress(WPARAM wParam)
{
	
	switch(wParam)
	{
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
	case VK_ESCAPE:
	case VK_SHIFT:
	case VK_CONTROL:
		return;
		break;
	case VK_RETURN:
		{
			// pass command
			printtext(input_data,RGB(0,0,200));
			consolecmd(input_data);
			input_data[0] = 0;
			input_index = 0;
			return;
		}
		break;
	case VK_BACK:
		{
			input_index--;
			if(input_index < 0) { input_index = 0; input_data[0] = 0;  return; }
			input_data[input_index] = 0;
			return;
		}
		break;
	case VK_CAPITAL:
		{
			if(icaps == true) { icaps = false; } else { icaps = true; }
		}
		break;
		
	}
	
	if(input_index < 150) 
	{
		
		input_data[input_index] = fixkeys((int)wParam,(int)icaps,false);
		input_index++;
		input_data[input_index] = 0;
		
	}
}

// draw input field
void MasterConsole::drawinput()
{
	char outstr[300];
	strcpy(outstr,"enter cmd =)> ");
	strcat(outstr,input_data);
	
	gcount++;
	
	if(gcount > 2)
	{
		
		strcat(outstr,"_");
	       gcount = 0;
	}
	
	mxhwnd.text.printtext(outstr,10,600-20); 
}

// draw data field
void MasterConsole::drawdata()
{
	int dy = 490;
	
	int pre_pos;
	pre_pos = print_pos - 6;
	if(pre_pos < 0) 
	{
		pre_pos = 0;
		
	}
	
	for(int i = 0; i < 6; i++)
	{ 
		if(dispdata[pre_pos + i].on == true)
		{
			mxhwnd.text.settextcolor(dispdata[pre_pos + i].cur_color);
			mxhwnd.text.printtext(dispdata[pre_pos + i].curline,10,dy);
		}
		dy = dy + 15;
	}
}
// print text
void MasterConsole::printtext(char* buff,COLORREF color)
{
	// clear it
	if(print_pos >= 99)
	{
		ZeroMemory(&dispdata,sizeof(dispdata));
		for(int i = 0; i <= 100; i++)
		{
			dispdata[i].setnull();
		}		
		print_pos = 0;
	}
	
	dispdata[print_pos].cur_color = color;
	strcpy(dispdata[print_pos].curline,buff);
	dispdata[print_pos].on = true;
	print_pos++;
}

// proccess a command from the console
void MasterConsole::consolecmd(char* cmd)
{
	if(strcmp(cmd,"about") == 0)
	{
		mprint("Written by Jared Bruni",RGB(200,200,200));
		mprint("www.lostsidedead.com",RGB(200,200,200));
		return;
	}

}


// important functions
// fix a key, format it correctly
char fixkeys(int key,int caps,bool cmd)
{
	
	char cur;	
	int shift;
	shift = 0;
	// shift switch
	if(GetAsyncKeyState(16))
	{
		shift = 1;
		if(caps)
		{
			cur = tolower(key);
		}
		else
		{
			cur = toupper(key);
		}
		// special shift character switch
		
		switch(cur)
		{
		case '0':
			cur = ')';
			break;
		case '1':
			cur = '!';
			break;
		case '2':
			cur = '@';
			break;
		case '3':
			cur = '#';
			break;
		case '4':
			cur = '$';
			break;
		case '5':
			cur = '%';
			break;
		case '6':
			cur = '^';
			break;
		case '7':
			cur = '&';
			break;
		case '8':
			cur = '*';
			break;
		case '9':
			cur = '(';
			break;
		}
	}
	else
	{
		
		if(caps)
		{
			cur =  toupper(key);
		}
		else
		{
			cur = tolower(key);
		}
	}
	
	// quick key to special char switch
	switch(key)
	{
	case 220:
		
		cur = '\\';
		
		break;
		
	case 191:
		if(shift)
		{
			cur = '?';
		}
		else
		{
			
			cur = '/';
		}
		
		break;
		
	case 192:
		
		cur = 'µ';
		break;
		
	case 186:
		if(shift)
		{
			cur = ':';
		}
		else
		{
			cur = ';';
		}
		break;
		
	case 219:
		
		if(shift)
		{
			if(cmd == false)
			{
				cur = '{';
			}
			else
			{
                cur = '/';
			}
		}
		else
		{
			cur = '[';
		}
		
		break;
	case 221:
		if(shift)
		{
			if(cmd == false)
			{
				cur = '}';
			}
			else
			{
                cur = '\\';
			}
		}
		else
		{
			cur = ']';
		}
		
		break;
	case 187:
		if(shift)
		{
			cur = '+';
		}
		else
		{
			cur = '=';
		}
		break;
	case 189:
		
		if(shift)
		{
			cur = '_';
		}
		else
		{
			cur = '-';
		}
		
		break;
	case 188:
		
		if(shift)
		{
			cur = '<';
		}
		else
		{
			cur = ',';
		}
		
		break;
		
	case 190:
		
		if(shift)
		{
			cur = '>';
		}
		else
		{
			cur = '.';
		}
		
		
		break;
	case 222:
		if(shift)
		{
			cur = '\"';
			break;
		}
		else
		{
			cur = '\'';
			break;
		}
		
		
		
		break;
		
		}
		
		return cur;
}

