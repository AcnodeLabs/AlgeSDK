#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>

using namespace std;

#include "importgl.h"
#include "app.h"

#ifdef ANDROID
#define CBASE "../../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"
#else
#define CBASE "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"
#endif
#include CBASE

#ifndef NO_IMGUI
// XGui stuff
#include "../../../imgui/imgui.h"
#include "../../../imgui/backends/imgui_impl_opengl2.h"
#include "../../SDKSRC/Base/fmod/framework.hpp"

static bool show_demo_window = true;
static bool show_another_window = false;
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void ImGui_ImplAlgeSDK_Main(int x, int y, int framebufferScale) {
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.DisplaySize.x = x;
    io.DisplaySize.y = y;
#ifdef IOS
    io.DisplayFramebufferScale = ImVec2(framebufferScale, framebufferScale); //
#endif
	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	ImGui::StyleColorsClassic();
	//ImGui::SetWindowFontScale(2);
}

void ImGui_ImplAlgeSDK_BeforeRender()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	//ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGui_ImplAlgeSDK_AfterRender(char* msg)
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

void GuiStarts() {
    ImGui_ImplAlgeSDK_BeforeRender();
}

void GuiEnds() {
    static char msg[1024] = {0,0};
#ifndef IOS
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData(),msg);
#endif
    ImGui_ImplAlgeSDK_AfterRender(msg);
}



void ImGui_ImplAlgeSDK_Shutdown() {
	// Cleanup
	ImGui_ImplOpenGL2_Shutdown();
//	ImGui_ImplWin32_Shutdown();
}

////////////////////////
#endif //NO_IMGUI



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

void appPushI(int command, int p1, int p2) {
    game.input.pushI(command,p1,p2);
#ifndef NO_IMGUI
    ImGuiIO& io = ImGui::GetIO();
    if (command == CMD_TOUCH_START) {
        io.MouseDown[0] = true;
        io.MousePos = ImVec2((float)p1, (float)p2);
    }
    if (command == CMD_TOUCHMOVE) {
        io.MousePos = ImVec2((float)p1, (float)p2);
    }
    
    if (command == CMD_TOUCH_END) {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2((float)p1, (float)p2);
        io.MouseDown[0] = false;
    }
#endif
}
void appInit(char *sz) { 
#ifndef NO_FMOD
    FMOD_Init();
#endif
	strcpy(ResPath, sz);
    game.aCamera.custom_type = 0xCA;
    game.aCamera.windowWidth = game.getBackgroundSize().x;
    game.aCamera.windowHeight = game.getBackgroundSize().y;
#ifndef NO_IMGUI
    int frameBufferScale = 2; //ios
    ImGui_ImplAlgeSDK_Main(game.getBackgroundSize().x,game.getBackgroundSize().y,1);
#endif
    game.rm.Init(sz);
    game.Init(sz);
    

    
}

void appSize(int w, int h) {
    int frameBufferScale = 2; //ios
    if (game.landscape) {
        game.ScreenSize(h, w, frameBufferScale);
    } else {
        game.ScreenSize(w, h, frameBufferScale);
    }
}
void appDeinit(){
#ifndef NO_IMGUI
    ImGui_ImplAlgeSDK_Shutdown();
#endif
#ifndef NO_FMOD
    FMOD_Deinit();
#endif
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
	
    switch (a->command) {
       case CMD_SNDSET0:
       case CMD_SNDSET1:
       case CMD_SNDSET2:
       case CMD_SNDSET3:
            {
            // sndSet((char*)c->param1, c->command-CMD_SNDSET, c->i2);
                string fullpath = string(game.rm.resourcepath) + string("/")+ string((char*)a->param1);
                FMOD_Set((a->command - CMD_SNDSET), (char*)fullpath.c_str());
            }
       break;
      
         case CMD_SNDPLAY0:
         case CMD_SNDPLAY1:
         case CMD_SNDPLAY2:
         case CMD_SNDPLAY3:
                {
                   // sndPlay(a->command-CMD_SNDPLAY);
                    FMOD_Play(a->command - CMD_SNDPLAY);
                    
                }
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


char msg[256];
void appRender(float tick, int width, int height, int accelX, int accelY, int accelZ)
{
#ifndef NO_IMGUI
   // ImGui_ImplAlgeSDK_BeforeRender();
#endif
	prepareFrame(width,height);
	if (accelX==0 && accelY==0 && accelZ==0) accelY = -9.8*100;
    
	game.Render(tick, accelX , accelY , accelZ );
#ifndef NO_IMGUI
  //  ImGui_ImplAlgeSDK_AfterRender((char*)msg);
#endif
  //  game.input.pushP(CMD_YOUTUBE_SHOW,msg,msg);
    
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


