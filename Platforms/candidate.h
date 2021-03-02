//				▌║█║▌│║▌│║▌║▌█║Welcome !! ▌│║▌║▌│║║▌█║▌║█

// Tip: Bookmark this file CANDIDATE.h for specifying App to build
// Available AddOns:-
// Windows          - CORE+BOX2D+IMGUI+FMOD+NATS
// macOS            - CORE+BOX2D+IMGUI+FMOD+GNAT
// iOS,ipadOS       - CORE+BOX2D+IMGUI+FMOD
// Android          - CORE+BOX2D

// Edit here to point to AlgeSDK based cross platform Candidate Application 
// ALGEAPPNAME will be name of Target in Mac, in Windows it is defined by ProjectName  
#define ALGEAPPNAME "AlgeApp"

// The Canditate to build is referenced below:-
// For uncluttered workspace 'Do Close All but canditdate.h' and Right Click and Open the file referenced below
#include "../XalApps/VehIsb/App.hpp"

//For ease of Development Common.Assets/Data is added in the Project Build Phase [mac], so
//if a new app is added of new asset is added, modify and run collect.sh in app directory once after adding assets, this will also copy the Data of the App to Common.Assets/Data, in Production Use Original App.Assets folder instead of Common.Assets




