TARGET_PLATFORM := android-16
ROOT_PATH := $(call my-dir)

include $(CLEAR_VARS)

    # ../../../../imgui\imgui.cpp \
    # ../../../../imgui\imgui_draw.cpp \
    # ../../../../imgui\imgui_widgets.cpp \
    # ../../../../imgui\imgui_demo.cpp \
    # imgui_impl_opengl2es.cpp \

LOCAL_MODULE     := alge_app
LOCAL_ARM_MODE   := arm
LOCAL_PATH       := $(ROOT_PATH)
LOCAL_SRC_FILES  := LOCAL_SRC_FILES  := importgl.c \
    device-app.cpp \
    app-android.c \
    ../../../SDKSRC/Base/camera.cpp \
    ../../../SDKSRC/Base/jpgd.cpp \
    Box2D.cpp \

LOCAL_CFLAGS     := -std=c17 -DANDROID_NDK -DDISABLE_IMPORTGL -Wno-pointer-sign -Wno-nonportable-include-path -Wno-implicit-function-declaration -Wpointer-sign
LOCAL_CPPFLAGS     := -std=c++17 -DANDROID_NDK -DDISABLE_IMPORTGL -Wno-pointer-sign -Wno-nonportable-include-path -Wno-implicit-function-declaration -Wpointer-sign
LOCAL_LDLIBS     := -lGLESv1_CM -ldl -llog -Wl,-s
LOCAL_CPP_FEATURES += exceptions
APP_CPPFLAGS += -std=c++17
LOCAL_C_INCLUDES += jni/../../../../Box2D/Box2D
LOCAL_C_INCLUDES += ../../../../imgui
LOCAL_C_INCLUDES += ../../../../../imgui
LOCAL_C_INCLUDES += ../../../../../../imgui
LOCAL_C_INCLUDES += ../../../imgui

include $(BUILD_SHARED_LIBRARY)
