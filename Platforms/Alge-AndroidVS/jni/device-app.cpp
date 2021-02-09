#undef ANDROID
#define ANDROID
#ifdef ANDROID
#define NO_FONTLIB
#define NO_IMGUI
#define NO_FMOD
#endif

#include "../../../../AlgeSDK/SDKSRC/Base/deviceapp.cpp"
