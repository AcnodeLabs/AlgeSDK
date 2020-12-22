class CGuage {
public:
	
	int min;
	int max;
	
	int angle_max;
	int base_angle;
	short rotz;
	
	int val;
	
	float vertexdata[9];
	
	short getRotz() {
		rotz = (val / (max-min)) * angle_max;
		return (base_angle + rotz);
		
	}
	
	bool set(int minimum_value, int maximum_value, int initial_value, 
			 int max_deflection_angle, int init_needle_angle) {
		
		min = minimum_value;
		max = maximum_value;
		val = initial_value;
		angle_max = max_deflection_angle;
		base_angle = init_needle_angle;
		
		vertexdata[0] = 0; vertexdata[1] = 1.0f; vertexdata[2] = 0;
		vertexdata[3] = -0.1f; vertexdata[4] = -0.1f; vertexdata[5] = 0;
		vertexdata[7] = 0.1f; vertexdata[6] = -0.1f; vertexdata[8] = 0;
		
		return ((max>min)&&(val>=min)&&(val<=max)&&(base_angle<angle_max));
	} 
	
   void info(char* szout) {
		char inf[10] = "[CGuage]";
		memcpy(szout, inf, 10);
	}
	
};
