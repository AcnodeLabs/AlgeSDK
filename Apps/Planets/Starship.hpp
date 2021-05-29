// Copyright (c) 2018 AcnodLabs Inc

/* 
 ALGE SDK JD4 Demo :: PoppingTime
 The Assets Folder Name is PoppingTime.Assets,
 macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
 */



class Burners : public GameObject {
public:
    void LoadIn(AlgeApp* that) {
        that->AddResource(this, "burn", "burn", 1);
    }
    void Update(float torque, f3 _pos) {
        JuiceSpeed = 123 + 50 * rndm(0.0, 1.0);
        pos.set(_pos);
        rot.z = torque*1000;
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
    bool burner_on;
    float force;
    float torque;
    void LoadIn(AlgeApp* that) {
        thiz = that;
        float density = 1.1;
        float restitution = 0.1;
        that->AddResourceEx(&ship, "DSC5164", "DSC5164", 1, false, /*oSize*/0.1, density, restitution);//false::Polygon/Box
        burners.LoadIn(that);
        ship.AddChild(&burners);
        burners.JuiceType = JuiceTypes::JUICE_FLICKER;
        burners.JuiceSpeed = 123.123;
        burners.hidden = true;
        reset();
    }
    
    float Alt() {
        float ht = (933.0-ship.getInstancePtr(0)->physBodyPtr->GetPosition().y* P2S - thiz->bottomSide/2.)/10.;
        return ht;
    }
    
    void Update( float thrustAngle,float deltaT) {
        if (!burners.hidden) {
           //
            float angleRad = -ship.getInstancePtr(0)->physBodyPtr->GetAngle();
            burners.Update(torque, getEnginePos(angleRad));
            
            float ang = (angleRad+90)/FACTOR_RADIANS_DEGREES;
            float fx = force*cos(thrustAngle-90);
            float fy = force*sin(ang);
            ship.getInstancePtr(0)->Thrust(f2(0, -fy));
            float dfx = 0.01;
            if (fx>dfx) fx = dfx;
            if (fx< -dfx) fx = -dfx;
            ship.getInstancePtr(0)->physBodyPtr->ApplyTorque(torque,true);
            
        }
    }
    
    f3 getEnginePos(float angR) {
        float r = ship.m_height/2.0;
        float s = sin(angR);
        float c = cos(angR);
        float px = r*s+ ship.getInstancePtr(0)->physBodyPtr->GetPosition().x * P2S - thiz->rightSide/2.0;
        float py = r*c+ ship.getInstancePtr(0)->physBodyPtr->GetPosition().y * P2S - thiz->bottomSide/2.0;
        float pz = 0;
        return f3(px,py,pz);
    }
    
    void reset() {
        ship.getInstancePtr(0)->physBodyPtr->SetTransform(b2Vec2(thiz->rightSide*0.5*S2P, 0), 0);
        torque = 0;
        force = 2.0;
        burner_on = false;
        burners.hidden = true;
     }
    
};


