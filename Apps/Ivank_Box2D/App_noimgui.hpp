//#include <CBaseV1_2.h>
// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/

class /*IvanK Box2D*/ App : public AlgeApp {

	GameObject winter2, boxes, balls;

public:

    int force;
    
        
    void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {

    }

	virtual void processInput(PEG::CMD* p, float deltaT) {
        
        if (p->command == CMD_SCREENSIZE) {
            f2 size;
            size.x = p->i1;
            size.y = p->i2;
        }
        
        if (p->command == CMD_KEYDOWN) {

        }
        
        
        if (p->command == CMD_TOUCH_START) {
           bool impulsed = false;
            for (auto b : touched_bodies) {
                b->Impulse(f2(0, -force));
               // if (b->UUID.find("ball")!=string::npos) b->color = f3(randm(),randm(),randm());
                impulsed = true;
                
            }
        }
	}

	virtual void Init(char* path) {
        landscape = true;
		AlInit(STANDARD_2D, "IvanK Box2D");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		InitPhysics();
		PhysAddGroundWithWalls();
        force = 10;
		AddResource(&winter2, "winter2", "winter2.jpg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        
        //AddResource(&winter2, "winter2", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        float oSize = (bottomSide - topSide)/ 30.0;// 30 balls could stack vertically
        oSize /= 20; //nullify alx size
        float density = 1.0;
        float restitution = 0.3;
        AddResourceEx(&boxes, "box", "box.jpg", 44, false, oSize, density, restitution);//false::Polygon/Box
        AddResourceEx(&balls, "bigball",99, true, oSize, density, restitution* 2.0);//true:Circle
        
#ifdef  NO_BOX2D
		output.pushP(CMD_TOAST, $ "NO_BOX2D", $ "NO_BOX2D");
#else 
		output.pushP(CMD_TOAST, $ "BOX2D ENABLED", $ "BOX2D ENABLED");
#endif // ! NO_BOX2D


	}
};
