// Copyright (c) 2019 AcnodLabs Inc

/* 
       ALGE SDK Demo :: NeHeLesson03 based Passthrough for ADA APP
     */

//#include "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"

// Ada Requirement
extern "C" void adainit(void);
extern "C" void adafinal(void);

extern "C" void AppInit(void);       //AdaCode
extern "C" void AppUpdate(float dt); //AdaCode
extern "C" void AppDeInit(void);     //AdaCode
extern "C" void AppRender(void);     //AdaCode

#define EMBED_ADA_APP

class /*Lesson03*/ App
{

public:
  CResourceManager rm;

  PEG output;
  PEG input;
  aL10 AL10; // To Make Desktop OpenGL style calls on an ES Platform

  void Render(float dt, int aX, int aY, int aZ)
  {
    glClearColor(0.,0.,0.,1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    
    glLoadIdentity();                                   // Reset The Current Modelview Matrix
                                                        // Move
#ifdef EMBED_ADA_APP
    AppUpdate(dt);
 //   glTranslatef(-1.5f, 0.0f, -10.0f);   // Move
    AL10.Capture(GL_TRIANGLES);          // Drawing Using Triangles
    AL10.glColor3f(1.0f, 0.0f, 0.0f);    // Set The Color To Red
    AL10.glVertex3f(0.0f, 1.0f, 0.0f);   // Top
    AL10.glColor3f(0.0f, 1.0f, 0.0f);    // Set The Color To Green
    AL10.glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
    AL10.glColor3f(0.0f, 0.0f, 1.0f);    // Set The Color To Blue
    AL10.glVertex3f(1.0f, -1.0f, 0.0f);  // Bottom Right
  //  AL10.Flush(0, false, true, false);   // Finished Drawing The Triangle
   // glTranslatef(3.0f, 0.0f, 0.0f);      // Move Left 1.5 Units And Into The Screen 6.0
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    AL10.Capture(GL_TRIANGLES); // Drawing Using Triangles
    AL10.glVertex3f(-1.0f, 1.0f, 0.0f);
    AL10.glVertex3f(1.0f, 1.0f, 0.0f);
    AL10.glVertex3f(1.0f, -1.0f, 0.0f);
    AL10.glVertex3f(1.0f, -1.0f, 0.0f);
    AL10.glVertex3f(-1.0f, -1.0f, 0.0f);
    AL10.glVertex3f(-1.0f, 1.0f, 0.0f);
//AL10.Flush(0, false, false, false);
    AppRender();
#endif
//for (int i=0; i<9; i++)
   // rm.models[8]->glDraw();
  }

  void Init(char *path)
  {
    rm.Init(path);
    printf(path);
    adainit();AppInit();
    //  al = & AL10;
#ifdef EMBED_ADA_APP
   // AppInit();
#endif

    alInit(STANDARD);
    output.pushP(CMD_TITLE, $ "Untitled", 0);

    GLfloat LightAmbient[4];  //=         { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat LightDiffuse[4];  //=         { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightPosition[4]; //=        { 0.0f, 0.0f, 2.0f, 1.0f };

    glEnable(GL_TEXTURE_2D);              // Enable Texture Mapping
    glShadeModel(GL_SMOOTH);              // Enable Smooth Shading
    glClearColor(0.0f, 1.0f, 0.0f, 0.5f); // Black Background
    //glClearDepthf(1.0f);                                                                      // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                           // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                            // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations

    {
      LightAmbient[0] = 0.5f;
      LightAmbient[1] = 0.5f;
      LightAmbient[2] = 0.5f;
      LightAmbient[3] = 1.0f;
      LightDiffuse[0] = LightDiffuse[1] = LightDiffuse[2] = LightDiffuse[3] = 1;
      LightPosition[0] = 0.0f;
      LightPosition[1] = 0.0f;
      LightPosition[2] = 2.0f;
      LightPosition[3] = 1.0f;
    }

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);

    glColor4f(1.0f, 1.0f, 1.0f, 0.5);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  }

  void Deinit()
  {

#ifdef EMBED_ADA_APP
    AppDeInit();
    adafinal();
#endif
  }
};
