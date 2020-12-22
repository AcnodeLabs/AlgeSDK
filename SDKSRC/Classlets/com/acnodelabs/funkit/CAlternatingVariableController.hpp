class CAlternatingVariableController {
	
		enum States {
			ST_FIX,
			ST_MOVING
		};

		float _A;
		float _B;
		float _Speed;
		float dir;
		short state;

	public:

		float curr;
		
		void Update(float dt) {			
			if (state==ST_MOVING) {
				if (dir>0 && curr>_B) 
				{
					curr=_B;state=ST_FIX;;//dir=-dir;
					return;
				}
				if (dir<0 && curr<=_A) {curr=_A;state = ST_FIX;dir=-dir;return;}
				curr = curr + (dir * dt * _Speed);
			} else {
				//curr = curr;
			}
		}

		float Curr() {
			return curr;
		}

		void Init(float A, float B, float speed, bool startFromA) {		
			_A = A; _B = B; _Speed = speed;
			if (startFromA) {curr = A; if (B>A) dir=+1; else dir=-1;state = ST_FIX;}
			if (!startFromA) {curr = B; if (B>A) dir=-1; else dir=1;state =ST_FIX;}
		}

		void ForceMoveToA() {
			dir = -1;
			StartRolling();
		}
		void ForceMoveToB() {
			dir = 1;
			StartRolling();
		}

		void StartRolling() {
			state= ST_MOVING;
		}

	};