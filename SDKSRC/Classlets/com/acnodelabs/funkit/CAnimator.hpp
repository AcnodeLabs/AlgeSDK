#ifndef CANIMATOR_CPP
#define CANIMATOR_CPP

#define nITEMS 10

#include "CVec.hpp"

class CAnimator {
public:
	float* curr;

	float desired[3];
	float d[3];
	float v[3];

	bool active;

	CAnimator() {
	
	}

	float LinearTween(float t, float start, float end) {
        if (t>=1) return end;
		return t*end+(1-t)*start;
	}
	float QuadraticEaseIn(float t, float start, float end) { return LinearTween(t*t,start,end);}

	vec3 LinearTween(float t, vec3 start, vec3 end) {
		vec3 r;
		r.x = LinearTween(t, start.x, end.x);
		r.y = LinearTween(t, start.y,end.y);
        r.z = LinearTween(t, start.z,end.z);
		return r;
	}

	vec3 QuadraticEaseInOut(float t, vec3 start, vec3 end) {
		vec3 r;
		r.x = QuadraticEaseInOut(t, start.x, end.x);
		r.y = QuadraticEaseInOut(t, start.y,end.y);
        r.z = QuadraticEaseInOut(t, start.z,end.z);
        return r;
	}

	float QuadraticEaseInOut(float t, float start, float end) {
		float middle=(start+end)/2;
		t=2*t;
		if(t<=1) return LinearTween(t*t,start,middle);
		t-=1;
		return LinearTween(t*t,middle,end);
	}


	void test() {
		
		
		float curre[3];

		curre[0] = 0;
		curre[1] = 0;
		curre[2] = 0;

		desired[0] = 0.002;
		desired[1] = 3.2;
		desired[2] = -4.9;

		Reset(&curre[0], &desired[0],1 );
		
		for (int l=0; l<1; l++)
			Step(0.1);

	}

	float speed;

	static float Sqr(float x) {return x*x;}

	static float Dist(float* current, float* desired) {
		return (float) sqrt(Sqr(desired[0]-current[0])  + Sqr(desired[1]-current[1]) + Sqr(desired[2]-current[2]) );
	}

	float tTotal, tRun;
	float startX, startY, startZ;

	void Reset(float *current, float* desirable, float speedA) {
	
		tTotal = Dist(current,desirable) / speedA;
	
		curr = current;
		speed = speedA;

		desired[0] = desirable[0];
		desired[1] = desirable[1];
		desired[2] = desirable[2];

		startX = current[0];
		startY = current[1];
        startZ = current[2];

		tRun = 0;

		active = true;
	}

	float r;

	void Step(float dt) {
		if (active) tRun += dt; else {tTotal = 0;return;}
		r = tRun / tTotal;
		curr[0] = LinearTween(r, startX, desired[0]);
		curr[1] = LinearTween(r, startY, desired[1]);
        curr[2] = LinearTween(r, startZ, desired[2]);
        if (r>=1) {
			active = false;
		}
	}

};


class LinearTweeningVariable {
protected:
	class CAnimator can;
public:
	float from;
	float to;
	float current;
	float r;

	void Reset() {
		r = 0;
	}

	void StartFromCurrent() {
		from = current;
		r = 0;
	}

	void func() {
		current = can.LinearTween(r, from, to);
	}

	float Step(float delta) {
		r+= delta;
		if (r>=1) r = 1;
		func();	
		return current;
	}

	LinearTweeningVariable() {
		r = 0;
	}
};

class EaseInOutTweeningVariable : public LinearTweeningVariable {
public:
	float func() {
		current = can.QuadraticEaseInOut(r,from,to);
        return current;
	}
};


class LinearTweeningVector {
public:
	LinearTweeningVariable X,Y;
	
	void Reset() {
		X.Reset();
		Y.Reset();
	}

	void StartFromCurrent() {
		X.StartFromCurrent();
		Y.StartFromCurrent();
	}

	vec2 From() {
		vec2 ret;
		ret.x = X.from;
		ret.y = Y.from;
		return ret;
	}

	void current(vec2 v) {
		X.current = v.x;
		Y.current = v.y;
	}

	void from(vec2 v) {
		X.from = v.x;
		Y.from = v.y;
	}

	void to(vec2 v) {
		X.to = v.x;
		Y.to = v.y;
	}

	vec2 To() {
		vec2 ret;
		ret.x = X.to;
		ret.y = Y.to;
		return ret;
	}

	vec2 Current() {
		vec2 ret;
		ret.x = X.current;
		ret.y = Y.current;
		return ret;
	}

	vec2 Step(float delta) {
		vec2 cur;
		cur.x = X.Step(delta);
		cur.y = Y.Step(delta);
		return cur;
	}

	LinearTweeningVector() {
		X.r = 0;
		Y.r = 0;
	}
};
#endif
