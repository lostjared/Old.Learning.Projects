// the main proccess callback function
// written by jared bruni
// www.lostsidedead.com

#include "thehead.h"

#define ID_COMBO 104
#define ID_COMBO2 105

HWND hcombo;
HWND hcombo2;

// main callback function
LRESULT APIENTRY MainProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	bool lswitch = false;

	switch(msg)
	{
	case WM_DESTROY:
		DeleteGraphics();
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		{
			if(MessageBox(hwnd,"Do you wish to save?","Save?",MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				MenuProc(ID_FILESAVE);
			}

			SendMessage(hwnd,WM_DESTROY,0,0);
		}
		break;
	case WM_CREATE:// create the maps interface
		{
			int start_x = 5;
			int start_y = 5;
			
			int sx = start_x;
			int sy = start_y;
			
			int row_count = 0;
			
			for(int i = 0; i < LevelSize; i++)
			{
				sthwnd[i] = CreateWindow("Static",NULL,WS_CHILD | WS_VISIBLE | SS_BITMAP,sx,sy,16,16,hwnd,0,hInst,0);
				SetImage(sthwnd[i],0);
				
				
				row_count ++;
				
				sy = sy + 16;
				
				if(row_count > 20)
				{
					row_count = 0;
					sx = sx + 16;
					sy = start_y;
				}
			}

		     HWND st;
			 st = CreateWindow("Static","Draw Image",WS_CHILD | WS_VISIBLE,5+470,5,100,20,hwnd,0,hInst,0);
			 SetFont(st);
			 hcombo = CreateWindow("ComboBox",NULL,WS_VSCROLL | WS_BORDER|CBS_DISABLENOSCROLL|WS_CHILD|CBS_DROPDOWNLIST|WS_VISIBLE,5+470,25,150,100,hwnd,(HMENU)ID_COMBO,hInst,0); 
			 SetFont(hcombo);

			 // add information into the combo box
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Grass");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Stone");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Gray Brick");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Stone # 2");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Stone # 3");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Sand ");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Sand #2");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Snow");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Water");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Water #2");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Black Sky");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Blue Sky");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Special Stone");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Red Brick");
			 SendMessage(hcombo,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Blue Brick");

			 HWND st2;
			 st2 = CreateWindow("Static","Draw Tool",WS_CHILD | WS_VISIBLE,5+470,5+25+25,100,20,hwnd,0,hInst,0);
	 		 hcombo2 = CreateWindow("ComboBox",NULL,WS_VSCROLL | WS_BORDER|CBS_DISABLENOSCROLL|WS_CHILD|CBS_DROPDOWNLIST|WS_VISIBLE,5+470,25+25+25,150,100,hwnd,(HMENU)ID_COMBO2,hInst,0); 
			 SetFont(st2);
			 SetFont(hcombo2);

			 SendMessage(hcombo2,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Pencil");
			 SendMessage(hcombo2,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Square");
			 SendMessage(hcombo2,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Fill");
			 SendMessage(hcombo2,CB_ADDSTRING,255,(LPARAM)(LPCSTR)"Eraser");

			 SendMessage(hcombo,CB_SETCURSEL,0,0);
			 SendMessage(hcombo2,CB_SETCURSEL,0,0);

			
		}
		break;
	case WM_LBUTTONDOWN:
		lswitch = true;
	
	case WM_MOUSEMOVE:
		{
			int mx;
			int my;
			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			int pos;
			pos = getblockbypos(mx,my);

			if(pos != -1)
			{
				if(wParam & MK_LBUTTON || lswitch == true)
				{
					switch(cur_draw)
					{
					case 0:// pencil draw
						{
					level.level_block[pos] = cur_image;
					// only update this specific block
					SetImage(sthwnd[pos],cur_image);
						}
						break;
					case 1:// square draw
						{
							if(pos + 22 < LevelSize)
							{

							level.level_block[pos] = cur_image;
							level.level_block[pos+1] = cur_image;
							level.level_block[pos+21] = cur_image;
							level.level_block[pos+22] = cur_image;

							SetImage(sthwnd[pos],cur_image);
							SetImage(sthwnd[pos+1],cur_image);
							SetImage(sthwnd[pos+21],cur_image);
							SetImage(sthwnd[pos+22],cur_image);

							}


						}
						break;
					case 2: // fill draw
						{
							if(MessageBox(hwnd,"Are you sure you wish to fill with current block?","Are you sure?",MB_YESNO|MB_ICONQUESTION) == IDYES)
							{
								fillmap(cur_image);
							}
						}
						break;
					case 3:// erase draw
						{
							level.level_block[pos] = 10;
						// only update this specific block
						SetImage(sthwnd[pos],10);

						}
						break;
					}
				}
			}

		}
		break;
	case WM_COMMAND:
		{
			MenuProc(wParam);

			switch(HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				{
					switch(LOWORD(wParam))
					{
					case ID_COMBO:
						{
							cur_image = SendMessage(hcombo,CB_GETCURSEL,0,0);

						}
						break;
					case ID_COMBO2:
						{
							cur_draw = SendMessage(hcombo2,CB_GETCURSEL,0,0);
						}
						break;
					}
				}
				break;
			}
		}
		break;
	default: return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}