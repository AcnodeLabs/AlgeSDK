//
//  alge-mac.cpp
//  Alge-Mac
//
//  Created by Bilal on 6/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
// http://scrumy.com/XAL_AlgeSDK

#define MACOSX
#define XCODE_BUILD
//#define NO_BOX2D
#define NO_NATS
#define glOrthof glOrtho
#include "../../SDKSRC/Base/CBaseV1_2.h"

#include "xgui.hpp"

#include "CANDIDATE.h"
#include "../../SDKSRC/Base/fmod/framework.hpp"

#include <GLUT/glut.h>
#include <stdio.h>


XHttpSocket msck;

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

int kWindowWidth =	(1920);
int kWindowHeight = (1080);
//#include CANDIDATE

#define TIMERMSECS 33

int startTime;
int prevTime;

struct dtx_font *font;

void alPrintText(string text, float scale) {
 glPushMatrix();
 glScalef(scale, scale, scale);
 if (font!=nullptr) dtx_string(text.c_str());
 glPopMatrix();
}

App app;

static int elapsedTime;

#include "Timer.h"
#include "MyOpenALSupport.h"

Timer time1;
float deltaT;
float lastTime;
float aX, aY, aZ;
/*
ALsizei nAL;
#define NUM_BUFFERS_SOURCES 16
ALuint alSources[NUM_BUFFERS_SOURCES];
ALuint alBuffers[NUM_BUFFERS_SOURCES];
float alPosition[3];

void initAL(char* respath) {
    nAL = NUM_BUFFERS_SOURCES;
    alGetError();
    
    ALCcontext		*newContext = NULL;
	ALCdevice		*newDevice = NULL;
    
	newDevice = alcOpenDevice(NULL);
	if (newDevice != NULL)
	{
		newContext = alcCreateContext(newDevice, 0);
		if (newContext != NULL)
		{
			alcMakeContextCurrent(newContext);
        }
    }
    alListenerfv(AL_POSITION, alPosition);
    alGenBuffers(nAL, alBuffers);
    alGenSources(nAL, alSources);
}

void deInitAL() {
 ALCcontext	*context = NULL;
 ALCdevice	*device = NULL;
 ALuint		returnedNames[NUM_BUFFERS_SOURCES];

 alDeleteSources(NUM_BUFFERS_SOURCES, returnedNames);
 alDeleteBuffers(NUM_BUFFERS_SOURCES, returnedNames);
 context = alcGetCurrentContext();
 device = alcGetContextsDevice(context);
 alcDestroyContext(context);
 alcCloseDevice(device);
}

void sndSetAl(char* filename, int id, int loops) {
 ALenum  format;
 ALvoid* data;
 ALsizei size;
 ALsizei freq;
	
 if (loops>0) alSourcei(alSources[id], AL_LOOPING, AL_TRUE);
 alSourcefv(alSources[id], AL_POSITION, alPosition);
 alSourcef(alSources[id],AL_REFERENCE_DISTANCE, 5.0f);
 
 char filespec[256];
 sprintf(filespec, "%s/%s", app.rm.resourcepath, filename);
 
 CFStringRef f1 = CFStringCreateWithFileSystemRepresentation(kCFAllocatorDefault, filespec);
 CFURLRef fileURL = CFURLCreateWithString(kCFAllocatorDefault, (CFStringRef)f1, NULL);
    data = malloc(1);//MyGetOpenALAudioData(fileURL, &size, &format, &freq);
 CFRelease(fileURL);
 alBufferData(alBuffers[id], format, data, size, freq);
 free(data);
 alSourcei(alSources[id], AL_BUFFER, alBuffers[id]);
}

void sndPlay(int id) {
 alSourcePlay(alSources[id]);
}
*/

extern void ShowToast(char*);

void processOutput() {
 PEG::CMD* c = app.output.pull();
 switch (c->command) {
   case CMD_SNDSET0:
   case CMD_SNDSET1:
   case CMD_SNDSET2:
   case CMD_SNDSET3:
        {
        // sndSet((char*)c->param1, c->command-CMD_SNDSET, c->i2);
            string fullpath = string(app.rm.resourcepath) + string("/")+ string((char*)c->param1);
            FMOD_Set(c->command-CMD_SNDSET, (char*)fullpath.c_str());
        }
   break;
  
     case CMD_SNDPLAY0:
     case CMD_SNDPLAY1:
     case CMD_SNDPLAY2:
     case CMD_SNDPLAY3:
            {
               // sndPlay(c->command-CMD_SNDPLAY);
                FMOD_Play(c->command-CMD_SNDPLAY);
                
            }
   break;
        case CMD_TITLE:
         glutSetWindowTitle( (char*)c->param1);
        break;
            
        case CMD_TOAST:
         ShowToast((char*)c->param1);
        break;
    }
}

static void HandleDisplay( )
{
 float newTime = time1.getElapsedTimeInSec();
 deltaT =  newTime - lastTime;
 if (aX==0 && aY==0 && aZ==0) aY=-9.8*100;
 ImGui_ImplAlgeSDK_BeforeRender();
 app.Render(deltaT,aX,aY,aZ);
 ImGui_ImplAlgeSDK_AfterRender();
 processOutput();
 glutSwapBuffers( );
 lastTime = newTime;
}

static void animate(int value)
{
 glutTimerFunc(TIMERMSECS, animate, 0);
 int currTime = glutGet(GLUT_ELAPSED_TIME);
 int timeSincePrevFrame = currTime - prevTime;
 elapsedTime = currTime - startTime;
 glutPostRedisplay();
 prevTime = currTime;
}

static void HandleIdle() {
 glutPostRedisplay();
}

void appSize(int w, int h) {
    if (app.landscape) {
        app.resolutionReported.x = w;
        app.resolutionReported.y = h;
  
    } else {
        app.resolutionReported.x = w;
        app.resolutionReported.y = h;
    
    }
    
}

static void HandleReshape( const int width, const int height )
{
    if (height>0 && width!=height)										// Prevent A Divide By Zero By
    {
       glViewport(0,0,width,height);						// Reset The Current Viewport
        appSize(width, height);
        kWindowWidth = width;
        kWindowHeight = height;
        printf("[%dx%d]", width, height);
        app.input.pushI(CMD_SCREENSIZE, width , height);
       glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
       glLoadIdentity();									// Reset The Projection Matrix
       gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
       glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
       glLoadIdentity();
    }
}

static void exitIt() {
  app.Deinit();
  FMOD_Deinit();
  exit(0);
}

static void HandleKeyBoard( const unsigned char inKey, const int inPosX, const int inPosY )
{
  if (inKey==27) {exitIt();}
  app.input.pushI(CMD_KEYDOWN, inKey, 0);
}

static void HandleSpecialKey( const int inKey, const int inPosX, const int inPosY )
{
 if (inKey==27) {exitIt();}
 app.input.pushI(CMD_KEYDOWN, inKey, 0);
}

static void HandleMouse( const int inButton, const int inState, const int inPosX, const int inPosY )
{
  if (inButton==0) app.input.pushI(inState==0?CMD_TOUCH_START:CMD_TOUCH_END, inPosX, inPosY);
}

static void HandleMotion( const int inPosX, const int inPosY )
{
  int x = inPosX;
  int y = inPosY;
  if (x!=0 || y!=0)
      app.input.pushI(CMD_TOUCHMOVE, x, y);
}

char ResPath[256];

void FindAppName() {
  FILE* f = fopen("CANDIDATE.h", "r");
  if (f) {
    char line[256];
    for (int i=0; i<100; i++) {
	 fscanf(f, "%s", line);
	 char* pn = strstr(line, ".hpp");
	 strcpy(ResPath, line);
	
    if (pn) {
	 int l = int(strlen(ResPath));
	  ResPath[l-8]=0;
  	  strcat(ResPath, "/Data");
	   break;
    }
	}
	fclose(f);
	}
}
void reset_window_title(int para)
{
 //   glutSetWindowTitle(APP_TITLE);
 //   glutFullScreen();
    
    glutReshapeWindow(kWindowWidth, kWindowHeight);
    glutPositionWindow(0,0);
  //  HandleReshape(kWindowWidth, kWindowHeight);
}

int main( int argc, char** argv )
{
  glutInit( &argc, argv );
  app.landscape = true;
  
 
    
  kWindowWidth = app.getBackgroundSize().x;
  kWindowHeight = app.getBackgroundSize().y;
  
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    
  int theWindowHandle = glutCreateWindow( ResPath );
  glutInitWindowSize( kWindowWidth, kWindowHeight );
  
  
  glutReshapeWindow(kWindowWidth, kWindowHeight);
    
  glutSetWindow( theWindowHandle );
  
 
  
  glutDisplayFunc( HandleDisplay );
  glutReshapeFunc( HandleReshape );
  glutIdleFunc( HandleIdle );
  glutKeyboardFunc( HandleKeyBoard );
  glutSpecialFunc( HandleSpecialKey );
  glutMouseFunc( HandleMouse );
  glutMotionFunc( HandleMotion );
  
  glutTimerFunc(0, reset_window_title, 50);
    
 // HandleMotion( 0, 0 );
    
  glClearColor( 0.3f, 0.3f, 0.3f, 1.0 );
  glEnable( GL_DEPTH_TEST );
    
 // FILE* f = fopen("CANDIDATE.h", "w");
 //  fputs(FULLYQUALIFIEDPATH, f);
//  fclose(f);
    
    ImGui_ImplAlgeSDK_Main();
  FindAppName();  sprintf(app.rm.resourcepath, "%s", argv[0]);
  
  char* l = strrchr(app.rm.resourcepath, '.');
	
  if (l) l[0] = 0;
   l = strrchr(app.rm.resourcepath, '/');
  if (l) l[0] = 0;
	
  strcat(app.rm.resourcepath, "/");
  strcat(app.rm.resourcepath, ALGEAPPNAME);
  strcat(app.rm.resourcepath, ".app/Contents/Resources/Data");
  
 // initAL(app.rm.resourcepath);
    FMOD_Init();
  app.rm.Init(app.rm.resourcepath);
 //   app.resolutionReported.x = kWindowWidth;
 //   app.resolutionReported.y = kWindowHeight;
    app.rightSide = kWindowWidth;
    app.bottomSide = kWindowHeight;
    app.originX = app.rightSide /2;
    app.originX = app.bottomSide /2;
    app.Init(app.rm.resourcepath);

    
  HandleReshape(kWindowWidth, kWindowHeight);
    
  startTime = glutGet(GLUT_ELAPSED_TIME);
  deltaT = 0;
  time1.start();
  lastTime = time1.getElapsedTimeInSec();
    
  font = nullptr;
   
  // https://github.com/jtsiomb/libdrawtext/blob/master/examples/simple/simple.c
    
  if(!(font = dtx_open_font("/Library/Fonts/AppleGothic.ttf", 24))) {
        fprintf(stderr, "failed to open font\n");
   }
    
  // XXX select the font and size to render with by calling dtx_use_font
//if you want to use a different font size, you must first call:
   // dtx_prepare(font, size) once.
   //
   
  dtx_use_font(font, 24);
  glutMainLoop( );
  
  ImGui_ImplAlgeSDK_Shutdown();
  return 0;
}

#include "../../SDKSRC/Base/externit.cpp"

