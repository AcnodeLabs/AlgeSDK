// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/

class /*IvanK Box2D*/ App : public AlgeApp {

	GameObject winter2, boxes, balls;

public:

    virtual i2 getBackgroundSize() {
		return i2(1024, 512);
    }

	void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_TOUCH_START) for (auto b : touched_bodies) b->Impulse(f2(0, -2));		
	}

	virtual void Init(char* path) {
		AlInit(STANDARD_2D, "IvanK Box2D");
		
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		PhysicsInit();
		PhysAddGroundWithWalls();
		
		AddResource(&winter2, "winter2"); 
		AddResourceEx(&boxes, "box", 50, false, 1, 0.1);//false::Polygon/Box
		AddResourceEx(&balls, "bigball", 50, true, 1, 0.3);//true:Circle
	}

};
