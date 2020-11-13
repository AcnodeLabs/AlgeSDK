#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>

using namespace std;

#include "importgl.h"
#include "app.h"

#ifdef ANDROID
#undef NO_BOX2D
#define CBASE "../../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"
#else
#define CBASE "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"
#endif
#include CBASE

// XGui stuff
#include "../../../imgui/imgui.h"
#include "../../../imgui/backends/imgui_impl_opengl2.h"

static bool show_demo_window = true;
static bool show_another_window = false;
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void ImGui_ImplAlgeSDK_Main() {
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();
	//ImGui::SetWindowFontScale(2);
}

void ImGui_ImplAlgeSDK_AfterRender()
{
	// Rendering
	ImGui::Render();
	ImGuiIO& io = ImGui::GetIO();

	//	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
	//	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	//	glClear(GL_COLOR_BUFFER_BIT);
	//glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void ImGui_ImplAlgeSDK_BeforeRender()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
//	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGui_ImplAlgeSDK_Shutdown() {
	// Cleanup
	ImGui_ImplOpenGL2_Shutdown();
//	ImGui_ImplWin32_Shutdown();
}

////////////////////////




#include "CANDIDATE.h"
//#include CANDIDATE

#define RUN_LENGTH  (20 * CAMTRACK_LEN)
#undef PI
#define PI 3.1415926535897932f
#define RANDOM_UINT_MAX 65535

App game;

/* Capped conversion from float to fixed.
static long floatToFixed(float value)
{
    if (value < -32768) value = -32768;
    if (value > 32767) value = 32767;
    return (long)(value * 65536);
}

#define FIXED(value) floatToFixed(value)
*/

char ResPath[256];
XHttpSocket sck;
XHttpSocket msck;

void appPushI(int command, int p1, int p2) { game.input.pushI(command,p1,p2);}
void appInit(char *sz) { 

	ImGui_ImplAlgeSDK_Main();

	strcpy(ResPath, sz);
    game.aCamera.custom_type = 0xCA;
    game.aCamera.windowWidth = game.getBackgroundSize().x;
    game.aCamera.windowHeight = game.getBackgroundSize().y;




    game.rm.Init(sz);
    game.Init(sz);
}

void appSize(int w, int h) {
    if (game.landscape) {
        game.resolutionReported.y = w;
        game.resolutionReported.x = h;
    } else {
        game.resolutionReported.x = w;
        game.resolutionReported.y = h;
    }
}
void appDeinit(){
    ImGui_ImplAlgeSDK_Shutdown();
}

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
    ImGui_ImplAlgeSDK_BeforeRender();
	game.Render(tick, accelX , accelY , accelZ );
    ImGui_ImplAlgeSDK_AfterRender();
	return;
}

void appRenderJ(int tickE6, int width, int height, int accelX, int accelY, int accelZ)
{
    float tick = (tickE6 / 1000000.0f);
	appRender( tick, width, height, accelX, accelY, accelZ);
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


