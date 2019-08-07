// Copyright (c) 2018 AcnodLabs Inc

/*
   ALGE SDK JD4 Demo :: PoppingTime
   The Assets Folder Name is PoppingTime.Assets,
   macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
*/
#include  "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"


#include <iostream>
#include <cmath>
// Elons's Advice: Aim to be Useful
// What ever is it that you are trying to create
// What will be the Utility Delta vs the State of the Art times how many people would effect
// maximize UtilityDelta * NumberOfPeople
// eg Wither SmallUtilityDelta * LargeNumberOfPeople OR LargeUtilityDelta * SmallNumberOfPeople
// OR     ::   LargeNumberOfPeople * LargeUtilityDelta
// Avoid:: SmallUtilityDelta && SmallNumberOfPeople

//Planets App : State of the Art App "C:\Program Files\BlueStacks\HD-RunApp.exe" -json "{\"app_icon_url\": \"\", \"app_name\": \"Solar Walk Free\", \"app_url\": \"\", \"app_pkg\": \"com.vitotechnology.SolarWalkFree\"}"

#define DEGTORAD 0.0174533
#define RADTODEG 57.2958

#include "SolarDB.hpp"

class Views {
	vector<PosRotScale> vintage_points[8];
	short i[8] = {0,0,0,0,0,0,0,0};
public:

	Views() {
		//venus
		vintage_points[1].push_back(PosRotScale({ 6660.3,-28.1,7029.0 }, { 2.0,958.4,0.0 }));
		vintage_points[1].push_back(PosRotScale({ 7314.7,-341.8,7483.1 }, { 38.5,944.0,0.0 }));
		vintage_points[1].push_back(PosRotScale({ 7490.3,70.1,7310.1 }, { 30.0,917.0,0.0 }));
		vintage_points[1].push_back(PosRotScale({ 7278.3,-35.3,7478.5 }, { 5.8,996.2,0.0 }));
		//earth
		vintage_points[2].push_back(PosRotScale({ 601.7,66.1,13270.9 }, { -3.4,879.0,0.0 }));
		vintage_points[2].push_back(PosRotScale({ 218.1,2.9,14278.5 }, { -3.0,880.6,0.0 }));
		vintage_points[2].push_back(PosRotScale({ 95.9,-2.6,14517.7 }, { 45.7,885.8,0.0 }));
		vintage_points[2].push_back(PosRotScale({ 219.4,-517.9,14030.3 }, { 35.5,891.0,0.0 }));
		//mars
		vintage_points[3].push_back(PosRotScale({ -11132.3,399.9,15091.1 }, { -2.9,821.4,0.0 }));
		vintage_points[3].push_back(PosRotScale({ -15362.0,181.3,15942.5 }, { -13.2,824.4,0.0 }));
		vintage_points[3].push_back(PosRotScale({ -15798.4,77.4,16096.8 }, { 23.0,767.0,0.0 }));
		vintage_points[3].push_back(PosRotScale({ -15829.5,498.9,15962.1 }, { -42.0,837.4,0.0 }));
	}

	void Next(int planetNum, Camera* aCamera, bool fwd = true) {
		int max = vintage_points[planetNum].size(); if (max == 0) return;
		if (fwd) { i[planetNum]++; if (i[planetNum] >= max) i[planetNum] = 0; } else { i[planetNum]--; if (i[planetNum] < 0) i[planetNum] = max - 1; }
		PosRotScale* p = &((vintage_points[planetNum])[i[planetNum]]);

		PosRotScale test;
		test.pos = aCamera->getPos();
		test.rot = aCamera->getRot();
		test.scale = aCamera->scale;
		aCamera->MoveAhead(100);
		//aCamera->transitionTo(test);
		//aCamera->PosRot({ p->pos.x, p->pos.y, p->pos.z }, { p->rot.x, p->rot.y, p->rot.z });
	}
};

class App : public AlgeApp {

	SolarDB db;
	vector<GameObject*> planets;
	DPad dpad;
//	DPointer dpointer;
	Views v;

	GameObject mercury, venus, earth, moon, mars, jupiter, saturn, uranus, neptune, pluto;
	GameObject voyager, starman, skydome;
	GameObject satringsFr, satringsBk;

	int scene, nLoops;
	int pnum = 0;
	int pnum_max;

	f2 getXZ(int angle) {
		f2 ret;
		ret.x = std::cos(angle * DEGTORAD);
		ret.y = std::sin(angle * DEGTORAD);
		return ret;
	}

public:

	virtual i2 getBackgroundSize() { return size_nokia5; }

	void AddPlanet(GameObject& pl, string alxtag, string tgatag, string name,int scale = 200) {
		planets.push_back(&pl);
		GameObject* g = AddResource(&pl, alxtag, tgatag, scale);
		g->JuiceType = JuiceTypes::JUICE_ROTY;
		g->JuiceSpeed *= 2;
		g->UUID = name + ".G";
		pnum++;
	}
	
	void AddSkyDome() {
		with AddResource(&skydome, "etetet","etetet", db.getMaxDist()* 1.3);
			//_.JuiceType = JuiceTypes::JUICE_ROTXYZ;
			_.JuiceSpeed *= 2;
			_.UUID = "SkyDome";
		_with
		PosRotScale* pUp = skydome.AddInstance(skydome);
		pUp->UUID = "skydomeUp";
		PosRotScale* pDn = skydome.AddInstance(skydome);
		pUp->UUID = "skydomeDn";
	}

	virtual void Init(char* path) {
	
	//	edit = true;
	//	wireframe = true;

		nLoops = 100;
		pnum = -1;

		AlInit(STANDARD);

		glEnable(GL_DEPTH_TEST);
	//	glEnable(GL_CULL_FACE);
	//	glCullFace(GL_BACK);

		AddDefaultCamera(Camera::CAM_MODE_LOOKAT, ORIGIN_IN_TOP_LEFT_OF_SCREEN);

		aCamera.PosRot({ 6660.3,-28.1,7029.0 }, { 2.0, 958.4, 0.0 });;
		string sphere = "earth";

		AddPlanet(mercury, "e", "e", "mercury", db.getSize(0));
		AddPlanet(venus, "ea", "ea", "venus", db.getSize(1));
		AddPlanet(earth, "earth", "earth", "earth", db.getSize(2));
		AddPlanet(mars, "mars", "mars", "mars", db.getSize(3));
		AddPlanet(jupiter, "jupiter", "jupiter", "jupiter", db.getSize(4));
		AddPlanet(saturn, "ee", "ee", "saturn", db.getSize(5));
		AddPlanet(uranus, "eart", "eart", "uranus", db.getSize(6));
		AddPlanet(neptune, "eeee", "eeee", "neptune", db.getSize(7));


//		AddPlanet(pluto, "eeeee", 6 * scal);
//		AddPlanet(moon, "earthe", 4 * scal);
//		AddPlanet(moon, "earthe", 4 * scal);
		///	AddPlanet(voyager, "hh", 10 * 3);

		pnum_max = pnum;

		AddSkyDome();

		with AddResource(&satringsFr, "erererer", "erererer", 500);
		_.JuiceType = JuiceTypes::JUICE_ROTY;
		_.JuiceSpeed *= 2;
	//	_.Hide();
		_with

			with AddResource(&satringsBk, "erererer", "erererer", 500);
		_.JuiceType = JuiceTypes::JUICE_ROTY;
		_.JuiceSpeed *= 2;
	//	_.Hide();
		_with

		dpad.LoadIn(this);
	//	dpointer.LoadIn(this);
		

		f3 center = {0,0,0};
		float rad = 0;
		

		int i = 0;
		for (int angle = 0; angle <360; angle+= (360/8)) {
			int dist = db.getDist(i);
			f2 r = getXZ(angle);
			planets[i]->pos.x = r.x * dist;
			planets[i]->pos.y = 0; 
			planets[i]->pos.z = r.y * dist;
			i++;
		}
		
		pnum_max = pnum;

		pnum = 0;
		selectedObject = planets[pnum];

		//planets.at(pnum)->Show();
	}

	PosRotScale graveyard;

	virtual void onActionComplete(GameObject* obj) {

	}

	virtual void processInput(PEG::CMD* cmd, float deltaT) {
		if (false && cmd->command == CMD_TOUCH_START) {
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

		if (cmd->command == CMD_KEYDOWN) {
		
		}


		if (cmd->command == CMD_TOUCH_START && dpad.wasTouched()) {
			switch (dpad.UDLRC()) {
			case 'U':	v.Next(pnum, &aCamera, true );break;
			case 'D':	v.Next(pnum, &aCamera, false);break;
			case 'L': {pnum--; if (pnum < 0) pnum = 0; v.Next(pnum, &aCamera, false); break; }
			case 'R': {
				pnum++; if (pnum > 3) pnum = 3; v.Next(pnum, &aCamera, false); break; 
			}
			}
			selectedObject = planets[pnum];
		}
	}

	float a;

	char tit1[128];

	float zRot =0;

	virtual void UpdateCustom(GameObject* gob, int instanceNo, float deltaT) {
			

		if (pnum == 6) {
			satringsFr.Show(); satringsBk.Show();
		}
		else {
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
	//		glRotatef(180, 1, 0, 0);
	//		glRotatef(-20, 0, 1, 0);
		}

		if (gob->is(skydome)) {
			skydome.getInstancePtr(0)->pos = aCamera.getPos(); 
			skydome.getInstancePtr(1)->pos = aCamera.getPos();
			skydome.getInstancePtr(0)->rot.x = (+90);
			skydome.getInstancePtr(1)->rot.x = (-90);
		}

		if (gob->is(dpad)) dpad.Update(deltaT);
		
//		if (gob->is(dpointer)) {
//			zRot += deltaT;
//			dpointer.SetDirection(aCamera.RotatedY);			
//		}

	}

	~App() {
	}
};

