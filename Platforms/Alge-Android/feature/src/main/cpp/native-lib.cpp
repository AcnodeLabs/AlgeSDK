#include <GLES/gl.h>

#include <jni.h>
#include <string>

#include "../../../../../../SDKSRC/Base/CBaseV1_2.h"

extern "C" JNIEXPORT jstring

JNICALL
Java_com_acnodelabs_apps_untitled_feature_MainActivity_stringFromJNI( JNIEnv *env, jobject /* this */) {

    //float Random(float rGen) { return randm(); }
    int i = int(Random(1.0) * 10);
    std::string hello = "XAL FUNCTION CALL ";
    for (int j=0; j< i ; j++) hello += " OK";

    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1.0,1.0,1.0,1.0);
    return env->NewStringUTF(hello.c_str());
}

/*
#define RUN_LENGTH  (20 * CAMTRACK_LEN)
#undef PI
#define PI 3.1415926535897932f
#define RANDOM_UINT_MAX 65535

// Capped conversion from float to fixed.
static long floatToFixed(float value)
{
    if (value < -32768) value = -32768;
    if (value > 32767) value = 32767;
    return (long)(value * 65536);
}

#define FIXED(value) floatToFixed(value)

char respath[256];

void appPushI(int command, int p1, int p2) {
//    game.input.pushI(command,p1,p2);
}
void appInit(char *sz) {
    strcpy(respath, sz);
  //  game.Init(sz);
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
  //  PEG::CMD* a = game.output.pull();
  //  lastP1 = a->param1;
  //  lastP2 = a->param2;

    int ae = 1;//glGetError();
    if (ae) {
          if (!notified) {

            sprintf(errsz, "glError=%d", ae);
            //game.output.pushP(CMD_MSG, $ errsz, 0);
            notified = 1;
        }
    }

 //   if (a->command>=CMD_TEXSET0 && a->command<=CMD_TEXSET3) {

        //	game.rm.LoadTGA((TextureImage* )lastP2 , (char*)lastP1);

 //   }

 //   lastI1 = a->i1;
 //   lastI2 = a->i2;

    return 0;//a->command;
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

static void prepareFrame(int width, int height) {

//    glViewport(0, 0, width, height);

//    glClearColorx((GLfixed)(0.0f * 65536),
//                  (GLfixed)(0.0f * 65536),
//                  (GLfixed)(0.0f * 65536), 0x10000);
//    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    aluPerspective(45, (float)width / (float)height, 0.05f, 150);

//    glMatrixMode(GL_MODELVIEW);

//    glLoadIdentity();

}

void appRender(float tick, int width, int height, int accelX, int accelY, int accelZ)
{
    prepareFrame(width,height);
    if (accelX==0 && accelY==0 && accelZ==0) accelY = -9.8*100;
  //  game.Render(tick, accelX , accelY , accelZ );
    return;
}
*/