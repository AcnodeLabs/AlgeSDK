// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: IvanK Box2D Impulse
   http://lib.ivank.net/demos/box2D.html
*/

class /*IvanK Box2D*/ App : public AlgeApp {

	GameObject winter2;
	GameObject boxes;
	GameObject balls;
	b2PolygonShape polygon;
	b2CircleShape circle;
	b2FixtureDef bxFixDef, blFixDef;
	b2BodyDef bodyDefBall;
	b2BodyDef bodyDefBox;

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
		world->Step(deltaT, 3,3);
		world->ClearForces();
	}


	void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {

		gob->rotatefirst = false;

		if (gob->modelId == boxes.modelId || gob->modelId == balls.modelId) {
	//		PhysUpdatePrsOf(gob, instanceNo);
		}
	}

#define numBalls 50
#define numBoxes 50
#define num_max 50

	b2Vec2 iUp;
	
	virtual void Init(char* path) {

		alInit(STANDARD);
		output.pushP(CMD_TITLE, $ "IvanK Box2D", 0);
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		
		//Initialize Physics
		world = new b2World(b2Vec2(0, 10));
	//	world->SetDebugDraw(&xDebugDraw);
//		xDebugDraw.SetFlags(-1);
	//	xDebugDraw.Setup(originX, originY, 0.01);
		
		Phys2DWallIt();// Make Lt Wall Bottom Ground Rt Wall as per 2D view
		
		iUp.x = 0;
		iUp.y = -2;

		AddResource(&winter2, "winter2"); // 512 pixels = 5.12 meters
		
		AddResource(&boxes, "box");// , 1, PhysBox);  // 0.25 meters
		AddResource(&balls, "bigball");//, 1, PhysCircle);//0.25 meters

		polygon.SetAsBox(20 * S2P, 20 * S2P); //20 is size from alx
		circle.m_radius = 20 * S2P;//20 is size from alx

		bxFixDef.shape = &polygon;
		blFixDef.shape = &circle;

		bxFixDef.density = 1;
		blFixDef.density = 1;

		bxFixDef.restitution = .15;
		blFixDef.restitution = .5;

		bodyDefBall.type = b2_dynamicBody;
		bodyDefBox.type = b2_dynamicBody;

		char szuuid[64];

		PosRotScale px[num_max];
		b2Body* px_body[num_max];

		for (int i = 0; i < numBoxes; i++) {
			
			float rndScale = 1.;// 0.5 + randm();
			float box_hh = 20 * rndScale;
			float box_hw = 20 * rndScale;
		
			polygon.SetAsBox(box_hh * S2P, box_hw * S2P);
			bodyDefBox.position.Set(randm() * 7, randm() * 5);

			px_body[i] = world->CreateBody(&bodyDefBox);
			b2FixtureDef* fixDef = &bxFixDef;
			px_body[i]->CreateFixture(fixDef);

			px[i].physBodyPtr = px_body[i];
			px[i].scale = rndScale;//?
			px[i].pos.x = bodyDefBox.position.x * P2S;
			px[i].pos.y = bodyDefBox.position.y * P2S;
			px[i].m_height = 2*box_hh;
			px[i].m_width = 2*box_hw; // == ball_rad = 20 in this case
			
			//bm[i].userId = i;

			sprintf(szuuid, "box#%d", i); 
			px[i].UUID = string(szuuid);
			boxes.AddInstance(px[i]);
			
		}

		PosRotScale pl[num_max];
		b2Body* pl_body[num_max];

		for (int i = 0; i < numBalls; i++) {

			float rndScale = 1.0;// 0.5 + randm();
			float ball_rad = 20;

			circle.m_radius = 20 * S2P * rndScale;
			bodyDefBall.position.Set(randm() * 7, randm() * 5);
			pl_body[i] = world->CreateBody(&bodyDefBall);

			b2FixtureDef* fixDef = &blFixDef;
			pl_body[i]->CreateFixture(fixDef);

			pl[i].physBodyPtr = pl_body[i];
			pl[i].scale = rndScale;//?
			pl[i].pos.x = bodyDefBall.position.x * P2S;
			pl[i].pos.y = bodyDefBall.position.y * P2S;
			pl[i].m_height = 2 * ball_rad;
			pl[i].m_width = 2 * ball_rad;

			sprintf(szuuid, "ball#%d", i);
			pl[i].UUID = string(szuuid);
			balls.AddInstance(pl[i]);

		}

	}

};
