// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: XGui
*/

extern void (*callBackIn)(string);
extern App game;



class /*XGui*/ App : public AlgeApp { 
	
	GameObject background, gui;

public:

		virtual void Init(char* path) {
		
		AlInit(STANDARD);
		SetTitle("Islamabad Vehicle Information ");
		
		AddDefaultCamera(Camera::CAM_MODE_2D,OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
            
            AddResource(&background, "juices",
                "chevy_volt.jpg",
                XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN
                );


            AddResource(&gui, "gui");
            gui.hidden = false;
            
            
             
		}
    
    i2 msize;
    i2 mou;
    
    i2 getBackgroudSize() {
        return msize;
    }

	bool done = false;
    
	void processInput(PEG::CMD* p, float deltaT) { 
		if (p->command == CMD_SCREENSIZE) {
            msize.x = p->i1;
            msize.y = p->i2;
		}

        if (p->command == CMD_REMOTE_COMMAND) {
            string data = string((char*) (p->param1));
            if (data.find("veh_regno_result") != string::npos) {
                strcpy(m_result, data.c_str()+17);
            }
        }
  	}

    char m_vehregno[128];
    char m_result[4096];

       
    void VehWindow(float dt) {
        
           static float f = 0.0f;
           static int counter = 0;
           
           ImGui::Begin("Vehicle Lookup");                          // Create a window called "Hello, world!" and append into it.

           ImGui::InputText("Enter Vehicle Reg No XX-NNN", m_vehregno,128,0,0,0);
           bool clicked = ImGui::Button("Go!");
           if (clicked) {
       //     netmsg.Post("veh_regno="+string(m_vehregno));
           }
           ImGui::Text("%s",m_result);

           //ImGui::Text("Screen Size = {%d x %d}", msize.x, msize.y);               // Display some text (you can use a format strings too)
           //ImGui::Text("Mouse Pos = {%d x %d}", mou.x, mou.y);               // Display some text
        
           //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
           //ImGui::Checkbox("Another Window", &show_another_window);

           //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
           //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

           //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
           //    counter++;
           //ImGui::SameLine();
           //ImGui::Text("counter = %d", counter);

           //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::SetWindowPos(ImVec2(0, 50), true);
        ImGui::End();
    }
  
	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (gob->is(gui) && !gui.hidden)
        {
            GuiStarts();
                VehWindow(deltaT);
            GuiEnds();
        }

	}

};
