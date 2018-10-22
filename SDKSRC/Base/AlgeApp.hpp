#ifndef NO_BOX2D
#include <Box2D/Box2D.h>
#endif
#ifndef NO_NATS
#include "..\..\..\AlgeSDK_m\m_Tools\CNetMsg\CNetMsg.h"
extern CNetMsg netmsg;
#endif

#define FIRST 1

#include "dimensions.h"

class AlgeApp {
public:
    #ifndef NO_BOX2D
	b2World* pWorld;
    #endif
	
	CTrackBall trackball;
	//CEasyBullet bullet;
	short renderSchemeVersion;//1=> Render processInput 2->UpdateCustom GOB's
	CAnimator can;
	CTimed animStepTimed;
	FontMap16x16 fonts;
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

    bool screenTouched = false;
    i2 wasTouchedi2;
    
	Camera aCamera;

	GameObject origin;

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
		
	}

	void Deinit() {}

	virtual i2 getBackgroundSize() {
		return i2(resolutionReported.x,resolutionReported.y);
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

	enum OrthoTypes {
		ORIGIN_IN_MIDDLE_OF_SCREEN = 0,
		ORIGIN_IN_TOP_LEFT_OF_SCREEN
	};

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

	GameObject* AddResource(GameObject* g, string name, float scale = 1.0) {
		ResourceInf res;
		res.Set(name, name + ".alx", name + ".tga", scale);
		LoadModel(g, &res);
		AddObject(g);
		g->pos.x = aCamera.windowWidth/2;
		g->pos.y = aCamera.windowHeight/2;
		g->originalScale = scale;
        g->JuiceType = 0;
        g->SetBounds(2.0 * rm.models[g->modelId]->boundx(), 2.0 * rm.models[g->modelId]->boundy(), name);
        g->UUID = name;
        g->m_touched = false;
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

	void ViewOrthoBegin(int width, int height, int depth = 1)												// Set Up An Ortho View
	{
		glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
		glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
		glPushMatrix();										// Store The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
#ifdef WIN32
#define glOrthof glOrtho
#endif
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



	void UpdateJuices(GameObject* it, int instanceNo, float deltaT) {
		static float juice_sine;
		static float juice_sine_angle;
		PosRotScale* jprs = (instanceNo < 1) ? reinterpret_cast<PosRotScale*>(it) : (it->getInstancePtr(instanceNo));
		switch (it->JuiceType) {

		case JuiceTypes::JUICE_ROTZ:
			jprs->rot.z += (deltaT * (jprs->JuiceSpeed));
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
			juice_sine_angle += (6.0 * deltaT * jprs->JuiceSpeed);
			glScalef(1. + 0.1 * sin(juice_sine_angle), 1. + 0.1 * sin(juice_sine_angle), 1. + 0.1 * sin(juice_sine_angle));
			break;
        case JuiceTypes::JUICE_PULSATEX:
             juice_sine_angle += (6.0 * deltaT * jprs->JuiceSpeed);
                glScalef(1. + 0.1 * sin(juice_sine_angle), 1. + 0.1 * sin(juice_sine_angle), 1. + 0.1 * sin(juice_sine_angle));
                jprs->rot.x = 50 * sin(juice_sine_angle);
             break;
		case JuiceTypes::JUICE_PULSATE_FULLY:
			//jprs->rot.z += (deltaT * jprs->JuiceSpeed);
			juice_sine_angle += (0.5 * deltaT * jprs->JuiceSpeed);
            glScalef(abs(sin(juice_sine_angle)), abs(sin(juice_sine_angle)), abs(sin(juice_sine_angle)));
			break;
        case JuiceTypes::JUICE_PULSATE_FULLY_AND_DIE:
                //jprs->rot.z += (deltaT * jprs->JuiceSpeed);
                juice_sine_angle += (0.5 * deltaT * jprs->JuiceSpeed);
                glScalef(abs(sin(juice_sine_angle)), abs(sin(juice_sine_angle)), abs(sin(juice_sine_angle)));
                jprs->scale -= deltaT * 10;
                if (jprs->scale<=0) jprs->scale = 0;
                break;
            case JuiceTypes::JUICE_CANCEL:
			jprs->rot.x = 0;
			jprs->rot.y = 0;
			jprs->rot.z = 0;
			break;
		}
	}

	void renderSingleObject(GameObject* it, float deltaT = 0.1f, int instanceNo = 0) {

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

		if (it->parent) {
			relPos.x += it->parent->pos.x;
			relPos.y += it->parent->pos.y;
			relPos.z += it->parent->pos.z;
			relRot.x += it->parent->rot.x;
			relRot.y += it->parent->rot.y;
			relRot.z += it->parent->rot.z;
		}

		if (!it->rotatefirst) glTranslatef(relPos.x, relPos.y, relPos.z);

		glRotatef(relRot.x, 1., 0., 0.);
		glRotatef(relRot.y, 0., 1., 0.);
		glRotatef(relRot.z, 0., 0., 1.);

		if (it->rotatefirst) glTranslatef(relPos.x, relPos.y, relPos.z);

		if (it->hidden) return;
		
		glScalef(it->scale, it->scale, it->scale);
		
        
		if (edit) {
			if (it->modelId >= 0)
			xyz.setSize(rm.models[it->modelId]->boundz() * 200.f);
			xyz.glDraw();//draw axis
		   //xyz.glDrawGroundAsGrid();
		}


		//it->Update(deltaT);
		UpdateCustom(it, instanceNo, deltaT);
			
		if (instanceNo>0 && it->applyTopLeftCorrectionWRTorigin) {//
			PosRotScale* i = it->getInstancePtr(instanceNo);
			i->pos.x = originX;
			i->pos.y = originY;
			float originalWidth = rm.models[it->modelId]->originalWidth();
			ammendTopLeft2D(&i->pos, i->scale, originalWidth);
		}
        
       
		if (it->billboard) alBillboardBegin();

		glScalef(it->scale, it->scale, it->scale);

		int m_j = it->JuiceType;//save  *1 >>>>>
		if ((edit && it == gobs[iSelectedObject])) it->JuiceType = JuiceTypes::JUICE_PULSATE;

		if (it != &aCamera) UpdateJuices(it, instanceNo, deltaT);
		
		
		if (it->m_touched && wireframe) glColor3f(0, 1, 0);
        
		if (edit) {
			if (it->modelId >= 0) alDrawModel(it->modelId, wireframe);
		}
		else {
			if (it->modelId >= 0) alDrawModel(it->modelId, wireframe);
		}
		if (it->billboard) alBillboardEnd();

		it->JuiceType = m_j;//restore *1 <<<<<

		//ShowMarkerinOrthoMode(10);
		glPopMatrix();
        glColor3f(1, 1, 1);
	}
	
    bool wasTouched() {
        if (screenTouched) {screenTouched=false; return true;}
        return false;
    }
    
    f2 screenToWorld(f2 point) {
        return f2(point.x / resolutionReported.x * getBackgroundSize().x, point.y / resolutionReported.y * getBackgroundSize().y);
    }
    
    bool doPicking2D(PosRotScale* it, f2 mouse) {
        f2 pt_in_world = screenToWorld(mouse);
        CRect obj = it->getOwnRect(it->UUID);
        bool ret = (CRect::PTInRect(pt_in_world.x, pt_in_world.y, obj, "doPicking2D"));
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
        
        if (cmd->command == CMD_TOUCH_START) {
            screenTouched = true;
            wasTouchedi2 = i2(cmd->i1, cmd->i2);
        }
      
        processInput(cmd, deltaT);
		
		PosRotScale* picked = 0;
        
        for (int i = 1; i < nGobs; i++) {
			GameObject* it = gobs[i];
			if (inhibitRender) { inhibitRender = false; continue; }
            
            PosRotScale origPRS;
			origPRS.CopyFrom(it);
			
			bool instanced = (it->prsInstances.size() > 0);
			int ins = 0;
			for (auto prs : it->prsInstances) {
				it->CopyFrom(&prs);
				if (!prs.hidden) { 
                    glColor3f(prs.color.x, prs.color.y, prs.color.z);
                    renderSingleObject(&(*it), deltaT, ins);
					glColor3f(1., 1., 1.);
					if (cmd->command == CMD_TOUCH_START) {
                       if (doPicking2D(&prs, f2(cmd->i1, cmd->i2))) {
							prs.m_touchedX = cmd->i1;
							prs.m_touchedY = cmd->i2;
							picked = &prs;
						}
					}
				}
				ins++;
				instanced = true;
			}

			if (!instanced && (it->prsInstances.size()==0) && !it->hidden) {
				glColor3f(it->color.x, it->color.y, it->color.z);
                renderSingleObject(&(*it), deltaT, -1);
				glColor3f(1., 1., 1.);
				if (cmd->command == CMD_TOUCH_START) {
                	if (doPicking2D(it, f2(cmd->i1, cmd->i2))) {
						it->m_touchedX = cmd->i1;
						it->m_touchedY = cmd->i2;
						picked = it;
					}
				}
			} 
			else {
				it->CopyFrom(&origPRS);
			}

			//netmsg.Post("Render::=" + it->Name());//Disabled due to perf concerns
		}

		if (picked) {
			picked->m_touched = true;
			picked = 0;
        }
        
		glPopMatrix();
        
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
		output.pushP(CMD_TITLE, msg, 0);
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
	char verbosity_lmh;
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
		static string fmt = "%.1f,%.1f,%.1f";
		static int mX, mY;
		static bool mousepass1 = true;

		if (p->command == CMD_REMOTE_COMMAND) {
			preProcessRemoteCommand((char*)p->param1);
		}

		if (p->command == CMD_KEYDOWN) { aCamera.KeyDownCcam(p->i1, deltaT*300.0f); }
		if (p->command == CMD_MOUSEWHEEL) {
			//aCamera.pos.x = aCamera.Position.x;//TBD:: merge pos and Position 
			//aCamera.pos.y = aCamera.Position.y;
			//aCamera.pos.z = aCamera.Position.y;

			aCamera.MoveForwards(p->i1 / -10.0);
		}

		///UNREAL STYLE MOUSE
		if (p->command == CMD_TOUCHMOVE || p->command == CMD_TOUCHMOVER) {
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


	void Render(float deltaT, int aX, int aY, int aZ) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!edit) {
			timeVar += deltaT;
			Update(deltaT);
			PhysicsUpdate(deltaT);
			for (int i = 1; i < nGobs; i++) {
				GameObject* it = gobs[i];
				it->Update(deltaT);
			}
		}
		//
#define DV /1.0
		if (aCamera.GetMode() == Camera::CAM_MODE_2D) {
			ViewOrthoBegin(aCamera.windowWidth, aCamera.windowHeight, 1000); // Must End
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

	void PhysicsUpdate(float deltaT) {
#ifndef NO_BOX2D
        if (pWorld) pWorld->Step(deltaT, velocityIterations, positionIterations);
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
		return AddFixturedBody(pWorld->CreateBody(&bodyDef));
	}

	b2Body* MakeStaticBody(PosRotScale* gob_as_prs,float width=1.0, float height=1.0) {
		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(gob_as_prs->pos.x, gob_as_prs->pos.y);
		return AddFixturedBody(pWorld->CreateBody(&bodyDef), width, height);
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


	//https://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
	inline bool isCircleIntersectingRect(float circleX, float circleY, float circleRadius, float rectX, float rectY, float rectWidth, float rectHeight)
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

	void SetTitle(char * name) {
		output.pushP(CMD_TITLE, $ name, 0);
	}
    //promotables - reusables
    
    bool isTouchAtLeft(GameObject* g) {
        bool l = (getMouseIntent(wasTouchedi2.x, wasTouchedi2.y, g->pos.x, g->pos.y).directionX=='L');
        return l;
    }
    void handy_moveToTouchLocation(GameObject* gob) {
    }
    
    //~ promotables
    
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
