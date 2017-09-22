/*

  MasterPiece written utilizing MasterX SDK
  written by Jared Bruni


  www.lostsidedead.com



  Open Source, Open Mind

   "I am only as I think and believe"


*/

#include "thehead.h"


void Start::ondraw()
{
	startg.DisplayGraphic(0,0);
	drawsub();
}

// subscreen draw switch
void Start::drawsub()
{
	switch(sub_screen)
	{
	case IDS_START:
		{
			switch(cursor_pos)
			{
			case 0: {
				
				cx = 250;
				cy = 170;
				
					}
				break;
			case 1:
				{
					cx = 250;
					cy = 170+70;
				}
				break;
			case 2: { cx = 250; cy = 170+70*2; } break;
			case 3: { cx = 250; cy = 170+70*3; } break;
			}
			
			startcur.DisplayGraphic(cx,cy);
		}
		break;
	case IDS_OP:
		{
			int sx = 10, sy = 100, sw = 620, sh = 350;

			mxhwnd.paint.mxdrawrect (sx,sy,sx + sw, sy + sh,0x0,0x0);
			
			mxhwnd.text.setbkcolor(0x0);
			mxhwnd.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
			mxhwnd.text.setfont(mfonts[1]);
			mxhwnd.text.printtext( "Options [ press enter to return ]",15,105);

			mxhwnd.text.setfont(mfonts[0]);
			mxhwnd.text.settextcolor(RGB(0,0,255));
			mxhwnd.text.sprinttext( 50,200," Amount of lines until speed increase: %i", Options.linec);
 


			int cur_x = 15;
			int cur_y = 200;


			mxhwnd.text.settextcolor(RGB(255,0,0));
			mxhwnd.text.sprinttext( cur_x, cur_y,"=)>");





		}
		break;
	case IDS_CRED:
		{
			int sx = 10, sy = 100, sw = 620, sh = 350;

			mxhwnd.paint.mxdrawrect (sx,sy,sx + sw, sy + sh,0x0,0x0);

			mxhwnd.text.setbkcolor(0x0);
			mxhwnd.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
			mxhwnd.text.setfont( mfonts[1] );
			mxhwnd.text.printtext( "Credits [ press enter to return ]",15,105);
			mxg.DisplayGraphic(sx + 90-3,sy + 250);
			jaredg.DisplayGraphic(560,380);// theres me ;] girlz email me: master322@aol.com

			// dreams can become a reality
			// its simply a decesion

			credits.update();


	 
		}
		break;
	case IDS_SCORE:
		{
			int sx = 10, sy = 100, sw = 620, sh = 350;

			mxhwnd.paint.mxdrawrect (sx,sy,sx + sw, sy + sh,0x0,0x0);

			
			mxhwnd.text.setbkcolor(0x0);
			mxhwnd.text.settextcolor(RGB(rand()%255,rand()%255,rand()%255));
			mxhwnd.text.setfont(mfonts[1]);
			mxhwnd.text.printtext("High Scores [ press enter to return ]",15,105);

			mxhwnd.text.setfont(mfonts[0]);
			mxhwnd.text.settextcolor( RGB( 0,255,0 ) );
			mxhwnd.text.printtext(" Player Name", 20, 140);
			mxhwnd.text.settextcolor ( RGB( 0, 0, 255 ) );

			for(int i = 0; i <= 10; i++)
			{

			unsigned long lscore = fscores.scorez[i].score;
			char name[100];
			strcpy(name,fscores.scorez[i].user_name);
			char cscore[100];
			char crank[10];
			itoa(i,crank,10);
			ltoa(lscore,cscore,10);
			char printout[100];
			strcpy(printout,"(");
			strcat(printout,crank);
			strcat(printout,") ");
			strcat(printout,name);
			strcat(printout," - Score: ");
			strcat(printout,cscore);
			mxhwnd.text.settextcolor ( RGB( 0,0,255) );
			mxhwnd.text.printtext(printout,20,165+(i*25));


			if(im_off == false)
			{

			if(user_score > fscores.scorez[10].score)
			{
				mxhwnd.text.settextcolor(RGB(255,0,0));
				mxhwnd.text.printtext(" You have won you a spot in the hall of fame ",300,200);
				mxhwnd.text.printtext(" Enter your name...",300,230);
				char pdata[150];
				strcpy(pdata,input_data);
				if(mxhwnd.SyncChange()) { strcat(pdata,"_"); }

				mxhwnd.text.printtext(pdata,300,260);

			}
			else
			{
				mxhwnd.text.settextcolor(RGB(0,200,0));
				mxhwnd.text.printtext(" Sorry, your score has not won",300,200);
				mxhwnd.text.printtext(" you must atleast beat the person in last",300,230);
				mxhwnd.text.printtext(" please try again [press enter]",300,260);
			}
	

			}
			
			}
		

			/* ticking away, the momments that make up the dull day */


		}
		break;
	}

}

//subscreen logic switch
void Start::onlogic()
{
	switch(sub_screen)
	{
	case IDS_START:
		{
		
		}
		break;
	case IDS_OP:
		{


		}
		break;
	case IDS_CRED:
		{


		}
		break;
	case IDS_SCORE:
		{


		}
		break;
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
