//#include <CBaseV1_2.h>
// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/
using namespace ImGui;

#include "Starship.hpp"

class /*SN11 Box2D*/ App : public AlgeApp {

	GameObject background, ship, balls, gui;

public:

    bool my_tool_active = true;
    float my_color[4];
   
    void MyFirstToolWindow(float dt) {
        // Create a window called "My First Tool", with a menu bar.
        Begin("Balls and Boxes", &my_tool_active, ImGuiWindowFlags_MenuBar);

        // Edit a color (stored as ~4 floats)
        //ColorEdit4("Color", my_color);

        // Plot some values
        const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
        PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

        // Display contents in a scrolling region
        TextColored(ImVec4(1,1,0,1), "Important Stuff");
        BeginChild("Scrolling");
        ImGui::Text("FPS %.2f", 1.0/dt);
        ImGui::Text("Pos of Ship %.1f,%.1f", ss.ship.getInstancePtr(0)->physBodyPtr->GetPosition().x, ss.ship.getInstancePtr(0)->physBodyPtr->GetPosition().y);
        ImGui::Text("Pos of Burners %.1f,%.1f", ss.burners.pos.x, ss.burners.pos.y);
        ImGui::SliderInt("Impulse", &force, 1, 100);
        
        for (auto b : ship.prsInstances) {
            ImGui::Text("Box@ [%.0f,%.0f]", b.pos.x,b.pos.y);
        }
        EndChild();
        End();
    }
    int force;
   
    void RenderGui(float dt) {
        if (gui.Visible()) {
            GuiStarts();
       //         MyFirstToolWindow(dt);
            GuiEnds();
        }
    }
    
    void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (gob->is(ss.ship)) {
        //for 2D model its not required//    glRotatef(90, 1, 0, 0);
        }

        if (gob->is(ss.burners)) {
            ss.burners.pos.x = ss.ship.getInstancePtr(0)->physBodyPtr->GetPosition().x* P2S - rightSide/2;
            ss.burners.pos.y = ss.ship.getInstancePtr(0)->physBodyPtr->GetPosition().y* P2S - bottomSide/2 + 85;
        }
        
        if (gob->is(gui)) RenderGui(deltaT);
    }

	virtual void processInput(PEG::CMD* p, float deltaT) {
        
        if (p->command == CMD_KEYDOWN) {
            if (p->i1 == ' ') gui.hidden = !gui.hidden;
        }
        
        if (p->command == CMD_KEYDOWN) {
            if (p->i1 == 'w' || p->i1 == 'W') wireframe = !wireframe;
            if (p->i1 == 'g' || p->i1 == 'G') gui.hidden = !gui.hidden;
            if (p->i1 == ' ') {
                ss.burners.hidden = false;
                ss.ship.getInstancePtr(0)->Thrust(f2(0, -force/1.0));
            }
        }
        
        if (p->command == CMD_KEYUP) {
            if (p->i1 == ' ') ss.burners.hidden = true;
        }
        
        if (p->command == CMD_TOUCH_END) {
            if (!ss.burners.hidden) {
               
                
            }
            
        }
        
	}
    
    StarShip ss;
    
	virtual void Init(char* path) {
        landscape = true;
		AlInit(STANDARD_2D, "SN11");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		InitPhysics();
		PhysAddGroundWithWalls(115.0);
        force = 1000;
		AddResource(&background, "bg_p", "bocachica.jpg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
     //   gui.Hide();
        ss.LoadIn(this);
        AddResource(&gui, "gui");
        output.pushP(CMD_SNDSET0, $ "pop.wav");
	}
};
