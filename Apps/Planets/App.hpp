// Copyright (c) 2018 AcnodLabs Inc

/* 
 ALGE SDK JD4 Demo :: PoppingTime
 The Assets Folder Name is PoppingTime.Assets,
 macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
 */

//#include  "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"

#include "SolarDb.hpp"

// Scrum Page https://scrumy.com/PoppingTime

class PlanetsApp : public MockUpOne {
public:
   
    GameObject planets[9];
	GameObject fps_text;
    SolarDB db;
    
    int nRemaining;
    int rightSide1;
    int leftSide1;
    int level = 1;
    
    void ShowPlanet(int n) {
        for (int i=0; i<9; i++) {
            planets[i].Hide();
        }
        planets[n].Show();
    }
    
    void LoadIn(AlgeApp* that) {
        //FIRST LOAD MOCK
		LoadMock(that,  /*TitleImage*/ "titletext", /*SettingsImage*/ "settings","pointer", "settings_icon");
		
		with that->AddObject(&fps_text);
			_.pos.x = that->rightSide / 20;
			_.pos.y = that->bottomSide / 20;
			_.color = f3(0, 0, 0);
		_with
        
		for (int i = 0; i < 8; i++) {
			with that->AddResource(&planets[i], db.getName(i), 100);
				_.pos.x = i * that->rightSide / SolarDB::NUM_PLANETS;
				_.hidden = true;
				_.rot.z = 180;
			_with

		}
        
    }
    
    void processInput(PEG::CMD* cmd, float deltaT) {
        
        if (cmd->command == CMD_TOUCH_START) {
            
            if (app->onTouched("bg")) {
                
                f2 postouch = startScreen.bg.posTouched();
                if (postouch.x > rightSide1) postouch.x = rightSide1;
                if (postouch.x < leftSide1) postouch.x = leftSide1;
               
                
            }
            
        }
        
        if (cmd->command == CMD_KEYDOWN) {
            if (cmd->i1 == MAC_KEY_PLUS) {
            
            }
        }
        
		if (cmd->command == CMD_SETTINGS_SCREEN) {
		}

        if (cmd->command == CMD_GAMEPAD_EVENT) {
            if (cmd->i1 == MyGamePad::EventTypes::BTN) {
				if (cmd->i2 == MyGamePad::EventCodes::BTN_X)
                    ;
            }
        }
        if (cmd->command == CMD_GAMEPAD_EVENT && cmd->i1 == MyGamePad::EventTypes::PAD) {
            if (cmd->i2 == MyGamePad::EventCodes::PAD_LT || cmd->i2 == MyGamePad::EventCodes::PAD_RT) {
            }
            if (cmd->i2 == MyGamePad::EventCodes::PAD_UP || cmd->i2 == MyGamePad::EventCodes::PAD_DN) {
            }
        }
        MockUpOne::processInput(cmd, deltaT);
    }
    
    void MakeStarField() {
        PosRotScale bp;
        for (int i = 0; i < 100; i++) {
        }
   
    }
    
    void onActionComplete(GameObject* obj) {
   
    }
   
};

class App : public AlgeApp {
    
    int scene, nLoops, level, iScore;
    i2 bgSize;
    FILE* f;
    
public:
	void printDebug() {
		
	}

    PlanetsApp pp;
    
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
        
        //output.pushP(CMD_SNDPLAY0, $ "happy-sandbox.wav", &nLoops);
        wall_msg = "Go";
        
		output.pushI(CMD_USEGAMEPAD, 0, 0);
        scene = 0;
        pp.dPad.Hide();

		pp.LoadIn(this);
    }
    
    virtual void onActionComplete(GameObject* obj) {
        pp.onActionComplete(obj);
    }
    
//    virtual i2 getBackgroundSize() {
//        return size_ipad_air;
//    }
    
    virtual void processInput(PEG::CMD* cmd, float deltaT) {
        static bool objectsNotLoaded = true;
		
			
		if (cmd->command == CMD_GAMEPAD_EVENT) {
            if (scene == 0) { scene++; return; }
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

		if (cmd->command == CMD_TOUCH_START) {
			pp.ShowPlanet(shownPlanet);
			shownPlanet++;
			if (shownPlanet >= SolarDB::NUM_PLANETS) shownPlanet=0;
		}

        pp.processInput(cmd,deltaT);
        
    }
    
	//CFTFont font;

    virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
       doInhibitLogic(gob);
        if (scene == 0) UpdateScene0(gob, instanceNo, deltaT);
        if (scene == 1) UpdateScene1(gob, instanceNo, deltaT);
        

		if (scene!=0 && gob->is(pp.fps_text)) {
			string x = string("LEFT= ") + to_string(pp.nRemaining);
				glPushMatrix();
				text.PrintTextGl(x.c_str(), f3(0,0,0), 2);
				glPopMatrix();
		}

       // inhibitRender = false;//Show ALL for DEBUG
    }
    
    void doInhibitLogic(GameObject* gob) {

    }

    // First Intro Screen
    virtual void UpdateScene0(GameObject* gob, int instanceNo, float deltaT) {
        if (scene!=0) return;

        if (onTouched("start"))
        {
            scene = 1; //dPad.Show();
            output.pushP(CMD_SNDPLAY4, $ "entry.wav");
            paused = false;
            pp.startScreen.bg.Hide();
        }
    }
	int shownPlanet = 0;
    // GamePlay Scene
    virtual void UpdateScene1(GameObject* gob, int instanceNo, float deltaT) {
        if (scene!=1) return;
      //  if (gob->isOneOf({ &pp.titl,&pp.startScreen.ratings,&pp.startScreen.start }))
        if (gob->is(pp.titl) || gob->is(pp.startScreen.ratings) || gob->is(pp.startScreen.start)) inhibitRender = true;
        
        if (gob->is(pp.dPad)) {
            //when come here when dPad.will be visible
            if (pp.settings.valueControlMethod > 0) inhibitRender = true;
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
		
		//shownPlanet++;
		//if (shownPlanet >= SolarDB::NUM_PLANETS) shownPlanet = 0;
        
    }
    
    ~App() {
        if (f) fclose(f);
    }
};

