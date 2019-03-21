#ifndef ACAMERA_H
#define ACAMERA_H
#define PI 3.1415265359
#define PIdiv180 3.1415265359/180.0

/////////////////////////////////
//Note: All angles in degrees  //
/////////////////////////////////

struct SF3dVector  //Float 3d-vect, normally used
{
	float x,y,z;
};
struct SF2dVector
{
	float x,y;
};

class CFpsCamera
{
private:
	
	SF3dVector ViewDir;		/*Not used for rendering the camera, but for "moveforwards"
							So it is not necessary to "actualize" it always. It is only
							actualized when ViewDirChanged is true and moveforwards is called*/
	bool ViewDirChanged;
	
	void GetViewDir ( void );
public:
	CFpsCamera();				//inits the values (Position: (0|0|0) Target: (0|0|-1) )
	//void Render ( void );	//executes some glRotates and a glTranslate command
							//Note: You should call glLoadIdentity before using Render
	void Move ( SF3dVector Direction );
	void RotateX ( float Angle );
	void RotateY ( float Angle );
	void RotateZ ( float Angle );
	void RotateXYZ ( SF3dVector Angles );
	void MoveForwards ( float Distance );
	void StrafeRight ( float Distance );
	void KeyDownCcam(unsigned char key, float d);
	float RotatedX, RotatedY, RotatedZ;
	SF3dVector Position;
	void PosRot(SF3dVector pos, SF3dVector rot);
};


SF3dVector F3dVector ( float x, float y, float z );
SF3dVector AddF3dVectors ( SF3dVector * u, SF3dVector * v);
void AddF3dVectorToVector ( SF3dVector * Dst, SF3dVector * V2);
#endif