#include <GLES/gl.h>

#include <jni.h>
#include <string>

//http://blog.sephiroth.it/2010/10/24/reading-resource-files-from-native-code/

#include "../../../../../../SDKSRC/Base/CBaseV1_2.h"

#include "../../../../../../Demos/PoppingTime/App.hpp"

#define RUN_LENGTH  (20 * CAMTRACK_LEN)
#undef PI
#define PI 3.1415926535897932f
#define RANDOM_UINT_MAX 65535

App game;

// Capped conversion from float to fixed.
static long floatToFixed(float value)
{
    if (value < -32768) value = -32768;
    if (value > 32767) value = 32767;
    return (long)(value * 65536);
}

#define FIXED(value) floatToFixed(value)

char respath[256];

void appPushI(int command, int p1, int p2) { game.input.pushI(command,p1,p2);}
void appInit(char *sz) {
    strcpy(respath, sz);
    strcpy(game.rm.resourcepath, respath);
    game.Init(sz);

}
void appDeinit(){}

void* lastP1 = 0;
void* lastP2 = 0;
int lastI1 = 0;
int lastI2 = 0;

char filename[256];


short notified = 0;
char errsz[64];

int appPull() {
    PEG::CMD* a = game.output.pull();
    lastP1 = a->param1;
    lastP2 = a->param2;

    int ae = glGetError();
    if (ae) {
        if (!notified) {

            sprintf(errsz, "glError=%d", ae);
            //game.output.pushP(CMD_MSG, $ errsz, 0);
            notified = 1;
        }
    }

    if (a->command>=CMD_TEXSET0 && a->command<=CMD_TEXSET3) {

        //	game.rm.LoadTGA((TextureImage* )lastP2 , (char*)lastP1);

    }

    lastI1 = a->i1;
    lastI2 = a->i2;

    return a->command;
}

void* appP1() { return (void*)lastP1;}
void* appP2() { return (void*)lastP2;}

char* appSzlastP1() {
    return (char*)lastP1;
}

int appIntlastP1() {
    return lastI1;
}

int appIntlastP2() {
    return lastI2;
}


void appAccelerometerSz(char* accelValues) {

}

static void prepareFrame(int width, int height)
{

    glViewport(0, 0, width, height);

    glClearColorx((GLfixed)(0.0f * 65536),
                  (GLfixed)(0.0f * 65536),
                  (GLfixed)(0.0f * 65536), 0x10000);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aluPerspective(45, (float)width / (float)height, 0.05f, 150);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}


void appRender(float tick, int width, int height, int accelX, int accelY, int accelZ)
{
    prepareFrame(width,height);
    if (accelX==0 && accelY==0 && accelZ==0) accelY = -9.8*100;
    game.Render(tick, accelX , accelY , accelZ );
    return;
}


//////////////////INCLUDE R1 CODE
#include <sys/time.h>
#include <time.h>
#include <android/log.h>
#include <stdint.h>
#include <stdio.h>

int   gAppAlive   = 1;

static int  sWindowWidth  = 320;
static int  sWindowHeight = 480;
static int  sDemoStopped  = 0;
static long sTimeOffset   = 0;
static int  sTimeOffsetInit = 0;
static long sTimeStopped  = 0;

static long
_getTime(void)
{
    struct timeval  now;

    gettimeofday(&now, NULL);
    return (long)(now.tv_sec*1000 + now.tv_usec/1000);
}

/* Call to initialize the graphics state */
char*
Java_com_acnodelabs_alge_DemoRenderer_nativeInit( JNIEnv*  env , jobject thiz, jstring uri)
{
    // importGLInit();
    // convert Java string to UTF-8
    jboolean isCopy;
    const char *utf8 = (env)->GetStringUTFChars(uri, &isCopy);
    appInit((char*)utf8);
    gAppAlive    = 1;
    sDemoStopped = 0;
    sTimeOffsetInit = 0;
    if (isCopy==JNI_TRUE) (env)->ReleaseStringUTFChars(uri, utf8);
    return game.rm.resourcepath;
}

/* Call to initialize the graphics state */
int
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativePull( JNIEnv*  env )
{
    int a = appPull();
    return a;
}

/* Call to initialize the graphics state */
jstring
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativeSzP1( JNIEnv*  env)
{
    return (env)->NewStringUTF((const char *)appSzlastP1());
}

jint
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativeIntP1( JNIEnv*  env)
{
    return appIntlastP1();
}
/* Call to initialize the graphics state */
jint
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativeIntP2( JNIEnv*  env)
{
    return appIntlastP2();
}

/* Call to initialize the graphics state */
void
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativePushI( JNIEnv*  env, jobject  thiz, jint cmd, jint x, jint y)
{
    appPushI(cmd,x,y);
}

void
Java_com_acnodelabs_alge_DemoRenderer_nativeResize( JNIEnv*  env, jobject  thiz, jint w, jint h )
{
    sWindowWidth  = w;
    sWindowHeight = h;
    __android_log_print(ANDROID_LOG_INFO, "AlgeApp", "resize w=%d h=%d", w, h);
}

/* Call to finalize the graphics state */
void
Java_com_acnodelabs_alge_DemoRenderer_nativeDone( JNIEnv*  env )
{
    appDeinit();
    // importGLDeinit();
}

/* This is called to indicate to the render loop that it should
 * stop as soon as possible.
 */
void
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativePause( JNIEnv*  env )
{
    sDemoStopped = !sDemoStopped;
    if (sDemoStopped) {
        /* we paused the animation, so store the current
         * time in sTimeStopped for future nativeRender calls */
        sTimeStopped = _getTime();
    } else {
        /* we resumed the animation, so adjust the time offset
         * to take care of the pause interval. */
        sTimeOffset -= _getTime() - sTimeStopped;
    }
}

/* Call to render the next GL frame */
void
Java_com_acnodelabs_alge_DemoRenderer_nativeRender( JNIEnv*  env, jobject  thiz, jint ax100, jint ay100, jint az100)
{
    long   curTime;

    /* NOTE: if sDemoStopped is TRUE, then we re-render the same frame
     *       on each iteration.
     */
    if (sDemoStopped) {
        curTime = sTimeStopped + sTimeOffset;
    } else {
        curTime = _getTime() + sTimeOffset;
        if (sTimeOffsetInit == 0) {
            sTimeOffsetInit = 1;
            sTimeOffset     = -curTime;
            curTime         = 0;
        }
    }

    //__android_log_print(ANDROID_LOG_INFO, "SanAngeles", "curTime=%ld", curTime);

    float accelX = ax100 / 100.0f;
    float accelY = ay100 / 100.0f;
    float accelZ = az100 / 100.0f;

    //sscanf(accelSz3, "%.2f,%.2f,%.2f", &accelX, &accelY, accelZ);
    //static char accelSz3[64];
    //sprintf(accelSz3, "%.2f,%.2f,%.2f", ax, ay, az);
    //appAccelerometerSz(accelSz3);
    appRender(curTime, sWindowWidth, sWindowHeight, ax100,ay100,az100);

}

///////////////////////////////

JNIEXPORT jstring JNICALL JavaString(JNIEnv *env, string str) {
    return (env)->NewStringUTF(str.c_str());
}
extern "C" JNIEXPORT jstring
JNICALL
Java_com_acnodelabs_apps_untitled_feature_MainActivity_stringFromJNI( JNIEnv *env, jobject thiz, jstring hello) {
    return JavaString(env, string(Java_com_acnodelabs_alge_DemoRenderer_nativeInit(env,thiz,hello)));
}

//defis imported from alge-gnat-mac
//TODO This code is common in Platforms iOS/device-app.cpp and OSX/alge-mac.cpp
// This part ahhead can be included from a single file placed in SDKSRC/Ada folder

extern "C++" void alAlphaTest(int set_unset, float fA) {

    if (set_unset) {
        glAlphaFunc(GL_GREATER, fA);
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_DEPTH_TEST);
        //   glDisable(GL_DEPTH_TEST);
        //  glEnable(GL_BLEND);
        //  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        //  glBlendEquation(GL_FUNC_ADD);
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
    game.rm.loadAlxModel(alx, tga, id,size );
}

extern "C++" int alLoadModel(ResourceInf* resInf) {
    static int counter = 0;
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

extern "C++" void alDrawModel(int id) {
    game.rm.models[id]->glDraw();
}
extern "C++" void alDrawModel(int id, bool wireframe) {
    game.rm.models[id]->glDraw(wireframe);
}
extern "C++" void alTranslateRotate( float posx , float posy, float posz,
                                     float angle,float x, float y,float z) {
    glTranslatef(posx,posy,posz);
    glRotatef(angle,x,y,z);
}


