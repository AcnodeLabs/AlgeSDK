//#include <CBaseV1_2.h>
// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/
using namespace ImGui;

class /*IvanK Box2D*/ App : public AlgeApp {

	GameObject winter2, boxes, balls, gui;

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
        ImGui::SliderInt("Impulse", &force, 1, 10);
        
        for (auto b : boxes.prsInstances) {
            ImGui::Text("Box@ [%.0f,%.0f]", b.pos.x,b.pos.y);
        }
        EndChild();
        End();
    }
    int force;
   
    void RenderGui(float dt) {
        if (gui.Visible()) {
            GuiStarts();
                MyFirstToolWindow(dt);
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
           bool impulsed = false;
            for (auto b : touched_bodies) {
                b->Impulse(f2(0, -force));
               // if (b->UUID.find("ball")!=string::npos) b->color = f3(randm(),randm(),randm());
                impulsed = true;
            }
            gui.hidden = false;
        }
	}

	virtual void Init(char* path) {
        landscape = true;
		AlInit(STANDARD_2D, "IvanK Box2D");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		InitPhysics();
		PhysAddGroundWithWalls();
        force = 2;
		AddResource(&winter2, "winter2", "winter2.jpg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        
        gui.Hide();
        //AddResource(&winter2, "winter2", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        float oSize = (bottomSide - topSide)/ 30.0;// 30 balls could stack vertically
        oSize /= 20; //nullify alx size
        float density = 1.0;
        float restitution = 0.3;
        AddResourceEx(&boxes, "box", "box.jpg", 4, false, oSize, density, restitution);//false::Polygon/Box
        AddResourceEx(&balls, "bigball",99, true, oSize, density, restitution* 2.0);//true:Circle
        
        AddResource(&gui, "gui");
        
#ifdef  NO_BOX2D
		output.pushP(CMD_TOAST, $ "NO_BOX2D", $ "NO_BOX2D");
#else 
		output.pushP(CMD_TOAST, $ "BOX2D ENABLED", $ "BOX2D ENABLED");
#endif // ! NO_BOX2D


	}
};
