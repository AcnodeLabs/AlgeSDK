// see http://stackoverflow.com/questions/31146698/pass-a-pointer-to-a-c-struct-into-ada
// g++ -c -fdump-ada-spec "StructDefs.h" -C
struct MoonInfo {
    int Year_Discovered;
    int Distance_From_Planet_km;
	int Diameter_km;
	float Orbital_Period_days;
} _MoonInfo;