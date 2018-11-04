class CPhys {
public: 

	float pos[3];
	float vel[3];
	float accel[3];
	float force[3];
	float impulse[3];
	float gravity[3];
	float momentum[3];
	float mass;
	float ydir;
	float friction;
	bool active;
	int bounced;
	int bouncelimit;
	float ground;
	float ftop,fleft,fbottom,fright;
	bool tophit,lefthit,righthit;
	float collisionloss;

	CPhys() {
		Clear();
	} 

	void Clear() {
		collisionloss = 0.8f;
		tophit = false;
		lefthit = false;
		righthit = false;
		ground = 0;
		bounced = 0;
		bouncelimit = 2;
		active = false;
		ydir = 1.0f;
		friction = 0.8f;
		vel[0] = 0.0f;
		vel[1] = 0.0f;
		vel[2] = 0.0f;
		mass = 10;

		ftop = 0;
		fbottom = 0;
		fleft = 0;
		fright = 0;

		accel[0] = 0.0f;
		accel[1] = 0.0f;
		accel[2] = 0.0f;

		force[0] = 0.0f;
		force[1] = 0.0f;
		force[2] = 0.0f;

		gravity[0] = 0.0f;
		gravity[1] = 0.0f;
		gravity[2] = 0.0f;

		impulse[0] = 0.0f;
		impulse[1] = 0.0f;
		impulse[2] = 0.0f;

		momentum[0] = 0;
		momentum[1] = 0;
		momentum[2] = 0;

		set_pos(0, 0, 0);
		set_gravity(0, -9.8, 0);

	}

	void ApplyFuzzySmallForce2D() {
		force[0] =  mass * 1000.0f;
		force[1] =  mass * 1000.0f;
	}

	void ApplyFuzzyModerateForce2D() {
		force[0] =  mass * 10000.0f;
		force[1] =  mass * 10000.0f;
	}

	void ApplyFuzzyLargeForce2D() {
		force[0] =  mass * 100000.0f;
		force[1] =  mass * 100000.0f;
	}

	void set_pos(float x, float y, float z) {
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}

	f3 getPos(string tag) {
		return f3(pos[0], pos[1], pos[2]);
	}

	void set_gravity(float x, float y, float z) {
		gravity[0] = x;
		gravity[1] = y;
		gravity[2] = z;
	}

	void set_bounds(float top, float left, float bottom, float right) {
		ftop = top; fleft = left; fbottom = bottom; fright = right;
	}

	void set_impulse(float x, float y, float z) {
		impulse[0] = x;
		impulse[1] = y;
		impulse[2] = z;
		active = true;
		bounced = 0;
	}

	void Update(float dt) {
		// Accel = Sum of All Forces / Mass;
	}

	void Step(float dt) {

		if (impulse[0]) force[0]+=impulse[0];
		if (impulse[1]) force[1]+=impulse[1];
		if (impulse[2]) force[2]+=impulse[2];


		float weight;
		weight = mass * gravity[1];

		impulse[0] = impulse[0] * 0.9f; if (abs(impulse[0])<0.001f) impulse[0] = 0.0f;
		impulse[1] = impulse[1] * 0.9f; if (abs(impulse[1])<0.001f) impulse[1] = 0.0f;
		impulse[2] = impulse[2] * 0.9f; if (abs(impulse[2])<0.001f) impulse[2] = 0.0f;

		if (!active) {
			return;
		}

		apply_force(&accel[0], &force[0], mass);

		if (active) accel[0] += gravity[0];
		if (active) accel[1] += gravity[1];
		if (active) accel[2] += gravity[2];

		apply_acceleration(&vel[0], &accel[0], dt); 

		vel[0]*= friction;
		vel[1]*= friction;
		vel[2]*= friction;

		apply_velocity(&pos[0], &vel[0], dt);

		momentum[0] = mass * vel[0];
		momentum[1] = mass * vel[1];
		momentum[2] = mass * vel[2];

	}

	float dist(float vel, float dt) {
		return (vel*dt);
	}

	void dist3(float* vel, float dt) {
		float distx ; distx = vel[0] * dt;
		float disty ; disty = vel[1] * dt;
		float distz ; distz = vel[2] * dt;
	}


	void apply_force(float* a, float* f, float m) {
		a[0] = f[0] / m;
		a[1] = f[1] / m;
		a[2] = f[2] / m;
	}

	void apply_acceleration(float* vel, float* accel, float dt) {
		vel[0] += accel[0] * dt;
		vel[1] += accel[1] * dt;
		vel[2] += accel[2] * dt;
	}

	void apply_velocity(float* pos, float* vel, float dt) {
		float distx = vel[0] * dt;
		float disty = vel[1] * dt;
		float distz = vel[2] * dt;
		pos[0] += distx ;
		pos[1] += disty ;
		pos[2] += distz ;
	}
	bool testCollision(f2 p1, f2 p2) {
		return false;
	}

};


