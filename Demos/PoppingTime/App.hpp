// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
*/

enum Sounds {
	SND_BG,
	SND_POP
};

class App : public AlgeApp {
	
    GameObject bg, spikey, heli, baloons, fan;
    CControls c;
    
public:
	
	class GameLogic {
	public:
		bool spikeyIsDropping = false;

	} logic;



	virtual void processInput(PEG::CMD* cmd, float deltaT) {
			if (onTouched("spikey")) {
				spikey.transitionTof2(f2(bg.posTouched().x, bottomSide), 500);
			}

			if (onTouched("bg")) {
				heli.JuiceType = 0;
				heli.transitionTof2(bg.posTouched(), 500);
			}
	}

	virtual void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        static bool done = false;
		static bool faceRight = false;

		if (gob->modelId==spikey.modelId) {
            gob->rotatefirst = false;
            spikey.pos = heli.pos;
            spikey.pos.y += 50;
			spikey.hidden = heli.hidden;
        } 
		
		if (gob->modelId == heli.modelId) {
			bool moveRight = bg.posTouched().x > heli.pos.x ;
			if (bg.wasTouched()) faceRight = moveRight;
			heli.rot.y = faceRight ? 180 : 0;
		}

		if (gob->modelId == fan.modelId) {
			fan.pos = heli.pos;
			fan.pos.y -= 33;
			fan.pos.x -= (heli.rot.y==0?15:-15);
			fan.hidden = heli.hidden;
		}
		static bool soundedOuch = false;

		if (heli.hidden && bg.wasTouched()) {
			heli.JuiceType = 0;
			heli.hidden = false;
			spikey.hidden = false;
			heli.pos = getBackgroundSize().half();
			soundedOuch = false;
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
				baloon->hidden = true;
				output.pushP(CMD_SNDPLAY1, $ "pop.wav");
			}
			
			

			if (doObjectsIntersect(baloon, &heli)) {
				heli.JuiceType = JuiceTypes::JUICE_DIE_TEMP;
				spikey.JuiceType = JuiceTypes::JUICE_ROTZ;
				if (!soundedOuch) {
					output.pushP(CMD_SNDPLAY2, $ "aargh.wav");
					soundedOuch = true;
				}
			
			}

        }
	}

	
	
	//Play Original https://bit.ly/2yKoV23
	virtual void Init(char* path) {
		AlInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);

		AddResource(&bg, "bg", 1);

        AddResource(&spikey, "spikey",0.5);
        spikey.JuiceType = JuiceTypes::JUICE_ROTZ;
        spikey.JuiceSpeed = 20;
		AddResource(&heli, "heli", 1);

		AddResource(&baloons, "baloon");// , 10, true, 1, 0.3);
		AddResource(&fan, "fans");
		fan.JuiceType = JuiceTypes::JUICE_ROTY;
		fan.JuiceSpeed = 1500;

		PosRotScale bp;
        bp.CopyFrom(&heli);
        for (int i=0; i< 100; i++) {
            bp.pos.x = randm() * rightSide;
			bp.pos.y = bottomSide + rndm(10, 500);  //initially place balloons below bottom side
            bp.scale = rndm(0.3, 0.5);
			bp.color = f3(randm(), randm(), randm());
            baloons.AddInstance(bp);
        }
	//	output.pushP(CMD_SNDSET0, $ "happy-sandbox.wav");
		output.pushP(CMD_SNDSET1, $ "pop.wav");
		output.pushP(CMD_SNDSET2, $ "aargh.wav");

	//	output.pushP(CMD_SNDPLAY0, $ "happy-sandbox.wav");
   }

    virtual i2 getBackgroundSize() {
        return i2(1024,512);
    }
};

