// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: PoppingTime
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
            spikey.pos.y += 50;
           // spikey.pos.y += heli.pos.y + 10;
        }
        if (bg.wasTouched()) {
           heli.transitionTo(bg.posTouched(), 500);
        }
        
        if (gob->modelId==baloons.modelId) {
			//point to y position of baloon
			float *y =  & (gob->getInstancePtr(instanceNo)->pos.y);
			// rise baloon
            *y -= rndm(0, 3); 
			// if baloon reaches topside teleport it 70 units below the bottom and let it rise again
            if ( *y < topSide) *y = bottomSide + 70;
        }
        
        if (spikey.wasTouched()) {
           spikey.transitionTo(f2(bg.posTouched().x, bottomSide), 500);
        }

	}
	
	//Play Original https://bit.ly/2yKoV23
	virtual void Init(char* path) {
		AlInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);

		PhysicsInit();
		PhysAddGroundWithWalls();

		AddResource(&bg, "bg", 1);
		AddResource(&heli, "heli", 1);

        spikey.JuiceType = JuiceTypes::JUICE_PULSATE;
        AddResource(&spikey, "spikey",0.5);
        spikey.JuiceType = JuiceTypes::JUICE_ROTZ_PULSATE;
        spikey.JuiceSpeed = 10;
        
        AddResource(&baloons, "baloon");
        PosRotScale bp;
        bp.CopyFrom(&heli);
        for (int i=0; i< 10; i++) {
            bp.pos.x = randm() * rightSide;
            bp.pos.y = bottomSide - rndm(10, 200);  //initially place balloons below bottom side
            bp.scale = rndm(0.3, 0.5);
            baloons.AddInstance(bp);
        }
   }

    virtual i2 getBackgroundSize() {
        return i2(1024,512);
    }
};

