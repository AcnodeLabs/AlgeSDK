// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/

class /*IvanK Box2D*/ App : public AlgeApp {

	GameObject winter2, boxes, balls;

public:

    virtual i2 getBackgroundSize() {
		return i2(512, 256).twice();
    }

	virtual void processInput(PEG::CMD* p, float deltaT) {
        if (p->command == CMD_TOUCH_START) for (auto b : touched_bodies) {
            b->Impulse(f2(0, -4));
            if (b->UUID.find("ball")!=string::npos)
                b->color = f3(randm(),randm(),randm());
        }
	}

	virtual void Init(char* path) {
		AlInit(STANDARD_2D, "IvanK Box2D");
        wireframe= true;
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		InitPhysics();
		PhysAddGroundWithWalls();
		
		AddResource(&winter2, "winter2");
        AddResourceEx(&boxes, "box", 20, false, 1, 0.1);//false::Polygon/Box
		AddResourceEx(&balls, "bigball", 20, true, 1, 0.3);//true:Circle
	}

};
