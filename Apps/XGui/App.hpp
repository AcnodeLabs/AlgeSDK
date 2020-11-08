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
		ImGui::StyleColorsClassic();
		
		}

	void processInput(PEG::CMD* p, float deltaT) { 
		if (p->command == CMD_SCREENSIZE) {
		}
	}

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		
		if (gob->is(background)) {
			ImGui::ShowDemoWindow();
		}
	}

};
