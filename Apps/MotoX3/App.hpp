// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: MotoX3
*/

class /*MotoX3*/ App : public AlgeApp {
	StartScreen ss;
	GameObject Screen0, sel_lvl, start0;

public:
	
	virtual void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (ss.bg.wasTouched()) { 
			ss.bg.HideFor(&sel_lvl);
		}
        if (sel_lvl.wasTouched()) { 
			sel_lvl.HideFor(&start0); PlaySnd("motorbike.wav");
		}
	}
	
	//Play Original https://bit.ly/2yKoV23
	virtual void Init(char* path) {
		AlInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		ss.LoadIn(this);
		AddResource(&sel_lvl, "sel-lvl",XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN)->hidden = true;
		AddResource(&start0, "start0", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN)->hidden = true;
        sel_lvl.Hide(); start0.Hide();
        PlaySnd("race-track.wav");
	}

};
