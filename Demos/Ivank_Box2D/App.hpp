// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/

class /*IvanK Box2D*/ App : public AlgeApp {

	GameObject winter2;
	GameObject boxes;
	GameObject balls;

public:

    virtual i2 getBackgroundSize() {
		return i2(1024, 512);//size_iphone5s;//i2(512,512);//as per backbroung ab_city.jpg
    }

	void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_TOUCH_START) {
			int x = p->i1;
			int y = p->i2;
			for (auto b : touched_bodies) {
				if (b->physBodyPtr->GetType() == b2_dynamicBody) {
					b->physBodyPtr->ApplyLinearImpulse(iUp, b->physBodyPtr->GetWorldCenter(), true);
				}
			}
		}
	}

	virtual void onRenderComplete() {
		world->DrawDebugData();
	}

	void Update(float deltaT) {
		if (world) {
			world->Step(deltaT, 3, 3);
			world->ClearForces();
		}
	}


	void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {

		gob->rotatefirst = false;

		if (gob->modelId == boxes.modelId || gob->modelId == balls.modelId) {
			if (instanceNo = 3) gob->getInstancePtr(instanceNo)->scale = 1.1;
		}
	}





	b2Vec2 iUp;
	
	virtual void Init(char* path) {

		alInit(STANDARD);
		output.pushP(CMD_TITLE, $ "IvanK Box2D", 0);
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
	
		world = new b2World(b2Vec2(0, 10));
			
		Phys2DWallIt();// Make Lt Wall Bottom Ground Rt Wall as per 2D view
		
		iUp.x = 0;
		iUp.y = -2;

		AddResource(&winter2, "winter2"); // 512 pixels = 5.12 meters
		AddResource(&boxes, "box");// , 1, PhysBox);  // 0.25 meters
		AddResource(&balls, "bigball");//, 1, PhysCircle);//0.25 meters

		i2 obj_size(20, 20);

		polygon.SetAsBox(obj_size.x * S2P, obj_size.y * S2P); //20 is size from alx
		circle.m_radius = obj_size.x * S2P;//20 is size from alx

		bxFixDef.shape = &polygon;
		blFixDef.shape = &circle;

		bxFixDef.density = 1;
		blFixDef.density = 1;

		bxFixDef.restitution = .15;
		blFixDef.restitution = .5;

		bodyDefBall.type = b2_dynamicBody;
		bodyDefBox.type = b2_dynamicBody;

		AddMultiplePhysicalInstances(boxes, 99, obj_size);
		AddMultiplePhysicalInstances(balls, 99, obj_size);

		
	}

};
