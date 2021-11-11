//#include <CBaseV1_2.h>
// Copyright (c) 2018 AcnodLabs Inc

using namespace ImGui;


#include "../Tetris/xtetris.hpp"


class /*Tetris*/ App : public AlgeApp {

	GameObject skydome, gui;

public:

    bool my_tool_active = true;
    float my_color[4];
    void MyFirstToolWindow(float dt) {
        // Create a window called "My First Tool", with a menu bar.
        Begin("XFs Flight Sim", &my_tool_active, ImGuiWindowFlags_MenuBar);

        // Edit a color (stored as ~4 floats)
        //ColorEdit4("Color", my_color);

        // Plot some values
        const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
        PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

        // Display contents in a scrolling region
        TextColored(ImVec4(1,1,0,1), "Important Stuff");
        BeginChild("Scrolling");
        ImGui::Text("FPS %.2f", 1.0/dt);
        ImGui::SliderInt("Impulse", &force, 1, 10);
        
        EndChild();
        End();
    }
    int force;
   
    void RenderGui(float dt) {
        if (gui.Visible()) {
            GuiStarts();
                MyFirstToolWindow(dt);
            ImGui::ShowDemoWindow();
            GuiEnds();
        }
    }
    
    void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (gob->is(gui)) RenderGui(deltaT);
    }

	virtual void processInput(PEG::CMD* p, float deltaT) {
        
        if (p->command == CMD_KEYDOWN) {
            if (p->i1 == ' ') gui.hidden = !gui.hidden;
        }
        
        
        if (p->command == CMD_TOUCH_START) {
            gui.hidden = false;
        }
	}

	virtual void Init(char* path) {
        
		AlInit(STANDARD_2D, "XFs Flight Sim");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		InitPhysics();
		
		AddResource(&skydome, "skydome", "skydome.jpg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        AddResource(&gui, "gui");
        gui.Hide();
   

	}
};
