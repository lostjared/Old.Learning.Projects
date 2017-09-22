/* MasterPeaceD3D - written by Jared Bruni
purposely written a mix between C++-style && C-style for fun :)
*/

//#define _DEBUG_ON

#include"mx3d.h"
#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_TEX1 )
mxHwnd mxhwnd;
mxScreen &screen = mxhwnd.screen;
const int STARTUP_SCREEN = 0;
LPDIRECT3DTEXTURE9 textures[11];
IDirect3DVertexBuffer9 *g_pVertexBuffer;
int num_images = 10;
static char *img_array[] = { "img\\block_clear.bmp", "img\\block_dblue.bmp", "img\\block_gray.bmp", "img\\block_green.bmp", "img\\block_ltblue.bmp", "img\\block_orange.bmp", "img\\block_pink.bmp", "img\\block_purple.bmp","img\\block_red.bmp","img\\block_yellow.bmp" };
HFONT fnt[2] = {CreateFont(17,0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,VARIABLE_PITCH,"Arial"), CreateFont(50,0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,VARIABLE_PITCH,"Arial")};
int cursor_pos = 0, score = 0, blocks = 0, speed = 15;


struct block {
	int x,y,color;
};
struct tile {
	int color;
	bool ani;
	int prev_color;

	tile() {
		prev_color = 0;
		ani = false;
	}

	bool operator==(const int &x) {
		if(this->color == x)
			return true;
			return false;
	}

	void operator=(int x) {
		if(x == 0) {
			prev_color = color, ani = true;
		}
		this->color = x;
	}
	bool operator!=(const int &x) {
		if(this->color != x)
			return true;
		return false;
	}
};

struct tile tiles[8][17];
struct block game_blocks[3];
static float cube_rot_x = 1.0f;

struct Vertex
{
	float x, y, z;
	float tu, tv;
};

Vertex Vertices[] =
{
	{-1.0f, 1.0f,-1.0f,  0.0f,0.0f },
	{ 1.0f, 1.0f,-1.0f,  1.0f,0.0f },
	{-1.0f,-1.0f,-1.0f,  0.0f,1.0f },
	{ 1.0f,-1.0f,-1.0f,  1.0f,1.0f },

	{-1.0f, 1.0f, 1.0f,  1.0f,0.0f },
	{-1.0f,-1.0f, 1.0f,  1.0f,1.0f },
	{ 1.0f, 1.0f, 1.0f,  0.0f,0.0f },
	{ 1.0f,-1.0f, 1.0f,  0.0f,1.0f },

	{-1.0f, 1.0f, 1.0f,  0.0f,0.0f },
	{ 1.0f, 1.0f, 1.0f,  1.0f,0.0f },
	{-1.0f, 1.0f,-1.0f,  0.0f,1.0f },
	{ 1.0f, 1.0f,-1.0f,  1.0f,1.0f },

	{-1.0f,-1.0f, 1.0f,  0.0f,0.0f },
	{-1.0f,-1.0f,-1.0f,  1.0f,0.0f },
	{ 1.0f,-1.0f, 1.0f,  0.0f,1.0f },
	{ 1.0f,-1.0f,-1.0f,  1.0f,1.0f },

	{ 1.0f, 1.0f,-1.0f,  0.0f,0.0f },
	{ 1.0f, 1.0f, 1.0f,  1.0f,0.0f },
	{ 1.0f,-1.0f,-1.0f,  0.0f,1.0f },
	{ 1.0f,-1.0f, 1.0f,  1.0f,1.0f },

	{-1.0f, 1.0f,-1.0f,  1.0f,0.0f },
	{-1.0f,-1.0f,-1.0f,  1.0f,1.0f },
	{-1.0f, 1.0f, 1.0f,  0.0f,0.0f },
	{-1.0f,-1.0f, 1.0f,  0.0f,1.0f }
};

inline void randtile() {
	unsigned int i;
	for(i = 0; i < 3; i++) {
		game_blocks[i].color = (rand()%num_images)+1;
	}

	if(game_blocks[0].color == game_blocks[1].color && game_blocks[0].color == game_blocks[2].color) {
		randtile();
		return;
	}

	game_blocks[0].x = 3;
	game_blocks[0].y = 0;
	game_blocks[1].x = 3;
	game_blocks[1].y = 1;
	game_blocks[2].x = 3;
	game_blocks[2].y = 2;
}

inline void merge_blocks() {
	int p;
	for(p = 0; p < 3; p++)
		tiles[game_blocks[p].x][game_blocks[p].y] = game_blocks[p].color;
	randtile();
}

inline void init_game() {
	memset(tiles,0,sizeof(tiles));
	score = 0;
	blocks = 0;
	speed = 15;
	randtile();
}

inline void move_left() {
	int p;
	for(p = 0; p < 3; p++) {
		if(game_blocks[p].x-1 < 0 || tiles[game_blocks[p].x-1][game_blocks[p].y] != 0)
			return;
	}

	for(p = 0; p < 3; p++) {
		game_blocks[p].x--;
	}
}

inline void move_right() {
	int p;
	for(p = 0; p < 3; p++) {
		if(game_blocks[p].x+1 >= 8 || tiles[game_blocks[p].x+1][game_blocks[p].y] != 0)
			return;
	}

	for(p = 0; p < 3; p++) {
		game_blocks[p].x++;
	}
}

inline void move_down() {
	if(game_blocks[2].y+1 < 17 && tiles[game_blocks[2].x][game_blocks[2].y+1] == 0)
	{
		int p;
		for(p = 0; p < 3; p++) {
			game_blocks[p].y++;
		}
	}
	else if(game_blocks[2].y <= 2) {
		mxhwnd.SetScreen(3);
	}
	else
		merge_blocks();
}

inline void move_blocks_down() {
	static int cnt = 0;
	for(int i = 0; i < 8; i++)
		for(int z = 0; z < 16; z++)
			if(tiles[i][z] != 0 && tiles[i][z+1] == 0) {
				tiles[i][z+1] = tiles[i][z];
				tiles[i][z] = 0;
				move_blocks_down();
				return;
			}

			if(++cnt > 3)
			{
				cnt = 0;
				cube_rot_x = 1;
			}
}

inline bool bounds(int x, int y) {
	if(x < 0 || y < 0 || x >= 8 || y >= 17)
		return false;
	return true;
}

inline void inc_score() {
	score += 10;
	blocks++;
	if(blocks > 10)
		speed = 12;
	else if(blocks > 20) {
		speed = 8;
	}
}

inline void proc_blocks() {

	for(int i = 0; i < 8; i++) {
		for(int z = 0; z < 17; z++) {
			int cur_color = tiles[i][z].color;
			if(cur_color != 0) {
				// 3 in a row going across
				if(bounds(i+2,z) && tiles[i+1][z] == cur_color && tiles[i+2][z] == cur_color) {
					tiles[i][z] = 0;
					tiles[i+1][z] = 0;
					tiles[i+2][z] = 0;
					inc_score();
				}
				// 3 in a row going down
				if(bounds(i,z+2) && tiles[i][z+1] == cur_color && tiles[i][z+2] == cur_color) {
					tiles[i][z] = 0;
					tiles[i][z+1] = 0;
					tiles[i][z+2] = 0;
					inc_score();
				}

				// 3 in a row diagnoal

				if(bounds(i+2,z+2) && tiles[i+1][z+1] == cur_color && tiles[i+2][z+2] == cur_color) {
					tiles[i][z] = 0;
					tiles[i+1][z+1] = 0;
					tiles[i+2][z+2] = 0;
					inc_score();
				}

				if(bounds(i-2,z-2) && tiles[i-1][z-1] == cur_color && tiles[i-2][z-2] == cur_color) {
					tiles[i][z] = 0;
					tiles[i-1][z-1] = 0;
					tiles[i-2][z-2] = 0;
					inc_score();
				}

				if(bounds(i-2,z+2) && tiles[i-1][z+1] == cur_color && tiles[i-2][z+2] == cur_color) {
					tiles[i][z] = 0;
					tiles[i-1][z+1] = 0;
					tiles[i-2][z+2] = 0;
					inc_score();
				}

				if(bounds(i+2,z-2) && tiles[i+1][z-1] == cur_color && tiles[i+2][z-2] == cur_color) {
					tiles[i][z] = 0;
					tiles[i+1][z-1] = 0;
					tiles[i+2][z-2] = 0;
					inc_score();
				}
			}
		}
	}
}

inline void shift_blocks() {
	int ic1;
	int ic2;
	int ic3;
	ic1 = game_blocks[0].color;
	ic2 = game_blocks[1].color;
	ic3 = game_blocks[2].color;
	game_blocks[0].color = ic3;
	game_blocks[1].color = ic1;
	game_blocks[2].color = ic2;
}
LRESULT CALLBACK MpProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATEAPP:
			mxhwnd.active = wParam;
			break;
		case WM_KEYDOWN:
			{
				switch(mxhwnd.GetScreen()) 
				{
				case 1:
					if(wParam == VK_UP || wParam == VK_DOWN)
						cursor_pos = !cursor_pos;
					else if(wParam == VK_RETURN) {
						switch(cursor_pos) 
						{
						case 0:
							mxhwnd.text.setfont(fnt[0]);
							mxhwnd.SetScreen(2);
							break;
						case 1:
							mxhwnd.Kill();
							break;
						}
					}
					break;
				case 2:
					{
						switch(wParam) 
						{
						case VK_LEFT:
							move_left();
							break;
						case VK_RIGHT:
							move_right();
							break;
						case VK_DOWN:
							move_down();
							break;
						case 'A':
						case 'a':
							shift_blocks();
							break;
						}
					}
					break;
				}
			}
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

void drawCube(LPDIRECT3DTEXTURE9 tex) {
	screen.pd3d_dev->SetTexture( 0, tex );
	screen.pd3d_dev->SetStreamSource( 0, g_pVertexBuffer, 0, sizeof(Vertex) );
	screen.pd3d_dev->SetFVF( D3DFVF_CUSTOMVERTEX );
	screen.pd3d_dev->DrawPrimitive( D3DPT_TRIANGLESTRIP,  0, 2 );
	screen.pd3d_dev->DrawPrimitive( D3DPT_TRIANGLESTRIP,  4, 2 );
	screen.pd3d_dev->DrawPrimitive( D3DPT_TRIANGLESTRIP,  8, 2 );
	screen.pd3d_dev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 12, 2 );
	screen.pd3d_dev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 16, 2 );
	screen.pd3d_dev->DrawPrimitive( D3DPT_TRIANGLESTRIP, 20, 2 );
}

void render_intro() {
	D3DXMATRIX matView;
	static float y = 45.0f;
	y++;
	D3DXMatrixPerspectiveFovLH( &matView, D3DXToRadian( y ), 640.0f / 480.0f, 0.1f, 100.0f );
	mxhwnd.screen.pd3d_dev->SetTransform(D3DTS_VIEW,&matView);

	mxhwnd.screen.pd3d_dev->BeginScene();

	static float roll = 0.0f, angle_x = 0, angle_y = 0, angle_z = 0;
	roll += 0.1f;
	D3DXMATRIX trans,rot_y, rot_x, rot_z,world,rotf;
	for(float x = -12; x < 13; x += 3.0f)
		for(float y = 8; y > -9; y -= 3.0f) {
			D3DXMatrixTranslation( &trans, .5f+x, y, 50.0f );
			D3DXMatrixRotationX(&rot_x, D3DXToRadian(angle_x));
			D3DXMatrixRotationZ(&rot_y, D3DXToRadian(angle_z));
			D3DXMatrixRotationY(&rot_z, D3DXToRadian(angle_y));
			world = rot_x * rot_y * rot_z * trans;
			mxhwnd.screen.pd3d_dev->SetTransform(D3DTS_WORLD,&world);

			drawCube(textures[(rand()%num_images)+1]);
		}
		mxhwnd.screen.pd3d_dev->EndScene();
		if(mxhwnd.input.key.KeyCheck(DIK_UP)) {
			angle_x += 0.2f;
		}
		if(mxhwnd.input.key.KeyCheck(DIK_DOWN)) {
			angle_x -= 0.2f;
		}
		if(mxhwnd.input.key.KeyCheck(DIK_LEFT)) {
			angle_y += 0.2f;
		}
		if(mxhwnd.input.key.KeyCheck(DIK_RIGHT)) {
			angle_y -= 0.2f;
		}
		if(mxhwnd.input.key.KeyCheck(DIK_Z)) {
			angle_z += 0.2f;
		}
		if(mxhwnd.input.key.KeyCheck(DIK_X)) {
			angle_z -= 0.2f;
		}


		angle_y += 0.5f;
		angle_x += 0.5f;
		angle_z += 0.5f;

		mxhwnd.text.settextcolor(D3DCOLOR_XRGB(rand()%255,rand()%255,rand()%255));
		mxhwnd.text.printtextf(100,100,"%s Start New Game\n %s Exit.", cursor_pos == 0 ? "=)>" : "" , cursor_pos == 1 ? "=)>" : "");


}

void render_startup() {
	static bool enter_pressed = false;
	static float ang_x = 0.0f, ang_y = 0.0f, ang_z = 0.0f, far_z = 2.8f;

	D3DXMATRIX trans,rot_y,rot_x,rot_z,world;
	D3DXMatrixTranslation( &trans, 0, 0, far_z );
	D3DXMatrixRotationZ(&rot_z, ang_z);
	D3DXMatrixRotationY(&rot_y, ang_y);
	D3DXMatrixRotationX(&rot_x, ang_x);
	if(enter_pressed == false)
		mxhwnd.text.printtextf(640/2-70,0,"Press [Enter] To continue..\n");
	world = rot_x * rot_y * rot_z * trans;
	mxhwnd.screen.pd3d_dev->BeginScene();
	mxhwnd.screen.pd3d_dev->SetTransform(D3DTS_WORLD, &world);
	drawCube(textures[0]);
	mxhwnd.screen.pd3d_dev->EndScene();

	if(enter_pressed == false) {
		if(mxhwnd.input.key.KeyCheck(DIK_RETURN)) 
			enter_pressed = true;
	}
	else {
		if(ang_y < 10)
			ang_y += 0.1f;
		else {
			ang_x += 0.1f;
			ang_y += 0.1f;
			if(ang_y > 10) {
				ang_z += 0.1f;
				if(ang_z > 10) {
					far_z += 0.1f;
					if(far_z > 30) {
						mxhwnd.SetScreen(1);
						mxhwnd.text.setfont(fnt[1]);
						ang_x = ang_y = ang_z = 0;
						far_z = 2.8f;
					}
				}
			}
		}
#ifdef _DEBUG_ON
		mxhwnd.text.printtextf(0,0,"%f %f %f %f\n", ang_y, ang_x, ang_z, far_z);
#endif
	}
}

void render_game_over() {
	mxhwnd.text.printtextf(100,100,"Game over!!");
}

void render_game() {
	static float spacing = 3.0f, per = 140.0f;
	float trans_x = -16.0f, trans_y = 30.0f;
	static int movement = 0;
	if(++movement > speed) {
		move_down();
		movement = 0;
	}

	proc_blocks();
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( per ), 640.0f / 480.0f, 0.1f, 150.0f );
	static float rot_y = 1.0f;
	static bool rotate = false;
	static bool found_ani = false;
	rot_y ++;
	screen.pd3d_dev->SetTransform( D3DTS_VIEW, &matProj );
	mxhwnd.screen.pd3d_dev->BeginScene();
	
	for(int i = 0; i < 8; i++) {
		for(int z = 0; z < 17; z++) {
			D3DXMATRIX trans,mrot_y,mrot_z, mrot_x, mat;
			D3DXMatrixTranslation(&trans,trans_x,trans_y,30.0f);
			D3DXMatrixRotationY(&mrot_y, rot_y);
			D3DXMatrixRotationZ(&mrot_z, rot_y);
			D3DXMatrixRotationX(&mrot_x, rot_y);
			mat = trans;
			mxhwnd.screen.pd3d_dev->SetTransform(D3DTS_WORLD,&mat);
			bool drawn = false;
			for(int p = 0; p < 3; p++) {
				if(game_blocks[p].x == i && game_blocks[p].y == z) {
					if(mxhwnd.input.key.KeyCheck(DIK_S))
						rotate = true;
					else
						rotate = false;
					if(rotate == true) {
						mat = mrot_x * mrot_y * mrot_z * trans;
						mxhwnd.screen.pd3d_dev->SetTransform(D3DTS_WORLD,&mat);
					}
					drawCube(textures[game_blocks[p].color]);
					drawn = true;
				}
			}
			if(drawn == false) {
				if(tiles[i][z].ani == false)
				drawCube(textures[tiles[i][z].color]);
				else {
					
					
					D3DXMatrixRotationY(&mrot_y, cube_rot_x);
					D3DXMatrixRotationZ(&mrot_z, cube_rot_x);
					D3DXMatrixRotationX(&mrot_x, cube_rot_x);
					mat = mrot_y * mrot_x * mrot_z * trans;
					mxhwnd.screen.pd3d_dev->SetTransform(D3DTS_WORLD,&mat);
					drawCube(textures[(rand()%num_images)+1]);
					if((cube_rot_x += 0.1f) > 10) {
						tiles[i][z].ani = false;
						tiles[i][z].color = 0;
						move_blocks_down();
					}

					
				}
			}
			trans_y -= 3.5f;
		}
		trans_x += 4.5f;
		trans_y = 30.0f;
	}
	mxhwnd.screen.pd3d_dev->EndScene();
	mxhwnd.text.printtextf(10,10,"Score: %d , Blocks: %d, Speed: %d", score, blocks, speed);

	if(mxhwnd.input.key.KeyCheck(DIK_SPACE))
		spacing += .01f;

	if(mxhwnd.input.key.KeyCheck(DIK_Z)) {
		per -= 0.1f;
	}

	if(mxhwnd.input.key.KeyCheck(DIK_X)) {
		per += 0.1f;
	}

}

void render(int screen) {
	mxhwnd.SetTicks();
	switch(screen) {
		case 0:
			render_startup();
			break;
		case 1:
			render_intro();
			break;
		case 2:
			render_game();
			break;
		case 3:
			render_game_over();
			break;
	}
	if(screen == 2)
		mxhwnd.WaitTicks(30);
	else
		mxhwnd.WaitTicks(5);
}

inline void load() {
	srand(unsigned int(GetTickCount()));

	D3DXCreateTextureFromFile( screen.pd3d_dev, "img\\logo.bmp", &textures[0] );
	for(int i = 0; i < num_images; i++) 
		D3DXCreateTextureFromFile(screen.pd3d_dev, img_array[i], &textures[i+1] );

	screen.pd3d_dev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	screen.pd3d_dev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	screen.pd3d_dev->CreateVertexBuffer( 24*sizeof(Vertex),0, D3DFVF_CUSTOMVERTEX,D3DPOOL_DEFAULT, &g_pVertexBuffer, NULL );
	void *pVertices = NULL;

	g_pVertexBuffer->Lock( 0, sizeof(Vertices), (void**)&pVertices, 0 );
	memcpy( pVertices, Vertices, sizeof(Vertices) );
	g_pVertexBuffer->Unlock();

	screen.pd3d_dev->SetRenderState( D3DRS_LIGHTING, FALSE );
	screen.pd3d_dev->SetRenderState( D3DRS_ZENABLE, TRUE );

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DXToRadian( 45.0f ), 640.0f / 480.0f, 0.1f, 100.0f );
	screen.pd3d_dev->SetTransform( D3DTS_PROJECTION, &matProj );
	mxhwnd.SetScreen(STARTUP_SCREEN);
	init_game();
}

inline void rls() {
	for(int i = 0; i < num_images+1; i++) {
		if(textures[i]) 
			textures[i]->Release();
	}
	if(g_pVertexBuffer)
		g_pVertexBuffer->Release();

	DeleteObject(fnt[0]);
	DeleteObject(fnt[1]);
}

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev, LPSTR line, int cmd) {

	if(mxhwnd.Init("mpd3d", false, 0,0,640,480,MpProc,0) && mxhwnd.InitDX(false,32)) {
		memset(textures, 0, sizeof(textures));
		load();
		mxhwnd.text.setfont(fnt[0]);
		mxhwnd.InitLoop(render);
		rls();
	}


	return 0;
}