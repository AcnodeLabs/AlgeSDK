#include "CVec.hpp"

class CQuaternion {
public:
	float x,y,z,w;

	CQuaternion() {
		clear();
	}
	
	void clear() {
		x = 0; y=0; z=0; w=1;
	}

	CQuaternion(float fx, float fy, float fz, float fw) {
		x = fx; y=fy; z=fz; w=fw;
	}

	void getAxis() {}
	void getAngleRadians() {}

	//Calls glRotatef and applies this CQuat onto it
	void alDoRotate2D() {
		double a = 2 * acos(w);// = 0
		double div = sqrt(1-w*w);
		if (div==0) return;
		double rx = x /div;
		double ry = y /div;
		double rz = 0;//z / div;
		bool active = (rx!=0 || ry!=0 || rx!=0);
		if (active) {
#ifndef NOGL
#ifndef NTDDI_WIN8
		 glRotatef(a * 57.2727272727f, rx,ry,rz);
#endif
#endif
		}
	}
	//Calls glRotatef and applies this CQuat onto it
	void alDoRotate() {
		double a = 2 * acos(w);// = 0
		double div = sqrt(1-w*w);
		if (div==0) return;
		double rx = x /div;
		double ry = y /div;
		double rz = z / div;
		bool active = (rx!=0 || ry!=0 || rx!=0);
		if (active) {
#ifndef NOGL
//#ifndef NTDDI_WIN8
			glRotatef(a * 57.2727272727f, rx,ry,rz);
//#endif
#endif
		}
	}

	static CQuaternion CreateFromVectors(vec3 v0, vec3 v1)  {
		CQuaternion q;
		
		if (v0 == -v1) {//Create from Axis Angle
		  //int a = 1;
		}

		vec3 c = v0.Cross(v1);
		float d = v0.Dot(v1);
		
		float s = (float)  sqrt((1+d)*2);

		q.x = c.x /s;
		q.y = c.y/s;
		q.z = c.z/s;
		q.w = s / 2.0f;
		return q;
	}

	CQuaternion Rotated(CQuaternion b) {
		CQuaternion q(x,y,z,w);
		q.w = w * b.w  - x *b.x - y*b.y -z*b.z;
		q.x  = w * b.x  + x *b.w +  y*b.z - z*b.y;
		q.y  = w * b.y  + y *b.w + z*b.x - x*b.z;
		q.z  = w * b.z  + z *b.w + x*b.y - y*b.x;
		return q;
	}


	void copy(CQuaternion q) {
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}
};