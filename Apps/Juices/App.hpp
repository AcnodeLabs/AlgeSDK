// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: Juices
   “A juicy game feels alive and responds to everything you do – 
   tons of cascading action and response for minimal user input. 
   It makes the player feel powerful and in control of the world, 
   and it coaches them through the rules of the game by constantly 
   letting them know on a per-interaction basis how they are doing.”
   (Quoteed from https://bit.ly/2A27Ke4)
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

	GameObject star;
	GameObject ring;
	GameObject *sel;
	
	int currentJuice;

public:

		virtual void Init(char* path) {
		
		currentJuice = 0;
		AlInit(STANDARD);
		SetTitle("Juices");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
	
        float scale = getBackgroundSize().x / 800.0;
		iit.Track(AddResource(&ring, "ab_city", scale));
	
		AddResource(&star, "adidas_ball", 100);
		iit.Track((GameObject*)ring.AddInstance(f2(originX - 100, originY)));
		iit.Track((GameObject*)ring.AddInstance(f2(originX + 100, originY)));
            star.JuiceSpeed = 10;
		//iit.clearPosofAll();
		sel = iit.First();
		//sel->pos = f3(originX, originY, 0.0);

		output.pushP(CMD_TOAST, $ "Juices are Effects applicable to single game object or its instance\nPress UP DOWN to change Object\nPress RT LT to change Effects (Juices)", 0);

	}

	string jn;
    CControls c;
    
	void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_KEYDOWN) {
			if (p->i1 == AL_KEY_RIGHT) {
				sel->pos.clear();
				sel = iit.Next();
				sel->pos = f3(originX, originY, 0.0);
			}
			if (p->i1 == AL_KEY_LEFT) {
                
			}
			if (p->i1 == AL_KEY_UP) {
				currentJuice++;
				if (currentJuice >= JuiceTypes::JUICES_END) currentJuice = 1;
				sel->JuiceType = currentJuice;
				jn = JuiceName(currentJuice);
			//	output.pushP(CMD_TOAST, $ jn.c_str(), 0);
			}
			if (p->i1 == AL_KEY_DOWN) {
				currentJuice--;
				if (currentJuice <= 1) currentJuice = 1;
				sel->JuiceType = currentJuice;
			}
		}
        
        if (p->command == CMD_TOUCH_START)
        switch (c.KROSS_(true, p->i1, p->i2)) {
            case KROSS_RIGHT:
				star.Show();
				star.NextJuice();
                break;
        }
        
	}

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		gob->rotatefirst = false;
        
	//	gob->applyTopLeftCorrectionWRTorigin = true;
	}

	virtual i2 getBackgroundSize() {
		return i2(1024, 1024);
	}
		


};
