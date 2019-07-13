// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/

class /*IvanK Box2D*/ App : public AlgeApp {

	GameObject winter2, boxes, balls;

public:

//    virtual i2 getBackgroundSize() {
//        return size_ipad_air.half().half();
//    }

	virtual void processInput(PEG::CMD* p, float deltaT) {
        if (p->command == CMD_TOUCH_START) {
            for (auto b : touched_bodies) {
                printf("\ttch:%s",b->UUID.c_str());
                b->Impulse(f2(0, -20));
                if (b->UUID.find("ball")!=string::npos) b->color = f3(randm(),randm(),randm());
            }
        }
	}

	virtual void Init(char* path) {
        landscape = true;
		AlInit(STANDARD_2D, "IvanK Box2D");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		InitPhysics();
		PhysAddGroundWithWalls();
		
		AddResource(&winter2, "winter2", size_ipad_air.x);
        float oSize = (bottomSide - topSide)/ 30.0;// 30 balls could stack vertically
        oSize /= 20; //nullify alx size
        float density = 1.0;
        float restitution = 0.3;
        AddResourceEx(&boxes, "box", 50, false, oSize, density, restitution);//false::Polygon/Box
        AddResourceEx(&balls, "bigball",50, true, oSize, density, restitution* 2.0);//true:Circle
	}
};
