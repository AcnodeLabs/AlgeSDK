// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
   The Assets Folder Name is PoppingTime.Assets,
   macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
*/
#include  "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"

class App : public AlgeApp {

	vector<GameObject*> planets;
	
	GameObject mercury, venus, earth, moon, mars, jupiter, saturn, uranus, neptune, pluto;
	GameObject voyager, starman;
	GameObject satrings;
	
	int scene, nLoops;
	int pnum;
	int pnum_max;
public:
	
	virtual i2 getBackgroundSize() { return size_nokia5; }
	
	void AddPlanet(GameObject& pl, string name, int scale = 200) {
		planets.push_back(&pl);
		with AddResource(&pl, name.c_str(), scale);
		_.JuiceType = JuiceTypes::JUICE_ROTY;
		_.JuiceSpeed *= 2;
		_.Hide();
		_with
		pnum++;
	}

	virtual void Init(char* path) {

		nLoops = 100;
		pnum = 0;

		AlInit(STANDARD);
		
		//glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);

		AddPlanet(mercury, "mercury");
		AddPlanet(venus, "venus");
		AddPlanet(earth, "earth");
		AddPlanet(moon, "moon");
		AddPlanet(mars, "mars");
		AddPlanet(jupiter, "jupiter");
		AddPlanet(saturn, "saturn");
		AddPlanet(uranus, "uranus");
		AddPlanet(neptune, "neptune");
		AddPlanet(pluto, "pluto");
		AddPlanet(voyager, "voyager", 1);

		pnum_max = pnum;
		pnum = 6;
		planets.at(6)->Show();
			
		with AddResource(&satrings, "satrings", 500);
		_.JuiceType = JuiceTypes::JUICE_ROTY;
		_.JuiceSpeed *= 2;
		_.Hide();
		_with
		
		with AddResource(&starman, "starman1", 500);
		_.JuiceType = JuiceTypes::JUICE_ROTY;
		_.JuiceSpeed *= 2;
		_.Hide();
		_with

	}

	
	virtual void onActionComplete(GameObject* obj) {
		
	}
	virtual void processInput(PEG::CMD* cmd, float deltaT) {
		if (cmd->command == CMD_TOUCH_START) {
			planets[pnum]->Hide();
			pnum++;
			if (pnum >= pnum_max) pnum = 0;
			planets[pnum]->Show();
		}
	}
	float a;

	float zRot;

	virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
		
		if (pnum == 6) satrings.Show(); else satrings.Hide();

		if (gob->is(satrings)) {
			glRotatef(90, 1, 0, 0);
			glRotatef(-20, 0, 1, 0);
			glDisable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
		}

		if (gob->is(*planets[pnum])) {
			glEnable(GL_CULL_FACE);
			glRotatef(180, 1, 0, 0);
			glRotatef(-20, 0, 1, 0);
		}
	}
	
	~App() {
	}
};

