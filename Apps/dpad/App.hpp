// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: MotoX3
*/
#include "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"


class /*D-Pad*/ App : public AlgeApp {
	
	GameObject Screen0, sel_lvl, start0;
	DPad dpad;

public:


	virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
		if (Screen0.wasTouched()) { Screen0.HideFor(&sel_lvl); }
		if (sel_lvl.wasTouched()) {
			sel_lvl.HideFor(&start0);
			PlaySnd("motorbike.wav");
			dpad.Show();
		}
		if (gob->is(dpad)) dpad.Update(deltaT);
	}

	//Play Original https://bit.ly/2yKoV23
	virtual void Init(char* path) {
		AlInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		AddResource(&Screen0, "screen0", "screen0");
		AddResource(&sel_lvl, "sel-lvl", "sel-lvl");
		AddResource(&start0, "start0", "start0");

		with dpad.LoadIn(this);
			_.Hide();
		_with


		sel_lvl.Hide(); start0.Hide();
		// PlaySnd("race-track.wav");
	}

	virtual i2 getBackgroundSize() {
		return i2(512, 512);
	}
};

