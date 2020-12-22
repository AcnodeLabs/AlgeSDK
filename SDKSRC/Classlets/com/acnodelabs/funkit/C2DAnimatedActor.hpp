class C2DAnimatedActor {
	
	CAnim9 anim9;
	int _numTgaFiles;
	int _firstModelId;

	CResourceManager* _rm;
	class CHealthIndicator healthIndicator;

	float _secondsPerFrame;
	float t1;
	int curMo;
	float curr[3];
	bool show_healthIndicator;
public:

	float heaven;
	CAnimator can;
	float health;
	C2DAnimatedActor* _other;


	void Init(CResourceManager* rm, int firstModelId,char* alx, char* tgaTag,  float scale, int numTgaFiles, float secondsPerFrame, bool with_healthindicator, char* healthIndicatorAlx) {
		_rm = rm;_firstModelId = firstModelId;_secondsPerFrame = secondsPerFrame;
		char tgaFile[32]; _numTgaFiles = numTgaFiles;
		for (int i=1; i<=numTgaFiles; i++) {
			sprintf(tgaFile, "%s%d.tga",tgaTag,i);
			rm->loadAlxModel(alx,tgaFile, firstModelId+(i-1), scale);
		}
		heaven = rm->models[firstModelId]->boundz() * 50;

		t1 = 0;
		curMo = _firstModelId;
		can.curr = curr;
		show_healthIndicator = with_healthindicator;
		if (show_healthIndicator) {
			InitHealthIndicator(rm,healthIndicatorAlx,firstModelId+(numTgaFiles+1),4,30);
			health = 1;
		}
		_other = 0;
	}

	void InitHealthIndicator(CResourceManager* rm, char* alx, int modelId, float width, float height) {
		rm->loadAlxModel( alx,(char*) "health_indicator.tga", modelId ,1);
		healthIndicator.Init(rm->models[modelId],width,height);
		show_healthIndicator = true;
	}

	float _chaseSpeed;

	void attack(C2DAnimatedActor* other, float chaseSpeed) {
		this->_other = other;
		_chaseSpeed = chaseSpeed;
	}

	void moveTo(float* desired, float speed) {
		can.Reset(curr,desired,speed);
		t1 = 0;
		curMo = _firstModelId;
	}

	bool isActive() {
		return can.active;
	}

	vec2 getPos() {
		return vec2(curr[0],curr[1]);
	}

	void setPos(float* pos) {
		can.curr[0] = pos[0];
		can.curr[1] = pos[1];
		can.curr[2] = 0;
		can.desired[0] = can.curr[0];
		can.desired[1] = can.curr[1];
		can.desired[2] = 0;
		can.active = false;
	}
#ifndef NOGL
	void glDraw(bool with_heading, bool with_health_indicator) {
		glPushMatrix();
		glTranslatef(can.curr[0], can.curr[1], 0);
		if (with_heading) {
			anim9.UpdateModelTexCoordsFromHeading(
				_rm->models[curMo]->uv_array, 
				can.active, 
				can.curr[0], can.curr[1], can.desired[0], can.desired[1]
			);}
		_rm->models[curMo]->glDraw();
		glTranslatef(-can.curr[0], -can.curr[1], 0);
		if (show_healthIndicator) {
			if (with_health_indicator)	healthIndicator.glDraw(can.curr[0]+ _rm->models[curMo]->boundz() *1.3
				,can.curr[1]+ 0,health);
		}

		glPopMatrix();
	}
#endif
	bool isAlive() {
		return can.curr[1]!=heaven;
	}

	bool damage(float tick) {
		bool dead;
		health *= (29* tick);
		if (health<0.1) {
			health = 0;
		}
		if (health <= 0 ) dead = true; else dead = false;
		return dead;
	}

	void Update(float tick) {

		if (_other){
			if (_other->isAlive()) {
				moveTo(_other->can.curr,_chaseSpeed);
				if (CAnimator::Dist(can.curr, _other->can.curr)<50) {
				bool otherIsDead = _other->damage(tick);
				if (otherIsDead) _other = 0;
				} 
			}
		}

		if (health<=0) {can.desired[1] = heaven;}
		t1+=tick;
		
		if (t1>_secondsPerFrame) {
			t1= 0;
			curMo ++;
			if (curMo > (_firstModelId + (_numTgaFiles-1))) curMo = _firstModelId; 
		}
		can.Step(tick);
	}
};
