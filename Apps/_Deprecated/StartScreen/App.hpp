// Copyright (c) 2018 AcnodLabs Inc

/* 
 ALGE SDK JD4 Demo :: PoppingTime
 The Assets Folder Name is PoppingTime.Assets,
 macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
 */

#include  "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"

class App : public AlgeApp {
    
public:
    
	StartScreen ss;
    
    virtual void Init(char* path) {
        AlInit(STANDARD);
        AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		ss.LoadIn(this);
    }

	virtual void processInput(PEG::CMD* cmd, float deltaT) {
		static bool toogle = true;
		if (cmd->command == CMD_TOUCH_START) {
			toogle = !toogle;
			ss.SetVisible(toogle);
		}
    }
    
    virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
    }
    
    ~App() {
    }
};

