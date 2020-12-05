// Copyright (c) 2012 AcnodLabs Inc

/* 
ALGE SDK Demo :: NeHeLesson05 (coolness added)
*/

using namespace ImGui;

class /*NeHeLesson05*/ App : public AlgeApp { 

	float rot;

public:
	aL10 AL10;
	float t0;
    
    void RenderGuia() {
        ImGui_ImplAlgeSDK_BeforeRender();
        ShowMetricsWindow();
        ImGui_ImplAlgeSDK_AfterRender();
    }
    bool b = true;
	void Render(float dt, int aX, int aY, int aZ) {
        RenderGuia();
        //
        t0+=dt;
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
		glLoadIdentity();									// Reset The Current Modelview Matrix
        glDisable(GL_CULL_FACE);
        glCullFace(GL_BACK);
		glTranslatef(0.0f,0.0f,-8.0f + (1.0f * sin(t0)));
		glRotatef(rot,0.0f,1.0f,0.0f);	
        float ar = (float)getBackgroundSize().y / (float)getBackgroundSize().x;
        glScalef(1.0, ar, 1.0);
		AL10.Capture(GL_TRIANGLES);							// Start Drawing A Triangle
		AL10.glColor3f(1.0f,0.0f,0.0f);						// Red
		AL10.glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Front)
		AL10.glColor3f(0.0f,1.0f,0.0f);						// Green
		AL10.glVertex3f(-1.0f,-1.0f, 1.0f);					// Left Of Triangle (Front)
		AL10.glColor3f(0.0f,0.0f,1.0f);						// Blue
		AL10.glVertex3f( 1.0f,-1.0f, 1.0f);					// Right Of Triangle (Front)
		AL10.glColor3f(1.0f,0.0f,0.0f);						// Red
		AL10.glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Right)
		AL10.glColor3f(0.0f,0.0f,1.0f);						// Blue
		AL10.glVertex3f( 1.0f,-1.0f, 1.0f);					// Left Of Triangle (Right)
		AL10.glColor3f(0.0f,1.0f,0.0f);						// Green
		AL10.glVertex3f( 1.0f,-1.0f, -1.0f);				// Right Of Triangle (Right)
		AL10.glColor3f(1.0f,0.0f,0.0f);						// Red
		AL10.glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Back)
		AL10.glColor3f(0.0f,1.0f,0.0f);						// Green
		AL10.glVertex3f( 1.0f,-1.0f, -1.0f);				// Left Of Triangle (Back)
		AL10.glColor3f(0.0f,0.0f,1.0f);						// Blue
		AL10.glVertex3f(-1.0f,-1.0f, -1.0f);				// Right Of Triangle (Back)
		AL10.glColor3f(1.0f,0.0f,0.0f);						// Red
		AL10.glVertex3f( 0.0f, 1.0f, 0.0f);					// Top Of Triangle (Left)
		AL10.glColor3f(0.0f,0.0f,1.0f);						// Blue
		AL10.glVertex3f(-1.0f,-1.0f,-1.0f);					// Left Of Triangle (Left)
		AL10.glColor3f(0.0f,1.0f,0.0f);						// Green
		AL10.glVertex3f(-1.0f,-1.0f, 1.0f);					// Right Of Triangle (Left)
		AL10.Flush(0, false, true, false);	

		rot+=0.8f;
        
	}

	void Init(char* path) {
		AlInit(STANDARD);
		output.pushP(CMD_TITLE, $ "Alge Nehe Lesson05",0);
		rot = 0;

		t0= 0;
		glClearColor(COLOR_CORNFLOWERBLUE);
		
	}

	void Deinit() {
	}

};
