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

class AlgeApp {
public:
	string wall_msg;
 #ifndef NO_BOX2D
	b2World* pWorld;
	b2World* world;
#endif

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
    
	CAxis xyz;

	short currentscene;

	int iUnassigned;
	int dcursor;
	int screen_y;
	PEG input, output;
	CResourceManager rm;
	aL10 AL10;

	bool inhibitRender = false;
	bool edit;
	bool wireframe = false;

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
		GameObject::windowSize.x = getBackgroundSize().x;
		GameObject::windowSize.y = getBackgroundSize().y;
		#ifndef NO_FONTLIB
		if (!(font = dtx_open_font_glyphmap("serif_s24.glyphmap"))) {
			fprintf(stderr, "failed to open font\n");
		} else
		dtx_use_font(font, 24);
		#endif
	}
		
	CModel* fontModel;
	char sz1[128];

#define NO_FONTLIB

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

	void Deinit() {}

	virtual i2 getBackgroundSize() {
		return i2(resolutionReported.x,resolutionReported.y);
	}

	virtual void onActionComplete(GameObject* obj) {
		
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

	void AddObject(GameObject *o, GameObject* parent = nullptr) {
		nGobs++;
		if (nGobs >= 128) nGobs = 127;
		gobs[nGobs - 1] = o;
		if (parent) parent->AddChild(o);
#ifndef NO_NATS
		netmsg.Post(string("AddObject::") + o->Name());
#endif
    }
	int orthoType;

	bool doObjectsIntersect(PosRotScale* prsCircle, PosRotScale* prsRect) {
		return isCircleIntersectingRect(prsCircle->pos.x, prsCircle->pos.y, prsCircle->m_width / 2, prsRect->pos.x, prsRect->pos.y, prsRect->m_width / 2, prsRect->m_height / 2);
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
		aCamera.windowWidth = getBackgroundSize().x;
		aCamera.windowHeight = getBackgroundSize().y;

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

	GameObject* AddResourceEx(GameObject* g, string name, int numInstances_max99, bool is_circle = false, float density = 1.0, float restitution = 0.1) {
		AddResource(g, name);
		AddMultiplePhysicalInstances(g, numInstances_max99, is_circle, density, restitution); //physics require half width/ half height
		return g;
	}


	GameObject* AddResource(GameObject* g, string name, float scale = 1.0) {
		ResourceInf res;
		res.Set(string(name), string(name + ".alx"), string(name + ".tga"), scale);
		g->modelId = LoadModel(g, &res);
		AddObject(g);
		g->pos.x = aCamera.windowWidth/2;
		g->pos.y = aCamera.windowHeight/2;
		g->originalScale = scale;
        g->JuiceType = 0;
        g->SetBounds(2.0 * rm.models[g->modelId]->boundx(), 2.0 * rm.models[g->modelId]->boundy(), name);
        g->UUID = name + ".G";

		return g;
	}
	

    GameObject* AddClusterResource(int n_duplicates, string tag, GameObject* array_of_objects, float size, int juiceType,bool useinstancing=false) {
        GameObject* g;
        if (!useinstancing) {
            for (int i = 0; i < n_duplicates; i++) {
                g = (array_of_objects+i);
                AddResource(g, tag, size);
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

	float juice_sine_angle;

	
	void UpdateJuices(GameObject* it, int instanceNo, float deltaT) {
		static float juice_sine;
		
		static float elapsed = 0;
		static int juice_frame[JuiceTypes::JUICES_END];

		elapsed += deltaT;
		static float timeNote;
		static bool timeNoted = false;
		static float x_pos_on_arrival = -1;

		PosRotScale* jprs = (instanceNo < 0) ? reinterpret_cast<PosRotScale*>(it) : (it->getInstancePtr(instanceNo));


		switch (jprs->JuiceType) {

		case JuiceTypes::JUICE_ROTZ:
			jprs->rot.z += (deltaT * (jprs->JuiceSpeed));
			break;
		case JuiceTypes::JUICE_ROTY:
			jprs->rot.y += (deltaT * (jprs->JuiceSpeed));
			break;
		case JuiceTypes::JUICE_DIE_TEMP:
		case JuiceTypes::JUICE_DIE:
			if (jprs->JuiceDuration>0) {
				jprs->rot.z += (deltaT * (jprs->JuiceSpeed));
				juice_sine_angle += 0.5f;
				glScalef(1. + 0.2 * sin(juice_sine_angle), 1. + 0.2 * sin(juice_sine_angle), 1. + 0.2 * sin(juice_sine_angle));
				jprs->JuiceDuration -= deltaT;
			}	else {
				if (jprs->JuiceType == JUICE_DIE) jprs->hidden = true;
				jprs->JuiceType = 0;
				jprs->rot.z = 0;
			}
			break;
		case JuiceTypes::JUICE_ROTXYZ:
			jprs->rot.x += (deltaT * (jprs->JuiceSpeed));
			jprs->rot.y += (deltaT * (jprs->JuiceSpeed));
			jprs->rot.z += (deltaT * (jprs->JuiceSpeed));
		break;
		case JuiceTypes::JUICE_ROTXYZ_PULSATE_FULLY:
			jprs->rot.x += (deltaT * (jprs->JuiceSpeed));
			jprs->rot.y += (deltaT * (jprs->JuiceSpeed));
			jprs->rot.z += (deltaT * (jprs->JuiceSpeed));
			juice_sine_angle += 0.02f;
			glScalef(abs(sin(juice_sine_angle)), abs(sin(juice_sine_angle)), abs(sin(juice_sine_angle)));		break;
		case JuiceTypes::JUICE_ROTZ_PULSATE:
			jprs->rot.z += (deltaT * (jprs->JuiceSpeed));
			juice_sine_angle += 0.2f;
			glScalef(1. + 0.02 * sin(juice_sine_angle), 1. + 0.02 * sin(juice_sine_angle), 1. + 0.02 * sin(juice_sine_angle));
			break;
		case JuiceTypes::JUICE_PULSATE:
			//jprs->rot.z += (deltaT * jprs->JuiceSpeed);
			juice_sine_angle += (0.01 * deltaT * jprs->JuiceSpeed);
			glScalef(1. + 0.02 * sin(juice_sine_angle), 1. + 0.02 * sin(juice_sine_angle), 1. + 0.02 * sin(juice_sine_angle));
			break;
		case JuiceTypes::JUICE_SCALE_IN:
			//jprs->rot.z += (deltaT * jprs->JuiceSpeed);
			juice_frame[JuiceTypes::JUICE_SCALE_IN]++;
			if (juice_sine_angle < 1.5708) juice_sine_angle += (0.5 * deltaT * jprs->JuiceSpeed);
			if (juice_frame[JuiceTypes::JUICE_SCALE_IN] == 1) juice_sine_angle = 0;
			glScalef(abs(sin(juice_sine_angle)), abs(sin(juice_sine_angle)), abs(sin(juice_sine_angle)));
			break;
		case JuiceTypes::JUICE_PULSATE_FULLY:
			//jprs->rot.z += (deltaT * jprs->JuiceSpeed);
			juice_sine_angle += (0.5 * deltaT * jprs->JuiceSpeed);
			glScalef(abs(sin(juice_sine_angle)), abs(sin(juice_sine_angle)), abs(sin(juice_sine_angle)));
			break;
		case JuiceTypes::JUICE_FLY_OUT:
			
			if (jprs->pos.x > -999) {
				if (x_pos_on_arrival==-1) x_pos_on_arrival = jprs->pos.x;
				jprs->pos.x -= (1000.0 * deltaT * jprs->JuiceSpeed);
			}
			else {
				//jprs->pos.x = x_pos_on_arrival;
				//jprs->JuiceType = 0;
				//x_pos_on_arrival = -1;
				//jprs->hidden = false;
			}
			break;
		case JuiceTypes::JUICE_CANCEL:
			jprs->rot.x = 0;
			jprs->rot.y = 0;
			jprs->rot.z = 0;
			break;
		}
	}

	void renderSingleObject(GameObject* iit, float deltaT = 0.1f, int instanceNo = -1) {

		PosRotScale* it = iit->getInstancePtr(instanceNo);

		static float wobble = 0.;
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
		UpdateCustom(iit, instanceNo, deltaT);
		
	
		
//	if (instanceNo>0 && it->applyTopLeftCorrectionWRTorigin) {//
//			PosRotScale* i = iit->getInstancePtr(instanceNo);
//			i->pos.x = originX;
//			i->pos.y = originY;
//			float originalWidth = rm.models[iit->modelId]->originalWidth();
//			ammendTopLeft2D(&i->pos, i->scale, originalWidth);
//		}
        
		if (iit->billboard) alBillboardBegin();

		glScalef(it->scale, it->scale, it->scale);

		int m_j = it->JuiceType;//save  *1 >>>>>
		if ((edit && it == gobs[iSelectedObject])) it->JuiceType = JuiceTypes::JUICE_PULSATE;

		if (iit != &aCamera) UpdateJuices(iit, instanceNo, deltaT);
		

		
		glColor3f(it->color.x, it->color.y, it->color.z);
		
		
		if (edit) {
			if (iit->modelId >= 0 && !inhibitRender) alDrawModel(iit->modelId, wireframe);
		}
		else {
			if (iit->modelId >= 0 && !inhibitRender) alDrawModel(iit->modelId, false);
		}
		if (iit->billboard) alBillboardEnd();

		it->JuiceType = m_j;//restore *1 <<<<<

		//ShowMarkerinOrthoMode(10);

		glPopMatrix();
		inhibitRender = false;
		glColor3f(1., 1., 1.);

	}
	        
    bool doPicking2D(PosRotScale* it, f2 mouse) {
        static char msg[128];
        f2 pt_in_world = f2(mouse.x / resolutionReported.x * getBackgroundSize().x, mouse.y / resolutionReported.y * getBackgroundSize().y);
        sprintf(msg, "%s@resolutionReported[%d,%d]",it->UUID.c_str(), resolutionReported.x, resolutionReported.y);
      //  SetTitle(msg);
        CRect obj = it->getOwnRect(it->UUID);
        bool ret = (CRect::PTInRect(pt_in_world.x, pt_in_world.y, obj, it->UUID));
        if (ret) {it->m_touchedX =pt_in_world.x; it->m_touchedY = pt_in_world.y;}
        return ret;
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

			int n = it->prsInstances.size();
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
			

	}

	bool onTouched(string name) {
		if (touched_bodies.size() > 0) {
			PosRotScale* bk = touched_bodies.back();
			if (bk->UUID.find(name) != string::npos) {
				return true;
			}
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
		rm.Init(path);
		Init(path);
#ifndef NO_NATS
		netmsg.Post(help);
#endif
		aCamera.custom_type = 0xCA;
		aCamera.windowWidth = getBackgroundSize().x;
		aCamera.windowHeight = getBackgroundSize().y;

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
		static char tval[128];
		if (r[0] == 'r') //report
		{
			if (r[1] == 'f') {// fps
				sprintf(tval, "fps(%d)", fps);
			//	netmsg.PostSub(string("Vars"), string(tval));
			}
		};

		if (r[0] == 'c') //CameMode
		{
			if (r[1] == 'l') aCamera.SetMode(Camera::CAM_MODE_LOOKAT);
			if (r[1] == 'c') aCamera.SetMode(Camera::CAM_MODE_CHASE);
			if (r[1] == 'f') aCamera.SetMode(Camera::CAM_MODE_FPS);
			if (r[1] == 'a') aCamera.SetMode(Camera::CAM_MODE_FLY);
			if (r[1] == '2') aCamera.SetMode(Camera::CAM_MODE_2D);


			CCamera* cc = ((CCamera*)(&aCamera));
			float val = 0.0f;
			if (r[2] >= '0' && r[2] <= '9') val = atof(r + 2);

			if (r[1] == 'x') cc->Position.x += val;
			if (r[1] == 'y') cc->Position.y += val;
			if (r[1] == 'z') cc->Position.z += val;
			if (r[1] == 'f') cc->MoveForwards(val);
			if (r[1] == 's') cc->StrafeRight(val);
		};

		if (r[0] == 's') //Select
		{
			int iSel = r[1] - 'a';//A=Select 0, B=Select 1, C=Select 2
			if (iSel >= 0 && iSel <= nGobs) iSelectedObject = iSel;
			selectedObject = gobs[iSelectedObject];
		};

		if (r[0] == 't') //transform
		{
			int iSel = r[1] - 'a';//A=Select 0, B=Select 1, C=Select 2
			if (iSel >= 0 && iSel <= nGobs) iSelectedObject = iSel;
			float val = atof(r + 2);

			if (r[1] == 's') //Scale
			{
				selectedObject->scale = val;
				//	selectedObject->Scale = val;
			};

			if (r[1] == 'x') //Transform Move x
			{
				selectedObject->pos.x += val;
			};

			if (r[1] == 'y') //Transform Move y
			{
				selectedObject->pos.y += val;
			};

			if (r[1] == 'z') //Transform Move z
			{
				selectedObject->pos.z += val;
			};

			if (r[1] == 'o' && r[2] == '?') //Transform Move z
			{
				char tval[128];
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
				char tval[128];
				sprintf(tval, "tranform(Camera:%s) pos(%.1f,%.1f,%.1f) rot(%.1f,%.1f,%.1f)",
					aCamera.Name().c_str(),
					aCamera.pos.x, aCamera.pos.y, aCamera.pos.z,
					aCamera.rot.x, aCamera.rot.y, aCamera.rot.z
				);
#ifndef NO_NATS
				netmsg.Post(string(tval));
#endif
			};

		};

		if (r[0] == 'n') //Select
		{
			string names = "gobs {";
			char c[64];
			for (int i = 0; i < nGobs; i++) {
				sprintf(c, "%c:%s\r\n", ('a' + i), gobs[i]->Name().c_str());
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

		if (r[0] == 'v') //Verbosity 
		{
			verbosity_lmh = r[1];
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

			aCamera.MoveForwards(p->i1 / -10.0);
		}

		///UNREAL STYLE MOUSE
		if (p->command == CMD_TOUCHMOVE || p->command == CMD_TOUCH_START || p->command == CMD_TOUCHMOVER) {
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
        
        if (p->command == CMD_SCREENSIZE) {
            resolutionReported.x = p->i1;
            resolutionReported.y = p->i2;
        }
        
		/////~UNREAL STYLE MOUSE
	}

	bool paused = false;

	char msg[128];
    
	void Render(float deltaT, int aX, int aY, int aZ) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (!edit) {
			timeVar += deltaT;
			if (!paused) {
				Update(deltaT);
				UpdatePhysics(deltaT);
				for (int i = 1; i < nGobs; i++) {
					GameObject* it = gobs[i];
					it->Update(deltaT);
					if (it->m_actionComplete) {
						it->m_actionComplete = false;
						onActionComplete(it);
					}
				}
			}
			else {
				bool break1 = true;
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

		}

		//glClearColor(0.0,0,0.,1);
		//	

		//processInput(p);
		renderObjects(deltaT, true);
		fps = 1.0 / deltaT;
		if (aCamera.GetMode() == Camera::CAM_MODE_2D) ViewOrthoEnd();
	}

	int LoadModel(GameObject* go, ResourceInf* res) {
		go->modelId = alLoadModel(res);
		go->resInf = res;
		go->custom_type = go->modelId;
#ifndef NO_NATS
		netmsg.Post(string("App::LoadModel:") + string(res->alx) + "," + string(res->tex));
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
		
		int32 velocityIterations = 6;
		int32 positionIterations = 2;
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
		output.pushP(CMD_SNDSET0+idx, $ name, 0);
		output.pushP(CMD_SNDPLAY0+idx, $ name, 0);
	}

	void SetTitle(const char * name) {
		output.pushP(CMD_TITLE, $ name, 0);
	}


};



class GameScene {
    
};

class GameObjectSnd {
public:
    GameObject obj;
    string tag;// filenames derived from tag
    
    void AddResourceWithSound(AlgeApp* app, string tag, float scale) {
        obj.JuiceType = 0;
        app->AddResource(&obj, tag, scale);
        app->PlaySnd(tag+".wav");
    }
};
class FontObject : public GameObject {
public:
    
};
