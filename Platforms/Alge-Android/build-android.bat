cls
set JAVA_HOME="C:\Program Files (x86)\Java\jdk1.8.0_181"
set NDK_ROOT="C:\android-ndk-r18b"
set SDK_ROOT="C:\Program Files (x86)\Android\android-sdk"
set ANT_EXE="c:\apache-ant\apache-ant-1.10.5\bin\ant"

set PACKAGE=%1
set APPNAME=%2
set VERSION=%3
set SDKVER=%4
set ORIENT=%5



echo ------------------ SLATE CLEAN
%SDK_ROOT%\platform-tools\adb uninstall %PACKAGE%
del assets\*.*
del bin\%APPNAME%*.apk

echo ------------------ COPYING APP ASSETS
cd assets
copy /Y ..\..\..\Apps\%APPNAME%.Assets\Data\* .
copy icon.png ..\res\drawable-ldpi
cd ..

echo ------------------ CONFIGURING NATIVE BUILD
set USERSRC=%PACKAGE:.=\%
cd src
mkdir %USERSRC%
cd ..
echo CHECK %USERSRC%
copy jni\CANDIDATE.h jni\CAND.h
del jni\CANDIDATE.h

del AndroidManifest.xml
cfgdroid.exe %PACKAGE% %APPNAME% %VERSION% %SDKVER% %ORIENT% > AndroidManifest.xml
copy jni\CAND.h jni\CANDIDATE.h
del jni\CAND.h

echo ------------------ COMPILING NATIVE CODES
call %NDK_ROOT%\ndk-build clean
call %NDK_ROOT%\ndk-build
echo ------------------- BUILDING JAVA PORTION
echo ----removing junk 
del res\.DS_*
del assets\.DS_*
del res\drawable-ldpi\.DS_*
echo ---- compiling java files in src folder
cd src/com/acnodelabs/alge
%JAVA_HOME%\bin\javac -classpath /Users/bilal/Library/Android/sdk/platforms/android-27/android.jar *.java
cd ../../../..
echo --- generating new ant build.xml
del build.xml
%SDK_ROOT%\tools\android update project --target android-27 --path .
echo --- generating apk 
%ANT_EXE% -q release
echo ------------------- SIGNING
del bin\$2.apk
%JAVA_HOME%\bin\jarsigner -verbose -keystore %userprofile%\algeandroidapps.keystore bin/$2-release-unsigned.apk alge
%SDK_ROOT%\build-tools\25.0.3\zipalign -v 4 bin\$2-release-unsigned.apk bin\$2.apk
echo Good Luck !!
del %USERSRC\$2.java
echo install check 

%SDK_ROOT%\platform-tools\adb install bin\$2.apk
echo Check App on your Device
