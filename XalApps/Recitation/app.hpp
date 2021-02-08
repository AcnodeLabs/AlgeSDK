// Copyright (c) 2012 AcnodLabs Inc

/* 
   ALGE SDK Demo :: CoverFlow
   IMPORTANT NOTICE :: Images hold Copyrights of aivault.com and Liscenced for ALGE SDK Commercial Liscence Holders only
   (means Dont Copy and Use content in any of your Freebie or Commercial venture)
*/
#include <cstdio>

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
	//	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);					// Set The Blending Function For Translucency
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

class CPushButton {
	bool touchdown;
	CRect _rect;
public:

	void Init(CResourceManager* rm, std::string resTag, int modelID, float scale, CRect rect) {
		rm->loadAlxModel((char*)(resTag + ".alx").c_str(), 0, modelID,scale);
		_rect = rect;
	}
	
	void onRender() {
		if (touchdown) glColor4f(0.6, 0.6, 0.6, 1); else glColor4f(1, 1, 1, 1);
	}

	void processInput(PEG::CMD* p) {
		switch (p->command) {
		case CMD_TOUCH_END:
		{
			touchdown = false;
		}
		break;

		case CMD_TOUCH_START:
		{
			if (_rect.PTInRect(p->i1,p->i2,_rect))
				touchdown = true;
		}
		break;
		}
	}
};


class /*DemoCoverFlow*/ App : public AlgeApp { 

	CControls controls;
	CCoverFlowController cfc;
	CPushButton btn;

    GameObject img[114];
    
	GLfloat	yrot;
	GLfloat	xrot;
	
	GLfloat	z;	
 
public:

    char szMsg[128];
    int screen[2];
    
	void processInput() {
		PEG::CMD* p = input.pull();
		switch (p->command) {
			case CMD_KEYDOWN:
				if (p->i1==-9) {cfc.Fold();}
				if (p->i1==-11) {cfc.UnFold();}
				if (p->i1 == -12) { cfc.Prev(); }
				if (p->i1 == -10) { cfc.Next(); }
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
		btn.processInput(p);
	}

	float zed;

    GameObject gui;
    
virtual void Init(char* path) {
            
            AlInit(STANDARD);
            SetTitle("XGui");
            
            AddDefaultCamera(Camera::CAM_MODE_2D,OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
                
                for (int i=9; i<10; i++) {
                    static char nn[12];
                    sprintf(nn,"%d", i);
                    AddResource(&img[i], "animposter",  nn, 256);
                }

                AddResource(&gui, "gui");
                gui.hidden = false;
                
                 
            }
        
        i2 msize;
        i2 mou;
        
        i2 getBackgroudSize() {
            return msize;
        }

        bool done = false;
        
        void processInput(PEG::CMD* p, float deltaT) {
            if (p->command == CMD_SCREENSIZE) {
                msize.x = p->i1;
                msize.y = p->i2;
            }
            
            
            if (p->command == CMD_YOUTUBE_SHOW) {
                if (!done) {
                    output.pushP(CMD_TOAST, $ p->param1, $ "hi");
                    done = true;
                }
            }

        }
        bool my_tool_active;
        float my_color[4];
       
     
        void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
            if (gob->is(gui) && !gui.hidden)
            {
                GuiStarts();
                    ImGui::ShowDemoWindow();
                GuiEnds();
            }

        }

	void Deinit() {
	}


};



