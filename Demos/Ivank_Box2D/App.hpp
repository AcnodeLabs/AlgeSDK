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
		
		PhysicsInit();
		PhysAddGroundWithWalls();
		
		AddResource(&winter2, "winter2"); 
		AddResourceEx(&boxes, "box", 99, i2(20, 20));
		AddResourceEx(&balls, "bigball", 99, i2(20, 20));
	}

};
