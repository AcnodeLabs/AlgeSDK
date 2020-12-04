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
		
		AddDefaultCamera(Camera::CAM_MODE_2D);
		AddResource(&background, "juices", 
			"green_natural.jpg", 
			XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN
			);
		ImGui::StyleColorsClassic();
		
		}
    
    i2 msize;
    
    i2 getBackgroudSize() {
        return msize;
    }
    
	void processInput(PEG::CMD* p, float deltaT) { 
		if (p->command == CMD_SCREENSIZE) {
            msize.x = p->i1;
            msize.y = p->i2;
		}
	}

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		
		if (gob->is(background)) {
            ImGui::ShowDemoWindow();
		}
	}

};
