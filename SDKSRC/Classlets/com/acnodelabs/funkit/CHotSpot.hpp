#ifdef CHOTSPOT_INCLUDED
#else
#define CHOTSPOT_INCLUDED
#include "CLog.hpp"

class CHotSpot {

public:
    int id;
	int Top, Left, Bottom, Right;
    static int sx, sy;
    static int ox, oy;
    static float aspect;
    
    static void Res(int iSx, int iSy) {
        sx = iSx;
        sy = iSy;
        aspect = sx / ( sy + 0.000001f);
    }
    void Set(int id, int iwidth, int iheight, int iTop, int iLeft, int iBottom, int iRight) {
        this->id = id;
        Set(iwidth, iheight, iTop, iLeft, iBottom, iRight);
    }

    void Set(int iwidth, int iheight, int iTop, int iLeft, int iBottom, int iRight) {
        ox = iwidth;
        oy = iheight;
        Top = iTop; Left = iLeft; Bottom = iBottom; Right = iRight;
    }
    static CLog log;
    static string sz;

    static void WriteCodeToLog(int touchstart_x, int touchstart_y, int touchend_x, int touchend_y) {
        int w, h, t, l, b, r;
        l = touchstart_x;
        r = touchend_x;
        t = touchstart_y;
        b = touchend_y;
        w = r - l;
        h = b - t;
        sz =  "hs[][].Set(" + std::to_string(w) + ",";
        sz +=  std::to_string(h) + ",";
        sz += std::to_string(t) + ",";
        sz += std::to_string(l) + ",";
        sz += std::to_string(b) + ",";
        sz += std::to_string(r) +");\n";
        log.it((char*)sz.c_str());
    }

    bool HitX(int cx, int cy) {
        bool bl = (cx>=Left);
        bool br = (cx<=Right);
        bool bt = (cy>=Top);
        bool bb = (cy<=Bottom);
        if ( bl && br && bt && bb) {
            return true; 
        }else {
            return false;   
        }
    }
    
    //With Aspect
    bool Hit(int cx, int cy) {
        
       // float fx = sx * 1.0f / ox;
        float fy = sy * 1.0f / oy;
        
        int pixelsinuseX = sy * ox / oy;
        int wastedPixelsXlft = (sx - pixelsinuseX)/2; 
        //int pixelsHotX = pixelsinuseX / (Right-Left) * (sx);
        
      //  bool bl = (cx>=Left*fx+wastedPixelsXlft);
      //  bool br = (cx<=wastedPixelsXlft + Left + pixelsHotX);
        int tx = (wastedPixelsXlft + Left/(float)ox * pixelsinuseX);
        int tx2 = (wastedPixelsXlft + Right/(float)ox * pixelsinuseX);
        bool bl = (cx>= tx);
        bool br = (cx<= tx2);
        
        bool bt = (cy>=Top*fy);
        bool bb = (cy<=Bottom*fy);
        if ( bl && br && bt && bb) {
            return true; 
        }else {
            return false;   
        }
    }
    
    bool HitChk(int cx, int cy) {
        
        float fx = sx * 1.0f / ox;
        float fy = sy * 1.0f / oy;
        
        bool bl = (cx>=Left*fx);
        bool br = (cx<=Right*fx);
        bool bt = (cy>=Top*fy);
        bool bb = (cy<=Bottom*fy);
        if ( bl && br && bt && bb) {
            return true; 
        }else {
            return false;   
        }
    } 
    
};

#ifndef METRO
float CHotSpot::aspect = 0;
int CHotSpot::sx = 320;
int CHotSpot::sy = 480;
int CHotSpot::ox = 320;
int CHotSpot::oy = 480;
#endif
#endif