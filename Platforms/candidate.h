// Edit here to point to AlgeSDK based cross platform Candidate Application 
// App Folder should Match ProjectName in Solution Explorer

//For ease of Development Common.Assets/Data is added in the Project Build Phase [mac], so
//if a new app is added of new asset is added, modify and run collect.sh in app directory once after adding assets, this will also copy the Data of the App to Common.Assets/Data, in Production Use Original App.Assets folder instead of Common.Assets

#define ALGEAPPNAME "AlgeApp"

//TODO:: move above line elsewhere

#include "../Apps/planets/App.hpp"

