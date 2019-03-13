"# AlgeGnat" 
Building Ada Based OSX Map

1) run GPS /usr/local/bin/gps
2) open xalgit/AlgeSDK/Platforms/Alge-Gnat-Mac/Untitled.gpr
3) rebuild the project - this will produce obj/planetsada binary
4) make directory ../PlanetsAda.app/Data with referenct to it copy data files in it and run planetsada.bin


Notes:-

following are necessary files:

- Alge-Gnat-Mac and Alge-OSX Platform Folder
- com_acnodelabs and AlgeSDK folder in XALGIT
- SDKSRC/Base/Ada folder
- Lesson03 based App.cpp in com_acnodelabs/PlanetsADA Folder
-  rename planetsada to Planets to let it work in spawner
