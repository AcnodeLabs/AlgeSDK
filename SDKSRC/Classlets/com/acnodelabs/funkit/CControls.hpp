#include "../../../../Base/CCommands.h"
class CControls {
public:
	
	float X;
	float Y;
	float Z;
	float t;
	
	float MY_PI;
	int screen[2];
	
	CControls() {
		t = 0.1;
		MY_PI = 22.0f/ 7.0f;
		screen[0] = 320;
		screen[1] = 480;
	}
	
	float Roll() {
		return atan2( sqrt(X*X + Z*Z), Y) * 180/MY_PI;
	}
	
	float Pitch() {
		return (-1.0f * (atan2( sqrt(Y*Y + X*X), Z) * 180/MY_PI - 90));
	}
	
	void RealWorldOrientation(float ax100, float ay100, float az100){
		Accel(ax100,ay100,az100);
#ifndef NOGL
#ifndef NTDDI_WIN8
		glRotatef (Roll(), 0.0f, 0.0f, 1.0f);
		glRotatef (Pitch(),  1.0f, 0.0f, 0.0f);
#endif
#endif
	}
	
	void Accel(float ax100, float ay100, float az100) {
		X = ax100/ 100.0f;
		Y = ay100/ 100.0f;
		Z = az100/ 100.0f;
	}
	
	//				 +UP
	//				 +
	//		LEFT+++++++++++++RT
	//				 +
	//				 +DOWN
	
    string toStr(short in) {
        if (in==KROSS_UP) return "KROSS_UP";
         if (in==KROSS_DOWN) return "KROSS_DOWN";
         if (in==KROSS_LEFT) return "KROSS_LEFT";
         if (in==KROSS_RIGHT) return "KROSS_RIGHT";
        if (in==KROSS_CENTER) return "KROSS_CENTER";
        return string("--");
    }

	char toChar(short in) {
		if (in == KROSS_UP) return 'U';
		if (in == KROSS_DOWN) return 'D';
		if (in == KROSS_LEFT) return 'L';
		if (in == KROSS_RIGHT) return 'R';
		if (in == KROSS_CENTER) return 'C';
		return char(' ');
	}


    
	short KROSS_(bool portrait, int touched_x, int touched_y) {
		
		static short trace[3];
		
		bool landscape = !portrait;
		bool K_UP;
		bool K_DOWN; 
		bool K_LEFT;
		bool K_RIGHT;
		
		short y = touched_y;
		short x = touched_x;
		
		if  (portrait) { 
			K_UP = (y < screen[1] * 1 / 4);
			K_DOWN = (y > screen[1] * 3 / 4);
			K_RIGHT = (x > screen[0] * 3 / 4);
			K_LEFT = (x < screen[0] * 1 / 4);
		}
		
		if  (landscape) { 
			K_UP = (y < screen[1] * 1 / 4);
			K_DOWN = (y > screen[1] * 3/ 4);
			K_RIGHT = (x > screen[0] * 3/4) ;
			K_LEFT = (x < screen[0] * 1/4);
		}
		
		short kk=0;
		if (K_UP) kk= KROSS_UP;
		if (K_DOWN) kk= KROSS_DOWN;
		if (K_LEFT) kk= KROSS_LEFT;
		if (K_RIGHT) kk= KROSS_RIGHT;

		trace[0] = trace[1];
		trace[1] = trace[2];
		trace[2] = kk;
		
		if (trace[0]==KROSS_LEFT && trace[1]==KROSS_RIGHT && trace[2]==KROSS_CENTER) kk = (short) CMD_END;
				
		if (kk==0) kk = KROSS_CENTER;
		return kk;
	}
	
};
