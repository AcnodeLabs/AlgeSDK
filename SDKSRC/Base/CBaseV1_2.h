/*
*  CBase

*
*  Copyright 2012 AcnodeLabs All rights reserved.
*
*/
#ifndef CBASE_H_INCLUDED
#define CBASE_H_INCLUDED
//#define METRO
#ifdef WIN32
#define GLfixed GLfloat
#pragma warning(disable : 4996)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)
#ifndef METRO
//#include "../../../Alge-WinPhone8/Alge-WinPhone8/gl2dxwp/gl2dx.h"

//#define GLES3

#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
/*
#ifndef GLES3
#include <gl/gl.h>
#include <gl/glu.h>
#else
#include <gl/gl3.h>
#endif
*/
#else
#define GLubyte unsigned char
#define GLuint unsigned int
#define GLint int
#define GLfloat float
#define GLsizei short
#endif
#else

#ifdef IOSMETAL
#define GLubyte unsigned char
#define GLuint unsigned int
#define GLint int
#define GLfloat float
#define GLsizei short
#endif

//#define MACOSX
#ifdef MACOSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
//iOs
#include "importgl.h"
#endif

#endif

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <math.h>
#include <string>
#include <vector>

//SomeHelper Defines
#define with {auto &_=*
#define _with }

using namespace std;

void alPrintText(string text, float scale);

class ResourceInf {
public:
	std::string tex;
	std::string name;
	float scale;
	std::string alx;
	ResourceInf() {};
	ResourceInf(std::string _name, std::string _alx, std::string _tex, float _scale = 1.0f) {
		Set(_name, _alx, _tex, _scale);
	};

	void Set(std::string _filed_name, float _scale = 1.0f) {
		Set(_filed_name, _filed_name + ".alx", _filed_name + ".tga", _scale);
	}

	void Set(std::string _name, std::string _alx, std::string _tex, float _scale = 1.0f) {
		tex = _tex;
		name = _name;
		alx = _alx;
		scale = _scale;
	}
};

#include "UTM.h"

#ifndef IOSMETAL
//#include <future>
#endif

#include "CCommands.h"

/*For Future Use
#include "../ThirdParty/assimp/include/assimp/Importer.hpp"
#include "../ThirdParty/assimp/include/assimp/scene.h"
#include "../ThirdParty/assimp/include/assimp/postprocess.h"
*/

#include "drawtext.h"

#ifdef XCODE_BUILD
#include "Ada/AlgeSDK.ads.h"
#endif
#ifdef WIN32
#include "Ada/AlgeSDK.ads.h"
#endif // WIN32

#ifdef ANDROID_VERSIONING_H
#define NO_BOX2D
#define ES_ONLY
#define NO_NATS
#include "Ada/AlgeSDK.ads.h"
#endif

#define AUTO 0
#define STANDARD 1
#define STANDARD_WITH_TEXTURES 3
#define STANDARD_2D 2

#define AL_QUADS 0x0007
#define KROSS_UP 1
#define KROSS_DOWN 2
#define KROSS_LEFT 3
#define KROSS_RIGHT 4
#define KROSS_CENTER 5


#define EFFECT_SQUEEZEIN	6701

float absolute(float value) {
	if (value<0.0f) return -value;
	return value;
}

float randm();
#define COLOR_CORNFLOWERBLUE 154.0f/255.0f, 206.0f/255.0f, 235.0f/255.0f,1.0f



char AlKeyChar(short i1) {
	return 'A' + i1 - AL_KEY_ALPHA;
}
#ifndef NOGL
#ifndef WIN32
void glColor3f(float r, float g, float b) {
	glColor4f(r, g, b, 1);
}
#endif
#endif


typedef struct												// Create A Structure
{
	GLubyte	*imageData;										// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
} TextureImage;												// Structure Name

															//OPTIMAL VECTOR FUNCS
float length(float* vector1)
{
	return (float)sqrt((double)(vector1[0] * vector1[0] + vector1[1] * vector1[1] + vector1[2] * vector1[2]));
}

void inline normalize(float* resultant, float* vector1)
{
	float s = 1.0f / length(vector1);
	resultant[0] = vector1[0] * s;
	resultant[1] = vector1[1] * s;
	resultant[2] = vector1[2] * s;
}

//#ifndef NOGL
void alBillboardBegin() {
	float modelview[16];
	int i, j;
	glPushMatrix();
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview);
	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++) {
			if (i == j)
				modelview[i * 4 + j] = 1.0;
			else
				modelview[i * 4 + j] = 0.0;
		}
	glLoadMatrixf(modelview);
}
//#endif



//#ifndef NOGL
void alBillboardEnd() {
	glPopMatrix();
}
//#endif

CRect screenRect;

float fromScreenX(float x) {
	return x - (screenRect.Right - screenRect.Left) / 2.0f;
}

float fromScreenY(float y) {
	float nPixY = (screenRect.Top - screenRect.Bottom);
	float r = (nPixY / 2.0f) - y;
	return  r;
}


void hudBegin(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {

	screenRect.Left = left;
	screenRect.Right = right;
	screenRect.Bottom = bottom;
	screenRect.Top = top;
#ifndef NOGL
	glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();										// Store The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

#ifdef WIN32
	glOrtho(left, right, bottom, top, 0.01f, 1000);							// Set Up An Ortho Screen
#else

#ifdef MACOSX
	glOrtho(left, right, bottom, top, 0.1f, 100);
#else
	glOrthof(left, right, bottom, top, 0.1f, 100);							// Set Up An Ortho 
#endif

#endif

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPushMatrix();										// Store The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	glTranslatef(0, 0, -0.5);

#endif
}


// Maintaining Aspect Ratio
void hudBegin(int* screen, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top) {
	float aspectratio = screen[0] / (screen[1] + 0.000001f);
	hudBegin(left*aspectratio, right*aspectratio, bottom, top);
}


// Strech without Maintaining Aspect Ratio
void hudBeginAxisTopLeft(int* screen) {
	hudBegin(0, screen[0], screen[1], 0);
}

void hudBegin(int* screen) {
	hudBegin(-screen[0] / 2, screen[0] / 2, -screen[1] / 2, screen[1] / 2);
}

void hudEnd() {
#ifndef NOGL
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glPopMatrix();										// Restore The Old Projection Matrix
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
#endif
}


void inline subtr(float* resultant, float* vector1, float* vector2)
{
	resultant[0] = (vector1[0] - vector2[0]);
	resultant[1] = (vector1[1] - vector2[1]);
	resultant[2] = (vector1[2] - vector2[2]);
}

void inline cross(float* resultant, float* vector1, float* vector2)
{
	resultant[0] = ((vector1[1] * vector2[2]) - (vector1[2] * vector2[1]));
	resultant[1] = ((vector1[2] * vector2[0]) - (vector1[0] * vector2[2]));
	resultant[2] = ((vector1[0] * vector2[1]) - (vector1[1] * vector2[0]));
}


void inline aluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez,
	GLfloat centerx, GLfloat centery, GLfloat centerz,
	GLfloat upx, GLfloat upy, GLfloat upz)
{
	GLfloat m[16], x[3], y[3], z[3], mag;
	z[0] = eyex - centerx; z[1] = eyey - centery; z[2] = eyez - centerz;
	mag = sqrtf(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
	if (mag) { z[0] /= mag; z[1] /= mag; z[2] /= mag; }
	y[0] = upx; y[1] = upy; y[2] = upz;
	x[0] = y[1] * z[2] - y[2] * z[1];
	x[1] = -y[0] * z[2] + y[2] * z[0];
	x[2] = y[0] * z[1] - y[1] * z[0];
	y[0] = z[1] * x[2] - z[2] * x[1];
	y[1] = -z[0] * x[2] + z[2] * x[0];
	y[2] = z[0] * x[1] - z[1] * x[0];
	mag = sqrtf(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
	if (mag) { x[0] /= mag; x[1] /= mag; x[2] /= mag; }
	mag = sqrtf(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
	if (mag) { y[0] /= mag; y[1] /= mag; y[2] /= mag; }

#define M(row,col)  m[col*4+row]
	M(0, 0) = x[0]; M(0, 1) = x[1]; M(0, 2) = x[2]; M(0, 3) = 0.0;
	M(1, 0) = y[0]; M(1, 1) = y[1]; M(1, 2) = y[2]; M(1, 3) = 0.0;
	M(2, 0) = z[0]; M(2, 1) = z[1]; M(2, 2) = z[2]; M(2, 3) = 0.0;
	M(3, 0) = 0.0; M(3, 1) = 0.0; M(3, 2) = 0.0; M(3, 3) = 1.0;
#undef M
#ifndef NOGL
	glMultMatrixf(m);
	glTranslatef(-eyex, -eyey, -eyez);
#endif
}


void limitf(float* var, float min, float max) {
	if (*var<min) *var = min;
	if (*var>max) *var = max;
}

#define TOUCHING_NOTHING     0
#define TOUCHING_ONEFINGER   1
#define TOUCHING_TWOFINGERS  2


typedef struct						// Create A Structure For Particle
{
	bool	active;					// Active (Yes/No)
	float	life;					// Particle Life
	float	fade;					// Fade Speed
	float	r;						// Red Value
	float	g;						// Green Value
	float	b;						// Blue Value
	float	x;						// X Position
	float	y;						// Y Position
	float	z;						// Z Position
	float	xi;						// X Direction
	float	yi;						// Y Direction
	float	zi;						// Z Direction
	float	xg;						// X Gravity
	float	yg;						// Y Gravity
	float	zg;						// Z Gravity
}
particles;

#ifndef METRO
class aL10 {

public:

	float v[512 * 4];
	float t[512 * 4];
	float n[512 * 4];
	float c[512 * 4];

	unsigned int iver;
	unsigned int itex;
	unsigned int inor;
	unsigned int icol;

	GLuint MODE;

	aL10() {
#ifndef NOGL
		MODE = GL_TRIANGLES;
#else
		MODE = 0;
#endif
		iver = 0;
		itex = 0;
		inor = 0;
		icol = 0;
	}

	void Test2D() {
		//////////////////////////////////////CHUNK DELETE 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		glLoadIdentity();									// Reset The Current Modelview Matrix
		glTranslatef(-1.5f, 0.0f, -10.0f);					// Move
		Capture(GL_TRIANGLES);							// Drawing Using Triangles
		glColor3f(1.0f, 0.0f, 0.0f);						// Set The Color To Red
		glVertex3f(0.0f, 1.0f, 0.0f);					// Top
		glColor3f(0.0f, 1.0f, 0.0f);						// Set The Color To Green
		glVertex3f(-1.0f, -1.0f, 0.0f);					// Bottom Left
		glColor3f(0.0f, 0.0f, 1.0f);						// Set The Color To Blue
		glVertex3f(1.0f, -1.0f, 0.0f);					// Bottom Right
		Flush(0, false, true, false);					// Finished Drawing The Triangle
		glTranslatef(3.0f, 0.0f, 0.0f);						// Move Left 1.5 Units And Into The Screen 6.0
		glColor4f(0.5f, 0.5f, 1.0f, 1.0f);

		Capture(GL_TRIANGLES);							// Drawing Using Triangles
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
		Flush(0, false, false, false);
		/////////////////////////////////////////////////////////////////////
	}


	void Triangle(float size) {
#ifndef NOGL
		Capture(GL_TRIANGLES);							// Drawing Using Triangles
		glColor3f(size, 0.0f, 0.0f);						// Set The Color To Red
		glVertex3f(0.0f, size, 0.0f);					// Top
		glColor3f(0.0f, size, 0.0f);						// Set The Color To Green
		glVertex3f(-size, -size, 0.0f);					// Bottom Left
		glColor3f(0.0f, 0.0f, 10.0f);						// Set The Color To Blue
		glVertex3f(size, -size, 0.0f);					// Bottom Right
		Flush(0, false, true, false);					// Finished Drawing The Triangle
#endif
	}

#ifndef NOGL

	void Capture() {
		Capture(GL_TRIANGLES);
	}

	void Capture(GLuint aMODE) {
		iver = 0;
		itex = 0;
		inor = 0;
		icol = 0;
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		MODE = aMODE;
	}
#endif

	void CopyBuf(const float* src, int size, char type)
	{
		float * dest;
		switch (type) {
		case 'V':
			dest = &v[0]; iver = size / 3;
			break;
		case 'N':
			dest = &n[0]; inor = size / 3;
			break;
		case 'T':
			dest = &t[0]; itex = size / 2;
			break;
		case 'C':
			dest = &c[0]; icol = size / 4;
			break;

		}

		for (int i = 0; i<size; i++)
			dest[i] = src[i];

	}
#ifndef NOGL
	/*
	void DrawFontV1Char(char c) {

	float* charvert = (float*)charvertA;
	int n= nA;
	switch (c) {
	case 'A':{charvert = (float*)charvertA; n = nA;} ;break;
	case 'B':{charvert = (float*)charvertB; n = nB;} ;break;
	case 'C':{charvert = (float*)charvertC; n = nC;} ;break;
	case 'D':{charvert = (float*)charvertD; n = nD;} ;break;
	case 'E':{charvert = (float*)charvertE; n = nE;} ;break;
	case 'F':{charvert = (float*)charvertF; n = nF;} ;break;
	case 'G':{charvert = (float*)charvertG; n = nG;} ;break;
	case 'H':{charvert = (float*)charvertH; n = nH;} ;break;
	case 'I':{charvert = (float*)charvertI; n = nI;} ;break;
	case 'J':{charvert = (float*)charvertJ; n = nJ;} ;break;
	case 'K':{charvert = (float*)charvertK; n = nK;} ;break;
	case 'L':{charvert = (float*)charvertL; n = nL;} ;break;
	case 'M':{charvert = (float*)charvertM; n = nM;} ;break;
	case 'N':{charvert = (float*)charvertN; n = nN;} ;break;
	case 'O':{charvert = (float*)charvertO; n = nO;} ;break;
	case 'P':{charvert = (float*)charvertP; n = nP;} ;break;
	case 'Q':{charvert = (float*)charvertQ; n = nQ;} ;break;
	case 'R':{charvert = (float*)charvertR; n = nR;} ;break;
	case 'S':{charvert = (float*)charvertS; n = nS;} ;break;
	case 'T':{charvert = (float*)charvertT; n = nT;} ;break;
	case 'U':{charvert = (float*)charvertU; n = nU;} ;break;
	case 'V':{charvert = (float*)charvertV; n = nV;} ;break;
	case 'W':{charvert = (float*)charvertW; n = nW;} ;break;
	case 'X':{charvert = (float*)charvertX; n = nX;} ;break;
	case 'Y':{charvert = (float*)charvertY; n = nY;} ;break;
	case 'Z':{charvert = (float*)charvertZ; n = nZ;} ;break;
	default:
	break;
	}


	glVertexPointer(3, GL_FLOAT, 0, charvert);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPointSize(4);
	//glEnable(GL_POINT_SMOOTH);
	glDrawArrays(GL_POINTS,0, n);
	}

	void DrawFontV1Char(char c, float scale)
	{
	glScalef(scale,scale,scale);
	DrawFontV1Char(c);
	}
	*/
	void ViewingBigFont() {
		glTranslatef(0, 0, -6.0f);
	}

	void ViewingSmallFont() {
		glTranslatef(0, 0, -8.0f);
	}

	/*
	void ButtonV1(const char* a, short style) {
	glRotatef(-90,0,0,1.0f);
	if (style==0) {
	int len = (int) strlen(a);
	float padding = 0.05;
	PrintFontV1(a,len);
	glTranslatef(-padding, -padding, 0);
	//Rect(0.5+ 3* padding, len*0.6 + 2* padding);
	glTranslatef(padding,padding,0);
	}
	glRotatef(90,0,0,1.0f);
	}
	*/

	void Line(float x1, float y1, float x2, float y2) {
		if (x1 == x2 && y1 == y2) return;
		float lineverts[] = { x1,y1, x2,y2 };
		glVertexPointer(2, GL_FLOAT, 0, lineverts);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_LINES, 0, 2);
	}

	void Circle(float r, short segments) {
		double lx = r* cos(0.0f);
		double ly = r* sin(0.0f);
		for (double th = 3.1417 / segments; th<3.1417 * 2; th += 3.1417 / segments) {
			float x = r* cos(th);
			float y = r* sin(th);
			Line(lx, ly, x, y);
			lx = x;
			ly = y;
		}
	}

	void Rect(float w, float h) {
		float squareverts[] = { 0,0, 0,h, 0,0, w,0, 0,h, w,h, w,h, w,0 };
		glVertexPointer(2, GL_FLOAT, 0, squareverts);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(GL_LINES, 0, 8);
	}
	/*
	void PrintFontV1(const char* a, short len) {
	glPushMatrix();
	int j = 0;
	for (int i=0; i<len; i++) {
	if (a[i]==' ') {glTranslatef(0,0.5f,0); continue;}
	if (a[i]=='\n') {j = (i-j); glTranslatef(0.7,-0.6f*j,0); continue;}
	DrawFontV1Char(a[i]);
	glTranslatef(0,0.6f,0);   						// Move Left 1.5 Units And Into The Screen 6.0
	}
	glPopMatrix();
	}
	*/
	void Flush(TextureImage* timg, bool NORMALS, bool COLORS, bool TEXTCOORDS) {

		if (TEXTCOORDS) {
			if (timg->texID == 0) timg->texID = 1;
			glBindTexture(GL_TEXTURE_2D, timg->texID); //[filter]
		}

		glVertexPointer(3, GL_FLOAT, 0, v);
		if (TEXTCOORDS) glTexCoordPointer(2, GL_FLOAT, 0, t);
		if (NORMALS) glNormalPointer(GL_FLOAT, 0, n);
		if (COLORS) glColorPointer(4, GL_FLOAT, 0, c);

		glEnableClientState(GL_VERTEX_ARRAY);
		if (NORMALS) glEnableClientState(GL_NORMAL_ARRAY);
		if (TEXTCOORDS) glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		if (COLORS) glEnableClientState(GL_COLOR_ARRAY);

		glDrawArrays(this->MODE, 0, (iver / 3));

	}
#endif

	void alBegin(int mode) {

	}

	void alEnd() {
	}

	void SquareSprite() {
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);//1
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);//2
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);//3
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);//3
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);//4
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);//1		
	}

	void alTranslatef(GLfloat x, GLfloat y, GLfloat z) {
		glTranslatef(x, y, z);
	}


	void glNormal3f(GLfloat x, GLfloat y, GLfloat z) {
		n[inor] = x; n[inor + 1] = y; n[inor + 2] = z;
		inor += 3;
	}

	void glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
		v[iver] = x; v[iver + 1] = y; v[iver + 2] = z;
		iver += 3;
	}
	void glTexCoord2f(GLfloat x, GLfloat y) {
		t[itex] = x; t[itex + 1] = y;
		itex += 2;
	}

	void glColor4f(float r, float g, float b, float a) {
		c[icol] = r; c[icol + 1] = g; c[icol + 2] = b; c[icol + 3] = a;
		icol += 4;
	}

	void glColor3f(float r, float g, float b) {
		if (icol>2044) return;
		c[icol] = r; c[icol + 1] = g; c[icol + 2] = b; c[icol + 3] = 1.0f;
		icol += 4;
	}
	void RandomDrawColor() {
		glColor4f(randm(), randm(), randm(), 1.0f);
	}


};
#endif


#ifndef NOGL

class PEG {

	FILE* logfile;

public:

	void * pulled_param1;
	void * pulled_param2;
	int pulled_i1;
	int pulled_i2;

	class CMD {
	public:
		int command;
		void* param1;
		void* param2;
		int i1;
		int i2;
		float f1;
		float f2;
		char type;

		void zero() {
			type = 'P';
			command = 0;
			param1 = 0;
			param2 = 0;
			i1 = 0;
			i2 = 0;
			f1 = 0.0f;
			f2 = 0.0f;
		}
	};

	int indx_r;
	int indx_w;
	int load;

	CMD cmd[1024];


	int getLoad() {
		return (indx_w - indx_r);
	}

	PEG() {
		for (int i = 0; i<1023; i++) cmd[i].zero();
		indx_r = 0;
		indx_w = 0;
	}

	~PEG() {
		if (logfile)
			fclose(logfile);
	}

	void pushP(int command, void* param1=0, void* param2 = 0) {
		cmd[indx_w].command = command;
		cmd[indx_w].param1 = param1;
		cmd[indx_w].param2 = param2;
		cmd[indx_w].type = 'P';

		indx_w++;

		if (indx_w>1023) {
			indx_w = 0;
		}
	}

	void pushI(int command, int i1, int i2) {
		cmd[indx_w].command = command;
		cmd[indx_w].i1 = i1;
		cmd[indx_w].i2 = i2;

		cmd[indx_w].type = 'I';

		indx_w++;
		if (indx_w>1023) {
			indx_w = 0;
		}
	}

	void pushF(int command, float f1, float f2) {
		cmd[indx_w].command = command;
		cmd[indx_w].f1 = f1;
		cmd[indx_w].f2 = f2;
		cmd[indx_w].type = 'F';
		indx_w++;
		if (indx_w>1023) {
			indx_w = 0;
		}
	}

	void push(PEG::CMD* c) {
		if (c->command) {
			cmd[indx_w].command = c->command;
			cmd[indx_w].f1 = c->f1;
			cmd[indx_w].f2 = c->f2;
			cmd[indx_w].i1 = c->i1;
			cmd[indx_w].i2 = c->i2;
			cmd[indx_w].param1 = c->param1;
			cmd[indx_w].param2 = c->param2;
			cmd[indx_w].type = c->type;

			indx_w++;
			if (indx_w>1023) {
				indx_w = 0;
			}
		}
	}

	bool test()
	{
		PEG t;
		float checksumPush = 0;
		float checksumPull = 0;
		int cmd = 0;
		int j = 0;
		for (j = 0; j<120; j++) {

			float x = cmd*0.1f;
			float y = cmd*0.2f;

			//Push 120 items
			checksumPush += cmd + x + y;
			t.pushF(cmd, x, y);
			cmd += 3;
		}

		for (j = 0; j<120; j++) {
			CMD* r = t.pull();
			float x = r->f1;
			float y = r->f2;
			checksumPull += r->command + x + y;
		}

		bool ret = (checksumPush == checksumPull);

		return ret;
	}

	char nextPullType()
	{
		CMD* ret = &cmd[indx_r];
		return ret->type;
	}

	CMD* pull() {
		if (indx_r>1023) { indx_r = 0; /*cmd[indx].command = CMD_ERR;*/ };

		//CLEAR OLD COMMAND
		short lastindx_r = indx_r - 1;
		if (lastindx_r == -1) lastindx_r = 1023;
		cmd[lastindx_r].command = 0;

		//GET CURRENT
		CMD* ret = &cmd[indx_r];
		if (ret->command) indx_r++;

		pulled_param1 = ret->param1;
		pulled_param2 = ret->param2;

		if (ret->type == 'I') {
			pulled_i1 = ret->i1;
			pulled_i2 = ret->i2;
		}
		return ret;
	}

};


char Gesture(int x, int y) {

	static PEG history;

	static int pos[2][2] = { { 0,0 },{ 0,0 } };
	static short ip = 0;

	pos[ip][0] = x;
	pos[ip][1] = y;

	short dx = (pos[1][0] - pos[0][0]);
	short dy = (pos[1][1] - pos[0][1]);

	bool valid = !(pos[1][0] == 0);

	bool w_right = dx>4;
	bool w_left = dx<4;
	bool w_up = dy<4;
	bool w_down = dy>4;

	short adx = abs(dx);
	short ady = abs(dy);

	//float th;
	//th = tan((float)dy+0.00001f) / ((float)dx+0.00001f);

	bool sw_right = (w_right && ady == 0);
	bool sw_left = (w_left  && ady == 0);
	bool sw_up = (w_up && adx == 0);
	bool sw_down = (w_down && adx == 0);

	bool sw_null = !sw_right && !sw_left && !sw_up && !sw_down;

	ip++;
	if (ip>1) ip = 0;

	char r = 0;

	if (valid && ip == 0 && !sw_null) {
		if (sw_right) r = 'R';
		if (sw_left)   r = 'L';
		if (sw_up)    r = 'U';
		if (sw_down) r = 'D';
	}
	else return 0;

	const int nprev = 30;
	char rr[nprev];
	short hits = 0;
	for (int i = 0; i<nprev; i++) {
		rr[i] = history.pull()->i1;
		if (rr[i] == r) hits++;
	}

	history.pushI(CMD_TOUCHMOVE, r, 0);

	//if (hits>15)
	if (rr[0] == rr[1] && rr[1] == rr[2] && rr[2] == rr[3] && rr[3] == rr[4])
	{

		//while (history.pull()->i1) {
		// FLUSH
		//}
		return r;
	}
	else
		return 0;
}

#define IPHONE_SCREEN_WIDTH 320
#define IPHONE_SCREEN_HEIGHT 480
#define ANDROID_SCREEN_WIDTH 320
#define ANDROID_SCREEN_HEIGHT 480



class CModel {

#ifndef METRO
	static aL10 AL10;
#endif

public:
	int index;
	char name[64];
	float vertex_array[512 * 512 * 6];
	float normals_array[512 * 512 * 6];
	unsigned char color_array[512 * 512 * 5];
	unsigned short indices_array[1024 * 3];
	float uv_array[512 * 512 * 4];

	float vertex_array_gl[1];
	float normals_array_gl[1];
	unsigned short indices_array_gl[1];
	float uv_array_gl[1];

	TextureImage texture[1];
	int textureWidth;

	int n_indices_accessors;
	int n_indices;
	int n_vertices;
	int n_normals;
	int n_uv;
	int n_colors;
	int INDICES_DRAWMODE;
	int* loaded;
	float fscale;
	GLuint vbo;
	GLuint vboNormals;

	bool noVBO;

	void init() {
		n_vertices = 0;
		n_normals = 0;
		n_colors = 0;
		n_indices = 0;
		n_uv = 0;
		fscale = 1.0f;
		loaded = &n_vertices;
		index = 0;
		noVBO = false;
		_scaleX = 1;
		_scaleY = 1;
		_scaleZ = 1;
		DRAWMODE = GL_TRIANGLES;
	}
	
	CModel() {
		init();
	}

	~CModel() {
#ifndef NOGL
#ifndef WIN32
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &vboNormals);
#endif
#endif
	}

	//called by resourcemanager
	void onLoad() {

#ifdef WIN32
		noVBO = true;
#endif

		if (!noVBO) {
#ifndef NOGL
#ifndef WIN32
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, n_vertices * 3 * sizeof(GLfloat), &vertex_array[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenBuffers(1, &vboNormals);
			glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
			glBufferData(GL_ARRAY_BUFFER, n_normals * 3 * sizeof(GLfloat), &normals_array[0], GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif      
#endif
		}
		if (n_indices == 0) {
			for (int i = 0; i<n_vertices; i++) {

			}
		}

	}

	//tries to get max depth of model
	float originalWidth() {
		return textureWidth * 2;
	}

	//tries to get max depth of model
	float boundx() {
		float xmax = 0;
		for (int i = 0; i<n_vertices * 3; i+=3) {
			xmax = (vertex_array[i]>xmax ? vertex_array[i] : xmax);
		}
		return xmax;
	}
    float boundy() {
        float ymax = 0;
        for (int i = 0; i<n_vertices * 3; i+=3) {
            ymax = (vertex_array[i+1]>ymax ? vertex_array[i+1] : ymax);
        }
        return ymax;
    }
    float boundz() {
        float zmax = 0;
        for (int i = 0; i<n_vertices * 3; i+=3) {
            zmax = (vertex_array[i+2]>zmax ? vertex_array[i+2] : zmax);
        }
        return zmax;
    }

	void info(char* o) {
		if (this->name[0]) { strcpy(o, "Name="); strcat(o, this->name); }
		char stats[128];
		sprintf(stats, "\n%d Vertices\n%d Colors\n%d Normals\n%d Texture Coords\n%d Indices\ntexId=%d", this->n_vertices, this->n_colors, this->n_normals, this->n_uv, this->n_indices, texture[0].texID);
		strcat(o, stats);
	}

	float _scaleX, _scaleY, _scaleZ = 1.0;

	void scale(float v) {
		for (int i = 0; i< n_vertices * 3; i++)
		{
			vertex_array[i] *= v;
		}
		fscale *= v;
		//phys.boundz*=v;
	}

	void glDrawLocalAxis()
	{

	}

	void SetScale(float sx, float sy, float sz) {
		_scaleX = sx;
		_scaleY = sy;
		_scaleZ = sz;
	}
#ifndef NOGL
	void glDraw(bool wireframe_mode = false) {
		glPushMatrix();
		glScalef(_scaleX, _scaleY, _scaleZ);
		glDrawEx(wireframe_mode);
		glPopMatrix();
	}

	int DRAWMODE;

	void glDrawEx(bool wireframe_mode)
	{

#ifdef WIN32
		noVBO = true;
#endif

		if (n_vertices) {
			if (noVBO) {
				glVertexPointer(3, GL_FLOAT, 0, vertex_array);
			}
			else {
				glVertexPointer(3, GL_FLOAT, 0, 0);
			}
			glEnableClientState(GL_VERTEX_ARRAY);
		}

		/*
		if (n_colors) {
		if (noVBO) {
		glColorPointer(4, GL_BYTE, 0, color_array);
		} else {
		glColorPointer( 4, GL_BYTE, 0, 0 );
		}
		glEnableClientState(GL_COLOR_ARRAY);
		} else {
		glDisableClientState(GL_COLOR_ARRAY);
		}
		*/

		if (!wireframe_mode) {
			if (n_uv>3) {
				//if (texture[0].texID==0) texture[0].texID = index+1; //Attemp to Attach De-Faulted TextureID
				glBindTexture(GL_TEXTURE_2D, texture[0].texID);
				glTexCoordPointer(2, GL_FLOAT, 0, uv_array);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glEnable(GL_TEXTURE_2D);
			}
		}
		else {
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_TEXTURE_2D);
		}

		if (n_normals) {
			if (noVBO) glNormalPointer(GL_FLOAT, 0, normals_array); else {
#ifndef WIN32
				glEnableClientState(GL_NORMAL_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
				glNormalPointer(GL_FLOAT, 0, 0);//NoVBO=//glNormalPointer(GL_FLOAT, 0, normals_array);
#endif
			}
		}

		if (n_indices == 0) {
			if (!noVBO) {
#ifndef WIN32
				glEnableClientState(GL_VERTEX_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glVertexPointer(3, GL_FLOAT, 0, 0);
#endif
			}
			glDrawArrays(wireframe_mode ? GL_LINE_STRIP : DRAWMODE, 0, n_vertices);
#ifndef WIN32
			if (!noVBO) glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
		}
		else
			glDrawElements(wireframe_mode ? GL_LINE_STRIP : DRAWMODE, n_indices, GL_UNSIGNED_SHORT, indices_array);

		glDisableClientState(GL_NORMAL_ARRAY);

		if (n_uv>3) {
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_TEXTURE_2D);
		}
	}

#endif

	void loadSeg(FILE* fl, short ver, char type, void* ptr)
	{

		//short v;
		//char t;
		int l = 0;

		//int n = (int) fread(&v, 1, sizeof(short), fl);
		//n = (int) fread(&t, 1, sizeof(char), fl);
		//n = (int) fread(&l, 1, sizeof(int), fl);

		if (type == 'V') n_vertices = l / sizeof(float) / 3;
		if (type == 'N') n_normals = l / sizeof(float) / 3;
		if (type == 'T') n_uv = l / sizeof(float) / 2;
		if (type == 'I') n_indices = l / sizeof(int);

		fread(ptr, 1, l, fl);

	}

	void loadVnt(char* objname)
	{
		char fname[64];
		sprintf(fname, "%s.vnt", objname);

		FILE*f = fopen(fname, "rb");
		short ver = 1;
		if (f)
		{
			loadSeg(f, ver, 'V', vertex_array_gl);
			loadSeg(f, ver, 'N', normals_array_gl);
			loadSeg(f, ver, 'T', uv_array_gl);
			loadSeg(f, ver, 'I', indices_array_gl);

			fclose(f);
		}

	}

	void saveSeg(FILE* fl, short ver, char type, int len, void* ptr)
	{
		fwrite(&ver, 1, sizeof(short), fl);
		fwrite(&type, 1, sizeof(char), fl);
		fwrite(&len, 1, sizeof(int), fl);
		fwrite(ptr, 1, len, fl);
	}

	void setFinalArray(char type, int n_items, float* array)
	{
		int nbytesrequired = 0;
		char* ptr = 0;

		switch (type) {
		case 'V':
		{n_vertices = n_items; ptr = (char*)vertex_array_gl; nbytesrequired = n_items * sizeof(float) * 3; }
		break;
		case 'N':
		{n_normals = n_items; ptr = (char*)normals_array_gl; nbytesrequired = n_items * sizeof(float) * 3; }
		break;
		case 'T':
		{n_uv = n_items; ptr = (char*)uv_array_gl; nbytesrequired = n_items * sizeof(float) * 2; }
		break;
		case 'I':
		{n_indices = n_items; ptr = (char*)indices_array_gl; nbytesrequired = n_items * sizeof(int); }
		break;
		default:
			break;
		}

		memcpy(ptr, array, nbytesrequired);

	}

	void dae_geometry(char* string)
	{
		char objname[12];
		sprintf(objname, "%s", name);

		sprintf(string, "<geometry id='%s' name='%s'>", objname, objname);

		strcat(string, "<mesh>");

		char srcid[16];
		char szFloatArray[64 * 1024];
		float* arr_gl;


		for (int i = 0; i<3; i++) {

			bool skip = true;

			if (i == 0) { sprintf(srcid, "Position"); arr_gl = vertex_array_gl; if (n_vertices) skip = false; }
			if (i == 1) { sprintf(srcid, "Normals"); arr_gl = normals_array_gl; if (n_normals) skip = false; }
			if (i == 2) { sprintf(srcid, "UV"); arr_gl = uv_array_gl; if (n_uv) skip = false; }

			if (skip) continue;


			char string1[128];
			sprintf(string1, "<source id='%s-%s'>", objname, srcid);

			strcat(string, string1);

			int estsizeofstring = 64 * 1024;

			int l = float2string((char*)szFloatArray, (float*)arr_gl, (int)n_vertices * 3, (char*)srcid);

			if (l>estsizeofstring) {
				sprintf(string, "REQ MEMORY BIGGER THAN <<MONKEY>>  dae_geometry()");
			}
			else {
				strcat(string, szFloatArray);
			}

			int stride = (srcid[0] == 'U' ? 2 : 3);
			sprintf(szFloatArray, "<technique_common><accessor count='%i' source='#%s-%s-array' stride='%i'>",
				n_vertices, objname, srcid, stride
			);

			strcat(string, szFloatArray);
			if (srcid[0] != 'U')
				strcat(string, "<param type='float' name='X'></param><param type='float' name='Y'></param><param type='float' name='Z'></param></accessor></technique_common>\n");
			else
				strcat(string, "<param type='float' name='S'></param><param type='float' name='T'></param></accessor></technique_common>\n");

			strcat(string, "</source>\n");
		}

		sprintf(szFloatArray, "<vertices id='%s-Vertex'><input semantic='POSITION' source='#%s-Position'/></vertices>\n", objname, objname);

		strcat(string, szFloatArray);

		sprintf(szFloatArray, "<triangles count='%i'>\n", n_vertices / 3);

		strcat(string, szFloatArray);

		sprintf(szFloatArray, "<input offset='0' semantic='VERTEX' source='#%s-Vertex'/>", objname);
		strcat(string, szFloatArray);

		sprintf(szFloatArray, "<input offset='1' semantic='NORMAL' source='#%s-Normals'/>", objname);
		strcat(string, szFloatArray);

		strcat(string, "<p>");

		for (int i = 0; i<n_vertices; i++) {
			sprintf(szFloatArray, "%i %i ", i, i);
			strcat(string, szFloatArray);
		}

		strcat(string, "</p>");

		strcat(string, "</triangles>\n");

		strcat(string, "</mesh>\n");

		strcat(string, "</geometry>\n");

	}

	int float2string(char* string, float* array, int len, char* pnui)
	{
		string[0] = 0;

		char fs[32];
		sprintf(string, "<float_array count='%i' id='%s-%s-array'>", len, name, pnui);

		for (int i = 0; i<len; i++) {
			sprintf(fs, "%.5f", array[i]);
			strcat(string, fs);
			if (i != len - 1) strcat(string, " ");
		}
		strcat(string, "</float_array>");

		int l = int(strlen(string));

		return l;
	}

	void saveDAE(char* objname)
	{
		char fname[64];
		sprintf(fname, "%s.dae", objname);

		FILE*f = fopen(fname, "wb");

		if (f)
		{

			fprintf(f, "<?xml version='1.0' encoding='utf-8'?>");
			fprintf(f, "<COLLADA version='1.4.0' xmlns='http://www.collada.org/2005/11/COLLADASchema'>");
			/*
			fprintf(f, "<asset>");
			fprintf(f, "<contributor>");
			fprintf(f, "<author>Acnodelabs - http://acnodelabs.com</author>");
			fprintf(f, "<authoring_tool>Alge GDK - Acnodelabs Collada Exporter v:1.0</authoring_tool>");
			fprintf(f, "<comments></comments>");
			fprintf(f, "<copyright></copyright>");
			fprintf(f, "<source_data>file://</source_data>");
			fprintf(f, "</contributor>");
			fprintf(f, "<created>2010-09-20T20:43:50.388788</created>");
			fprintf(f, "<modified>2010-09-20T20:43:50.388838</modified>");
			fprintf(f, "<unit meter='0.01' name='centimeter'/>");
			fprintf(f, "<up_axis>Z_UP</up_axis>");
			fprintf(f, "</asset>");
			*/

			fprintf(f, "<library_cameras><camera id='Camera-Camera' name='Camera-Camera'><optics><technique_common><perspective><yfov>49.13434</yfov><znear>0.1</znear><zfar>100.0</zfar></perspective></technique_common></optics></camera></library_cameras>");

			fprintf(f, "<library_lights><light id='Spot' name='Spot'><technique_common><point><color>1.00000 1.00000 1.00000</color><constant_attenuation>1.0</constant_attenuation><linear_attenuation>0.0</linear_attenuation><quadratic_attenuation>0.0</quadratic_attenuation></point></technique_common></light></library_lights>");

			fprintf(f, "<library_geometries>");
			char geom[256 * 1024];
			dae_geometry(geom);
			fprintf(f, "%s", geom);
			fprintf(f, "</library_geometries>");


			fprintf(f, "<library_visual_scenes><visual_scene id='Scene'>");
			fprintf(f, "<node layer='L1' id='Cube' name='Cube'>");
			fprintf(f, "<translate sid='translate'>0.00000 0.00000 0.00000</translate>");
			fprintf(f, "<rotate sid='rotateZ'>0 0 1 0.00000</rotate>");
			fprintf(f, "<rotate sid='rotateY'>0 1 0 -0.00000</rotate>");
			fprintf(f, "<rotate sid='rotateX'>1 0 0 0.00000</rotate>");
			fprintf(f, "<scale sid='scale'>4.72433 4.72433 4.72433</scale>");
			fprintf(f, "<instance_geometry url='#%s'></instance_geometry>", name);
			fprintf(f, "</node>");

			fprintf(f, "<node layer='L1' id='Lamp' name='Lamp'>");
			fprintf(f, "<translate sid='translate'>4.07625 1.00545 5.90386</translate>");
			fprintf(f, "<rotate sid='rotateZ'>0 0 1 106.93632</rotate>");
			fprintf(f, "<rotate sid='rotateY'>0 1 0 3.16371</rotate>");
			fprintf(f, "<rotate sid='rotateX'>1 0 0 37.26105</rotate>");
			fprintf(f, "<scale sid='scale'>1.00000 1.00000 1.00000</scale>");
			fprintf(f, "<instance_light url='#Spot'/>");
			fprintf(f, "</node>");
			fprintf(f, "<node layer='L1' id='Camera' name='Camera'>");
			fprintf(f, "<translate sid='translate'>7.48113 -6.50764 5.34367</translate>");
			fprintf(f, "<rotate sid='rotateZ'>0 0 1 46.69194</rotate>");
			fprintf(f, "<rotate sid='rotateY'>0 1 0 0.61977</rotate>");
			fprintf(f, "<rotate sid='rotateX'>1 0 0 63.55930</rotate>");
			fprintf(f, "<scale sid='scale'>1.00000 1.00000 1.00000</scale>");
			fprintf(f, "<instance_camera url='#Camera-Camera'/>");
			fprintf(f, "</node>");

			fprintf(f, "</visual_scene>");
			fprintf(f, "</library_visual_scenes>");
			fprintf(f, "<scene>");
			fprintf(f, "<instance_visual_scene url='#Scene'/>");
			fprintf(f, "</scene>");


			fprintf(f, "</COLLADA>");
			fclose(f);
		}
	}

	void saveVnt(char* objname)
	{
		char fname[64];
		sprintf(fname, "%s.vnt", objname);

		FILE*f = fopen(fname, "wb");
		short ver = 1;
		if (f)
		{
			saveSeg(f, ver, 'V', n_vertices * 3 * sizeof(float), vertex_array_gl);
			saveSeg(f, ver, 'N', n_normals * 3 * sizeof(float), normals_array_gl);
			saveSeg(f, ver, 'T', n_uv * 2 * sizeof(float), uv_array_gl);
			saveSeg(f, ver, 'I', n_indices * sizeof(int), indices_array_gl);

			fclose(f);
		}

	}

	void fillGLarrays()
	{
		int j = 0;
		int j_3 = 0;

		bool no_tex;
		bool no_normals;

		for (int i = 0; i<n_indices*n_indices_accessors; i += n_indices_accessors) {

			no_tex = (n_indices_accessors<3);
			no_normals = (n_indices_accessors<2);

			int iver = indices_array[i];
			int ino = indices_array[i + 1];
			int itx = indices_array[i + 2];

			float vx = vertex_array[3 * iver];
			float vy = vertex_array[3 * iver + 1];
			float vz = vertex_array[3 * iver + 2];

			float nx = normals_array[3 * ino];
			float ny = normals_array[3 * ino + 1];
			float nz = normals_array[3 * ino + 2];

			float tu = uv_array[2 * itx];
			float tv = uv_array[2 * itx + 1];

			indices_array_gl[j] = j;

			vertex_array_gl[j_3] = vx;
			vertex_array_gl[j_3 + 1] = vy;
			vertex_array_gl[j_3 + 2] = vz;

			if (!no_normals) {
				normals_array_gl[j_3] = nx;
				normals_array_gl[j_3 + 1] = ny;
				normals_array_gl[j_3 + 2] = nz;
			}

			if (!no_tex) {
				uv_array_gl[2 * j] = tu;
				uv_array_gl[2 * j + 1] = tv;
			}
			j++;
			j_3 += 3;
		}

		if (n_vertices) n_vertices = j;
		if (n_normals) n_normals = j;
		if (n_indices) n_indices = j;
		if (n_uv) n_uv = j;

		if (no_tex) n_uv = 0;
		if (no_normals) n_normals = 0;
	}


	void setName(char* n) {
		strcpy(name, n);
	}

};

#endif //nogl



class FontMap16x16 {

public:
	CModel* m;
	short seq;
	short row1;
	short lut[16][16];
	short mapX[16 * 16];
	short mapY[16 * 16];
	short width;
	short spacing;

	void SetScale(float _scale) {
		scale = _scale;
		spacing = 1.5f * scale;
		width = 256 * scale;
	}

	FontMap16x16() {
		m = 0;
		int run = 32;
		SetScale(1);
		for (int row = 0; row<16; row++) {
			for (int col = 0; col<16; col++) {
				lut[row][col] = run;
				mapX[run - 32] = col;
				mapY[run - 32] = row;
				run++;
			}
		}
	}

	void usetexof(CModel* mod) {
		m = mod;
#ifndef NOGL
#ifndef METRO
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
#endif
#endif
		mod->noVBO = true;
	}

	void chardata(short indx, char c) {
		if (m == 0) return;
		seq = c - ' ';
		short co = mapX[seq];
		short ro = mapY[seq];
		float left = co / 16.0f;
		float top = ro / 16.0f;
		float down = top + 1.0f / 16.0f;
		float right = left + 1.0f / 16.0f;
		top = 1.0f - top;
		down = 1.0f - down;

		short index12 = indx * 12;
		short index = indx * 18;

		m->uv_array[index12 + 0] = right;
		m->uv_array[index12 + 1] = top;
		m->uv_array[index12 + 2] = left;
		m->uv_array[index12 + 3] = top;
		m->uv_array[index12 + 4] = left;
		m->uv_array[index12 + 5] = down;

		m->uv_array[index12 + 6] = right;
		m->uv_array[index12 + 7] = top;
		m->uv_array[index12 + 8] = left;
		m->uv_array[index12 + 9] = down;
		m->uv_array[index12 + 10] = right;
		m->uv_array[index12 + 11] = down;
		m->n_uv = 6 * (indx + 1);

		short cx = indx;

		//FILL VERTEXARRAY/NORMALS OF CMODEL
		m->vertex_array[index + 0] = cx + 1;
		m->vertex_array[index + 1] = 1;
		m->vertex_array[index + 2] = 0;
		m->normals_array[index + 0] = 0;
		m->normals_array[index + 1] = 0;
		m->normals_array[index + 2] = 1;

		m->vertex_array[index + 3] = cx - 1;
		m->vertex_array[index + 4] = 1;
		m->vertex_array[index + 5] = 0;
		m->normals_array[index + 3] = 0;
		m->normals_array[index + 4] = 0;
		m->normals_array[index + 5] = 1;

		m->vertex_array[index + 6] = cx - 1;
		m->vertex_array[index + 7] = -1;
		m->vertex_array[index + 8] = 0;
		m->normals_array[index + 6] = 0;
		m->normals_array[index + 7] = 0;
		m->normals_array[index + 8] = 1;

		m->vertex_array[index + 9] = cx + 1;
		m->vertex_array[index + 10] = 1;
		m->vertex_array[index + 11] = 0;
		m->normals_array[index + 9] = 0;
		m->normals_array[index + 10] = 0;
		m->normals_array[index + 11] = 1;

		m->vertex_array[index + 12] = cx - 1;
		m->vertex_array[index + 13] = -1;
		m->vertex_array[index + 14] = 0;
		m->normals_array[index + 12] = 0;
		m->normals_array[index + 13] = 0;
		m->normals_array[index + 14] = 1;

		m->vertex_array[index + 12] = cx - 1;
		m->vertex_array[index + 13] = -1;
		m->vertex_array[index + 14] = 0;
		m->normals_array[index + 12] = 0;
		m->normals_array[index + 13] = 0;
		m->normals_array[index + 14] = 1;

		m->vertex_array[index + 15] = cx + 1;
		m->vertex_array[index + 16] = -1;
		m->vertex_array[index + 17] = 0;
		m->normals_array[index + 15] = 0;
		m->normals_array[index + 16] = 0;
		m->normals_array[index + 17] = 1;
		m->n_normals = 6 * (indx + 1);
		m->n_vertices = 6 * (indx + 1);



	}

	int x1, y1;
	float scale;
	//
	public:
	void print(char* sz) {
		int l = int(strlen(sz));
		for (int i = 0; i<l; i++)
			chardata(i, sz[i]);
		m->scale(scale);
	}
};



#undef PI
#define PI 3.1415926535897932f

void rotPoint(float*x1, float*y1, float degrees, float x, float y) {
	float angle = degrees * PI / 180.0f;
	*x1 = x * cos(angle) - y * sin(angle);
	*y1 = x * sin(angle) + y * cos(angle);
}


// Definition of one GL object in this demo.
typedef struct {
	/* Vertex array and color array are enabled for all objects, so their
	* pointers must always be valid and non-NULL. Normal array is not
	* used by the ground plane, so when its pointer is NULL then normal
	* array usage is disabled.
	*
	* Vertex array is supposed to use GL_FIXED datatype and stride 0
	* (i.e. tightly packed array). Color array is supposed to have 4
	* components per color with GL_UNSIGNED_BYTE datatype and stride 0.
	* Normal array is supposed to use GL_FIXED datatype and stride 0.
	*/
	GLfloat *vertexArray;
	GLubyte *colorArray;
	GLfloat *normalArray;
	GLint vertexComponents;
	GLsizei count;
} GLOBJECT;


typedef struct {
	float x, y, z;
} VECTOR3;

class CAlObject {
public:
	CModel* model;
	char name[16];
	int TexId;

	float scalex;
	float scaley;
	float scalez;

	float translatex;
	float translatey;
	float translatez;

	float rotatex;
	float rotatey;
	float rotatez;
};

class CHelp {
public:
	void WhereDoIPlaceFiles(char* tag) {
		char f[256] = { 0 };
		strcpy(f, "PlaceFilesHereEtc");
		strcat(f, tag);
	}
};

#define numModels 50
#define numObjects 20

/* For Future Use Assimp based Scene
class CScene : public aiScene {
public:
};
*/
class CAsset: public CModel {
	//CScene* scene;
public:
	CAsset() {
		init();
	}

	//http://assimp.sourceforge.net/lib_html/usage.html
	CModel* ImportSceneFromFile(const std::string& pFile)
	{
		/* Create an instance of the Importer class
		Assimp::Importer importer;

		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll 
		// propably to request more postprocessing than we do in this example.
		scene = (CScene*)importer.ReadFile(pFile,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);

		// If the import failed, report it
		if (!scene)
		{
			return nullptr;
		}

		*/
		// We're done. Everything will be cleaned up by the importer destructor
		return (CModel*)this;
	}

	~CAsset() {
		
	}

};

class CResourceManager {
	//std::mutex rmutex;
public:
	std::vector<CModel*> cmodels;

	CModel* models[numModels];
	CAlObject* alObject[numModels];
	char resourcepath[256];
	char error[64];

	

	CResourceManager() {
		resourcepath[0] = 0;
	}

	void Init(char* respath) {
		strcpy(resourcepath, respath);
	}

	int pickArray(FILE* file, float* toPtr) {

		char line[64];
		int numvals = 0;
		int zoom = 1;
		fscanf(file, "%s", line);
		char* ebrace = 0;
		while (strstr(line, "=")) {

			if (strstr(line, "count=")) {
				numvals = atoi(line + 7);
			}

			ebrace = strstr(line, ">");

			if (ebrace) {
				toPtr[0] = atof(ebrace + 1);
			}

			fscanf(file, "%s", line);
		}
		int iver = 1;
		for (iver = (ebrace == 0 ? 0 : 1); iver<numvals; iver++) {
			toPtr[iver] = atof(line)*zoom;
			fscanf(file, "%s", line);
		}
		toPtr[iver] = atof(line)*zoom;
		return iver;
	}

	CModel* loadGenericAsset(string filename, int modelId)
	{
		string fname = string(resourcepath) + filename;
		CAsset * anAsset = new CAsset();
		models[modelId] = (CModel*)(anAsset->ImportSceneFromFile(fname), modelId);
		return models[modelId];
	}

	void loadColladaModel(const char* fname, int modelId)
	{
		models[modelId] = new CModel;

#define NN 1

		FILE* file = fopen(fname, "rb");
		char line[128];
		if (file) {

			while (!feof(file)) {
				fscanf(file, "%s", line);

				if (strcmp(line, "<source") == 0) {
					fscanf(file, "%s", line);
					bool id_0 = strstr(line, "id=") != NULL;
					bool id_pos = strstr(line, "Position") != NULL;
					bool id_nrm = strstr(line, "Normal") != NULL;
					bool id_uv = strstr(line, "UV") != NULL;
					float* toPtr;

					if (id_pos) toPtr = models[modelId]->vertex_array;
					if (id_nrm) toPtr = models[modelId]->normals_array;
					if (id_uv) toPtr = models[modelId]->uv_array;

					if (id_0 && (id_pos || id_nrm || id_uv)) {
						fscanf(file, "%s", line);
						if (strcmp(line, "<float_array") == 0) {
							int c = pickArray(file, toPtr);
							if (id_pos) {
								models[modelId]->n_vertices = c / 3;
							}
							if (id_nrm) {
								models[modelId]->n_normals = c / 3;
							}
							if (id_uv) {
								models[modelId]->n_uv = c / 2;
							}

						}
					}
				}

				//	int somecount=0;

				if (strstr(line, "count=") != NULL) {
					//somecount=atoi(line+7);
				}

				if (strstr(line, "-UV-array") != NULL) {
					//	[self pickArray:file:models[modelId]->uv_array];
				}

				if (!strcmp(line, "<triangles")) {
					fscanf(file, "%s", line);
					if (strstr(line, "count=") != NULL) models[modelId]->n_indices = atof(line + 7) * 3;

					fscanf(file, "%s", line);

					models[modelId]->n_indices_accessors = 0;
					bool p = false;
					do {
						fscanf(file, "%s", line);
						if (strstr(line, "offset") != NULL) models[modelId]->n_indices_accessors++;

						if (line[0] == '<' && line[1] == 'p') p = true;
					} while (!p && !feof(file));

					models[modelId]->indices_array[0] = (unsigned short)atoi(line + 3);
					//fscanf(file, "%s", line);
					//int n1 = atoi(line);


					for (int ii = 1; ii< models[modelId]->n_indices * 3; ii++) {
						fscanf(file, "%s", line);
						int v1 = atoi(line);
						//fscanf(file, "%s", line);
						//int n1 = atoi(line);

						models[modelId]->indices_array[ii] = (unsigned short)v1;
					}
				}
			}

			fclose(file);
		}

		models[modelId]->fillGLarrays();
	}

	char filename[256];

	//Accepts converted images from http://image.online-convert.com/convert-to-tga
	//Must be 32 bpp for RGBA and 24 bpp for RGB stored without compression
	//
	bool LoadTGA(TextureImage* ti, char* fn)			// Loads A TGA File Into Memory
	{

		TextureImage *texture = (TextureImage *)ti;

		sprintf(filename, "%s/%s", resourcepath, (char*)fn);
		GLubyte		TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };	// Uncompressed TGA Header
		GLubyte		TGAcompare[12];								// Used To Compare TGA Header
		GLubyte		header[6];									// First 6 Useful Bytes From The Header
		GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
		GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
		GLuint		temp;										// Temporary Variable
#ifndef GL_RGBA
#define GL_RGBA                           0x1908
#define GL_RGB                            0x1907
#endif
																// Set The Default GL Mode To RBGA (32 BPP)
		GLuint		type = GL_RGBA;
		//FILE *filex = fopen("LoadTgaFolder", "wb+");			// Open The TGA File
		//	fwrite("Here", 1, 4, filex);
		//fclose(filex);

		FILE *file = fopen(filename, "rb");						// Open The TGA File
																//FILE *file = fopen("c:\NeHe.tga", "rb");						// Open The TGA File

		if (file == NULL ||										// Does File Even Exist?
			fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
			memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||	// Does The Header Match What We Want?
			fread(header, 1, sizeof(header), file) != sizeof(header))				// If So Read Next 6 Header Bytes
		{
			if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
				return false;									// Return False
			else
			{
				fclose(file);									// If Anything Failed, Close The File
				return false;									// Return False
			}
		}

		texture->width = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
		texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)


		if (texture->width <= 0 ||								// Is The Width Less Than Or Equal To Zero
			texture->height <= 0 ||								// Is The Height Less Than Or Equal To Zero
			(header[4] != 24 && header[4] != 32))					// Is The TGA 24 or 32 Bit?
		{
			fclose(file);										// If Anything Failed, Close The File
			return false;										// Return False
		}

		texture->bpp = header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
		bytesPerPixel = texture->bpp / 8;						// Divide By 8 To Get The Bytes Per Pixel
		imageSize = texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

		texture->imageData = (GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

		if (texture->imageData == NULL ||							// Does The Storage Memory Exist?
			fread(texture->imageData, 1, imageSize, file) != imageSize)	// Does The Image Size Match The Memory Reserved?
		{
			if (texture->imageData != NULL)						// Was Image Data Loaded
				free(texture->imageData);						// If So, Release The Image Data

			fclose(file);										// Close The File
			return false;										// Return False
		}

		for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)		// Loop Through The Image Data
		{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
			temp = texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
			texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
			texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
		}


		fclose(file);											// Close The File

																// Build A Texture From The Data

#ifndef NOGL
		{

			texture->texID = 0;
			glGenTextures(1, &texture->texID);
			glBindTexture(GL_TEXTURE_2D, texture->texID);			// Bind Our Texture
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// 
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// 

			if (texture->bpp == 24)									// Was The TGA 24 Bits
			{
				type = GL_RGB;										// If So Set The 'type' To GL_RGB
			}

			glTexImage2D(GL_TEXTURE_2D, 0, type, texture->width, texture->height, 0, type, GL_UNSIGNED_BYTE, texture->imageData);

		}
		free(texture->imageData);
#endif
		printf("\nTGA:%s[%dx%d]", filename, texture->width, texture->height);
		return true;											// Texture Building Went Ok, Return True
	}

#define NN 1

	/*	std::future <CModel*> loadAlxModelAsync(char* alxfilename, char* tgafilename, short modelId, float fscale)
	{
	auto call = std::async(std::launch::async,&CResourceManager::loadAlxModel, this ,alxfilename, tgafilename, modelId, fscale);
	return call;
	}
	*/
	/*Assimp LoadModed
	int loadModelUsingAssimp(char* pFile )
	{

	// const std::string& pFile = NULL;
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile( pFile,
	aiProcess_CalcTangentSpace       |
	aiProcess_Triangulate            |
	aiProcess_JoinIdenticalVertices  |
	aiProcess_SortByPType);

	// If the import failed, report it
	if( !scene)
	{
	printf("%s", importer.GetErrorString());
	return 0;
	}
	// Now we can access the file's contents.



	// We're done. Everything will be cleaned up by the importer destructor
	return 0;
	}

	//https://sites.google.com/site/gsucomputergraphics/educational/load_3d_model
	void glDraw (const aiScene *sc, const aiNode* nd)
	{

	// draw all meshes assigned to this node
	for (unsigned int n=0; n < nd->mNumMeshes; ++n){

	// Bind VAO, which contains the VBOs for indices, positions, normals, and texture coordinates
	// of the current mesh for the current node.
	// Each node in aiScene has an index (nd->mMeshs[n]) into the aiMesh array (see Figure 2).
	// In previous steps, each aiMesh in the aiMesh array has been transferred to a Vertex Array Object (VAO).
	// The indices of these VBOs are stored in an array myMeshes[].
	// The aiMesh array in an aiScene object and the myMeshes[] array is perfectly aligned.
	// That is, the first mesh in the aiMesh list corresponds to the first mesh on the myMeshes[] array, and so on.
	// Therefore, myMeshes[0].vao is the index of the VAO for the first aiMesh in the aiScene object, and so on.
	glBindVertexArray(myMeshes[nd->mMeshes[n]].vao);

	// Use glDrawElements() to draw the 3D object because we have an index buffer in the VAO.
	glDrawElements(GL_TRIANGLES,myMeshes[nd->mMeshes[n]].numFaces*3,GL_UNSIGNED_INT,0);

	}

	// Draw all THE children
	for (unsigned int n=0; n < nd->mNumChildren; ++n){
	recursive_render(sc, nd->mChildren[n]);
	}
	}
	*/

	CModel* loadAlxModel(char* alxfilename, char* tgafilename, short modelId, float fscale)
	{

		static int numloads = 1;

		char _alxfname[128];
		char fname[256];
        char fnamed[256];
        
		strcpy(_alxfname, alxfilename);

		if (resourcepath[0]>0) {
			strcpy(fname, resourcepath);
			strcat(fname, "/");
            strcpy(fnamed, resourcepath);
			strcat(fnamed, "/Data/");
		}
		else fname[0] = 0;

		strcat(fname, alxfilename);
		strcat(fnamed, alxfilename);

		models[modelId] = new CModel();

		FILE* file = fopen(fnamed, "r");//try data folder first
        if (!file) file = fopen(fname, "r"); //fallbcak to root
        
		char line[1280];

		if (file)
		{

			int vx_i = 0;
			int vn_i = 0;
			int color_i = 0;
			int ind_i = 0;
			int uv_i = 0;

			while (!feof(file)) {
				line[0] = 0;
				//  fgets(line, 1280, file);
				fscanf(file, "%s", line);
				//std::cout << line << "\n";

				if (strcmp(line, "Good Luck") == 0) {
					break;
				}
				
				if (strstr(line, "Mode=") != NULL) {
                    if (line[5] == 'T')models[modelId]->DRAWMODE = GL_TRIANGLES;
#ifndef ES_ONLY
                    if (line[5] == 'P')models[modelId]->DRAWMODE = GL_POLYGON;
					if (line[5] == 'Q')models[modelId]->DRAWMODE = GL_QUADS;
#endif
				}

				if (strcmp(line, "obj[") == 0) {
					fscanf(file, "%s", line);
					strcpy(models[modelId]->name, line);
				}

				if (strcmp(line, "t[") == 0) {
					int zoom = 1;
					fscanf(file, "%s", line);
					models[modelId]->uv_array[uv_i] = atof(line)*zoom;
					fscanf(file, "%s", line);
					models[modelId]->uv_array[uv_i + 1] = atof(line)*zoom;
					uv_i += 2;
				}


				if (strcmp(line, "n[") == 0) {
					int zoom = 1;
					fscanf(file, "%s", line);
					models[modelId]->normals_array[vn_i] = atof(line)*zoom;
					fscanf(file, "%s", line);
					models[modelId]->normals_array[vn_i + 1] = atof(line)*zoom;
					fscanf(file, "%s", line);
					models[modelId]->normals_array[vn_i + 2] = atof(line)*zoom;
					vn_i += 3;
				}


				if (strcmp(line, "v[") == 0) {
					int zoom = 1;
					fscanf(file, "%s", line);
					models[modelId]->vertex_array[vx_i] = atof(line)*zoom;
					fscanf(file, "%s", line);
					models[modelId]->vertex_array[vx_i + 1] = atof(line)*zoom;
					fscanf(file, "%s", line);
					models[modelId]->vertex_array[vx_i + 2] = atof(line)*zoom;
					vx_i += 3;
				}

				if (strcmp(line, "c[") == 0) {
					fscanf(file, "%s", line);
					models[modelId]->color_array[color_i] = atof(line);
					fscanf(file, "%s", line);
					models[modelId]->color_array[color_i + 1] = atof(line);
					fscanf(file, "%s", line);
					models[modelId]->color_array[color_i + 2] = atof(line);
					models[modelId]->color_array[color_i + 3] = 255;
					color_i += 4;
				}

				if (strcmp(line, "ni[") == 0) {
					fscanf(file, "%s", line);
					models[modelId]->n_indices = atoi(line);
					fscanf(file, "%s", line);
					models[modelId]->INDICES_DRAWMODE = atoi(line);
				}

				if (strcmp(line, "i[") == 0) {
					fscanf(file, "%s", line);
					int ind_i_n = atoi(line);
					for (int j = 0; j<ind_i_n; j++) {
						fscanf(file, "%s", line);
						models[modelId]->indices_array[ind_i + j] = atof(line);
					}
					ind_i += ind_i_n;
				}
			}

			if (vx_i>0) {
				models[modelId]->n_vertices = (vx_i - 1) / 3 + 1;
				models[modelId]->n_normals = (vn_i - 1) / 3 + 1;
				models[modelId]->n_uv = (uv_i - 1) / 2 + 1;
				models[modelId]->n_colors = (color_i - 1) / 4 + 1;
				models[modelId]->n_indices = ind_i;
			}

			fclose(file);
			int l = int(strlen(fname));
			if (l>3) {
				fname[l - 3] = 't';
				fname[l - 2] = 'g';
				fname[l - 1] = 'a';
			}

			l = int(strlen(_alxfname));
			if (l>3) {
				_alxfname[l - 3] = 't';
				_alxfname[l - 2] = 'g';
				_alxfname[l - 1] = 'a';
			}

			if (tgafilename) sprintf(fname, "%s/%s", resourcepath, tgafilename);
			if (fname[0]) {
				FILE * ftex = fopen(fname, "rb");
				if (ftex) {
					fclose(ftex);
					LoadTGA(models[modelId]->texture, tgafilename ? tgafilename : _alxfname);
					//Assume if TGA is Avail tex stats from 1
					if (models[modelId]->texture->texID == 0) models[modelId]->texture->texID = numloads;
					models[modelId]->textureWidth = models[modelId]->texture->width;
					numloads++;
				}
				else {
					printf("\nFAILED LOAD OF :%s", fname);
				}

				_alxfname[l - 3] = 'a';
				_alxfname[l - 2] = 'l';
				_alxfname[l - 1] = 'x';
			}

			models[modelId]->scale(fscale);
		}
		else {
			printf("\n%s", fname);
		}
		memset(_alxfname, 0, 64);
		models[modelId]->index = modelId;
		models[modelId]->onLoad();

		return models[modelId];
	}

	void freeModelsAndObjects()
	{
		int i;

		for (i = 0; i<numModels; i++) {
			if (models[i]) delete models[i];
		}

	}


	static void freeGLObject(GLOBJECT *object)
	{
		if (object == NULL)
			return;
		free(object->normalArray);
		free(object->colorArray);
		free(object->vertexArray);
		free(object);
	}


	static GLOBJECT * newGLObject(long vertices, int vertexComponents,
		int useNormalArray)
	{
		GLOBJECT *result;
		result = (GLOBJECT *)malloc(sizeof(GLOBJECT));
		if (result == NULL)
			return NULL;
		result->count = int(vertices);
		result->vertexComponents = vertexComponents;
		result->vertexArray = (GLfloat *)malloc(vertices * vertexComponents *
			sizeof(GLfloat));
		result->colorArray = (GLubyte *)malloc(vertices * 4 * sizeof(GLubyte));
		if (useNormalArray)
		{
			result->normalArray = (GLfloat *)malloc(vertices * 3 *
				sizeof(GLfloat));
		}
		else
			result->normalArray = NULL;
		if (result->vertexArray == NULL ||
			result->colorArray == NULL ||
			(useNormalArray && result->normalArray == NULL))
		{
			freeGLObject(result);
			return NULL;
		}
		return result;
	}

	void makeObject(int objectId, char* objectname, int modelId, int texId)
	{
		alObject[objectId] = new CAlObject;
		//sprintf([alObject[objectId] getName], objectname);
		//alObject[objectId]->TexId = texId;
		//alObject[objectId]->model = models[modelId];
	}

	void loadModel(int modelId, char* objname)
	{
		loadColladaModel(objname, modelId);
		//sprintf(models[modelId]->name, objname);
	}

};


#include "../Classlets/com/acnodelabs/funkit/all.h"

static unsigned long sRandomSeed = 0;

/*
static void seedRandom(unsigned long seed)
{
sRandomSeed = seed;
}


static unsigned long randomUInt()
{
sRandomSeed = sRandomSeed * 0x343fd + 0x269ec3;
return sRandomSeed >> 16;
}
*/


float randm()
{
	//	float r =  ((float)(randomUInt())) / 65535.0f;
	float r = rand() / float(RAND_MAX);
	return r;
}

float rndm(float min, float max) {
	float diff = (max - min);
	float r = randm() * diff;
	return (min + r);
}

enum OrthoTypes {
	ORIGIN_IN_MIDDLE_OF_SCREEN = 0,
	ORIGIN_IN_TOP_LEFT_OF_SCREEN
};

void AlInit(int TYPE, std::string title = "") {
	
	if (TYPE == STANDARD || TYPE == STANDARD_2D) {
#ifndef NOGL
#ifndef METRO
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
															//glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.5);
#endif
#endif
	}

	//To add these two lines refactoring would be needed: PENDED
	//if (TYPE == STANDARD_2D) game.AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
	//SetTitle(title);

};



#ifdef MACOSX
#define GLfixed GLfloat
#define glFrustumx glFrustum
#endif

float Random(float rGen) { return randm(); }

static void aluPerspective(GLfloat fovy, GLfloat aspect,
	GLfloat zNear, GLfloat zFar)
{
	GLfloat xmin, xmax, ymin, ymax;

	ymax = zNear * (GLfloat)tan(fovy * 3.14157f / 360);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;
#ifndef NOGL
#ifdef WIN32
#ifndef METRO
	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
#endif
#else    
	glFrustumx
	((GLfixed)(xmin * 65536), (GLfixed)(xmax * 65536),
		(GLfixed)(ymin * 65536), (GLfixed)(ymax * 65536),
		(GLfixed)(zNear * 65536), (GLfixed)(zFar * 65536));
#endif
#endif
}

#include "AlgeApp.hpp"

class GameText : public GameObject, public FontMap16x16 {
	ResourceInf rGameText;
public:

	void Setup(AlgeApp* app, char* text, int modelId, float scale = 1.0) {
		this->modelId = modelId;
		custom_type = this->modelId;
		usetexof(app->rm.loadAlxModel((char*) "font.alx", AUTO, modelId, scale));
		print(text);
	}


};

#endif



