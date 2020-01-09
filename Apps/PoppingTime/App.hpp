// Copyright (c) 2018 AcnodLabs Inc

/* 
 ALGE SDK JD4 Demo :: PoppingTime
 The Assets Folder Name is PoppingTime.Assets,
 macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
 */

//#include  "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"

#include "PoppingTimeLogic.hpp"
#include "../LevelSelect/LevelSelector.hpp"

// Scrum Page https://scrumy.com/PoppingTime

class PoppingGame : public MockUpOne {
public:
    GameObject spikey, heli, baloons, fan, cloud, getready;
	GameObject fps_text;
    
    
    int nRemaining;
    int rightSide1;
    int leftSide1;
    int level = 1;
    
    enum Scenes {
        StartScene,
        PlayScene,
    };


    void LoadIn(AlgeApp* that) {
        //FIRST LOAD MOCK
		LoadMock(that,  /*TitleImage*/ "poppingtime", /*SettingsImage*/ "settings","pointer", "settings_icon");
		
        ///LOAD PLAY OBJECTS
        that->AddResource(&baloons, "baloon");// , 10, true, 1, 0.3);
        MakeBaloons();
        
        that->AddResource(&cloud, "cloud");
        MakeClouds(7);
        
        with that->AddResource(&spikey, "spikey", 0.5);
        _.JuiceType = JuiceTypes::JUICE_ROTZ;
        //_.JuiceSpeed = 20;
        _with
        
        that->AddResource(&heli, "heli", 1);
        
        with that->AddResource(&fan, "fans");
        _.JuiceType = JuiceTypes::JUICE_ROTY;
        _.JuiceSpeed *= 15;
        _with
        
        with that->AddResource(&getready, "getready");
		 _.JuiceType = JuiceTypes::JUICE_DIE;
		  //_.JuiceSpeed = 0.005;
		  _.hidden = true;
		_with

		with that->AddObject(&fps_text);
			_.pos.x = that->rightSide / 20;
			_.pos.y = that->bottomSide / 20;
			_.color = f3(0, 0, 0);
            _with

        

    }
    
    void MakeClouds(int n) {
        cloud.prsInstances.clear();
        PosRotScale bp;
        for (int i = 0; i < n; i++) {
            bp.pos = f3(rndm(app->leftSide, app->rightSide), rndm(10, app->bottomSide /2), 0);  //initially place balloons below bottom side
            bp.scale = rndm(0.5, 1.1);
            cloud.AddInstance(bp);
        }
        
    }
    
    void processInput(PEG::CMD* cmd, float deltaT) {
        
        if (cmd->command == CMD_TOUCH_START) {

            {
                if (app->onTouched("spikey") || app->onTouched("heli")) DropSpikey();
            }


            if (app->onTouched("bg") || app->onTouched("baloon")) {
                heli.JuiceType = 0;
                f2 postouch = startScreen.bg.posTouched();
                if (postouch.x > rightSide1) postouch.x = rightSide1;
                if (postouch.x < leftSide1) postouch.x = leftSide1;
                int topSide1 = app->topSide + (heli.m_height);
                int bottomSide1 = app->bottomSide - (heli.m_height + spikey.m_height);
                if (postouch.y > bottomSide1) postouch.y = bottomSide1;
                if (postouch.y < topSide1) postouch.y = topSide1;
                heli.transitionTof2(postouch, 500);

                if (heli.hidden) {
                    heli.JuiceType = 0;
                    heli.hidden = false;
                    spikey.hidden = false;
                    heli.pos = app->getBackgroundSize().half();// pos in middle of screen
                }
            }

        }

        if (cmd->command == CMD_TOUCHMOVE) {
            if (!heli.hidden) {
                heli.animPos.active = false;
                heli.pos = i2(cmd->i1, cmd->i2);
            }
        }
        
        if (cmd->command == CMD_KEYDOWN) {
            if (cmd->i1 == MAC_KEY_PLUS) {
                for (unsigned int i=0; i< baloons.prsInstances.size(); i++) {
                    baloons.getInstancePtr(i)->hidden = false;
                    app->output.pushP(CMD_SNDPLAY3, $ "drop.wav");
                }
            }
        }
        
        if (cmd->command == CMD_GAMEPAD_EVENT) {
            if (cmd->i1 == MyGamePad::EventTypes::BTN) {
                if (cmd->i2 == MyGamePad::EventCodes::BTN_X) DropSpikey();
            }
        }
        if (cmd->command == CMD_GAMEPAD_EVENT && cmd->i1 == MyGamePad::EventTypes::PAD) {
            if (cmd->i2 == MyGamePad::EventCodes::PAD_LT || cmd->i2 == MyGamePad::EventCodes::PAD_RT) {
                heli.transitionTof2(f2(startScreen.bg.m_touchedX, heli.pos.y), 500);
            }
            if (cmd->i2 == MyGamePad::EventCodes::PAD_UP || cmd->i2 == MyGamePad::EventCodes::PAD_DN) {
                heli.transitionTof2(f2(heli.pos.x, startScreen.bg.m_touchedY), 500);
            }
        }
        MockUpOne::processInput(cmd, deltaT);
    }
    
    void MakeBaloons() {
        int n = (level++) * 25 * (settings.valueDifficulty + 1);
        rightSide1 = settings.ico.getOwnRect().Left - heli.m_width;
        leftSide1 = heli.m_width / 2;
        baloons.prsInstances.clear();
        PosRotScale bp;
        bp.CopyFrom(&heli);
        for (int i = 0; i < n; i++) {
            bp.pos = f3(rndm(leftSide1,rightSide1), app->bottomSide + rndm(100, 600), 0);  //initially place balloons below bottom side
            bp.scale = rndm(0.3, 0.5);
            bp.color = f3(rndm(0.3, 0.99), rndm(0.3, 0.99), rndm(0.3, 0.99));
            baloons.AddInstance(bp);
        }
        nRemaining = (int) baloons.prsInstances.size();
        getready.Show();
        getready.JuiceType = JuiceTypes::JUICE_DIE;
        getready.JuiceDuration = 2;
		getready.JuiceSpeed = 0.005;
    }
    
    void onActionComplete(GameObject* obj) {
        if (obj->is(heli)) {
           // bool ok = true;
        }
    }
        
    void DropSpikey() {
        if (spikey.animPos.active) return;
        spikey.transitionTof2(f2(startScreen.bg.posTouched().x, app->bottomSide), 500);
        app->output.pushP(CMD_SNDPLAY3, $ "drop.wav");
    }
};

class App : public AlgeApp {
    
    int scene, nLoops, level, iScore;
    i2 bgSize;
    FILE* f;
    
public:

    PoppingGame pp;
    LevelSelector lvlSelector;

    bool soundedOuch;
    
    virtual void Init(char* path) {
  
        soundedOuch = false;
        nLoops = 100;
        level = 1;
        iScore = 0;
        
        AlInit(STANDARD);
        AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
        
        output.pushP(CMD_SNDSET0, $ "happy-sandbox.wav");
        output.pushP(CMD_SNDSET1, $ "pop.wav");
        output.pushP(CMD_SNDSET2, $ "aargh.wav");
        output.pushP(CMD_SNDSET3, $ "drop.wav");
        output.pushP(CMD_SNDSET4, $ "entry.wav");
        
        wall_msg = "Go";
        
		output.pushI(CMD_USEGAMEPAD, 0, 0);
        scene = PoppingGame::Scenes::StartScene;

        lvlSelector.Init(path);  // resoucemanaer not working with app in app

    }
    
    virtual void processInput(PEG::CMD* cmd, float deltaT) {
        static bool objectsNotLoaded = true;
			
		if (cmd->command == CMD_GAMEPAD_EVENT) {
            if (scene == PoppingGame::Scenes::StartScene) { 
                scene = PoppingGame::Scenes::PlayScene; 
                return; 
            }
        }
        
        if (cmd->command == CMD_SCREENSIZE) {
            bgSize = i2(cmd->i1, cmd->i2);
            resolutionReported.x = cmd->i1;
            resolutionReported.y = cmd->i2;
            //  startScreen.start.pos.x = bgSize.x;
            //  startScreen.start.pos.y = bgSize.y;
            SetCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
            if (objectsNotLoaded) {
                pp.LoadIn(this);objectsNotLoaded = false;
            }
        }

        pp.processInput(cmd,deltaT);
    }
    
    virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {

        if (scene == PoppingGame::Scenes::StartScene) UpdateStartScene(gob, instanceNo, deltaT);
        if (scene == PoppingGame::Scenes::PlayScene)  UpdatePlayScene(gob, instanceNo, deltaT);
        
        //Clouds Move in Both Screens
        if (gob->is(pp.cloud)) {
            for (unsigned short i = 0; i < pp.cloud.prsInstances.size(); i++) {
                PosRotScale* cloudprs = pp.cloud.getInstancePtr(i);
                cloudprs->pos.x -= (deltaT * i);
                cloudprs->rot.z = 0;
                if (cloudprs->pos.x < -(leftSide * 0.2)) cloudprs->pos.x = rightSide * 1.2;
            }
        }

    }
    
    // First Intro Screen
    virtual void UpdateStartScene(GameObject* gob, int instanceNo, float deltaT) {
        if (scene!=0) return;
        if ((gob->is(pp.heli) || gob->is(pp.spikey) || gob->is(pp.fan) || gob->is(pp.baloons)|| gob->is(pp.MockUpOne::dPad))) inhibitRender = true;
        if (onTouched("start"))
        {
            scene = 1; //dPad.Show();
            output.pushP(CMD_SNDPLAY4, $ "entry.wav");
            paused = false;      
        }
    }
    
    // GamePlay Scene
    virtual void UpdatePlayScene(GameObject* gob, int instanceNo, float deltaT) {
        if (scene!=1) return;
      //  if (gob->isOneOf({ &pp.titl,&pp.startScreen.ratings,&pp.startScreen.start }))
        if (gob->is(pp.titl) || gob->is(pp.startScreen.ratings) || gob->is(pp.startScreen.start)) inhibitRender = true;
        
        if (gob->is(pp.dPad)) {
            //when come here when dPad.will be visible
            if (pp.settings.valueControlMethod > 0) inhibitRender = true;
        }
        
        if (gob->is(pp.spikey)) {
            gob->rotatefirst = false;
            if (!pp.spikey.animPos.active) {
                pp.spikey.pos = pp.heli.pos;
                pp.spikey.pos.y += 50;
            }
            pp.spikey.hidden = pp.heli.hidden;
        }
        
        if (gob->is(pp.score)) {
            glColor3f(0.0, 0.0, 0.0);
            std::ostringstream sc;
            sc << "Score : " << iScore;
            alPrint(sc.str().c_str());
            glPushMatrix();
            glTranslatef(0,30,0);
            alPrint(wall_msg.c_str());
            glPopMatrix();
        }
        
        if (gob->is(pp.heli)) {
            static bool faceRight = false;
            bool moveRight = pp.startScreen.bg.posTouched().x > pp.heli.pos.x;
            //if (bg.wasTouched())
            faceRight = moveRight;
            pp.heli.rot.y = faceRight ? 180 : 0;
        }
        
        if (gob->is(pp.fan)) {
            auto &_ = pp.fan; {
                _.pos = pp.heli.pos;
                _.pos.y -= 33;
                _.pos.x -= (pp.heli.rot.y == 0 ? 15 : -15);
                _.hidden = pp.heli.hidden;
            }
        }
        
        if (gob->is(pp.baloons)) {
            //point to y position of baloon
            //PosRotScale *baloon = gob->getInstancePtr(instanceNo);
            
            PosRotScale* baloon = gob->getInstancePtr(instanceNo);//Gob==Balloon
            // rise baloon
            if (!paused) {
                //https://docs.google.com/spreadsheets/d/1ug4E5MBKOYcaR2HvguslmNZtZei-e0NyGpNKOelGcD0/edit#gid=0
                int val = (1 + (pow(pp.settings.valueDifficulty+1, 2) * deltaT * 100 * (baloon->scale)));
                baloon->pos.y -= val;
            }
            // if baloon reaches topside teleport it 70 units below the bottom and let it rise again
            
            //static ostringstream oss;
            //oss.clear();
            //oss << "\ndeltaT=" << deltaT;
            //fputs(oss.str().c_str(), f);
            
            if (baloon->pos.y < topSide) {
                baloon->pos.y = bottomSide + 70;
                baloon->hidden = false;
            }
            
            if (doObjectsIntersect(baloon, &pp.heli)) {
                if (pp.heli.JuiceType == 0) output.pushP(CMD_SNDPLAY2, $ "aargh.wav", &nLoops);
                soundedOuch = true;
                //    pp.heli.JuiceType = JuiceTypes::JUICE_DIE;
                //    pp.heli.JuiceDuration = 0.75;
                iScore /= 2;
                if (iScore < 0) iScore = 0;
            }

            if (doObjectsIntersect(&pp.spikey, baloon) || soundedOuch) {
                soundedOuch = false;
                baloon->hidden = true;
                output.pushP(CMD_SNDPLAY1, $ "pop.wav", &nLoops);
                iScore++;
                
                //	static stringstream ss;
                //	ss.clear();
                //	ss << nRemaining;
                //	wall_msg = ss.str();
                
                pp.nRemaining = 0;
                for (unsigned short i=0; i< gob->prsInstances.size(); i++) {
                    if (!gob->getInstancePtr(i)->hidden) pp.nRemaining++;
                }
                
                if (pp.nRemaining <= 0) {
                    paused = true;
                    pp.MakeBaloons();
                    paused = false;
                }
            }
            
            
            
        }

        if (gob->is(pp.fps_text)) {
            string x = string("LEFT= ") + to_string(pp.nRemaining);
            glPushMatrix();
            text.PrintTextGl(x.c_str(), f3(0, 0, 0), 2);
            glPopMatrix();
        }

    }
    //fully delegated
    virtual void onActionComplete(GameObject* obj) { pp.onActionComplete(obj); }
    ////

    ~App() {
        if (f) fclose(f);
    }
};

