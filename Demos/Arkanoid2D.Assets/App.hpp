// Copyright (c) 2012 AcnodLabs Inc

/* 
   ALGE SDK Demo :: 2D
*/

#include "../../Base/CBaseV1_2.h"

/* 
   ALGE SDK Demo :: 2D
   Demonstrates Use of Orthographic Helper Functions HudBegin and HudEnd
*/

enum { 
	MDL_POSTER 
};

class App { 
public:
	CResourceManager rm;
	

	PEG output;
	PEG input;

    int screen[2];
    
	void processInput() {
		PEG::CMD* p = input.pull();
		switch (p->command) {
            case CMD_SCREENSIZE:
                //Store Screen Size
                screen[0] = p->i1;
                screen[1] = p->i2;				
                break;
            }
	}

	void Render(float tick, int aX, int aY, int aZ) {
		processInput();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		
        hudBegin(screen);
		 rm.models[MDL_POSTER]->glDraw();
        hudEnd();
	}

	void Init(char* path) {
		alInit(STANDARD_WITH_TEXTURES);	
		rm.Init(path);
		rm.loadAlxModel((char*) "animposter.alx",(char*) "animposter.tga", MDL_POSTER, 160);
	}

	void Deinit() {
	}


};
