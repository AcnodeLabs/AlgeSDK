// AlgeSDK.ads.h // The high level interface to AlgeSDK in conformance with Ada Specifications
#ifndef ALGESDK_ADS_H
#define ALGESDK_ADS_H
#include <math.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <sstream>
#include <list>

#ifdef __is_target_os
#ifndef MACOSX
//#define NO_BOX2D
#endif
#endif


#ifndef NO_BOX2D //Box2D is to be built by premake which does not support ios, Box2D is excluded from ios from time bieng
#include <Box2D/Box2D.h>
#endif

using namespace std;
#define GLfloat float
#include "../CCommands.h"
#include "../../Classlets/com/acnodelabs/funkit/CAnimator.hpp"
#include "../../Base/camera.h"



const float FACTOR_RADIANS_DEGREES = 57.295779513082;
void inline aluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez,
                      GLfloat centerx, GLfloat centery, GLfloat centerz,
                      GLfloat upx, GLfloat upy, GLfloat upz);

class i2 {
public:
	int x, y;
	void clear() { x = 0; y = 0; }
	i2() { clear(); };
	
	i2(int mx, int my) { x = mx; y = my; }
    void CopyFrom(i2 p) { x = p.x; y = p.y; }
    i2 half() { return i2(x / 2, y / 2); }
	i2 twice() { return i2(x * 2, y * 2); }
    i2 flip() {return i2(y,x);}
	bool isZero() { return (x == 0 && y == 0); }
};


class f2 {
public:
	float x, y;
	void clear() { x = 0; y = 0; }
	f2() { clear(); };
	f2(float mx, float my) { x = mx; y = my; }
	void CopyFrom(f2 p) { x = float(p.x); y = float(p.y); }
    f2 half() { return f2(x / 2, y / 2); }
    f2 twice() { return f2(x * 2, y * 2); }
    f2 flip() {return f2(y,x);}
    i2 toi2() {return i2(x,y);}
};

class f3 {
public:
    float x,y,z;
	char xyz[64] = { 0 };
	void clear() { x = 0; y = 0; z = 0; }
	f3(float mx, float my, float mz) { x = mx; y = my; z = mz; }
    void set(float mx, float my, float mz) { x = mx; y = my; z = mz; }
    void set(f3 p) { x = p.x; y = p.y; z = p.z; }
	f3(i2 m) { x = m.x; y = m.y; z = 0; }
	string str(string fmt) {
    snprintf(xyz, 64, fmt.c_str(), x, y, z);
    //sprintf(xyz, fmt.c_str(), x, y, z);
		return string(xyz);
	}
	f2 xy() {return f2( x,y ); }
	f3* ref() { return this; }

    f3() {clear();};
};


struct CRect {
public:
    float Top, Bottom, Left, Right;
    CRect() {};
    CRect(float _top, float _bottom, float _left, float _right) {
        Top = _top; Bottom = _bottom; Left = _left; Right = _right;
    }
    
 //   CRect objectToScreen() {}
 //   CRect screenToScreen() {}
    
    CRect scaledRect(CRect s) {
        CRect ret;
        float width = abs(Right-Left);
        float height = abs(Top-Bottom);
        float cX = width / 2.0;
        float cY = height / 2.0;
        
        float s_width = abs(s.Right-s.Left);
        float s_height = abs(s.Top-s.Bottom);
        
        float x_scale_factor = s_width / width;
        float y_scale_factor = s_height / height;
        
        float new_width = width * x_scale_factor;
        float new_height = height * y_scale_factor;
        
        float cnX = cX / width * new_width;
        float cnY = cY / height * new_height;
        
        ret.Left = cnX - (new_width / 2.);
        ret.Right = cnX + (new_width / 2.);
        
        ret.Top = cnY - (new_height / 2.);
        ret.Bottom = cnY + (new_height / 2.);
        return ret;
    }
    
    //updated top is 0 and bottom is max
    static bool PTInRect(float x1, float y1, CRect aRect, string uuid = "") {
        //((y1 >= aRect.Top) && (y1<aRect.Bottom) && (x1 >= aRect.Left) && (x1<aRect.Right));
        bool ret1 = (y1 >= aRect.Top);
        bool ret2 = (y1 <  aRect.Bottom);// && (x1 >= aRect.Left) && (x1<aRect.Right));
        bool ret3 = (x1 >= aRect.Left);// && (x1<aRect.Right));
        bool ret4 = (x1 <  aRect.Right);
        return (ret1 && ret2 && ret3 && ret4);
    }
    // Update required as now in 2d  top is 0 and bottom is max
    static bool OverlapRect(CRect Rect1, CRect Rect2) {
        bool result = false;
        float cx = (Rect1.Left + Rect1.Right) / 2.f;
        float cy = (Rect1.Top + Rect1.Bottom) / 2.f;
        
        result = PTInRect(cx, cy, Rect2, "OverLapRect");
        return result;
    }
     // Update required as now in 2d  top is 0 and bottom is max
    static bool RectRectCollision(CRect Rect1, CRect Rect2) {
        return  !(
                  (Rect1.Bottom < Rect2.Top) ||
                  (Rect1.Top > Rect2.Bottom) ||
                  (Rect1.Left > Rect2.Right) ||
                  (Rect1.Right < Rect2.Left));
    }
    
	bool improper() {
		bool ret;
		int w = Right - Left;
		int h = Bottom - Top;
		ret = !(w > 0 && h > 0);
		return ret;
	}

	std::string toStr() {
		ostringstream oss;
		int w = Right - Left;
		int h = Bottom - Top;
		int cx = Left + w / 2;
		int cy = Top + h / 2;
		oss << "Top:" << Top << " Bottom:" << Bottom << " Left:" << Left << " Right:" << Right << " w:" << w << " h:" << h << " cx:" << cx << " cy:" << cy;
		return oss.str();
	}

};

enum JuiceTypes {
	JUICE_ROTZ = 1,
	JUICE_SCALE_OUT,
	JUICE_SCALE_IN,
	JUICE_FLY_OUT,
	JUICE_FLY_IN,
	JUICE_ROTY,
    JUICE_ROTX,
	JUICE_PULSATE,
	JUICE_PULSATE_FULLY,
	JUICE_ROTZ_PULSATE,
	JUICE_ROTXYZ,
	JUICE_ROTXYZ_PULSATE_FULLY,
	JUICE_DIE,
	JUICE_DIE_TEMP,
	JUICES_CANCEL,
	JUICES_END
};

string JuiceName(int j) {
	if (j == 0) return "NIL";
	if (j == JUICE_ROTZ) return "JUICE_ROTZ";
	if (j == JUICE_SCALE_IN) return "JUICE_SCALE_IN";
	if (j == JUICE_SCALE_OUT) return "JUICE_SCALE_OUT";
	if (j == JUICE_FLY_IN) return "JUICE_FLY_IN";
	if (j == JUICE_FLY_OUT) return "JUICE_FLY_OUT";
	if (j == JUICE_ROTY) return "JUICE_ROTY";
    if (j == JUICE_ROTX) return "JUICE_ROTX";
	if (j == JUICE_PULSATE) return "JUICE_PULSATE";
	if (j == JUICE_PULSATE_FULLY) return "JUICE_PULSATE_FULLY";
	if (j == JUICE_ROTZ_PULSATE) return "JUICE_ROTZ_PULSATE";
	if (j == JUICE_ROTXYZ) return "JUICE_ROTXYZ";
	if (j == JUICE_ROTXYZ_PULSATE_FULLY) return "JUICE_ROTXYZ_PULSATE_FULLY";
	if (j == JUICE_DIE) return "JUICE_DIE";
	if (j == JUICE_DIE_TEMP) return "JUICE_DIE_TEMP";
	if (j == JUICES_CANCEL) return "JUICE_CANCEL";
	if (j == JUICES_END) return "JUICE_END";
	return "Wrong ID " + std::to_string(j);
}

class PosRotScale {
public:
	PosRotScale() {
		color.x = 1.;
		color.y = 1.;
		color.z = 1.;
	}

	PosRotScale(f3 pos, f3 rot, float scale = 1.0) {
		PosRotScale();
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

    f3 pos;
    f3 rot;
	f3 color;

	float scale;
	bool hidden = false;
	int JuiceType;
	float JuiceSpeed = 1.;
	float JuiceDuration = 3;
    bool touchable = true;
	double juice_sine_angle = 0.0;
	float originalScale = 1.;
    float originalAspect = 1.78;
    float debugUseOnly = 0.;
	 float m_width;
	 float m_height;
#ifndef NO_BOX2D
	 b2Body* physBodyPtr = nullptr;
#endif
	 int m_touchedX;
	 int m_touchedY;
	 string UUID;

	 CRect getOwnRect(string name = "") {
         int mm_height = m_height;
         int mm_width  = m_width;
	//	 if (scale == -1) {  //AUTOSCALING = -1
	//	    XFunction_AutoScalingToFullScreen::GetDimensionsOf((PosRotScale*)this, &mm_width, &mm_height);
	//	 }
         CRect own(pos.y - mm_height / 2.0, pos.y + mm_height / 2.0, pos.x - mm_width / 2.0, pos.x + mm_width / 2.0);
		 return own;
	 }

    bool Visible() {
        return !hidden;
    }
    
	 void SetJuiceScaleIn() {
		 this->scale = 0.1;
		 this->JuiceType = JuiceTypes::JUICE_SCALE_IN;
	 }

    void CopyFrom(PosRotScale* o) {
        pos.x = o->pos.x;
        pos.y = o->pos.y;
        pos.z = o->pos.z;
        rot.x = o->rot.x;
        rot.y = o->rot.y;
        rot.z = o->rot.z;
        scale = o->scale;
        hidden = o->hidden;
        JuiceType = o->JuiceType;
        JuiceSpeed = o->JuiceSpeed;
        originalScale = o->originalScale;
        originalAspect = o->originalAspect;
		m_width = o->m_width;
		m_height = o->m_height;
#ifndef NO_BOX2D
		physBodyPtr = o->physBodyPtr;
#endif
		UUID = o->UUID;
    }

	void Impulse(f2 up) {
#ifndef NO_BOX2D
		static b2Vec2 bUp;
		bUp.x = up.x;
		bUp.y = up.y;
		if (physBodyPtr) physBodyPtr->ApplyLinearImpulse(bUp, physBodyPtr->GetWorldCenter(), true);
#endif
	}

    void Thrust(f2 up) {
#ifndef NO_BOX2D
        static b2Vec2 bUp;
        bUp.x = up.x;
        bUp.y = up.y;
        if (physBodyPtr) physBodyPtr->ApplyForceToCenter(bUp, true);
#endif
  }
    
    void Torque(int angle) {
#ifndef NO_BOX2D
        if (physBodyPtr) physBodyPtr->ApplyTorque(angle, true);
#endif
    }
    
};

class Serializable : public PosRotScale {
    
    public:

    //can be used externally for Appends
    void readin(FILE *f) {
        fread((void*)&pos,sizeof(pos),1, f);
        fread((void*)&rot,sizeof(rot),1, f);
        fread((void*)&scale,sizeof(scale),1, f);
    }
    
    void writeout(FILE *f) {
        fwrite((void*)&pos,sizeof(pos),1, f);
        fwrite((void*)&rot,sizeof(rot),1, f);
        fwrite((void*)&scale,sizeof(scale),1, f);
    }
    
    void SetSerializeTag(const char* UUID) {
        this->UUID = string(UUID);
     //   return;
        if (this->UUID.size()>0) {
            FILE* f = fopen(this->UUID.c_str(), "rb");
            if (f) {
              //  readin(f);
                fclose(f);
            }
        }
    }
    
    ~Serializable() {
        if (UUID.size()>0) {
            FILE* f = fopen(UUID.c_str(), "wb");
            if (f) {
                writeout(f);
                fclose(f);
                printf("\tSerialized: %s", UUID.c_str());
            }
        }
    }
};



extern class App game;

class GameObject : public Serializable {
    
public:
    CRect m_rect;
    bool m_touched;//deprecated   use touched_bodies instead
	
	bool m_actionComplete = false;

    int m_touchedX;//deprecated
    int m_touchedY;//deprecated
	bool hud = false;
    //Add PRS to multiple drawing of same model
    //use getInstancePtr to access instances
    vector<PosRotScale> prsInstances;
    int modelId;
    ResourceInf* resInf;
    short custom_type;
    GameObject* parent;
    std::list<GameObject*> children;
    short instanceBiengRendered;
    bool rotatefirst;
    
    string Text;
    // float Scale;
    bool billboard;
    PosRotScale desirable;
    
    bool applyTopLeftCorrectionWRTorigin;
    
    static i2 windowSize;
    
    CAnimator animPos, animRot, animScale;
    
#ifndef NO_BOX2D
    b2Body * phys_body;
#endif
    
    void Show() {hidden = false;}
    void Hide() {
		hidden = true;
	}
    void HideFor(GameObject* next) {
        Hide();
		next->Show();
    }
    
    void SetBounds(float fWidth, float fHeight, string name= "") {
        m_width = fWidth;
        m_height = fHeight;
    }
    
	bool is(GameObject& other) {
		if (this->modelId == -1) {
			return (this->UUID == other.UUID);
		} else {
			return (this->modelId == other.modelId);
		}
	}

    bool isOneOf(vector<GameObject*> other) {
        bool ret = false;
        for (auto o : other) {
            ret = ret || (this->modelId == o->modelId);
        }
        return ret;
    }
    
    void NextJuice() {
        JuiceType ++;
        if (JuiceType == JuiceTypes::JUICES_END)
            JuiceType = 0;
    }
    
    
    bool wasTouched() {
		if (hidden) return false;
		bool m_touched_act = m_touched;
		m_touched = false;
        if (m_touched_act) {
			return true;
		} else return false;
    }
    
	bool actionComplete() {
		if (hidden) return false;
		if (m_actionComplete) { m_actionComplete = false; return true; }
		else return false;
	}

    f2 posTouched() {
        return f2(m_touchedX, m_touchedY);
    }
    
    void Update(float dt) {
        
		if (animPos.active) {
			animPos.Step(dt);
            pos.x = mPos[0];
            pos.y = mPos[1];
            pos.z = mPos[2];
        }
        if (animRot.active) {
            animRot.Step(dt);
            rot.x = mRot[0];
            rot.y = mRot[1];
            rot.z = mRot[2];			
        }
        if (animScale.active) {
            animScale.Step(dt);
            scale = mScale[0];//3d?
			m_actionComplete = false;
        }

		m_actionComplete = (animPos.r>=1 && animRot.r>=1 && animRot.r>=1);
	
#ifndef NO_BOX2D
        if (phys_body && phys_body->GetType()==b2_dynamicBody) {
            b2Vec2 position = phys_body->GetPosition();
            float32 angle = phys_body->GetAngle();
            pos.x = position.x ;
            pos.y = position.y ;
            rot.z = angle * 57.272727;
        }
#endif
		
        m_rect.Top = pos.y - m_height / 2.0;
        m_rect.Bottom = pos.y + m_height / 2.0 ;
        m_rect.Left = pos.x - m_width / 2.0;
        m_rect.Right = pos.x + m_width / 2.0;
    }
    
    void o2vf(f3* o, float* v3) {
        v3[0] = o->x; v3[1] = o->y; v3[2] = o->z;
    }
    
    
    float tgtPos[3];
    float tgtRot[3];
    float mPos[3];
    float mRot[3];
    float mScale[3];
    float tgtScale[3];
    
    void transitionTof2(f2 pos, float speed = 0.3, short type = 0) {
        PosRotScale tgt;
        tgt.CopyFrom(this);
        tgt.pos.x = pos.x;
        tgt.pos.y = pos.y;
        transitionTo(tgt, speed, type);
		m_actionComplete = false;
    }
    
    void transitionTo(PosRotScale tgt, float speed = 60., short type = 0) {
        o2vf(&tgt.pos, tgtPos);
        o2vf(&tgt.rot, tgtRot);
        o2vf(&pos, mPos);
        o2vf(&rot, mRot);
        mScale[0] = mScale[1] = mScale[2] = scale;
        tgtScale[0]=tgtScale[1]=tgtScale[2]= tgt.scale;
        animPos.Reset(mPos, tgtPos, speed, type);
        animRot.Reset(mRot, tgtRot, speed, type);
        animScale.Reset(mScale, tgtScale, speed, type);
    }
    
    void Clone(GameObject* clone) {
        clone->pos = pos;
        clone->rot = rot;
        //   clone->Scale = Scale;
        clone->scale = scale;
        clone->resInf = resInf;
        clone->custom_type = custom_type;
        clone->modelId = modelId;
        //clone->children = children;
        clone->hidden = hidden;
        clone->rotatefirst = rotatefirst;
        clone->parent = parent;
        clone->billboard = billboard;
        clone->m_rect = m_rect;
        clone->m_height = m_height;
        clone->m_width = m_width;
    }
    
    void AddChild(GameObject* child){
        children.push_back(child);
        child->parent = this;
    }
    PosRotScale* AddInstance(PosRotScale &prs) {
        if (prs.scale <= 0) prs.scale = 1.0;
        prs.originalScale = prs.scale;
       //?? prs.originalAspect = prs.originalAspect
		prs.UUID = this->UUID;
        prsInstances.push_back(prs);
        return &prs;
    }

    PosRotScale prst;

    PosRotScale*  AddInstance(f2 pos) {
        prst.pos.x = pos.x;
        prst.pos.y = pos.y;
        prst.scale = this->scale;
        prst.JuiceType = this->JuiceType;
        prst.JuiceSpeed = this->JuiceSpeed;
        prst.originalScale = this->originalScale;
        prst.originalAspect = this->originalAspect;
        prsInstances.push_back(prst);
		return &prsInstances.back();
    }
    
    //getInstance(-1) returns main object instances are at 0..n-1
    PosRotScale* getInstancePtr(int n) {
        if (n < 0 || n >= int(prsInstances.size())) return ((PosRotScale*)this);
        return &prsInstances.at(n);
    }
    
   
    GameObject() {
        pos.clear();
        rot.clear();
        prsInstances.clear();
        modelId = -1;
        scale = 1.;
        resInf = nullptr;
        custom_type = -1;
        children.clear();
        hidden = false;
        parent = nullptr;
        rotatefirst = false;
        UUID = "";
        //    Scale = 1.0f;
        billboard = false;
        applyTopLeftCorrectionWRTorigin = false;
        m_touched = false;
		resInf = nullptr;
    }
    
    string Name() {
		if (UUID.size()) return UUID;
        if (Text.size()) return Text;
        if (!resInf) return "Undefined";
       // if (resInf->name.size()) return resInf->name;
        if (resInf) if (resInf->alx.size()) return resInf->alx;
        return "Undefined";
    }
    
    ~GameObject() {
        
    }
    
};
i2 GameObject::windowSize;


class Camera : public GameObject, public CFpsCamera {
	
public:
    short mode;
	int windowWidth;//for 2D ortho setup
	int windowHeight;
    int orthoType;
    
    enum {
        CAM_MODE_NULL,
        CAM_MODE_FPS,
        CAM_MODE_LOOKAT,
		CAM_MODE_2D,
        CAM_MODE_LAST, //ALL MODES AFTER THIS WILL BE IGNORED
        CAM_MODE_CHASE,
        CAM_MODE_FLY
    } camModes;
    
	void SetMode(int MODE) {
		this->mode = MODE;
	}
	
	int GetMode() {
		return this->mode;
	}

	Camera(int MODE) {
		SetMode(MODE);
		pos.z = 10;
		Position.z = pos.z;
		resInf = new ResourceInf();
        resInf->Set("Camera", "", "",1);
    }
    
	f3 getPos() {
		return f3(Position.x, Position.y, Position.z);
	}

	f3 getRot() {
		return f3(RotatedX, RotatedY, RotatedZ);
	}


    Camera()  {
        SetMode(CAM_MODE_NULL);
    }
    
    ~Camera() {
        delete resInf;
    }
    
	inline void MoveAhead(float d) { pos.z += d; Position.z = pos.z; }
	inline void MoveBack(float d) { pos.z-= d; Position.z = pos.z;}
    inline void MoveRight(float d) {pos.x+=d; Position.x = pos.x;}
    inline void MoveLeft(float d) {pos.x-=d; Position.x = pos.x;}
    inline void MoveDown(float d) {pos.y-=d; Position.y = pos.y;}
    inline void MoveUp(float d) {pos.y+=d; Position.y = pos.y;}
    
	inline void RollRight(float d) { rot.z += d; RotatedZ = rot.z; }
    inline void RollLeft(float d) {rot.z-=d; RotatedZ = rot.z;}
    inline void PitchUp(float d) {rot.x-=d; RotatedX = rot.x;}
    inline void PitchDown(float d) {rot.x+=d; RotatedX = rot.x;}
    inline void YawRight(float d) {rot.y+=d; RotatedY = rot.y;}
    inline void YawLeft(float d) {rot.y-=d; RotatedY = rot.y;}
    
    void ViewFromCurrent() {
        glRotatef(rot.x, 1., 0., 0.);
        glRotatef(rot.y, 0., 1., 0.);
        glRotatef(rot.z, 0., 0., 1.);
        glTranslatef(-pos.x, -pos.y, -pos.z);
    }
    
	void OnPosRotChanged() {
		Position.x = pos.x;
		Position.y = pos.y;
		Position.z = pos.z;
		RotatedX = rot.x;
		RotatedY = rot.y;
		RotatedZ = rot.z;
	}

    void Update(float deltaT, GameObject* obj) {
		if (obj == this) {
			OnPosRotChanged();
		}

        if (mode==CAM_MODE_LOOKAT) {
           // aluLookAt(pos.x, pos.y, pos.z, obj->pos.x, obj->pos.y, obj->pos.z, 0.,1.,0.);
        }

		if (mode == CAM_MODE_2D) {
		//	aluLookAt(0., 0., 0., obj->pos.x, obj->pos.y, obj->pos.z, 0., 1., 0.);
		//	ViewFromCurrent();
		}
        
        if (mode==CAM_MODE_FPS || mode==CAM_MODE_FLY) {
            ViewFromCurrent();
        }
        
    }
    
    void NextMode() {
        mode++;
        if (mode>=CAM_MODE_LAST) {
            mode= CAM_MODE_NULL + 1;
        }
        if (mode==CAM_MODE_LOOKAT) printf("\tCameraMode:LOOKAT");
        if (mode==CAM_MODE_FPS) printf("\tCameraMode:FIRSTPERSON");
        if (mode==CAM_MODE_FLY) printf("\tCameraMode:FLY");
        if (mode==CAM_MODE_CHASE) printf("\tCameraMode:CHASE");
		if (mode == CAM_MODE_2D) printf("\tCameraMode:2D");
    }
    
	void processKeyDownWin(int key, float distStep) {
		if (mode == CAM_MODE_LOOKAT) {
			switch (key) {
			case AL_KEY_UP:
				MoveAhead(distStep);
				break;
			case AL_KEY_DOWN:
				MoveBack(distStep);
				break;
			case AL_KEY_LEFT:
				MoveLeft(distStep);
				break;
			case AL_KEY_RIGHT:
				MoveRight(distStep);
				break;
			case '3':
				MoveDown(distStep);
				break;
			case '9':
				MoveUp(distStep);
				break;
			default:
				break;
			}
		}
	}

    void processKeyDownMac(int key, float distStep) {
    
       if (mode==CAM_MODE_FPS) {
        switch (key) {
            case '8':
                MoveAhead(distStep);
                break;
            case '2':
                MoveBack(distStep);
                break;
            case '4':
                MoveLeft(distStep);
                break;
            case '6':
                MoveRight(distStep);
                break;
            case '3':
                MoveDown(distStep);
                break;
            case '9':
                MoveUp(distStep);
                break;
            default:
                break;
        }
       }
    }
};

#include "../XFunctions.hpp"

#define C_float float
#define Sin sin
#define Cos cos

char* New_String(const char* sz) {return ((char*)sz);}

void alPushI (int cmd, int x, int y);
void alPushP (int cmd, void* param1, void* param2);
int alLoadModel(ResourceInf* r);
int alReserveModelId(void);
void alDrawModel (int ident, bool wireframe = false);

void alBillBoardBegin();
void alBillBoardEnd();
void alLoadIdentity();
void alPushMatrix();
void alPopMatrix();
void alaluLookAt(float x1, float y1, float z1, float x2, float y2, float z2, float x, float y, float z);
void alTriangle(float size);
void alLine(float x1, float y1, float x2, float y2);
void alCircle(float r, int segments);
void alRect(float w, float h);
void alLoadModel(char* alx, char* tga, int id, float size);
void alScaleModel(int id, float sx, float sy, float sz);
void alAlphaTest (int enable, float fA = 0.4); // 0=>unset ; 1=>set GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
float alModelBounds(int id);
void alDrawModelTranslateRotate (int id, float posx = 0.0, float posy = 0.0, float posz = 0.0, float angle = 0.0, float x = 0.0, float y = 0.0, float z = 0.0, int rotatefirst = 0, int billboard = 0);
void alTranslateRotate (float posx = 0.0, float posy = 0.0, float posz = 0.0, float angle =0.0, float x = 0.0, float y = 0.0, float z = 0.0);

#endif
