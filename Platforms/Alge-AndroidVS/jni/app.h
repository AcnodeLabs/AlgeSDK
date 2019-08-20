
#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

extern void appInit(char*);
extern void appDeinit();
extern void appAccelerometerSz(char*);
extern void appRender(float tick, int width, int height, int accelX, int accelY, int accelZ);
extern void appRenderJ(int tickE6, int width, int height, int accelX, int accelY, int accelZ);
extern int appPull();
extern void appPushI(int,int,int);
extern char* appSzlastP1();	
extern int appIntlastP1();
extern int appIntlastP2();
extern void* appP1();
extern void* appP2();
extern bool LoadTGA2(void*,void*);
	
#ifdef __cplusplus
}
#endif


#endif // !APP_H_INCLUDED
