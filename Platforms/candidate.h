
//				▌║█║▌│║▌│║▌║▌█║Welcome !! ▌│║▌║▌│║║▌█║▌║█

// Tip: Bookmark this file CANDIDATE.h for specifying App to build
// Available AddOns:-
// Windows          - CORE+BOX2D+IMGUI+FMOD+NATS
// macOS Intel      - CORE+BOX2D+IMGUI+FMOD+GNAT
// macOS Silicon    - CORE+BOX2D+IMGUI+FMOD
// iOS,ipadOS       - CORE+BOX2D+IMGUI+FMOD
// Android          - CORE+BOX2D

// Edit here to point to AlgeSDK based cross platform Candidate Application 
// ALGEAPPNAME will be name of Target in Mac, in Windows it is defined by ProjectName  
#define ALGEAPPNAME "AlgeApp" //Should Match with Product .app or .exe name
//Only use 1 ref in candidate.h else name picking will fail
#include "../Apps/XGui/App.hpp"
// The Canditate to build is referenced above:-
// For uncluttered workspace 'Do "Close All but this" canditdate.h' and Right Click and Open the file referenced below,
// Some Samples are XGui, DodgeTheCreeps, PoppingTime, Juices, Ivank_Box2D, Planets

//For ease of Development Common.Assets/Data is added in the Project Build Phase [mac], so
//if a new app is added of new asset is added, modify and run collect.sh in app directory once after adding assets, this will also copy the Data of the App to Common.Assets/Data, in Production Use Original App.Assets folder instead of Common.Assets
