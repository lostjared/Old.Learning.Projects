#ifndef __MXMATH__H_
#define __MXMATH__H_
#include<math.h>
#include<iostream>

using namespace std;

class mxRay;



typedef class mxVector {

	
	float x,y,z,w;
	DWORD color;
public:
	mxVector() { x = y = z = w = 0; }
	mxVector(float x, float y, float z, float w) {
		setVector(x,y,z,1.0f,0x0);
	}
	void setVector( float x, float y, float z, float w, DWORD color ) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		this->color = color;
	}
	void setVector( float x, float y, float z ) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = 1.0f;
	}

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getW() { return w; }

	void operator=(mxVector& vect) {
		this->x = vect.getX();
		this->y = vect.getY();
		this->z = vect.getZ();
		this->w = vect.getW();
	}

	mxVector operator+(mxVector& vect) {

		this->x += vect.getX();
		this->y += vect.getY();
		this->z += vect.getZ();
		this->w += vect.getW();
		return (*this);
	}

	mxVector operator-(mxVector& vect) {
		this->x -= vect.getX();
		this->y -= vect.getY();
		this->z -= vect.getZ();
		this->w -= vect.getW();
		return (*this);
	}

	mxVector operator*(mxVector& vect) {
		this->x *= vect.getX();
		this->y *= vect.getY();
		this->z *= vect.getZ();
		this->w *= vect.getW();
		return (*this);
	}

	mxVector operator/(mxVector& vect) {
		this->x /= vect.getX();
		this->y /= vect.getY();
		this->z /= vect.getZ();
		this->w /= vect.getW();
		return (*this);
	}

	void operator+=(mxVector& vect) {
		this->operator+(vect);
	}
	void operator-=(mxVector& vect) {
		this->operator-(vect);
	}

	void operator*=(mxVector& vect) {
		this->operator*(vect);
	}
	void operator/=(mxVector& vect) {
		this->operator/(vect);
	}

	void Negative() {
		x = -x;
		y = -y;
		z = -z;
		w = -w;
	}

	void Difference(mxVector& vect1, mxVector& vect2) {
		x = vect2.x - vect1.x;
		y = vect2.y - vect1.y;
		z = vect2.z - vect2.z;
		w = 1.0f;
	}

	float SqrLen() { return ((x*x) + (y*y) + (z*z)); }

	float GetLen() { return (float) sqrt(x*x + y*y + z*z); }

	void Normalize() { 
		float f = 0;
		f = (float) sqrt(x*x + y*y + z*z);
		if(f != 0.0f) {
			x/=f; 
			y/=f;
			z/=f;
		}
	}

	friend class mxRay;

}mxVertex;

class mxMatrix {
public:
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;

	mxMatrix() { memset(this,0,sizeof(mxMatrix)); }

	void Identity() {
		float *f = (float*)&this->m11;
		memset(f,0,sizeof(mxMatrix));
		m11 = m22 = m33 = m44 = 1.0f;
	}

	void operator=(mxMatrix &m) {
		memcpy(this,&m,sizeof(mxMatrix));
	}

	void RotateX(float m) {
		float fc = cosf(m);
		float fs = sinf(m);
		m22 = fc;
		m23 = fs;
		m32 = fs;
		m33 = fc;
		m11 = m44 = 1.0f;
		m12=m13=m14=m=m21=m24=m31=m34=m41=m42=m43=0.0f;
	}

	void RotateY(float m) {
		float fc = cosf(m);
		float fs = sinf(m);
		m11 = fc;
		m13 = fs;
		m31 = fs;
		m33 = fc;

		m22 = m44 = 1.0f;
		m12 = m23 = m14 = m21 = m24 = m32 = m34 = m41 = m42 = m43 = 0.0f;
	}

	void RotateZ(float m) {
		float fc = cosf(m);
		float fs = sinf(m);
		m11 = fc;
		m12 = fs;
		m21 = fs;
		m22 = fc;
		m33 = m44 = 1.0f;
		m13 = m14 = m23 = m24 = m31 = m32 = m34 = m41 = m42 = m43 = 0.0f;
	}

	void RotateArb(mxVector Axis, float m) {
		float fc = cosf(m);
		float fs = sinf(m);
		float fsum = 1.0f - fc;
		Axis.Normalize();

		m11 = (Axis.getX()*Axis.getX()) * fsum + fc;
		m12 = (Axis.getX()*Axis.getY()) * fsum - (Axis.getZ()*fs);
		m13 = (Axis.getX()*Axis.getZ()) * fsum + (Axis.getY()*fs);
		
		m21 = (Axis.getY()*Axis.getX()) * fsum + (Axis.getZ()*fs);
		m22 = (Axis.getY()*Axis.getY()) * fsum + fc;
		m23 = (Axis.getY()*Axis.getZ()) * fsum - (Axis.getX()*fs);

		m31 = (Axis.getZ()*Axis.getX()) * fsum - (Axis.getY()*fs);
		m32 = (Axis.getZ()*Axis.getY()) * fsum + (Axis.getX()*fs);

		m14 = m24 = m34 = m41 = m42 = m43 = 0.0f;
		m44 = 1.0f;
	}

	void Translatef(float dx, float dy, float dz) {
		m41 = dx;
		m42 = dy;
		m43 = dz;
	}

	void Transpose(const mxMatrix& m) {
		m11 = m.m11;
		m21 = m.m12;
		m31 = m.m13;
		m41 = m.m14;

		m12 = m.m21;
		m22 = m.m22;
		m32 = m.m23;
		m42 = m.m24;

		m13 = m.m31;
		m23 = m.m32;
		m33 = m.m33;
		m43 = m.m34;

		m14 = m.m41;
		m24 = m.m42;
		m34 = m.m43;
		m44 = m.m44;
	}

	void Inverse(const mxMatrix &m) {
		m11 = -m.m11;
		m12 = -m.m12;
		m13 = -m.m13;
		m14 = -m.m14;
		m21 = -m.m21;
		m22 = -m.m22;
		m23 = -m.m23;
		m24 = -m.m24;
		m31 = -m.m31;
		m32 = -m.m32;
		m33 = -m.m33;
		m34 = -m.m34;
		m41 = -m.m41;
		m42 = -m.m42;
		m43 = -m.m43;
		m44 = -m.m44;
	}
};

class mxRay {
public:
	mxVector orig, dir;
	mxRay() {}
	void SetRay(mxVector orig, mxVector dir) {
		this->orig = orig;
		this->dir = dir;
	}
	void DeTrans(const mxMatrix &matrix) {
		mxMatrix mi;
		mxMatrix m=matrix;

		orig.x = m.m41;
		orig.y = m.m42;
		orig.z = m.m43;

		m.m41 = m.m42 = m.m43 = 0;

	}
};


#endif
