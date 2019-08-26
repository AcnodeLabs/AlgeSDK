// Copyright (c) 2018 AcnodLabs Inc

//Clone of GoDot's Example found at https://docs.godotengine.org/en/3.1/getting_started/step_by_step/your_first_game.html

//////////////////////////////XTimer

// on device : respath = /data/user/0/com.acnodelabs.DodgeTheCreeps/files

class BiSprite {
	f3 MyPos;
	float heading; //0 to 180
	
public:
	GameObject flip, flop;

	void LoadIn(AlgeApp* thiz, string prefix) {
		thiz->AddResource(&flip, prefix + "1");
		thiz->AddResource(&flop, prefix + "2");
		flip.hidden = false;
		flop.hidden = false;
		heading = rndm(100, 360);
		MyPos.x = rndm(thiz->leftSide, thiz->rightSide);
		MyPos.y = rndm(thiz->topSide, thiz->bottomSide);
	}

	bool toggle;
	float timeVar;

	bool IsItYou(GameObject* g) {
		return ( g == &flip ||  g == &flop );
	}

	void Update(float dt, AlgeApp* app) {
		timeVar += dt;
		if (timeVar > 0.5) {
			timeVar = 0.0;
			toggle = !toggle;
			if (toggle) {
				flip.hidden = true;
				flop.hidden = false;
			} else 	{
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

class Sprite {
	f3 MyPos;
	char UDLR = ' ';
	GameObject playerGrey_up1, playerGrey_up2, playerGrey_walk1, playerGrey_walk2;
public: 
	
	void SetIntent(char dir) {
		UDLR = dir;
	}

	bool IsItYou(GameObject* g) {
		return (g == &playerGrey_up1 ||	g == &playerGrey_up2 || g == &playerGrey_walk1 || g == &playerGrey_walk2 );
	}

	void SetVisibility() {
		playerGrey_up1.hidden = true;
		playerGrey_up2.hidden = true;
		playerGrey_walk1.hidden = true;
		playerGrey_walk2.hidden = true;
		
		if ((UDLR == 'U' || UDLR == ' ') &&  toggle) {
			playerGrey_up1.hidden = false; playerGrey_up1.rot.z = 0;
			return;
		}
		if ((UDLR == 'U' || UDLR == ' ') && !toggle) {
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
		
		const int dd = 10;

		if (UDLR == 'U') 
			SetPos(f3(MyPos.x,		MyPos.y>0?MyPos.y-dd:MyPos.y,					MyPos.z));
		if (UDLR == 'D')
			SetPos(f3(MyPos.x,		MyPos.y<app->bottomSide?MyPos.y+dd:MyPos.y,		MyPos.z));
		if (UDLR == 'L')
			SetPos(f3(MyPos.x>0?MyPos.x-dd:MyPos.x,					MyPos.y, MyPos.z));
		if (UDLR == 'R')
			SetPos(f3(MyPos.x<app->rightSide?MyPos.x+dd:MyPos.x,	MyPos.y, MyPos.z));
		
		if (timeVar >= 1.0) {
			timeVar = 0.0;
			toggle = !toggle;
		}

		SetVisibility();
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

	f3 GetPos() { return MyPos; }

	void WasHit() {
		playerGrey_up1.JuiceType = JuiceTypes::JUICE_SCALE_IN;
		UDLR = ' ';
	}
	
	float playerGrey_up1_width = 10.;
	
	float GetWidth() { return playerGrey_up1_width; }

	void LoadIn(AlgeApp* thiz, string tagUpward, string tagRightward) {
		thiz->AddResource(&playerGrey_up1, tagUpward+"1");
		thiz->AddResource(&playerGrey_up2, tagUpward+"2");
		thiz->AddResource(&playerGrey_walk1, tagRightward+"1");
		thiz->AddResource(&playerGrey_walk2, tagRightward+"2");
		SetPos(f3(thiz->rightSide / 2, thiz->bottomSide / 2, 0));
		playerGrey_up1.pos = MyPos;	
		playerGrey_up1_width = playerGrey_up1.getOwnRect().Right - playerGrey_up1.getOwnRect().Left;
	}
};


///TODO
///Flicker, Trail
class /*DodgeTheCreeps*/ App : public AlgeApp { 

	GameObject background;
	Sprite playerGrey;
	GameObject playerTrail;
	BiSprite enemyFlyingAlt[3], enemySwimming[3], enemyWalking[3];
	GameObject count_text;
	
public:

	void MakeTrail() {
		playerTrail.prsInstances.clear();
		return;
		PosRotScale bp;
		bp.CopyFrom((PosRotScale*)&playerGrey);
		
		for (int i = 0; i < 4; i++) {
			bp.scale = 1.0;
			playerTrail.AddInstance(bp);
		}
	}

	virtual void Init(char* path) {
		AlInit(STANDARD);
		SetTitle("DodgeTheCreeps");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		AddResource(&background, "bg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);

		//AddResource(&playerTrail, "playerGrey_up1", 1);
		//MakeTrail();

		playerGrey.LoadIn(this, "playerGrey_up", "playerGrey_walk");

		for_i(3)
			enemyFlyingAlt[i].LoadIn(this, "enemyFlyingAlt_");
			enemySwimming[i].LoadIn(this, "enemySwimming_");
			enemyWalking[i].LoadIn(this, "enemyWalking_");
		_for

		with AddObject(&count_text);
			_.scale = 2.0;
			_.pos.x = rightSide / 2;
			_.pos.y = bottomSide * 0.1;
		_with

		output.pushP(CMD_SNDSET0, $ "house.wav");
		output.pushP(CMD_SNDSET1, $ "gameover.wav");
		output.pushP(CMD_SNDPLAY0, $ "house.wav");
		
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

	
	//https://docs.google.com/spreadsheets/d/1_TFyagNzOVhD4MxVY3VLq7RzB8og0wDuWRb5HTW-KFg/edit#gid=0
	void trailLogic(float deltaT) {
		static int i = 0;
		static float trailVar = 0.0f;
		trailVar += deltaT;
		f3 p = playerGrey.GetPos();
		int w = playerGrey.GetWidth();

		for (int i = 0; i < int(playerTrail.prsInstances.size());i++) {
			float inv = 0.9 / sqrt(i+1);
			with (playerTrail.getInstancePtr(i));
				_.scale = sqrt(inv);
				p.x += (w /(i+1) );
				_.pos = p;
			_with
	 	}
	}

	
	void intersectLogic(GameObject* gob) {
		
		if (doObjectsIntersect((PosRotScale*)& playerGrey,gob) ){
			timeVar = 0;
			output.pushP(CMD_SNDPLAY1, $ "gameover.wav");
			playerGrey.SetPos(f3(rightSide / 2., bottomSide / 2., 0.));
			playerGrey.WasHit();
		}
	}
	
	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		
		if (gob->is(count_text)) {
			string x = to_string(int(timeVar));
			glPushMatrix();
			text.PrintTextGl(x.c_str(), f3(0, 0, 0), 2);
			glPopMatrix();
		}

		if (gob->is(playerTrail)) {
			trailLogic(deltaT);
		}

		if (playerGrey.IsItYou(gob)) {
			playerGrey.Update(deltaT, this);
		}

		for_i(3)
			if (enemyFlyingAlt[i].IsItYou(gob)) {
				enemyFlyingAlt[i].Update(deltaT, this);
				intersectLogic(gob);
			}

			if (enemySwimming[i].IsItYou(gob)) {
				enemySwimming[i].Update(deltaT, this);
				intersectLogic(gob);
			}

			if (enemyWalking[i].IsItYou(gob)) {
				enemyWalking[i].Update(deltaT, this);
				intersectLogic(gob);
			}
		_for
	}

};
