// Copyright (c) 2012 AcnodLabs Inc

/* 
ALGE SDK Demo :: NeHeLesson05 (coolness added)
*/

#include "../../Base/CBaseV1_2.h"

class /*NeHeLesson05*/ App { 

	float rot;

public:
    CResourceManager rm;
    
	PEG output;
	PEG input;
	aL10 AL10;

	float t0;

	void Render(float dt, int aX, int aY, int aZ) {
		t0+=dt;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		glLoadIdentity();									// Reset The Current Modelview Matrix
		glTranslatef(0.0f,0.0f,-6.0f + (2.0f * sin(t0)));	
		glRotatef(rot,0.0f,1.0f,0.0f);						

		AL10.Capture(GL_TRIANGLES);							// Start Drawing A Triangle
		AL10.glColor3f(1.0f,0.0f,0.0f);						// Red
		AL10.glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Front)
		AL10.glColor3f(0.0f,1.0f,0.0f);						// Green
		AL10.glVertex3f(-1.0f,-1.0f, 1.0f);					// Left Of Triangle (Front)
		AL10.glColor3f(0.0f,0.0f,1.0f);						// Blue
		AL10.glVertex3f( 1.0f,-1.0f, 1.0f);					// Right Of Triangle (Front)
		AL10.glColor3f(1.0f,0.0f,0.0f);						// Red
		AL10.glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Right)
		AL10.glColor3f(0.0f,0.0f,1.0f);						// Blue
		AL10.glVertex3f( 1.0f,-1.0f, 1.0f);					// Left Of Triangle (Right)
		AL10.glColor3f(0.0f,1.0f,0.0f);						// Green
		AL10.glVertex3f( 1.0f,-1.0f, -1.0f);				// Right Of Triangle (Right)
		AL10.glColor3f(1.0f,0.0f,0.0f);						// Red
		AL10.glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Back)
		AL10.glColor3f(0.0f,1.0f,0.0f);						// Green
		AL10.glVertex3f( 1.0f,-1.0f, -1.0f);				// Left Of Triangle (Back)
		AL10.glColor3f(0.0f,0.0f,1.0f);						// Blue
		AL10.glVertex3f(-1.0f,-1.0f, -1.0f);				// Right Of Triangle (Back)
		AL10.glColor3f(1.0f,0.0f,0.0f);						// Red
		AL10.glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Left)
		AL10.glColor3f(0.0f,0.0f,1.0f);						// Blue
		AL10.glVertex3f(-1.0f,-1.0f,-1.0f);					// Left Of Triangle (Left)
		AL10.glColor3f(0.0f,1.0f,0.0f);						// Green
		AL10.glVertex3f(-1.0f,-1.0f, 1.0f);					// Right Of Triangle (Left)
		AL10.Flush(0, false, true, false);	

		rot+=0.8f;											
	}

	void Init(char* path) {
		alInit(STANDARD);
		output.pushP(CMD_TITLE, $ "Alge Nehe Lesson05",0);
		rot = 0;
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		t0= 0;
		glClearColor(COLOR_CORNFLOWERBLUE);
	}

	void Deinit() {
	}

};
