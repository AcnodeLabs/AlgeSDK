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
	ResourceInf rSkyDome;
	GameText line;	
	GameText line2;

public:

	void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_TOUCH_START) {
			PosRotScale tilt45;
			tilt45.rot.z = 45.;
			//prs.scale = 10.0;
			line.transitionTo(tilt45,40.);
		}
		if (p->command == CMD_TOUCH_END) {
			PosRotScale origin;
			line.transitionTo(origin, 40.);
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

	void AddDome() {
		SkyDome.SetSerializeTag("SKYDOME.GOB");
		rSkyDome.Set("SkyDome", "skydome.alx", "skydome.tga", 0.1f);
		LoadModel(&SkyDome, &rSkyDome, MODEL_SKYDOME);
        AddObject(&SkyDome);
	}

	void AddText() {
		line.Setup(this, "Hello World", MODEL_FONT);
		AddObject(&line);
	
		PosRotScale y10;
		y10.pos.y = 10.;
		line2.transitionTo(y10,1E9);
		line2.Setup(this, "Above All", MODEL_FONT2);
		AddObject(&line2);
	}

	virtual void Init(char* path) {
		alInit(STANDARD);
		output.pushP(CMD_TITLE, $ "DemoFont",0);
		AddDefaultCamera();
		AddDome();
		AddText();
	}

};
