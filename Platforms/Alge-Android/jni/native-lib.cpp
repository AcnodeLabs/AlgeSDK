

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>

///////////#include "importgl.h"
/* San Angeles Observation OpenGL ES version example
 * Copyright 2004-2005 Jetro Lauha
 * All rights reserved.
 * Web: http://iki.fi/jetro/
 *
 * This source is free software; you can redistribute it and/or
 * modify it under the terms of EITHER:
 *   (1) The GNU Lesser General Public License as published by the Free
 *       Software Foundation; either version 2.1 of the License, or (at
 *       your option) any later version. The text of the GNU Lesser
 *       General Public License is included with this source in the
 *       file LICENSE-LGPL.txt.
 *   (2) The BSD-style license that is included with this source in
 *       the file LICENSE-BSD.txt.
 *
 * This source is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files
 * LICENSE-LGPL.txt and LICENSE-BSD.txt for more details.
 *
 * $Id: importgl.h,v 1.4 2005/02/24 20:29:33 tonic Exp $
 * $Revision: 1.4 $
 */

#ifndef IMPORTGL_H_INCLUDED
#define IMPORTGL_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif
#ifndef DISABLE_IMPORTGL
#define DISABLE_IMPORTGL
#endif
    
#if defined(__APPLE__)
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#else
    //#include <GLES/egl.h>
#include <GLES/gl.h>
#endif
    
    //#include <GLES/gl.h>
    
    
    
#ifndef ANDROID_NDK
    //#include <OpenGLES/EAGL.h> //ADD
    //#include <GLES/egl.h>
#endif /* !ANDROID_NDK */
    
    /* Use DISABLE_IMPORTGL if you want to link the OpenGL ES at
     * compile/link time and not import it dynamically runtime.
     */
#ifndef DISABLE_IMPORTGL
    
    /* Dynamically fetches pointers to the egl & gl functions.
     * Should be called once on application initialization.
     * Returns non-zero on success and 0 on failure.
     */
    extern int importGLInit();
    
    /* Frees the handle to egl & gl functions library.
     */
    extern void importGLDeinit();
    
    
#ifndef IMPORTGL_API
#define IMPORTGL_API extern
#endif
#ifndef IMPORTGL_FNPTRINIT
#define IMPORTGL_FNPTRINIT
#endif
    
#define FNDEF(retType, funcName, args) IMPORTGL_API retType (*funcPtr_##funcName) args IMPORTGL_FNPTRINIT
    
#ifndef ANDROID_NDK
    FNDEF(EGLBoolean, eglChooseConfig, (EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config));
    FNDEF(EGLContext, eglCreateContext, (EGLDisplay dpy, EGLConfig config, EGLContext share_list, const EGLint *attrib_list));
    FNDEF(EGLSurface, eglCreateWindowSurface, (EGLDisplay dpy, EGLConfig config, NativeWindowType window, const EGLint *attrib_list));
    FNDEF(EGLBoolean, eglDestroyContext, (EGLDisplay dpy, EGLContext ctx));
    FNDEF(EGLBoolean, eglDestroySurface, (EGLDisplay dpy, EGLSurface surface));
    FNDEF(EGLBoolean, eglGetConfigAttrib, (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value));
    FNDEF(EGLBoolean, eglGetConfigs, (EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config));
    FNDEF(EGLDisplay, eglGetDisplay, (NativeDisplayType display));
    FNDEF(EGLint, eglGetError, (void));
    FNDEF(EGLBoolean, eglInitialize, (EGLDisplay dpy, EGLint *major, EGLint *minor));
    FNDEF(EGLBoolean, eglMakeCurrent, (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx));
    FNDEF(EGLBoolean, eglSwapBuffers, (EGLDisplay dpy, EGLSurface draw));
    FNDEF(EGLBoolean, eglTerminate, (EGLDisplay dpy));
#endif /* !ANDROID_NDK */
    
    FNDEF(void, glBlendFunc, (GLenum sfactor, GLenum dfactor));
    FNDEF(void, glClear, (GLbitfield mask));
    FNDEF(void, glClearColorx, (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha));
    FNDEF(void, glColor4x, (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha));
    FNDEF(void, glColorPointer, (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer));
    FNDEF(void, glDisable, (GLenum cap));
    FNDEF(void, glDisableClientState, (GLenum array));
    FNDEF(void, glDrawArrays, (GLenum mode, GLint first, GLsizei count));
    FNDEF(void, glEnable, (GLenum cap));
    FNDEF(void, glEnableClientState, (GLenum array));
    FNDEF(void, glFrustumx, (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar));
    FNDEF(GLenum, glGetError, (void));
    FNDEF(void, glLightxv, (GLenum light, GLenum pname, const GLfixed *params));
    FNDEF(void, glLoadIdentity, (void));
    FNDEF(void, glMaterialx, (GLenum face, GLenum pname, GLfixed param));
    FNDEF(void, glMaterialxv, (GLenum face, GLenum pname, const GLfixed *params));
    FNDEF(void, glMatrixMode, (GLenum mode));
    FNDEF(void, glMultMatrixx, (const GLfixed *m));
    FNDEF(void, glNormalPointer, (GLenum type, GLsizei stride, const GLvoid *pointer));
    FNDEF(void, glPopMatrix, (void));
    FNDEF(void, glPushMatrix, (void));
    FNDEF(void, glRotatex, (GLfixed angle, GLfixed x, GLfixed y, GLfixed z));
    FNDEF(void, glScalex, (GLfixed x, GLfixed y, GLfixed z));
    FNDEF(void, glShadeModel, (GLenum mode));
    FNDEF(void, glTranslatex, (GLfixed x, GLfixed y, GLfixed z));
    FNDEF(void, glVertexPointer, (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer));
    FNDEF(void, glViewport, (GLint x, GLint y, GLsizei width, GLsizei height));
    
    
#undef FN
#define FNPTR(name) funcPtr_##name
    
#ifndef IMPORTGL_NO_FNPTR_DEFS
    
    // Redirect egl* and gl* function calls to funcPtr_egl* and funcPtr_gl*.
    
#ifndef ANDROID_NDK
#define eglChooseConfig         FNPTR(eglChooseConfig)
#define eglCreateContext        FNPTR(eglCreateContext)
#define eglCreateWindowSurface  FNPTR(eglCreateWindowSurface)
#define eglDestroyContext       FNPTR(eglDestroyContext)
#define eglDestroySurface       FNPTR(eglDestroySurface)
#define eglGetConfigAttrib      FNPTR(eglGetConfigAttrib)
#define eglGetConfigs           FNPTR(eglGetConfigs)
#define eglGetDisplay           FNPTR(eglGetDisplay)
#define eglGetError             FNPTR(eglGetError)
#define eglInitialize           FNPTR(eglInitialize)
#define eglMakeCurrent          FNPTR(eglMakeCurrent)
#define eglSwapBuffers          FNPTR(eglSwapBuffers)
#define eglTerminate            FNPTR(eglTerminate)
#endif /* !ANDROID_NDK */
    
#define glBlendFunc             FNPTR(glBlendFunc)
#define glClear                 FNPTR(glClear)
#define glClearColorx           FNPTR(glClearColorx)
#define glColor4x               FNPTR(glColor4x)
#define glColorPointer          FNPTR(glColorPointer)
#define glDisable               FNPTR(glDisable)
#define glDisableClientState    FNPTR(glDisableClientState)
#define glDrawArrays            FNPTR(glDrawArrays)
#define glEnable                FNPTR(glEnable)
#define glEnableClientState     FNPTR(glEnableClientState)
#define glFrustumx              FNPTR(glFrustumx)
#define glGetError              FNPTR(glGetError)
#define glLightxv               FNPTR(glLightxv)
#define glLoadIdentity          FNPTR(glLoadIdentity)
#define glMaterialx             FNPTR(glMaterialx)
#define glMaterialxv            FNPTR(glMaterialxv)
#define glMatrixMode            FNPTR(glMatrixMode)
#define glMultMatrixx           FNPTR(glMultMatrixx)
#define glNormalPointer         FNPTR(glNormalPointer)
#define glPopMatrix             FNPTR(glPopMatrix)
#define glPushMatrix            FNPTR(glPushMatrix)
#define glRotatex               FNPTR(glRotatex)
#define glScalex                FNPTR(glScalex)
#define glShadeModel            FNPTR(glShadeModel)
#define glTranslatex            FNPTR(glTranslatex)
#define glVertexPointer         FNPTR(glVertexPointer)
#define glViewport              FNPTR(glViewport)
    
#endif // !IMPORTGL_NO_FNPTR_DEFS
    
    
#endif // !DISABLE_IMPORTGL
    
    
#ifdef __cplusplus
}
#endif


#endif // !IMPORTGL_H_INCLUDED

////////////////////////////importgl.h

///////////////////#include "app.h"
#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
    
    extern void appInit(char*);
    extern void appDeinit();
    extern void appAccelerometerSz(char*);
    //extern void appRender(int accelX, int accelY, int accelZ);
    extern void    appRender(float tick, int width, int height, int accelX, int accelY, int accelZ);
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
///////////////////////////////////

//#include "CANDIDATE.h"
#include "../../../../../../SDKSRC/Base/cbaseV1_2.h"

#define CANDIDATE "../../../../../../Demos/PoppingTime/App.hpp"

#include CANDIDATE
//#include "../../../Apps/Planets/App.hpp"

#define RUN_LENGTH  (20 * CAMTRACK_LEN)
#undef PI
#define PI 3.1415926535897932f
#define RANDOM_UINT_MAX 65535

App game;  

// Capped conversion from float to fixed.
static long floatToFixed(float value)
{
    if (value < -32768) value = -32768;
    if (value > 32767) value = 32767;
    return (long)(value * 65536);
}

#define FIXED(value) floatToFixed(value)

char respath[256];

void appPushI(int command, int p1, int p2) { game.input.pushI(command,p1,p2);}
void appInit(char *sz) { 
	strcpy(respath, sz);
	game.Init(sz);
	
}
void appDeinit(){}

void* lastP1 = 0;
void* lastP2 = 0;
int lastI1 = 0;
int lastI2 = 0;

char filename[256];


short notified = 0;
char errsz[64];

int appPull() {
	PEG::CMD* a = game.output.pull();
	lastP1 = a->param1;
	lastP2 = a->param2;

	int ae = glGetError();
	if (ae) {
		if (!notified) {
			
			sprintf(errsz, "glError=%d", ae);
			//game.output.pushP(CMD_MSG, $ errsz, 0);
			notified = 1;
		}
	}
	
	if (a->command>=CMD_TEXSET0 && a->command<=CMD_TEXSET3) {
		
	//	game.rm.LoadTGA((TextureImage* )lastP2 , (char*)lastP1);
		
	}
	
	lastI1 = a->i1;
	lastI2 = a->i2;
	
	return a->command;
}

void* appP1() { return (void*)lastP1;}
void* appP2() { return (void*)lastP2;}

char* appSzlastP1() {
	return (char*)lastP1;
}

int appIntlastP1() {
	return lastI1;
}

int appIntlastP2() {
	return lastI2;
}


void appAccelerometerSz(char* accelValues) {

}

static void prepareFrame(int width, int height)
{
	
    glViewport(0, 0, width, height);
	
    glClearColorx((GLfixed)(0.0f * 65536),
                  (GLfixed)(0.0f * 65536),
                  (GLfixed)(0.0f * 65536), 0x10000);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aluPerspective(45, (float)width / (float)height, 0.05f, 150);
	
    glMatrixMode(GL_MODELVIEW);
	
    glLoadIdentity();
}


void appRender(float tick, int width, int height, int accelX, int accelY, int accelZ)
{
    tick = 1/30.0f;
    prepareFrame(width,height);
	if (accelX==0 && accelY==0 && accelZ==0) accelY = -9.8*100;
	game.Render(tick, accelX , accelY , accelZ );
	return;
}


//APPANDROID.C
#include <sys/time.h>
#include <time.h>
#include <android/log.h>
#include <stdint.h>
#include <stdio.h>

int   gAppAlive   = 1;

static int  sWindowWidth  = 320;
static int  sWindowHeight = 480;
static int  sDemoStopped  = 0;
static long sTimeOffset   = 0;
static int  sTimeOffsetInit = 0;
static long sTimeStopped  = 0;

static long
_getTime(void)
{
    struct timeval  now;
    
    gettimeofday(&now, NULL);
    return (long)(now.tv_sec*1000 + now.tv_usec/1000);
}

/* Call to initialize the graphics state */
void
Java_com_acnodelabs_apps_appwithcpp_feature_MainActivity_nativeInit( JNIEnv*  env , jobject thiz, jstring uri)
{
    importGLInit();
    // convert Java string to UTF-8
    const jbyte *utf8 = (*env)->GetStringUTFChars(env, uri, NULL);
    appInit(utf8);
    gAppAlive    = 1;
    sDemoStopped = 0;
    sTimeOffsetInit = 0;
    (*env)->ReleaseStringUTFChars(env, uri, utf8);
    
}

/* Call to initialize the graphics state */
int
Java_com_acnodelabs_apps_appwithcpp_feature_MainActivity_nativePull( JNIEnv*  env )
{
    int a = appPull();
    return a;
}

/* Call to initialize the graphics state */
jstring
Java_com_acnodelabs_apps_appwithcpp_feature_MainActivity_nativeSzP1( JNIEnv*  env)
{
    return (*env)->NewStringUTF(env, (const char *)appSzlastP1());
}

jint
Java_com_acnodelabs_apps_appwithcpp_feature_MainActivity_nativeIntP1( JNIEnv*  env)
{
    return appIntlastP1();
}
/* Call to initialize the graphics state */
jint
Java_com_acnodelabs_apps_appwithcpp_feature_MainActivity_nativeIntP2( JNIEnv*  env)
{
    return appIntlastP2();
}

/* Call to initialize the graphics state */
void
Java_com_acnodelabs_apps_appwithcpp_feature_MainActivity_nativePushI( JNIEnv*  env, jobject  thiz, jint cmd, jint x, jint y)
{
    appPushI(cmd,x,y);
}

void
Java_com_acnodelabs_apps_appwithcpp_feature_MainActivity_nativeResize( JNIEnv*  env, jobject  thiz, jint w, jint h )
{
    sWindowWidth  = w;
    sWindowHeight = h;
    __android_log_print(ANDROID_LOG_INFO, "AlgeApp", "resize w=%d h=%d", w, h);
}

/* Call to finalize the graphics state */
void
Java_com_acnodelabs_apps_appwithcpp_feature_MainActivity_nativeDone( JNIEnv*  env )
{
    appDeinit();
    importGLDeinit();
}

/* This is called to indicate to the render loop that it should
 * stop as soon as possible.
 */
void
Java_com_acnodelabs_apps_appwithcpp_feature_MainActivity_nativePause( JNIEnv*  env )
{
    sDemoStopped = !sDemoStopped;
    if (sDemoStopped) {
        /* we paused the animation, so store the current
         * time in sTimeStopped for future nativeRender calls */
        sTimeStopped = _getTime();
    } else {
        /* we resumed the animation, so adjust the time offset
         * to take care of the pause interval. */
        sTimeOffset -= _getTime() - sTimeStopped;
    }
}

/* Call to render the next GL frame */
void
Java_com_acnodelabs_apps_appwithcpp_feature_MainActivity_nativeRender( JNIEnv*  env, jobject  thiz, jint ax100, jint ay100, jint az100)
{
    long   curTime;
    
    /* NOTE: if sDemoStopped is TRUE, then we re-render the same frame
     *       on each iteration.
     */
    if (sDemoStopped) {
        curTime = sTimeStopped + sTimeOffset;
    } else {
        curTime = _getTime() + sTimeOffset;
        if (sTimeOffsetInit == 0) {
            sTimeOffsetInit = 1;
            sTimeOffset     = -curTime;
            curTime         = 0;
        }
    }
    
    //__android_log_print(ANDROID_LOG_INFO, "SanAngeles", "curTime=%ld", curTime);
    
    float accelX = ax100 / 100.0f;
    float accelY = ay100 / 100.0f;
    float accelZ = az100 / 100.0f;
    
    //sscanf(accelSz3, "%.2f,%.2f,%.2f", &accelX, &accelY, accelZ);
    //static char accelSz3[64];
    //sprintf(accelSz3, "%.2f,%.2f,%.2f", ax, ay, az);
    //appAccelerometerSz(accelSz3);
    appRender(curTime, sWindowWidth, sWindowHeight, ax100,ay100,az100);
    
}
