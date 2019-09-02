#ifndef EXTERNIT_CPP_INCLUDED
#define EXTERNIT_CPP_INCLUDED

#ifdef WIN32
#define APPREF game
#else
#define APPREF app
#define EXTERNIT
#endif

extern class App APPREF;

EXTERNIT void alAlphaTest(int set_unset, float fA) {

  if (set_unset) {
    glAlphaFunc(GL_GREATER, fA);
    glEnable(GL_ALPHA_TEST);
  // glDisable(GL_DEPTH_TEST);
  //  glEnable(GL_BLEND);
  //  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  //  glBlendEquation(GL_FUNC_ADD);
  } else {
    glDisable(GL_ALPHA_TEST);
  }
}


EXTERNIT void alScalef(float x =1.0, float y=1.0, float z=1.0) {
  glScalef(x,y,z);
}

EXTERNIT void alBillBoardBegin() {
//  billboardBegin();

}

EXTERNIT void alLoadIdentity() {
  glLoadIdentity();
}

EXTERNIT void alPushMatrix() {
  glPushMatrix();
}

EXTERNIT void alPopMatrix() {
  glPopMatrix();
}

EXTERNIT void alaluLookAt(float x1, float y1, float z1, float x2, float y2, float z2, float x, float y, float z) {
  aluLookAt(x1,y1,z1,x2,y2,z2,x,y,z);
}

EXTERNIT void alBillBoardEnd() {
 // billboardEnd();
}


EXTERNIT void PushP(int cmd, char* param1, char* param2) {
	APPREF.output.pushP(cmd, (void*)param1, (void*)param2);
}

EXTERNIT void PushI(int cmd, int x, int y) {
	APPREF.output.pushI(cmd,x,y);
}

EXTERNIT void alTriangle(float size) {
	APPREF.AL10.Triangle(float(size));

}

EXTERNIT void alLoadModel(char* alx, char* tga, int id, float size) {
	APPREF.rm.loadAlxModel(alx, tga, id,size );
}

EXTERNIT void alDrawModelTranslateRotate(int id, float posx , float posy, float posz,
					   float angle,float x, float y,float z,
 int rotatefirst , int billboard )
{
  glPushMatrix();
  if (rotatefirst!=0)  {
    glRotatef(angle, x,y,z);
    glTranslatef(posx,posy,posz);
    } else {
    glTranslatef(posx,posy,posz);
    glRotatef(angle, x,y,z);
  }

  if (APPREF.rm.models[id]->loaded) {
    if (billboard==1) alBillboardBegin();
	APPREF.rm.models[id]->glDraw();
    if (billboard==1) alBillboardEnd();
  }
  glPopMatrix();
}

EXTERNIT void alScaleModel(int id, float sx, float sy, float sz) {
	APPREF.rm.models[id]->SetScale(sx,sy,sz);
}
/*
EXTERNIT void alDrawModel(int id) {
  APPGAME.rm.models[id]->glDraw();
}
*/
EXTERNIT float alModelBounds(int id) {
 return APPREF.rm.models[id]->boundz();
}


EXTERNIT void alTranslateRotate( float posx , float posy, float posz,
					             float angle,float x, float y,float z) {
     glTranslatef(posx,posy,posz);
     glRotatef(angle,x,y,z);
}

EXTERNIT void alLine(float x1, float y1, float x2, float y2) {
	APPREF.AL10.Line(x1,y1,x2,y2);
  }

EXTERNIT void alCircle(float r, int segments) {
	APPREF.AL10.Circle(r,short(segments));
  }

EXTERNIT void alRect(float w, float h) {
	APPREF.AL10.Rect(w,h);
  }
#endif
