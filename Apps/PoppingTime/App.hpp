// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
   The Assets Folder Name is PoppingTime.Assets,
   macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
*/
#include  "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"

#include "PoppingTimeLayer1.hpp"


// Scrum Page https://scrumy.com/PoppingTime

class App : public AlgeApp {
	
    GameObject bg, ratings,spikey, heli, baloons, fan, p_time, score;
	
	bool soundedOuch;
	int scene, nLoops, numBaloons, iScore, nRemaining;
	PoppingTimeLayer1 l1;

public:
	
	virtual i2 getBackgroundSize() { return size_nokia5; }
	virtual void Init(char* path) {

		soundedOuch = false;
		nLoops = 100;
		numBaloons = 1;
		iScore = 0;

		AlInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);

		AddResource(&bg, "bg", 1.5);
		with AddResource(&ratings, "ratings", 0.7);
			_.pos.y = 0.1 * bottomSide;
		_with

		with AddResource(&p_time, "poppingtime", 1);
		_.JuiceType = JuiceTypes::JUICE_PULSATE;
		_.JuiceSpeed = 500;
		_.AddInstance(f2(_.pos.x - 3, _.pos.y - 3))->color = f3(0.7, 0.7, 0.7); //grey shadow
		_.AddInstance(f2(_.pos.xy()));
		_with

			with AddResource(&spikey, "spikey", 0.5);
		_.JuiceType = JuiceTypes::JUICE_ROTZ;
		_.JuiceSpeed = 20;
		_with

		AddResource(&heli, "heli", 1);

		AddResource(&baloons, "baloon");// , 10, true, 1, 0.3);

		with AddResource(&fan, "fans");
		_.JuiceType = JuiceTypes::JUICE_ROTY;
		_.JuiceSpeed = 1500;
		_with

			score.pos.y = 0.05 * bottomSide;
		score.pos.x = 0.85 * rightSide;
		AddObject(&score);

		//MakeBaloons(numBaloons);
		MakeBaloons(3);
	
	//	output.pushP(CMD_SNDSET0, $ "happy-sandbox.wav");
		output.pushP(CMD_SNDSET1, $ "pop.wav");
		output.pushP(CMD_SNDSET2, $ "aargh.wav");
		output.pushP(CMD_SNDSET3, $ "drop.wav");

	//	output.pushP(CMD_SNDPLAY0, $ "happy-sandbox.wav", &nLoops);

		wall_msg = "Go";

	}

	void MakeBaloons(int n) {
		baloons.prsInstances.clear();
		PosRotScale bp;
		bp.CopyFrom(&heli);
		for (int i = 0; i < n; i++) {
			bp.pos = f3(rightSide *randm(), bottomSide + rndm(10, 500), 0);  //initially place balloons below bottom side
			bp.scale = rndm(0.3, 0.5);
			bp.color = f3(rndm(0.3, 0.99), rndm(0.3, 0.99), rndm(0.3, 0.99));
			baloons.AddInstance(bp);
		}
		nRemaining = baloons.prsInstances.size() - 1;
	}

	
	virtual void onActionComplete(GameObject* obj) {
		if (obj->is(heli)) {
			bool ok = true;
		}
	}
	virtual void processInput(PEG::CMD* cmd, float deltaT) {
		if (onTouched("spikey") || onTouched("heli")) {
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
	virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
		if (scene == 0) UpdateScene0(gob, instanceNo, deltaT);
		if (scene == 1) UpdateScene1(gob, instanceNo, deltaT);
	}
	// First Intro Screen
	virtual void UpdateScene0(GameObject* gob, int instanceNo, float deltaT) {
		if (gob->is(heli) || gob->is(spikey) || gob->is(fan) || gob->is(baloons)) inhibitRender = true;
		if (onTouched("bg")) scene = 1;
	}
	// GamePlay Screen
	virtual void UpdateScene1(GameObject* gob, int instanceNo, float deltaT) {
		
		if (gob->is(p_time)) { 
			p_time.Hide();
			ratings.Hide();
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
		
		if (gob->is(score)) {
			glColor3f(0.0, 0.0, 0.0);
			std::ostringstream sc;
			sc << "Score : " << iScore;
			alPrint(sc.str().c_str());
			glPushMatrix();
			glTranslatef(0,30,0);
			alPrint(wall_msg.c_str());
			glPopMatrix();
		}

		if (gob->is(heli)) {
			static bool faceRight = false;
			bool moveRight = bg.posTouched().x > heli.pos.x;
			if (bg.wasTouched()) faceRight = moveRight;
			heli.rot.y = faceRight ? 180 : 0;
		}

		if (gob->is(fan)) {
			auto &_ = fan; {
				_.pos = heli.pos;
				_.pos.y -= 33;
				_.pos.x -= (heli.rot.y == 0 ? 15 : -15);
				_.hidden = heli.hidden;
			}
		}
	
		if (gob->is(baloons)) {
			//point to y position of baloon
			//PosRotScale *baloon = gob->getInstancePtr(instanceNo);
			
            PosRotScale* baloon = gob->Inst(instanceNo);//Gob==Balloon
			// rise baloon
			if (!paused) baloon->pos.y -= rndm(0, 3);
			// if baloon reaches topside teleport it 70 units below the bottom and let it rise again
			if (baloon->pos.y < topSide) {
				baloon->pos.y = bottomSide + 70;
				baloon->hidden = false;
			}

			if (doObjectsIntersect(&spikey, baloon)) {
				
				baloon->hidden = true;
				output.pushP(CMD_SNDPLAY1, $ "pop.wav", &nLoops);
				iScore++;
				
				stringstream ss;
				ss << nRemaining;
				wall_msg = ss.str();
				

					nRemaining--;
					if (nRemaining < 0) {
						MakeBaloons((numBaloons++)*5);
					}

				//fprintf_s(f, "\nMATCH sp{%.1f,%.1f, bl{%.1f,%.1f}", spikey.pos.x, spikey.pos.y, baloon->pos.x, baloon->pos.y);
			} else {
				//	fprintf_s(f, "\n----- sp{%.1f,%.1f, bl{%.1f,%.1f}", spikey.pos.x, spikey.pos.y, baloon->pos.x, baloon->pos.y);
			}

			if (doObjectsIntersect(baloon, &heli)) {
				if (heli.JuiceType == 0) output.pushP(CMD_SNDPLAY2, $ "aargh.wav", &nLoops);
				soundedOuch = true;
				heli.JuiceType = JuiceTypes::JUICE_DIE_TEMP;
				heli.JuiceDuration = 0.75;
				iScore /= 2;
				if (iScore < 0) iScore = 0;
				//output.pushP(CMD_SNDPLAY0, $ "happy-sandbox.wav", &nLoops);
			}
            
		}
	}
	
	~App() {
	}
};

