#ifndef CEasyBullet_INCLUDED
#define CEasyBullet_INCLUDED

#include "../../../../Base/CBaseV1_2.h"
#include "btBulletDynamicsCommon.h"


btDynamicsWorld* dynamicsWorld;
btAlignedObjectArray<btCollisionShape*> collisionShapes;


class CActor {
    btScalar m[16];
	btTransform t;
	

public://Initially Public until formation
    
	enum bodyType { BODYTYPE_BOX , BODYTYPE_CYLINDER, BODYTYPE_SPHERE, BODYTYPE_CAPSULE, BODYTYPE_CONE};
    btRigidBody* body1;
    btCollisionShape* shape;
    btTransform transform;
    float pos[3];
	CModel* model;	
	
	CActor() {
		model = 0;
	}

	static void setDynamicsWorld(btDynamicsWorld *w) {
		dynamicsWorld = w;
	}

	 void alApplyPosQuat(float* pos, btQuaternion* qua) {
        btVector3 r = qua->getAxis();
		btScalar a = qua->getAngle();
		glTranslatef(pos[0],pos[1],pos[2]);	
		glRotatef(a * 57.2727272727f, r.getX(),r.getY(),r.getZ());
    }

	
	void glDraw() {
		if (!model) return;
		body1->getMotionState()->getWorldTransform(t);
		t.getOpenGLMatrix(m);		
		glPushMatrix();
		glMultMatrixf(m);
		model->glDraw();
		glPopMatrix();
	}

	void rigidBox(vec3 origin, vec3 size) {
		vec3 inertia; inertia.unity();
		float mass = 1;
		body(BODYTYPE_BOX, origin, size, inertia, mass);
	}

    void body(int bodytype, vec3 origin,vec3 size, vec3 inertia,float mass) {
        btCollisionShape* aShape = NULL;
		pos[0] = origin.x; pos[1] = origin.y; pos[2] = origin.z;
        inertia.x = 1;
		inertia.y = 1;
		inertia.z = 1;
		mass = 1;

		switch (bodytype) {
            case BODYTYPE_BOX:
                aShape = new btBoxShape(btVector3(btScalar(size.x),btScalar(size.y),btScalar(size.z)));
                break;
			case BODYTYPE_CYLINDER:
				aShape = new btCylinderShape(btVector3(btScalar(size.x),btScalar(size.y),btScalar(size.z)));
                break;
			case BODYTYPE_SPHERE:
				aShape = new btSphereShape(btScalar(size.x));
		        break;
        	case BODYTYPE_CAPSULE:
				aShape = new btCapsuleShape(btScalar(size.x),btScalar(size.y));
                break;
			case BODYTYPE_CONE:
				aShape = new btConeShape(btScalar(size.x),btScalar(size.y));
		        break;
        }
        
        if (aShape) {
            btScalar Mass(mass);
            bool isDynamic = (Mass != 0.f);
            btVector3 localInertia(inertia.x,inertia.y,inertia.z);
            if (isDynamic)
                aShape->calculateLocalInertia(mass,localInertia);
            transform.setIdentity();
            transform.setOrigin(btVector3(origin.x,origin.y,origin.z));
			btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(Mass,myMotionState,aShape,localInertia);
			body1 = new btRigidBody(rbInfo);            
            collisionShapes.push_back(aShape);
			dynamicsWorld->addRigidBody(body1);
        }

        //return body1;
    }
    
    static void Deinit() {
        int i;
        for (i = dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			dynamicsWorld->removeCollisionObject( obj );
			delete obj;
		}
        
		for (int j=0;j<collisionShapes.size();j++) {
			btCollisionShape* shape = collisionShapes[j];
			collisionShapes[j] = 0;
			delete shape;
		}
        collisionShapes.clear();
        
    }
    
}; 

class CEasyBulletDebugDraw: public btIDebugDraw {
  
    int m_debugMode;
    float v[6];
    float c[6]; 
        
    public:
        
        CEasyBulletDebugDraw() {
            m_debugMode = DBG_DrawWireframe;
            setDebugMode(m_debugMode);
        }
        
        void	drawLine(const btVector3& from,const btVector3& to,const btVector3& color) {
            drawLine(from, to, color,color);
        }
        
        void	drawLine(const btVector3& from,const btVector3& to,const btVector3& fromcolor, const btVector3& tocolor ) {
            v[0] = from.getX();
            v[1] = from.getY();
            v[2] = from.getZ();
            v[3] = to.getX();
            v[4] = to.getY();
            v[5] = to.getZ();
            c[0]  = fromcolor.getX();
            c[1]  = fromcolor.getY();
            c[2]  = fromcolor.getZ();
            c[3]  = tocolor.getX();
            c[4]  = tocolor.getY();
            c[5]  = tocolor.getZ();
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, v);
            glDrawArrays(GL_LINES, 0, 2);
        }
        
        void	drawSphere (const btVector3& p, btScalar radius, const btVector3& color) {}
        void	drawBox (const btVector3& boxMin, const btVector3& boxMax, const btVector3& color, btScalar alpha) {}
        
        void	drawTriangle(const btVector3& a,const btVector3& b,const btVector3& c,const btVector3& color,btScalar alpha){}
        
        void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color) {}
        
        void	reportErrorWarning(const char* warningString) {}
        
        void	draw3dText(const btVector3& location,const char* textString) {}
        
        void	setDebugMode(int debugMode) {
            m_debugMode = debugMode;
        }
        
        int		getDebugMode() const { return m_debugMode;}
        
    };


class CEasyBullet {
    
    btDispatcher *dispatcher;
    btBroadphaseInterface *pairCache;
    btConstraintSolver *constraintSolver;
    btCollisionConfiguration *collisionConfiguration;
    CEasyBulletDebugDraw gldbg;
    
    void Init(int worldsize) {
        btVector3 min3(-worldsize,-worldsize,-worldsize);
        btVector3 max3( worldsize, worldsize, worldsize);
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
        constraintSolver = new btSequentialImpulseConstraintSolver();
        pairCache = new btAxisSweep3(min3, max3);
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,pairCache,constraintSolver,collisionConfiguration);
        dynamicsWorld->setGravity(btVector3(0,0.0f,-9.8f));
    }

public:
    
    void InitDebugDraw() {
        dynamicsWorld->setDebugDrawer(&gldbg);
        dynamicsWorld->getDebugDrawer()->setDebugMode(CEasyBulletDebugDraw::DBG_DrawWireframe);
    }
    
    void SaveWorld(char* filename) {
        
    }
    
    void LoadWorld(char* filename) {
    
    }
        
    CEasyBullet() {Init(1000);}
    CEasyBullet(int worldsize) {Init(worldsize);}
    
    btDiscreteDynamicsWorld *dynamicsWorld;
    
    void RenderDbg(bool debug, float dt) {
        dynamicsWorld->stepSimulation(dt,0);//ms / 1000000.f);
		if (debug) dynamicsWorld->debugDrawWorld();
    }
    
    ~CEasyBullet() {
        delete dynamicsWorld;
        delete pairCache;
        delete constraintSolver;
        delete dispatcher;
        delete collisionConfiguration;
    }
    
};

#endif