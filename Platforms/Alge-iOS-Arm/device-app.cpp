#define XCODE_BUILD
#define IOS

#ifdef IOS
#define NO_NATS
#define ES_ONLY
#define NO_FONTLIB
#define GLES_SILENCE_DEPRECATION
#endif

#include "../../../AlgeSDK/SDKSRC/Base/deviceapp.cpp"
