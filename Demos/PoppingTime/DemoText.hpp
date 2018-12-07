// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
   The Assets Folder Name is PoppingTime.Assets,
   macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
*/


class App : public AlgeApp {
	
    GameObject bg, heli, score;
	
public:

	~App() {
		
	}

	virtual void onActionComplete(GameObject* obj) {
		if (obj->is(heli)) {
		}
	}

	virtual void processInput(PEG::CMD* cmd, float deltaT) {
		if (onTouched("heli")) {
		}			
	}
	
	int iScore = 0;

	virtual void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		
		if (gob->is(heli)) {
			static bool faceRight = false;
			bool moveRight = bg.posTouched().x > heli.pos.x;
			if (bg.wasTouched()) faceRight = moveRight;
			heli.rot.y = faceRight ? 180 : 0;
		}

		if (gob->is(score)) {
			glColor3f(iScore<5?1.0:0.0, iScore / 100, 0.0);
			std::ostringstream sc;
			sc << "Score : " << iScore;
			alPrint(sc.str().c_str());
		}

		if (gob->is(bg)) {
			bool moveRight = bg.posTouched().x > heli.pos.x;
		}

    }
	
	virtual void Init(char* path) {
		AlInit(STANDARD); 
		
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		
		score.pos.y = 0.05 * bottomSide;
		score.pos.x = 0.85 * rightSide;
		
		AddResource(&bg, "bg", 1.5);
        AddResource(&heli, "heli", 1);
		AddObject(&score);

		output.pushP(CMD_SNDSET0, $ "pop.wav");
		output.pushP(CMD_SNDPLAY0, $ "pop.wav",&nLoops);
   }

	int nLoops = 1;

	virtual i2 getBackgroundSize() { return size_ipad_air.half(); }
};

