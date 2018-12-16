TARGET_PLATFORM := android-4
ROOT_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE     := alge_app
LOCAL_ARM_MODE   := arm
LOCAL_PATH       := $(ROOT_PATH)
LOCAL_SRC_FILES  := importgl.c \
    device-app.cpp \
    app-android.c \
    ../../../SDKSRC/Base/camera.cpp \

LOCAL_CFLAGS     := -DANDROID_NDK -DDISABLE_IMPORTGL -Wnonportable-include-path -Wimplicit-function-declaration -Wpointer-sign
LOCAL_CPPFLAGS     := -DANDROID_NDK -DDISABLE_IMPORTGL -Wnonportable-include-path -Wimplicit-function-declaration -Wpointer-sign
LOCAL_LDLIBS     := -lGLESv1_CM -ldl -llog -Wl,-s


include $(BUILD_SHARED_LIBRARY)
