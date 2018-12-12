TARGET_PLATFORM := android-16
ROOT_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE     := alge_app
LOCAL_ARM_MODE   := arm
LOCAL_PATH       := $(ROOT_PATH)
LOCAL_SRC_FILES  := importgl.c \
    device-app.cpp \
    app-android.c \
    ../../../SDKSRC/Base/camera.cpp \

LOCAL_CFLAGS     := -std=c17 -DANDROID_NDK -DDISABLE_IMPORTGL -Wno-pointer-sign -Wno-nonportable-include-path -Wno-implicit-function-declaration -Wpointer-sign
LOCAL_CPPFLAGS     := -std=c++17 -DANDROID_NDK -DDISABLE_IMPORTGL -Wno-pointer-sign -Wno-nonportable-include-path -Wno-implicit-function-declaration -Wpointer-sign
LOCAL_LDLIBS     := -lGLESv1_CM -ldl -llog -Wl,-s
APP_CPPFLAGS += -std=c++17

include $(BUILD_SHARED_LIBRARY)
