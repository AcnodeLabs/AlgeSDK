// Copyright (c) 2018 AcnodLabs Inc

/* 
 ALGE SDK JD4 Demo :: PoppingTime
 The Assets Folder Name is PoppingTime.Assets,
 macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
 */

#include  "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"

// Scrum Page https://scrumy.com/PoppingTime

//  	LoadMock(that,  /*TitleImage*/ "poppingtime", /*SettingsImage*/ "settings","pointer", "settings_icon");

class MockTest : public MockUpOne {
public:

};

class App : public AlgeApp {
    
public:
    
	MockTest pp;
    
    virtual void Init(char* path) {
        AlInit(STANDARD);
        AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		pp.LoadMock(this, "title", "settings", "pointer", "settings_icon");
    }

	virtual void processInput(PEG::CMD* cmd, float deltaT) {
        pp.processInput(cmd,deltaT);
    }
    
    virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
    }
    
    ~App() {
    }
};

