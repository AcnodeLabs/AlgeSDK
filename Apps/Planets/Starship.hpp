// Copyright (c) 2018 AcnodLabs Inc

/* 
 ALGE SDK JD4 Demo :: PoppingTime
 The Assets Folder Name is PoppingTime.Assets,
 macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
 */

#include "SolarDb.hpp"



class Burners : public GameObject {
public:
    void LoadIn(AlgeApp* that) {
        that->AddResource(this, "burn", "burn", 1);
    }
};

class ShipAttitudeController {
public:
    int burner_rotz = 0;
    int ship_rotz = 0;
    int burner_rotx = 0;
    int ship_rotx = 0;
    
    void SetZTilt(int angle) {
        burner_rotz = angle;
        ship_rotz = angle;
    }
    void SetXTilt(int angle) {
        burner_rotx = angle;
        ship_rotx = angle;
    }
    
    int xx =0;
    
    void Transform(char thing, GameObject& obj) {
        if (thing=='b') {
            obj.rot.y = burner_rotz - 90;
            obj.rot.x = burner_rotx ;
        }
        if (thing=='s') {
            obj.rot.y = ship_rotz;
            obj.rot.x = ship_rotx;
        }
    }
        
};


class StarShip {
public:
    Burners burners;
    ShipAttitudeController controls;
    GameObject ship;
    b2Transform initialTransform;
    AlgeApp* thiz;
    void LoadIn(AlgeApp* that) {
        thiz = that;
        float density = 1.1;
        float restitution = 0.1;
        that->AddResourceEx(&ship, "Starship/DSC5164", "Starship/DSC5164", 1, false, /*oSize*/0.1, density, restitution);//false::Polygon/Box
        burners.LoadIn(that);
        ship.AddChild(&burners);
    //    burners.JuiceType = JuiceTypes::JUICE_ROTY;
    //    burners.JuiceSpeed = 123.123;
        burners.hidden = true;
        reset();
    }
    
    void reset() {
        ship.getInstancePtr(0)->physBodyPtr->SetTransform(b2Vec2(thiz->rightSide*0.5*S2P, 0), 0);
     }
    
};

class AWindow {
public:
    GameObject gui;
    void Init(AlgeApp* that) {
        that->AddResource(&gui, "gui");
    }

    void Update(GameObject* check, float deltaT) {
        if (check->is(gui) && !gui.hidden)
        {
        }
    }
};
