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
		
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		AddResource(&background, "juices", 
			"green_natural.jpg", 
			XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN
			);
	//	ImGui::StyleColorsClassic();
		output.pushP(CMD_TOAST, $ "hello,", $ "hi");
		}

    i2 getBackgroudSize() {
        return size_imac_4k;
    }
    
	void processInput(PEG::CMD* p, float deltaT) { 
		if (p->command == CMD_SCREENSIZE) {
		}
	}
	bool my_tool_active;
	float my_color[4];
	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		
		if (gob->is(background)) {
			// Create a window called "My First Tool", with a menu bar.
			ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
					if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
					if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			// Edit a color (stored as ~4 floats)
			ImGui::ColorEdit4("Color", my_color);

			// Plot some values
			const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
			ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

			// Display contents in a scrolling region
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
			ImGui::BeginChild("Scrolling");
			for (int n = 0; n < 50; n++)
				ImGui::Text("%04d: Some text", n);
			ImGui::EndChild();
			ImGui::End();
		}
	}

};
