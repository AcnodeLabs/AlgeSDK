// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: XGui
*/

//App Specifics
#include "AnotherOne.hpp"

class /*XGui*/ App : public AlgeApp {
    
	GameObject background, gob_gui;
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


    AddResource(&gob_gui, "gui");
    app_gui.Init(string(path));
        
    }
    void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_SCREENSIZE) app_gui.msize = i2(p->i1,p->i2);
		
  	}
	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (gob->is(gob_gui))
        {
            GuiStarts();
                app_gui.ShowWindows(deltaT);
            GuiEnds();
        }

	}

    //Secondary Functions
    i2 getBackgroudSize() {return app_gui.msize;}
};
