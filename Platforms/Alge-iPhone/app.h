
#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

extern void appInit(char*);
extern void appSize(int,int);
extern void appDeinit(void);
extern void appAccelerometerSz(char*);
//extern void appRender(int accelX, int accelY, int accelZ);
extern void	appRender(float tick, int width, int height, int accelX, int accelY, int accelZ);
extern int appPull(void);
extern void appPushI(int,int,int);
extern char* appSzlastP1(void);
extern int appIntlastP1(void);
extern int appIntlastP2(void);
extern void* appP1(void);
extern void* appP2(void);
extern bool LoadTGA2(void*,void*);
	
#ifdef __cplusplus
}
#endif


#endif // !APP_H_INCLUDED
