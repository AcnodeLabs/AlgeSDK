// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: Terrain Model
*/

enum {
 MODEL_SKYDOME,
 MODEL_FONT,
 MODEL_FONT2
} models;


class /*DemoFont*/ App : public AlgeApp { 

	GameObject SkyDome;
	GameText line;	
//	GameText line2;

public:


	void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_TOUCH_START) {
			PosRotScale tilt45;
			tilt45.rot.z = 45.;
			//prs.scale = 10.0;
	//		line.transitionTo(tilt45,40.);
		}
		if (p->command == CMD_TOUCH_END) {
			PosRotScale origin;
	//		line.transitionTo(origin, 40.);
		}
	}

	void UpdateCustom(GameObject* gob) {
		edit = true;
		if (gob->custom_type == MODEL_FONT) {
			//wireframe = !wireframe;
			glColor3f(1.0, 1., 1.);
		} else glColor3f(1., 1., 1.);
		if (gob->custom_type == MODEL_SKYDOME) {			
		}
	}


	void AddText() {
		line.Setup(this, "Hello World", SkyDome.modelId+1);
	//	AddObject(&line);
		PosRotScale y10;
		y10.pos.y = 10.;
	}

	virtual void Init(char* path) {
		AlInit(STANDARD);
		output.pushP(CMD_TITLE, $ "DemoFont",0);
		AddDefaultCamera();
	//	AddResource(&SkyDome, "skydome"); 
		AddText();
	}

};
