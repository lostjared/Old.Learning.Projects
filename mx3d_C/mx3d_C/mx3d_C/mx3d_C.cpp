#include "mx3d.h"
#include "mx3d_texture.h"
#include "mx3d_math.h"

#include<string>

mxHwnd mxhwnd;

class Err {
public:
	Err(std::string source) {
		src = source;
	}
	void Exception() {
		MessageBox(GetForegroundWindow(), src.c_str(), "Unhandled Exception!\n", MB_OK | MB_ICONERROR);
	}
protected:
	std::string src;
};

class LPipe : public mx3d::PipeLine {
protected:
	mx3d::mxTexture *tex;
public:
	inline void DrawArt(mx3d::mxTexture *tex, mx3d::RenderList &l) {
		this->tex = tex;
		for(unsigned int i = 0; i < l.polys.size(); i++) {
			if(l.polys[i].state == 0 || l.polys[i].state == mx3d::MX_BACKFACE )
				continue;
			this->drawtextri(int(l.polys[i].tlist[0].x), int(l.polys[i].tlist[0].y), int(l.polys[i].tlist[1].x), int(l.polys[i].tlist[1].y), int(l.polys[i].tlist[2].x), int(l.polys[i].tlist[2].y),D3DCOLOR_XRGB(rand()%255,rand()%255,rand()%255));
		}
	}

	inline void drawhline(int x,int x2, int y, D3DCOLOR color) {
		static int i = 0, z = 0;
		for(int p = x; p <= x2; p++) {
				if(++i > tex->width-1) i = 0;
				if(++z > tex->height-1) z = 0;
				mx->paint.fast_sp(p,y,mx->paint.rect.Pitch,tex->getPixel(i,z));
		}
	}

	inline void drawtextri(int x1, int y1,int x2, int y2, int x3, int y3, D3DCOLOR color) {
		int temp_x,temp_y,new_x;

		if ((x1==x2 && x2==x3)  ||  (y1==y2 && y2==y3))
			return;

		if (y2<y1) {
			temp_x = x2;
			temp_y = y2;
			x2     = x1;
			y2     = y1;
			x1     = temp_x;
			y1     = temp_y;
		}

		if (y3<y1) {
			temp_x = x3;
			temp_y = y3;
			x3     = x1;
			y3     = y1;
			x1     = temp_x;
			y1     = temp_y;
		}

		if (y3<y2) {
			temp_x = x3;
			temp_y = y3;
			x3     = x2;
			y3     = y2;
			x2     = temp_x;
			y2     = temp_y;

		} 
		if ( y3<min_clip_y || y1>max_clip_y || (x1<min_clip_x && x2<min_clip_x && x3<min_clip_x) || (x1>max_clip_x && x2>max_clip_x && x3>max_clip_x) )
			return;


		if (y1==y2)  {
			this->drawtoptri(x1,y1,x2,y2,x3,y3,color);
		} 
		else
			if (y2==y3){
				this->drawbottomtri(x1,y1,x2,y2,x3,y3,color);
			} 
			else {
				new_x = x1 + (int)(0.5+(float)(y2-y1)*(float)(x3-x1)/(float)(y3-y1));
				this->drawbottomtri(x1,y1,new_x,y2,x2,y2,color);
				this->drawtoptri(x2,y2,new_x,y2,x3,y3,color);
			} 
	}

	inline void drawtoptri(int x1, int y1,int x2, int y2, int x3, int y3, D3DCOLOR color) {

		float dx_right,dx_left,xs,xe,height;  

		int temp_x,temp_y,right,left;

		if (x2 < x1) {
			temp_x = x2;
			x2     = x1;
			x1     = temp_x;
		}

		height = float(y3-y1);

		dx_left  = (x3-x1)/height;
		dx_right = (x3-x2)/height;

		xs = (float)x1;
		xe = (float)x2; 
		if (y1 < min_clip_y) {
			xs = xs+dx_left*(float)(-y1+min_clip_y);
			xe = xe+dx_right*(float)(-y1+min_clip_y);
			y1=min_clip_y;
		}

		if (y3>max_clip_y)
			y3=max_clip_y;

		if (x1>=min_clip_x && x1<=max_clip_x && x2>=min_clip_x && x2<=max_clip_x && x3>=min_clip_x && x3<=max_clip_x) {
			for (temp_y=y1; temp_y<=y3; temp_y++) {
				drawhline(int(xs),int(xs+(int)xe-xs+1),temp_y,color);
				xs+=dx_left;
				xe+=dx_right;
			} 
		}
		else {
			for (temp_y=y1; temp_y<=y3; temp_y++) {
				left  = (int)xs;
				right = (int)xe;
				xs+=dx_left;
				xe+=dx_right;
				if (left < min_clip_x) {
					left = min_clip_x;
					if (right < min_clip_x)
						continue;
				}

				if (right > max_clip_x) {
					right = max_clip_x;

					if (left > max_clip_x)
						continue;
				}
				drawhline((int)left,(int)left+(int)right-left+1,temp_y,color);
			}
		}
	}

		inline void drawbottomtri(int x1, int y1, int x2, int y2, int x3, int y3, D3DCOLOR color) {
			float dx_right,dx_left,xs,xe,height;     
			int temp_x,temp_y,right,left;
			if (x3 < x2) {
				temp_x = x2;
				x2     = x3;
				x3     = temp_x;
			}
			height = float(y3-y1);
			dx_left  = (x2-x1)/height;
			dx_right = (x3-x1)/height;

			xs = (float)x1;
			xe = (float)x1;
			if (y1 < min_clip_y) {
				xs = xs+dx_left*(float)(-y1+min_clip_y);
				xe = xe+dx_right*(float)(-y1+min_clip_y);
				y1 = min_clip_y;
			}

			if (y3 > max_clip_y)
				y3 = max_clip_y;

			if (x1>=min_clip_x && x1<=max_clip_x && x2>=min_clip_x && x2<=max_clip_x && x3>=min_clip_x && x3<=max_clip_x) {
				for (temp_y=y1; temp_y<=y3; temp_y++) {
					drawhline(int(xs),(int)xs+(int(xe-xs+1)),temp_y,color);
					xs+=dx_left;
					xe+=dx_right;

				} 
			}
			else
			{
				for (temp_y=y1; temp_y<=y3; temp_y++) {
					left  = (int)xs;
					right = (int)xe;
					xs+=dx_left;
					xe+=dx_right;

					if (left < min_clip_x){
						left = min_clip_x;

						if (right < min_clip_x)
							continue;
					}

					if (right > max_clip_x)
					{
						right = max_clip_x;

						if (left > max_clip_x)
							continue;
					}
					drawhline(int(left),(int)left+(int(right-left+1)),temp_y,color);
				}
			}
		}
};
class Visual {
	struct Pixel {
		int x,y;
		D3DCOLOR color;
	};

	Pixel pixels[640][480];
public:

	Visual(mxHwnd *mx) {
		this->mx = mx;
	}
	inline void Init() {
		if(!(tex1.LoadBMP("img\\lsd-1.bmp")))
			throw Err("Error Loading Bitmap: lsd-1.bmp");
		if(!(tex2.LoadBMP("img\\lsd-2.bmp")))
			throw Err("Error Loading Bitmap: lsd-2.bmp");

		if(!(obj.LoadPLG("mesh\\tank1.plg", mx3d::vec4D(1.0f,1.0f,1.0f,1),mx3d::vec4D(1.0f,1.0f,1.0f,1), mx3d::vec4D(0.0f,0.0f,0.0f,1))))
			throw Err("Error Loading Object Mesh!");
		cam.Init(0,mx3d::vec4D(0,100,1,1),mx3d::vec4D(0,0,0,1),0,50.0f,1000.0f,90.0f,float(mxhwnd.w),float(mxhwnd.h));
		obj.world_pos.x = 0.0f;
		obj.world_pos.y = 0.0f;
		obj.world_pos.z = 400.0f;


	}
	inline void Stretch(bool f) {
		switch(f) {
			case true: cam.pos.z --; break;
			case false: cam.pos.z ++; break;
		}
	}

	inline void Explode() {
		for(unsigned int i = 0; i< 640; i++)
			for(unsigned int z = 0; z < 480; z++) {
				pixels[i][z].x += rand()%3;
				pixels[i][z].y -= rand()%3;
				mx->paint.fast_sp(pixels[i][z].x, pixels[i][z].y, mx->paint.rect.Pitch, pixels[i][z].color);
			}
	}

	inline void LostSideDead() {
		static float alpha = 0.0f;
		mx->paint.Lock();
		alpha ++;

		tex1.AlphaBlend(0,0,*mx,tex2,alpha);
		mx->paint.UnLock();
		obj.Reset();
		static int Frame = 0;
		mxhwnd.text.printtextf(0,0,"Frame %d Alpha State (%f)\n Object Cords (%f)", ++Frame, alpha, obj.world_pos.z);
		if(Frame > 100)
			Frame = 0;

		static mx3d::Mat4D rotation_matrix;
		obj.Reset();
		float angle_x = rand()%1, angle_y = rand()%1, angle_z = 5;
		rotation_matrix.BuildXYZ(angle_x,angle_y,angle_z);	
		obj.TransformObject(rotation_matrix,0);
		obj.ModelToWorld();
		cam.BuildEuler(5);
		obj.RemoveFaces(cam.pos);
		cam.WorldToCamera(obj);
		cam.CameraToPerspective(obj);
		cam.PerspectiveToScreen(obj);
		gpipe.Begin(*mx);
		rl.Reset();
		obj.BuildRenderList(rl);
		gpipe.DrawArt(&tex1, rl);
		gpipe.End();

		if(mxhwnd.input.key.KeyCheck(DIK_UP)) {
			Stretch(false);
		}
		else if(mxhwnd.input.key.KeyCheck(DIK_DOWN)) {
			Stretch(true);
		}

		obj.world_pos.z -= 3;
		if(obj.world_pos.z <= -1000) 
			obj.world_pos.z = 400;

		static bool explo = true;
		if(mxhwnd.input.key.KeyCheck(DIK_R)) {
			explo = true;
		}

		if(mxhwnd.input.key.KeyCheck(DIK_SPACE)) {
			
			if(explo == true) {
				for(int l = 0; l < 640; l++)
					for(int s = 0; s < 480; s++)
						pixels[l][s].color = mx->paint.fast_gp(l,s), pixels[l][s].x = l, pixels[l][s].y = s;
				explo = false;
			}
			Explode();
		}

	}
protected:
	mxHwnd *mx;
	mx3d::mxTexture tex1,tex2;
	LPipe gpipe;
	mx3d::RenderList rl;
	mx3d::Triangle pysche_vec, delic_vec;
	mx3d::Camera cam;
	mx3d::Mat4D mrot;
	mx3d::mxObject obj;
};

Visual visuals(&mxhwnd);

LRESULT CALLBACK CProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {

	switch(msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_ACTIVATEAPP:
			mxhwnd.active = wParam;
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	} 
	return 0;
}

void render(int screen) {
	visuals.LostSideDead();
}

inline void Init() {
	mx3d::BuildTables();
	visuals.Init();
}

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev, char *line, int cmd) {
	try {

		if(mxhwnd.Init("mx3d_C",false,0,0,640,480,CProc,0) && mxhwnd.InitDX(false,32)) {
			Init();
			return mxhwnd.InitLoop(render);
		}
		else 
			throw Err("Error Couldnt Initalize Direct3D !\n Make sure you have DirectX 9.0c installed on your system!\n And have a good enough video card to support this application!\n");

	} catch ( Err &e) {
		e.Exception();
	}
	return 0;
}