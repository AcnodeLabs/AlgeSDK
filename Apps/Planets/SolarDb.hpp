class SolarDB {
public:

	static const short NUM_PLANETS = 8;

	string getName(int i) {
		string name;
		if (i == 0) name = "mercury"; if (i == 1) name = "venus"; if (i == 2) name = "earth"; if (i == 3) name = "mars"; if (i == 4) name = "jupiter"; if (i == 5) name = "saturn"; if (i == 6) name = "uranus"; if (i == 7) name = "neptune";
		return name;
	}

	short getIndex(string name) {
		short i = -1;
		if (name.find("mercury") != string::npos) i = 0;
		if (name.find("venus") != string::npos) i = 1;
		if (name.find("earth") != string::npos) i = 2;
		if (name.find("mars") != string::npos) i = 3;
		if (name.find("jupiter") != string::npos) i = 4;
		if (name.find("saturn") != string::npos) i = 5;
		if (name.find("uranus") != string::npos) i = 6;
		if (name.find("neptune") != string::npos) i = 7;

		if (name.find("moon") != string::npos) i = 21;

		return i;
	}

	int distfromSun[8] = { 5800,10800,14900,22800,77800,143400,287100,449500 };
	int planetSize[8] = {7,10,10,10,2,15,10,10};
	
	int getDist(int i) { return distfromSun[i]; }
	int getSize(int i) { return 30 * planetSize[i]; }
	int getMaxDist() {
		int max = 0;
		for (auto d : distfromSun) {
			if (d > max) max = d;
		}
		return max;
	};
	int get(int i, string value) { return get(getName(i), value); }

	int get(string context, string value) {
		if (value == "size") {
			int scal = 30;
			if (context == "mercury") return (7 * scal);
			if (context == "venus") return (10 * scal);
			if (context == "earth") return (10 * scal);
			if (context == "mars") return (10 * scal);
			if (context == "jupiter") return (20 * scal);
			if (context == "saturn") return (15 * scal);
			if (context == "uranus") return (10 * scal);
			if (context == "neptune") return (10 * scal);
		}
		if (value == "dist") {
			int scal = 30;
			if (context == "mercury") return (7 * scal);
			if (context == "venus") return (10 * scal);
			if (context == "earth") return (10 * scal);
			if (context == "mars") return (10 * scal);
			if (context == "jupiter") return (20 * scal);
			if (context == "saturn") return (15 * scal);
			if (context == "uranus") return (10 * scal);
			if (context == "neptune") return (10 * scal);
		}
		return 0;
	}
};