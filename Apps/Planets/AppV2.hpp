#include <string>
#include <vector>

// Parallax Effect : http://blog.denivip.ru/index.php/2013/08/parallax-in-ios-applications/?lang=en

#define ID_LINK_YOUTUBE	16
#define ID_LINK_WIKIPEDIA 17

#define ANIMSEQ_SPHERE	1
#define ANIMSEQ_SURFACE	2
#define ANIMSEQ_LAND	3
#define ANIMSEQ_SLINGSHOT	4

using namespace std;

#include "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"
#define EXTERNIT extern "C"
#include "../../SDKSRC/Base/externit.cpp"

class App : AlgeApp {
    
    //CONSTANTS
    const int iUnassigned = -1;
    const int DIST_FAR = 75;
    const int DIST_NEAR = 5;
    const int DIST_CLOSER = 2;
    const int NUMSTARS = 777;
    
    //ALGE VARS
    CTrackBall trackball;
    CAnimator can;
    GameObject voyager, panel, star, cockpit, arrowkeys, saturnRings, planets[11];
    f3 eye,eyerot,tgt,up;
    CTimed animStepTimed;
    f3 check1f, starpos[777];
    vector<ResourceInf> planetInf;

    float timeVar = 0.0;
    int width = 0;
    int height = 0;
    
    float MIN_ALLOWABLE_DISTANCE = 5;
    float MIN_ALLOWABLE_SPEED = 50.0;
    float NORMAL_SPEED = 1000.0;
    
    int keyframe = 1;
    float animstep = 0.0;
    float deltaT;
    float bz = 1.0;
    int nseq = 0;
    float rGen = 0.0;
    float angle1 = 0.0;
    
    float desiredDist = DIST_NEAR;
    float dist = DIST_FAR;
    
    float speed = MIN_ALLOWABLE_SPEED;
    float move_speed = MIN_ALLOWABLE_SPEED;
    float tilt = 0.0;
    float desiredTilt = 0.0;
    
    const int NP = 12;
    
    string title;
    
    float sc = 1.0;
    int planetNo = 0;
    
    int screenX  = iUnassigned;
    int screenY  = iUnassigned;
    
    float rotation = 180.0;
    float desiredHeading = 180.0;
       
    float r, theta,phi = 0.0;
    
public:
	PEG input,output;
	CResourceManager rm;
    
    void Deinit() {}
    
    bool getSomeInfo(int planetNum, int* idtype , char* link) {
        
        //if (planetNum==0 && nseq==0)     return MakeLink(1, "Article - Mercury (planet)"),"http://en.wikipedia.org/wiki/Planet_Mercury")),ID_LINK_WIKIPEDIA, idtype);
        if (planetNum==0 && nseq==ANIMSEQ_SURFACE)     return MakeLink(2, New_String("The Planet Mercury"),New_String("o3dnVR_Xtpg"),ID_LINK_YOUTUBE, idtype);
        if (planetNum==0 && nseq==ANIMSEQ_SLINGSHOT)   return MakeLink(3, New_String("Mission to Mercury -MESSENGER"),New_String("oswC3GXooZA"),ID_LINK_YOUTUBE, idtype);
        if (planetNum==0 && nseq==ANIMSEQ_LAND)   return MakeLink(4, New_String("Landing on Planet Mercury in 2011"),New_String("Z_HwjzjqwN4"),ID_LINK_YOUTUBE, idtype);
        
        //if (planetNum==1 && nseq==0)     return MakeLink(5, New_String("Article - Venus"),"http://en.wikipedia.org/wiki/Planet_Venus")),ID_LINK_WIKIPEDIA, idtype);
        if (planetNum==1 && nseq==ANIMSEQ_LAND)     return MakeLink(6, New_String("Robotic Exploration of Venus"),New_String("oet63vzBvkg"),ID_LINK_YOUTUBE, idtype);
        if (planetNum==1 && nseq==ANIMSEQ_SURFACE)  return MakeLink(7, New_String("Venus Surface Tour"), New_String("ro-EG0ZCvKE"),ID_LINK_YOUTUBE, idtype);
        if (planetNum==1 && nseq==ANIMSEQ_SLINGSHOT)  return MakeLink(8, New_String("Mariner 10 - Venus Slingshot"), New_String("iypYPGE19ME"),ID_LINK_YOUTUBE, idtype);
        
        if (planetNum==2 && nseq==ANIMSEQ_SURFACE)    return MakeLink(9, New_String("Planet Earth seen from space"), New_String("P5_GlAOCHyE"), ID_LINK_YOUTUBE, idtype);
        if (planetNum==2 && nseq==0)                return MakeLink(10, New_String("Carl Sagan - Pale Blue Dot"), New_String("wupToqz1e2g"), ID_LINK_YOUTUBE, idtype);
        if (planetNum==2 && nseq==ANIMSEQ_SLINGSHOT)    return MakeLink(11, New_String("Views From Low Earth Orbit"), New_String("jlNEHKpQyio"), ID_LINK_YOUTUBE, idtype);
        if (planetNum==2 && nseq==ANIMSEQ_LAND)                return MakeLink(12, New_String("NASA Shuttle Endeavour Re-Entry Video"), New_String("hK1RxQKCmCE"), ID_LINK_YOUTUBE, idtype);
        
        //if (planetNum==3 && nseq==0)        return MakeLink(13, New_String("Article - Mars"), New_String("http://en.wikipedia.org/wiki/Planet_Mars"), ID_LINK_WIKIPEDIA, idtype);
        if (planetNum==3 && nseq==ANIMSEQ_LAND)        return MakeLink(14, New_String("Curiosity Rover Mission"), New_String("P4boyXQuUIw"), ID_LINK_YOUTUBE, idtype);
        if (planetNum==3 && nseq==ANIMSEQ_SURFACE)        return MakeLink(15, New_String("Panoramic Video of Mars Surface"), New_String("Cvq1CYazUzc"), ID_LINK_YOUTUBE, idtype);
        
        if (planetNum==4 && nseq==0)        return MakeLink(16, New_String("Jupiter the Giant Planet"), New_String("IxgSJJ0kyoQ"), ID_LINK_YOUTUBE, idtype);
        if (planetNum==4 && nseq==ANIMSEQ_LAND)        return MakeLink(17, New_String("Jupiter Impact By The Galileo Spacecraft"), New_String("Lrs-H0PUFFA"), ID_LINK_YOUTUBE, idtype);
        if (planetNum==4 && nseq==ANIMSEQ_SURFACE)        return MakeLink(18, New_String("Weather on Jupiter"), New_String("yjU_CJWzAd4"), ID_LINK_YOUTUBE, idtype);
        if (planetNum==4 && nseq==ANIMSEQ_SLINGSHOT)        return MakeLink(19, New_String("JUNO NASA Jupiter Exploration Spacecraft"), New_String("r8p7eyLOxdM"), ID_LINK_YOUTUBE, idtype);
        
        if (planetNum==5 && nseq==0)        return MakeLink(20, New_String("Saturn Overview"), New_String("5p6yUIOzqtc"), ID_LINK_YOUTUBE, idtype);
        if (planetNum==5 && nseq==ANIMSEQ_LAND)        return MakeLink(21, New_String("Saturn Exploration"), New_String("cL2QrfxrgBI"), ID_LINK_YOUTUBE, idtype);
        //if (planetNum==5 && nseq==ANIMSEQ_SURFACE)        return MakeLink(22, New_String("Article - Saturn"), New_String("http://en.wikipedia.org/wiki/Saturn"), ID_LINK_WIKIPEDIA, idtype);
        if (planetNum==5 && nseq==ANIMSEQ_SLINGSHOT)        return MakeLink(23, New_String("Saturn Rings Disturber"), New_String("rgre5C-7Af4"), ID_LINK_YOUTUBE, idtype);
        
        if (planetNum==6 && nseq==0)        return MakeLink(24, New_String("Space School - Uranus"), New_String("G7f1nuwRq_E"), ID_LINK_YOUTUBE, idtype);
        if (planetNum==6 && nseq==ANIMSEQ_SURFACE)        return MakeLink(25, New_String("The Voyager 2 Uranus encounter"), New_String("r46QdcnAYeU"), ID_LINK_WIKIPEDIA, idtype);
        if (planetNum==6 && nseq==ANIMSEQ_SLINGSHOT) return MakeLink(26, New_String("Voyager Flyby of Uranus"), New_String("DrKQaDupdWQ"), ID_LINK_YOUTUBE, idtype);
        
        if (planetNum==7 && nseq==0)        return MakeLink(27, New_String("Neptune from The Planets Suite"), New_String("PSJub1A1aIk"), ID_LINK_YOUTUBE, idtype);
        if (planetNum==7 && nseq==ANIMSEQ_SLINGSHOT) return MakeLink(28, New_String("Voyager Flyby of Neptune (1989)"), New_String("ynUihD47ajo"), ID_LINK_YOUTUBE, idtype);
        
        //if (planetNum==8 && nseq==0) return MakeLink(29, New_String("Pluto Article"), New_String("http://en.wikipedia.org/wiki/Pluto")),ID_LINK_WIKIPEDIA, idtype);
        if (planetNum==8 && nseq==ANIMSEQ_SURFACE) return MakeLink(30, New_String("Why Pluto is Not a Planet"), New_String("BKoRt-6pjAE"),ID_LINK_WIKIPEDIA, idtype);
        
        return false;
    }

    void initPosOrient() {
        rotation = 0.0;
        desiredHeading = 90.0;
        tilt = 0.0;
        desiredTilt = 0.0;
        trackball.reset();
        timeVar = 0;
    }
    
    float incAnim(float animstep) {
        return animstep;
    }
    
    void renderStars() {
        angle1 = float(timeVar) * FACTOR_RADIANS_DEGREES * 0.005;
        // Convert to Degrees
         for (int n =1; n<=NUMSTARS ; n++) {
           r = C_float(1.001 * (Random(rGen)));
           alScaleModel(star.modelId, r, r, 1.0);
        
        alDrawModelTranslateRotate(star.modelId,
                                   C_float(starpos[n].x),
                                   C_float(starpos[n].y),
                                   C_float(starpos[n].z),
                                   C_float(angle1),
                                   0.0, 1.0, 0.0,
                                   1, //rotatefirst
                                   1  //billboard
                                   );
        }
    }
    
    void onHit(int hitId) {
    }
    
    void updateVar(float deltaT, float* var , float* varTo, float mspeed) {
        if (*var < *varTo) {*var = *var + float(mspeed) * float(deltaT) * 0.001 * abs(var - varTo);}
        if (*var > *varTo) {*var = *var - float(mspeed) * float(deltaT) * 0.001 * abs(var - varTo);}
    } //end updateVar;
    
    void Update(float dt) {
        timeVar= timeVar + dt;
        updateVar(dt, &tilt, &desiredTilt, speed);
        updateVar(dt, &dist, &desiredDist, move_speed);
        updateVar(dt, &rotation, &desiredHeading, speed );
        printf(" tilt %.1f", tilt);
    }
    
    float angleStep = 45.0;
    int nr = NP-1;
    
    void renderPlanets() {
        alPushMatrix();
        for (int n=0; n<NP; n++) {
            nr = (NP-1) - n;
            alPushMatrix();
            if (nr == planetNo) {
                alTranslateRotate(0.0,0.0,0.0,C_float(timeVar * speed / 30.0f),0.0,1.0,0.0);

                if (planetNo == 3) { //if moon
                    alPushMatrix();
                    trackball.ApplyRotate();
                    alTranslateRotate(60.0,0.0, 0.0);
                    glScalef(40.0, 40.0, 40.0);
                    alDrawModel(planets[2].modelId);//earth
                    alPopMatrix();
                }
                
                if (planetNo == 6|| planetNo == 7) { //if io & europa also draw jupiter
                    alPushMatrix();
                    trackball.ApplyRotate();
                    alTranslateRotate(60.0,0.0, 0.0);
                    glScalef(50.0, 50.0, 50.0);
                    alDrawModel(planets[5].modelId);//jupiter
                    alPopMatrix();
                }
                
                if (planetNo == 8) { //saturn=5
                    alPushMatrix();
                    trackball.ApplyRotate();
                    alTranslateRotate(0.0,0.0,0.0,90.0,1.0,0.0,0.0);
                    alTranslateRotate(0.0,0.0,0.0,8.0,0.0,1.0,0.0);
                    alScaleModel(saturnRings.modelId, 1.0, 1.0, 1.0);
                    
                    alDrawModel(saturnRings.modelId);
                    alPopMatrix();
                }
                trackball.ApplyRotate();
                alDrawModel(planets[nr].modelId);
            }
            alPopMatrix();
        alTranslateRotate(0.0,0.0,0.0,angleStep,0.0,1.0,0.0);
        } //~loopy
        alPopMatrix();
    }
    
	void Render(float deltaT, int aX, int aY, int aZ) {
       
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (dist>DIST_NEAR) move_speed = MIN_ALLOWABLE_SPEED * 200.0;
        else move_speed = MIN_ALLOWABLE_SPEED * 100;
        
        Update(deltaT);
        processInput();
        
        angle1 = float(timeVar) * FACTOR_RADIANS_DEGREES  * 0.1; // Convert to Degrees
 
        alPushMatrix(); // save for cockpit
        
         alPushMatrix();
            alTranslateRotate(0.0,0.0,0.0,tilt-aY,0.0,0.0,1.0);
             trackball.ApplyRotate();
            renderStars();
         alPopMatrix();
        
        alTranslateRotate(0.0,0.0,-dist);
        alTranslateRotate(0.0,0.0,0.0,tilt-aY,0.0,0.0,1.0);
    //  alTranslateRotate(0.0,0.0,0.0,rotation,0.0,1.0,0.0);
        
        alPushMatrix();
        //prallax
        alTranslateRotate(0.0,0.01-aZ/600.0,0.0,0.0 ,0.0,0.0,0.0);
        renderPlanets();
        alPopMatrix();
        
        alPushMatrix();
         alTranslateRotate(0.0,0.0,0.0,angle1,0.0,1.0,0.0);
         alDrawModelTranslateRotate(voyager.modelId, 0.0,0.0,1.4, 180.0,  0.0,1.0,0.0);
        alPopMatrix();//undo rotation
        
        alPopMatrix();
        
        // draw cockpit
        
        if (dist >4.5) {
            alPushMatrix();
        //    alBillBoardBegin();
            glScalef(1.35, 1.0, 1.0);
            alDrawModelTranslateRotate(cockpit.modelId,0.0,0.0,-2.4);
        //    alBillBoardEnd();
            alPopMatrix();
        }
        
	}
    
    int dcursor = 0;
    
    int screen_y = 0;
    float youFrame[4];
    
	void processInput() {

        PEG::CMD* cmd = input.pull();
       
        if (cmd->command==CMD_SCREENSIZE) {
            trackball.onScreenSize(cmd->i1, cmd->i2);
            screenY = cmd->i2;
            screenX = cmd->i1;
        
            youFrame[0] = screenX * 0.05; youFrame[1] = screenY*0.18;
            youFrame[2] = screenX * 0.13;
            youFrame[3] = youFrame[2];
        
        }
        
       if (absolute(dist-float(DIST_CLOSER))<=1.5)
           trackball.radius = screenX;
       else
           trackball.radius = screenX/3.0;
        
        
       trackball.processTouches(cmd->command, cmd->i1,cmd->i2);
        //-------------------------------------------------------
        //----------------------------------  101 ----
        //--  Keycodes of arrow keys are         100  103 102
        //--  ----------------------------------------
        if (cmd->command == CMD_KEYDOWN) {
            
            if (cmd->i1 == 101) { // Fwd
                if (desiredDist == 0.0) {
                desiredDist = MIN_ALLOWABLE_DISTANCE;
                } else {
                desiredDist = 0.0;
                }
            }
            
            if (cmd->i1 == 103) { //back
                desiredDist = 20.0;
                desiredTilt = 0.0;
            }
        
            if (cmd->i1 == 100) {// left
                desiredTilt = desiredTilt -2.0;
            }
        
            if (cmd->i1 == 102) { //right
                desiredTilt = desiredTilt +2.0;
            }
        }
    
        if (cmd->command==CMD_TOUCH_START &&
            (absolute(dist-DIST_CLOSER)>=0.05)) {
            planetNo++;
            initPosOrient();
            if (planetNo>(NP-1)) planetNo=0;
            output.pushP(CMD_MSG, (void*)(char*) planetInf.at(planetNo).name.c_str(), 0);
            return;
        }
        
        if (cmd->command==CMD_PINCH_MOVE_OUT) {
                //user wants to zoom in
                if (absolute(dist-DIST_NEAR)<=1.5) {desiredDist = DIST_CLOSER; return;}
                if (absolute(dist-DIST_FAR)<=1.5) {desiredDist = DIST_NEAR; return;}
                output.pushP(CMD_MSG, (void*)(char*) planetInf.at(planetNo).name.c_str(), 0);
                
        } else if (cmd->command==CMD_PINCH_MOVE_IN) {
                //user want to move back
                if (absolute(dist-DIST_CLOSER)<=1.5) {desiredDist = DIST_NEAR; return;}
                //    if (abs(dist-DIST_NEAR)<=1.5) {desiredDist = DIST_FAR; return;}
            char info1[128];
            int idtype;
            nseq=ANIMSEQ_SURFACE;
            getSomeInfo(planetNo, &idtype, info1);
        }
        
 	}
	
    char link[256], text[64], idvideox[32];
    bool youReady;
    
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
    
    string planet_tex;
    
    short modelId = 0;
    
    void LoadModel(GameObject* gob, ResourceInf* res) {
        gob->modelId = modelId;
        alLoadModel((char*) res->alx.c_str(), (char*) res->tex.c_str(), modelId, res->scale);
        modelId++;
    }
    
    void Init(char* path) {
        rm.Init(path);
		strcpy(rm.resourcepath, path);
        string sphere = "sphere.alx";
        
        planetInf.push_back(ResourceInf("Mercury", "mercury4k.tga", sphere, 1.0));
        planetInf.push_back(ResourceInf("Venus", "venus4_rgb_cyl_www.tga", sphere, 1.0));
        planetInf.push_back(ResourceInf( "Earth", "earth4k.tga", "sphere.alx", 1.0));
        planetInf.push_back(ResourceInf( "Moon","2k_moon.tga", sphere, 1.0));
        planetInf.push_back(ResourceInf("Mars", "mars4k.tga", sphere, 1.0));
        planetInf.push_back(ResourceInf( "Jupiter","jupiter4k.tga", sphere, 1.0));
        planetInf.push_back(ResourceInf("IO (Moon of Jupiter)","io_rgb_cyl.tga", sphere, 1.0));
        planetInf.push_back(ResourceInf( "Europa (Moon of Jupiter)","europa2048.tga", sphere, 1.0));
        planetInf.push_back(ResourceInf("Saturn", "saturn.tga", sphere, 1.0));
        planetInf.push_back(ResourceInf("Uranus", "uranus.tga", sphere, 1.0));
        planetInf.push_back(ResourceInf("Neptune", "neptune.tga", sphere, 1.0));
        planetInf.push_back(ResourceInf("Pluto", "pluto.tga", sphere, 1.0));
        
        alAlphaTest(1);
        
        for (auto &res : planetInf) // access by reference to avoid copying
        {
            LoadModel(&planets[modelId], &res);
        }
       
        voyager.modelId = modelId;
        voyager.scale = 0.005;
        alLoadModel(New_String("voyager2.alx") , New_String("voyager2.tga") , int(voyager.modelId) , C_float(voyager.scale));
        panel.modelId = 13;
        alLoadModel(New_String("misc.alx")       , New_String("misc.tga")        , int(panel.modelId) , 1.0);
        cockpit.modelId = 14;
     
        alLoadModel(New_String("rect1.alx")       , New_String("cockpit_1.tga")        , int(cockpit.modelId) , 1.0);
        star.modelId = 15;
        alLoadModel(New_String("star.alx"), New_String("star.tga"), int(star.modelId), 0.3);
        arrowkeys.modelId = 16;
        alLoadModel(New_String("rect1.alx"), New_String("arrowkeys.tga"), int(arrowkeys.modelId), 0.2);
        saturnRings.modelId = 17;
        alLoadModel(New_String("satrings.alx"), New_String("satring2kwidth.tga"), int(saturnRings.modelId), 2.0);
        
        for (int n =1; n<=NUMSTARS ; n++) {
            r = 70.0 + (Random(rGen) * 100.0);
            theta =  (Random(rGen) * 44.0/ 7.0);
            phi =  (Random(rGen) * 44.0/ 7.0);
            
            starpos[n].x = r * Sin(theta) * Cos(phi);  //https://en.wikipedia.org/wiki/Spherical_coordinate_system
            starpos[n].y = r * Sin(theta) * Sin(phi);
            starpos[n].z = r * Cos(theta) ;
        }
        
        output.pushP(CMD_MSG, (void*)"Mercury\nIn Cockpit Mode - Touch & hold to Change Planet", 0);
    }
    

};
