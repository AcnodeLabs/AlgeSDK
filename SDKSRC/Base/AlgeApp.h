#include "../Classlets/com/acnodelabs/funkit/all.h"

class AlgeApp {

public:
    CTrackBall trackball;
    CAnimator can;
    CTimed animStepTimed;
    FontMap16x16 fonts;
    int keyframe, nseq,screenX, screenY;
    f3 eye,eyerot,tgt,up;
    float timeVar, animstep, deltaT;
    float bz, width, height;
    GameObject* gobs[128]; short nGobs;
    GameObject* selectedObject;
    CAxis xyz;
    
    short currentscene;
    
    int iUnassigned;
    int dcursor;
    int screen_y;
    PEG input,output;
    CResourceManager rm;
    aL10 AL10;
    virtual void UpdateCustom(GameObject*,PEG::CMD*) {};
    bool inhibitRender = false;
    bool edit;
    bool wireframe = false;
    
    Camera aCamera;
    
    GameObject origin;
    
    AlgeApp() :
    iUnassigned(-1),
    timeVar(0.0)  {
        width = 0;
        height = 0;
        dcursor = 0;
        screen_y = 0;
        keyframe = 1;
        animstep = 0.0;
        bz = 1.0;
        nseq = 0;
        screenX  = iUnassigned;
        screenY  = iUnassigned;
        selectedObject = nullptr;
        edit = false;
        iSelectedObject = 0;
        nGobs = 0;
        wireframe = false;
        iSelectedObject = 0;
        currentscene=0;
        LoadScene(currentscene);
    }
    
	void Init(char* path);
	void Deinit();
	short LoadScene(short n);
    
	auto AddObject(GameObject *o, GameObject* parent = nullptr);
    
	void UndoInheritedRotation(GameObject* it);
    
	auto renderSingleObject(GameObject* it);
    
    short iSelectedObject = 0;
    
	auto renderObjects(float deltaT, bool btrackball);
    
    virtual void Update(float delta_t) {};
    virtual void processInput() {};
    
	auto Render(float deltaT, int aX, int aY, int aZ);
    
	auto LoadModel(GameObject* go, ResourceInf* res, short customtype = 0);
    
};

