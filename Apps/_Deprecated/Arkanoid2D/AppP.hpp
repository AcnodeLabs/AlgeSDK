// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD3 Demo :: Arkanoid2D
*/


constexpr float paddleWidth{ 60.f }, paddleHeight{ 20.f }, paddleVelocity{ 6.f };
constexpr float blockWidth{ 60.f }, blockHeight{ 20.f };
constexpr int countBlocksX{ 1 }, countBlocksY{ 5 };

class RoundGameObject : public GameObject
{
public:
	float ballRadius{ 10.f }, ballVelocity{ 250.f };

	f2 velocity{ -ballVelocity, -ballVelocity };

	RoundGameObject() {};

	RoundGameObject(float mX, float mY)
	{
        pos.x = mX; pos.y = mY;
	}

	bool didBallTouchWall(float deltaT, int rightSide, int bottomSide)
	{
		pos.x += velocity.x * deltaT;
		pos.y += velocity.y * deltaT;
		bool hit = false;

		if (left() < 0) {
			velocity.x = ballVelocity;
			hit = true;
		}
		else if (right() > rightSide) {
			hit = true;
			velocity.x = -ballVelocity;
		}

		if (top() < 0) {
			velocity.y = ballVelocity;
			hit = true;
		}
		else if (bottom() > bottomSide) {
			velocity.y = -ballVelocity;
			hit = true;
		}
		return hit;
	}

	float x() { return pos.x; }
	float y() { return pos.y; }
	float left() { return x() - ballRadius; }
	float right() { return x() + ballRadius; }
	float top() { return y() - ballRadius; }
	float bottom() { return y() + ballRadius; }
};
class RectGameObject : public GameObject {
public:
	float width;
};

class /*Arkanoid2D*/ App : public AlgeApp {
    
	GameObject bg;
	GameText bat;
	RoundGameObject bal, bal2; ResourceInf res;
	GameObject bric;
    CControls controls;
	CPhys2D phys;
	

	const int xMax = 500;
	const int xSpd = 10;
public:

    virtual i2 getBackgroundSize() {
        return size_iphone5s;//i2(512,512);//as per backbroung ab_city.jpg
    }

	void processInput(PEG::CMD* p, float deltaT) {
		PosRotScale prs;
		float moveDelta = 0.1;//10%
        
		if (p->command == CMD_KEYDOWN) {
			if (p->i1 == AL_KEY_RIGHT) {
		
			}
			if (p->i1 == AL_KEY_LEFT) {
			}
		}

		if (p->command == CMD_TOUCH_START) {
			int x = p->i1;
			int y = p->i2;
            int k = controls.KROSS_(true, x, y);
            
            if (k==KROSS_RIGHT) {
            }
            if (k==KROSS_LEFT) {
            }
		}
		if (p->command == CMD_TOUCH_END) {

		}
	}

#define ADJUST /1.0

	void Update(float deltaT) {
		phys.Step(deltaT);
	}

	virtual void onRenderComplete() {
	//	phys.DebugDraw(); not working
	}

	void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
		
		return;
		if (gob->modelId == bric.modelId) {
			RectGameObject* b = (RectGameObject*)bric.getInstancePtr(instanceNo);
			if (isCircleIntersectingRect(bal.pos.x, bal.pos.y, bal.ballRadius, b->pos.x, b->pos.y, blockWidth, blockHeight)) {
				if (bat.pos.x < bal.pos.x) bal.velocity.x = -bal.velocity.x;
				bal.velocity.y = -bal.velocity.y;
                output.pushP(CMD_SNDPLAY2);//blob.wav
			};
		}
		if (gob->modelId == bg.modelId) {
			//bg.rotatefirst = false;
		}

		if (gob->modelId == bat.modelId) {
			if (isCircleIntersectingRect(bal.pos.x, bal.pos.y, bal.ballRadius, bat.pos.x, bat.pos.y, bat.width, 20)) {
				if (bat.pos.x < bal.pos.x) bal.velocity.x = -bal.velocity.x;
				bal.velocity.y = -bal.velocity.y;
				output.pushP(CMD_SNDPLAY1);//wall.wav
			};
			bat.Update(deltaT);
		}

		static float r;
		if (gob->modelId == bal.modelId) {
			bal.rotatefirst = false;
			bal.rot.z += 1;
			if (bal.didBallTouchWall(deltaT, rightSide, bottomSide)) { /*output.pushP(CMD_SNDPLAY1);*/ }

		}
	}

	char bricTag[64];
	b2GLDraw dd;

	virtual void Init(char* path) {
		wireframe = true;
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
        //800 is width of ab_city, this scalefactor will strech ab_city as per width of backgroundsize
        float scalefactor_bg = getBackgroundSize().x / 800.;
        AddResource(&bg, "ab_city", scalefactor_bg);
		//phys.AddGround(f2(leftSide, bottomSide - 100), f2(rightSide, bottomSide- 100));
		
		
		phys.m_world->SetDebugDraw(&dd);
		uint32 flags = 0;
		flags |= b2Draw::e_shapeBit;
		flags |= b2Draw::e_jointBit;
		flags |= b2Draw::e_aabbBit;
		flags |= b2Draw::e_pairBit;
		flags |= b2Draw::e_centerOfMassBit;
		dd.SetFlags(flags);

		AddResource(&bal, "adidas_ball", 10.);
		bal.pos.x = originX;
		bal.pos.y = originY;
		bal2.pos.x = originX - 100;
		bal2.pos.y = originY - 100;
		phys.AddAsCircle(&bal, "ball");
	
		AddResource(&bal2, "adidas_ball", 10.);
		phys.AddAsRect(&bal2, "ball2");


		AddResource(&bat, "paddle");
		bat.pos.x = originX - 200;
		bat.pos.y = bottomSide - 50;
		phys.AddAsRect(&bat, "bat");

		AddResource(&bric, "brick", 1.0);
		
		PosRotScale prs;
		
		int n = 0;
		for (int x = leftSide + 100; x < rightSide - 50; x += 100) {
			prs.pos.x = x;
			prs.pos.y = topSide + 100;
			sprintf(bricTag, "bric%d", n++);
			phys.AddAsRect(bric.AddInstance(prs),bricTag);
			prs.pos.y += 50;
			sprintf(bricTag, "bric%d", n++);
			phys.AddAsRect(bric.AddInstance(prs), bricTag); 
			prs.pos.y += 50;
			sprintf(bricTag, "bric%d", n++);
			phys.AddAsRect(bric.AddInstance(prs), bricTag);
		}
	}

};
