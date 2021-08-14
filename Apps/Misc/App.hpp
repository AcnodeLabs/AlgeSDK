// Copyright (c) 2018 AcnodLabs Inc

/* 
   ALGE SDK Flag App :: Flag
*/
#define HEIGHT 600
#define WIDTH 600



class /*Juices*/ App : public AlgeApp { 
    
    GameObject flag;
	
    unsigned char matrix[HEIGHT][WIDTH][3]; // r,g,b
    double offset=0;

    
    void m_init()
    {
        int i,j;

        for(i=100;i<200;i++)
            for(j=0;j<WIDTH;j++)
            {
                matrix[i][j][0] = 0; // red
                matrix[i][j][1] = 255; // green
                matrix[i][j][2] = 0; // blue
            }

        for(i=200;i<400;i++)
            for(j=0;j<WIDTH;j++)
            {
                matrix[i][j][0] = 255; // red
                matrix[i][j][1] = 255; // green
                matrix[i][j][2] = 255; // blue
            }

        for(i=400;i<600;i++)
            for(j=0;j<WIDTH;j++)
            {
                matrix[i][j][0] = 0; // red
                matrix[i][j][1] = 0; // green
                matrix[i][j][2] = 255; // blue
            }

        glClearColor(0,0,0.4,0);
        glOrtho(-2,2,-2,2,-2,2);
    }

    void m_display()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawPixels(WIDTH,HEIGHT,GL_RGB,GL_UNSIGNED_BYTE,matrix);
        
    }

    void m_idle()
    {
        static float count = 0.0;

        int i,j;
        count += 0.05;
        offset-=0.14;

        for(i=0;i<200;i++)
            for(j=0;j<WIDTH;j++)
            {
                matrix[i][j][0] = 0; // red
                matrix[i][j][1] = 200 + 55 * sin(count + j * 0.02); // green
                matrix[i][j][2] = 0; // blue
            }

        for(i=200;i<400;i++)
            for(j=0;j<WIDTH;j++)
            {
                matrix[i][j][0] = 200 + 55 * sin(count + j * 0.02); // red
                matrix[i][j][1] = 200 + 55 * sin(count + j * 0.02); // green
                matrix[i][j][2] = 200 + 55 * sin(count + j * 0.02); // blue
            }

        for(i=400;i<600;i++)
            for(j=0;j<WIDTH;j++)
            {
                matrix[i][j][0] = 0; // red
                matrix[i][j][1] = 0; // green
                matrix[i][j][2] = 200 + 55 * sin(count + j * 0.02); // blue
            }


    }
    
public:

    virtual void Init(char* path) {
		AlInit(STANDARD);
		SetTitle("Flag");
		AddDefaultCamera(Camera::CAM_MODE_2D, OrthoTypes::ORIGIN_IN_MIDDLE_OF_SCREEN);
        AddObject(&flag);
        m_init();
	}
    
	void processInput(PEG::CMD* p, float deltaT) { 
        static char tim[64];
        static int calls = 0;
        short touchData = 0;

		if (p->command == CMD_SCREENSIZE) {

		}

        if (p->command == CMD_HHMM) {
            calls++;
            float mmhhf = (p->i1) + p->i2/60.0;
            short ang = mmhhf*30;//0,3,6,9,12...=>0,90,180,270..

            sprintf(tim,"%02d:%02d %.2f %03d [call#%d]", p->i1, p->i2, mmhhf,ang,calls);
            SetTitle(tim);
        }
        
		if (0 && p->command == CMD_TOUCH_START) {

                
		}

	}
    
	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        glClearColor(1.0, 1.0, 1.0, 1.0);
          if (gob->is(flag)) {

            m_idle();
            m_display();
        }
	}

};
