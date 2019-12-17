// Copyright (c) 2019 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: LevelSelect
*/

class /*LevelSelector*/ App : public AlgeApp { 
	GameObject background;
public:

		virtual void Init(char* path) {

		AlInit(STANDARD);
		
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		AddResource(&background, "levelselect", "levelselect.jpg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN
		);
		
			//load hsdata dump
		#include "../LevelSelect.Assets/Data/levelselect.h"

		output.pushP(CMD_SNDSET0, $ "entry.wav", 0);

		}

		void levelSelected(int lvl) {
			sz = std::to_string(lvl) +"<< Level Selected!";
			SetTitle(sz.c_str());
			output.pushP(CMD_SNDPLAY0, $ "entry.wav", 0);
		}

    CControls c;
	CHotSpot hs[3][5];
	string sz;
	int sx; int sy;
	void processInput(PEG::CMD* p, float deltaT) { 
		
		short touchData = 0;

		if (p->command == CMD_SCREENSIZE) {
			c.screen[0] = p->i1 ;
			c.screen[1] = p->i2;
			CHotSpot::sx = p->i1;
			CHotSpot::sy = p->i2;
		}
		
		if (p->command == CMD_TOUCH_START) {
			sx = p->i1;
			sy = p->i2;
			//HITTEST
			for (int r = 0; r < 3; r++) for (int c = 0; c < 5; c++) {
				if (hs[r][c].HitX(sx, sy)) levelSelected(hs[r][c].id);
			}
		}

		if (p->command == CMD_TOUCH_END) {
			//CHotSpot::WriteCodeToLog(sx, sy, p->i1, p->i2);
		}

	}

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		//		if (gob->is(background)) //			glColor3f(0.8, 0.8, 0.8);//dim 80%
	}

};
