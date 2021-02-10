// Copyright (c) 2012 AcnodLabs Inc

/* 
ALGE SDK Demo :: NeHeLesson09 - Twinkling Stars
*/

#include "../../Base/CBaseV1_2.h"

class /*NeHeLesson09*/ App { 
public:
	CResourceManager rm;

	GLfloat	xrot;	
	GLfloat	yrot;	
	GLfloat xspeed;	
	GLfloat yspeed;	
	GLfloat	z;		

	short light;
	short blend;
	short twinkle;

	int num;

	typedef struct	
	{
		int r, g, b;	
		GLfloat dist,
			angle;
	}
	stars;
	stars star[50];	

	GLfloat	zoom;
	GLfloat tilt;
	GLfloat	spin;

	short	loop;
	TextureImage texture[1];

	GLfloat LightAmbient[4];
	GLfloat LightDiffuse[4];
	GLfloat LightPosition[4];

public:
	PEG output;
	PEG input;
	aL10 AL10;
	char szP1[128];

	void processInput() {
		PEG::CMD* p = input.pull();
		switch (p->command) {
			case CMD_KEYDOWN:
				{
					switch (p->i1) {

			case AL_KEY_UP:   {xspeed-=0.1f;break;}
			case AL_KEY_DOWN: {xspeed+=0.1f;break;}
			case AL_KEY_LEFT: {yspeed-=0.1f;break;}
			case AL_KEY_RIGHT:{yspeed+=0.1f;break;}
			case AL_KEY_ALPHA + ('L'-'A') :
				{
					light=!light; 
					if (!light) glDisable(GL_LIGHTING);
					else glEnable(GL_LIGHTING);

					break;
				}
			case AL_KEY_ALPHA + ('B'-'A') :
				{
					blend=!blend; 
					if (!blend) {glDisable(GL_BLEND);glEnable(GL_DEPTH_TEST);}
					else {glEnable(GL_BLEND);glDisable(GL_DEPTH_TEST);}

					break;
				}
			case AL_KEY_ALPHA + ('T'-'A') :
				{
					twinkle=!twinkle; 
					break;
				}
			default:


				break;
					}

				}
				break;
		}
	}


	void Render(float dt, int aX, int aY, int aZ) {

		processInput();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
		glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Select Our Texture

		for (loop=0; loop<num; loop++)						// Loop Through All The Stars
		{
			glLoadIdentity();								// Reset The View Before We Draw Each Star
			glTranslatef(0.0f,0.0f,zoom);					// Zoom Into The Screen (Using The Value In 'zoom')
			glRotatef(tilt,1.0f,0.0f,0.0f);					// Tilt The View (Using The Value In 'tilt')
			glRotatef(star[loop].angle,0.0f,1.0f,0.0f);		// Rotate To The Current Stars Angle
			glTranslatef(star[loop].dist,0.0f,0.0f);		// Move Forward On The X Plane
			glRotatef(-star[loop].angle,0.0f,1.0f,0.0f);	// Cancel The Current Stars Angle
			glRotatef(-tilt,1.0f,0.0f,0.0f);				// Cancel The Screen Tilt

			if (twinkle)
			{
				glColor4ub(star[(num-loop)-1].r,star[(num-loop)-1].g,star[(num-loop)-1].b,255);
				rm.models[0]->glDraw();
			}

			glRotatef(spin,0.0f,0.0f,1.0f);
			glColor4ub(star[loop].r,star[loop].g,star[loop].b,255);

			rm.models[0]->glDraw();

			spin+=0.01f;
			star[loop].angle+=float(loop)/num;
			star[loop].dist-=0.01f;
			if (star[loop].dist<0.0f)
			{
				star[loop].dist+=5.0f;
				star[loop].r=rand()%256;
				star[loop].g=rand()%256;
				star[loop].b=rand()%256;
			}
		}
	}

	void Init(char* path) {
		glEnable(GL_TEXTURE_2D);
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		glEnable(GL_BLEND);

		for (loop=0; loop<num; loop++)
		{
			star[loop].angle=0.0f;
			star[loop].dist=(float(loop)/num)*5.0f;
			star[loop].r=rand()%256;
			star[loop].g=rand()%256;
			star[loop].b=rand()%256;
		}

		output.pushP(CMD_TITLE, $ "Alge Nehe Lesson09",0);
		xrot=0;
		yrot=0;
		z=-6.0f;
		xspeed = 0;
		yspeed = 0;
		light = 0;
		blend = 0;
		num = 50;
		zoom=-20.0f;		// Distance Away From Stars
		tilt=90.0f;			// Tilt The View
		twinkle = 0;
		rm.Init(path);
		rm.loadAlxModel((char*) "star.alx",AUTO, 0, 1);

	}

	void Deinit() {
	}


};
