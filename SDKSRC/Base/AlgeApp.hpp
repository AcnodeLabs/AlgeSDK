
#define GLES_SILENCE_DEPRECATION
#include "Ada/AlgeSDK.ads.h"
#include "camera.h"

#ifndef NO_BOX2D
#include <Box2D/Box2D.h>
#endif
#ifndef NO_NATS
#include "../../Tools/CNetMsg/CNetMsg.h"
extern CNetMsg netmsg;
#endif

#define FIRST 1
#define P2S 100
#define S2P 0.01
#include "dimensions.h"
#include "drawtext.h"
#include <sstream>
#include <iomanip>

#include "XFunctions.hpp"


class AlgeApp {
public:
	bool desktop;
	string wall_msg;
 #ifndef NO_BOX2D
	b2World* pWorld;
	b2World* world;
#endif
	CFTFont text;
	FILE* f;
	vector<PosRotScale*> touched_bodies;

	CTrackBall trackball;
	//CEasyBullet bullet;
	short renderSchemeVersion;//1=> Render processInput 2->UpdateCustom GOB's
	CAnimator can;
	CTimed animStepTimed;
	FontMap10x10 fonts;
	int keyframe, nseq, screenX, screenY;
	f3 eye, eyerot, tgt, up;
	float timeVar, animstep, deltaT;
	float bz, width, height;
	GameObject* gobs[128]; short nGobs;
	GameObject* selectedObject;
    i2 resolutionReported;
    bool landscape ;
    
	CAxis xyz;

	
	short currentscene;

	int iUnassigned;
	int dcursor;
	int screen_y;
	PEG input, output;
	static CResourceManager rm;
	aL10 AL10;
	int backgroundModelId = 0;//used for dimming

	bool inhibitRender = false;
	bool edit;
	bool wireframe = false;
	float timeMultiplier = 1.0;

	Camera aCamera;

	GameObject origin;

#ifndef NO_FONTLIB
	struct dtx_font * font;
#endif

	AlgeApp() :
		iUnassigned(-1),
		timeVar(0.0) {
		edit = false;
		renderSchemeVersion = 2;
		width = 0;
		height = 0;
		dcursor = 0;
		screen_y = 0;
		keyframe = 1;
		animstep = 0.0;
		bz = 1.0;
		nseq = 0;
		screenX = iUnassigned;
		screenY = iUnassigned;
		selectedObject = nullptr;
		edit = false;
		iSelectedObject = 0;
		nGobs = 0;
		wireframe = false;
		iSelectedObject = 1;
		currentscene = 0;
		LoadScene(currentscene);
		counter = 0;
        landscape = true;
		desktop = false;//on desktop platforms sdk will set it to true 
		#ifndef NO_FONTLIB
		if (!(font = dtx_open_font_glyphmap("serif_s24.glyphmap"))) {
			fprintf(stderr, "failed to open font\n");
		} else
		dtx_use_font(font, 24);
		#endif
		f = fopen("AlgeApp.log", "w");
	}
		
	CModel* fontModel;
	char sz1[128];

#define NO_FONTLIB

	virtual void ScreenSize(int width, int height, int framebufferScale) {
		resolutionReported.x = width / framebufferScale;
		resolutionReported.y = height / framebufferScale;
		input.pushI(CMD_SCREENSIZE, width, height);
	}


	inline void alPrint(const char* text,  int size = 24 ) {
		#ifndef NO_FONTLIB
		if (size!=24) dtx_use_font(font, size);
		glPushMatrix();
		
		glRotatef(180, 1, 0, 0);
		dtx_string(text);
		glPopMatrix();
		#else
		glPushMatrix();
		glRotatef(180, 1, 0, 0);
		strcpy(sz1, text);
	//	fonts.print(sz1);
		glColor3f(0.5, 0.5, 0.5);
		glScalef(15,15,15);
	//	fontModel->glDraw();
		glPopMatrix();
		glColor3f(1., 1., 1.);
		#endif
	}

	void Deinit() {
		fclose(f);
	}
	
	
	void setTiming(float timeMultiplier) {
		this->timeMultiplier = timeMultiplier;
	}

	vector<bool> dimmed_states;

	//caution: No New objects should be added between the Dim and Undim call
	void Dim() {
		int i0 = 0;
		for (int i = 0; i < nGobs; i++) {
			dimmed_states.push_back(gobs[i]->hidden); 
			if (gobs[i]->modelId != backgroundModelId) gobs[i]->hidden = true;
			for (unsigned short j = 0; j < gobs[i]->prsInstances.size(); j++) {
				dimmed_states.push_back(gobs[i]->prsInstances[j].hidden);
				gobs[i]->prsInstances[j].hidden = true;
				i0++;
			}
			i0++;
		}
		paused = true;
	}

	void UnDim() {
		if (dimmed_states.size()<=0) return;
		int i0 = 0;
		for (int i = 0; i < nGobs; i++) {
			gobs[i]->hidden = dimmed_states[i0];
			for (unsigned short j = 0; j < gobs[i]->prsInstances.size(); j++) {
				gobs[i]->prsInstances[j].hidden = dimmed_states[i0];
				i0++;
			}
			i0++;
		}
		dimmed_states.clear();
		paused = false;
	}

	virtual void onSettingChanged(string setting, int value) {
		static char msg[128];
		static int _value = value;
		strcpy(msg, setting.c_str());
		output.pushP(CMD_SETTINGS_SCREEN, $ msg , (void*) &_value);
	}

	virtual i2 getBackgroundSize() {
		printf("Bg Size reported = %d ,%d", resolutionReported.x, resolutionReported.y);
       if (resolutionReported.x<1) resolutionReported.x = size_ipad_air.x;
       if (resolutionReported.y<1) resolutionReported.y = size_ipad_air.y;
		return i2(resolutionReported.x,resolutionReported.y);
	}

	virtual void onActionComplete(GameObject* obj) {
		
	}

    virtual void RenderGui() {
        
    }
    
	//Preconditions: Dont call before init
	//Assumption Scene is Saved from same arrangement of Gobs
	short LoadScene(short n) {
		/*char filename[16];
		 sprintf(filename, "")
		 for (int i=0; i<nGobs; i++) {
		 gobs[i]
		 }
		 */
		return 0;
	}

	GameObject* AddObject(GameObject *o, GameObject* parent = nullptr) {
		nGobs++;
		if (nGobs >= 128) nGobs = 127;
		gobs[nGobs - 1] = o;
		if (parent) parent->AddChild(o);
#ifndef NO_NATS
		netmsg.Post(string("AddObject::") + o->Name());
#endif
		o->UUID = "GOB#" + to_string(nGobs - 1);
		return o;
    }
	int orthoType;

	bool doObjectsIntersect(PosRotScale* prsCircle, PosRotScale* prsRect) {
		return isCircleIntersectingRect(prsCircle->pos.x, prsCircle->pos.y, prsCircle->m_width /2, prsRect->pos.x, prsRect->pos.y, prsRect->m_width/2 , prsRect->m_height/2 );
	}

	struct Polygon {
		vector<float> Points;
	};

	
	void PositionCamera(f3 position, f3 rotation) {
        SF3dVector p, r;
        p.x = position.x;
        p.y = position.y;
        p.z = position.z;
        r.x = rotation.x;
        r.y = rotation.y;
        r.z = rotation.z;
		aCamera.PosRot(p,r);
		aCamera.pos = position;
		aCamera.rot = rotation;
	}
    
	void AddDefaultCamera(int camMode = Camera::CAM_MODE_FPS, int _orthoType= ORIGIN_IN_MIDDLE_OF_SCREEN) {
		orthoType = _orthoType;
		static bool once = false;
		if (!once) {
			aCamera.SetSerializeTag("ACAMERA.GOB");
			aCamera.SetMode(camMode);
			AddObject(&aCamera);
			once = true;
		}
        SetCamera(camMode, _orthoType);
	}

    void CamReshape(i2 rect) {
        aCamera.windowWidth = rect.x;
        aCamera.windowHeight = rect.y;
        if (orthoType == ORIGIN_IN_MIDDLE_OF_SCREEN) {
            leftSide = -aCamera.windowWidth / 2.0;
            rightSide = aCamera.windowWidth / 2.0;
            bottomSide = -aCamera.windowHeight / 2.0;
            topSide = aCamera.windowHeight / 2.0;
            originX = 0;
            originY = 0;
        }
        if (orthoType == ORIGIN_IN_TOP_LEFT_OF_SCREEN) {
            leftSide = 0;
            rightSide = aCamera.windowWidth;
            bottomSide = aCamera.windowHeight;
            topSide = 0;
            originX = rightSide / 2;
            originY = bottomSide / 2;
        }
    }
    
    void SetCamera(int camMode = Camera::CAM_MODE_FPS, int _orthoType= ORIGIN_IN_MIDDLE_OF_SCREEN) {
        orthoType= _orthoType;
        aCamera.mode = camMode;
        CamReshape(getBackgroundSize());
    }

	
    GameObject* AddResourceEx(GameObject* g, string alx_tga_name, int numInstances_max99, bool is_circle = false, float scale = 1.0, float density = 1.0, float restitution = 0.1) {
        return AddResourceEx(g, alx_tga_name, alx_tga_name, numInstances_max99, is_circle, scale, density, restitution);
    }
    
	// .jpg has no alpha channel, for alpha channel support use tga pair
	GameObject* AddResourceEx(GameObject* g, string alx_name, string tga_name, int numInstances_max99, bool is_circle = false, float scale = 1.0, float density = 1.0, float restitution = 0.1) {
		AddResource(g, alx_name,tga_name, scale);
		AddMultiplePhysicalInstances(g, numInstances_max99, is_circle, density, restitution); //physics require half width/ half height
		return g;
	}

	GameObject* AddResource(GameObject* g, string tag, float scale = 1.0) {
		return AddResource(g, tag, tag, scale);
	}

	//Assume tag as name of alx(without extension) and tex is tga(without extension)/jpeg(with extension)
	GameObject* AddResource(GameObject* g, string alx_name, string tex_name, float scale = 1.0) {
		ResourceInf res;
		bool jpeg = (tex_name.find(".jp") != string::npos);
		res.Set(string(tex_name), string(alx_name + ".alx"), string(tex_name + (jpeg?"":".tga")), scale);
		g->modelId = LoadModel(g, &res);
		AddObject(g);
		g->pos.x = aCamera.windowWidth/2;
		g->pos.y = aCamera.windowHeight/2;
		g->originalScale = scale;
		g->JuiceType = 0;
        g->SetBounds(2.0 * rm.models[g->modelId]->boundx(), 2.0 * rm.models[g->modelId]->boundy(), tex_name);
        g->UUID = alx_name +"_"+ tex_name + ".G";
		XFunction_AutoScalingToFullScreen::GameObjectAdded(g, scale);
		g->m_touched = false;
		return g;
	}
	

    GameObject* AddClusterResource(int n_duplicates, string alxtag, string tgatag, GameObject* array_of_objects, float size, int juiceType,bool useinstancing=false) {
        GameObject* g;
        if (!useinstancing) {
            for (int i = 0; i < n_duplicates; i++) {
                g = (array_of_objects+i);
                AddResource(g, alxtag,tgatag, size);
                g->pos.x = randm() * rightSide;
                g->pos.y = randm() * bottomSide;
                g->applyTopLeftCorrectionWRTorigin = false;
                g->JuiceType = juiceType;
            } } else {
                /*  INSTANCING :S NOT FUNCTIONAL PROPERLY YET
                 AddResource(&star, "star", 20);
                 star.pos.x = originX;
                 star.pos.y = originY;
                 star.NextJuice();
                 
                 PosRotScale starPrs;
                 starPrs.JuiceType = 0;
                 starPrs.JuiceSpeed = 10;
                 for (int i = 0; i < 10; i++) {
                 starPrs.pos.x = randm()* rightSide;
                 starPrs.pos.y = randm()* bottomSide;
                 //starPrs.scale = star.scale;
                 star.AddInstance(starPrs);
                 printf("Star(%.1f,%.1f)", starPrs.pos.x, starPrs.pos.y);
                 }*/
            }
        return array_of_objects;
    }
    
	int leftSide, rightSide, topSide, bottomSide, originX, originY;

#ifdef WIN32
#define glOrthof glOrtho
#endif

	void ViewOrthoBegin(int width, int height, int depth = 1)												// Set Up An Ortho View
	{
		glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPushMatrix();										// Store The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
		glOrthof(leftSide, rightSide, bottomSide, topSide, -depth, depth);
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPushMatrix();										// Store The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
	}

	void ViewOrthoEnd()											// Set Up A Perspective View
	{
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPopMatrix();										// Restore The Old Projection Matrix
		glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
		glPopMatrix();										// Restore The Old Projection Matrix
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	}

	void UndoInheritedRotation(GameObject* it) {
		it->rot.x = -it->parent->rot.x;
		it->rot.y = -it->parent->rot.y;
		it->rot.z = -it->parent->rot.z;

		//https://stackoverflow.com/questions/22269435/how-to-iterate-through-a-list-of-objects-in-c
		for (auto const& child : it->children) {
			child->rot.x = -it->rot.x;
			child->rot.y = -it->rot.y;
			child->rot.z = -it->rot.z;
		}
	}

	void ammendTopLeft2D(f3* pos, float scaledTo, float widthOriginal) {
		float w = widthOriginal / scaledTo;
		pos->x += 0.5 * w * (1 - scaledTo);
		pos->y += 0.5 * w * (1 - scaledTo);
	}

	int juice_frame[JuiceTypes::JUICES_END];
	
	void UpdateJuices(GameObject* it, int instanceNo, float deltaT) {
	//	static float juice_sine;
		
		static float elapsed = 0;
		
		elapsed += deltaT;
	//	static float timeNote;
	//	static bool timeNoted = false;
		static float x_pos_on_arrival = -1;

		PosRotScale* jprs = (instanceNo < 0) ? reinterpret_cast<PosRotScale*>(it) : (it->getInstancePtr(instanceNo));

		float speedDt = (deltaT * (jprs->JuiceSpeed * 100));
		float angleDt = speedDt * 0.1;

		switch (jprs->JuiceType) {

		case JuiceTypes::JUICE_ROTZ:
			jprs->rot.z += speedDt;
			break;
		case JuiceTypes::JUICE_ROTY:
			jprs->rot.y += speedDt;
			break;
		case JuiceTypes::JUICE_DIE_TEMP:
		case JuiceTypes::JUICE_DIE:
			if (jprs->JuiceDuration>0) {
				jprs->rot.z += speedDt;
				jprs->juice_sine_angle += 0.01;/// (0.5f * jprs->JuiceSpeed);
				if (jprs->juice_sine_angle >= 6.28319) jprs->juice_sine_angle = 0.0; //rotate on 360 degree i.e 6.28319 radians
				float fsin = float(1.0 + 0.2 * sin(jprs->juice_sine_angle));
				glScalef(fsin, fsin, fsin);
				jprs->JuiceDuration -= deltaT;
			}	else {
				if (jprs->JuiceType == JUICE_DIE) {
					jprs->hidden = true;
					jprs->JuiceType = 0;
					jprs->rot.z = 0;
					jprs->juice_sine_angle = 0.;
				}
			}
			break;
		case JuiceTypes::JUICE_ROTXYZ:
			jprs->rot.x += speedDt;
			jprs->rot.y += speedDt;
			jprs->rot.z += speedDt;
		break;
		case JuiceTypes::JUICE_ROTXYZ_PULSATE_FULLY:
		{
			jprs->rot.x += speedDt;
			jprs->rot.y += speedDt;
			jprs->rot.z += speedDt;
			jprs->juice_sine_angle += angleDt / 2.;
			float sinj = sin(jprs->juice_sine_angle);
			glScalef(abs(sinj), abs(sinj), abs(sinj));
			break;
		}
		case JuiceTypes::JUICE_ROTZ_PULSATE:
		{
			jprs->rot.z += (deltaT * (jprs->JuiceSpeed * 100));
			jprs->juice_sine_angle += angleDt;
			float sinjx = 1. + 0.02 * sin(jprs->juice_sine_angle);
			glScalef(sinjx, sinjx, sinjx);
			break;
		}
		case JuiceTypes::JUICE_PULSATE:
		{
			jprs->juice_sine_angle += angleDt;
			//jprs->rot.z += (deltaT * jprs->JuiceSpeed);
			float sinjx = 1. + 0.02 * sin(jprs->juice_sine_angle);
			glScalef(sinjx, sinjx, sinjx);
			break;
		}
		
		//for this to work also set jprs->scale = 0 to start effect
		case JuiceTypes::JUICE_SCALE_IN:
		{
			if (jprs->scale < jprs->originalScale) {
				jprs->scale *= 1.02;
			} else {
				jprs->scale = jprs->originalScale;
			}
			break;
		}

		case JuiceTypes::JUICE_SCALE_OUT:
		{
			if (jprs->scale > 0) {
				jprs->scale /= 1.02;
			}
			else {
				jprs->scale = jprs->originalScale;
			}
			break;
		}

		case JuiceTypes::JUICE_PULSATE_FULLY:
		{
			//jprs->rot.z += (deltaT * jprs->JuiceSpeed);
			jprs->juice_sine_angle += angleDt / 2.;
			float sinj = sin(jprs->juice_sine_angle);
			glScalef(abs(sinj), abs(sinj), abs(sinj));
			break;
		}
		case JuiceTypes::JUICE_FLY_OUT:
			
			if (jprs->pos.x > -999) {
				if (x_pos_on_arrival==-1) x_pos_on_arrival = jprs->pos.x;
				jprs->pos.x -= speedDt * 50;
				if (jprs->pos.x < (-x_pos_on_arrival)) {
					jprs->pos.x = x_pos_on_arrival;
					jprs->JuiceType = JuiceTypes::JUICES_CANCEL;
					jprs->juice_sine_angle = 0;
					x_pos_on_arrival = -1;
				}
			}
			else {
				//jprs->pos.x = x_pos_on_arrival;
				//jprs->JuiceType = 0;
				//x_pos_on_arrival = -1;
				//jprs->hidden = false;
			}
			break;
		
		case JuiceTypes::JUICES_CANCEL:
			jprs->rot.x = 0;
			jprs->rot.y = 0;
			jprs->rot.z = 0;
			jprs->juice_sine_angle = 0;
			jprs->hidden = false;
			break;
		}
	}

	void renderSingleObject(GameObject* iit, float deltaT = 0.1f, int instanceNo = -1) {

		if (iit->hud) hudBegin(0, rightSide, bottomSide, 0);

		PosRotScale* it = iit->getInstancePtr(instanceNo);

	//	static float wobble = 0.;
		glPushMatrix();
		f3 relPos, relRot;
	
		relPos.x = it->pos.x;
		relPos.y = it->pos.y;
		relPos.z = it->pos.z;
		relRot.x = it->rot.x;
		relRot.y = it->rot.y;
		relRot.z = it->rot.z;

		//glScalef(it->scale, it->scale, it->scale);

		if (iit->parent) {
			relPos.x += iit->parent->pos.x;
			relPos.y += iit->parent->pos.y;
			relPos.z += iit->parent->pos.z;
			relRot.x += iit->parent->rot.x;
			relRot.y += iit->parent->rot.y;
			relRot.z += iit->parent->rot.z;
		}

		if (!iit->rotatefirst) glTranslatef(relPos.x, relPos.y, relPos.z);

		glRotatef(relRot.x, 1., 0., 0.);
		glRotatef(relRot.y, 0., 1., 0.);
		glRotatef(relRot.z, 0., 0., 1.);

		if (iit->rotatefirst) glTranslatef(relPos.x, relPos.y, relPos.z);

		if (it->hidden) return;
		
		glScalef(it->scale, it->scale, it->scale);
		
        
		if (edit) {
			if (iit->modelId >= 0)
			xyz.setSize(rm.models[iit->modelId]->boundz() * 200.f);
			xyz.glDraw();//draw axis
		   //xyz.glDrawGroundAsGrid();
		}


		//it->Update(deltaT);
		if (iit->modelId == backgroundModelId) {
			iit->color = (dimmed_states.size() > 0) ? f3(0.5, 0.5, 0.5) : f3(1, 1, 1);
		}
		
		glColor3f(it->color.x, it->color.y, it->color.z);
		if (iit != &aCamera) UpdateJuices(iit, instanceNo, deltaT);
		UpdateCustom(iit, instanceNo, deltaT);
		
//	if (instanceNo>0 && it->applyTopLeftCorrectionWRTorigin) {//
//			PosRotScale* i = iit->getInstancePtr(instanceNo);
//			i->pos.x = originX;
//			i->pos.y = originY;
//			float originalWidth = rm.models[iit->modelId]->originalWidth();
//			ammendTopLeft2D(&i->pos, i->scale, originalWidth);
//		}
        
		if (iit->billboard) alBillboardBegin();
        
        if (it->originalScale == XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN) {
			//	it->originalAspect = float(rightSide) / float(bottomSide);
			//  it->originalScale = rightSide;
            float sx = rightSide ;
            float sy = bottomSide / it->originalAspect;
         	if (orthoType == OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN) {
				it->pos.x = rightSide /2;
				it->pos.y = bottomSide /2;
			} //else no need to adjust pos
            glScalef(sx, sy, 1);
        } else
            glScalef(it->scale, it->scale, it->scale);
    

		int m_j = it->JuiceType;//save  *1 >>>>>
		if ((edit && it == gobs[iSelectedObject])) it->JuiceType = JuiceTypes::JUICE_PULSATE;

		
		if (edit) {
			xyz.glDraw();
		}
	
		if (iit->modelId >= 0 && !inhibitRender && !iit->hidden) alDrawModel(iit->modelId, wireframe);
		
		if (iit->hud) hudEnd();

		if (iit->billboard) alBillboardEnd();

		it->JuiceType = m_j;//restore *1 <<<<<

		//ShowMarkerinOrthoMode(10);

		glPopMatrix();
		inhibitRender = false;
		glColor3f(1., 1., 1.);

	}
	        
    bool doPicking2D(PosRotScale* it, f2 mouse) {
        //if (it->touchable==false) return false;
        TRAP(it, "bg");
        i2 fb = getBackgroundSize();
        i2 rr = resolutionReported;
        f2 pt_in_world = f2(mouse.x / rr.x * fb.x, mouse.y / rr.y * fb.y);
        // static char msg[128];
        //sprintf(msg, "%s@rr[%d,%d]",it->UUID.c_str(), resolutionReported.x, resolutionReported.y);
        //SetTitle(msg);
        CRect obj = it->getOwnRect(it->UUID);
		if (it->scale == XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN) {
			obj.Top = topSide;
			obj.Bottom = bottomSide;
			obj.Right = rightSide;
			obj.Left = leftSide;
		}
        bool ret = (CRect::PTInRect(pt_in_world.x, pt_in_world.y, obj, it->UUID));
        if (ret) {it->m_touchedX =pt_in_world.x; it->m_touchedY = pt_in_world.y;}
        return ret;
    }
    
    void TRAP(PosRotScale* prs, string name) {
        if (prs->UUID.find(name)!= string::npos) {
            printf("trap of %s", name.c_str());
        }
    }
    
	void renderObjects(float deltaT, bool btrackball) {
		counter++;
		selectedObject = gobs[iSelectedObject];
		glPushMatrix();
		aCamera.Update(deltaT, selectedObject);

		if (btrackball) trackball.ApplyRotate();

		vec3 gray(0.5, 0.5, 0.5);
		xyz.setStippleAndColor(2, 0xAEAE, gray, gray, gray);

		if (edit) {
			xyz.glDraw();
			xyz.glDrawGroundAsGrid();
		}
        
        PEG::CMD* cmd = input.pull();
        preProcessInput(cmd, deltaT);
        
		touched_bodies.clear();
        		
        int picked = -1;
        
        for (int i = 1; i < nGobs; i++) {
			GameObject* it = gobs[i];
			if (inhibitRender) { inhibitRender = false; continue; }
            
            PosRotScale origPRS;
			origPRS.pos.x = it->pos.x; origPRS.pos.y = it->pos.y; origPRS.pos.z = it->pos.z;
			origPRS.rot.x = it->rot.x; origPRS.rot.y = it->rot.y; origPRS.rot.z = it->rot.z;
			origPRS.scale = it->scale;
			origPRS.JuiceSpeed = it->JuiceSpeed;
			origPRS.JuiceType = it->JuiceType;
			origPRS.hidden = it->hidden;

			int n = (int)it->prsInstances.size();
			bool instanced = (n > 0);

			for (int ins = 0; ins < n; ins++) {
				
				PosRotScale* prs = it->getInstancePtr(ins);
#ifndef NO_BOX2D
				if (prs->physBodyPtr) {
					b2Body *b = (b2Body*)prs->physBodyPtr;
					prs->pos.x = b->GetPosition().x * P2S;
					prs->pos.y = b->GetPosition().y * P2S;
					prs->rot.z = b->GetAngle() * 57.2958f;
				}
#endif
				it->pos.x = prs->pos.x; it->pos.y = prs->pos.y; it->pos.z = prs->pos.z;
				it->rot.x = prs->rot.x; it->rot.y = prs->rot.y; it->rot.z = prs->rot.z;
				it->scale = prs->scale;
				it->hidden = prs->hidden;
				it->JuiceSpeed = prs->JuiceSpeed;
				it->JuiceType = prs->JuiceType;
				

				//Touched flag updated here for instances
				if (cmd->command == CMD_TOUCH_START) {
                    
                    if (!it->hidden)
						if (doPicking2D(prs, f2(cmd->i1, cmd->i2))) {
							touched_bodies.push_back(prs);
							picked = i; //will be overriden by last ordered object
							prs->m_touchedX = cmd->i1;
							prs->m_touchedY = cmd->i2;
						}
				}

				if (!prs->hidden) renderSingleObject(it, deltaT, ins);
			}

			if (!instanced && !it->hidden) {
#ifndef NO_BOX2D
				if (it->physBodyPtr) {
					b2Body *b = (b2Body*) it->physBodyPtr;
					it->pos.x = b->GetPosition().x *P2S;
					it->pos.y = b->GetPosition().y * P2S;
					it->rot.z = b->GetAngle() * 57.2958f;
				}
#endif
				renderSingleObject(&(*it), deltaT, -1);
				
				//Touched flag updated here for principal objects
				if (cmd->command == CMD_TOUCH_START) {
					if (!it->hidden)
						if (doPicking2D(it, f2(cmd->i1, cmd->i2))) {
							touched_bodies.push_back(it);
							//MessageBeep(MB_OK);
							picked = i; //will be overriden by last ordered object
							it->m_touched = true;
							it->m_touchedX = cmd->i1;
							it->m_touchedY = cmd->i2;
						}
				}
			} else {
				it->pos.x = origPRS.pos.x; it->pos.y = origPRS.pos.y; it->pos.z = origPRS.pos.z;
				it->rot.x = origPRS.rot.x; it->rot.y = origPRS.rot.y; it->rot.z = origPRS.rot.z;
				it->scale = origPRS.scale;
				it->hidden = origPRS.hidden;
				it->JuiceSpeed = origPRS.JuiceSpeed;
				it->JuiceType = origPRS.JuiceType;
			}

			//netmsg.Post("Render::=" + it->Name());//Disabled due to perf concerns
		}


		glPopMatrix();

		//allow for touch processing call onTouched(uuid) to determine if body is touched
		processInput(cmd, deltaT);
		
		bool postTouchData = true;
		if (postTouchData) {
			if (cmd->command == CMD_TOUCH_START) {
				td.x = cmd->i1; td.y = cmd->i2;
				ostringstream oss;
				oss << "[TOUCHED x:" << cmd->i1 << " y:" << cmd->i2;
#ifdef NATS_EXTERN
				netmsg.Post(oss.str());
#endif
			}
			if (cmd->command == CMD_TOUCH_END) {
				ostringstream oss;
				CRect r(td.y, cmd->i2, td.x, cmd->i2);
				oss << r.toStr();
#ifdef NATS_EXTERN
				netmsg.Post( "[" + oss.str() + "]]"); 
#endif
				td = i2( 0,0 );
			}
		}

	}
	i2 td;//used by postTouchData

	bool onTouched(string name) {
       
        if (touched_bodies.size() > 0) {
			PosRotScale* bk = touched_bodies.back();
			if (bk->UUID.find(name) != string::npos) {
				return true;
			}
            printf(",Touch:%s", name.c_str());
		}
		return false;
	}


    short iSelectedObject = 1;
    
    void ShowMarkerinOrthoMode(float size = 100.0) {
        aL10 al;
        al.alBegin(GL_TRIANGLES);                                // Drawing Using Triangles
        al.glVertex3f(0.0f, size, 0.0f);                    // Top
        al.glVertex3f(-size, -size, 0.0f);                    // Bottom Left
        al.glVertex3f(size, -size, 0.0f);                    // Bottom Right
        al.alEnd();                                            // Finished Drawing The Triangle
    }

	char PlatformCode;

	//Called by alge-main cpp
	void Init0(char* path, char platcode) {
		edit = false;
		PlatformCode = platcode;

#ifndef NO_NATS
		try {
	//		netmsg.Post(help);
		}
		catch (...) {
			printf("Could not Post netmsg");
		}
#endif
		aCamera.custom_type = 0xCA;
        
		aCamera.windowWidth = getBackgroundSize().x;
		aCamera.windowHeight = getBackgroundSize().y;
		rm.Init(path);
		Init(path);
		//Font v1 init
		fontModel =  rm.loadAlxModel((char*) "font.alx", AUTO, alReserveModelId(), 1);	// Fonts Loaded just like Model load but it doesnt involve managed resource 
		fonts.usetexof(fontModel);						// Associate texure of Loaded Model to FontMap
	}

	virtual void Init(char* path) {};
	virtual void UpdateCustom(GameObject*, int, float) {};
	virtual void Update(float delta_t) {};
	virtual void processInput(PEG::CMD* p, float deltaT) {};

	struct DirectionMagnitude {
		char directionX; //L R
		char directionY; //U D
		float magnitudeX;
		float magnitudeY;
	};

	DirectionMagnitude getMouseIntent(int newX, int newY, int oldX, int oldY) {
		static DirectionMagnitude dm;
		dm.directionX = ' ';
		dm.directionY = ' ';
		if (newX > oldX) dm.directionX = 'R'; else dm.directionX = 'L';
		if (newY > oldY) dm.directionY = 'D'; else dm.directionY = 'U';
		if (newX == oldX) dm.directionX = ' ';
		if (newY == oldY) dm.directionY = ' ';
		static char msg[3];
		msg[0] = dm.directionX;
		msg[1] = dm.directionY;
		msg[2] = 0;
	//	output.pushP(CMD_TITLE, msg, 0);
		dm.magnitudeX = (newX - oldX) / 5.;
		dm.magnitudeY = (newY - oldY) / 10.;
		if (dm.directionX == ' ') dm.magnitudeX = 0.f;
		if (dm.directionY == ' ') dm.magnitudeY = 0.f;
		return dm;
	}

	string help =
		string("[h]elp") +
		string("\r\n[s]elect\t[a..z] where A is firstObject e.g sa") +
		string("\r\n[l]ookat\t[a..z] e.g la") +
		string("\r\n[c]amera pos [x/y/z/f(orward/back)/r(strafe-rt/lft)]%f  e.g 'cx3.0'") +
		string("\r\n[c]amMode\t[t{lookat},c{chase},f{first person},a{aircraft}] e.g cp") +
		string("\r\n[t]ransform [c?] see transform of camera") +
		string("\r\n[n]ames i.e list game objects") +
		string("\r\n[t]ransform [o?] see transform of selected object") +
		string("\r\n[t]ransform [s]cale %f") +
		string("\r\n[t]ransform move [x/y/z]%f  e.g 'tx3.0'") +
		string("\r\n[t]ransform rotate [r/t/p]%f  e.g 'tp30.1'") +
		string("\r\n[w]ireframe [t/f] 'wf: wireframe false'") +
		string("\r\n[v]erbosity [l/m/h] 'vx: verbosity low/med/high' default is medium") +
		"";
	char verbosity_lmh = 'h';
	long counter = 0;
	int fps = 30;

	//THINK ON WHICH REMOTE COMMANDS ARE TO BE HANDLED AND WHY
	void preProcessRemoteCommand(char* r) {
		char tval[512];
		if (r[0] == 'r') //report
		{
			if (r[1] == 'f') {// fps
				sprintf(tval, "fps(%d)", fps);
				netmsg.Post(string(tval));
				//netmsg.PostSub(string("Vars"), string(tval));
			}
		};

		if (r[0] == 'c') //CameMode
		{
			if (r[1] == 'l') aCamera.SetMode(Camera::CAM_MODE_LOOKAT);
			if (r[1] == 'c') aCamera.SetMode(Camera::CAM_MODE_CHASE);
			if (r[1] == 'f') aCamera.SetMode(Camera::CAM_MODE_FPS);
			if (r[1] == 'a') aCamera.SetMode(Camera::CAM_MODE_FLY);
			if (r[1] == '2') aCamera.SetMode(Camera::CAM_MODE_2D);


			Camera* cc = ((Camera*)(&aCamera));
			float val = 0.0f;
			if (r[2] >= '0' && r[2] <= '9') val = atof(r + 2);

			if (r[1] == 'x') cc->Position.x += val;
			if (r[1] == 'y') cc->Position.y += val;
			if (r[1] == 'z') cc->Position.z += val;
			if (r[1] == 'f') cc->MoveForwards(val);
			if (r[1] == 's') cc->StrafeRight(val);
		};

		if (r[0] == 'd') //dump
		{
			if (r[1] == 'v') //vertices
			{
				//char vertices[256];
				for (int i = 0; i < rm.models[selectedObject->modelId]->n_vertices; i+=3) {
					//sprintf_s(vertices, 128, "v[%d]={%.2f,%.2f,%.2f}", rm.models[selectedObject->modelId]->vertex_array[i], rm.models[selectedObject->modelId]->vertex_array[i + 1], rm.models[selectedObject->modelId]->vertex_array[i + 2]);
			//		netmsg.Post("string(vertices)");
					if (i > 64) {
			//			netmsg.Post(" Dump Stopped beyond i>64");
						break;
					}
				}
			}
		};

		if (r[0] == 's') //Select
		{
			int iSel = r[1] - 'a';//A=Select 0, B=Select 1, C=Select 2
			if (iSel != '?' - 'a') {
				if (iSel >= 0 && iSel <= nGobs) {
					iSelectedObject = iSel;
					selectedObject = gobs[iSelectedObject];
				}
			}
			string name = selectedObject->Name();
#ifndef NO_NATS
			netmsg.Post("Selected " +name);
#endif
		};

		if (r[0] == 't') //transform
		{
			//int iSel = r[1] - 'a';//A=Select 0, B=Select 1, C=Select 2
			//if (iSel >= 0 && iSel <= nGobs) iSelectedObject = iSel;
			float val = atof(r + 2);
			bool cam = (iSelectedObject==0);

			if (r[1] == 's') //Scale
			{
				selectedObject->scale = val;
				//	selectedObject->Scale = val;
			};

			if (r[1] == 'x') //Transform Move x
			{
				selectedObject->pos.x += val;
				if (cam) aCamera.Position.x = selectedObject->pos.x;
			};

			if (r[1] == 'y') //Transform Move y
			{
				selectedObject->pos.y += val;
				if (cam) aCamera.Position.y = selectedObject->pos.y;
			};

			if (r[1] == 'z') //Transform Move z
			{
				selectedObject->pos.z += val;
				if (cam) aCamera.Position.z = selectedObject->pos.z;
			};

			if (r[1] == 'r') //Transform Rot r
			{
				selectedObject->rot.x += val;
				if (cam) aCamera.RotatedX = selectedObject->rot.x;
			};

			if (r[1] == 't') //Transform Rot t
			{
				selectedObject->rot.y += val;
				if (cam) aCamera.RotatedY = selectedObject->rot.y;
			};

			if (r[1] == 'p') //Transform Rot p
			{
				selectedObject->rot.z += val;
				if (cam) aCamera.RotatedZ = selectedObject->rot.z;
			};

			if (r[1] == 'o' && r[2] == '?') //Transform Move z
			{
				sprintf(tval, "tranform(Object:%s) pos(%.1f,%.1f,%.1f) rot(%.1f,%.1f,%.1f) scale(%.1f)",
					selectedObject->Name().c_str(),
					selectedObject->pos.x, selectedObject->pos.y, selectedObject->pos.z,
					selectedObject->rot.x, selectedObject->rot.y, selectedObject->rot.z,
					selectedObject->scale
				);
#ifndef NO_NATS
               netmsg.Post(string(tval));
#endif
			};
			if (r[1] == 'c' && r[2] == '?') //Transform Move z
			{
				static char tval[200];
				f3 campos = aCamera.getPos();
				f3 camrot = aCamera.getRot();
				sprintf(tval, "PosRotScale({%.1f,%.1f,%.1f},{%.1f,%.1f,%.1f})",
					campos.x, campos.y, campos.z,
					camrot.x, camrot.x, camrot.z
				);
#ifndef NO_NATS
				netmsg.Post(string(tval));
#endif
			};

		};

		if (r[0] == 'n') //Select
		{
			string names = "gobs {";
			char c[128];
			for (int i = 1; i < nGobs; i++) {
				sprintf(c, "%c%c:%s i/%d {%d vets}\r\n", gobs[i]->hidden?'-':'+',('a' + i), gobs[i]->Name().c_str(), (int)gobs[i]->prsInstances.size(), gobs[i]->modelId>=0?rm.models[gobs[i]->modelId]->n_vertices:0);
				names += string(c);
			}
			names += "}";
#ifndef NO_NATS
			netmsg.Post(names);
#endif
		};

		//convertToPEG(p, r);//Ctransform incoming remote command to PEG::Cmd
		if (r[0] == '?' || r[0] == 'h') //Select
		{
#ifndef NO_NATS
			netmsg.Post(help);
#endif
		};

		if (r[0] == 'w') wireframe = (r[1] == 't');
		if (r[0] == 'e') edit = (r[1] == 't');

		if (r[0] == 'v') //Verbosity 
		{
			verbosity_lmh = r[1];
		};

		if (r[0] == 'p' || r[1] == 'h') //hidden status Property Hidden
		{
			static ostringstream oss;
			oss.clear();
			oss << "slected object " << gobs[iSelectedObject]->UUID	<< " is "<< ((gobs[iSelectedObject]->hidden==true)?"":"NOT") << " hidden";
#ifndef NO_NATS
			netmsg.Post(oss.str());
#endif
		};

	}

	void preProcessInput(PEG::CMD* p = NULL, float deltaT = 0.0f) {
		/*
		stringstream ss;
		int c = input.cmd[input.indx_r - 1].command;
		ss << "c";
		ss << "0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << c;

		ss << "r";
		ss << input.indx_r;

		ss << "w";
		ss << input.indx_w;

		if (c) wall_msg = ss.str();
		*/
		static string fmt = "%.1f,%.1f,%.1f";
		static int mX, mY;
		static bool mousepass1 = true;

		if (p->command == CMD_REMOTE_COMMAND) {
			preProcessRemoteCommand((char*)p->param1);
		}

		if (p->command == CMD_KEYDOWN) { aCamera.KeyDownCcam(p->i1, deltaT*300.0f); paused = false; }
		if (p->command == CMD_MOUSEWHEEL) {
			//aCamera.pos.x = aCamera.Position.x;//TBD:: merge pos and Position 
			//aCamera.pos.y = aCamera.Position.y;
			//aCamera.pos.z = aCamera.Position.y;

			aCamera.MoveForwards(p->i1 / -1.0);
		}

		///UNREAL STYLE MOUSE
		if (p->command == CMD_TOUCHMOVE || p->command == CMD_TOUCHMOVER) {
			if (p->command != CMD_TOUCH_START)
				if (mousepass1) { mX = p->i1; mY = p->i2; mousepass1 = false; return; }
			DirectionMagnitude dm = getMouseIntent(p->i1, p->i2, mX, mY);
			if (dm.directionY != ' ') {
				if (p->command == CMD_TOUCHMOVE) aCamera.MoveForwards(dm.magnitudeY);//Forwards back
				if (p->command == CMD_TOUCHMOVER) aCamera.RotateX(-dm.magnitudeY);//Ooper Neechay Dekhna
			}
			if (dm.directionX != ' ') aCamera.RotateY(-dm.magnitudeX);//left right
			mX = p->i1;	mY = p->i2;	mousepass1 = false;
		}

		if (p->command == CMD_TOUCH_END) {
			mousepass1 = true;
		}
        
        //Screen Size may have changed
        if (p->command == CMD_SCREENSIZE) {
          
        }
        
		/////~UNREAL STYLE MOUSE
	}

	bool paused = false;

	char msg[128];
    
	class RunningAverage {
		unsigned long int counter = 0;
		long double sum = 0;
		long double r;
	public:
		void Put(float x) {
			counter++;
			sum += x;
			r = sum / counter;
		}
		float Get() {
			return float(r);
		}
	};

	RunningAverage tAvg;

	void Render(float dT, int aX, int aY, int aZ) {

		tAvg.Put(dT);
		float deltaT = tAvg.Get() * timeMultiplier;  //Always use running average of incoming dt
		
	//	((GameObject*)&aCamera)->Update(deltaT);

		if (aCamera.GetMode() == Camera::CAM_MODE_LOOKAT) {
		//	int t = aZ;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		timeVar += deltaT;

		if (!edit) {
			
			if (!paused) {
				Update(deltaT);
				UpdatePhysics(deltaT);
				
				for (int i = 0; i < nGobs; i++) {
					GameObject* it = gobs[i];
#ifndef NO_LOGS
				//	fprintf(f, "\n%f:G#%d pos=%s", timeVar,i, it->pos.str("%f,%f,%f").c_str());
#endif
					it->Update(deltaT);
					if (i == 0) {
						aCamera.Update(deltaT, &aCamera);
					//	aCamera.OnPosRotChanged();
						
					}
					if (it->m_actionComplete) {
						it->m_actionComplete = false;
						onActionComplete(it);
					}
				}
			}
			else {
			//	bool break1 = true;
			}
		}
		//
#define DV /1.0
		if (aCamera.GetMode() == Camera::CAM_MODE_2D) {
			ViewOrthoBegin(aCamera.windowWidth, aCamera.windowHeight, 1100); // Must End
		}

		if (aCamera.GetMode() == Camera::CAM_MODE_FPS) {
			glLoadIdentity();
			glRotatef(-aCamera.RotatedX, 1.0, 0.0, 0.0);
			glRotatef(-aCamera.RotatedY, 0.0, 1.0, 0.0);
			glRotatef(-aCamera.RotatedZ, 0.0, 0.0, 1.0);
			glTranslatef(-aCamera.Position.x, -aCamera.Position.y, -aCamera.Position.z);
		}

		if (aCamera.GetMode() == Camera::CAM_MODE_LOOKAT) {
			glLoadIdentity();
			f3 cp = aCamera.getPos();
			aluLookAt(cp.x, cp.y, cp.z, selectedObject->pos.x, selectedObject->pos.y, selectedObject->pos.z, 0., 1., 0.);
			aCamera.pos = cp;
		}

		//glClearColor(0.0,0,0.,1);
		//	
		//processInput(p);
		
		renderObjects(deltaT, true);

		fps = 1.0 / deltaT;
		if (aCamera.GetMode() == Camera::CAM_MODE_2D) ViewOrthoEnd();
	//	if (!edit) aCamera.PosRot({ aCamera.pos.x, aCamera.pos.y, aCamera.pos.z }, { aCamera.rot.x, aCamera.rot.y, aCamera.rot.z });
        
	}

	int LoadModel(GameObject* go, ResourceInf* res) {
		go->modelId = alLoadModel(res);
		go->resInf = res;
		go->custom_type = go->modelId;
#ifndef NO_NATS
		netmsg.Post(string("App::LoadModel:") + string(res->alx) + "," + string(res->tex));
#endif

#ifndef NO_LOGS
		//fprintf(f,"\n%s,modelID=%d,n_vertices=%d",(string("App::LoadModel:") + string(res->alx) + "," + string(res->tex)).c_str(), go->modelId, rm.models[0]->n_vertices);
#endif
		return go->modelId;
	}

	////////////////////////////PHYSICS 2D Box2D
	//Phys2D phys;
		
	int velocityIterations = 6;
	int positionIterations = 2;

	void InitPhysics() {
#ifndef NO_BOX2D
		world = new b2World(b2Vec2(0, 10));
#endif
	}

	void UpdatePhysics(float deltaT) {
#ifndef NO_BOX2D
        if (world) world->Step(deltaT, velocityIterations, positionIterations);
		if (world) world->ClearForces();
#endif
	}

#ifndef NO_BOX2D
	b2Body* AddFixturedBody(b2Body* body, float width=1.0, float height = 1.0) {
		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(width, height);
		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;
		// Override the default friction.
		fixtureDef.friction = 0.3f;
		// Add the shape to the body.
		body->CreateFixture(&fixtureDef);
		return body;
	}

	b2Body* MakeDynamicBody(PosRotScale* gob_as_prs) {
		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(gob_as_prs->pos.x, gob_as_prs->pos.y);
		return AddFixturedBody(world->CreateBody(&bodyDef));
	}

	b2Body* MakeStaticBody(PosRotScale* gob_as_prs,float width=1.0, float height=1.0) {
		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(gob_as_prs->pos.x, gob_as_prs->pos.y);
		return AddFixturedBody(world->CreateBody(&bodyDef), width, height);
	}
#endif

	int metersX, pixX;
	int metersY, pixY;
	
	void PhysicsGroundWork(float widthMeters, int _pixX, int _pixY) {
		
		metersX = width;
		metersY = metersX / _pixX * _pixY;
		pixX = _pixX;
		pixY = _pixY;
#ifndef NO_BOX2D
		// Define the gravity vector.
		b2Vec2 gravity;// (0.0f, -10.0f);
		
		int dirY = -1;
		
	//	int32 velocityIterations = 6;
	//	int32 positionIterations = 2;
		f2 ownerSize;

		gravity.x = 0.0; gravity.y = 100.0 * dirY;
		pWorld = new b2World(gravity);
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);
		// Call the body factory which allocates memory for the ground body
		// from a pool and creates the ground box shape (also from a pool).
		// The body is also added to the world.
		b2Body* groundBody = pWorld->CreateBody(&groundBodyDef);
		// Define the ground box shape.
		b2PolygonShape groundBox;
		// The extents are the half-widths of the box.
		groundBox.SetAsBox(widthMeters, 10.0f);
		// Add the ground fixture to the ground body.
		groundBody->CreateFixture(&groundBox, 0.0f);
#endif
	}
	/////////////
#ifndef NO_BOX2D
	b2PolygonShape polygon;
	b2CircleShape circle;
	b2FixtureDef bxFixDef, blFixDef;
	b2BodyDef bodyDefBall;
	b2BodyDef bodyDefBox;
#endif
	
	void AddMultiplePhysicalInstances(GameObject* o, int count, bool is_circle = false, float density = 1.0, float restitution = 0.1) {
#ifndef NO_BOX2D
		#define max_generate_obj 99

		char szuuid[64];
		static PosRotScale px[max_generate_obj];
		static b2Body* px_body[max_generate_obj];

		i2 obj_size = i2(o->m_width, o->m_height).half();
		
		polygon.SetAsBox(obj_size.x * S2P, obj_size.y * S2P); //20 is size from alx
		circle.m_radius = obj_size.x * S2P;//20 is size from alx

		bxFixDef.shape = &polygon;
		blFixDef.shape = &circle;

		bxFixDef.density = density;
		blFixDef.density = density;

		bxFixDef.restitution = restitution;
		blFixDef.restitution = restitution;

		bodyDefBall.type = b2_dynamicBody;
		bodyDefBox.type = b2_dynamicBody;

		if (count > max_generate_obj) {
			output.pushP(CMD_TOAST, $ "numInstances exceeds limit", 0);
			return;
		}

		for (int i = 0; i < count; i++) {

			float rndScale = 1.0;// 0.5 + randm();
			float box_hh = obj_size.x  * rndScale;
			float box_hw = obj_size.y * rndScale;

			polygon.SetAsBox(box_hh * S2P, box_hw * S2P);
			bodyDefBox.position.Set(randm() * 7, randm() * 5);
            
			px_body[i] = (world) ? world->CreateBody(&bodyDefBox) : 0;
			b2FixtureDef* fixDef = (is_circle?&blFixDef:&bxFixDef);
			if (world) {
				px_body[i]->CreateFixture(fixDef);
				px[i].physBodyPtr = px_body[i];
			}
			px[i].scale = rndScale;//?
			px[i].pos.x = bodyDefBox.position.x * P2S;
			px[i].pos.y = bodyDefBox.position.y * P2S;
			px[i].m_height = 2 * box_hh;
			px[i].m_width = 2 * box_hw; // == ball_rad = 20 in this case

			//bm[i].userId = i;
			sprintf(szuuid, "%s#%d", o->UUID.c_str(), i);
			px[i].UUID = string(szuuid);
			o->AddInstance(px[i]);

		}
#endif
	}

#ifndef NO_BOX2D
	b2BodyDef bodyDefWalls;
	b2PolygonShape shp;
#endif

	void PhysAddGroundWithWalls() {
#ifndef NO_BOX2D

		bxFixDef.shape = &shp;
		// create ground
		shp.SetAsBox(rightSide * S2P / 2, 1 * S2P);
		bodyDefWalls.position.Set(rightSide * S2P / 2, bottomSide * S2P );
		if (world) world->CreateBody(&bodyDefWalls)->CreateFixture(&bxFixDef);

		shp.SetAsBox(1 * S2P, bottomSide*S2P);
		// left wall
		bodyDefWalls.position.Set(0, bottomSide * S2P / 2);
		if (world) world->CreateBody(&bodyDefWalls)->CreateFixture(&bxFixDef);
		// right wall
		bodyDefWalls.position.Set(rightSide * S2P, bottomSide * S2P / 2);
		if (world) world->CreateBody(&bodyDefWalls)->CreateFixture(&bxFixDef);
#endif
	}


	//https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
	bool isCircleIntersectingRect(float circleX, float circleY, float circleRadius, float rectX, float rectY, float rectWidth, float rectHeight)
	{
		f2 circleDistance;
		circleDistance.x = abs(circleX - rectX);
		circleDistance.y = abs(circleY - rectY);

		if (circleDistance.x > (rectWidth / 2 + circleRadius)) { return false; }
		if (circleDistance.y > (rectHeight / 2 + circleRadius)) { return false; }

		if (circleDistance.x <= (rectWidth / 2)) { return true; }
		if (circleDistance.y <= (rectHeight / 2)) { return true; }

		float cornerDistance_sq = (circleDistance.x - rectWidth / 2)*(circleDistance.x - rectWidth / 2)
			+ (circleDistance.y - rectHeight / 2) * (circleDistance.y - rectHeight / 2);

		return (cornerDistance_sq <= (circleRadius*circleRadius));
	}

	string sndName;

	void PlaySnd(string name, int idx = 0) {
		sndName = name;
		PlaySndEx((char*)(sndName.c_str()), idx);
	}

	void PlaySndEx(char * name, int idx = 0) {
		return;
        output.pushP(CMD_SNDSET0+idx, $ name, 0);
		output.pushP(CMD_SNDPLAY0+idx, $ name, 0);
	}

	void SetTitle(const char * name) {
		static string n;
		n = string(name);
		output.pushP(CMD_TITLE, $ n.c_str(), 0);
	}


};

CResourceManager AlgeApp::rm;

class GameScene {
    
};

class GameObjectSnd {
public:
    GameObject obj;
    string tag;// filenames derived from tag
    
    void AddResourceWithSound(AlgeApp* app, string alx_tag, string tga_tag, float scale = 1.0) {
        obj.JuiceType = 0;
        app->AddResource(&obj, alx_tag, tga_tag, scale);
        app->PlaySnd(tag+".wav");
    }
};
class FontObject : public GameObject {
public:
    
};


class DPad : public GameObject {
	
public:
	bool enabled;
    AlgeApp* that;
    
	string m_tag;
	DPad() {};

	DPad(string filetag) {
		m_tag = filetag;
		enabled = true;
	}

	GameObject* LoadIn(AlgeApp* thiz) {
        that = thiz;
		if (m_tag.size() == 0) m_tag = "dpad";
		GameObject* d = thiz->AddResource(this, m_tag, m_tag);
		pos.x = thiz->rightSide - 64;
		pos.y = thiz->bottomSide / 2;
		JuiceType = 0;// JuiceTypes::JUICE_SCALE_IN;
		JuiceSpeed *= 2;
		color = f3(0.9, 0.9, 0.9);
		center = pos;
		hud = true;
		return d;
	}

	f3 center;

	virtual void Update(float deltaT) {

		if (wasTouched()) {
	//		int t = UDLRC();
		}
		else {
       
			rot.x = 0;
			rot.y = 0;
			rot.z = 0;
		}
	}

	//udlr = updownleftrt
	char UDLRC() {
		f2 p = posTouched();
		f2 pt = f2(p.x - center.x, center.y - p.y);
		int row, col = 0;
		int a = this->m_width / 6;
		if (pt.x <= -a) col = 0; else
			if (pt.x > -a && pt.x < a) col = 1; else
				if (pt.x >= a) col = 2;

		if (pt.y >= a) row = 0; else
			if (pt.y > -a && pt.y < a) row = 1; else
				if (pt.y <= a) row = 2;

		char ret = ' ';
		if (col == 0) {
			if (row == 1) ret = 'L';
		}
		if (col == 1) {
			if (row == 0) ret = 'U';
			if (row == 1) ret = 'C';
			if (row == 2) ret = 'D';
		}
		if (col == 2) {
			if (row == 1) ret = 'R';
		}

	//	Swivel(ret);

		return ret;
	}

	void Swivel(char dir) {
		rot.z = 0;
		if (dir == 'U') rot.x = -20;
		if (dir == 'D') rot.x = +20;
		if (dir == 'L') rot.y = -20;
		if (dir == 'R') rot.y = +20;
		if (dir == 'C' || dir == ' ') {
			rot.x = 0; rot.y = 0;
		}
	}


};

class DBtn : public GameObject {
	string m_tag;

public:

	DBtn() {};

	DBtn(string filetag) {
		m_tag = filetag;
	}

	GameObject* LoadIn(AlgeApp* thiz, string m_tag, float scale = 1.0) {
		if (m_tag.size() == 0) m_tag = "pointer";
		GameObject* d = thiz->AddResource(this, m_tag, m_tag, scale);
		pos.x = thiz->rightSide - 64;
		pos.y = thiz->topSide + 64;
		JuiceType = JuiceTypes::JUICE_SCALE_IN;
		JuiceSpeed *= 2;
		color = f3(0.9, 0.9, 0.9);
		hud = true;
		return d;
	}
	
	void SetDirection(int angle) {
		rot.z = angle;//??
	//	rot.x = degrees;//??
	//	rot.y = degrees;//??
	}
	
};


// specs:
// i1=='p' AND i2= 'U' : Pad Up //'D' : Pad Dn // 'L' : Pad Up //'R' : Pad Dn 
// i1=='b' AND i2 = buttonID
class MyGamePad {
public:
	enum EventTypes { PAD = 'p', BTN = 'b' };
	enum EventCodes { PAD_UP = 'U', PAD_DN = 'D', PAD_LT = 'L', PAD_RT = 'R' , BTN_DELTA=0, BTN_SQUARE=3, BTN_X=2, BTN_CIRCLE=1 };

	static char get_i1(unsigned int buttonID, int axisID, float value, void* context) {
		static char i1 = '?';
		if (buttonID == -1) {//axis
			i1 = EventTypes::PAD;
		}
		else {//button
			i1 = EventTypes::BTN;
		}
		return i1;
	}
	
	static char get_i2(unsigned int buttonID, int axisID, float value, void* context) {
		static char i2 = '?';
		if (buttonID == -1) {//axis
			if (axisID == 5 && value == -1.0) i2 = PAD_UP;
			if (axisID == 5 && value == 1.0) i2 = PAD_DN;
			if (axisID == 4 && value == 1.0) i2 = PAD_RT;
			if (axisID == 4 && value == -1.0) i2 = PAD_LT;
		}
		else {//button
			i2 = buttonID;
		}
		return i2;
	}
};

//added 04 Feb 2014
class SettingScreen : public GameObject {
public:

	enum EventNames {
		Exiting = 1
	};

	DBtn p1, p2, p3;
	DBtn ico;

	string m_tag;
	float x[3] = {0,0,0};
	DBtn *p;

	SettingScreen() {};
	int ix[3] = { 0,0,0 };

	void RepositionObject(int rightSide, int bottomSide) {
		int w = ico.getOwnRect().Right - ico.getOwnRect().Left;
		int h = ico.getOwnRect().Bottom - ico.getOwnRect().Top;
		ico.pos.x = rightSide - w;
		ico.pos.y = h;
	}
	int getIdFromX(int x) {
		if (abs(x - 1056) < 50) return 2;
		if (abs(x - 818) < 50) return 1;
		if (abs(x - 581) < 50) return 0;
		return -1;
	}
	/*
	int getSettingOfOrientation(int posx) {
		ix[1] = getIdFromX(posx);
		return ix[1] == 0 ? 0 : 1;
	}

	int getSettingOfDifficulty(int posx) {
		ix[2] = getIdFromX(posx); 
		return ix[2];
	}

	int getSettingOfControlMode(int posx) {
		ix[0] = getIdFromX(posx); 
		return ix[0];
	}
	*/
	SettingScreen(string filetag) {
		m_tag = filetag;
		valueControlMethod = 1;// Touch
		valueDifficulty = 0;//Easy
		valueOrientation = 0;//landscape
	}
	f3 center;
	
	void RollDown() { 
		p->JuiceType = 0;
		if (p == &p2) p = &p3;
		if (p == &p1) p = &p2;
		p->JuiceType = JUICE_PULSATE_FULLY;
	}
	void RollUp() {
		p->JuiceType = 0;
		if (p == &p2) p = &p1;
		if (p == &p3) p = &p2;
		p->JuiceType = JUICE_PULSATE_FULLY;
	}

	int Which() {
		int which = 0;
		if (p1.JuiceType == JuiceTypes::JUICE_PULSATE_FULLY) which = 1;
		if (p2.JuiceType == JuiceTypes::JUICE_PULSATE_FULLY) which = 2;
		if (p3.JuiceType == JuiceTypes::JUICE_PULSATE_FULLY) which = 3;
		return which;
	}

	void NotifyApp(int ptrId, int posx) {
		
		switch (ptrId) {
		case 0:
			valueControlMethod = getIdFromX(posx);
			break;
		case 1:
			valueOrientation = getIdFromX(posx);
			break;
		case 2:
			valueDifficulty = getIdFromX(posx);
			break;
		default:
			break;
		}
	}



	void RollLeft() {
		int ip = Which() - 1;
		ix[ip]--;
		if (ix[ip] < 0) ix[ip] = 0;
		p->pos = f3(anchors_v1[ip][ix[ip]].x, anchors_v1[ip][ix[ip]].y, 0.0);
		NotifyApp(ip, p->pos.x);
	}

	void RollRight() {
		int ip = Which() - 1;
		ix[ip]++;
		if (ix[ip] > 2) ix[ip] = 2;
		p->pos = f3(anchors_v1[ip][ix[ip]].x, anchors_v1[ip][ix[ip]].y, 0.0);
		NotifyApp(ip, p->pos.x);
	}

	void processInput(int command, i2 loc) {
		if (p->hidden) return;

		if (command == CMD_GAMEPAD_EVENT) {
			processGamePadEvent(loc.x,loc.y);
		}
		if (command == CMD_TOUCH_START) {
			
			string ret = processTouchEvent(loc);
            printf("%s",ret.c_str());
		}
	}

	void processGamePadEvent(char type, char code) {
		if (type==MyGamePad::EventTypes::PAD) {
			if (code == MyGamePad::EventCodes::PAD_UP) RollUp();
			if (code == MyGamePad::EventCodes::PAD_DN) RollDown();
			if (code == MyGamePad::EventCodes::PAD_LT) RollLeft();
			if (code == MyGamePad::EventCodes::PAD_RT) RollRight();
		}
	}
		

	string processTouchEvent(i2 point) {
		ostringstream oss;

		if (m_thiz->onTouched("settings_icon")) {
			//	SetVisible(true,backgr);
				oss << "settings_icon;";
				m_thiz->input.pushI(CMD_SETTINGS_SCREEN, 1, 1);
				return oss.str();
		}
		
		
		CRect btnExit;
		btnExit.Right = (0.1875 * m_thiz->rightSide);
		btnExit.Top = (0.8 * m_thiz->bottomSide);
		
		if (point.x < btnExit.Right && point.y> btnExit.Top) {
			this->JuiceType = JuiceTypes::JUICE_FLY_OUT;
			p1.Hide();
			p2.Hide();
			p3.Hide();
			ico.Show();
			valueControlMethod = getIdFromX(p1.pos.x);
			valueOrientation = getIdFromX(p2.pos.x);
			valueDifficulty = getIdFromX(p3.pos.x);
			lastPointerX[0] = p1.pos.x;
			lastPointerX[1] = p2.pos.x;
			lastPointerX[2] = p3.pos.x;
			oss << "settings_exit[ controlmode=" << valueControlMethod << ", orientation=" << valueOrientation << ", difficulty=" << valueDifficulty << "];";
			m_thiz->UnDim();
			m_thiz->onSettingChanged("controlmode", valueControlMethod);
			m_thiz->onSettingChanged("orientation", valueOrientation);
			m_thiz->onSettingChanged("difficulty", valueDifficulty);
			return oss.str();
		}
				
		//find the nearest anchor
		int Yoffset = (anchors_v1[1][0].y - anchors_v1[0][0].y) / 2;
		i2 b(point.x,point.y + Yoffset);//Buttons are Yoffset above pointers
		
		bool hit(false);
		int im =0, jm=0, dmin = 1E3;
		for (int i=0; i<3; i++) for (int j = 0; j < 3; j++) {
			i2 a = anchors_v1[i][j];
			//float pt2[2];
			//pt2[0] = float(a.x);
			//pt2[1] = float(a.y);
			float dist = sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));// sqrt(1234); CAnimator::Dist(pt1, pt2);
			oss << dist << "/" << dmin << ";";
			if (dist < dmin) {
				dmin = dist; im = i; jm = j; hit = true;
			}
		}
	//	oss << "im:" << im << " jm:" << jm << " hit:" << hit;
		//move to achor and select it
		f3 pt(anchors_v1[im][jm]);
	//	oss << " pt:"<< pt.str("%.1f,%.1f");
		p->JuiceType = 0;
		if (p1.pos.y == pt.y) { p1.pos = pt; p = &p1; NotifyApp(0, p1.pos.x);}
		if (p2.pos.y == pt.y) { p2.pos = pt; p = &p2; NotifyApp(1, p2.pos.x);}
		if (p3.pos.y == pt.y) { p3.pos = pt; p = &p3; NotifyApp(2, p3.pos.x);}
		p->JuiceType = JuiceTypes::JUICE_PULSATE_FULLY;



		return oss.str();
	}

//	#include "../../Apps/SettingsScreen.Assets/Data/settings.anchors"
	//anchorpoints for settings.alx & settings.tga screen
	i2 anch_size = i2(1024,512);
	i2 anchors_v1[3][3] = {
        {i2(465,185),i2(655,185),i2(845,185)},
        {i2(465,315),i2(655,315),i2(845,315)},
        {i2(465,460),i2(655,460),i2(845,460)},
	};//row col

	short valueOrientation = 0, valueDifficulty = 0, valueControlMethod = 1;
	int lastPointerX[3];

	void setXY(int col) {
		p1.pos.x = anchors_v1[0][col].x;
		p2.pos.x = anchors_v1[1][col].x;
		p3.pos.x = anchors_v1[2][col].x;
		p1.pos.y = anchors_v1[0][col].y;// thiz->bottomSide * 2 / 6;
		p2.pos.y = anchors_v1[1][col].y;// thiz->bottomSide * 4 / 6;
		p3.pos.y = anchors_v1[2][col].y;// thiz->bottomSide * 5 / 6;
	}

	void resize2Dmodel(CModel* m, i2 now) {
		for (int i = 0; i < m->n_vertices * 3; i += 3) {
			f3 vert = f3(m->vertex_array[i] / float(anch_size.x) * float(now.x), m->vertex_array[i + 1] / float(anch_size.y) * float(now.y), m->vertex_array[i + 2]);
			m->vertex_array[i] =  vert.x ;
			m->vertex_array[i + 1] = vert.y ;
		}
	}
	AlgeApp* m_thiz;
	GameObject* backgr;
	bool m_visible;

	void SetVisible(bool showit, GameObject* background = nullptr) {
		m_visible = showit;
		if (showit) m_thiz->Dim(); else m_thiz->UnDim();

		if (showit == true) {

			//ico.Hide();
			setXY(0);
			//	GameObject::Show();

			p1.JuiceType = JuiceTypes::JUICE_PULSATE_FULLY;
			p1.JuiceSpeed /= 2; p2.JuiceSpeed /= 2; p3.JuiceSpeed /= 2;
			p2.JuiceType = 0;
			p3.JuiceType = 0;
			this->scale = 0; this->JuiceType = JuiceTypes::JUICE_SCALE_IN;
			this->juice_sine_angle = 0; //resetPrev Juice Effect 
			p1.scale = 0.8;
			p2.scale = p1.scale;
			p3.scale = p1.scale;
			p1.Show();
			p2.Show();
			p3.Show();

			p1.pos.x = lastPointerX[0];
			p2.pos.x = lastPointerX[1];
			p3.pos.x = lastPointerX[2];
			
			Show();
		} 	else {
			ico.Show();
			this->JuiceType = 0;
			HideFor(&ico);
			p1.Hide();
			p2.Hide();
			p3.Hide();
		}
		
	}

	GameObject* LoadIn(AlgeApp* thiz, string tagSettings, string tagPointer, string tagIcon, GameObject* background = nullptr, bool showit = true) {
		m_thiz = thiz;
		i2 now = thiz->getBackgroundSize();
		//rescale anchordata as per our new screensize
		for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
			float xo = anchors_v1[i][j].x;
			float yo = anchors_v1[i][j].y;
			float xn = (xo / anch_size.x)*now.x;
			float yn = (yo / anch_size.y)*now.y;
			anchors_v1[i][j].x = int(xn);
			anchors_v1[i][j].y = int(yn);
		}

		lastPointerX[0] = anchors_v1[0][valueControlMethod].x;
		lastPointerX[1] = anchors_v1[1][valueOrientation].x;
		lastPointerX[2] = anchors_v1[2][valueDifficulty].x;
		
		if (m_tag.size() == 0) m_tag = tagSettings;
        GameObject* d;
        d = thiz->AddResource(this, m_tag, XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        
	////	resize2Dmodel(thiz->rm.models[d->modelId], thiz->getBackgroundSize());
        SetVisible(showit, background);//hidden
        
		center = pos;
		//hud = true;
		p1.LoadIn(thiz, tagPointer);
		p2.LoadIn(thiz, tagPointer);
		p3.LoadIn(thiz, tagPointer);
		p = &p1;
		ico.LoadIn(thiz, tagIcon, 0.6);
		ico.JuiceType = JuiceTypes::JUICE_ROTZ;
		ico.JuiceSpeed /= 3;
		
		return d;
	}

};


class StartScreen {
public:
	GameObject bg;
	GameObject start;

	GameObject ratings;

	void LoadIn(AlgeApp* thiz, string bgd = "bg") {
        
		thiz->AddResource(&bg, bgd, XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN);
        
		int middleX = thiz->rightSide / 2;

		with thiz->AddResource(&ratings, "ratings", 0.7);
		 _.pos.x = middleX;
		 _.pos.y = 0.1 * thiz->bottomSide;
		_with
     
        with thiz->AddResource(&start, "start");
		_.pos.x = middleX;
        _.pos.y =  0.9 * thiz->bottomSide;
         _.JuiceType = JuiceTypes::JUICE_PULSATE;
        _with

	}
	
	void SetVisible(bool visible = true) {
		if (visible) {
			ratings.Show();
			start.Show();
			bg.Show(); 
		} else {
			ratings.Hide();
			start.Hide();
			bg.Hide();
		}
	}
	

};


class MockUpOne {
public:
    GameObject score, titl;
    
    SettingScreen settings;
    StartScreen startScreen;
    DPad dPad;
    AlgeApp* app;
    
	///
	//A mock is a set of Screen and associated interactions
	//e.g a standard setting screen which shows
	// a start screen with a title and ratings image and a Start button and a settings icon on top right
	// setting screen that shows up and has user clickable regions defined by anchors

    void LoadMock(AlgeApp* thiz, string titleTag, string tagSettings, string tagPointer, string tagIcon, string backgrnd) {
        app = thiz;
        
        startScreen.LoadIn(thiz,backgrnd);
        
        with thiz->AddResource(&titl, titleTag.c_str(), 1.2);
        _.JuiceType = JuiceTypes::JUICE_PULSATE;
        _.AddInstance(f2(_.pos.x - 3, _.pos.y - 3))->color = f3(0.7, 0.7, 0.7); //grey shadow
        _.AddInstance(f2(_.pos.xy()));
        _with
      
        score.pos.y = 0.05 * thiz->bottomSide;
        score.pos.x = 0.85 * thiz->rightSide;
        thiz->AddObject(&score);
        
        with dPad.LoadIn(thiz);
		dPad.JuiceType = 0;// JuiceTypes::JUICE_SCALE_IN;
        _.color = f3( 1,1,1);
        _with
        
        settings.LoadIn(thiz,  tagSettings,  tagPointer,  tagIcon, &startScreen.bg, false);
    }
    
    void processInput(PEG::CMD* cmd, float deltaT) {
       
        if (!app) return;
		if (cmd->command == CMD_SCREENSIZE) {
			RepositionObjects(app->rightSide, app->bottomSide);
			settings.RepositionObject(app->rightSide, app->bottomSide);
		}
        
        if (cmd->command == CMD_SETTINGS_SCREEN) {
            if (cmd->i1 == 1) {
                ShowTitle(false);
                startScreen.SetVisible(false);
                //startScreen.bg.Show();              
            }
            if (cmd->i1 == 2) {
                ShowTitle(true);
                startScreen.SetVisible(true);
                //startScreen.bg.Show();
            }
        }
        
        if (cmd->command == CMD_TOUCH_START)
            if (app->onTouched("settings_icon")) {
                settings.SetVisible(true);
            }
        
        if (cmd->command == CMD_GAMEPAD_EVENT && cmd->i1 == MyGamePad::EventTypes::PAD) {
            if (cmd->i2 == MyGamePad::EventCodes::PAD_LT || cmd->i2 == MyGamePad::EventCodes::PAD_RT) {
                startScreen.bg.m_touchedX = (cmd->i2 == MyGamePad::EventCodes::PAD_LT? app->leftSide:app->rightSide);
            }
            if (cmd->i2 == MyGamePad::EventCodes::PAD_UP || cmd->i2 == MyGamePad::EventCodes::PAD_DN) {
                startScreen.bg.m_touchedY = (cmd->i2 == MyGamePad::EventCodes::PAD_UP ? app->topSide : app->bottomSide);
            }
        }
        
        if (settings.m_visible) settings.processInput(cmd->command, i2(cmd->i1, cmd->i2));
       
    }
    
    void ShowTitle(bool visible = true) {
        if (visible) {
            titl.Show();
            titl.getInstancePtr(1)->hidden = false;
        }
        else {
            titl.Hide();
            titl.getInstancePtr(1)->hidden = true;
        }
    }
    
    void RepositionObjects(int rightSide, int bottomSide) {
		const int shadowSize = 3;
		for (int i = 0; i < 2; i++) {
			titl.getInstancePtr(i)->pos.x = rightSide / 2.0 + i * shadowSize;
			titl.getInstancePtr(i)->pos.y = bottomSide / 2.0 + i * shadowSize;
		}
        startScreen.ratings.pos.y = 0.1 * bottomSide;
        startScreen.start.pos.x = 0.5 * rightSide;
		startScreen.ratings.pos.x = startScreen.start.pos.x;
        startScreen.start.pos.y = 0.9 * bottomSide;
        score.pos.y = 0.05 * bottomSide;
        score.pos.x = 0.85 * rightSide;
        dPad.pos.x = rightSide - 64;
        dPad.pos.y = bottomSide / 2;
    }
};

