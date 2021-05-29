//#include <CBaseV1_2.h>
// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/

#ifndef NO_IMGUI
using namespace ImGui;
#endif
#include "Starship.hpp"
#include "Box2DebugDraw.hpp"
#include "StarShipAppGui.hpp"

class /*SN11 Main Box2D*/ App : public AlgeApp {

    GameObject background, dbglayer;
    StarShip starship;
    StarShipAppGui gui;
    DataBuffer bufHeight;
    
public:

    void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (gob->is(gui.gob)) gui.RenderGui(deltaT,rightSide,bottomSide, bufHeight, starship);
        if (gob->is(dbglayer)) {
            world->DrawDebugData();
        }
    }
  
    bool Kee(int i1, char large) {
        char smal = large + 32;
        return (i1 == smal || i1 == large || i1 - AL_KEY_ALPHA == smal || i1 - AL_KEY_ALPHA == large );
    }
    
	virtual void processInput(PEG::CMD* p, float deltaT) {
        
        starship.Update(0,deltaT);
        
        if (p->command == CMD_KEYDOWN) {
            if (Kee(p->i1,'W')) wireframe = !wireframe;
            if (Kee(p->i1,'G')) gui.gob.hidden = !gui.gob.hidden;
            if (Kee(p->i1,'D')) dbglayer.hidden = !dbglayer.hidden;
            if (Kee(p->i1,'B')) starship.burners.hidden = !starship.burners.hidden;
         }

        bufHeight.pushDat(starship.Alt());
 	}
    
    
    int BaseLineHeight = 115;
    
	virtual void Init(char* path) {
        bufHeight.clear();
        landscape = true;
		AlInit(STANDARD_2D, "SN11");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		InitPhysics();
        
		PhysAddGroundWithWalls(BaseLineHeight);
        
		AddResource(&background, "bg_p", "bocachica.jpg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        starship.LoadIn(this);
       // AddResource(&starship.ship, "DSC5164");
        AddResource(&gui.gob, "gui");
        output.pushP(CMD_SNDSET0, $ "pop.wav");
        AddResource(&dbglayer,"")->hidden = true; 
        
        starship.reset();
   }
};
