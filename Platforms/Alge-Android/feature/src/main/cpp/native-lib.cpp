#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring

JNICALL
Java_com_acnodelabs_apps_untitled_feature_MainActivity_stringFromJNI( JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++ XAL";
    return env->NewStringUTF(hello.c_str());
}
