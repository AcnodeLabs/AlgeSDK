//#include <CBaseV1_2.h>
// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/
using namespace ImGui;

#include "Starship.hpp"

class /*SN11 Box2D*/ App : public AlgeApp {

	GameObject background, gui;

public:

    bool my_tool_active = true;
    float my_color[4];

    float dat[64];
    bool burner_on;

    void pushDat(float f) {
        for (int i=0; i<64; i++) {
            dat[i] = dat[i+1];
        }
        dat[63] = f;
    }
    
    void MyFirstToolWindow(float dt) {
        // Create a window called "My First Tool", with a menu bar.
        Begin("Starship Parameters", &my_tool_active, ImGuiWindowFlags_MenuBar);

        // Edit a color (stored as ~4 floats)
        //ColorEdit4("Color", my_color);

        // Plot some values
        
        PlotLines("Height", dat, IM_ARRAYSIZE(dat));

        // Display contents in a scrolling region
        TextColored(ImVec4(1,1,0,1), "Altitude");
        for (auto b : ss.ship.prsInstances) {
            ImGui::Text("Alt@ [%d m]", Alt());
        }
       
        BeginChild("Controls");
        ImGui::SliderInt("Thrust [0-15]", &force, 0, 15);
        ImGui::SliderInt("Thrust Angle [-20 to +20]", &angle, -20, 20);
        ImGui::Checkbox("Burners", &burner_on);
        ss.burners.hidden = !burner_on;
        if (!burner_on) force = 0;
        EndChild();
        ImGui::Button("Redo");
        End();
    }
    int force, angle;
   
    void RenderGui(float dt) {
        if (gui.Visible()) {
            GuiStarts();
                MyFirstToolWindow(dt);
            GuiEnds();
        }
    }
    
    void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (gob->is(ss.ship)) {
        //for 2D model its not required//    glRotatef(90, 1, 0, 0);
        }

        if (gob->is(ss.burners)) {
            ss.burners.pos.x = ss.ship.getInstancePtr(0)->physBodyPtr->GetPosition().x* P2S - rightSide/2;
            ss.burners.pos.y = ss.ship.getInstancePtr(0)->physBodyPtr->GetPosition().y* P2S - bottomSide/2 + 100;
        }
        
        if (gob->is(gui)) RenderGui(deltaT);
    }

    int Alt() {
        float ht = (933-ss.ship.getInstancePtr(0)->physBodyPtr->GetPosition().y* P2S - bottomSide/2)/10;
        return ht;
    }
    
	virtual void processInput(PEG::CMD* p, float deltaT) {
        if (!ss.burners.hidden) {
            ss.ship.getInstancePtr(0)->Thrust(f2(0, -force/1.0));
        }
        if (p->command == CMD_KEYDOWN) {
            if (p->i1 == 'w' || p->i1 == 'W') wireframe = !wireframe;
            if (p->i1 == 'g' || p->i1 == 'G') gui.hidden = !gui.hidden;
        }
        pushDat(Alt());
 	}
    
    StarShip ss;
    int BaseLineHeight = 115;
    
	virtual void Init(char* path) {
        memset(dat,0,IM_ARRAYSIZE(dat));
        landscape = true;
		AlInit(STANDARD_2D, "SN11");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		InitPhysics();
        
		PhysAddGroundWithWalls(BaseLineHeight);
        force = 0;
		AddResource(&background, "bg_p", "bocachica.jpg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
     //   gui.Hide();
        ss.LoadIn(this);
        AddResource(&gui, "gui");
        output.pushP(CMD_SNDSET0, $ "pop.wav");
	}
};
