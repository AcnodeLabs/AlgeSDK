#!/bin/bash
cd ../Alge-Gnat-macOS/
gprclean Untitled.gpr
clear
gprbuild Untitled.gpr
cp obj/algegnatmac ../Spawner-macOS/Planets
cp -r obj/algegnatmac.app ../Spawner-macOS/Planets.app
cd ../Spawner-macOS/
echo CodeSigning
sh sign.sh
echo Generating Icons
sh icons.sh
cp MyIcon.icns planetsplus/MyIcon.icns
echo Pl Rebuild SolarSystemPlanets3D Application
open SolarSystemPlanets3D.xcodeproj
cd ../Alge-Ada-VSCode/
