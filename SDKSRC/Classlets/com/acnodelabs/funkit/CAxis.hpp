#ifdef CAXIS_INCLUDED
#else
#define CAXIS_INCLUDED
class CAxis {
    ////CODE TO DRAW SIMPLE AXES
    float ORG[3];
    float XP[3];
    float XN[3];
    float YP[3];
    float YN[3];
    float ZP[3];
    float ZN[3];
    
public:
    
    void setSize(float size) {
        ORG[0] = 0;
        ORG[1] = 0;
        ORG[2] = 0;
        XP[0] = size; XN[0] = -1;
        XP[1] = 0; XN[1] =  0;
        XP[2] = 0; XN[2] =  0;
        YP[0] = 0; YN[0] = 0;
        YP[1] = size; YN[1] =  -1;
        YP[2] = 0; YN[2] =  0;
        ZP[0] = 0; ZN[0] =  0;
        ZP[1] = 0; ZN[1] =  0;
        ZP[2] = size; ZN[2] =  -1;
    }
    
    CAxis() {
        setSize(100);
    }
    
#ifndef NOGL
    class mDesign {
    public:
        GLint st;
        GLushort pattern;
        vec3 colorX;
        vec3 colorY;
        vec3 colorZ;
        mDesign() {
            st = 1;
            pattern = 0x1FEA;
            colorX.x = 1.;//xRed
            colorY.y = 1.;//yGreen
            colorZ.z = 1.;//zBlue
        }
    } _mDesign, _mDesignCopy;
    
    void setStippleAndColor(GLint st, GLushort pattern, vec3 colorX, vec3 colorY, vec3 colorZ) {
        _mDesign.st = st;
        _mDesign.pattern = pattern;
        _mDesign.colorX = colorX;
        _mDesign.colorY = colorY;
        _mDesign.colorZ = colorZ;
    }
    
    void glDrawGroundAsGrid(void)
    {
        static GLfloat color[4];
        glGetFloatv(GL_CURRENT_COLOR, color);
        
        glPushMatrix ();
        glLineWidth (0.05);
        //glEnable( GL_LINE_STIPPLE );
        //glLineStipple( _mDesign.st, _mDesign.pattern);
        
#ifdef WIN32
        glBegin (GL_LINES);
        glColor3f (0.2f,0.2f,0.2f);
        for (float x=-100.; x<=100.; x+=10) {
            ORG[0] = x;ORG[1] = 0;ORG[2] = -100;
            XP[0] = x;XP[1] = 0;XP[2] = +100;
            glVertex3fv (ORG);
            glVertex3fv (XP );
        }
        ORG[0] = 0;
        //glColor3f (_mDesign.colorY.x,_mDesign.colorY.y,_mDesign.colorY.z);
        //glVertex3fv (ORG);
        //glVertex3fv (YP );
        //glColor3f (_mDesign.colorZ.x,_mDesign.colorZ.y,_mDesign.colorZ.z);
        for (float z=-100.; z<=100.; z+=10) {
            ORG[0] = -100;ORG[1] = 0;ORG[2] = z;
            ZP[0] = +100;ZP[1] = 0;ZP[2] = z;
            glVertex3fv (ORG);
            glVertex3fv (ZP );
        }
        glEnd();
        glColor3f (color[0],color[1],color[2]);
        glDisable( GL_LINE_STIPPLE );
#endif
        
        glPopMatrix ();
        _mDesign = _mDesignCopy;
    }
    
    void glDraw(void)
    {
        static GLfloat color[4];
        glGetFloatv(GL_CURRENT_COLOR, color);
        
        glPushMatrix ();
        glLineWidth (0.1);
#ifdef WIN32
        glEnable( GL_LINE_STIPPLE );
        glLineStipple( _mDesign.st, _mDesign.pattern);
       //  #ifdef WIN32
         glBegin (GL_LINES);
         glColor3f (_mDesign.colorX.x,_mDesign.colorX.y,_mDesign.colorX.z);
         glVertex3fv (ORG);
         glVertex3fv (XP );
         glColor3f (_mDesign.colorY.x,_mDesign.colorY.y,_mDesign.colorY.z);
         glVertex3fv (ORG);
         glVertex3fv (YP );
         glColor3f (_mDesign.colorZ.x,_mDesign.colorZ.y,_mDesign.colorZ.z);
         glVertex3fv (ORG);
         glVertex3fv (ZP );
         glEnd();
         glColor3f (color[0],color[1],color[2]);
        
        glDisable( GL_LINE_STIPPLE );
#endif
        glPopMatrix ();
        _mDesign = _mDesignCopy;
    }
#endif
    
};//~CAxis
#endif
