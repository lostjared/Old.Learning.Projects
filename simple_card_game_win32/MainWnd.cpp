// Quick Intution Builder by Master on LSD (LmaSterD)
// Email me: Master322@aol.com
/*

  ALL Fourtnes are Based Off Input, How it was Entered, how Fast
  What kind , etc
  then special variables are based off it:

  if(ifinsane() == 2) // Sanity Level of 2 Was Determined
  {

  }

  // etc
*/


#include <windows.h>
#include <string.h>
#include <time.h>
#include <ctime>
#include "resource.h"
#include "RandNumber.h"


// GLOBAL CONSTANTS
#define LOW 0
#define MED 1
#define HIGH 2
//


// Function Prototypes

// Non-Card Functions
LRESULT APIENTRY WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY InputProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void MenuProc(WPARAM);
void LoadGraphics(HINSTANCE hInst);

// Card Functions
void ShuffleDeck();  // GAME 1 STYLE DECK
void ShuffleDeck2(); // GAME 2 STYLE DECK
void NextCard();
void SetCard(HWND,HBITMAP);
void ShowCard(int);
void FourtneResponse(char* fourtne, int CorrectGuess, int RndTime);
int eRate();
int ifinsane();
int randbytime(int);
int GetGuess(int);
int enterRate = 0;
int EnterySum[24];
int EnteryIndex = 0;
clock_t wait;
clock_t waitI[24];
int waitIndex = 0;


enum GAMETYPE { GAME1, GAME2 };
//                 0       1
GAMETYPE game;
int gplay = 0;
int Count5 = 0;
int total_t = 0;
// Global Variables

// Non Card Variables
HWND MainWindow;
HWND CardDeckStatic;
HWND CardShownStatic;
HWND InputWindow;
HWND InputStatic;

// Card Variables
int DECK[24];
int cardindex = 0;
bool gotinput = false;

// Bitmaps
HBITMAP CardBack;
HBITMAP CardBlack;
HBITMAP Card1;
HBITMAP Card2;
HBITMAP Card3;
HBITMAP Card4;
HBITMAP Card5;
HBITMAP Guess;


int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR l, int CmdShow)
{


	MSG msg;
	WNDCLASS wc;
  
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = "MasterCard";
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);
    
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "MasterInput";
    wc.lpfnWndProc = (WNDPROC) InputProc;
	
	RegisterClass(&wc);

	LoadGraphics(hInst);

	MainWindow = CreateWindow("MasterCard", "Masters Intution Builder",  WS_POPUP| WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,0,0,230,200,0,0,hInst,NULL);
    CardDeckStatic  = CreateWindow("STATIC", "", SS_BITMAP|WS_VISIBLE|WS_CHILD,20,20,0,0,MainWindow,0,hInst,0);
    CardShownStatic = CreateWindow("STATIC", "", SS_BITMAP|WS_VISIBLE|WS_CHILD,120,20,0,0,MainWindow,0,hInst,0);
    
    SendMessage(CardDeckStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)CardBack);
    SendMessage(CardShownStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)CardBlack);
	ShowWindow(CardDeckStatic,SW_SHOW);
    ShowWindow(MainWindow,SW_SHOW);
	UpdateWindow(MainWindow);

	InputWindow = CreateWindow("MasterInput", "Guess Next Card (1-5)", WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX,0,0,332,102,0,0,hInst,0);
    InputStatic  = CreateWindow("STATIC", "", SS_BITMAP|WS_VISIBLE|WS_CHILD,0,0,0,0,InputWindow,0,hInst,0);
    SetCard(InputStatic,Guess); 
	ShowWindow(InputStatic, SW_SHOW);

   SetWindowPos(MainWindow, HWND_TOPMOST, 0,0,230,200,WS_POPUP| WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX);
   SetWindowPos(InputWindow, HWND_TOPMOST,0,0,332,102,WS_POPUP | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX);
 

	game = GAME1;
 
	
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

return msg.wParam;
}

LRESULT APIENTRY WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch(msg)
	{
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    case WM_COMMAND:

		MenuProc(wParam);

		break;

	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	
	}

return 0;
}

LRESULT APIENTRY InputProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch(msg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

return 0;
}

void MenuProc(WPARAM wParam)
{

	HMENU MainMenu;
	MainMenu = GetMenu(MainWindow);
    

	switch(wParam)
	{

	case ID_FILEEXIT:

		if(MessageBox(MainWindow, "Do You Wish to Exit?", "Quit..", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{

			PostQuitMessage(0);

		}
		
		break;
    case ID_FILENEW:

		

		ShuffleDeck();

		int CorrectGuess;
		CorrectGuess = 0;

         gplay++;

		if(game == GAME1)
		{
         
			MessageBox(MainWindow, "How to Play:\nThere will be 25 cards in this deck shuffled\nYou enter the number (1-5) you think that is going to appear next\nthe cards within the deck are mixed, so this time you could have 4 5 cards, and next time 6\nUsing this method prevents card counting\nuse your intution to try and guess\nafter each card you will be prompted on your success\nand in the end you will see what percentage of cards were guessed correct\nfollow your inner mind and flex those powers\nReady Lets Start!", "Master's Intution Builder" , MB_OK | MB_ICONINFORMATION);
		
			while(cardindex <= 24)
		{

			ShowWindow(InputWindow, SW_SHOW);
			UpdateWindow(InputWindow);
			UpdateWindow(InputStatic);
			SetFocus(InputWindow);
			
			gotinput = false;
			int newKey = 0;
			
			 clock_t start = clock();

			 clock_t stop;

			
			while(gotinput == false)
			{
            	
				SetFocus(InputWindow);
                
                if(GetAsyncKeyState(49))
				{
					newKey = 0;
					gotinput = true;

				}
				if(GetAsyncKeyState(50))
				{
					newKey = 1;
					gotinput = true;

				}
				if(GetAsyncKeyState(51))
				{
					newKey = 2;
					gotinput = true;

				}
				if(GetAsyncKeyState(52))
				{
					newKey = 3;
					gotinput = true;

				}
				if(GetAsyncKeyState(53))
				{
					newKey = 4;
					Count5++; // Sanity Check
					gotinput = true;
				}
			
				// Count How Long Inbetween Each Guess For Rate

				stop = clock();
                enterRate++;
				wait = stop;
				waitI[waitIndex] = wait;
				waitIndex++;
			}
        
			EnterySum[EnteryIndex] = enterRate; 
			enterRate = 0;
			EnteryIndex++; // Count How Long Each Time Took
		



		

			int next;
			next = DECK[cardindex + 1];
            ShowWindow(InputWindow, SW_HIDE);
			NextCard();

			if(next == newKey)
			{

				MessageBox(MainWindow, "You Are Correct!","Master's Intution Builder", MB_OK | MB_ICONINFORMATION);
                CorrectGuess++;
				
			}
			else
			{

				MessageBox(MainWindow, "You are Incorrect!", "Master's Intution Builder", MB_OK | MB_ICONINFORMATION);
				
			}
         

		}

		}
        else
        {

			// Game 2

			MessageBox(MainWindow, "Welcome to Game2!\n\nThis mode is alot like the first, but the cards\n are cut into maximum amounts of each kind,\n per 25. that means, theres only 5 , 5 's and only 5 of\n the 2's. So to minimize, the amount and\n give you a easyier way to get more correct\n", "Master's Intution Builder", MB_OK | MB_ICONINFORMATION);


		}

		char GameOver[800];
		strcpy(GameOver, "Master's Intution Builder: Game Over\n\nYour Overal Score: ");
        char cbuff[10];
		itoa(CorrectGuess,cbuff,10);
		strcat(GameOver, cbuff);
		strcat(GameOver, " \\ 25\n\nYour Rank: ");
        char Rank[100];
	    
		int pGuess;
		pGuess = rand()%1;

		// Routine to Rate the Entery Length
         int erate;
		 erate = eRate();
        
		// Routine to Check Sanity (Remembering Skils)!
		int sanity; sanity = ifinsane();

		

		if((CorrectGuess > 0) && (CorrectGuess < 4))
		{
		
			if(pGuess == 1)
			{
				strcpy(Rank, "Normal Person Who Loves");
			}
			else
			{
				if(sanity == LOW)
				{

				strcpy(Rank, "Normal Person Possibly Seperated");

				}
				if(sanity == MED)
				{

					strcpy(Rank, "Normal Person, not very aware");
					
				}
				if(sanity == HIGH)
				{

					strcpy(Rank, "Your Attention is Low");
				}

			}
		}
        
		if((CorrectGuess >= 4) && (CorrectGuess < 9))
		{
            if(pGuess == 1)
			{
			strcpy(Rank,"Maybe You Dropped Acid Before, or are Lucky"); // L S D 
			}
			else
			{
				if(sanity == 0)
				{
                strcpy(Rank, "Powers are growing, but are lacked because you dont have enough faith");
				}

				if(sanity == 1)
				{

					strcpy(Rank, "Possible Mood Swings,block you");
				}
				if(sanity == 2)
				{

				strcpy(Rank, "Listen carefuly, and try to concentrate, use all your senses. watch the cards!");
				
				}
			}
		}

		
		if((CorrectGuess >= 9) && (CorrectGuess < 14))
		{

			strcpy(Rank, "Some Intutive Ability: ");
			if(sanity == 0)
			{

				strcat(Rank, "You Focus carefully, and watch close");
			}
			if(sanity == 1)
			{

				strcat(Rank, "the bottom of your mind, helps you only a little");
			}
			if(sanity == 2)
			{

				strcat(Rank, "your not doing to hot in the memory area");
			}
	
		}
		if
		((CorrectGuess >= 14) && (CorrectGuess < 19))
		{
			strcpy(Rank, "Your powers are growing");
		}

		if((CorrectGuess >= 19))
		{
         	strcpy(Rank, "You have a powerful intuitive ability");
		}
    
		strcat(GameOver, Rank);

		
		char FourtneBuff[1000];
		char Fourtne[500];

		strcpy(FourtneBuff, "\n\nFourtne Based off Your Intutive Hamrony Level:\n\n");
        if(gplay == 5)
		{
		strcpy(Fourtne, "You seem to be compulsive, and not let things go");
		}else
		{
		FourtneResponse(Fourtne,CorrectGuess, randbytime(10));
		}
		strcat(FourtneBuff,Fourtne);
        strcat(GameOver,FourtneBuff);


		// Fourtne Response, based off of Correct Number, Into Randomizer

		


        MessageBox(MainWindow, GameOver, "Master's Intution Builder", MB_OK | MB_ICONINFORMATION);

		SetCard(CardShownStatic, CardBlack);
		break;


		case ID_CARDMODE1:
		
	    CheckMenuItem(MainMenu,ID_CARDMODE2, MF_UNCHECKED);
        CheckMenuItem(MainMenu,ID_CARDMODE1, MF_CHECKED);
		game = GAME1;			
			break;
		case ID_CARDMODE2:
		
	    CheckMenuItem(MainMenu,ID_CARDMODE1, MF_UNCHECKED);
        CheckMenuItem(MainMenu,ID_CARDMODE2, MF_CHECKED);
		game = GAME2;
	        break;

    
    
    case ID_HELPABOUT:
        MessageBox(MainWindow, "Master's Intution Builder By LmaSterD\n\nUse this program, to help grasp\nallowing the super concious, to fill you with information, on whats coming next\n\nGrahpics Thanks to Micheal\n\nEmail me: Master322@aol.com", "Master's Intution Builder", MB_OK | MB_ICONINFORMATION);
		break;

    case ID_HELPTIPS:
        char duf[500];
		FourtneResponse(duf,15,randbytime(50));

		MessageBox(MainWindow, "Master's Tips on using Intution:\n\nMethod 1:\nPut yourself into a relaxed state and\nask your inner mind what is the next number?\nthis first thought that pops in your head should be your answer\n\nMethod 2:\nLet the keypresses flow, just hit the keys off the top of your head\nAllow the universal conciousness to guide you\n\nMethod 3:\nFocus on the card see a white image\nAllow yourself to see what number will come up next\nfirst picture you see, use it\n\n\nMany other Methods may be used, these are just suggestions. -Master", "Master's Intution Builder", MB_OK | MB_ICONINFORMATION);
		break;

	}

}

void LoadGraphics(HINSTANCE hInst)
{
	CardBack  = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
    CardBlack = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
    Card1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
    Card2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	Card3 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
	Card4 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
	Card5 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	Guess = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));

}



// Card Functions

void SetCard(HWND hwnd, HBITMAP hbitmap)
{
SendMessage(hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbitmap);
}


void ShuffleDeck()
{
    
	cardindex = 0;

	// Reset Card Deck
	for(int i = 0; i < 24; i++)
	{
		DECK[i] = rand()%4;

	}

}

void ShuffleDeck2()
{

	cardindex = 0;
    // Deck Count Index
	int m1 = 0;
	int m2 = 0;
	int m3 = 0;
	int m4 = 0;
    int m5 = 0;

	int deckindex = 0;

	// Randomize the Deck, but allow only 5 of Each Number 

	while(deckindex < 24)
	{

		int curRand = rand()%4;

		switch(curRand)
		{
		case 0:
	
			if(m1 < 4)
			{
				DECK[deckindex] = curRand;
				deckindex++;
				m1++;
			}

			break;
        case 1:
		
			if(m2 < 4)
			{
				DECK[deckindex] = curRand;
				deckindex++;
				m2++;
			}


			break;
		case 2:
			if(m3 < 4)
			{
				DECK[deckindex] = curRand;
				deckindex++;
				m3++;
			}

			break;
		case 3:
			if(m4 < 4)
			{
				DECK[deckindex] = curRand;
				deckindex++;
				m4++;
			}

			break;
		case 4:
			if(m5 < 4)
			{
				DECK[deckindex] = curRand;
				deckindex++;
				m5++;
			}

			break;
		}
	
	}


}


void NextCard()
{
   	cardindex++;
    int curCard;
	curCard = DECK[cardindex];
	ShowCard(curCard);

}

void ShowCard(int card)
{
	switch(card)
	{
    case 0:
	    SetCard(CardShownStatic,Card1);
		break;
	case 1:
		SetCard(CardShownStatic,Card2);
		break;
	case 2:
		SetCard(CardShownStatic,Card3);
		break;
	case 3:
		SetCard(CardShownStatic,Card4);
		break;
	case 4:
		SetCard(CardShownStatic,Card5);
		break;
	}
}


/*

  ******************** FOURTNE ANSWERS / RELATED FUNCTIONS ******************************

*/
// Card Fourtne Randomized Answers
void FourtneResponse(char* fourtne, int CorrectGuess, int RndTime)
{

	// Make New Variable From This Randomized 

	int RndFort = 0;
	RndFort = RndTime;
	int Guess = GetGuess(CorrectGuess); // Return Level of Guesses
		// Each One 3, Possible Sizes for Guess, it is Returned
    int erate = eRate();// Entery Rate of Previous Game
	int sanity = ifinsane();

	// 0 NORMAL
	// 1 INTUITIVE
	// 2 POWERFUL

	switch(RndFort)
	{

	case 0:

		switch(Guess)
		{
        case 0:
			strcpy(fourtne, "You have much variety, and come before most.");
			break;
		case 1:
	     	strcpy(fourtne, "Eternal Situations, Possibly Hold you Down");
			break;
		case 2:
	    	strcpy(fourtne, "You attract what you put out, whats returned to you is a success.");
	 		break;
	 }
	break;
	
	case 1:
	
		switch(Guess)
		{
		
			case 0:
			   strcpy(fourtne, "Lifes not sometimes how you want it to be");
				break;
			case 1:
				strcpy(fourtne, "you wonder alot about stuff, possibly in different states of mind");
                break;
			case 2:
			strcpy(fourtne, "wonderful things fill your life, your luck is amazing.");
				break;
		}
		break;
	 case 2:
	   switch(Guess)
	   {

	   case 0:
		   strcpy(fourtne, "Your patience at times, becomes low");
		   break;
	   case 1:
		   strcpy(fourtne, "trust in yourself, it is what creates you");
		   break;
	   case 2:
		   strcpy(fourtne, "movement upward has implemented great wealth in your life");
		   break;

	   }
		break;
	   case 3:
		   switch(Guess)
		   {
		   case 0:
			
			   strcpy(fourtne, "your mind sometimes, seems out of control");
			   break;
		   case 1:
			   strcpy(fourtne, "by reciving this message, you have had some luck!");
			   break;
		   case 2:
			   strcpy(fourtne, "the one mind, now flows freely within you");
			   break;
			}
		   
		   break;

		   case 4:
			   switch(Guess)
			   {
			   case 0:
				   strcpy(fourtne, "your personality, and ego are what bind you");
				   break;
			   case 1:
				   strcpy(fourtne, "the stripping of the layers of the mind, allow you to recivie this message");
				   break;
			   case 2:
				   strcpy(fourtne, "you are filled with love, you have had the luck, to be a beautiful angel of the divine mind");
				   break;
			   }
			   break;

			case 5:
			
				switch(Guess)
				{
				case 0:
				    strcpy(fourtne, "your concious, has not yet grown, you must clear yourself to reach higher");
                    break;
				case 1:
					strcpy(fourtne, "your starting to open , up to more powerful sides of life");
					break;
				case 2:
					strcpy(fourtne, "Your continued efforts, have brought you great harmony");
					break;
				}
				
				break;
				case 6:
					
					switch(Guess)
					{
					case 0:
					       
						strcpy(fourtne, "you are so perfect, you even allow yourself to believe your not, because all you are is what you think");
						break;
					case 1:
						strcpy(fourtne, "you must learn to break through, these bariers, to reach the highest levels of thought");
						break;
					case 2:
						strcpy(fourtne, "you are the master within. purify your channel to move upward");
						break;
					}
					case 7:
						switch(Guess)
						{
						case 0:
						strcpy(fourtne, "emotional upset, is exisiting within your life");
							break;
						case 1:
							strcpy(fourtne, "your mind is begining to expand. continue you in your important work!");
							break;
						case 2:
							strcpy(fourtne, "your answer, is based off your inner knowing, which guides you");
							break;
						}
						
						
						break;

						case 8:
						
						switch(Guess)
						{
						case 0:
						strcpy(fourtne, "you must remember, everything is this way becasue your made it like that");
							break;
						case 1:
							strcpy(fourtne, "allow yourself to open, to higher truths and knowing!");
							break;
						case 2:
							strcpy(fourtne, "meditation is the key, you must continue in your important work!");
							break;
						}
						
							break;

						case 9:

						switch(Guess)
						{
						case 0:
						strcpy(fourtne," you must free yourself from the burdens of negitivity");
							break;
						case 1:
							strcpy(fourtne, "your mind, now hears the sounds");
							break;
						case 2:
							strcpy(fourtne, "highly determitable responses have been issued, your level has issued you this one, be thankful and move on");
							break;
						}
						
							break;

						case 10:
						
						switch(Guess)
						{
						case 0:
						strcpy(fourtne, "emotional upset, is still exisiting within your life");
							break;
						case 1:
							strcpy(fourtne, "you are becoming one");
							break;
						case 2:
							strcpy(fourtne, "all i have to say is I am, what i believe, I am . Love ");
							break;
						}
						
							break;

	}

	
	
}
int randbytime(int size)
{

	int Rt;
 
  TMotherRandomGenerator RG;    // define random number generator

  RG.RandomInit(time(0));       // use time as random seed

  RG.SetInterval(0, size);        // set interval for integer output

  Rt = RG.iRandom();

 return Rt;
}

int GetGuess(int CorrectGuess)
{


	int GuessType = 0;

	 if((CorrectGuess > 0) && (CorrectGuess < 4))
		{
		
		GuessType = 0;
			
		}
        
		if((CorrectGuess >= 4) && (CorrectGuess < 7))
		{

		GuessType =	0;

		}
        
		
		if((CorrectGuess >= 7) && (CorrectGuess < 14))
		{

		GuessType =	1;
			
		}
		if((CorrectGuess >= 14) && (CorrectGuess < 19))
		{
			GuessType = 1;

		}

		if((CorrectGuess >= 19))
		{
         	GuessType = 2;

		}

		return GuessType;
}

int eRate()
{

	// Algorithim to Return How In Length Measurment Of How Long it Took
	// 0 Being fast
	// 1 Being Medium
	// 2 Being Slow

	// Rate Based off Full * Individual Divided into 3 Sections, BASED OFF TOTAL TIME

	int Full = 0;

	for(int i = 0; i < 24; i++)
	{

		Full = Full + EnterySum[i];
	}

    int Indiv = 0;
    int Low = 0;
	int Med = 0;
	int High = 0;

	 
	for(int l = 0; l < 24; l++)
	{

		if(EnterySum[i] > Low)
		{

			Indiv = Indiv + 1;

		}
		if(EnterySum[i] > Med)
		{

			Indiv = Indiv + 5;
		}

		if(EnterySum[i] > High)
		{

			Indiv = Indiv + 10;
		}
	}

	int Final = 0;
	Final = Full * Indiv / 2;

	// Based Return Value as 0 , 1 , 2
	int Complete = 0;

	return Complete;
}

int ifinsane()
{

	int sanity = 0;

	if(Count5 == 0)
	{
    	sanity = 0; // Remember
	}
	if(Count5 > 2)
	{
		sanity = 1; // Catch On
	}

	if(Count5 > 4)
	{
		sanity = 2; // Stupid
	}
	return sanity;
}