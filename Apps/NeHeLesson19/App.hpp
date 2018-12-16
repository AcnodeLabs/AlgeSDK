// Copyright (c) 2012 AcnodLabs Inc

/*
ALGE SDK Demo :: NeHeLesson19 - Particles
*/

#include <math.h>

#define	MAX_PARTICLES	400		// Number Of Particles To Create ( NEW )

typedef struct						// Create A Structure For Particle
{
	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	x;						// X Position
	float	y;						// Y Position
	float	z;						// Z Position
	float	xi;						// X Direction
	float	yi;						// Y Direction
	float	zi;						// Z Direction
	float	xg;						// X Gravity
	float	yg;						// Y Gravity
	float	zg;						// Z Gravity
}
parti;							// Particles Structure

parti particle[MAX_PARTICLES];	// Particle Array (Room For Particle Info)

static GLfloat colors[12][3]=		// Rainbow Of Colors
{
	{1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
	{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
	{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};


class /*NeheLesson19*/ App  : public AlgeApp {

public:
	CControls controls;
	aL10 AL10;

	short rainbow;				// Rainbow Mode?
	float	slowdown;				// Slow Down Particles
	float	xspeed;						// Base X Speed (To Allow Keyboard Direction Of Tail)
	float	yspeed;						// Base Y Speed (To Allow Keyboard Direction Of Tail)
	float	zoom;				// Used To Zoom Out

	GLuint	loop;						// Misc Loop Variable
	GLuint	col;
	float points[45][45][3];    // The Array For The Points On The Grid Of Our "Wave"

	//////ALGE FUNCS
	void processInput() {
		PEG::CMD* p = input.pull();
		int command = p->command;
		void* p1 = input.pulled_param1;
		void* p2 = input.pulled_param2;

		if (command==CMD_TOUCH_START)

			{
				int x = input.pulled_i1;
				int y = input.pulled_i2;
				int K = controls.KROSS_(true, x, y);
				switch (K) {
				case CMD_END:
					output.pushP(CMD_END,0,0);
					break;
				case KROSS_UP:
					for (loop=0;loop<MAX_PARTICLES;loop++) particle[loop].yg-=1.9f;
					break;
				case KROSS_DOWN:
					for (loop=0;loop<MAX_PARTICLES;loop++) particle[loop].yg+=1.9f;
					break;
				case KROSS_RIGHT:
					for (loop=0;loop<MAX_PARTICLES;loop++) particle[loop].xg-=1.9f;
					break;
				case KROSS_LEFT:
					for (loop=0;loop<MAX_PARTICLES;loop++) particle[loop].xg+=1.9f;
					break;
				case KROSS_CENTER:
					for (loop=0;loop<MAX_PARTICLES;loop++)				// Initials All The Textures
					{

    					particle[loop].x=0.0f;								// Center On X Axis
						particle[loop].y=0.0f;								// Center On Y Axis
						particle[loop].z=0.0f;								// Center On Z Axis
						particle[loop].xi=float((rand()%50)-26.0f)*10.0f;	// Random Speed On X Axis
						particle[loop].yi=float((rand()%50)-25.0f)*10.0f;	// Random Speed On Y Axis
						particle[loop].zi=float((rand()%50)-25.0f)*10.0f;	// Random Speed On Z Axis
					}
						output.pushP(CMD_SNDPLAY0, (char*) "explosion.wav", 0);
					break;


				}


		}

	};

	void InitParticles() {

		rm.loadAlxModel((char*) "star.alx", AUTO, 0, 0.5);

		for (loop=0;loop<MAX_PARTICLES;loop++)				// Initials All The Textures
		{
			particle[loop].active=true;								// Make All The Particles Active
			particle[loop].life=1.0f;								// Give All The Particles Full Life
			particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Speed
			particle[loop].r=colors[loop*(12/MAX_PARTICLES)][0];	// Select Red Rainbow Color
			particle[loop].g=colors[loop*(12/MAX_PARTICLES)][1];	// Select Red Rainbow Color
			particle[loop].b=colors[loop*(12/MAX_PARTICLES)][2];	// Select Red Rainbow Color
			particle[loop].xi=float((rand()%50)-26.0f)*10.0f;		// Random Speed On X Axis
			particle[loop].yi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Y Axis
			particle[loop].zi=float((rand()%50)-25.0f)*10.0f;		// Random Speed On Z Axis
			particle[loop].xg=0.0f;									// Set Horizontal Pull To Zero
			particle[loop].yg=-0.8f;								// Set Vertical Pull Downward
			particle[loop].zg=0.0f;									// Set Pull On Z Axis To Zero
		}

	}

	void Init(char* path) {
		SetTitle(path);
		glEnable(GL_TEXTURE_2D);
	//	output.pushP(CMD_TITLE, $ "Lesson 19 Alge Port", 0);

		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f,0.0f,0.0f,0.0f);					// Black Background
		glDisable(GL_DEPTH_TEST);							// Disable Depth Testing
		glEnable(GL_BLEND);									// Enable Blending
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Type Of Blending To Perform
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
		glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping

		slowdown = 2.0f;
		zoom =-20.0f;

		rm.Init(path);

		InitParticles();

		output.pushP(CMD_SNDSET0, (char*) "explosion.wav", 0);

	};

	void Deinit() {
	};

	void Render(float dt, int ax, int ay, int az) {

		processInput();
		glLoadIdentity();										// Reset The ModelView Matrix

		glClear(GL_COLOR_BUFFER_BIT);


		for (loop=0;loop<MAX_PARTICLES;loop++)					// Loop Through All The Particles
		{

			if (particle[loop].active)							// If The Particle Is Active
			{
				float x=particle[loop].x;						// Grab Our Particle X Position
				float y=particle[loop].y;						// Grab Our Particle Y Position
				float z=particle[loop].z+zoom;					// Particle Z Pos + Zoom

				glLoadIdentity();

				glTranslatef(x,y,zoom);

				// Draw The Particle Using Our RGB Values, Fade The Particle Based On It's Life
				glColor4f(particle[loop].r,particle[loop].g,particle[loop].b,particle[loop].life);

				rm.models[0]->glDraw();

				//glBegin(GL_TRIANGLE_STRIP);						// Build Quad From A Triangle Strip
				//glTexCoord2d(1,1); glVertex3f(x+0.5f,y+0.5f,z); // Top Right
				//glTexCoord2d(0,1); glVertex3f(x-0.5f,y+0.5f,z); // Top Left
				//glTexCoord2d(1,0); glVertex3f(x+0.5f,y-0.5f,z); // Bottom Right
				//glTexCoord2d(0,0); glVertex3f(x-0.5f,y-0.5f,z); // Bottom Left
				//glEnd();										// Done Building Triangle Strip

				particle[loop].x+=particle[loop].xi/(slowdown*1000);// Move On The X Axis By X Speed
				particle[loop].y+=particle[loop].yi/(slowdown*1000);// Move On The Y Axis By Y Speed
				particle[loop].z+=particle[loop].zi/(slowdown*1000);// Move On The Z Axis By Z Speed

				particle[loop].xi+=particle[loop].xg;			// Take Pull On X Axis Into Account
				particle[loop].yi+=particle[loop].yg;			// Take Pull On Y Axis Into Account
				particle[loop].zi+=particle[loop].zg;			// Take Pull On Z Axis Into Account
				particle[loop].life-=particle[loop].fade;		// Reduce Particles Life By 'Fade'

				if (particle[loop].life<0.0f)					// If Particle Is Burned Out
				{
					particle[loop].life=1.0f;					// Give It New Life
					particle[loop].fade=float(rand()%100)/1000.0f+0.003f;	// Random Fade Value
					particle[loop].x=0.0f;						// Center On X Axis
					particle[loop].y=0.0f;						// Center On Y Axis
					particle[loop].z=0.0f;						// Center On Z Axis
					particle[loop].xi=xspeed+float((rand()%60)-32.0f);	// X Axis Speed And Direction
					particle[loop].yi=yspeed+float((rand()%60)-30.0f);	// Y Axis Speed And Direction
					particle[loop].zi=float((rand()%60)-30.0f);	// Z Axis Speed And Direction
					particle[loop].r=colors[col][0];			// Select Red From Color Table
					particle[loop].g=colors[col][1];			// Select Green From Color Table
					particle[loop].b=colors[col][2];			// Select Blue From Color Table
				}


			}
		}

	};
};
