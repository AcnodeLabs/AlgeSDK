// Copyright (c) 2018 AcnodLabs Inc


class SpriteWithTwoFramesThatCanFreelyMove {
	f3 MyPos;
	float heading; //0 to 180
public:
	GameObject flip, flop;
	void LoadIn(AlgeApp* thiz, string prefix) {
		thiz->AddResource(&flip, prefix + "_1");
		thiz->AddResource(&flop, prefix + "_2");
		flip.hidden = false;
		flop.hidden = false;
		heading = rndm(100, 360);
		MyPos.x = rndm(thiz->leftSide, thiz->rightSide);
		MyPos.y = rndm(thiz->topSide, thiz->bottomSide);
	}
	bool toggle;
	float timeVar;

	bool IsItYou(GameObject* g) {
		return (
			g == &flip ||
			g == &flop
			);
	}

	void Update(float dt, AlgeApp* app) {
		timeVar += dt;
		if (timeVar > 0.5) {
			timeVar = 0.0;
			toggle = !toggle;
			if (toggle) {
				flip.hidden = true;
				flop.hidden = false;
			}
			else
			{
				flip.hidden = false;
				flop.hidden = true;
			}
		}
		
		float dy = 100 * dt * sin(heading / FACTOR_RADIANS_DEGREES);
		float dx = 100 * dt * cos(heading / FACTOR_RADIANS_DEGREES);
		MyPos.x += dx;
		MyPos.y += dy;
		if (MyPos.x < app->leftSide) MyPos.x = app->rightSide;
		if (MyPos.x > app->rightSide) MyPos.x = app->leftSide;
		if (MyPos.y < app->topSide) MyPos.y = app->bottomSide;
		if (MyPos.y > app->bottomSide) MyPos.y = app->topSide;
		flip.pos = MyPos;
		flop.pos = MyPos;
		flip.rot.z = heading;
		flop.rot.z = heading;
	}
};


class PlayerGrey {
	f3 MyPos;
	char UDLR = 'U';
	GameObject playerGrey_up1, playerGrey_up2, playerGrey_walk1, playerGrey_walk2;
public: 
	
	void SetIntent(char dir) {
		UDLR = dir;
	}

	bool IsItYou(GameObject* g) {
		return (
			g == &playerGrey_up1 ||
			g == &playerGrey_up2 ||
			g == &playerGrey_walk1 ||
			g == &playerGrey_walk2 
			);
	}

	void SetVisibility() {
		playerGrey_up1.hidden = true;
		playerGrey_up2.hidden = true;
		playerGrey_walk1.hidden = true;
		playerGrey_walk2.hidden = true;
		
		if (UDLR == 'U' &&  toggle) {
			playerGrey_up1.hidden = false; playerGrey_up1.rot.z = 0;
			return;
		}
		if (UDLR == 'U' && !toggle) {
			playerGrey_up2.hidden = false; playerGrey_up2.rot.z = 0;
			return;
		}
		if (UDLR == 'L' && toggle) {
			playerGrey_walk1.rot.y = 180;
			playerGrey_walk1.hidden = false;
			return;
		}
		if (UDLR == 'L' && !toggle) {
			playerGrey_walk2.rot.y = 180;
			playerGrey_walk2.hidden = false;
			return;
		}
		if (UDLR == 'R' && toggle) {
			playerGrey_walk1.rot.y = 0;
			playerGrey_walk1.hidden = false;
			return;
		}
		
		if (UDLR == 'R' && !toggle) {
			playerGrey_walk2.rot.y = 0;
			playerGrey_walk2.hidden = false;
			return;
		}
		
		if (UDLR == 'D' && toggle) {
			playerGrey_up1.hidden = false; playerGrey_up1.rot.z = 180;
			return;
		}
		if (UDLR == 'D' && !toggle) {
			playerGrey_up2.hidden = false; playerGrey_up2.rot.z = 180;
			return;
		}
	}

	bool toggle;
	float timeVar = 0;

	void Update(float dt, AlgeApp* app) {
		timeVar += dt;
		if (timeVar > 0.5) {
			timeVar = 0.0;
			toggle = !toggle;
		}
		SetVisibility();
		if (UDLR == 'U') 
			SetPos(f3(MyPos.x,		MyPos.y>0?MyPos.y-10:MyPos.y,					MyPos.z));
		if (UDLR == 'D')
			SetPos(f3(MyPos.x,		MyPos.y<app->bottomSide?MyPos.y+10:MyPos.y,		MyPos.z));
		if (UDLR == 'L')
			SetPos(f3(MyPos.x>0?MyPos.x-10:MyPos.x,					MyPos.y, MyPos.z));
		if (UDLR == 'R')
			SetPos(f3(MyPos.x<app->rightSide?MyPos.x+10:MyPos.x,	MyPos.y, MyPos.z));
	}

	void SetPos(f3 pos) {
		MyPos.x = pos.x;
		MyPos.y = pos.y;
		MyPos.z = pos.z;
		playerGrey_up1.pos = MyPos;
		playerGrey_up2.pos = MyPos;
		playerGrey_walk1.pos = MyPos;
		playerGrey_walk2.pos = MyPos;	
	}

	void LoadIn(AlgeApp* thiz) {
		thiz->AddResource(&playerGrey_up1, "playerGrey_up1");
		thiz->AddResource(&playerGrey_up2, "playerGrey_up2");
		thiz->AddResource(&playerGrey_walk1, "playerGrey_walk1");
		thiz->AddResource(&playerGrey_walk2, "playerGrey_walk2");
		SetPos(f3(thiz->rightSide / 2, thiz->bottomSide / 2, 0));
		playerGrey_up1.pos = MyPos;
		
	}
};

class /*DodgeTheCreeps*/ App : public AlgeApp { 

	GameObject background;
	PlayerGrey playerGrey;
	SpriteWithTwoFramesThatCanFreelyMove enemyFlyingAlt, enemySwimming, enemyWalking;

public:

		virtual void Init(char* path) {
		
		AlInit(STANDARD);
		SetTitle("DodgeTheCreeps");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		
		AddResource(&background, "bg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
		playerGrey.LoadIn(this);
		enemyFlyingAlt.LoadIn(this, "enemyFlyingAlt");
		enemySwimming.LoadIn(this, "enemySwimming");
		enemyWalking.LoadIn(this, "enemyWalking");

		}

	CControls c;
	
	void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_KEYDOWN) {

			if (p->i1 == AL_KEY_PLUS) {
			}
			if (p->i1 == AL_KEY_MINUS) {
			}

			if (p->i1 == AL_KEY_RIGHT) {
				playerGrey.SetIntent('R');
			}
			if (p->i1 == AL_KEY_LEFT) {
				playerGrey.SetIntent('L');
			}
			if (p->i1 == AL_KEY_UP) {
				playerGrey.SetIntent('U');
			}
			if (p->i1 == AL_KEY_DOWN) {
				playerGrey.SetIntent('D');
			}
		}
        
		if (p->command == CMD_TOUCH_START) {
					
		}

	}

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		if (playerGrey.IsItYou(gob)) {
			playerGrey.Update(deltaT, this);
			return;
		}
		if (enemyFlyingAlt.IsItYou(gob)) {
			enemyFlyingAlt.Update(deltaT, this);
			return;
		}
		if (enemySwimming.IsItYou(gob)) {
			enemySwimming.Update(deltaT, this);
			return;
		}
		if (enemyWalking.IsItYou(gob)) enemyWalking.Update(deltaT, this);
	}

};
