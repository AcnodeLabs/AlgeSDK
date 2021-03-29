//#include <CBaseV1_2.h>
// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/

#ifndef NO_IMGUI
using namespace ImGui;
#endif
#include "Starship.hpp"
#include "Box2DebugDraw.hpp"

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
    int force;
    int angle;
#ifndef NO_IMGUI    
    void MyFirstToolWindow(float dt) {

        // Create a window called "My First Tool", with a menu bar.
        Begin("Starship Parameters", &my_tool_active, ImGuiWindowFlags_MenuBar);
        ImGui::SetWindowSize(ImVec2((float)rightSide/2, (float)bottomSide/3));
        // Edit a color (stored as ~4 floats)
        //ColorEdit4("Color", my_color);

        // Plot some values
        
        PlotLines("Height", dat, sizeof(dat));

        // Display contents in a scrolling region
        TextColored(ImVec4(1,1,0,1), "Altitude");
        for (auto b : starship.ship.prsInstances) {
            ImGui::Text("Alt@ [%d m]", Alt());
        }
       
        BeginChild("Controls");
        ImGui::SliderInt("Thrust [0-15]", &force, 0, 15);
        ImGui::SliderInt("Thrust Angle", &angle, -30,30);
        ImGui::Checkbox("Burners", &burner_on);
        starship.burners.hidden = !burner_on;
        if (!burner_on) force = 0;
        if (ImGui::Button("Redo")) {
            starship.reset();
        }
        EndChild();
        
        End();
    }
    
   
    void RenderGui(float dt) {
        if (gui.Visible()) {
            GuiStarts();
                MyFirstToolWindow(dt);
            GuiEnds();
        }
    }
#endif // !NO_IMGUI

    void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (gob->is(starship.ship)) {
        //for 2D model its not required//    glRotatef(90, 1, 0, 0);
        }

        if (gob->is(starship.burners)) {
            starship.burners.pos.x = starship.ship.getInstancePtr(0)->physBodyPtr->GetPosition().x* P2S - rightSide/2;
            starship.burners.pos.y = starship.ship.getInstancePtr(0)->physBodyPtr->GetPosition().y* P2S - bottomSide/2 + 50;
        }
#ifndef NO_IMGUI
        if (gob->is(gui)) RenderGui(deltaT);
#endif // !NO_IMGUI
        if (gob->is(dbglayer)) {
            world->DrawDebugData();
        }
    }

    GameObject dbglayer;
    
    int Alt() {
        float ht = (933-starship.ship.getInstancePtr(0)->physBodyPtr->GetPosition().y* P2S - bottomSide/2)/10;
        return ht;
    }
    
    bool Kee(int i1, char large) {
        char small = large + 32;
        return (i1 == small || i1 == large || i1 - AL_KEY_ALPHA == small || i1 - AL_KEY_ALPHA == large );
    }
    
	virtual void processInput(PEG::CMD* p, float deltaT) {
        if (!starship.burners.hidden) {
            float angR = (angle+90)/FACTOR_RADIANS_DEGREES;
            float fx = force*cos(angR);
            float fy = force*sin(angR);
            starship.burners.JuiceSpeed = 123 + 50 * rndm(0.0, 1.0);
            starship.ship.getInstancePtr(0)->Thrust(f2(-fx, -fy));
            //starship.ship.getInstancePtr(0)->rot- ->Torque(-angle/20);
            starship.burners.pos.x = starship.ship.getInstancePtr(0)->physBodyPtr->GetPosition().x * P2S;
            starship.burners.pos.y= starship.ship.getInstancePtr(0)->physBodyPtr->GetPosition().y * P2S;
            starship.burners.rot.z = angle;
        }
        if (p->command == CMD_KEYDOWN) {
            if (Kee(p->i1,'W')) wireframe = !wireframe;
            if (Kee(p->i1,'G')) gui.hidden = !gui.hidden;
            if (Kee(p->i1,'D')) dbglayer.hidden = !dbglayer.hidden;
            if (Kee(p->i1,'B')) starship.burners.hidden = !starship.burners.hidden;
         }
        pushDat(Alt());
 	}
    
    StarShip starship;
    int BaseLineHeight = 115;
    
	virtual void Init(char* path) {
        memset(dat,0,sizeof(dat));
        landscape = true;
		AlInit(STANDARD_2D, "SN11");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		InitPhysics();
        
		PhysAddGroundWithWalls(BaseLineHeight);
        force = 0;
		AddResource(&background, "bg_p", "bocachica.jpg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        starship.LoadIn(this);
        AddResource(&gui, "gui");
        output.pushP(CMD_SNDSET0, $ "pop.wav");
        AddResource(&dbglayer,"")->hidden = true;
        
   }
};
