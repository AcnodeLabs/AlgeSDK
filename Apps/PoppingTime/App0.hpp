// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
   The Assets Folder Name is PoppingTime.Assets,
   macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
*/
#include  "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"

#include "PoppingTimeLogic.hpp"

// Scrum Page https://scrumy.com/PoppingTime

class App : public AlgeApp {
	
	GameLogic logic;

	SettingScreen settings;
	StartScreen startScreen;

    GameObject spikey, heli, baloons, fan, score, cloud, getready, p_time;
	
	bool soundedOuch;
	int scene, nLoops, level, iScore, nRemaining;
	
	DPad dPad;

	i2 bgSize;
	int rightSide1;
	int leftSide1;

	FILE* f;

public:
	
    void LoadObjects() {
        startScreen.LoadIn(this);
        settings.LoadIn(this, &startScreen.bg, false);
        
        AddResource(&baloons, "baloon");// , 10, true, 1, 0.3);
        MakeBaloons();
        
        AddResource(&cloud, "cloud");
        MakeClouds(7);
        
        with AddResource(&spikey, "spikey", 0.5);
        _.JuiceType = JuiceTypes::JUICE_ROTZ;
        _.JuiceSpeed = 20;
        _with
        
        AddResource(&heli, "heli", 1);
        
        with AddResource(&fan, "fans");
        _.JuiceType = JuiceTypes::JUICE_ROTY;
        _.JuiceSpeed = 1500;
        _with
        
        score.pos.y = 0.05 * bottomSide;
        score.pos.x = 0.85 * rightSide;
        AddObject(&score);
        
        with dPad.LoadIn(this);
        dPad.JuiceType = 0;// JuiceTypes::JUICE_SCALE_IN;
        _.color = { 1,1,1 };
        _with
        
        with AddResource(&p_time, "poppingtime", 1.2);
        _.JuiceType = JuiceTypes::JUICE_PULSATE;
        _.JuiceSpeed = 200;
        _.AddInstance(f2(_.pos.x - 3, _.pos.y - 3))->color = f3(0.7, 0.7, 0.7); //grey shadow
        _.AddInstance(f2(_.pos.xy()));
        _with
        
        with AddResource(&getready, "getready");
        //_.JuiceType = JuiceTypes::JUICE_DIE;
        _.JuiceSpeed = 0.1;
        _.hidden = true;
        _with
    }
    
    void RepositionObjects() {
        startScreen.ratings.pos.y = 0.1 * bottomSide;
        startScreen.start.pos.x = 0.5 * rightSide;
        startScreen.start.pos.y = 0.9 * bottomSide;
        score.pos.y = 0.05 * bottomSide;
        score.pos.x = 0.85 * rightSide;
    }
    
	virtual void Init(char* path) {
	//	fopen_s(&f, "dbg.txt", "w");
		soundedOuch = false;
		nLoops = 100;
		level = 1;
		iScore = 0;
   //     wireframe = true;
        
		AlInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);

        
        output.pushP(CMD_SNDSET0, $ "happy-sandbox.wav");
        output.pushP(CMD_SNDSET1, $ "pop.wav");
        output.pushP(CMD_SNDSET2, $ "aargh.wav");
        output.pushP(CMD_SNDSET3, $ "drop.wav");
        output.pushP(CMD_SNDSET4, $ "entry.wav");

        output.pushP(CMD_SNDPLAY0, $ "happy-sandbox.wav", &nLoops);
        wall_msg = "Go";
        //glDisable(GL_CULL_FACE);
        output.pushI(CMD_USEGAMEPAD, 0, 0);

        scene = 0;
	}

	void MakeClouds(int n) {
		cloud.prsInstances.clear();
		PosRotScale bp;
		for (int i = 0; i < n; i++) {
			bp.pos = f3(rndm(leftSide, rightSide), rndm(10, bottomSide /2), 0);  //initially place balloons below bottom side
			bp.scale = rndm(0.5, 1.1);
			cloud.AddInstance(bp);
		}

	}

	void MakeBaloons() {
		int n = (level++) * 5 * (settings.valueDifficulty + 1);
		rightSide1 = settings.ico.getOwnRect().Left - heli.m_width;
		leftSide1 = heli.m_width / 2;
		baloons.prsInstances.clear();
		PosRotScale bp;
		bp.CopyFrom(&heli);
		for (int i = 0; i < n; i++) {
			bp.pos = f3(rndm(leftSide1,rightSide1), bottomSide + rndm(100, 600), 0);  //initially place balloons below bottom side
			bp.scale = rndm(0.3, 0.5);
			bp.color = f3(rndm(0.3, 0.99), rndm(0.3, 0.99), rndm(0.3, 0.99));
			baloons.AddInstance(bp);
		}
		nRemaining = baloons.prsInstances.size();
		getready.Show();
		getready.JuiceType = JuiceTypes::JUICE_DIE;
		getready.JuiceDuration = 2;
	}
	
	void DropSpikey() {
		if (spikey.animPos.active) return;
		spikey.transitionTof2(f2(startScreen.bg.posTouched().x, bottomSide), 500);
		output.pushP(CMD_SNDPLAY3, $ "drop.wav");
	}

	virtual void onActionComplete(GameObject* obj) {
		if (obj->is(heli)) {
			bool ok = true;
		}
	}
	
	void SetVisibleGameName(bool visible = true) {
		if (visible) {
			p_time.Show();
			p_time.getInstancePtr(1)->hidden = false;
		}
		else {
			p_time.Hide();
			p_time.getInstancePtr(1)->hidden = true;
		}
	}

	virtual void processInput(PEG::CMD* cmd, float deltaT) {
        static bool objectsNotLoaded = true;
        if (cmd->command == CMD_SCREENSIZE) {
            bgSize = i2(cmd->i1, cmd->i2);
            resolutionReported.x = cmd->i1;
            resolutionReported.y = cmd->i2;
          //  startScreen.start.pos.x = bgSize.x;
          //  startScreen.start.pos.y = bgSize.y;
            SetCamera(Camera::CAM_MODE_FPS, ORIGIN_IN_MIDDLE_OF_SCREEN);
            if (objectsNotLoaded) {LoadObjects();objectsNotLoaded = false;}
            RepositionObjects();
        }
        
        if (cmd->command == CMD_TOUCH_START) {
          //  startScreen.start.pos.x = cmd->i1;
          //  startScreen.start.pos.y = cmd->i2;
        }

		//test dimming
		if (cmd->command == CMD_KEYDOWN) {
			//dPad.hidden = !dPad.hidden;
		}

		if (cmd->command == CMD_SETTINGS_SCREEN) {
			if (cmd->i1 == 1) {
				SetVisibleGameName(false);
				startScreen.SetVisible(false);
				startScreen.bg.Show();
				
			}
			if (cmd->i1 == 2) {
				SetVisibleGameName(true);
				startScreen.SetVisible(true);
				startScreen.bg.Show();
			}
		}

		if (cmd->command == CMD_GAMEPAD_EVENT) {
			if (scene == 0) { scene++; return; }

			if (cmd->i1 == MyGamePad::EventTypes::BTN) {
				if (cmd->i2 == MyGamePad::EventCodes::BTN_X) DropSpikey();
			}
		}

		if (cmd->command == CMD_GAMEPAD_EVENT && cmd->i1 == MyGamePad::EventTypes::PAD) {
			if (cmd->i2 == MyGamePad::EventCodes::PAD_LT || cmd->i2 == MyGamePad::EventCodes::PAD_RT) {
				startScreen.bg.m_touchedX = (cmd->i2 == MyGamePad::EventCodes::PAD_LT? leftSide:rightSide);
				heli.transitionTof2(f2(startScreen.bg.m_touchedX, heli.pos.y), 500);
			}
			if (cmd->i2 == MyGamePad::EventCodes::PAD_UP || cmd->i2 == MyGamePad::EventCodes::PAD_DN) {
				startScreen.bg.m_touchedY = (cmd->i2 == MyGamePad::EventCodes::PAD_UP ? topSide : bottomSide);
				heli.transitionTof2(f2(heli.pos.x, startScreen.bg.m_touchedY), 500);
			}
		}

		if (onTouched("settings_icon")) {
			settings.SetVisible(true);
		}

		if (onTouched("spikey") || onTouched("heli")) DropSpikey();

		if (onTouched("bg") || onTouched("baloon")) {
							
			heli.JuiceType = 0;
			f2 postouch = startScreen.bg.posTouched();
			if (postouch.x > rightSide1) postouch.x = rightSide1;
			if (postouch.x < leftSide1) postouch.x = leftSide1;
			int topSide1 = topSide + (heli.m_height);
			int bottomSide1 = bottomSide - (heli.m_height + spikey.m_height);
			if (postouch.y > bottomSide1) postouch.y = bottomSide1;
			if (postouch.y < topSide1 ) postouch.y = topSide1;
			heli.transitionTof2(postouch, 500);
				
			if (heli.hidden) {
				heli.JuiceType = 0;
				heli.hidden = false;
				spikey.hidden = false;
				heli.pos = getBackgroundSize().half();
				soundedOuch = false;
			}
		}
	    if (settings.m_visible)	settings.processInput(cmd->command, i2(cmd->i1, cmd->i2));
	}

	virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
		doInhibitLogic(gob);
		if (scene == 0) UpdateScene0(gob, instanceNo, deltaT);
		if (scene == 1) UpdateScene1(gob, instanceNo, deltaT);

		if (gob->is(cloud)) {
			for (int i = 0; i < cloud.prsInstances.size(); i++) {
				PosRotScale* cloudprs = cloud.getInstancePtr(i);
				cloudprs->pos.x -= (deltaT * i);
				if (cloudprs->pos.x < -(leftSide * 0.2)) cloudprs->pos.x = rightSide * 1.2;
			}
		}
	}

	void doInhibitLogic(GameObject* gob) {
		if ((scene==0) &&(gob->is(heli) || gob->is(spikey) || gob->is(fan) || gob->is(baloons)))
			inhibitRender = true;
	}

	// First Intro Screen
	virtual void UpdateScene0(GameObject* gob, int instanceNo, float deltaT) {
        if (scene!=0) return;
		if (gob->isOneOf({ &heli,&spikey,&fan,&baloons,&dPad })) inhibitRender = true;

 		if (onTouched("start"))
        {
			scene = 1; //dPad.Show();
			output.pushP(CMD_SNDPLAY4, $ "entry.wav");
            paused = false;

		}
	}
	// GamePlay Scene
	virtual void UpdateScene1(GameObject* gob, int instanceNo, float deltaT) {
        if (scene!=1) return;
		if (gob->isOneOf({ &p_time,&startScreen.ratings,&startScreen.start })) inhibitRender = true;

		if (gob->is(dPad)) {
			//when come here when dPad.will be visible
			if (settings.valueControlMethod > 0) inhibitRender = true;
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
			bool moveRight = startScreen.bg.posTouched().x > heli.pos.x;
			//if (bg.wasTouched()) 
			faceRight = moveRight;
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
		
            PosRotScale* baloon = gob->getInstancePtr(instanceNo);//Gob==Balloon
			// rise baloon
			if (!paused) baloon->pos.y -= (1 + (pow(settings.valueDifficulty, 2) * deltaT * 100));
			// if baloon reaches topside teleport it 70 units below the bottom and let it rise again
			
			//static ostringstream oss;
			//oss.clear();
			//oss << "\ndeltaT=" << deltaT;
			//fputs(oss.str().c_str(), f);

			if (baloon->pos.y < topSide) {
				baloon->pos.y = bottomSide + 70;
				baloon->hidden = false;
			}

			if (doObjectsIntersect(&spikey, baloon)) {
				
				baloon->hidden = true;
				output.pushP(CMD_SNDPLAY1, $ "pop.wav", &nLoops);
				iScore++;
				
			//	static stringstream ss;
			//	ss.clear();
			//	ss << nRemaining;
			//	wall_msg = ss.str();
			
					nRemaining--;
					if (nRemaining <= 0) {
						paused = true;
						MakeBaloons();
						paused = false;
					}
			} 

			if (doObjectsIntersect(baloon, &heli)) {
				if (heli.JuiceType == 0) output.pushP(CMD_SNDPLAY2, $ "aargh.wav", &nLoops);
				soundedOuch = true;
				heli.JuiceType = JuiceTypes::JUICE_DIE_TEMP;
				heli.JuiceDuration = 0.75;
				iScore /= 2;
				if (iScore < 0) iScore = 0;
			}
            
		}
	}
	
	~App() {
		fclose(f);
	}
};

