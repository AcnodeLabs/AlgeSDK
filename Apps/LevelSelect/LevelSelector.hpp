// Copyright (c) 2019 AcnodLabs Inc

/* 
   ALGE SDK JD3 Demo :: LevelSelect
*/

class LevelSelector : public AlgeApp { 
	GameObject background;
	GameObject locks;
	
public:
    
        i2 getBackgroundSize() {
           return i2(c.screen[0],c.screen[1]);
        }
    
		int CMD_LEVELSELECT = 4111;
		vector<bool> lockHid;
		
		void slideIn() {
			background.hidden = false;
			for_i(locks.prsInstances.size())
				locks.getInstancePtr(i)->hidden = lockHid.at(i);
			_for
		}
	
		void slideOut() {
			lockHid.clear();
			background.hidden = true;
			for_i(locks.prsInstances.size())
				lockHid.push_back(locks.getInstancePtr(i)->hidden);
				locks.getInstancePtr(i)->hidden = background.hidden;
			_for
		}
		
		// Call after AlInit and AddDefaultCamera
		virtual void Init(char* path) {

		AddResource(&background, "levelselect", "levelselect.jpg", XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN
		);

		AddResource(&locks, "lock","lock.jpg");
					//load hsdata dump
		#include "../LevelSelect.Assets/Data/levelselect.h"
		PosRotScale prs;
		
		for (int i = 0; i < 3; i++) for (int j = 0; j < 5; j++) {
			int w = hs[i][j].Right - hs[i][j].Left;
			int h = hs[i][j].Bottom - hs[i][j].Top;
			int px = hs[i][j].Left + w /2;
			int py = hs[i][j].Top + h / 2;
			prs.pos.x = px;
			prs.pos.y = py;
			prs.scale = 2;
			locks.AddInstance(prs);
		}

            wireframe = false;
            
		output.pushP(CMD_SNDSET0, $ "entry.wav", 0);

		}

		void unlock(int l) {
			for_i(l)
				locks.getInstancePtr(i)->hidden = true;
			_for
		}
		
		void levelSelected(int lvl) {
			output.pushP(CMD_SNDPLAY0, $ "entry.wav", 0);
			slideOut();
			input.pushI(LevelSelector::CMD_LEVELSELECT, lvl, 0);
		}

		int dim(int r, int c) {
			int ret = (r+1)*(c+1);
			return ret;
		}

    CControls c;
	CHotSpot hs[3][5];
	string sz;
	int sx; int sy;
	void processInput(PEG::CMD* p, float deltaT) { 
		if (background.hidden) return;
		short touchData = 0;

		if (p->command == CMD_SCREENSIZE) {
			c.screen[0] = p->i1 ;
			c.screen[1] = p->i2 ;
			CHotSpot::sx = p->i1 * 2;
			CHotSpot::sy = p->i2 * 2;
		}
		
		if (p->command == CMD_TOUCH_START) {
			sx = p->i1;
			sy = p->i2;
			//HITTEST
			for (int r = 0; r < 3; r++) for (int c = 0; c < 5; c++) {
				bool hid = locks.getInstancePtr(dim(r, c))->hidden;
				if (hs[r][c].HitX(sx, sy) && !hid) levelSelected(hs[r][c].id);
			}
		}

		if (p->command == CMD_TOUCH_END) {
			//CHotSpot::WriteCodeToLog(sx, sy, p->i1, p->i2);
		}

	}

	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
		//		if (gob->is(background)) //			glColor3f(0.8, 0.8, 0.8);//dim 80%
	}

};
