#!/bin/bash

#For ease of Development Common.Assets/Data is added in the Project Build Phase [mac], so
#if a new app is added of new asset is added, modify and run collect.sh in app directory once after adding assets, this will also copy the Data of the App to Common.Assets/Data, in Production Use Original App.Assets folder instead of Common.Assets

MyApps="Brochures DemoCoverFlow DodgeTheCreeps Ivank_Box2D JapCarBrochures Juices LevelSelect NeheLesson05 NeheLesson09 NeheLesson19 Planets PoppingTime XFs XGui"
for app in $MyApps; do
   cp -v $app.Assets/Data/* COMMON.Assets/Data
done
