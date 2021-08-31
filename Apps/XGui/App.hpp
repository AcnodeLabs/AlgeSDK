// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: XGui
*/

//App Specifics
#include "XGUI_App_Windows.hpp"

class /*XGui*/ App : public AlgeApp {
    
    //Variables
    bool my_tool_active;
    float my_color[4];
    ImFont *roboto;
    i2 msize;
    i2 mou;
    bool done = false;

    //Gfx Objects
	GameObject background, gui;

    
    
    XGUI_App_Windows app_gui;
public:
    
    
    //Primary Functions
    virtual void Init(char* path) {
    
    AlInit(STANDARD);
    SetTitle("XGui");
    
    AddDefaultCamera(Camera::CAM_MODE_2D,OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
        
        AddResource(&background, "juices",
            "green_natural.jpg",
            XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN
            );


        AddResource(&gui, "gui");
        gui.hidden = false;
        ImGui::GetIO().Fonts->AddFontDefault();
        roboto = ImGui::GetIO().Fonts->AddFontFromFileTTF((string(path)+"/Roboto-Bold.ttf").c_str(), 16.0f);
    }
    void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_SCREENSIZE) {
            msize.x = p->i1;
            msize.y = p->i2;
		}
  	}
	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (gob->is(gui) && !gui.hidden)
        {
            GuiStarts();
                app_gui.MyFirstToolWindow(deltaT);
            GuiEnds();
        }

	}

    //Secondary Functions
    i2 getBackgroudSize() {return msize;}
};
