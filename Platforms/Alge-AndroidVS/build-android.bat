cls
@echo off
echo JAVA_HOME=%JAVA_HOME%
echo NDK_ROOT=%NDK_ROOT%
echo SDK_ROOT=%SDK_ROOT%
echo ANT_HOME=%ANT_HOME%
set ANT_EXE=%ANT_HOME%\bin\ant
set KEYSTORE_FILE=C:\algeandroidapps.keystore
set KEYSTORE_USERNAME=bilal
echo KEYSTORE_FILE=%KEYSTORE_FILE% with alias-name=%KEYSTORE_USERNAME%   [generated by keytool command of javasdk]

set PACKAGEQ=%1
set PACKAGE=%PACKAGEQ:"=%
echo PACKAGE=%PACKAGE%
set APPNAMEQ=%2
set APPNAME=%APPNAMEQ:"=%
echo APPNAME=%APPNAME%
set VERSION=%3
echo VERSION=%VERSION%
set SDKVER=%4
echo SDKVER=%SDKVER%
set ORIENT=%5
echo ORIENT=%ORIENT%
set PASSW=%6

rem type jni\CANDIDATE.h
echo [1] Checking .. src\%PACKAGE:.=\%\%APPNAME%.java

set GLUEDIR=src\%PACKAGE:.=\%\
echo [2] Will make ... %GLUEDIR%  

set /p var=Pl Check above info/variables are set Properly, Ensure Device is Connected and Unlocked, Continue as per above?[y/n]: 
if not %var%==y exit /B

mkdir %GLUEDIR%
set PWD=%cd%
cd %GLUEDIR%

set GLUECODE=package %PACKAGE%; public class %APPNAME% extends com.acnodelabs.alge.BaseActivity{}
echo [3] Writing .. Gluecode in %APPNAME%.java
echo %GLUECODE% > %APPNAME%.java
rem del /Q 1.java
echo cd %PWD%
cd %PWD%

echo [5] src\%PACKAGE:.=\%\%APPNAME%.java
type src\%PACKAGE:.=\%\%APPNAME%.java
echo [6] ...


echo [7] ------------------ SLATE CLEAN --- Cleaning up src\..\assets directory
del /Q assets\*.*

echo [8] ------------------ COPYING APP ASSETS
cd assets
echo [8.1] copying from ..\..\..\Apps\%APPNAME%.Assets\Data\ to jni\..\assets 
copy /Y ..\..\..\Apps\%APPNAME%.Assets\Data\* .
copy icon.png ..\res\drawable-ldpi
cd ..

echo [9] ------------------ CONFIGURING NATIVE BUILD
set USERSRC=%PACKAGE:.=\%
cd src
mkdir %USERSRC%
cd ..
echo [10] CHECK %USERSRC%
rem copy jni\CANDIDATE.h jni\CAND.h
rem del jni\CANDIDATE.h

cd Platforms\Alge-AndroidVS

del AndroidManifest.xml
echo [11] %cd%\cfgdroid.exe %PACKAGE% %APPNAME% %VERSION% %SDKVER% %ORIENT% generated AndroidManifest.xml
cfgdroid.exe %PACKAGE% %APPNAME% %VERSION% %SDKVER% %ORIENT% > AndroidManifest.xml
rem goto endz
rem copy jni\CAND.h jni\CANDIDATE.h
rem del jni\CAND.h

echo [12] ------------------ COMPILING NATIVE CODES
call %NDK_ROOT%\ndk-build clean
call %NDK_ROOT%\ndk-build
echo [13] ------------------- BUILDING JAVA PORTION
echo [14] ---- compiling java files in src folder
cd src/com/acnodelabs/alge
echo %cd%
echo [15] javac -classpath %SDK_ROOT%\platforms\android-27\android.jar *.java
call javac -classpath %SDK_ROOT%\platforms\android-27\android.jar *.java
cd ../../../..
echo [16] --- generating new ant build.xml
del build.xml
call %SDK_ROOT%\tools\android update project --target android-27 --path .
echo [17] --- generating apk 
call %ANT_EXE% -q release
del /Q bin\%APPNAME%.apk
echo [18] ------------------- SIGNING
echo [19] jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore %KEYSTORE_FILE% bin\%APPNAME%-release-unsigned.apk %KEYSTORE_USERNAME% -keypass %PASSW%
call jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore %KEYSTORE_FILE% bin\%APPNAME%-release-unsigned.apk %KEYSTORE_USERNAME% -storepass %PASSW% -keypass %PASSW%
echo [20] %SDK_ROOT%\build-tools\29.0.2\zipalign -v 4 bin\%APPNAME%-release-unsigned.apk bin\%APPNAME%.apk
call %SDK_ROOT%\build-tools\28.0.3\zipalign -v 4 bin\%APPNAME%-release-unsigned.apk bin\%APPNAME%.apk
%SDK_ROOT%\platform-tools\adb uninstall %PACKAGE%
echo [21] Deploying...
%SDK_ROOT%\platform-tools\adb install bin\%APPNAME%.apk
%SDK_ROOT%\platform-tools\adb shell am start -n %PACKAGE%/.%APPNAME%

endz:
echo [22] Check App on your Device
