// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: Juices
   “A juicy game feels alive and responds to everything you do – 
   tons of cascading action and response for minimal user input. 
   It makes the player feel powerful and in control of the world, 
   and it coaches them through the rules of the game by constantly 
   letting them know on a per-interaction basis how they are doing.”
   (Quoted from https://bit.ly/2A27Ke4)
*/


class InstanceIterator {
	static short idx;
	static short iidx;// instance
public:
	vector<GameObject*> list;

	InstanceIterator() {
		idx = 0;
		list.clear();
	}

	void Track(GameObject* item) {
		list.push_back(item);
	}

	GameObject* Next() {
		idx++;
		if (idx >= (list.capacity()-1)) idx = 0;
		GameObject* it = list.at(idx);
		it->hidden = false;
		return it;
	}

	void clearPosofAll() {
		for (auto it : list) {
			((PosRotScale*)it)->pos.clear();
			it->hidden = true;
		}
	}

	GameObject* First() {
		idx = 0;
		return list.at(idx);
	}
	// Example Test call : 	int testresult = InstanceIterator::Test(); should return 0 to pass
	static int Test() {
		GameObject a, b, c, d, e;
		InstanceIterator iit;
		iit.Track(&a); iit.Track(&b); iit.Track(&c); iit.Track(&d); iit.Track(&e);
		if (iit.First() != &a) return -1;
		if (iit.Next() != &b) return -2;
		if (iit.Next() != &c) return -3;
		if (iit.Next() != &d) return -4;
		if (iit.Next() != &e) return -5;
		if (iit.Next() != &a) return -6;
		return 0;
	}
	
};

short InstanceIterator::idx = -1;

class /*Juices*/ App : public AlgeApp { 
	
	InstanceIterator iit;

	GameObject objct;
	GameObject background;
	PosRotScale *sel;
	
	int currentJuice[2];

public:

		virtual void Init(char* path) {
		
		currentJuice[0] = 0;
		currentJuice[1] = 0;

		AlInit(STANDARD);
		SetTitle("Juices");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
	
      //  float scale = getBackgroundSize().x / 800.0;
		//iit.Track(
		AddResource(&background, "juices", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
		//);
		
		iit.Track(
			AddResource(&objct, "slice")
		);
		iit.Track((GameObject*)objct.AddInstance(f2(rightSide*0.25, bottomSide/2)));
		iit.Track((GameObject*)objct.AddInstance(f2(rightSide*0.75, bottomSide/2)));
		objct.getInstancePtr(0)->UUID = "LEFT";
		objct.getInstancePtr(1)->UUID = "RIGHT";
		objct.JuiceSpeed = 1;
		sel = iit.First();
		resetPosRotSpeed(0);
		resetPosRotSpeed(1);
		output.pushP(CMD_TOAST, $ "Juices are Effects applicable to single game object or its instance\nPress UP DOWN to change Object\nPress RT LT to change Effects (Juices)", 0);
	}

	void resetPosRotSpeed(PosRotScale* p) {
		p->pos.y = bottomSide / 2;
		p->pos.z = 0;
		p->rot.x = 0;
		p->rot.y = 0;
		p->rot.z = 0;
		p->hidden = false;
	}
	
	void resetPosRotSpeed(int j) {
		PosRotScale* p = objct.getInstancePtr(j);
		resetPosRotSpeed(p);
		p->pos.x = rightSide * (j == 0 ? 0.25 : 0.75);
	}
	
	string jn;
    CControls c;
    
	void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_KEYDOWN) {

			if (p->i1 == AL_KEY_PLUS) {
				sel->JuiceSpeed *= 2;
				jn = "[x2] JuiceSpeed=" + std::to_string(sel->JuiceSpeed);
			}
			if (p->i1 == AL_KEY_MINUS) {
				sel->JuiceSpeed /= 2;
				jn = "[/2] JuiceSpeed=" + std::to_string(sel->JuiceSpeed);
			}

			if (p->i1 == AL_KEY_RIGHT) {
				sel = objct.getInstancePtr(1);
				resetPosRotSpeed(1);
				jn = "SELECTED RIGHT";
			}
			if (p->i1 == AL_KEY_LEFT) {
				sel = objct.getInstancePtr(0);
				resetPosRotSpeed(0);
				jn = "SELECTED LEFT";
			}
			if (p->i1 == AL_KEY_UP) {
				sel->JuiceType++;
				if (sel->JuiceType >= JuiceTypes::JUICES_END) {
					sel->JuiceType = 0;
					resetPosRotSpeed(sel);
				}
				jn = sel->UUID + ":" + JuiceName(sel->JuiceType);
			}
			if (p->i1 == AL_KEY_DOWN) {
				sel->JuiceType--;
				if (sel->JuiceType < 0) {
					sel->JuiceType = 0;
					resetPosRotSpeed(sel);
				}
			}
			output.pushP(CMD_TITLE, $ jn.c_str(), 0);
		}
        
		if (p->command == CMD_TOUCH_START) {
					
		}

	}

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		if (gob->is(background)) 
			glColor3f(0.8, 0.8, 0.8);//dim 80%
	}

};
