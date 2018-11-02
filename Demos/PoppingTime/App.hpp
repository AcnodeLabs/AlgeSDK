// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
*/

class App : public AlgeApp {
	
    GameObject bg, spikey, heli, baloons;
    CControls c;
    
public:
	
	virtual void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        static bool done = false;

		if (gob->modelId == bg.modelId) {
			inhibitRender = true;
		}

        if (gob->modelId==spikey.modelId) {
            gob->rotatefirst = false;
            spikey.pos = heli.pos;
            spikey.pos.y += 50;
           // spikey.pos.y += heli.pos.y + 10;
        }
        if (bg.wasTouched()) {
		  heli.JuiceType = 0;
          heli.transitionTo(bg.posTouched(), 500);
        }
        
        if (gob->modelId==baloons.modelId) {
			//point to y position of baloon
			PosRotScale *baloon =  gob->getInstancePtr(instanceNo);
			// rise baloon
            if (!paused) baloon->pos.y -= rndm(0, 3);
			// if baloon reaches topside teleport it 70 units below the bottom and let it rise again
			if (baloon->pos.y < topSide) {
				baloon->pos.y = bottomSide + 70; baloon->hidden = false;
			}

			if (doObjectsIntersect(baloon, &spikey)) {
				baloon->JuiceType = JuiceTypes::JUICE_DIE;
				baloon->JuiceSpeed = 100;
			//	paused = true;
			}

        }
        
        if (spikey.wasTouched()) {
           spikey.transitionTo(f2(bg.posTouched().x, bottomSide), 500);
        }

	}



	//Play Original https://bit.ly/2yKoV23
	virtual void Init(char* path) {
		AlInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);

		AddResource(&bg, "bg", 1);
		
		AddResource(&heli, "heli", 1);
	
        spikey.JuiceType = JuiceTypes::JUICE_PULSATE;
        AddResource(&spikey, "spikey",0.5);
        spikey.JuiceType = JuiceTypes::JUICE_ROTZ_PULSATE;
        spikey.JuiceSpeed = 10;
        
		AddResource(&baloons, "baloon");// , 10, true, 1, 0.3);
        
		PosRotScale bp;
        bp.CopyFrom(&heli);
        for (int i=0; i< 10; i++) {
            bp.pos.x = randm() * rightSide;
			bp.pos.y = bottomSide - rndm(10, 200);  //initially place balloons below bottom side
            bp.scale = rndm(0.3, 0.5);
            baloons.AddInstance(bp);
        }
		//output.pushP(CMD_SNDSET0, $ "happy-sandbox.wav", 0);
		//output.pushP(CMD_SNDPLAY0, $ "happy-sandbox.wav", 0);
   }

    virtual i2 getBackgroundSize() {
        return i2(1024,512);
    }
};

