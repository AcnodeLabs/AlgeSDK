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

//    virtual i2 getBackgroundSize() {
//        return size_ipad_air.half().half();
//    }
    bool my_tool_active = true;
    float my_color[4];
    void MyFirstToolWindow() {
        // Create a window called "My First Tool", with a menu bar.
        Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
        if (BeginMenuBar())
        {
            if (BeginMenu("File"))
            {
                if (MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
                if (MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
                if (MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
         //       EndMenu();
            }
            EndMenuBar();
        }

        // Edit a color (stored as ~4 floats)
        ColorEdit4("Color", my_color);

        // Plot some values
        const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
        PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

        // Display contents in a scrolling region
        TextColored(ImVec4(1,1,0,1), "Important Stuff");
        BeginChild("Scrolling");
        for (int n = 0; n < 5; n++)
            ImGui::Text("%04d: Some text", n);
        EndChild();
        End();
    }
    
    void RenderGui() {
        if (gui.Visible()) {
            GuiStarts();
                MyFirstToolWindow();
            GuiEnds();
        }
    }
    
    void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        
    }

	virtual void processInput(PEG::CMD* p, float deltaT) {
        
        if (p->command == CMD_KEYDOWN) {
            if (p->i1 == ' ') gui.hidden = !gui.hidden;
        }
        
        
        if (p->command == CMD_TOUCH_START) {
            
			static string msg;
			f3 pos(p->i1,p->i2,0);
			msg = pos.str("tch:%.1f,%.1f,%.1f");
			
            bool impulsed = false;
            for (auto b : touched_bodies) {
                b->Impulse(f2(0, -4));
               // if (b->UUID.find("ball")!=string::npos) b->color = f3(randm(),randm(),randm());
                impulsed = true;
            }
            gui.hidden = !gui.hidden;
        }
	}

	virtual void Init(char* path) {
        landscape = true;
		AlInit(STANDARD_2D, "IvanK Box2D");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		InitPhysics();
		PhysAddGroundWithWalls();
		
		AddResource(&winter2, "winter2", "winter2.jpg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        AddResource(&gui, "gui");
        gui.Hide();
        //AddResource(&winter2, "winter2", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        float oSize = (bottomSide - topSide)/ 30.0;// 30 balls could stack vertically
        oSize /= 20; //nullify alx size
        float density = 1.0;
        float restitution = 0.3;
        AddResourceEx(&boxes, "box", "box.jpg", 4, false, oSize, density, restitution);//false::Polygon/Box
        AddResourceEx(&balls, "bigball",40, true, oSize, density, restitution* 2.0);//true:Circle

#ifdef  NO_BOX2D
		output.pushP(CMD_TOAST, $ "NO_BOX2D", $ "NO_BOX2D");
#else 
		output.pushP(CMD_TOAST, $ "BOX2D ENABLED", $ "BOX2D ENABLED");
#endif // ! NO_BOX2D


	}
};
