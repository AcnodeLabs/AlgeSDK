#include "camera.h"
#include "math.h"
#include <iostream>

#ifdef WIN32
#include "windows.h"
#endif

SF3dVector F3dVector ( float x, float y, float z )
{
	SF3dVector tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}
SF3dVector AddF3dVectors (SF3dVector* u, SF3dVector* v)
{
	SF3dVector result;
	result.x = u->x + v->x;
	result.y = u->y + v->y;
	result.z = u->z + v->z;
	return result;
}
void AddF3dVectorToVector ( SF3dVector * Dst, SF3dVector * V2)
{
	Dst->x += V2->x;
	Dst->y += V2->y;
	Dst->z += V2->z;
}


/***************************************************************************************/

CFpsCamera::CFpsCamera()
{
	//Init with standard OGL values:
	Position = F3dVector (	0.0, 
							0.0,
							0.0);
	ViewDir = F3dVector(	0.0,
							0.0,
							-1.0);
	ViewDirChanged = false;
	//Only to be sure:
	RotatedX = RotatedY = RotatedZ = 0.0;
	
}

void CFpsCamera::GetViewDir( void )
{
	SF3dVector Step1, Step2;
	//Rotate around Y-axis:
	Step1.x = (float)cos( (RotatedY + 90.0) * PIdiv180);
	Step1.z = (float) -sin( (RotatedY + 90.0) * PIdiv180);
	//Rotate around X-axis:
	double cosX = cos (RotatedX * PIdiv180);
	Step2.x = (float) (Step1.x * cosX);
	Step2.z = (float) (Step1.z * cosX);
	Step2.y = (float) sin(RotatedX * PIdiv180);
	//Rotation around Z-axis not yet implemented, so:
	ViewDir = Step2;
}
void CFpsCamera::Move (SF3dVector Direction)
{
	AddF3dVectorToVector(&Position, &Direction );
}

void CFpsCamera::RotateY (float Angle)
{
	RotatedY += Angle;
	ViewDirChanged = true;
}

void CFpsCamera::RotateX (float Angle)
{
	RotatedX += Angle;
	ViewDirChanged = true;
}
/*
void CFpsCamera::Render( void )
{
	glRotatef(-RotatedX , 1.0, 0.0, 0.0);
	glRotatef(-RotatedY , 0.0, 1.0, 0.0);
	glRotatef(-RotatedZ , 0.0, 0.0, 1.0);
	glTranslatef( -Position.x, -Position.y, -Position.z );
}
*/
void CFpsCamera::MoveForwards( float Distance )
{
	if (ViewDirChanged) GetViewDir();
	SF3dVector MoveVector;
	MoveVector.x = ViewDir.x * -Distance;
	MoveVector.y = ViewDir.y * -Distance;
	MoveVector.z = ViewDir.z * -Distance;
	AddF3dVectorToVector(&Position, &MoveVector );
}

void CFpsCamera::StrafeRight ( float Distance )
{
	if (ViewDirChanged) GetViewDir();
	SF3dVector MoveVector;
	MoveVector.z = -ViewDir.x * -Distance;
	MoveVector.y = 0.0;
	MoveVector.x = ViewDir.z * -Distance;
	AddF3dVectorToVector(&Position, &MoveVector );
}

void CFpsCamera::PosRot(SF3dVector pos, SF3dVector rot) {
	Position = pos;
	RotatedX = rot.x; RotatedY = rot.y; RotatedZ = rot.z;
}

void CFpsCamera::KeyDownCcam(unsigned char key, float d)
{
	key = key + 81;
	switch (key)
	{
	case 'a':
		RotateY(d);
		break;
	case 'd':
		RotateY(-d);
		break;
	case 'w':
	case 70:
		MoveForwards(-d);
		break;
	case 's':
	case 72:
		MoveForwards(d);
		break;
	case 'x':
		RotateX(d);
		break;
	case 'y':
		RotateX(-d);
		break;
	case 'c':
	case 69:
		StrafeRight(-d);
		break;
	case 'v':
	case 71:
		StrafeRight(d);
		break;
	case 'f':
		Move(F3dVector(0.0, -d, 0.0));
		break;
	case 'r':
		Move(F3dVector(0.0, d, 0.0));
		break;

	}
}
