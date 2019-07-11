// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: ColorSwitch2D (Front Screen Only)
*/
CRect a;

class /*ColorSwitch2D*/ App : public AlgeApp {

	GameObjectSnd  screen0cs;
	GameObject stars[10];
	GameObject ring4color;
	GameObject starL, starR;
	GameObject gamemodesbanner;

public:

    inline void AddRings(App &object, GameObject &ring4color) {
        object.AddResource(&object.ring4color, "ring4color", 1);
        object.ring4color.applyTopLeftCorrectionWRTorigin = false;
        PosRotScale ringPrs;
        ringPrs.JuiceType = JuiceTypes::JUICE_ROTZ;

        int anchorRingsCenterPointY = 0.95* object.originY;
        ringPrs.pos = f3(object.originX,anchorRingsCenterPointY,0);
        ringPrs.scale = 0.995;
        ringPrs.JuiceSpeed = -75;
        object.ring4color.AddInstance(ringPrs);

        ringPrs.scale = 0.886;
        ringPrs.JuiceSpeed = 70;
        object.ring4color.AddInstance(ringPrs);

        ringPrs.scale = 0.786;
        ringPrs.JuiceSpeed = -85;
        object.ring4color.AddInstance(ringPrs);
    }

	virtual void Init(char* path) {
        rm.Init(path);
        AlInit(STANDARD);

	AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
        screen0cs.AddResourceWithSound(this, "Screen0cs","Screen0cs", 0.5);

        //AddClusterResource(20, "star", stars, 15., JuiceTypes::JUICE_PULSATE_FULLY, false);
        //return;
        AddRings(*this, ring4color);

        int anchorGameModeBannerY = (originY + bottomSide) / 2  + 18;
        AddResource(&starR, "star5", 20);
        starR.pos = f3(0.825*rightSide, anchorGameModeBannerY,0);
        starR.JuiceType = JuiceTypes::JUICE_ROTZ;
        starR.JuiceSpeed = 100;

        AddResource(&starL, "star5", 20);
        starL.pos = f3(0.175*rightSide, anchorGameModeBannerY,0);
        starL.JuiceType = JuiceTypes::JUICE_ROTZ;
        starL.JuiceSpeed = -100;

		AddResource(&gamemodesbanner, "gamemodesbanner", 27);
		gamemodesbanner.pos.y = anchorGameModeBannerY;
		gamemodesbanner.JuiceType = JuiceTypes::JUICE_PULSATE;

	}
   

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        
        gob->rotatefirst = false;
        if (gamemodesbanner.wasTouched()) {
            PosRotScale tgt;
            tgt.CopyFrom(gob);
            tgt.pos.x = randm() * rightSide;
            tgt.pos.y = randm() * bottomSide;
            gamemodesbanner.transitionTo(tgt);
        };

	}

    virtual i2 getBackgroundSize() {
        return i2(1280, 720);
    }

};
