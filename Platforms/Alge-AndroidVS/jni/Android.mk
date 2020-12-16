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
    ../../../SDKSRC/Base/jpgd.cpp \
    ../../../../imgui\imgui.cpp \
    ../../../../imgui\imgui_draw.cpp \
    ../../../../imgui\imgui_widgets.cpp \
    ../../../../imgui\imgui_demo.cpp \
    imgui_impl_opengl2es.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Contacts/b2Contact.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2GearJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2Joint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/b2Body.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/b2ContactManager.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/b2Fixture.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/b2Island.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/b2World.cpp \
    # ../../../../Box2D/Box2D/Box2D/Dynamics/b2WorldCallbacks.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/Shapes/b2ChainShape.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/Shapes/b2CircleShape.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/Shapes/b2EdgeShape.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/Shapes/b2PolygonShape.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/b2BroadPhase.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/b2CollideCircle.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/b2CollideEdge.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/b2CollidePolygon.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/b2Collision.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/b2Distance.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/b2DynamicTree.cpp \
    # ../../../../Box2D/Box2D/Box2D/Collision/b2TimeOfImpact.cpp \
    # ../../../../Box2D/Box2D/Box2D/Common/b2BlockAllocator.cpp \
    # ../../../../Box2D/Box2D/Box2D/Common/b2Draw.cpp \
    # ../../../../Box2D/Box2D/Box2D/Common/b2Math.cpp \
    # ../../../../Box2D/Box2D/Box2D/Common/b2Settings.cpp \
    # ../../../../Box2D/Box2D/Box2D/Common/b2StackAllocator.cpp \
    # ../../../../Box2D/Box2D/Box2D/Common/b2Timer.cpp \

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
