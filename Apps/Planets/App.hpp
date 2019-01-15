// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD4 Demo :: PoppingTime
   The Assets Folder Name is PoppingTime.Assets,
   macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
*/
#include  "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"


// Elons's Advice: Aim to be Useful
// What ever is it that you are trying to create
// What will be the Utility Delta vs the State of the Art times how many people would effect
// maximize UtilityDelta * NumberOfPeople
// eg Wither SmallUtilityDelta * LargeNumberOfPeople OR LargeUtilityDelta * SmallNumberOfPeople
// OR     ::   LargeNumberOfPeople * LargeUtilityDelta
// Avoid:: SmallUtilityDelta && SmallNumberOfPeople

//Planets App : State of the Art App "C:\Program Files\BlueStacks\HD-RunApp.exe" -json "{\"app_icon_url\": \"\", \"app_name\": \"Solar Walk Free\", \"app_url\": \"\", \"app_pkg\": \"com.vitotechnology.SolarWalkFree\"}"


class App : public AlgeApp {

	vector<GameObject*> planets;
	GameObject mercury, venus, earth, moon, mars, jupiter, saturn, uranus, neptune, pluto;

	GameObject voyager, starman;
	GameObject satringsFr, satringsBk;
	
	int scene, nLoops;
	int pnum;
	int pnum_max;
public:
	
	virtual i2 getBackgroundSize() { return size_nokia5; }
	
	void AddPlanet(GameObject& pl, string name, int scale = 200) {
		planets.push_back(&pl);
		GameObject* g =  AddResource(&pl, name, scale);
		g->JuiceType = JuiceTypes::JUICE_ROTY;
		g->JuiceSpeed *= 2;
	//	_.Hide();
		
		pnum++;
	}

	virtual void Init(char* path) {

		nLoops = 100;
		pnum = -1;

		AlInit(STANDARD);
		
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		AddDefaultCamera(Camera::CAM_MODE_2D, ORIGIN_IN_TOP_LEFT_OF_SCREEN);

	
		AddPlanet(mercury, "mercury", 100 * 3);
		AddPlanet(venus, "venus", 90 * 3);
		AddPlanet(earth, "earth", 80 * 3);
		AddPlanet(moon, "moon", 70 * 3);
		AddPlanet(mars, "mars", 60 * 3);
		AddPlanet(jupiter, "jupiter", 50 * 3);
		AddPlanet(saturn, "saturn", 40 * 3);
		AddPlanet(uranus, "uranus", 30 * 3);
		AddPlanet(neptune, "neptune", 20 * 3);
		//AddPlanet(pluto, "pluto", 10 * 3);

		pnum_max = pnum;
					
		with AddResource(&satringsFr, "satrings", 500);
		_.JuiceType = JuiceTypes::JUICE_ROTY;
		_.JuiceSpeed *= 2;
		_.Hide();
		_with

		with AddResource(&satringsBk, "satrings", 500);
		_.JuiceType = JuiceTypes::JUICE_ROTY;
		_.JuiceSpeed *= 2;
		_.Hide();
		_with

		//w.e.f
		pnum = 0;
		planets.at(pnum)->Show();
	}
	
	PosRotScale graveyard;
	
	virtual void onActionComplete(GameObject* obj) {
		
	}
	virtual void processInput(PEG::CMD* cmd, float deltaT) {
		if (cmd->command == CMD_TOUCH_START) {
			planets[pnum]->JuiceType = JuiceTypes::JUICE_FLY_OUT;
			planets[pnum]->JuiceSpeed = 3;
			juice_sine_angle = 0; //ResetJuiceParameters //TODO add proper fn
			pnum++;
			sprintf(tit1, "#%d", pnum);
			SetTitle(tit1);
			
			if (pnum > pnum_max) pnum = 0;

			planets[pnum]->pos = f3(originX, originY, 0.0);
			planets[pnum]->Show();
			juice_sine_angle = 0;
			planets[pnum]->pos = f3(originX, originY, 0);
			planets[pnum]->JuiceType = JuiceTypes::JUICE_SCALE_IN;
			planets[pnum]->JuiceSpeed = 3;
		}
	}
	float a;
	
	char tit1[128];

	float zRot;

	virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
		
		if (pnum == 6) { 
			satringsFr.Show(); satringsBk.Show();
		} else { 
			satringsFr.Hide(); satringsBk.Hide();
		}

		if (gob->is(satringsFr)) {
			glRotatef(90, 1, 0, 0);
			glRotatef(-20, 0, 1, 0);
			glEnable(GL_DEPTH_TEST);
		}

		if (gob->is(satringsBk)) {
			glRotatef(-90, 1, 0, 0);
			glRotatef(20, 0, 1, 0);
			glEnable(GL_DEPTH_TEST);
		}


		if (gob->is(*planets[pnum])) {
			glRotatef(180, 1, 0, 0);
			glRotatef(-20, 0, 1, 0);
		}
	}
	
	~App() {
	}
};

