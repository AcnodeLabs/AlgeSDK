#define XCODE_BUILD
#define IOS

#ifdef IOS
#define NO_NATS
#define ES_ONLY
#define NO_FONTLIB
#define GLES_SILENCE_DEPRECATION
#define NO_FMOD //For Simulator Only, Check Sound on Actual Device Using Alge-iOS-Arm Platform
#endif

#include "../../../AlgeSDK/SDKSRC/Base/deviceapp.cpp"
