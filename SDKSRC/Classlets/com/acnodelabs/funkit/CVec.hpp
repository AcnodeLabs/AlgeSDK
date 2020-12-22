#ifndef VEC_INCLUDED
#define VEC_INCLUDED

#include <math.h>

class vec2 {
public:
	float x,y;
	vec2() { clear(); }
	vec2(float xx, float yy) {x = xx; y= yy;}
	

	float DistanceFrom(vec2 point) {
		vec2 diff = this->subtract(*this,point);
		return diff.length();
	}

	float degrees() {
		float theta;
       theta = atan(y / x);
	   float deg = theta * 180.0f / (3.14159f);
	   if (x<0 && y>0) deg+=180.0f;
	   if (x>=0 && y<0) deg+=360.0f;
	   if (x<0 && y<=0) deg+=180.0f;
	   return deg;
	}

    static vec2 subtract(vec2 a, vec2 b) {
		vec2 c;
		c.x = a.x - b.x; c.y = a.y - b.y;
		return c;
	}
	
    void clear() {
        x=0;y=0;
    }
    
	float lengthsquared() {
	
		return (float) (x*x + y*y);
	}

	float length() {
		return (float) sqrt(lengthsquared());
	}
    
    bool positive() {
        return (x>=0 && y>=0);
    }
    
    bool negative() {
        return (x<0 && y<0);
    }
};


class vec3 {
public:
	float x,y,z;
    
    vec3() { }
    
    vec3(float xx, float yy, float zz) {set(xx,yy,zz);}
	
    void set(float xx, float yy, float zz) {x = xx; y= yy; z = zz;}
	
	vec3 divide(float r) {
		vec3 ret(x/r,y/r,z/r);
		return ret;
	}

	vec3 operator - (const vec3& v) {
		return vec3(x-v.x,y-v.y,z-v.z);
	}
	
	vec3 operator * (float v) {
		return vec3(x*v,y*v,z*v);
	}
	
	void operator -= (const vec3& v) {
		x-=v.x;y-=v.y;z-=v.z;
	}
	void operator += (const vec3& v) {
		x+=v.x;y+=v.y;z+=v.z;
	}
	bool operator == (const vec3& v) const {
		return x==v.x && y==v.y && z==v.z;
	}

	vec3 operator-() const {
		return vec3(-x,-y,-z);
	}

	vec3 operator+() const {
		return vec3(-x,-y,-z);
	}
	float Dot(vec3 v) const {
		return (x*v.x+ y*v.y+ z*v.z);
	}

	vec3 Cross(vec3 v) const {
		return vec3(y*v.z - z*v.y,
						z*v.x  - x*v.z,
						x*v.y  - y*v.x);
	}
	void zero() {
		x = 0; y=0; z=0;
	}
	void unity() {
		x = 1; y=1; z=1;
	}
};

#endif
