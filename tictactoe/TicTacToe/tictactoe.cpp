#include"masterx.h"
#include"resource.h"
#include<time.h>


MasterXHWND mxhwnd;// the MasterX hwnd object
MasterGraphic Background,XGraphic,OGraphic,MasterXLogo;// the MasterGraphic objects to hold the background, x,o,masterX logo images
MasterSound Drop,GameOverSound,CatsGameSound; // the MasterSound objects
// the screens variables
enum { ID_GAME, ID_ABOUT };

// the games Board variables
enum { EMPTY, X, O };
int Board[3][3];

// the player variables
int Player = 0;
int Player1;
int Player2;
// the GameOver and Game's Winner Variables
bool GameOver;
int GameWinner = 0;



LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam); // the Windows Callback function
void RenderScreen(int Screen);// the render callback function
void Initilize();// the init function
void InitPlayers(); // the initilize players function
void ClearBoard(); // clear Board function 
void DrawGameScreen();
void DrawAboutScreen();
void DrawBoard(); // draw the Board function 
bool CheckBoard(int& Winner);// Check and see if someone has won
void NextMove(); // Moves to a different player

// the mastermain entry point
int APIENTRY MasterMain(HINSTANCE hInst,LPSTR line)
{
	mxhwnd.setfullflag(false);
	if(mxhwnd.CreateMasterX("TicTacToe",640,480,COLOR_DEFAULT,WndProc,hInst,LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)),NULL)) // the call to create MasterX to create the window, pass it the class name, window name,
		//screen width and height the color option, pass it the window callback function
		//pass it the icon
	{
		Initilize(); // call the initilization
		return (mxhwnd.InitLoop(RenderScreen));//call the init loop command passing the function pointer to the render callback function

	}
	
	return (0);
}

// the initilization function call
void Initilize()
{
	mxhwnd.LoadGraphic(&Background,"bg.bmp"); // load the background image into the MasterGraphic object
	mxhwnd.LoadGraphic(&XGraphic,"x.bmp"); // load the x image into the MasterGraphic object 
	mxhwnd.LoadGraphic(&OGraphic,"o.bmp"); // load the o image into the MasterGraphic object
	mxhwnd.LoadGraphic(&MasterXLogo,"mx.bmp"); // load the MasterX image into the MasterGraphic object
	mxhwnd.LoadSound(&Drop,"cherry1.wav");
	mxhwnd.LoadSound(&GameOverSound,"Explosion5.wav");
	mxhwnd.LoadSound(&CatsGameSound,"Hyperdrive.wav");
	ClearBoard();
	mxhwnd.SetScreen(ID_GAME);
	InitPlayers();
}

// the initilize players function
// this initlizes the players sets which player is X and which is O
// and sets the Player value to 1
void InitPlayers()
{
	srand(time(0));
	if(rand()%10 > 5)
	{
		Player1 = X;
		Player2 = O;
	}
	else
	{
		Player1 = O;
		Player2 = X;
	}

	Player = 1;
}


// clear Board function
// clears the Board sets it to empty
void ClearBoard()
{
	for(int i = 0; i < 3; i++)
	{
		for(int z = 0; z < 3; z++)
		{
			Board[i][z] = EMPTY;
		}
	}
}

// call to check and see if there is a winner
// the CheckBoard function
bool CheckBoard(int& Winner)
{

    // see if they got 3 in a row going top to bottom on the left hand side
	if(Board[0][0] == Player1 && Board[0][1] == Player1 && Board[0][2] == Player1)
	{
		Winner = 1;
		return true;
	}

	// see if they got 3 in a row going top to bottom on the left hand side
	if(Board[0][0] == Player2 && Board[0][1] == Player2 && Board[0][2] == Player2)
	{
		Winner = 2;
		return true;
	}

	//check to see if they got 3 in a row going across on the top row
	if(Board[0][0] == Player1 && Board[1][0] == Player1 && Board[2][0] == Player1)
	{
		Winner = 1;
		return true;
	}

	// check to see if they got 3 in a row going across on the top row
	if(Board[0][0] == Player2 && Board[1][0] == Player2 && Board[2][0] == Player2)
	{
		Winner = 2;
		return true;
	}


	// check to see if they got 3 in a row going bottom to top on the left hand side 
	if(Board[0][1] == Player1 && Board[1][1] == Player1 && Board[2][1] == Player1)
	{
		Winner = 1;
		return true;
	}

	// check to see if they got 3 in a row going bottom to top on the left hand side
	if(Board[0][1] == Player2 && Board[1][1] == Player2 && Board[2][1] == Player2)
	{
		Winner = 2;
		return true;
	}

	// check to see if they got 3 in a row going bottom to top on the right hand side
	if(Board[0][2] == Player1 && Board[1][2] == Player1 && Board[2][2] == Player1)
	{
		Winner = 1;
		return true;
	}

	// check to see if they got 3 in a row going bottom to top on the right hand side
	if(Board[0][2] == Player2 && Board[1][2] == Player2 && Board[2][2] == Player2)
	{
		Winner = 2;
		return true;
	}

	// check to see if they got 3 in a row going left to right across the middle
	if(Board[1][0] == Player1 && Board[1][1] == Player1 && Board[1][2] == Player1)
	{
		Winner = 1;
		return true;
	}

	// check to see if they got 3 in a row going left to right across the middle
	if(Board[1][0] == Player2 && Board[1][1] == Player2 && Board[1][2] == Player2)
	{
		Winner = 2;
		return true;
	}

	// check to see if they got 3 in a row going left to right across the top
	if(Board[0][0] == Player1 && Board[0][1] == Player1 && Board[0][2] == Player1)
	{
		Winner = 1;
		return true;
	}

	// check to see if they got 3 in a row going left to right across the top
	if(Board[0][0] == Player2 && Board[0][1] == Player2 && Board[0][2] == Player2)
	{
		Winner = 2;
		return true;
	}

	// check to see if they got 3 in a row going left to right across the bottom
	if(Board[2][0] == Player1 && Board[2][1] == Player1 && Board[2][2] == Player1)
	{
		Winner = 1;
		return true;
	}

	// check to see if they got 3 in a row going left to right across the bottom
	if(Board[2][0] == Player2 && Board[2][1] == Player2 && Board[2][2] == Player2)
	{
		Winner = 2;
		return true;
	}


	// check to see if they got 3 in a row going diagnoal 
	if(Board[0][0] == Player1 && Board[1][1] == Player1 && Board[2][2] == Player1)
	{
		Winner = 1;
		return true;
	}

	// check to see if they got 3 in a row going diagonal
	if(Board[0][0] == Player2 && Board[1][1] == Player2 && Board[2][2] == Player2)
	{
		Winner = 2;
		return true;
	}

	// check to see if they got 3 in a row going diagonal
	if(Board[0][2] == Player1 && Board[1][1] == Player1 && Board[2][0] == Player1)
	{
		Winner = 1;
		return true;
	}

	// check to see if they got 3 in a row going diagonal
	if(Board[0][2] == Player2 && Board[1][1] == Player2 && Board[2][0] == Player2)
	{
		Winner = 2;
		return true;
	}

	bool ItsEmpty = false;

	for(int i = 0; i < 3; i++)
	{
		for(int z = 0; z < 3; z++)
		{
			if(Board[i][z] == EMPTY)
			{
				ItsEmpty = true;
				break;
			}
		}
	}

	if(ItsEmpty == false)// the Board is full its a cats game
	{
		Winner = 0; // so set the winner to 0 
		return true;// and return true
	}

	return false;
}

// next move, moves to a different player
// the NextMove function
void NextMove()
{
	if(Player == 1)
	{
		Player = 2;
	}
	else
	{
		Player = 1;
	}

	Drop.Play();

	int Winner = 0;
	if(CheckBoard(Winner) == true)
	{
		GameOver = true;
		GameWinner = Winner;
		if(GameWinner == 0)
		{
		CatsGameSound.Play();
		}
		else
		{
		GameOverSound.Play();
		}
	}
}

// the window callback function 
// which we passed a pointer to on the CreateMasterX method, this callback function contains a variable called
// msg that we switch and have different case 's for different messages windows sends are program
// like the WM_DESTROY message, this is were we post the quit message to break the while loop
// that we initilized in the InitLoop method.
LRESULT APIENTRY WndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:// called when the window is destroyed
		PostQuitMessage(0);// breaks the while loop
		break;
	case WM_ACTIVATEAPP:
		__mxhwnd.active = wParam;// sets the app as active
		break;
	case WM_KEYDOWN:// is sent when a key is pressed
		{
			switch(wParam) // contains the key that was pressed
			{
			case VK_ESCAPE:// when the escape key is pressed
				{
					mxhwnd.Kill();// break the while loop
				}
				break;
			}

			switch(mxhwnd.GetScreen())
			{
			case ID_GAME:
				{
					switch(wParam)
					{
					case VK_RETURN:
						{
							mxhwnd.SetScreen(ID_ABOUT);
						}
						break;
					case VK_SPACE:
						{
							if(GameOver == true)// if the Game is Over then when they press space
							{                   // we wanna Clear the Board, Initilize the Players
								ClearBoard();   // and set GameOver to false
								InitPlayers();
								GameOver = false;
							}
						}
						break;
					}

				}
				break;
			case ID_ABOUT:
				{
					switch(wParam)
					{
					case VK_SPACE:
					case VK_RETURN:
						{
							mxhwnd.SetScreen(ID_GAME);
						}
						break;
					}
				}
				break;
			}

		}
		break;
	case WM_LBUTTONDOWN:// the WM_LBUTTONDOWN, when the left mouse button is clicked
		{
			int x = LOWORD(lParam), y = HIWORD(lParam);

			if(GameOver == false)
			{


			// a if statement to check and see if they clicked within a rectangle
			// if they did then set the Board[0][0] to the Player thats turn it is
			if(x > 50 && x < 160 && y > 130 && y < 200)
			{
				// switch of the Player thats turn it is
				switch(Player)
				{
				case 1:
					{
						if(Board[0][0] == EMPTY)
						{
						Board[0][0] = Player1; // set Board[0][0] to Player1's value
						NextMove();// do the NextMove
						}
					}
					break;
				case 2:
					{
						if(Board[0][0] == EMPTY)
						{
						Board[0][0] = Player2;// set Board[0][0] to Player2's value
						NextMove();// do the NextMove
						}
					}
					break;
				}
			}

			// a if statement to check and see if they clicked within a rectangle
			// if they did then set Board[0][1] to Player thats turn it is
			if(x > 175 && x < 440 && y > 100 && y < 200)
			{
				switch(Player)
				{
				case 1:
					{
						if(Board[0][1] == EMPTY)
						{
						Board[0][1] = Player1;// set Board[0][1] to Player1's value
						NextMove();// do the NextMove
						}
					}
					break;
				case 2:
					{
						if(Board[0][1] == EMPTY)
						{
						Board[0][1] = Player2;// set Board[0][1] to Player2's value
						NextMove();// do the NextMove
						}
					}
					break;
				}

			}


			// a if statement to see if they clicked within a specific rectangle
			// this rectangle is the upper left hand corner of the screen
			// and is were Board[0][2] is drawn 
			if(x > 460 && x < 580 && y > 100 && y < 200)
			{
				switch(Player)
				{
				case 1:
					{
						if(Board[0][2] == EMPTY)
						{
						Board[0][2] = Player1;// set Board[0][2] to Player1's value
						NextMove(); // do the NextMove
						}
					}
					break;
				case 2:
					{
						if(Board[0][2] == EMPTY)
						{
						Board[0][2] = Player2;// set Board[0][2] to Player2's value
						NextMove();// do the NextMove
						}
					}
					break;
				}
			}

			// a if statement to see if they clicked within a rectangle
			// its checking to see if they clicked in the the right middle 
			if(x > 50 && x < 160 && y > 215 && y < 335)
			{
				switch(Player)
				{
				case 1:
					{
						if(Board[1][0] == EMPTY)
						{
						Board[1][0] = Player1;// set Board[1][0] to Player1's value
						NextMove();// do the NextMove
						}
					}
					break;
				case 2:
					{
						if(Board[1][0] == EMPTY)
						{
						Board[1][0] = Player2;// set Board[1][0] to Player2's value
						NextMove();// do the NextMove
						}
					}
					break;
				}

			}

			// a if statement to see if they clicked within a rectangle
			// the rectangle is the center of the screen the center sqaure
			if(x > 175 && x < 445 && y > 220 && y < 335)
			{
				switch(Player)
				{
				case 1:
					{
						if(Board[1][1] == EMPTY)
						{
						Board[1][1] = Player1;// set Board[1][1] to Player1's value
						NextMove();// do the NextMove
						}
					}
					break;
				case 2:
					{
						if(Board[1][1] == EMPTY)
						{
						Board[1][1] = Player2;// set Board[1][1] to Player2's value
						NextMove();// do the NextMove
						}
					}
					break;
				}

			}

			// a if statement to see if they clicked within a rectangle
			// the rectangle is near the middle right of the screen
			if(x > 450 && x < 585 && y > 220 && y < 335)
			{
				switch(Player)
				{
				case 1:
					{
						if(Board[1][2] == EMPTY)
						{
						Board[1][2] = Player1;// set Board[1][2] to Player1's value
						NextMove();// do the NextMove
						}
					}
					break;
				case 2:
					{
						if(Board[1][2] == EMPTY)
						{
						Board[1][2] = Player2;// set Board[1][2] to Player2's value
						NextMove();// do the NextMove
						}
					}
					break;
				}


			}

			// a if statment to see if they clicked within a rectangle
			// the rectangle is near the lower left hand corner of the screen
			if(x > 50 && x < 160 && y > 350 && y < 445)
			{
				switch(Player)
				{
				case 1:
					{
						if(Board[2][0] == EMPTY)
						{
						Board[2][0] = Player1;// set Board[2][0] to Player1's value
						NextMove();// do the NextMove
						}
					}
					break;
				case 2:
					{
						if(Board[2][0] == EMPTY)
						{
						Board[2][0] = Player2;// set Board[2][0] to Player2's value
						NextMove();// do the NextMove
						}
					}
					break;
				}

			}

			// a if statement to see if they clicked within a rectangle
			// the rectangle is near the bottom middle of the screen
			if(x > 175 && x < 445 && y > 350 && y < 430)
			{
				switch(Player)
				{
				case 1:
					{
						if(Board[2][1] == EMPTY)
						{
						Board[2][1] = Player1;//set Board[2][1] to Player1's value
						NextMove();// do the NextMove
						}
					}
					break;
				case 2:
					{
						if(Board[2][1] == EMPTY)
						{
						Board[2][1] = Player2;// set Board[2][1] to Player2's value
						NextMove();// do the NextMove
						}
					}
					break;
				}

			}

			// a if statement to see if they clicked within a rectangle
			// this is to see if they clicked the square in the bottom right hand corner
			if(x > 450 && x < 585 && y > 350 && y < 445)
			{
				switch(Player)
				{
				case 1:
					{
						if(Board[2][2] == EMPTY)
						{
						Board[2][2] = Player1;// set Board[2][2] to Player1's value
						NextMove();// do the NextMove
						}
					}
					break;
				case 2:
					{
						if(Board[2][2] == EMPTY)
						{
						Board[2][2] = Player2;// set Board[2][2] to Player2's value
						NextMove();// do the NextMove
						}
					}
					break;
				}

			}

			}

		}
		break;
	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);// call the default window proccess
	}
	return (0);
}

// the render function
// is called for every frame update
// cointains a variable called screen which we have used to set multiple screens up
// we have the game screen
// and the about screen
void RenderScreen(int Screen)
{
	switch(Screen)
	{
	case ID_GAME:
		{
			DrawGameScreen(); // call to DrawGameScreen function
		}
		break;
	case ID_ABOUT:
		{
			DrawAboutScreen(); // call to DrawAboutScreen function
		}
		break;
	}

}

// draw the game screen function
void DrawGameScreen()
{
	Background.DisplayGraphic(0,0);// call to the bg object to DisplayGraphic
	DrawBoard(); // call to draw the games Board 

	mxhwnd.text.setbkcolor(RGB(0,0,0));
	mxhwnd.text.settextcolor(RGB(255,0,0));
	
	
	if(GameOver == false)
	{

	switch(Player)
	{
	case 1:
	switch(Player1)
	{
		case X:
		{
			mxhwnd.text.printtext("player 1 is X click the screen to place your move",10,10);
		}
		break;
		
		case O:
		{
			mxhwnd.text.printtext("player 1 is O click the screen to place your move",10,10);
		}
		break;
	}
	break;
	case 2:
	switch(Player2)
	{
	case O:
		{
			mxhwnd.text.printtext("player 2 is O click the screen to place your move",10,10);
		}
	break;
	case X:
		{
			mxhwnd.text.printtext("player 2 is X click the screen to place your move",10,10);
		}
	break;
	}
	}

	}
	else
	{
		switch(GameWinner)
		{
			case 0:
			{
				mxhwnd.text.printtext("game over it was a cats game press space to play a new game",10,10);
			}
			break;
		
			case 1:
			{
				mxhwnd.text.printtext("game over player 1 won press space to play a new game",10,10);
			}
			break;
			case 2:
			{
				mxhwnd.text.printtext("game over player 2 won press space to play a new game",10,10);
			}
			break;
		}

	}

	mxhwnd.text.printtext("press enter to see the about screen",450,10);

}

// draw about screen function
void DrawAboutScreen()
{	
 	MasterXLogo.DisplayGraphic(100,100);// call to DisplayGraphic method of the MasterGraphic class
 	mxhwnd.text.printtext("Master's TicTacToe written by Jared Bruni",10,10);// print out to the screen nancy's tictactoe
	mxhwnd.text.printtext("written utilizing MasterX SDK in masterlibrary4",10,30);
	mxhwnd.text.printtext("press enter to return to the game ",10,60);
}

// function to draw the Board
void DrawBoard()
{

	for(int i = 0; i < 3; i++)
	{
		for(int z = 0; z < 3; z++) // nested for loop
		{
			// if statements to draw the different rows of the Board
			if(i == 0 && z == 0)
			{
				switch(Board[i][z])
				{
				case X:
					{
						XGraphic.DisplayGraphic(100,150);
					}
					break;
				case O:
					{
						OGraphic.DisplayGraphic(100,150);
					}
					break;
				}

			}
			
			if(i == 0 && z == 1)
			{
				switch(Board[i][z])
				{
				case X:
					{
						XGraphic.DisplayGraphic(300,150);
					}
					break;
				case O:
					{
						OGraphic.DisplayGraphic(300,150);
					}
					break;
				}
			}

			if(i == 0 && z == 2)
			{
				switch(Board[i][z])
				{
				case X:
					{
						XGraphic.DisplayGraphic(520,150);
					}
					break;
				case O:
					{
						OGraphic.DisplayGraphic(520,150);
					}
					break;
				}

			}

			if(i == 1 && z == 0)
			{
				switch(Board[i][z])
				{
				case X:
					{
						XGraphic.DisplayGraphic(100,260);
					}
					break;
				case O:
					{
						OGraphic.DisplayGraphic(100,260);
					}
					break;
				}

			}

			if(i == 1 && z == 1)
			{
				switch(Board[i][z])
				{
				case X:
					{
						XGraphic.DisplayGraphic(300,260);
					}
					break;
				case O:
					{
						OGraphic.DisplayGraphic(300,260);
					}
					break;
				}

			}

			if(i == 1 && z == 2)
			{
				switch(Board[i][z])
				{
				case X:
					{
						XGraphic.DisplayGraphic(520,260);
					}
					break;
				case O:
					{
						OGraphic.DisplayGraphic(520,260);
					}
					break;
				}


			}

			if(i == 2 && z == 0)
			{
				switch(Board[i][z])
				{
				case X:
					{
						XGraphic.DisplayGraphic(100,380);
					}
					break;
				case O:
					{
						OGraphic.DisplayGraphic(100,380);
					}
					break;
				}

			}

			if(i == 2 && z == 1)
			{
				switch(Board[i][z])
				{
				case X:
					{
						XGraphic.DisplayGraphic(300,380);
					}
					break;
				case O:
					{
						OGraphic.DisplayGraphic(300,380);
					}
					break;
				}
			}

			if(i == 2 && z == 2)
			{
				switch(Board[i][z])
				{
				case X:
					{
						XGraphic.DisplayGraphic(520,380);
					}
					break;
				case O:
					{
						OGraphic.DisplayGraphic(520,380);
					}
					break;
				}

			}
		}
	}
}