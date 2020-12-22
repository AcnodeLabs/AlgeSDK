#include "SolarDb.hpp"

class PlanetsApp : public MockUpOne {
public:
	int scene, iScore;
	GameObject mercury, venus;
	GameObject fps_text;
	SolarDB db;
	AlgeApp* that = nullptr;

	int nRemaining;
	int rightSide1;
	int leftSide1;
	int level = 1;

	void onSceneEnter() {
		ShowPlanet(0);
	}

	void LoadIn(AlgeApp* that) {
		level = 1;
		iScore = 0;
		//FIRST LOAD MOCK
		LoadMock(that,  /*TitleImage*/ "titletext", /*SettingsImage*/ "settings", "pointer", "settings_icon");
		this->that = that;

		with that->AddObject(&fps_text);
		_.pos.x = that->rightSide / 20;
		_.pos.y = that->bottomSide / 20;
		_.color = f3(0, 0, 0);
		_with

			string oo = "sphere";
		
		with that->AddResource(&mercury, "sphere", "mercury", 100);
			_.pos.x = that->rightSide * 0.25;
			_.pos.y = that->bottomSide * 0.5;
		_with
		
		with that->AddResource(&venus, "sphere", "venus", 100);
			_.pos.x = that->rightSide * 0.75;
			_.pos.y = that->bottomSide * 0.5;
		_with
		
		MakeStarField();
	}

	void ShowPlanet(int n) {
		for (int i = 0; i < 9; i++) {
	//		planets[i].Hide();
		}
		mercury.Show();
		venus.Show();
	}

	void UpdateScene(GameObject* gob, int instanceNo, float deltaT) {

		if (gob->is(score)) {
			glColor3f(0.0, 0.0, 0.0);
			std::ostringstream sc;
			sc << "Score : " << iScore;
			that->alPrint(sc.str().c_str());			
		}
	}
	   
	void processInput(PEG::CMD* cmd, float deltaT) {



		if (cmd->command == CMD_KEYDOWN) {
			if (cmd->i1 == MAC_KEY_PLUS) {

			}
		}

		if (cmd->command == CMD_SETTINGS_SCREEN) {
		}

		if (cmd->command == CMD_GAMEPAD_EVENT) {
			if (cmd->i1 == MyGamePad::EventTypes::BTN) {
				if (cmd->i2 == MyGamePad::EventCodes::BTN_X) {}				
			}
		}

		if (cmd->command == CMD_GAMEPAD_EVENT && cmd->i1 == MyGamePad::EventTypes::PAD) {
			if (cmd->i2 == MyGamePad::EventCodes::PAD_LT || cmd->i2 == MyGamePad::EventCodes::PAD_RT) {
			}
			if (cmd->i2 == MyGamePad::EventCodes::PAD_UP || cmd->i2 == MyGamePad::EventCodes::PAD_DN) {
			}
		}
		MockUpOne::processInput(cmd, deltaT);
	}

	void MakeStarField() {
		PosRotScale bp;
		for (int i = 0; i < 100; i++) {
		}

	}

};