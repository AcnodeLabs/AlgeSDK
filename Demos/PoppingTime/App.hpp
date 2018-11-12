// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
*/

class App : public AlgeApp {
	
    GameObject bg, spikey, heli, baloons, fan, p_time;
	FILE* f;

	bool soundedOuch = false;
	short scene = 0;
	int nLoops = 1;
	int numBaloons = 50;

public:

	~App() {
		if (f) fclose(f);
	}

	virtual void processInput(PEG::CMD* cmd, float deltaT) {
			if (onTouched("spikey")) {
				spikey.transitionTof2(f2(bg.posTouched().x, bottomSide), 500);
				output.pushP(CMD_SNDPLAY3, $ "drop.wav");
			}

			if (onTouched("bg") || onTouched("baloon")) {
				heli.JuiceType = 0;
				heli.transitionTof2(bg.posTouched(), 500);
				
				if (heli.hidden) {
					heli.JuiceType = 0;
					heli.hidden = false;
					spikey.hidden = false;
					heli.pos = getBackgroundSize().half();
					soundedOuch = false;
				}
			}			
	}
	
	// First Intro Screen
	virtual void UpdateScene0(GameObject* gob, int instanceNo, float deltaT) {
		if (gob->is(heli) || gob->is(spikey) ||	gob->is(fan) ||	gob->is(baloons))
			inhibitRender = true;

		if (onTouched("bg")) scene = 1;
	}
	// GamePlay Screen
	virtual void UpdateScene1(GameObject* gob, int instanceNo, float deltaT) {
	
		if (gob->is(p_time)) { 
			p_time.Hide();
			inhibitRender = true; 
		}

		if (gob->is(spikey)) {
			gob->rotatefirst = false;
			if (!spikey.animPos.active) {
				spikey.pos = heli.pos;
				spikey.pos.y += 50;
			}
			spikey.hidden = heli.hidden;
		}

		if (gob->is(heli)) {
			static bool faceRight = false;
			bool moveRight = bg.posTouched().x > heli.pos.x;
			if (bg.wasTouched()) faceRight = moveRight;
			heli.rot.y = faceRight ? 180 : 0;
		}

		if (gob->is(fan)) {
			fan.pos = heli.pos;
			fan.pos.y -= 33;
			fan.pos.x -= (heli.rot.y == 0 ? 15 : -15);
			fan.hidden = heli.hidden;
		}
	
		if (gob->is(baloons)) {
			//point to y position of baloon
			PosRotScale *baloon = gob->getInstancePtr(instanceNo);

			// rise baloon
			if (!paused) baloon->pos.y -= rndm(0, 3);
			// if baloon reaches topside teleport it 70 units below the bottom and let it rise again
			if (baloon->pos.y < topSide) {
				baloon->pos.y = bottomSide + 70; baloon->hidden = false;
			}

			if (doObjectsIntersect(&spikey, baloon)) {
				baloon->hidden = true;
				output.pushP(CMD_SNDPLAY1, $ "pop.wav", &nLoops);
				//fprintf_s(f, "\nMATCH sp{%.1f,%.1f, bl{%.1f,%.1f}", spikey.pos.x, spikey.pos.y, baloon->pos.x, baloon->pos.y);
			}
			else {
				//	fprintf_s(f, "\n----- sp{%.1f,%.1f, bl{%.1f,%.1f}", spikey.pos.x, spikey.pos.y, baloon->pos.x, baloon->pos.y);
			}

			if (doObjectsIntersect(baloon, &heli)) {
				//	heli.JuiceType = JuiceTypes::JUICE_DIE_TEMP;
				//	spikey.JuiceType = JuiceTypes::JUICE_ROTZ;
				if (!soundedOuch) {
					output.pushP(CMD_SNDPLAY2, $ "aargh.wav", &nLoops);
					soundedOuch = true;
					heli.JuiceType = JuiceTypes::JUICE_DIE_TEMP;
					heli.JuiceDuration = 0.75;
					baloon->hidden = true;
					for (int i = 0; i < numBaloons; i++) {
						PosRotScale *b = gob->getInstancePtr(i);
						f3 loc_to(rightSide - b->pos.x, 800 + bottomSide -b->pos.y,0);
						b->pos = loc_to;
					}
				}

			}
			else {
				soundedOuch = false;
			}

		}

	}

	virtual void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        
		if (scene == 0) UpdateScene0(gob, instanceNo, deltaT);
		if (scene == 1) UpdateScene1(gob, instanceNo, deltaT);
	
	}
	
	virtual void Init(char* path) {
		AlInit(STANDARD); wireframe = true;
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		//fopen_s(&f, "spiky-vs-balloon.G", "w+");

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
        for (int i=0; i< numBaloons; i++) {
			bp.pos.x = rightSide *randm();
			bp.pos.y = bottomSide /2 + rndm(10, 500);  //initially place balloons below bottom side
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

