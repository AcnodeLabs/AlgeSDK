// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: MotoX3
*/

class /*MotoX3*/ App : public AlgeApp {
	
	GameObject Screen0, sel_lvl, start0;

public:
	
	virtual void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (Screen0.wasTouched()) { Screen0.HideFor(&sel_lvl);}
        if (sel_lvl.wasTouched()) { sel_lvl.HideFor(&start0); PlaySnd("motorbike.wav");}
	}
	/
	//Play Original https://bit.ly/2yKoV23
	virtual void Init(char* path) {
		alInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		AddResource(&Screen0, "Screen0");
        AddResource(&sel_lvl, "sel-lvl");
        AddResource(&start0, "start0");
        sel_lvl.Hide(); start0.Hide();
        PlaySnd("race-track.wav");
	}

    virtual i2 getBackgroundSize() {
        return i2(512,512);
    }
};
