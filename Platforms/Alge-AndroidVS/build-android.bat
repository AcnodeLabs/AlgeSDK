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

set PACKAGE=%1
echo PACKAGE=%PACKAGE%
set APPNAME=%2
echo APPNAME=%APPNAME%
set VERSION=%3
echo VERSION=%VERSION%
set SDKVER=%4
echo SDKVER=%SDKVER%
set ORIENT=%5
echo ORIENT=%ORIENT%

type jni\CANDIDATE.h
echo Checking .. src\%PACKAGE:.=\%\%APPNAME%.java

set GLUEDIR=src\%PACKAGE:.=\%\
echo Making ... %GLUEDIR%  
mkdir %GLUEDIR%
set PWD=%cd%
cd %GLUEDIR%

set GLUECODE=package %PACKAGE%; public class %APPNAME% extends com.acnodelabs.alge.BaseActivity{}
echo Writing .. Gluecode in %APPNAME%.java
echo %GLUECODE% > %APPNAME%.java
echo cd %PWD%
cd %PWD%

echo src\%PACKAGE:.=\%\%APPNAME%.java
type src\%PACKAGE:.=\%\%APPNAME%.java
echo ...
set /p var=Pl Check above info/variables are set Properly, Continue as per above?[y/n]: 
if not %var%==y exit /B

echo ------------------ SLATE CLEAN
%SDK_ROOT%\platform-tools\adb uninstall %PACKAGE%
del assets\*.jpg
del assets\*.png
del assets\*.alx
del assets\*.tga
del assets\*.wav
del assets\*.mp3

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
echo ---- compiling java files in src folder
cd src/com/acnodelabs/alge
call javac -classpath %SDK_ROOT%\platforms\android-27\android.jar *.java
cd ../../../..
echo --- generating new ant build.xml
del build.xml
call %SDK_ROOT%\tools\android update project --target android-27 --path .
echo --- generating apk 
call %ANT_EXE% -q release
del bin\%APPNAME%.apk
echo ------------------- SIGNING
call jarsigner -verbose -keystore %KEYSTORE_FILE% bin\%APPNAME%-release-unsigned.apk %KEYSTORE_USERNAME%
call %SDK_ROOT%\build-tools\25.0.3\zipalign -v 4 bin\%APPNAME%-release-unsigned.apk bin\%APPNAME%.apk
echo Good Luck !!
echo install check 

%SDK_ROOT%\platform-tools\adb install bin\%APPNAME%.apk
echo Check App on your Device
