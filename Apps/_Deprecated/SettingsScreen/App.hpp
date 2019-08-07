// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
   The Assets Folder Name is PoppingTime.Assets,
   macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
*/
#include  "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"

// Scrum Page https://scrumy.com/PoppingTime
class Colorify : public f3 {
	int xdir, ydir, zdir;
	float speed = 1.0;
public:
	Colorify() {
		f3(rndm(0,1), rndm(0, 1), rndm(0, 1));
	}
	void Update(float deltaT) {
		x +=  xdir * deltaT * speed;
		y +=  ydir * deltaT * speed; 
		z +=  zdir * deltaT * speed;
		if (x > .9) xdir = -1;
		if (y > .8) ydir = -1;
		if (z > .7) zdir = -1;
		if (x < .6) xdir = 1;
		if (y < .5) ydir = 1;
		if (z < .4) zdir = 1;
	}
};

class App : public AlgeApp {
	GameObject bg;
    SettingScreen settings;
		
public:
	
	//virtual i2 getBackgroundSize() { return size_ipad_air; }
	virtual void Init(char* path) {
		AlInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		
		with AddResource(&bg, "sbg", 1.0);
			settings.LoadIn(this,&_, false);
            settings.SetVisible(true);
		_with

		glClearColor(COLOR_CORNFLOWERBLUE);
       
	}

	string ret;

	virtual void processInput(PEG::CMD* cmd, float deltaT) {
		settings.processInput(cmd->command, i2(cmd->i1, cmd->i2));
	}
	virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
		if (gob->is(bg)) bg.color = (settings.hidden ? f3(1, 1, 1): f3(0.6, 0.6, 0.6));
	}
};

