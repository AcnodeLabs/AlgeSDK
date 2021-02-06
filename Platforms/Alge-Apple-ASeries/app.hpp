#include "../../AlgeSDK_1701/SDKSRC/Base/cbasev1_2.h"
#include <string>
//#include <future>

//#define BOOST_ALL_DYN_LINK
//#include <boost\thread.hpp>

#define BTN_CLOSE 7

#define ANIMSEQ_SPHERE	1
#define ANIMSEQ_SURFACE	2
#define ANIMSEQ_LAND	3
#define ANIMSEQ_SLINGSHOT	4

//PLANETS APP

#define NUMSTARS (350)
#define ID_STAR 10
#define ID_BTN 11
#define ID_PANEL 12
#define ID_FONTS	13
#define ID_SPLASH	14
#define ID_SATRINGS	15
#define ID_LINK_YOUTUBE	16
#define ID_LINK_WIKIPEDIA 17
#define ID_VOYAGER 18

#define SOUND_COSMOS	0
#define SOUND_SPHERE	1
#define SOUND_SURFACE	2
#define SOUND_LAND		3
#define SOUND_SLINGSHOT	4

namespace PlanetApp {
	class StateMgr {
	public:
		short currentState;
		enum states {
			EVACUATING,EVACUATED,LANDING,LANDED,SLINGING,SLINGED,SURFACING,SURFACED
		};

	};
}

class App {
	PlanetApp::StateMgr state;
	static const short USER_ALXFILENAME = 1;
	char pl9[9][256], szP1[256], alxfilename[256], link[256], text[64], idvideox[32], szAbout[255];

	float zmax, beat, tfontA, animstep, dt;
	float dist; /*COMENT OF A MEMBER */
	short planetNum;
	short starpos[3][NUMSTARS];
	short numv, light, blend, depth;;
	int nseq, idtype;
	
	float eye[3], eyerot[3], tgt[3], size[10], youFrame[4];
	short keyframe;
	bool unpressed, splashit, nearv, hsLeftHit, hsRightHit, hsLinksHit, youReady, _freezeRot, linkActive;
	int zx, zy, it, t, tbegin, tplanetchanged;

			GLfloat	xrot, yrot, xspeed, yspeed, z;
			GLfloat LightAmbient[4];//=		{ 0.5f, 0.5f, 0.5f, 1.0f };
			GLfloat LightDiffuse[4];//=		{ 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat LightPosition[4];//=		{ 0.0f, 0.0f, 2.0f, 1.0f };
			CHotSpot hsEvac, hsSurf, hsLand, hsSling, hsLeft, hsRight, hsLinks;
			CControls controls;
			CAnimator can;
			CTrackBall trackball;
			FontMap16x16 fonts;
			CTimed fntX, fntY, fntZ, animStep;
			CTimed tSplashRot360, tSplashZ, tSplashFOV, tPlanetRot, tPlanetIn, tSlidingPanelY;
	
	void freezeRot(bool val) {
		_freezeRot = val;
		if (_freezeRot) {
			_freezeRot = val;
		}
	}

	float tgt0, tgt1, tgt2, eye0, eye1, eye2, eyerot2;
		
	void saveCurrentLocAndEyeDirection() {
		tgt0 = tgt[0] ;tgt1 = tgt[1];tgt2 = tgt[2];eye0 = eye[0] ;eye1 = eye[1];eye2 = eye[2];eyerot2=eyerot[2];
	}

    void AnimDo() {
		float bz = rm.models[planetNum]->boundz();/*BOUNDZ*/
		float altFar = bz*5;
		freezeRot(false);
		float altA = bz*1.3;
		float altB = bz*0.8;
		float altC = bz*1.01;

		if (nseq==ANIMSEQ_SPHERE) {
            
			if (keyframe==1) {
				saveCurrentLocAndEyeDirection();
				animstep = 0;
				keyframe++;
			}
            
			if (keyframe == 2) {
				tgt[0] = can.QuadraticEaseIn(animstep, tgt0, 0.0f);
				tgt[1] = can.QuadraticEaseIn(animstep, tgt1, 0.0f);
				tgt[2] = can.QuadraticEaseIn(animstep, tgt2, 0.0f);
				eye[0] = can.QuadraticEaseIn(animstep, eye0, 0.0f);
				eye[1] = can.QuadraticEaseIn(animstep, eye1, 0.0f);
				eye[2] = can.QuadraticEaseIn(animstep, eye2, -altFar);
				eyerot[2] = can.QuadraticEaseIn(animstep, eyerot2, 0.0f);
				animstep = incAnim(animstep);
				if (animstep>1) { animstep = 0; nseq = 0; }
			}
		}
        
		if (nseq==0) {
			tgt[0] = tgt[1] = tgt[2] = 0; eye[0] = 0; eye[1] = 0;	eye[2] = -altFar;
			eyerot[2] = 0;
			keyframe = 1;
		}
        
		if (nseq==ANIMSEQ_SURFACE) { //SURFACE VIEW
			
			if (keyframe == 1) {
				saveCurrentLocAndEyeDirection();
				animstep = 0;
				keyframe ++;
			}

			if (keyframe==2) {
				
				tgt[0] = can.QuadraticEaseIn(animstep, tgt0, -altB);
				tgt[1] = can.QuadraticEaseIn(animstep, tgt1, 0.0f);;
				tgt[2] = can.QuadraticEaseIn(animstep, tgt2, 0.0f);
				
				eye[0] = can.QuadraticEaseIn(animstep, eye0, -altB);
				eye[1] = can.QuadraticEaseIn(animstep, eye1, 0.0f);
				eye[2] = can.QuadraticEaseIn(animstep, eye2, -altB);
				
				eyerot[2] = can.QuadraticEaseIn(animstep, eyerot2, 90);
				animstep = incAnim(animstep);
				if (animstep>1 ) {saveCurrentLocAndEyeDirection(); animstep =0;keyframe++ ;}
			}
            
			if (keyframe ==3) {
				animstep = incAnim(animstep);
				if (animstep>1 ) {saveCurrentLocAndEyeDirection(); animstep =0;}
			}

		}
        
		if (nseq==ANIMSEQ_LAND) { //Land
			//KeyFrame 1
		//	yrot = 0;//-0.01f *t ; //cancel out movement
					
			if (keyframe == 1) {
				saveCurrentLocAndEyeDirection();
				animstep = 0;
				keyframe++;
			}

			//if (keyframe == 2) {
			//	tgt[0] = can.QuadraticEaseIn(animstep, tgt0, 0.0f);
			//	tgt[1] = can.QuadraticEaseIn(animstep, tgt1, 0.0f);
			//	tgt[2] = can.QuadraticEaseIn(animstep, tgt2, 0.0f);
			//	eye[0] = can.QuadraticEaseIn(animstep, eye0, 0.0f);
			//	eye[1] = can.QuadraticEaseIn(animstep, eye1, 0.0f);
			//	eye[2] = can.QuadraticEaseIn(animstep, eye2, -altFar);
			//	eyerot[2] = can.QuadraticEaseIn(animstep, eyerot2, 0.0f);
			//	animstep = incAnim(animstep,8);
			//	if (animstep>1) { animstep = 0;  keyframe++;saveCurrentLocAndEyeDirection();}
			//}
   //         
			if (keyframe==2) {
				tgt[0] = tgt0; tgt[1] = tgt1;
				tgt[2] = can.QuadraticEaseInOut(animstep, tgt2, -(bz * 1.001f));
				eye[0] = eye0; eye[1] = eye1;
				eye[2] = can.QuadraticEaseIn(animstep,eye2, -(bz* 1.001f));
				animstep = incAnim(animstep);
				if (animstep>1) {saveCurrentLocAndEyeDirection(); animstep =0;keyframe++;}                
			}
            
			if (keyframe==3) {
				freezeRot(true);
			}
            
		}

		if (nseq==ANIMSEQ_SLINGSHOT) { //SLINGSHOT
			//KeyFrame 1
			if (keyframe == 1) {
				saveCurrentLocAndEyeDirection();
				animstep = 0;
				keyframe++;
			}

			if (keyframe==2) {
				tgt[0] = can.QuadraticEaseIn(animstep, tgt0, bz*1.01);
				tgt[1] = can.QuadraticEaseIn(animstep, tgt1, 0.0f);
				tgt[2] = can.QuadraticEaseIn(animstep, tgt2, 0.0f);
				eye[0] = can.QuadraticEaseIn(animstep,eye0, bz*1.01);
				eye[1] = can.QuadraticEaseIn(animstep, eye1, 0.0f);
				eye[2] = can.QuadraticEaseIn(animstep, eye2, -bz*1.05);
				eyerot[2] = can.QuadraticEaseIn(animstep,eyerot2, 90.f);
				animstep = incAnim(animstep);
				if (animstep>1 ) {animstep =0;keyframe++;}
			}
            
			if (keyframe==3) {
				static float yrotin = yrot;
				yrot+=1;
				if (yrot>(yrotin+180)) {keyframe++;animstep=0;}
			}
            
			if (keyframe==4) {
				yrot+=1.4f;
				tgt[0] = can.QuadraticEaseIn(animstep, altC, 0);
				tgt[1] = can.QuadraticEaseIn(animstep,0.0f, 0.0f);
				tgt[2] = can.QuadraticEaseIn(animstep,0.0f, -1.0f);
				eye[0] = can.QuadraticEaseIn(animstep,altC,0.0f);
				eye[1] = can.QuadraticEaseIn(animstep,0.0f, 0.0f);
				eye[2] = can.QuadraticEaseIn(animstep,- altC/2., - altFar);
				eyerot[2] = can.QuadraticEaseIn(animstep,90.f, 0.f);
				animstep = incAnim(animstep);
				if (animstep>1 ) {animstep =1;yrot-=1.4f;}
			}
            
		}
        

        
	}
	void PlanetChanged() {
		//output.pushP(CMD_TOAST, $ "Seeking Content", 0);
        tPlanetRot.ReDo();
		tPlanetIn.ReDo();
		fntX.ReDo();fntY.ReDo();fntZ.ReDo();
		trackball.reset();
		dist = 0;//zoom reset
	}

#ifndef NOGL
    void DrawLink(char* txt, int radius, int IDTYPE) {
        if (!youReady) return;
        glPushMatrix();
        hudBegin(controls.screen);
        fonts.print(txt);
        //glTranslatef(-controls.screen[0]/2*0.25, controls.screen[1]/2*0.55,0);
        //rm.models[IDTYPE]->glDraw();
        glTranslatef(-controls.screen[0]/2*0.50, controls.screen[1]/2*0.55,0);
        rm.models[ID_FONTS]->scale(controls.screen[0]/58.0f);
        rm.models[ID_FONTS]->glDraw();
        hudEnd();
		glPopMatrix();
	}
#endif

    //Helper Functions
    float incAnim(float animstep, float speed=1) {
		if (animstep==0) {animStep.Set(0,1,speed*0.1f);animStep.ReDo();}
		animstep = animStep.StepLinear(dt);
		return (animstep);
	}
	void LoadModel(int modelID, char* desc, char* alxfile, char* tgafile, float scale) {
        rm.loadAlxModel(alxfile, tgafile?tgafile:AUTO, modelID, scale); strcpy(rm.models[modelID]->name, desc);
    }
    void PrintInfo(short planeNum) {
        
		if (nseq==0) {
			char line[256] = {0};
			strcat(line, pl9[planeNum]);
			numv = 0;
			char * pch = strtok (line,"\n");
			while (pch != NULL)		{
				fonts.print(pch);
#ifndef NOGL
				rm.models[ID_FONTS]->glDraw();
				glTranslatef(fntX.StepLinear(dt),fntY.StepLinear(dt),fntZ.StepLinear(dt));
#endif
                pch = strtok (NULL, "\n");
                
            }
		}
	}
	bool MakeLink(int id1, char* itxt, char* idvideo, int idtype1, int* idty) {
		static int lastId=0;
        strcpy(text, itxt);
        strcpy(idvideox, idvideo);
		sprintf(link, "http://www.youtube.com/watch?v=%s",idvideox);
        *idty = idtype1;
        
        if (idtype1==ID_LINK_YOUTUBE && id1!=lastId) {
            //output.pushP(CMD_TOAST, $ "Seeking Content ..", 0);
            output.pushP(CMD_YOUTUBE_SHOW, $ idvideox, youFrame);
            youReady = false;
            lastId = id1;
        }
        
		return true;
	}
	bool getSomeInfo(int planetNum, int* idtype , char* link) {
		
		//if (planetNum==0 && nseq==0)     return MakeLink(1, "Article - Mercury (planet)","http://en.wikipedia.org/wiki/Planet_Mercury",ID_LINK_WIKIPEDIA, idtype);
		if (planetNum==0 && nseq==ANIMSEQ_SURFACE)     return MakeLink(2, "The Planet Mercury","o3dnVR_Xtpg",ID_LINK_YOUTUBE, idtype);
		if (planetNum==0 && nseq==ANIMSEQ_SLINGSHOT)   return MakeLink(3, "Mission to Mercury - MESSENGER","oswC3GXooZA",ID_LINK_YOUTUBE, idtype);
		if (planetNum==0 && nseq==ANIMSEQ_LAND)   return MakeLink(4, "Landing on Planet Mercury in 2011","Z_HwjzjqwN4",ID_LINK_YOUTUBE, idtype);
		
		//if (planetNum==1 && nseq==0)     return MakeLink(5, "Article - Venus","http://en.wikipedia.org/wiki/Planet_Venus",ID_LINK_WIKIPEDIA, idtype);
		if (planetNum==1 && nseq==ANIMSEQ_LAND)     return MakeLink(6, "Robotic Exploration of Venus","oet63vzBvkg",ID_LINK_YOUTUBE, idtype);
		if (planetNum==1 && nseq==ANIMSEQ_SURFACE)  return MakeLink(7, "Venus Surface Tour", "ro-EG0ZCvKE",ID_LINK_YOUTUBE, idtype);
		if (planetNum==1 && nseq==ANIMSEQ_SLINGSHOT)  return MakeLink(8, "Mariner 10 - Venus Slingshot", "iypYPGE19ME",ID_LINK_YOUTUBE, idtype);
		
		if (planetNum==2 && nseq==ANIMSEQ_SURFACE)	return MakeLink(9, "Planet Earth seen from space", "P5_GlAOCHyE", ID_LINK_YOUTUBE, idtype);
		if (planetNum==2 && nseq==0)				return MakeLink(10, "Carl Sagan - Pale Blue Dot", "wupToqz1e2g", ID_LINK_YOUTUBE, idtype);
		if (planetNum==2 && nseq==ANIMSEQ_SLINGSHOT)	return MakeLink(11, "Views From Low Earth Orbit", "jlNEHKpQyio", ID_LINK_YOUTUBE, idtype);
		if (planetNum==2 && nseq==ANIMSEQ_LAND)				return MakeLink(12, "NASA Shuttle Endeavour Re-Entry Video", "hK1RxQKCmCE", ID_LINK_YOUTUBE, idtype);
		
		//if (planetNum==3 && nseq==0)		return MakeLink(13, "Article - Mars", "http://en.wikipedia.org/wiki/Planet_Mars", ID_LINK_WIKIPEDIA, idtype);
		if (planetNum==3 && nseq==ANIMSEQ_LAND)		return MakeLink(14, "Curiosity Rover Mission", "P4boyXQuUIw", ID_LINK_YOUTUBE, idtype);
		if (planetNum==3 && nseq==ANIMSEQ_SURFACE)		return MakeLink(15, "Panoramic Video of Mars Surface", "Cvq1CYazUzc", ID_LINK_YOUTUBE, idtype);
		
		if (planetNum==4 && nseq==0)		return MakeLink(16, "Jupiter the Giant Planet", "IxgSJJ0kyoQ", ID_LINK_YOUTUBE, idtype);
		if (planetNum==4 && nseq==ANIMSEQ_LAND)		return MakeLink(17, "Jupiter Impact By The Galileo Spacecraft", "Lrs-H0PUFFA", ID_LINK_YOUTUBE, idtype);
		if (planetNum==4 && nseq==ANIMSEQ_SURFACE)		return MakeLink(18, "Weather on Jupiter", "yjU_CJWzAd4", ID_LINK_YOUTUBE, idtype);
		if (planetNum==4 && nseq==ANIMSEQ_SLINGSHOT)		return MakeLink(19, "JUNO NASA Jupiter Exploration Spacecraft", "r8p7eyLOxdM", ID_LINK_YOUTUBE, idtype);
        
		if (planetNum==5 && nseq==0)		return MakeLink(20, "Saturn Overview", "5p6yUIOzqtc", ID_LINK_YOUTUBE, idtype);
		if (planetNum==5 && nseq==ANIMSEQ_LAND)		return MakeLink(21, "Saturn Exploration", "cL2QrfxrgBI", ID_LINK_YOUTUBE, idtype);
		//if (planetNum==5 && nseq==ANIMSEQ_SURFACE)		return MakeLink(22, "Article - Saturn", "http://en.wikipedia.org/wiki/Saturn", ID_LINK_WIKIPEDIA, idtype);
		if (planetNum==5 && nseq==ANIMSEQ_SLINGSHOT)		return MakeLink(23, "Saturn Rings Disturber", "rgre5C-7Af4", ID_LINK_YOUTUBE, idtype);
        
		if (planetNum==6 && nseq==0)		return MakeLink(24, "Space School - Uranus", "G7f1nuwRq_E", ID_LINK_YOUTUBE, idtype);
		if (planetNum==6 && nseq==ANIMSEQ_SURFACE)		return MakeLink(25, "The Voyager 2 Uranus encounter", "r46QdcnAYeU", ID_LINK_WIKIPEDIA, idtype);
		if (planetNum==6 && nseq==ANIMSEQ_SLINGSHOT) return MakeLink(26, "Voyager Flyby of Uranus", "DrKQaDupdWQ", ID_LINK_YOUTUBE, idtype);
        
		if (planetNum==7 && nseq==0)		return MakeLink(27, "Neptune from The Planets Suite", "PSJub1A1aIk", ID_LINK_YOUTUBE, idtype);
		if (planetNum==7 && nseq==ANIMSEQ_SLINGSHOT) return MakeLink(28, "Voyager Flyby of Neptune (1989)", "ynUihD47ajo", ID_LINK_YOUTUBE, idtype);
		
		//if (planetNum==8 && nseq==0) return MakeLink(29, "Pluto Article", "http://en.wikipedia.org/wiki/Pluto",ID_LINK_WIKIPEDIA, idtype);
		if (planetNum==8 && nseq==ANIMSEQ_SURFACE) return MakeLink(30, "Why Pluto is Not a Planet", "BKoRt-6pjAE",ID_LINK_WIKIPEDIA, idtype);
		
		return false;
	}
	
public:
	PEG input,output;
	CResourceManager rm;
    
#ifndef NOGL
	void Render(float deltaT, int aX, int aY, int aZ) {
	
		dt = deltaT;//for outside funcs
		processInput();
        
		static float dist2 = 0;
        
		glClearColor(0,0,0,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
		if (splashit) {
			glLoadIdentity();
        	float r = tSplashRot360.StepLinear(deltaT);
		//	glRotatef(r, 0, 0, 1);
			glTranslatef(0, 0, tSplashZ. StepLinear(deltaT));
			rm.models[ID_SPLASH]->glDraw();
			return;
		}
        
		{
            
			for (int i =0; i<NUMSTARS; i++) {
				if ((abs(starpos[0][i])<3 || abs(starpos[1][i])<3 || abs(starpos[2][i])<3)==false) {
					glLoadIdentity();
					aluLookAt(eye[0],eye[1],eye[2], tgt[0],tgt[1],tgt[2], 0,1,0);//aluLookAt(4.2f,0.0f,z, 0,0,0, 0,1,0);
					glRotatef(_freezeRot?yrot/100.0f:yrot,0.0f,1.0f,0.0f);
					glTranslatef(starpos[0][i], starpos[1][i], starpos[2][i]);
                    
					billboardBegin();
					rm.models[ID_STAR]->glDraw();
					billboardEnd();
				} else {
					glLoadIdentity();
				}
			}
		}
        
		glLoadIdentity();
        
		AnimDo();
		glRotatef(eyerot[2], 0,0,1);
		aluLookAt(eye[0],eye[1],eye[2], tgt[0],tgt[1],tgt[2], 0,1,0);
        
		if (z>-1.00000000f) {
			z = -1.0f;
		}
        
		int pinchDir = trackball.pinchDirection();
        
		//if (planetNum==1 || planetNum==6) yrot = -1 * yrot; //Venus and Uranus Rotate Clockwise
        
		if (rm.models[planetNum]) {
			dist2 = dist + 3.0f * pinchDir;
			if (dist<dist2) dist += 0.1f;
			if (dist>dist2) dist -= 0.1f;
			limitf(&dist, -.5f, 10.0f);
            
			glTranslatef(0, 0, dist);
			if (tPlanetIn.done) trackball.ApplyRotate();
			glTranslatef(0, 0, tPlanetIn.StepLinear(deltaT));
            
			//if (nseq==ANIMSEQ_LAND)
			yrot = -tPlanetRot.StepLinear(deltaT);
			if (!_freezeRot) glRotatef(yrot, 0.0f, 1.0f, 0.0f);
			
			if (planetNum==5) /*SATURN*/ {
				glRotatef(90,1.0f,0.0f,0.0f);
				glRotatef(10, 0.0f, 1.0f, 0.0f);
				
				rm.models[ID_SATRINGS]->glDraw();

				glRotatef(-10, 0.0f, 1.0f, 0.0f);
				glRotatef(-90, 1.0f, 0.0f, 0.0f);//Remove this line if dual rings
				/*glRotatef(-180,1.0f,0.0f,0.0f);
				rm.models[ID_SATRINGS]->glDraw();
				glRotatef(90,1.0f,0.0f,0.0f);*/
			}
            
            rm.models[planetNum]->glDraw();
			
            glTranslatef(0,0,rm.models[planetNum]->boundz()*3);
			glRotatef(180,0,1,0);
            
			rm.models[ID_VOYAGER]->glDraw();
            
			static int ID1 = 0;
			linkActive = getSomeInfo(planetNum, &ID1, link);
			if (linkActive) {
				glColor4f(1,1,hsLinksHit?0:1,1);
				DrawLink(text, size[planetNum], ID1);
				glColor4f(1,1,1,1);
			} else {
                output.pushP(CMD_YOUTUBE_CLOSE, 0,0);
            }
            
            
            
			if (trackball.isPinching()) return;
            
		}
        
		glLoadIdentity();
        //glTranslatef(0, 0.66f, 2.0f);
		glTranslatef(0, tSlidingPanelY.StepLinear(deltaT), -2.0f);
		glRotatef(180,0,0,1);
		glDisable(GL_DEPTH_TEST);
		rm.models[ID_PANEL]->glDraw();//DRAW SLIDING PANEL
		glEnable(GL_DEPTH_TEST);
        
		if (unpressed) {
			glLoadIdentity();
			glDisable(GL_DEPTH_TEST);
			glTranslatef(-20.0f,-18.0f,-85.f);
			glColor4f(0.7,0.7,0.7,1);
			PrintInfo(planetNum);
			glColor4f(1,1,1,1);
		}
        
		glLoadIdentity();
		//DRAW RT AND LEFT BTN
		if (nseq==0) {
            
			float s1 = unpressed?0.5f:0.76f;
			float z1 = unpressed?-2.1f:-3.1f;
			glTranslatef(s1,0,z1);
            
			bool invrt = !unpressed;
            
			if (invrt) glRotatef(179, 0, 0, 1);
			rm.models[ID_BTN]->glDraw();
			if (invrt) glRotatef(-179, 0, 0, 1);
            
			glTranslatef(-s1*2,0,0);
			glRotatef(180,0,0,1);
            
			if (invrt) glRotatef(179, 0, 0, 1);
			rm.models[ID_BTN]->glDraw();
			if (invrt) glRotatef(-179, 0, 0, 1);
            
		}
        
		glEnable(GL_DEPTH_TEST);
	}
#endif
    
	void processInput() {
        
		static int cmd, x,y;
		static int KroSSS = 0;
        
		static bool btn_close_hit = false;
        
        
		static bool hsEvacHit;
		static bool hsSurfHit;
		static bool hsLandHit;
		static bool hsSlingHit;
        
		PEG::CMD* p;
        
		p = input.pull();
		cmd = p->command;
		x = p->i1;
		y = p->i2;
        
        
		switch (cmd) {
                
			case CMD_SCREENSIZE:
            {
                controls.screen[0] = x;
                controls.screen[1] = y;
                CHotSpot::Res(x, y);
                
                youFrame[0] = x * 0.05; youFrame[1] = y*0.18;
                youFrame[2] = x * 0.13;
                youFrame[3] = youFrame[2];
                break;
            }
                             
	        case CMD_YOUTUBE_READY:
            {
                youReady = true;
                break;
            }
			case CMD_TOUCH_START:
	            
            {
                hsLeftHit = false;
                hsRightHit = false;
                zx = x;
                zy = y;
                unpressed = true;
                float xf = controls.screen[0] / 320.0f;
                float yf = controls.screen[1] / 480.0f;
                if (splashit) {
                    if (y>0*yf && y<45*yf && x>270*xf && x<320*xf) output.pushP(CMD_MSG, $ szAbout, $ "Info");
                    if (y>408*yf && y<447*yf && x>186*xf && x<284*xf) {beat = 0; splashit = false;}// Begin Arena
                    tbegin = t;
                    PlanetChanged();
                    break;
                }
                
                else {
                    if (controls.screen[0]==1280) {//OSX
                        hsEvac.Set(controls.screen[0], controls.screen[1],34,472,114,543);
                        hsSurf.Set(controls.screen[0], controls.screen[1],34,561,114,632);
                        hsLand.Set(controls.screen[0], controls.screen[1],34,649,114,721);
                        hsSling.Set(controls.screen[0], controls.screen[1],34,737,114,806);
                        hsLeft.Set(controls.screen[0], controls.screen[1],325,429,349,451);
                        hsRight.Set(controls.screen[0], controls.screen[1],325,828,349,849);
                        
                        hsEvacHit = hsEvac.HitX(x,y);
                        hsSurfHit = hsSurf.HitX(x,y);
                        hsLandHit = hsLand.HitX(x,y);
                        hsSlingHit = hsSling.HitX(x,y);
                    } else {//iOs
                        hsEvacHit = hsEvac.Hit(x,y);
                        hsSurfHit = hsSurf.Hit(x,y);
                        hsLandHit = hsLand.Hit(x,y);
                        hsSlingHit = hsSling.Hit(x,y);
                        hsLinksHit = hsLinks.Hit(x,y);
                    }
                    
                    if (hsEvacHit || hsSurfHit || hsSlingHit || hsLandHit) {
                        keyframe = 1;
                        animstep = 0;
						freezeRot(false);
                    }
                    
                    if (hsLinksHit) {
                        if (linkActive) {
                            output.pushP(CMD_YOUTUBE_SHOW, $ idvideox, youFrame);
                        }
                        
                        break;
                    }
                    
                    if (hsEvacHit) {
                        nseq = ANIMSEQ_SPHERE;
                        dist = 0;
                        output.pushP(CMD_SNDPLAY+SOUND_SPHERE, 0,0);
                        break;
                    }
                    
                    if (hsSurfHit) {
                        nseq = ANIMSEQ_SURFACE;
                        dist = 0;
                        output.pushP(CMD_SNDPLAY+SOUND_SURFACE, 0,0);
                        break;
                    }
                    
                    if (hsLandHit) {
                        nseq = ANIMSEQ_LAND;
                        dist = 0;
                        output.pushP(CMD_SNDPLAY+SOUND_LAND, 0,0);
                        break;
                    }
                    
                    if (hsSlingHit) {
                        nseq = ANIMSEQ_SLINGSHOT;
                        dist = 0;
                        output.pushP(CMD_SNDPLAY+SOUND_SLINGSHOT, 0,0);
                        break;
                    }
                    
                } ;
                
                
                {
                    unpressed = true;
                    
                    {
                        
                        
                        KroSSS = 0;
                        hsLeftHit = hsLeft.Hit(x,y);
                        hsRightHit = hsRight.Hit(x,y);
                        if (hsLeftHit) KroSSS  = KROSS_LEFT;
                        if (hsRightHit) KroSSS = KROSS_RIGHT;
                        
                        
                        switch (KroSSS)
                        {
                                
                            case KROSS_RIGHT:
                                
                                planetNum++;
                                //beat = 0;
                                //z = -18.0000000000f;//
                                if (planetNum>8) planetNum=0;
                                // nearv = false;
                                //animstep = 0;
                                nseq=0;
                                PlanetChanged();
                                break;
                            case KROSS_LEFT:
                                //z = -18.0000000000f;
                                //beat = 0;
                                planetNum--;
                                if (planetNum<0) planetNum=8;
                                
                                //nearv = false;
                                //animstep = 0;
                                nseq=0;
                                PlanetChanged();
                                break;
                        }
                        
                    }
                }
                
                break;
            }
		}
        
        
		if (btn_close_hit) output.pushI(CMD_END, 0, 0);
        
		if (KroSSS || hsEvacHit || hsSurfHit || hsSlingHit || hsLandHit) return;
        
		trackball.processTouches(cmd, x, y);
        
	}
	
	
	void Init(char* path) {

		int maxTextureSize =0;
#ifndef NOGL
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
#endif
		freezeRot(false);
		size[0]  = 4880; size[1] = 7500; size[2] = 7500; size[3] = 4444; size[4]=9900;
		size[5]  = 9500; size[6] = 8000; size[7] = 8000; size[8] = 4880; size[9]=2274;
		youReady = false;
        
		it = 0;
        
		strcpy(szAbout, "3D Planets v2.2 by AcnodeLabs\nNew in 2.2\n-Related YouTube content\n-Voyager Model\nInstructions:\nSwipe on Planet to Rotate\nPinch to Zoom In /Out\nUse HUD Buttons to enter\nView Modes\nPowered by ALGE SDK\nFollow: twitter.com/algesdk\nAcnodeLabs (c) 2011");
        
		nearv = false;
		nseq = 0;
		beat = 0;
		splashit = true;/*PRODUCTION=true*/
        
		sprintf(pl9[0],"Planet MERCURY [HD] %d\n4878 km diameter\nNo moons, -279 F to 800 F\n88 Earth days = 1 Mercury year\n59 Earth days = 1 Mercury day\n.06 mass\n.3 AU from the Sun",maxTextureSize);
		sprintf(pl9[1],"Planet VENUS [HD]\n12,104 km diameter\nNo moons, 900 F\n225 Earth days = 1 Venus year\n243 Earth days = 1 Venus day\n.82 mass\n.7 AU from the Sun");
		sprintf(pl9[2],"Planet EARTH [HD]\n12,756 km diameter\n1 moon, 56 F\n365 days = 1 Earth year\n24 hours = 1 Earth day\n1 mass\n1 AU from the Sun");
		sprintf(pl9[3],"Planet MARS [HD]\n6795 km diameter\n2 moons, -200 to 70 F\n687 Earth days = 1 Mars year\n24.5 Earth hours = 1 Mars day\n.1 mass\n1.67 AU from the Sun");
		sprintf(pl9[4],"Planet JUPITER [HD]\n142,985 km diameter\n63 moons, 3 rings, -150 F\n12 Earth years = 1 Jupiter year\n10 Earth hours = 1 Jupiter day\n318 mass\n5 AU from the Sun");
		sprintf(pl9[5],"Planet SATURN\n120,537 km diameter\n33 moons, main and thousands of smaller rings\n-300 F\n30 Earth years = 1 Saturn year\n10.5 Earth hours = 1 Saturn day\n95 mass\n9 AU from the Sun");
		sprintf(pl9[6],"Planet URANUS\n51,119 km diameter\n21 moons, 11 rings\n-350 F\n84 Earth years = 1 Uranus year\n15 Earth hours = 1 Uranus day\n14.5 mass\n19 AU from the Sun");
		sprintf(pl9[7],"Planet NEPTUNE\n50,538 km diameter\n13 moons, 4 rings\n-260 F\n165 Earth years = 1 Neptune year\n18 Earth hours = 1 Neptune day\n17 mass\n30 AU from the Sun");
		sprintf(pl9[8],"Dwarf PLUTO\n2320 km diameter\n3 moons, -370 F\n249 Earth years = 1 Pluto year\n6.5 Earth days = 1 Pluto day\n.003 mass\n49 AU from the Sun");
        
		for (int i=0; i<10; i++) {size[i] = size[i] / 12756.f;}
        
		rm.Init(path);
        
		strcpy(rm.resourcepath, path);
		zmax = 0;
#ifndef NOGL
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.7f, 0.7f, 0.7f, 0.5f);				// Black Background
		//glClearDepthf(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
        
		{
			LightAmbient[0] = 0.5f;	LightAmbient[1] = 0.5f;	LightAmbient[2] = 0.5f; LightAmbient[3] = 1.0f;
			LightDiffuse[0] = LightDiffuse[1]	= LightDiffuse[2] = LightDiffuse[3] = 1;
			LightPosition[0]  =	0.0f; LightPosition[1]  =	0.0f;LightPosition[2]  =	2.0f;LightPosition[3]  =	1.0f;
		}
        
		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
		glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
        
		glColor4f(1.0f, 1.0f, 1.0f, 0.5);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
#endif
		output.pushP(CMD_SNDSET+SOUND_COSMOS, $ "cosmos.mp3",0);
		output.pushP(CMD_SNDSET+SOUND_LAND, $ "anim_land.wav",0);
		output.pushP(CMD_SNDSET+SOUND_SPHERE, $ "anim_sphere.wav",0);
		output.pushP(CMD_SNDSET+SOUND_SLINGSHOT, $ "anim_slingshot.wav",0);
		output.pushP(CMD_SNDSET+SOUND_SURFACE, $ "anim_surface.wav",0);
        
		float sc;
		sc = 0.7f;
		

        //hires maps : http://laps.noaa.gov/albers/sos/sos.html 2k
		auto m0 = rm.loadAlxModel((char*) "sphere.alx", (char*) "mercury4k.tga", 0, size[0]*sc);
		auto m1 = rm.loadAlxModel((char*) "sphere.alx", (char*) "venus4_rgb_cyl_www.tga", 1, size[1]*sc);
		auto m2 = rm.loadAlxModel((char*)"sphere.alx", (char*) "earth4k.tga", 2, size[2]*sc);
		auto m3 = rm.loadAlxModel((char*) "sphere.alx", (char*) "mars4k.tga", 3, size[3]*sc);
		rm.loadAlxModel((char*) "sphere.alx", (char*) "jupiter_rgb_cyl_www.tga", 4, size[4]*sc);
		rm.loadAlxModel((char*) "sphere.alx", (char*) "saturn.tga", 5, size[5]*sc);
		rm.loadAlxModel((char*) "sphere.alx", (char*) "uranus.tga", 6, size[6]*sc);
		rm.loadAlxModel((char*) "sphere.alx", (char*) "neptune.tga", 7, size[7]*sc);
		rm.loadAlxModel((char*) "sphere.alx", (char*) "pluto.tga", 8, size[8]*sc);
		
		auto lane1 = true;// (m0.get() && m1.get() && m2.get() && m3.get());
		
		if (lane1) {
			strcpy(rm.models[0]->name, "Mercury");
			strcpy(rm.models[1]->name, "Venus");
			strcpy(rm.models[2]->name, "Earth");
			strcpy(rm.models[3]->name, "Mars");
			strcpy(rm.models[4]->name, "Jupiter");
			strcpy(rm.models[5]->name, "Saturn");
			strcpy(rm.models[6]->name, "Uranus");
			strcpy(rm.models[7]->name, "Neptune");
			strcpy(rm.models[8]->name, "Pluto");
		}
		
		

		rm.loadAlxModel((char*) "font.alx",AUTO,  ID_FONTS,1);
		fonts.usetexof(rm.models[ID_FONTS]);
		rm.models[ID_FONTS]->noVBO = true;
        
		rm.loadAlxModel((char*) "satrings.alx", AUTO, ID_SATRINGS,1*.8f);
		strcpy(rm.models[ID_SATRINGS]->name, "satrings");
        
		for (int i=0; i< rm.models[ID_SATRINGS]->n_vertices; i++) {
			//	rm.models[ID_SATRINGS]->vertex_array[i*3+2]= 0.0f;
		}
		rm.models[ID_SATRINGS]->SetScale(1.5, 1.5, 1.5);

        rm.loadAlxModel((char*) "misc.alx", AUTO, ID_PANEL, 0.55f);
		strcpy(rm.models[ID_PANEL]->name, "misc");
		rm.loadAlxModel((char*) "tabbar.alx",AUTO,  ID_BTN, 0.05f);
		strcpy(rm.models[ID_BTN]->name, "Tabbar");
		rm.loadAlxModel((char*)"star.alx", AUTO, ID_STAR, 0.2f);
		strcpy(rm.models[ID_STAR]->name, "Stardome");
		rm.loadAlxModel((char*)"splash.alx", (char*)"misc.tga", ID_SPLASH, 1);
		strcpy(rm.models[ID_SPLASH]->name, "Splash");
        
		rm.loadAlxModel((char*) "square.alx", (char*) "youtube.tga", ID_LINK_YOUTUBE, 15);
		strcpy(rm.models[ID_LINK_YOUTUBE]->name, "youtube");
		rm.loadAlxModel((char*) "square.alx", (char*) "wikipedia.tga", ID_LINK_WIKIPEDIA, 15);
		strcpy(rm.models[ID_LINK_WIKIPEDIA]->name, "wikipedia");
        rm.loadAlxModel((char*)"voyager2.alx", (char*)"voyager2.tga", ID_VOYAGER, 0.005f);
		strcpy(rm.models[ID_VOYAGER]->name, "Voyager");
        
		planetNum = 0;
		int loop = 10;
		output.pushP(CMD_SNDPLAY0+SOUND_COSMOS, $ "cosmos.mp3", (void*) & loop);
        
        
		xrot=0;
		yrot=0;
		z = - 20.f;
		xspeed = 0.3;
		yspeed = 0.3;
		light = 0;
		blend = 0;
        depth = 1;
        
#ifndef NOGL
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
#endif
        unpressed = true;
        
		for (int i =0; i<NUMSTARS; i++) {
			starpos[0][i] = randm()*140-30;// + 20;
			//	if (abs(starpos[0][i]<10)) starpos[0][i] *= 10;
			starpos[1][i] = randm()*140-30;// + 20;//updown angle +-90 deg;;//;rndm();
			//	if (abs(starpos[1][i]<10)) starpos[1][i] *= 10;
			starpos[2][i] = randm()*140-30;// + 20;//360;//rotatex;//70-i*2;//rndm();
			//	if (abs(starpos[2][i]<10)) starpos[2][i] *= 10;
            
		}
        
		//Timed Vars
		tSplashRot360.Set(10,360/*Deg*/, 180/*DegPerSec*/);
		tSplashFOV.Set(180,45,-90);
		tSplashZ.Set(0,-4.2, -4.2/*Zeds*/ / 3.0/*Sec*/);
		tPlanetRot.Set(0,999999999/*Deg*/, 2/*DegPerSec*/);
		tPlanetIn.Set(10,0, -3);
		tSlidingPanelY.Set(1.0f, 0.66f, 2);
		fntX.Set(  20, 0, -1);
		fntY.Set( -20, -2, 10);
		fntZ.Set( 0, -30, 0);
        
		//hotSpots
		hsEvac.Set(320,480,0,32,64,(32+52));
		hsSurf.Set(320,480,0,100,64,(100+52));
		hsLand.Set(320,480,0,168,64,(168+52));
		hsSling.Set(320,480,0,230,64,(230+52));
		hsLeft.Set(320, 480,225,0,249,35);
		hsRight.Set(320, 480,225,280,249,321);
		hsLinks.Set(320, 480, 80, 0, 110, 320);
        
		hsLeftHit = false;
		hsRightHit = false;
		dist = 0;
        linkActive = false;
	}
	void Deinit() {}
};
