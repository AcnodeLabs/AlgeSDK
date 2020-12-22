// Copyright (c) 2019 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: LevelSelect
*/
#include "LevelSelector.hpp"

class App : public LevelSelector {
public:

    void Init(char* path) {
        AlInit(STANDARD);
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
	    LevelSelector::Init(path);
        unlock(1);
    }
    bool toggle = true;
    int currlevel = 1;
    void processInput(PEG::CMD* cmd, float deltaT) {
        
        if (cmd->command == CMD_KEYDOWN) {
            toggle = !toggle;
            if (toggle) slideOut(); else slideIn();
            unlock(currlevel);
        }

        
        if (cmd->command == LevelSelector::CMD_LEVELSELECT) {
            sz = std::to_string(cmd->i1) + "<< Level Selected!";
            SetTitle(sz.c_str());          
            currlevel = cmd->i1;
        }

        LevelSelector::processInput(cmd, deltaT);
    }

};