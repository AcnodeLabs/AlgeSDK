## AlgeSDK: A Truly Native Crossplatform framework 

![alt text](https://raw.githubusercontent.com/AcnodeLabs/AlgeSDK/master/_acnode_/GetIt.PNG)
### **Get It, clone into your sandbox directory and do:** 

## Verified Desktop Environments 
Windows: Win10SDK_10.0.18362 on Visual Studio 2019 version 16.2 on Microsoft WIndows 10 Pro Build 18362
macOS:

## Basic Version (iOS, Win)
```sh
git clone https://github.com/AcnodeLabs/AlgeSDK.git
cd AlgeSDK
setup-deps [First Time Only, will pull ThirdParty Requirements]
KickStart  [run bat or sh script]
```
## Bleeding Edge (iOS, macOS, GNAT-macOS (Ada), Win, Android)
```sh
git clone -b develop https://github.com/AcnodeLabs/AlgeSDK.git
cd AlgeSDK
setup-deps [First Time Only, will pull ThirdParty Requirements]
KickStart  [run bat or sh script], Xcode may install additional components on macOS on first run
Note:- Box2D N/A on iOS for timebieng
```

### **Programming with ALGE Vanilla SDK**
### **Developing Platform Independent**
### **3D Graphics Applications**

AcnodeLabs (c)  2018

## Quick Start Guide

In this chapter you will plunge in Vanilla World and develop your first ALGE Application from scratch and deploy it on multiple devices using the ALGE SDK.

The ALGE Kit includes the following:

* Platform Templates
Your SDK includes Platform Templates or IDE project folders. These templates are meant to develop and port the Apps to the particular platform. Essentialy you may debug and develop your Apps (even iOS/OSX Apps) in MS Visual Studio. Or conversely you can develop your Windows Apps in XCode. You will get the hang of this idea progressively.

* Essential Includes
Every ALGE SDK App is required to include the core header file core CBase_<version>.h, this directory includes the requisite headers.

* Tools and Utilities
ALGE is not a full fledge game development engine however it provides basic tools to import and export assets. E.g Blender ALX export script is provided to export 3D Assets to ALX format , the ALX Viewer to view 3D assets. An olx2alx is also provided to convert community 3D models to alx. Images format used is uncompressed .TGA.

* Sample Apps
Many  Sample  Apps  are  provided  for  demonstration  and  for  your HelloWorldly  desires.  Any  one  of  these  Apps  can  be  used  as  a baseline of your App Idea thus avoiding writing boilerplate code.

* ThirdParty Extensions
The extensions as the name signifies extend the functionality available for you. e.g Physics Library like Bullet3D can be used as extension. A game engine like Irrichlit can also form an extension. Refer to Adrenaline zone on Alge website to share and find new extensions.

* Documentation
The standard documentation shipped with SDK in html, pdf or docx provided for reference and kickstarts. 

This book deals with introduction and kickstarts and would introduce the ALGE Paradigm of programming. So expect Shedding off some irrelevant styles and get ready to embrace vanilla coding.


## Installing the ALGE SDK

Visual Studio (Windows) , XCode (macOS, iOS),  Android Studio (android) and are the preferred development environments. 

The installation is pretty straightforward. Extract the package to your repository and you are good to Go. First step would be to use and Run existing provided Applications to get the idea of the Caps. Gather your devices, iPod touch, iPhone , Android Phone, iPad, Atom Notebook etc to automatically build an existing App from source. ALGE SDK Folder can be copied to another machine and would run as all paths are
relative. It also simplifies to zip your App Folder to backup all your work periodically. 


Under the platforms folder you can find IDE project templates. To take a start Lets compile and a defacto demo application �Lesson03�. In fact this is an Alge compatible port of Lesson03 of the defacto OpenGL tutorials of NeHe (original is found at http://nehe.gamedev.net). This App displays a colored rectangle and a colored Quad on the Screen. You would be glad that Lesson 01 and Lesson 02 are not required
as initialization of GL Context and window creating has already been catered for by ALGE framework. 


Check that you have properly configured iOS SDK and XCode IDE installed on your Mac. You can counter check it by creating and running standard OpenGL ES Template provided in XCode.

Coming to ALGE, In XCode open up the Project file (.xcodeproj) in provided in the Platforms/Alge-iPhone directory.

*Step#1 � Name your Project; in this case �Lesson03�.

*Step#2 � Name your Product; in this case �Lesson03�.

*Step#3 � Specify Resource Files; in this case SKIP THIS STEP as no resource files are required.

*Step#4 � Set Candidate

change
#define CANDIDATE "../../../Apps/APPNAME/App.hpp" to
#define CANDIDATE "../../../Apps/Lesson03/App.hpp"

Step#5 � Set Active Device Scheme and Run

You should see the XCode firing up the iOS Simulator and your First
Demo App is Running. 

Lets Generalize the Configuration Steps to Develop/Run/Port any App using XCode in four easy to remember steps.

Step A � Name your Project/ Product;
Step B � Add Resource files to Assets Folder; (described later) Step C � Set Candidate;
Step D � Select Scheme and Run. 

In Visual Studio open up the Solution Alge.sln. The default project contains a file name CANDIDATE.h that defines the App Directory of the Candidate Application. Edit CANDIDATE.h to point to Lesson03 App.hpp file as under. The Candidate.h header file serves two functions. Firstly it is used to include the App source at build time. And secondly at runtime it is used by SDK to extract the name of the application.

change
#define CANDIDATE "../../../Apps/APPNAME/App.hpp" to
#define CANDIDATE "../../../Apps/Lesson03/App.hpp"

The build tools of Alge SDK determine that you are interested in building Application class under Lesson03 folder that resides in Apps directory of SDK.

Hit Build> Clean, Rebuild All and Run. You will see the Demo App running in a 320x480 Win32 container Window.

Note:-

To specify a longer name of the Application eg �My First App� is defined by substituting underscores instead of spaces.

#define CANDIDATE �../../Apps/My_First_App/App.hpp�

## App Structure

The Application is a single file hpp containing class definitions and implementation. The main class name is App

e.g Contents of File AppName/App.hpp

//DEFINES

class App : public AlgeApp {
public:
}; 

The App is identified not by the name of class nor by its File name, it is identified by the Parent Folder in which the App.hpp resides. Another important convention to remember is that the App�s data files should reside in Data subfolder. E.g all icons, and resource files (or assets) would be placed in Data folder within the App folder. You may cross examine other sample apps (app==folder) to get a hold on this scheme. Here are few basic standard conventions:-

?         Every App Folder resides in Apps directory of SDK
?         Every App has a self contained Data folder
?	Every App is a encapsulated in a class named App contained in file App.hpp
?         App Folder name �IS THE� Apps Name

Getting used to these conventions is a good idea at the beginning to avoid confusions later.

Essential ALGE Variables Objects and Methods

The App class should contains few essential elements that are to be used as-is.

a.	Two PEG Objects input and output, for communicating with platform.
b.    Init Method Signature
c.    DeInit Method Signature
d.    Render Method Signature

These are the essential ingredients and may not be altered or modified else builds will fail.

Every App class is expected to contain public instances of class PEG named input and output. Your Application can read input messages queued for processing through the �input PEG� and send or request platform services through �output PEG�. PEG is not an acronym, it can be considered as a peg that joins items or a channel of communication of messages and associated data.

**IMPORTANT**:- Your App has one chance per message, if the queue is read and message is ignored, the message is removed the queue assuming you dont intend to act on it. 
The Init Method is called once the Platform is ready with OpenGL context and loading other preliminaries. The path in which the app can read and write data in a vanilla way is passed to you as a parameter. Simply put you can even use core C stdio functions on every platform using this path. This is also used to initialize the resource manger(s) in your application to read and write to assets.

The DeInit method is called before the App quits to give you an opportunity to deallocate any user objects and perform de-initialization of the App.

The Render method is called in a loop. This is the place where you have full control available to render in the OpenGL context, Normally you would be performing these blocks of operation.

(a)    processInput() You must Process the input queue to act upon messages.

*a.     Issue OpenGL Calls.

*b.   Anything other thing you would like to do, Update Animation and Physics Library etc.

Every render method is accompanied with a float elapsed time variable (in seconds) to be used for time based animation and also give you scaled raw accelerometer values for computing device orientation. .The elapsed time is provided in seconds, you can easily compute millis (if required)  by multiplying this value by 1000. The Seconds offer a more natural way to visualize your Animation code. Luckily, You are not required to setup anything in this regard, if the platform is supporting these features you will get these values by default.

## USER Variables, Objects and Methods

All your Application specific variables and objects can be defined and used within the class in the same hpp file. It is recommended that you restrict your Apps code in the same hpp file, you may use your own objects as a separate hpp code file and include in the App.hpp defines section, but still a better way is to write re-usable code is through the Extension Scheme of the SDK. You can use inner classes and avoid using class wizards that auto generate class file pairs of Cpp and h files one per class. If you are used to using C/C++ cpp and header files separately, consider making all reusable code as an Extension, and retain only the App specific code in the App.hpp File. 

## About Messaging and Commands

The Messaging scheme of ALGE is first come first serve, impermanent messages and a parameter pair Param1 and Param2. You would
find that though only two variables are used per message but they are sufficient to pass everything and they can also pass pointers to structures and objects. For most of the Commands only one Parameter is good enough.

IMPORTANT:- Ensure that passing pointer addresses are pointing to
valid memory location that should not go out of scope until the message is processed.

Every Message is expected to be sent as

MessageID,Param1,Param2
Message ID�s are Constant integer defines in Commands.h Header files. E.g To send a message to play a sound these two messages are used
CMD_SNDSET and CMD_SNDPLAY. These are called as under
output.pushP(CMD_SNDSET ,$ �MySong.mp3�, 0);
output.pushP(CMD_SNDPLAY,$ �MySong.mp3�, 0);

CMD_SNDSET is generally required to be called once in your init method.

And CMD_SNDPLAY message is sent whenever you would like to play the sound file e.g on a particular event.

e.g consider the following code to play a mp3 file over a blank screen:-

1.    #include �../../Base/CBaseXX.h�
2.    class App : public AlgeApp {
3.          public:
4.                PEG input, output;
5.          void Init(char *path) {
6.                output.pushP(CMD_SNDSET0,$ �MySong.mp3�,0);
7.                output.pushP(CMD_SNDPLAY0,NOPARAMS); 
8.          }
9.          void DeInit() {}
10.         void Render(float sec, int aX, int aY, int aZ)() {}
11.   };

That�s Everything you need to do to play your wave file irrespective of Platform!!. The same code will be valid for iPhone, OSX, Windows, Android and others.

Lets revisit some characteristics of the this 11 line APPLICATION.

1.           It uses Core Command defines and utility functions.
2.           Define everything your app does is within your class App.
3.	It only includes the essentials, except Line 6,7 concerning sound, each and every line is �Essential�.
4.	You would be encountering the remaining 9 lines in each and every ALGE App.
5.	In essence you are just concerned about specifying a sound file and playing in a �Vanilla Way�

## Give it a �Push� !!

You can push and pull messages from the PEGs, pushP is used for parameters of type POINTER; After all the file name is a const char*, Also $ is a helper define that means ((void*)(char*)) cast.

The PEG Objects also include another variant to support integer values, thru call pushI , if u need to pass Integer parameters.

The commands are equivalent:-
output.pushI(CMD_COMMAND, 12, 13);        // pass as integer
or
int p1 =  12;
int p2 =  13;

output.pushP(CMD_COMMAND, &p1, &p2);      // pass pointers to integers

you can use pull commands to read inputs to you app

PEG::CMD* cmd = input.pull();
int width, height;
If (cmd->command==CMD_SCREENSIZE) {
width = cmd->i1; height = cmd->i2;
} 
It is highly recommended to separate the input processing in a separate function as seen in examples processInput() that is executed once or less in every render call e.g.

class App {

public:
PEG input, output

void processInput() {
PEG::CMD* cmd = input.pull();
int width, height;
If (cmd->command==CMD_TOUCHMOVE) {
x = cmd->i1; y = cmd->i2;
}
If (cmd->command==CMD_SCREENSIZE) {
width = cmd->i1; height = cmd->i2;
}
}

void DeInit() {}
void Render(..) {
processInput();
// Other Rendering calls
}

};//~App

Lets Return to 3D Graphics
===========================
Now its time to break the Good News!!

**ALGE is mainly intended for loop structured 3D graphics applications.

**Init Method is called after platform specific OpenGL context and window creation. The Init is for the init gl calls concerning your App. So you can start issuing GL calls right away.

**Render method provides you maximum opportunity to draw your stuff and run app logic, the moment ALGE code gets execution handle it processes your output queue acts on all pending commands and again re-enters your Render function with a time elapsed variable.

**The FPS is not restricted to a fixed value, rather you get elapsed time variable to perform frame rate independent animations. Essentially this elapsed time is equivalent to 
processing time of all pending ALGE output queue messages and re-entry in render loop

**DeInit provides you the last opportunity to de-init your objects and allocation before exit.

## Extensions

The extensions provide a way to incorporate additional functionality to the SDK. The extensions are also by nature vanilla in way that they only contain classes or closely related functions for ease of use or to hide complexity of the code. The user includes and source is packaged in a folder without any outside dependencies however an extension parent folder can include other files relative to the root folder. The extension folder may also contain helper classes for ease of use. The purpose of extension scheme is to provide a mechanism to reuse existing vanilla sources. These packages could easily be shared or reused for different applications.

# Happy Coding !!

do start %SDK_ROOT%
rename tools to tools1
rename platform-tools to platform-tools1
Download Tools from google (tools_r22.0.5-windows) Repository extract to %SDK_ROOT% (i.e tools)
Download Platform-Tools (platform-tools_r22-windows) from google Repository (see wget entry in setup-deps)
Change line containing zipalign version number as per the installed directrory in build-andrroid.bat
make sure ANT_HOME is set also

Developer Notes:-
To build cnats on a (Apple M1) use this:-
cmake -G Xcode .. -DNATS_BUILD_WITH_TLS=OFF -DNATS_BUILD_STREAMING=OFF 
It will generate xcode project to build cnats static lib

