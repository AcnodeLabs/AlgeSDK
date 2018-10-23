// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: MotoX3
*/

class App : public AlgeApp {
	
    GameObject bg, spikey, heli, baloons;
    CControls c;
    
public:
	
	virtual void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        static bool done = false;
        if (gob->modelId==spikey.modelId) {
            gob->rotatefirst = false;
            spikey.pos = heli.pos;
            spikey.pos.y += 150;
           // spikey.pos.y += heli.pos.y + 10;
        }
        if (bg.wasTouched()) {
           heli.transitionTo(bg.posTouched(), 500);
        }
        
        if (gob->modelId==baloons.modelId) {
            gob->getInstancePtr(instanceNo)->pos.y -= rndm(0, 3);
            if ( gob->getInstancePtr(instanceNo)->pos.y < topSide) gob->getInstancePtr(instanceNo)->pos.y = bottomSide + 70;
        }
        
        if (spikey.wasTouched()) {
           spikey.transitionTo(f2(bg.posTouched().x, bottomSide), 500);
        }
	}
	
	//Play Original https://bit.ly/2yKoV23
	virtual void Init(char* path) {
		alInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
        
		AddResource(&bg, "bg", 1);
        AddResource(&heli, "heli", 1);
        spikey.JuiceType = JuiceTypes::JUICE_PULSATE;
        AddResource(&spikey, "spikey",0.3);
        spikey.JuiceType = JuiceTypes::JUICE_ROTZ_PULSATE;
        spikey.JuiceSpeed = 10;
        
        AddResource(&baloons, "baloon");
        PosRotScale bp;
        bp.CopyFrom(&heli);
        for (int i=0; i< 10; i++) {
            bp.pos.x = randm() * rightSide;
            bp.pos.y = bottomSide - rndm(10, 200);
            bp.scale = rndm(0.5, 0.8);
            baloons.AddInstance(bp);
        }
        
        
        
        //PlaySnd("race-track.wav");
	}

    virtual i2 getBackgroundSize() {
        return i2(2048,1536);
    }
};
