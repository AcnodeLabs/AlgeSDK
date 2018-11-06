// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
*/

class App : public AlgeApp {
	
    GameObject bg, spikey, heli, baloons, fan, p_time;
    
public:

	virtual void processInput(PEG::CMD* cmd, float deltaT) {
			if (onTouched("spikey")) {
				spikey.transitionTof2(f2(bg.posTouched().x, bottomSide), 500);
				output.pushP(CMD_SNDPLAY3, $ "drop.wav");
			}

			if (onTouched("bg") || onTouched("baloon")) {
				heli.JuiceType = 0;
				heli.transitionTof2(bg.posTouched(), 500);
			}			
	}

	virtual void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        static bool done = false;
		static bool faceRight = false;


		if (scene == 0) {
			if (gob->modelId == heli.modelId ||
			    gob->modelId == spikey.modelId ||
				gob->modelId == fan.modelId ||
				gob->modelId == baloons.modelId) 
				inhibitRender = true;
		}
		else if (scene == 1) {
			if (gob->modelId == p_time.modelId) {
				inhibitRender = true; p_time.hidden = true;
			}
		}
				
		if (scene == 0 && bg.wasTouched()) {
			scene = 1;
			
		}


		if (gob->modelId==spikey.modelId) {
			spikey.Hide();
			inhibitRender = true;
			return;
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

			if (false && doObjectsIntersect(baloon, &spikey)) {
				baloon->hidden = true;
				output.pushP(CMD_SNDPLAY1, $ "pop.wav", &nLoops);
			}
		
			if (doObjectsIntersect(baloon, &heli)) {
			//	heli.JuiceType = JuiceTypes::JUICE_DIE_TEMP;
			//	spikey.JuiceType = JuiceTypes::JUICE_ROTZ;
				if (!soundedOuch) {
					output.pushP(CMD_SNDPLAY2, $ "aargh.wav", &nLoops);
					soundedOuch = true;
					heli.JuiceType = JuiceTypes::JUICE_DIE_TEMP;
				}
			
			}
			else {
				soundedOuch = false;
			}

        }
	}

	short scene = 0;
    int nLoops = 1;
    
	//Play Original https://bit.ly/2yKoV23
	virtual void Init(char* path) {
		AlInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);

		AddResource(&bg, "bg", 1.5);

		AddResource(&p_time, "poppingtime", 1);
		p_time.JuiceType = JuiceTypes::JUICE_PULSATE;
		p_time.JuiceSpeed = 500;

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
        for (int i=0; i< 2; i++) {
			bp.pos.x = 20 + rightSide / 2;// *randm();
			bp.pos.y = bottomSide + rndm(10, 500);  //initially place balloons below bottom side
            bp.scale = rndm(0.3, 0.5);
			bp.color = f3(rndm(0.3, 0.99), rndm(0.3, 0.99), rndm(0.3, 0.99));
            baloons.AddInstance(bp);
        }
		output.pushP(CMD_SNDSET0, $ "happy-sandbox.wav");
		output.pushP(CMD_SNDSET1, $ "pop.wav");
		output.pushP(CMD_SNDSET2, $ "aargh.wav");
		output.pushP(CMD_SNDSET3, $ "drop.wav");

		//output.pushP(CMD_SNDPLAY0, $ "happy-sandbox.wav",&nLoops);
   }

	virtual i2 getBackgroundSize() { return size_ipad_air.half(); }
};

