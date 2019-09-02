#ifndef EXTERNIT_CPP_INCLUDED
#define EXTERNIT_CPP_INCLUDED

#ifdef WIN32
#define APPREF game
extern "C++" void alAlphaTest(int set_unset, float fA) {
	if (set_unset) {
		glAlphaFunc(GL_GREATER, fA);
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_ALPHA_TEST);
	}
}

extern "C++" void alLoadIdentity() {
	glLoadIdentity();
}

extern "C++" void alPushMatrix() {
	glPushMatrix();
}

extern "C++" void alPopMatrix() {
	glPopMatrix();
}

extern "C++" void alLoadModel(char* alx, char* tga, int id, float size) {
	string fname = string(alx);
	if (fname.find(".alx") != string::npos)
		game.rm.loadAlxModel((char*)alx, (char*)tga, id, size);
	else //generic 
		game.rm.loadGenericAsset(fname, id);
}

int model_counter = -1;

int alLoadModel(ResourceInf* resInf) {
	alLoadModel((char*)resInf->alx.c_str(), (char*)resInf->tex.c_str(), ++model_counter, resInf->scale);
	return model_counter;
}

int alReserveModelId() {
	++model_counter;
	return model_counter;
}

extern "C++" void alDrawModelTranslateRotate(int id, float posx, float posy, float posz,
	float angle, float x, float y, float z,
	int rotatefirst,
	int billboard)
{
	glPushMatrix();
	if (rotatefirst != 0) {
		glRotatef(angle, x, y, z);
		glTranslatef(posx, posy, posz);
	}
	else {
		glTranslatef(posx, posy, posz);
		glRotatef(angle, x, y, z);
	}

	if (game.rm.models[id]->loaded) {
		if (billboard == 1) alBillboardBegin();
		game.rm.models[id]->glDraw();
		if (billboard == 1) alBillboardEnd();
	}
	glPopMatrix();
}

extern "C++" void alScaleModel(int id, float sx, float sy, float sz) {
	game.rm.models[id]->SetScale(sx, sy, sz);
}

extern "C++" void alDrawModel(int id, bool wireframe) {
	game.rm.models[id]->glDraw(wireframe);
}

extern "C++" void alTranslateRotate(float posx, float posy, float posz,
	float angle, float x, float y, float z) {
	glTranslatef(posx, posy, posz);
	glRotatef(angle, x, y, z);
}

#else

//MACOS
#define game app
extern "C++" void alAlphaTest(int set_unset, float fA) {
    if (set_unset) {
        glAlphaFunc(GL_GREATER, fA);
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_ALPHA_TEST);
    }
}

extern "C++" void alLoadIdentity() {
    glLoadIdentity();
}

extern "C++" void alPushMatrix() {
    glPushMatrix();
}

extern "C++" void alPopMatrix() {
    glPopMatrix();
}

extern "C++" void alLoadModel(char* alx, char* tga, int id, float size) {
    game.rm.loadAlxModel((char*)alx, (char*)tga, id,size );
}
int alLoadModel(ResourceInf* resInf) {
    static int counter = -1;
    alLoadModel((char*)resInf->alx.c_str(), (char*)resInf->tex.c_str(), ++counter, resInf->scale);
    return counter;
}

extern "C++" void alDrawModelTranslateRotate(int id, float posx , float posy, float posz,
                                             float angle,float x, float y,float z,
                                             int rotatefirst ,
                                             int billboard )
{
    glPushMatrix();
    if (rotatefirst!=0)  {
        glRotatef(angle, x,y,z);
        glTranslatef(posx,posy,posz);
    } else {
        glTranslatef(posx,posy,posz);
        glRotatef(angle, x,y,z);
    }
    
    if (game.rm.models[id]->loaded) {
        if (billboard==1) alBillboardBegin();
        game.rm.models[id]->glDraw();
        if (billboard==1) alBillboardEnd();
    }
    glPopMatrix();
}

extern "C++" void alScaleModel(int id, float sx, float sy, float sz) {
    game.rm.models[id]->SetScale(sx,sy,sz);
}

extern "C++" void alDrawModel(int id, bool wireframe) {
    game.rm.models[id]->glDraw(wireframe);
}

extern "C++" void alTranslateRotate( float posx , float posy, float posz,
                                    float angle,float x, float y,float z) {
    glTranslatef(posx,posy,posz);
    glRotatef(angle,x,y,z);
}

#endif
#endif

