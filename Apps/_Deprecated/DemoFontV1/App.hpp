// Copyright (c) 2012 AcnodLabs Inc

/* 
   ALGE SDK Demo :: Font
*/

#include <time.h>

class /*DemoFont*/ App : public AlgeApp { 

	GLfloat	yrot;				 
	GLfloat	z;					 

	FontMap16x16 fonts;

public:
	char szP1[128];

	void Render(float dt, int aX, int aY, int aZ) {
		
		static time_t last_time, new_time;
		static int nframe = 0;
		static int framerate = 0;
		static char c= 'A';

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		glLoadIdentity();									// Reset The Current Modelview Matrix
		glTranslatef(-5.0f,0.0f,-c+30);
		glRotatef(90*sin(yrot),1,1,1);
		
		if (nframe>0) {
				sprintf(szP1, "[%c] FPS::%d", c, framerate);
				fonts.print(szP1);
				c++;
		}
		//Calc FPS
		if (nframe%100==0)
		{
			new_time=clock();
			int ticks = new_time - last_time;
			framerate=100 * CLOCKS_PER_SEC /ticks;
			last_time=new_time;

		}
		nframe++;		
		rm.models[0]->glDraw();
		
		if (c>'Z') c='A';
	}

	void Init(char* path) {
		memset(szP1, 0, sizeof(szP1));
		glClearColor(0.0f, 0.0f, 0.3f, 0.5f);				// Background Color
		glColor4f(1.0f, 0.0f, 1.0f, 0.5);					// Foreground Color

		yrot=0;
		z = 'A';
		
		rm.Init(path);
		rm.loadAlxModel((char*) "font.alx", AUTO, 0, 1);	// Fonts Loaded just like Model
		fonts.usetexof(rm.models[0]);						// Associate texure of Loaded Model to FontMap
	}

	void Deinit() {
	}
};
