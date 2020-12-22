// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
   The Assets Folder Name is PoppingTime.Assets,
   macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
*/

struct v3 {
	float x, y, z;
};

struct triangle {
	v3 p[3];
};

struct mesh
{
	vector<triangle> tris;
};


class App : public AlgeApp {
	
    GameObject bg, heli, score;
	mesh meshCube;

public:

	~App() {
		
	}

	virtual void onActionComplete(GameObject* obj) {
		
	}

	virtual void processInput(PEG::CMD* cmd, float deltaT) {
					
	}
	
	int iScore = 0;

	virtual void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		
		if (gob->is(score)) {

			for (auto tri : meshCube.tris) {
				glColor3f(1, 1, 1);
				//std::ostringstream sc;
				//sc << "x" << iScore;
		
			}
			
		}

    }
	
	virtual void Init(char* path) {
		AlInit(STANDARD); 
		
		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);
		
		score.pos.y = 0.05 * bottomSide;
		score.pos.x = 0.85 * rightSide;
	
		AddObject(&score);
		
		meshCube.tris
			= {
			//SOUTH
			{ 0.0f, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 0.0f},
			{ 0.0f, 0.0f, 0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f},
			
			//EAST
			{ 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f},
			{ 1.0f, 0.0f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 0.0f, 1.0f},

			//NORTH
			{ 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 1.0f,		0.0f, 1.0f, 1.0f},
			{ 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 0.0f, 1.0f},

			//WEST
			{ 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f},
			{ 0.0f, 0.0f, 1.0f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f},

			//TOP
			{ 0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 1.0f,		1.0f, 1.0f, 1.0f},
			{ 0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,		1.0f, 1.0f, 0.0f},

			//BOTTOM
			{ 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f},
			{ 1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f, 0.0f}
			
		};

   }

	int nLoops = 1;

	virtual i2 getBackgroundSize() { return size_ipad_air.half(); }
};

