// Copyright (c) 2012 AcnodLabs Inc

/* 
   ALGE SDK Demo :: CoverFlow
   IMPORTANT NOTICE :: Images hold Copyrights of aivault.com and Liscenced for ALGE SDK Commercial Liscence Holders only
   (means Dont Copy and Use content in any of your Freebie or Commercial venture)
*/

#include "../../Base/CBaseV1_2.h"

class CCoverFlowItem {
	
	EaseInOutTweeningVariable yTilt;
	EaseInOutTweeningVariable z;

	float xPos1, yTilt1, z1;
	CAnimator can;

public:
	short modelId;
	float lastT;
	bool visible;
	EaseInOutTweeningVariable xPos;

	void Update(float t) {
		float dt = 0.02f;
		xPos.Step(dt);
		yTilt.Step(dt);
		z.Step(dt);
		lastT = t;
	}

	void setXPos(float x) {	xPos.StartFromCurrent();xPos.to = x;}
	float getXPos() {	return xPos.current;}
	void setYTilt(float th) {	yTilt.StartFromCurrent();yTilt.to = th;}
	float getYTilt() {	return yTilt.current;}
	void setZ(float z1) {	z.StartFromCurrent();z.to = z1;}
	float getZ() {	return z.current;}
	
	CCoverFlowItem() {
		modelId = 0;
		Reset();
		visible = true;
	}

	void SaveParams() {
		xPos1 = xPos.to;
		yTilt1 = yTilt.to;
		z1 = z.to;
	}

	void RestoreParams() {
		xPos.to = xPos1;
		yTilt.to = yTilt1;
		z.to = z1;
		xPos.StartFromCurrent();
		yTilt.StartFromCurrent();
		z.StartFromCurrent();
	}


	void Reset() {	
		yTilt.Reset();
		z.Reset();
		xPos.Reset();
	}

};

class CCoverFlowController {
public:
	CCoverFlowItem item[nITEMS];
	short currentId;
	float xSpan;
	int farZdist;
	int nearZdist;
	float xSlot[9];
	float xSlotSpacing;
	float OriginX;
	float OriginY;
	
	CCoverFlowController() {
		Setup(15,5,8);
		OriginX = 0;
		OriginY = 0;
	}

	void SetOrigin(float x, float y) {
		OriginX = x;
		OriginY = y;
	}

	void Setup(float farZ, float nearZ, float spanX) {
		farZdist = farZ;
		nearZdist = nearZ;
		SetSpan(spanX);
		Select(0);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);					// Set The Blending Function For Translucency
	}
	
	void ResetAll() {
		for (int i=0; i<nITEMS; i++) item[i].Reset();
	}

	bool isAnimating() {
		if (item[currentId].xPos.r<1) return true; else return false;
	}

	void SetSpan(float xSpan1) {
		xSpan = xSpan1;
		xSlotSpacing = xSpan/6.0f;
		for (int i=0; i<4; i++) {
			xSlot[i] = (-xSpan) + i *  xSlotSpacing;
		}
		for (int i=8; i>4; i--) {
			xSlot[i] = (xSpan) + (i-8) *  xSlotSpacing;
		}
		xSlot[4] = 0;
	}

	bool folded;

	void Fold() {
		if (!folded) {
		for (int i=0; i<nITEMS; i++) {
			float check = item[i].getXPos();
			item[i].SaveParams();
			item[i].setXPos(OriginX);
			item[i].setZ(item[i].getZ()*2);
		}
		}
		folded = true;
	}

	void UnFold() {
		if (folded) {
		for (int i=0; i<nITEMS; i++) {
			item[i].RestoreParams();
			item[i].setZ(item[i].getZ()/2);
		}
		}
		folded = false;
	}

	void Select(int curr) {
		ResetAll();
		currentId = curr;
		for (int i=0; i<currentId; i++) {item[i].setYTilt(+65);item[i].setZ(-farZdist);}
		for (int i=curr+1; i<nITEMS; i++) {item[i].setYTilt(-65);item[i].setZ(-farZdist);}	
				int ii = 0;
		
		int nL = curr;
		int nR = nITEMS - curr -1;
		
		int iSlot = 0;
		int min = curr -4;
		int max = curr +4;

		for (int i=0; i<nITEMS; i++) 
		{	
			item[i].setXPos(xSpan*999);//Init Everytihng Out of sight
			item[i].visible = false;
		}

		for (int i=-4; i<=4; i++) {
			int idx = curr+i;
			

			if (idx>=min && idx<=max) {//Limit to 4 Slots
				if (idx>=0 && idx<nITEMS) {//Boundz check
					item[idx].setXPos( xSlot[iSlot] );	
					item[idx].setZ(-farZdist-xSlot[iSlot]/100.0f);
					item[idx].visible = true;
				}
			} 
			iSlot++;
		}

		item[curr].setYTilt(0);item[curr].setZ(-nearZdist);item[curr].setXPos(0);
	}

	void Update(float t) {
		for (int i=0; i<nITEMS; i++) {
			item[i].Update(t);
		}
	}

	void inline drawSingleItem(CResourceManager* rm, int i) {
			if (!item[i].visible) return;
			glLoadIdentity();
			glTranslatef(item[i].getXPos(),0,item[i].getZ());
			glRotatef(item[i].getYTilt(),0,1,0);
			glColor4f(1,1,1,1);
			rm->models[item[i].modelId]->glDraw();
			float modelHeight = rm->models[item[i].modelId]->boundz();
			glTranslatef(0,-modelHeight*2,0);
			glRotatef(180,1,0,0);
			glColor4f(0.15,0.15,0.15,1);
			rm->models[item[i].modelId]->glDraw();
	}

	void glDraw(CResourceManager* rm) {
		glPushMatrix();
		for (int i=0; i<currentId; i++) {
			drawSingleItem(rm,i);
		}
		for (int i=nITEMS-1; i>=currentId; i--) {
			drawSingleItem(rm,i);
		}
		glPushMatrix();
	}

	void Next() {
		currentId++;
		if (currentId>(nITEMS-1)) currentId=(nITEMS-1);
		Select(currentId);
	}

	void Prev() {
		currentId--;
		if (currentId<0) currentId=0;
		Select(currentId);
		
	}

};

class /*DemoCoverFlow*/ App { 

	CResourceManager rm;
	CControls controls;
	CCoverFlowController cfc;

	GLfloat	yrot;
	GLfloat	xrot;
	
	GLfloat	z;	
    
    CHotSpot hsSet;

public:
	PEG output;
	PEG input;

    char szMsg[128];
    int screen[2];
    
	void processInput() {
		PEG::CMD* p = input.pull();
		switch (p->command) {
            case CMD_SCREENSIZE:
                screen[0] = p->i1;
                screen[1] = p->i2;
                CHotSpot::Res(screen[0], screen[1]);
                break;
			case CMD_KEYDOWN:
				if (p->i1==21) {cfc.Fold();}
				if (p->i1==36) {cfc.UnFold();}
				break;
			case CMD_TOUCH_END:
					{
						touchdown = false;
					}
			break;

			case CMD_TOUCH_START:
				{
					if (p->i2<64) touchdown = true; 
				}
				break;
			
			case CMD_TOUCHMOVE:
				{
					if (!cfc.isAnimating()) {
						switch (Gesture(p->i1,p->i2)) {
						case 'L': {cfc.Next();break;}
						case 'R': {cfc.Prev();break;}
					}
					}
				}
				break;
		}
	}

	float zed;
	bool touchdown;

	void Render(float tick, int aX, int aY, int aZ) {
		glColor4f(1,1,1,1);
		processInput();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		glLoadIdentity();
		cfc.Update(tick);// Animation needs time
		cfc.glDraw(&rm);
		glLoadIdentity();
		if (touchdown) glColor4f(0.6,0.6,0.6,1); else glColor4f(1,1,1,1);
		if (!cfc.isAnimating() && cfc.currentId>0) {
		 	hudBegin(screen);
				glTranslatef(0,screen[1]/2-32,0);
				rm.models[nITEMS+1]->glDraw();
			hudEnd();
		}
	}


	void Init(char* path) {
		
	//	cfc.Test11();

		alInit(STANDARD_WITH_TEXTURES);	
		zed = 0;
		yrot=0;
		xrot=0;
		z=-3.5f;		
		rm.Init(path);

		char img[32];

		for (int i=0; i<=21; i++) {
			sprintf(img, "image%03d.tga", i+1);
			rm.loadAlxModel("animposter.alx", img, i, 1);
			cfc.item[i].modelId = i;
		}

		rm.loadAlxModel("apply.alx", 0, nITEMS+1, 0.75);
		
	  	hsSet.Set(320,480,0,22,64,(32+52));

	}

	void Deinit() {
	}


};



