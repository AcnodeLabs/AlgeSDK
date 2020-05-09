//
//  alge-mac.cpp
//  Alge-Mac
//
//  Created by Bilal on 6/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define MACOSX
#define ADA

#include "CANDIDATE.h"
//#define GLES3
#define ADA
#define CPP11
#define NO_BOX2D
#define NO_NATS

#include "../../../SDKSRC/Base/CBaseV1_2.h"

#include <GLUT/glut.h>
//#include <AL/alut.h>

//#include <glut.h>
#include <stdio.h>

#include <OpenAL/al.h>
#include <OpenAL/alc.h>

//http://www.e38.org/onboardmonitor.pdf //bmw
#define kWindowScale 0.6
#define kWindowWidth (2048 * kWindowScale)
#define kWindowHeight (1536 * kWindowScale)
#include CANDIDATE

#define TIMERMSECS 33

int startTime;
int prevTime;

App app;
static int elapsedTime;
#include "Timer.h"
//#include "MyOpenALSupport.h"

Timer time1;
float deltaT;
float lastTime;
float aX, aY, aZ;

ALsizei nAL;
#define NUM_BUFFERS_SOURCES 16
ALuint alSources[NUM_BUFFERS_SOURCES];
ALuint alBuffers[NUM_BUFFERS_SOURCES];
float alPosition[3];

#define dbg printf

void initAL(char *respath)
{
 
  nAL = NUM_BUFFERS_SOURCES;
  alGetError();

  ALCcontext *newContext = NULL;
  ALCdevice *newDevice = NULL;

  newDevice = alcOpenDevice(NULL);
  if (newDevice != NULL)
  {
    // Create a new OpenAL Context
    // The new context will render to the OpenAL Device just created
    newContext = alcCreateContext(newDevice, 0);
    if (newContext != NULL)
    {
      // Make the new context the Current OpenAL Context
      alcMakeContextCurrent(newContext);
    }
  }
  alListenerfv(AL_POSITION, alPosition);

  alGenBuffers(nAL, alBuffers);
  alGenSources(nAL, alSources);
}

void deInitAL()
{
  ALCcontext *context = NULL;
  ALCdevice *device = NULL;
  ALuint returnedNames[NUM_BUFFERS_SOURCES];

  // Delete the Sources
  alDeleteSources(NUM_BUFFERS_SOURCES, returnedNames);
  // Delete the Buffers
  alDeleteBuffers(NUM_BUFFERS_SOURCES, returnedNames);

  //Get active context
  context = alcGetCurrentContext();
  //Get device for active context
  device = alcGetContextsDevice(context);
  //Release context
  alcDestroyContext(context);
  //Close device
  alcCloseDevice(device);
  alutExit();
}

void sndSet(char *filename, int id, int loops)
{
  ALenum error = AL_NO_ERROR;
  ALenum format;
  ALvoid *data;
  ALsizei size;
  ALsizei freq;

  // Turn Looping ON
  if (loops > 0)
    alSourcei(alSources[id], AL_LOOPING, AL_TRUE);
  // Set Source Position
  alSourcefv(alSources[id], AL_POSITION, alPosition);
  // Set Source Reference Distance
  alSourcef(alSources[id], AL_REFERENCE_DISTANCE, 5.0f);

  char filespec[256];
  sprintf(filespec, "%s/%s", app.rm.resourcepath, filename);
  printf("\nSound File :%s ", filespec);

  alBuffers[id] = alutCreateBufferFromFile(filespec);
  if (alBuffers[id] == AL_NONE)
  {
    error = alutGetError();
    fprintf(stderr, "Error loading file: '%s'\n",
            alutGetErrorString(error));
    alutExit();
    exit(EXIT_FAILURE);
  }

  /*
  CFStringRef f1 = CFStringCreateWithFileSystemRepresentation(kCFAllocatorDefault, filespec);
    CFURLRef fileURL = CFURLCreateWithString(kCFAllocatorDefault, (CFStringRef)f1, NULL);
    data = MyGetOpenALAudioData(fileURL, &size, &format, &freq);
    CFRelease(fileURL);
   */
  // ALuint i1 = alutCreateBufferHelloWorld ();//alutCreateBufferFromFile (filespec);

  //   alBufferData(alBuffers[id], format, data, size, freq);

  // Release the audio data
  // free(data);

  // attach OpenAL Buffer to OpenAL Source
  alSourcei(alSources[id], AL_BUFFER, alBuffers[id]);
  alSourcePlay(alSources[id]);
}

void sndPlay(int id)
{
  printf("\nStart Playing Sound #%d", id);
  alSourcePlay(alSources[id]);
}

#define EXTERNIT extern "C"
#include "../../../SDKSRC/Base/externit.cpp"

void processOutput()
{
  PEG::CMD *c = app.output.pull();

  switch (c->command)
  {
  case CMD_SNDSET0:
  case CMD_SNDSET1:
  case CMD_SNDSET2:
  case CMD_SNDSET3:
  {
    sndSet((char *)c->param1, c->command - CMD_SNDSET, c->i2);
  }
  break;

  case CMD_SNDPLAY0:
  case CMD_SNDPLAY1:
  case CMD_SNDPLAY2:
  case CMD_SNDPLAY3:
  {
    sndPlay(c->command - CMD_SNDPLAY);
  }
  break;
  case CMD_TITLE:
    glutSetWindowTitle((char *)c->param1);
    break;

  case CMD_TOAST:
    glutSetWindowTitle((char *)c->param1);
    break;
  }
}

static void HandleDisplay()
{
  
  float newTime = time1.getElapsedTimeInSec();
  deltaT = newTime - lastTime;
  if (aX == 0 && aY == 0 && aZ == 0)
    aY = -9.8 * 100;

  app.Render(deltaT, aX, aY, aZ);
  processOutput();
  glutSwapBuffers(); 
  lastTime = newTime;
}

static void animate(int value)
{
  // Set up the next timer tick (do this first)
  glutTimerFunc(TIMERMSECS, animate, 0);

  // Measure the elapsed time
  int currTime = glutGet(GLUT_ELAPSED_TIME);
  int timeSincePrevFrame = currTime - prevTime;
  elapsedTime = currTime - startTime;

  // ##### REPLACE WITH YOUR OWN GAME/APP MAIN CODE HERE #####

  // Rotate the triangle
  //rot = (ROTRATE / 1000) * elapsedTime;

  // ##### END OF GAME/APP MAIN CODE #####

  // Force a redisplay to render the new image
  glutPostRedisplay();

  prevTime = currTime;
}

static void HandleIdle()
{
  glutPostRedisplay();
}

bool appintialized = false;
#define ADAHANDLING true
extern "C" void AppProcessInput(int, int, int);

static void sendInput(int cmd, int i1, int i2)
{
  if (!appintialized)
    return;
  if (!ADAHANDLING)
    app.input.pushI(cmd, i1, i2);
  if (ADAHANDLING)
    AppProcessInput(cmd, i1, i2);
}

static void HandleReshape(const int width, const int height)
{
  /*
     if (width!=320) {
     glutReshapeWindow(320, 480);
     return;
     }
     */

 // if (height > 0) // Prevent A Divide By Zero By
  {
    //height=1;										// Making Height Equal One

    glViewport(0, 0, width, height); // Reset The Current Viewport
    sendInput(CMD_SCREENSIZE, width, height);
    glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
    glLoadIdentity();            // Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.001f, 100.0f);

    glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
    glLoadIdentity();
  }
}

static void exitIt()
{
  app.Deinit();
  deInitAL();
  exit(0);
}

static void HandleKeyBoard(const unsigned char inKey, const int inPosX, const int inPosY)
{

  if (inKey == 27)
  {
    exitIt();
  }
  //if (inKey>='A' && inKey<='Z')   ---why restrict
  //  sendInput(CMD_KEYDOWN, inKey-49, 0);
  sendInput(CMD_KEYDOWN, inKey, 0);
}

static void HandleSpecialKey(const int inKey, const int inPosX, const int inPosY)
{
  sendInput(CMD_KEYDOWN, inKey, 0);
  printf("key");
}

static void HandleMouse(const int inButton, const int inState, const int inPosX, const int inPosY)
{
  if (inButton == 0)
    sendInput(inState == 0 ? CMD_TOUCH_START : CMD_TOUCH_END, inPosX, inPosY);
}

static void HandleMotion(const int inPosX, const int inPosY)
{
  int x = inPosX;
  int y = inPosY;
  sendInput(CMD_TOUCHMOVE, x, y);
}

char ResPath[256];

void FindAppName()
{
  FILE *f = fopen("CANDIDATE.h", "r");
  if (f)
  {
    char line[256];

    for (int i = 0; i < 100; i++)
    {
      fscanf(f, "%s", line);
      char *pn = strstr(line, ".hpp");
      strcpy(ResPath, line);
      if (pn)
      {
        int l = int(strlen(ResPath));
        ResPath[l - 8] = 0;
        strcat(ResPath, "/Data");
        break;
      }
    }

    fclose(f);
  }
  else
  {
  }
}
 
 #define sizeIni kWindowWidth * 1.25, kWindowHeight * 1.25

void reset_window_title(int para)
{
  glutSetWindowTitle("Solar System Planets 3D (c) AcodeLabs 2017");
 // glutFullScreen();
}

int main(int argc, char **argv)
{

  /*   ALuint helloBuffer, helloSource; */
  /*   alutInit (&argc, argv); */
  /*   helloBuffer = alutCreateBufferHelloWorld (); */
  /*   alGenSources (1, &helloSource); */
  /*   printf("playing"); */
  /*   alSourcei (helloSource, AL_BUFFER, helloBuffer); */
  /*   alSourcePlay (helloSource); */
  /*   alutSleep (4); */
  /*   printf(" exiting"); */
  /*   alutExit (); */
  /*   return EXIT_SUCCESS; */

  glutInit(&argc, argv);
  alutInit(&argc, argv);
 
  glutInitWindowSize(sizeIni);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  int theWindowHandle = glutCreateWindow("Solar");
  glutSetWindow(theWindowHandle);
  glutSetCursor(GLUT_CURSOR_CROSSHAIR);
  glutDisplayFunc(HandleDisplay);
  glutReshapeFunc(HandleReshape);
  glutIdleFunc(HandleIdle);
  glutKeyboardFunc(HandleKeyBoard);
  glutSpecialFunc(HandleSpecialKey);
  glutMouseFunc(HandleMouse);
  glutMotionFunc(HandleMotion);
  HandleMotion(0, 0);

  //glutFullScreen();

  // Setup default render states

  // glutDestroyMenu(glutGetMenu());

  //glClearColor(0.3f, 0.3f, 0.3f, 1.0);
  glEnable(GL_DEPTH_TEST);
  //glEnable( GL_COLOR_MATERIAL );

  //FILE *f = fopen("CANDIDATE.h", "w");
  //  fputs(FULLYQUALIFIEDPATH, f);
  //fclose(f);

  FindAppName();
  sprintf(app.rm.resourcepath, "%s", argv[0]);
  //char* l = strrchr(app.rm.resourcepath, '.');
  char *l = strstr(app.rm.resourcepath, PROJ_NAME);
  if (l)
    l[strlen(PROJ_NAME)] = 0;
  //    l = strrchr(app.rm.resourcepath, '/');
  //	if (l) l[0] = 0;
  char datadir[256];
  sprintf(datadir, "%s.app/Data", app.rm.resourcepath); // (char *) APP_SUBDIR);
  strcpy(app.rm.resourcepath, datadir);
  initAL(app.rm.resourcepath);
  app.Init(app.rm.resourcepath);
  appintialized = true;

  startTime = glutGet(GLUT_ELAPSED_TIME);
  deltaT = 0;
  time1.start();
  lastTime = time1.getElapsedTimeInSec();

  glutTimerFunc(0, reset_window_title, 0);

  HandleReshape(sizeIni);


  glutMainLoop();
  app.Deinit();
  alutExit();
  return 0;
}

//////////////////////////////////////////////////////////////////////////////
// Timer.cpp
// =========
// High Resolution Timer.
// This timer is able to measure the elapsed time with 1 micro-second accuracy
// in both Windows, Linux and Unix system 
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2003-01-13
// UPDATED: 2006-01-13
//
// Copyright (c) 2003 Song Ho Ahn
//////////////////////////////////////////////////////////////////////////////

#include "Timer.h"
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
// constructor
///////////////////////////////////////////////////////////////////////////////
Timer::Timer()
{
#ifdef WIN32
    QueryPerformanceFrequency(&frequency);
    startCount.QuadPart = 0;
    endCount.QuadPart = 0;
#else
    startCount.tv_sec = startCount.tv_usec = 0;
    endCount.tv_sec = endCount.tv_usec = 0;
#endif

    stopped = 0;
    startTimeInMicroSec = 0;
    endTimeInMicroSec = 0;
}

///////////////////////////////////////////////////////////////////////////////
// distructor
///////////////////////////////////////////////////////////////////////////////
Timer::~Timer()
{
}

///////////////////////////////////////////////////////////////////////////////
// start timer.
// startCount will be set at this point.
///////////////////////////////////////////////////////////////////////////////
void Timer::start()
{
    stopped = 0; // reset stop flag
#ifdef WIN32
    QueryPerformanceCounter(&startCount);
#else
    gettimeofday(&startCount, NULL);
#endif
}



///////////////////////////////////////////////////////////////////////////////
// stop the timer.
// endCount will be set at this point.
///////////////////////////////////////////////////////////////////////////////
void Timer::stop()
{
    stopped = 1; // set timer stopped flag

#ifdef WIN32
    QueryPerformanceCounter(&endCount);
#else
    gettimeofday(&endCount, NULL);
#endif
}



///////////////////////////////////////////////////////////////////////////////
// compute elapsed time in micro-second resolution.
// other getElapsedTime will call this first, then convert to correspond resolution.
///////////////////////////////////////////////////////////////////////////////
double Timer::getElapsedTimeInMicroSec()
{
#ifdef WIN32
    if(!stopped)
        QueryPerformanceCounter(&endCount);

    startTimeInMicroSec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
    endTimeInMicroSec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);
#else
    if(!stopped)
        gettimeofday(&endCount, NULL);

    startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
    endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
#endif

    return endTimeInMicroSec - startTimeInMicroSec;
}



///////////////////////////////////////////////////////////////////////////////
// divide elapsedTimeInMicroSec by 1000
///////////////////////////////////////////////////////////////////////////////
double Timer::getElapsedTimeInMilliSec()
{
    return this->getElapsedTimeInMicroSec() * 0.001;
}



///////////////////////////////////////////////////////////////////////////////
// divide elapsedTimeInMicroSec by 1000000
///////////////////////////////////////////////////////////////////////////////
double Timer::getElapsedTimeInSec()
{
    return this->getElapsedTimeInMicroSec() * 0.000001;
}



///////////////////////////////////////////////////////////////////////////////
// same as getElapsedTimeInSec()
///////////////////////////////////////////////////////////////////////////////
double Timer::getElapsedTime()
{
    return this->getElapsedTimeInSec();
}
