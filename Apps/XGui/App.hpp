// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: XGui
*/


class /*XGui*/ App : public AlgeApp { 
	
	GameObject background;

public:

		virtual void Init(char* path) {
		
		AlInit(STANDARD);
		SetTitle("XGui");
		
		AddDefaultCamera(Camera::CAM_MODE_2D,OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		AddResource(&background, "juices", 
			"green_natural.jpg", 
			XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN
			);
	//	ImGui::StyleColorsClassic();
	//	output.pushP(CMD_TOAST, $ "hello,", $ "hi");
		}
    
    i2 msize;
    
    i2 getBackgroudSize() {
        return msize;
    }

	bool done = false;
	void processInput(PEG::CMD* p, float deltaT) { 
		if (p->command == CMD_SCREENSIZE) {
            msize.x = p->i1;
            msize.y = p->i2;
		}
		if (p->command == CMD_YOUTUBE_SHOW) {
			if (!done) {
				output.pushP(CMD_TOAST, $ p->param1, $ "hi");
				done = true;
			}
		}

	}
	bool my_tool_active;
	float my_color[4];
	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		
		 {

			{
				static float f = 0.0f;
				static int counter = 0;
                
				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
                
			}
            
		}
	}

};
