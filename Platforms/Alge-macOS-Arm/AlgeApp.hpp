
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
    
    //Preconditions: Dont call before init
    //Assumption Scene is Saved from same arrangement of Gobs
    short LoadScene(short n) {
        char filename[16];
        /* sprintf(filename, "")
         for (int i=0; i<nGobs; i++) {
         gobs[i]
         }
         */
        return 0;
    }
    
    auto AddObject(GameObject *o, GameObject* parent = nullptr) {
        nGobs++;
        if (nGobs>=128) nGobs=127;
        gobs[nGobs-1] = o;
        if (parent) parent->AddChild(o);
    }
    
    void UndoInheritedRotation(GameObject* it) {
        it->rot.x = - it->parent->rot.x;
        it->rot.y = - it->parent->rot.y;
        it->rot.z = - it->parent->rot.z;
        
        //https://stackoverflow.com/questions/22269435/how-to-iterate-through-a-list-of-objects-in-c
        for (auto const& child : it->children) {
            child->rot.x = - it->rot.x;
            child->rot.y = - it->rot.y;
            child->rot.z = - it->rot.z;
        }
    }
    
    auto renderSingleObject(GameObject* it) {
        static float wobble = 0.;
        glPushMatrix();
        f3 relPos, relRot;
        
        if (edit && it==gobs[iSelectedObject]) {
            wobble+=0.2f;
            glScalef(1. + 0.01 * sin(wobble),1. + 0.01 * sin(wobble), 1. + 0.01 * sin(wobble));
        }
        
        relPos.x = it->pos.x;
        relPos.y = it->pos.y;
        relPos.z = it->pos.z;
        relRot.x = it->rot.x;
        relRot.y = it->rot.y;
        relRot.z = it->rot.z;
        
        if (it->parent) {
            relPos.x += it->parent->pos.x;
            relPos.y += it->parent->pos.y;
            relPos.z += it->parent->pos.z;
            relRot.x += it->parent->rot.x;
            relRot.y += it->parent->rot.y;
            relRot.z += it->parent->rot.z;
        }
  
        if (!it->rotatefirst) glTranslatef(relPos.x , relPos.y, relPos.z);
        
         glRotatef(relRot.x, 1., 0., 0.);
         glRotatef(relRot.y, 0., 1., 0.);
         glRotatef(relRot.z, 0., 0., 1.);
        
        if (it->rotatefirst) glTranslatef(relPos.x , relPos.y, relPos.z);
        
        if (it->hidden) return;
        
        glScalef(it->scale,it->scale,it->scale);
        
        if (edit) {
            if (it->modelId>=0)
             xyz.setSize(rm.models[it->modelId]->boundz() * 2.f);
             xyz.glDraw();//draw axis
            //xyz.glDrawGroundAsGrid();
        }
        
        PEG::CMD* cmd  = input.pull();
        UpdateCustom(it, cmd);
        
        if (it->billboard) alBillboardBegin();
        if (edit) {
            if (it->modelId>=0) alDrawModel(it->modelId, wireframe);
        } else {
            if (it->modelId>=0) alDrawModel(it->modelId);
        }
        if (it->billboard) alBillboardEnd();
        glPopMatrix();
    }
    
    short iSelectedObject = 0;
    
    auto renderObjects(float deltaT, bool btrackball) {
        selectedObject = gobs[iSelectedObject];
        alPushMatrix();
        aCamera.Update(deltaT, selectedObject);
        if (btrackball) trackball.ApplyRotate();
        
        vec3 gray(0.5,0.5,0.5);
        xyz.setStippleAndColor(2, 0xAEAE, gray, gray, gray);
        
        if (edit) {
            xyz.glDraw();
            xyz.glDrawGroundAsGrid();
        }
        
        for (int i=1; i<nGobs; i++) {
            GameObject* it = gobs[i];
            if (inhibitRender) {inhibitRender = false; continue;}
            renderSingleObject(&(*it));
        }
        
        alPopMatrix();
    }
    
    virtual void Update(float delta_t) {};
    virtual void processInput() {};
    
    auto Render(float deltaT, int aX, int aY, int aZ) {
        if (!edit) {
            timeVar += deltaT;
            Update(deltaT);
            for (int i=1; i<nGobs; i++) {
                GameObject* it = gobs[i];
                 it->Update(deltaT);
            }
        }
        glLoadIdentity();
        glClearColor(0.0,0,0.,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput();
        renderObjects(deltaT, true);
    }
    
    auto LoadModel(GameObject* go, ResourceInf* res, short customtype = 0) {
        go->modelId = alLoadModel(res);
        go->resInf = res;
        go->custom_type = customtype;
    }
    
};

