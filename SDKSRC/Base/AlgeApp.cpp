#include "AlgeApp.h"

    
	void AlgeApp::Init(char* path) {
	}

	void AlgeApp::Deinit() {}

    //Preconditions: Dont call before init
    //Assumption Scene is Saved from same arrangement of Gobs
    short AlgeApp::LoadScene(short n) {
        char filename[16];
        /* sprintf(filename, "")
         for (int i=0; i<nGobs; i++) {
         gobs[i]
         }
         */
        return 0;
    }
    
    auto AlgeApp::AddObject(GameObject *o, GameObject* parent = nullptr) {
        nGobs++;
        if (nGobs>=128) nGobs=127;
        gobs[nGobs-1] = o;
        if (parent) parent->AddChild(o);
    }
    
    void AlgeApp::UndoInheritedRotation(GameObject* it) {
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
    
    auto AlgeApp::renderSingleObject(GameObject* it) {
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
    
    short AlgeApp::iSelectedObject = 0;
    
    auto AlgeApp::renderObjects(float deltaT, bool btrackball) {
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
    
    virtual void AlgeApp::Update(float delta_t) {};
    virtual void AlgeApp::processInput() {};
    
    auto AlgeApp::Render(float deltaT, int aX, int aY, int aZ) {
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
    
    auto AlgeApp::LoadModel(GameObject* go, ResourceInf* res, short customtype = 0) {
        go->modelId = alLoadModel(res);
        go->resInf = res;
        go->custom_type = customtype;
    }
    


