/* San Angeles Observation OpenGL ES version example
 * Copyright 2009 The Android Open Source Project
 * All rights reserved.
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
 */
#include <jni.h>
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



/* Call to initialize the graphics state */
void
Java_com_acnodelabs_alge_DemoRenderer_nativeInit( JNIEnv*  env , jobject thiz, jstring _s)
{
    importGLInit();
	// convert Java string to UTF-8
    //const jbyte *utf8 = (jbyte*)(*env)->GetStringUTFChars(env, uri, NULL);
    //const char *utf8 = (*env)->GetStringUTFChars(env,uri, NULL);

    //https://stackoverflow.com/questions/32205446/getting-true-utf-8-characters-in-java-jni
    const jclass stringClass = (*env)->GetObjectClass(env, _s);
    const jmethodID getBytes = (*env)->GetMethodID(env, stringClass, "getBytes", "(Ljava/lang/String;)[B");

    const jstring charsetName = (*env)->NewStringUTF(env, "UTF-8");
    const jbyteArray stringJbytes = (jbyteArray) (*env)->CallObjectMethod(env, _s, getBytes, charsetName);
    (*env)->DeleteLocalRef(env, charsetName);

    const jsize length = (*env)->GetArrayLength(env, stringJbytes);
    const jbyte* pBytes = (*env)->GetByteArrayElements(env, stringJbytes, NULL); 

    //for (int i = 0; i < length; ++i)
   //     fprintf(stderr, "%d: %02x\n", i, pBytes[i]);

    (*env)->ReleaseByteArrayElements(env, stringJbytes, pBytes, JNI_ABORT); 
    (*env)->DeleteLocalRef(env, stringJbytes);



    appInit(pBytes);
    gAppAlive    = 1;
    sDemoStopped = 0;
    sTimeOffsetInit = 0;
	//(*env)->ReleaseStringUTFChars(env, uri, (const char*)utf8);
	
}

/* Call to initialize the graphics state */
int
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativePull( JNIEnv*  env )
{
	int a = appPull();
	return a;
}

/* Call to initialize the graphics state */
jstring
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativeSzP1( JNIEnv*  env)
{
	return (*env)->NewStringUTF(env, (const char *)appSzlastP1());
}

jint
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativeIntP1( JNIEnv*  env)
{
	return appIntlastP1();
}
/* Call to initialize the graphics state */
jint
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativeIntP2( JNIEnv*  env)
{
	return appIntlastP2();
}

/* Call to initialize the graphics state */
void
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativePushI( JNIEnv*  env, jobject  thiz, jint cmd, jint x, jint y)
{
	appPushI(cmd,x,y);
}

void
Java_com_acnodelabs_alge_DemoRenderer_nativeResize( JNIEnv*  env, jobject  thiz, jint w, jint h )
{
    sWindowWidth  = w;
    sWindowHeight = h;
    __android_log_print(ANDROID_LOG_INFO, "AlgeApp", "resize w=%d h=%d", w, h);
}

/* Call to finalize the graphics state */
void
Java_com_acnodelabs_alge_DemoRenderer_nativeDone( JNIEnv*  env )
{
    appDeinit();
    importGLDeinit();
}

/* This is called to indicate to the render loop that it should
 * stop as soon as possible.
 */
void
Java_com_acnodelabs_alge_DemoGLSurfaceView_nativePause( JNIEnv*  env )
{
    sDemoStopped = !sDemoStopped;
    if (sDemoStopped) {
        /* we paused the animation, so store the current
         * time in sTimeStopped for future nativeRender calls */
 //       sTimeStopped = _getTime();
    } else {
        /* we resumed the animation, so adjust the time offset
         * to take care of the pause interval. */
  //      sTimeOffset -= _getTime() - sTimeStopped;
    }
}

static float _getElapsedTime() {
    static float OldTime = 0;
    struct timeval  now;
    gettimeofday(&now, NULL);
    int seconds = ((int)now.tv_sec);
    int microseconds = ((int)now.tv_usec);
    float time = microseconds / 1000.0;
    float elapsed = time - OldTime;
    if (elapsed<=0) elapsed = 0.0166666667;
    OldTime = time;
    return elapsed;
}

/* Call to render the next GL frame */
void
Java_com_acnodelabs_alge_DemoRenderer_nativeRender( JNIEnv*  env, jobject  thiz, jint ax100, jint ay100, jint az100)
{
	float accelX = ax100 / 100.0f;
	float accelY = ay100 / 100.0f;
	float accelZ = az100 / 100.0f;
	
   int ielapsed = _getElapsedTime() * 1E6 / 1E3;
   // if (sDemoStopped) elapsed = 0;
	appRenderJ( ielapsed, sWindowWidth, sWindowHeight, ax100,ay100,az100);

}
