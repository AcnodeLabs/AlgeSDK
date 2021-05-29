// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 App :: Spiral
*/


class /*Juices*/ App : public AlgeApp { 
	
	GameObject objct;
	GameObject background;
	PosRotScale *sel;
	
	int currentJuice[2];

public:

    virtual void Init(char* path) {
		
		currentJuice[0] = 0;
		currentJuice[1] = 0;

		AlInit(STANDARD);
		SetTitle("24h Spiral");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		AddResource(&background, "background",
			"time_machine.jpg",
			XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN
		);
            AddResource(&objct, "spiral", "spiral.jpg", 1.5);
            sel = &objct;
	}

    string jn;
    CControls c;
    
	void processInput(PEG::CMD* p, float deltaT) { 

		short touchData = 0;

		if (p->command == CMD_SCREENSIZE) {
			c.screen[0] = p->i1;
			c.screen[1] = p->i2;
		}

		if (p->command == CMD_TOUCH_START) {
			touchData = (c.KROSS_(false, p->i1, p->i2));
            jn = "Touched " + c.toStr(touchData);
            
            if (onTouched(objct.getInstancePtr(0)->UUID)) {
                jn = "Touched LEFT" ;
            }
            if (onTouched(objct.getInstancePtr(1)->UUID)) {
                jn = "Touched RIGHT" ;
            }         
		}

		if (p->command == CMD_KEYDOWN || touchData) {

			if (p->i1 == AL_KEY_PLUS) {
				sel->JuiceSpeed *= 2;
				jn = "[x2] JuiceSpeed=" + std::to_string(sel->JuiceSpeed);
			}
			if (p->i1 == AL_KEY_MINUS || touchData == KROSS_DOWN) {
				sel->JuiceSpeed /= 2;
				jn = "[/2] JuiceSpeed=" + std::to_string(sel->JuiceSpeed);
			}

			if (p->i1 == AL_KEY_RIGHT || touchData == KROSS_RIGHT) {
			//	sel = objct.getInstancePtr(1);
			//	resetPosRotSpeed(1);
				jn = "SELECTED RIGHT";
			}
			if (p->i1 == AL_KEY_LEFT || touchData == KROSS_LEFT) {
			//	sel = objct.getInstancePtr(0);
			//	resetPosRotSpeed(0);
				jn = "SELECTED LEFT";
			}
			if (p->i1 == AL_KEY_UP || touchData == KROSS_UP) {
				sel->JuiceType++;
				if (sel->JuiceType == JuiceTypes::JUICE_SCALE_IN) sel->scale = 0.1;
				if (sel->JuiceType >= JuiceTypes::JUICES_CANCEL) {
					sel->JuiceType = 0;
					//resetPosRotSpeed(sel);
				}
				jn = sel->UUID + ":" + JuiceName(sel->JuiceType);
			}
			if (p->i1 == AL_KEY_DOWN || touchData == KROSS_DOWN) {
				sel->JuiceType--;
				if (sel->JuiceType == JuiceTypes::JUICE_SCALE_IN) sel->scale = 0.1;
				if (sel->JuiceType < 0) {
					sel->JuiceType = 0;
					//resetPosRotSpeed(sel);
				}
			}
			output.pushP(CMD_TITLE, $ jn.c_str(), 0);
			output.pushP(CMD_TOAST, $ jn.c_str(), 0);
		}

	}

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		if (gob->is(background)) 
			glColor3f(0.8, 0.8, 0.8);//dim 80%
	}

};
