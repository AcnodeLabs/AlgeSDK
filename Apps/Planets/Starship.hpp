// Copyright (c) 2018 AcnodLabs Inc

/* 
 ALGE SDK JD4 Demo :: PoppingTime
 The Assets Folder Name is PoppingTime.Assets,
 macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
 */

#include "SolarDb.hpp"

class StarshipApp : public MockUpOne {
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
		LoadMock(that,  /*TitleImage*/ "titletext", /*SettingsImage*/ "settings","pointer", "settings_icon", "bg_p");
		
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
        int nxtModelId = planets[7].modelId+1;
        string fpath = string(that->rm.resourcepath)+ "/Starship/model.dae";
   //     that->rm.loadColladaModel(fpath.c_str(), nxtModelId);
        
		//dPad.Hide();
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

class AWindow {
public:
    GameObject gui;
    void Init(AlgeApp* that) {
        that->AddResource(&gui, "gui");
    }

    void Update(GameObject* check, float deltaT) {
        if (check->is(gui) && !gui.hidden)
        {
            //GuiStarts();
            //Show(deltaT);
            //GuiEnds();
        }
    }

    void Show(float dt) {
    //    {
    //        static string m_vehregno, m_result;
    //        static float f = 0.0f;
    //        static int counter = 0;

    //        ImGui::Begin("Vehicle Lookup");                          // Create a window called "Hello, world!" and append into it.

    //        ImGui::InputText("Enter Vehicle Reg No XX-NNN", (char*)m_vehregno.c_str(), 128, 0, 0, 0);
    //        bool clicked = ImGui::Button("Go!");
    //        if (clicked) {
    //            netmsg.Post("veh_regno=" + string(m_vehregno));
    //        }
    //        ImGui::Text("%s", m_result);

    //        //ImGui::Text("Screen Size = {%d x %d}", msize.x, msize.y);               // Display some text (you can use a format strings too)
    //        //ImGui::Text("Mouse Pos = {%d x %d}", mou.x, mou.y);               // Display some text

    //        //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    //        //ImGui::Checkbox("Another Window", &show_another_window);

    //        //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    //        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    //        //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
    //        //    counter++;
    //        //ImGui::SameLine();
    //        //ImGui::Text("counter = %d", counter);

    //        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    //        ImGui::SetWindowPos(ImVec2(0, 50), true);
    //        ImGui::End();
    //    }
    }
};

class App : public AlgeApp {
    
    int scene, nLoops, level, iScore;
    i2 bgSize;
    FILE* f;
    
public:
	void printDebug() {
		
	}

    StarshipApp pp;
    GameObject sn11;

    bool soundedOuch;


    virtual void Init(char* path) {
  
        soundedOuch = false;
        nLoops = 100;
        level = 1;
        iScore = 0;
        
        AlInit(STANDARD);
        AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
    //	pp.LoadIn(this);
    //    w.Init(this);
        AddResource(&sn11, "sn11" /*blender 2.92 .blend>>.stl>>import stl in blender 2.44>export_alx script*/, 50.0);
        
        sn11.JuiceType = JuiceTypes::JUICE_ROTXYZ;
        wireframe = true;
    }
    
    virtual void onActionComplete(GameObject* obj) {
        pp.onActionComplete(obj);
    }

    
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
    AWindow w;

    virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
        if (scene == 0) UpdateScene0(gob, instanceNo, deltaT);
        if (scene == 1) UpdateScene1(gob, instanceNo, deltaT);
        
        w.Update(gob,deltaT);

		if (scene!=0 && gob->is(pp.fps_text)) {
			string x = string("LEFT= ") + to_string(pp.nRemaining);
				glPushMatrix();
				text.PrintTextGl(x.c_str(), f3(0,0,0), 2);
				glPopMatrix();
		}

       // inhibitRender = false;//Show ALL for DEBUG
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

