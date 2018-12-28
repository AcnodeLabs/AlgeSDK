////////// Requires AlgeSDK and Candidate App code to Operate

#include <WinSock2.h>
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <Windowsx.h>
#include "resource.h"
#include <winerror.h>
#pragma comment(lib, "comctl32.lib")
#include  <commctrl.h>
#define CBASE "../../../AlgeSDK/SDKSRC/Base/CBaseV1_2.h"
#include CBASE 
#include "CANDIDATE.h"
#include "Timer.h"
#include <stdio.h>



char ResPath[256];

extern void(*callBackIn)(string);

CNetMsg netmsg;

CFTFont font;

App		game;
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application
FILE* a;

#ifdef USING_IRRLICHT
MyIrrHello ir;
#endif

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
BOOL    CALLBACK  DlgProc(HWND, UINT, WPARAM, LPARAM) ;

HWND hToast ;
HWND hAccel ;

float aX;
float aY;
float aZ;
float lastTime;
Timer time1;

char msg[128];

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}
#ifndef USING_IRRLICHT
	glViewport(0,0,width,height);						// Reset The Current Viewport
#endif

	game.input.pushI(CMD_SCREENSIZE, width , height);
	sprintf(msg, "ScreenSize(%d,%d)", width, height);
	if (game.verbosity_lmh == 'h') netmsg.Post(string(msg));
#ifndef USING_IRRLICHT
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.001f,10000.0f);
	//glOrtho(0, width, height, 0, 0, -100);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
#endif

}



int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	game.Init0(ResPath+1,'W');
	ReSizeGLScene(game.getBackgroundSize().x, game.getBackgroundSize().y);
	return TRUE;										// Initialization Went OK
}

char soundfiles[16][128];
float deltaT;

//for mnouse reposition
double r_mouse;
POINT p_mouse;
POINT pn_mouse;

void UpdateMouse(float deltaT) {
	
	if (r_mouse > 2.0) r_mouse = 2.0;
	if (r_mouse >= 1.0) return;
	r_mouse += deltaT;
	static CAnimator can;
	p_mouse.x = int(can.LinearTween(r_mouse, p_mouse.x, pn_mouse.x));
	p_mouse.y = int(can.LinearTween(r_mouse, p_mouse.y, pn_mouse.y));
	SetCursorPos(p_mouse.x, p_mouse.y);
	ShowCursor(true);
}
//////////////////////~~ Mouse reposition

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	static char fullres[64];
	game.edit = false;


	float newTime = time1.getElapsedTimeInSec();
	deltaT =  newTime - lastTime;
	if (aX==0 && aY==0 && aZ==0) aY=-9.8*100;
	//deltaT = 0.1;

#ifdef USING_IRRLICHT
		ir.driver->beginScene(true, true, SColor(255,100,101,140));
		game.Render(deltaT, aX,aY,aZ);
		ir.smgr->drawAll();
		ir.guienv->drawAll();
		ir.driver->endScene();
	#else
		
	if (game.nGobs > 0) {
		UpdateMouse(deltaT);
		game.Render(deltaT, aX, aY, aZ);
	}
	

#endif
	

	lastTime = newTime;

	int command = -1;
	while (command != 0) {
		command = game.output.pull()->command;
		void* p1 = game.output.pulled_param1;
		void* p2 = game.output.pulled_param2;

		//	int port;

		if (command == CMD_TOAST) {
			SetWindowTextA(GetDlgItem(hToast, IDC_EDIT1), (LPCSTR)p1);
			ShowWindow(hToast, SW_SHOW);
			DlgProc(hToast, CMD_TOAST, CMD_TOAST, CMD_TOAST);
		}

		if (command == CMD_MOUSE_REPOSITION) {
			GetCursorPos(&p_mouse);
			r_mouse = 0;
			pn_mouse.x = game.output.pulled_i1;
			pn_mouse.y = game.output.pulled_i2;
		}

		if (command == CMD_SPAWN) {
			ShellExecuteA(hWnd, "open", (LPCSTR)p1, "", "C:\\", SW_SHOWNORMAL);
		}

		if (command == CMD_MSG) {
			MessageBoxA(hWnd, (LPCSTR)p1, "Notification", MB_ICONINFORMATION);
		}
		else if (command == CMD_END) {
			game.Deinit();
			PostQuitMessage(0);
		}
		else if (command >= CMD_SNDSET0 && command <= CMD_SNDSET0 + 15) {
			sprintf(soundfiles[command - CMD_SNDSET0], "%s/%s", ResPath + 1, (char*)p1);
		}
		else if (command >= CMD_SNDPLAY0 && command <= CMD_SNDPLAY0 + 15) {
			//sndPlaySoundA((char*)soundfiles[command-CMD_SNDPLAY0],SND_ASYNC);
			//PlaySoundA(NULL,0,0);
			PlaySoundA(soundfiles[command - CMD_SNDPLAY0], NULL, SND_NOSTOP | SND_ASYNC | SND_FILENAME);
			//	ShellExecuteA(hWnd, "open", soundfiles[command-CMD_SNDPLAY0], "", "C:\\", SW_SHOWNORMAL);
		}
		else if (command == CMD_VIDPLAY) {
			ShellExecuteA(hWnd, "open", "C:\\acnode\\Alge_Demos\\Data\\video1.mp4", "", "C:\\", SW_SHOWNORMAL);
		}
		else if (command == CMD_TITLE) {
			SetWindowTextA(hWnd, (LPCSTR)p1);
		}
		else if (command == CMD_TEXSET0) {
		}
	}


	return TRUE;										// Keep Going
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBoxA(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBoxA(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBoxA(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBoxA(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass(TEXT("OpenGL"),hInstance))			// Are We Able To Unregister Class
	{
		MessageBoxA(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
		
	
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;//1280 - width/2;			// Set Left Value To 0
	WindowRect.right=(long)game.getBackgroundSize().x;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;//800 - height /2;				// Set Top Value To 0
	WindowRect.bottom=(long)game.getBackgroundSize().y;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= TEXT("OpenGL");								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBoxA(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBoxA(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBoxA(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		//ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								TEXT("OpenGL"),							// Class Name
								TEXT("Alge"),								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}



	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		(BYTE)bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	//ShowCursor(FALSE);
	SetWindowPos(hWnd,NULL, (1280-320)/2, (800-480)/2,0,0,SW_SHOW);
	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(game.getBackgroundSize().x, game.getBackgroundSize().y);					// Set Up Our Perspective GL Screen


	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBoxA(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}
	return TRUE;									// Success
}

int NumberKeys(WPARAM wParam) {
 return wParam-49;
}


BOOL CALLBACK AccelDlgProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	
	switch (uMsg)									// Check For Windows Messages
	{
		

		case WM_HSCROLL :
			{
			HWND hSb = (HWND) lParam;
			int val = SendMessage(hSb, TBM_GETPOS, 0, 0);
			if (hSb==GetDlgItem(hAccel, IDC_SLIDER1)) aX=val;
			if (hSb==GetDlgItem(hAccel, IDC_SLIDER2)) aY=val;
			if (hSb==GetDlgItem(hAccel, IDC_SLIDER3)) aZ=val;
			}
         break;
	  break;
		case WM_INITDIALOG:
			SetScrollRange (GetDlgItem(hAccel, IDC_SLIDER1), SB_HORZ, 0, 100, TRUE) ;
			SetScrollRange (GetDlgItem(hAccel, IDC_SLIDER2), SB_HORZ, 0, 100, TRUE) ;
			SetScrollRange (GetDlgItem(hAccel, IDC_SLIDER3), SB_HORZ, 0, 100, TRUE) ;
			return TRUE;
			break;

		case WM_CLOSE :
		     DestroyWindow (hWnd) ;
			 hAccel = NULL ;
			break ;

	}

	return FALSE;
}

BOOL CALLBACK DlgProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	
	switch (uMsg)									// Check For Windows Messages
	{
		case CMD_TOAST:
			{
				SetTimer(hWnd,CMD_TOAST,2500,0);
			}
			return TRUE;
			break;

		case WM_TIMER:
			{
				ShowWindow(hWnd, SW_HIDE);
				KillTimer(hWnd, CMD_TOAST);
			}
			return TRUE;
			break;

		case WM_INITDIALOG:
			return TRUE;
			break;
		case WM_LBUTTONDOWN:
			return TRUE;
			break;
		case WM_CLOSE :
		     DestroyWindow (hWnd) ;
			 hToast = NULL ;
			break ;

	}

	return FALSE;
}


bool touching = false;
bool touchingR = false;

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	
	switch (uMsg)									// Check For Windows Messages
	{

		case WM_CREATE:
#ifdef USING_IRRLICHT
			ir.Init(0, ResPath+1);
#endif
		break;

		case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			game.input.pushI(CMD_TOUCH_START, xPos, yPos);
			touching = true;
		}
		break;
		case WM_RBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			game.input.pushI(CMD_TOUCH_STARTR, xPos, yPos);
			touchingR = true;
		}
		break;
		case WM_MOUSEWHEEL:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			int fwKeys = GET_KEYSTATE_WPARAM(wParam);
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			game.input.pushI(CMD_MOUSEWHEEL, zDelta, fwKeys);
		}
		break;
		case WM_MOUSELEAVE:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam); 
			int yPos = GET_Y_LPARAM(lParam); 
			game.input.pushI(CMD_TOUCH_END, xPos, yPos);
			touching = false;
			touchingR = false;
		}
		break;
		case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			if (touching)
				game.input.pushI(CMD_TOUCHMOVE, xPos, yPos);
			if (touchingR)
				game.input.pushI(CMD_TOUCHMOVER, xPos, yPos);

			if (!touching && !touchingR) game.input.pushI(CMD_MOUSEMOVE, xPos, yPos);

		}
			break;

		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
				lastTime = time1.getElapsedTimeInSec();
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		case WM_SYSKEYDOWN:
		{
			static BOOL bCursor = true;
			game.input.pushI(CMD_KEYDOWN,NumberKeys(wParam),0);
			if (NumberKeys(wParam)==18) bCursor=!bCursor;
			ShowCursor(bCursor);
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}



void FindAppName() {

	FILE* f = fopen("CANDIDATE.h", "r");
	if (f)
	{
		char line[256] = { 0 };

		for (int i=0; i<100; i++) {
			int ret = fscanf(f, "%s", line);
			char* pn = strstr(line, ".hpp");
			strcpy(ResPath, line);
			if (pn) {
				pn[0] = 0;
				char* r = strrchr(line, '/');
				if (r) {
					r[0] = 0;
					sprintf_s(ResPath, 256, "%s.Assets/Data/", line);
				}
				break;
			}
		}

		fclose(f);
	}
}
static char remoteCommand[256];
void onRemoteCommand(string cmd) {
	strcpy(remoteCommand, cmd.c_str());
	game.input.pushP(CMD_REMOTE_COMMAND, (void*)remoteCommand, 0);
}

int WINAPI WinMain(	_In_ HINSTANCE	hInstance,			// Instance
					_In_opt_ HINSTANCE	hPrevInstance,		// Previous Instance
					_In_ LPSTR		lpCmdLine,			// Command Line Parameters
					_In_ int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	//nats1();
	r_mouse = 2.0;//means mouse update will not disturb 
		
	if (lpCmdLine[0]) {
		game.input.pushP(CMD_COMMANDLINE, lpCmdLine, 0);
	} else {
		FindAppName();
	}

	//MessageBoxA(NULL, "Use a.e to monitor\na.e.In to command", "NATS", MB_ICONINFORMATION);
	//netmsg.Connect("e");// "Evolution");
	
	//callBackIn = &onRemoteCommand; //Some Error Recheck Callback scheme

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Alge Prototype",
		game.getBackgroundSize().x,
		game.getBackgroundSize().y,
		16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	//DialogBox (hInstance, TEXT ("Toast"), hWnd, (DLGPROC)DlgProc) ;
	DWORD A = GetLastError();
	hToast=CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd,(DLGPROC)DlgProc); 
	DWORD Ab = GetLastError();
    ShowWindow (hToast, SW_HIDE) ;
	//hAccel=CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hWnd,(DLGPROC)AccelDlgProc); 
	//ShowWindow (hAccel, SW_SHOW) ;
	RECT rect;
	GetWindowRect (hToast, &rect) ;
    SetWindowPos (hAccel, NULL, rect.right+100,rect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE) ;


	while(!done)									// Loop That Runs While done=FALSE
	{

		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
			    if (hToast == 0 || !IsDialogMessage (hToast, &msg))
				  {
			         TranslateMessage (&msg) ;
					 DispatchMessage  (&msg) ;
				   }
				
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
				
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("Alge Container",game.getBackgroundSize().x,game.getBackgroundSize().y,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}

extern "C++" void alAlphaTest(int set_unset, float fA) {
	if (set_unset) {
		glAlphaFunc(GL_GREATER, fA);
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_ALPHA_TEST);
	}
}

extern "C++" void alLoadIdentity() {
	glLoadIdentity();
}

extern "C++" void alPushMatrix() {
	glPushMatrix();
}

extern "C++" void alPopMatrix() {
	glPopMatrix();
}

extern "C++" void alLoadModel(char* alx, char* tga, int id, float size) {
	string fname = string(alx);
	if (fname.find(".alx") != string::npos)
		game.rm.loadAlxModel((char*)alx, (char*)tga, id, size);
	else //generic 
		game.rm.loadGenericAsset(fname, id);
}
int alLoadModel(ResourceInf* resInf) {
	static int counter = -1;
	alLoadModel((char*)resInf->alx.c_str(), (char*)resInf->tex.c_str(), ++counter, resInf->scale);
	return counter;
}

extern "C++" void alDrawModelTranslateRotate(int id, float posx, float posy, float posz,
	float angle, float x, float y, float z,
	int rotatefirst,
	int billboard)
{
	glPushMatrix();
	if (rotatefirst != 0) {
		glRotatef(angle, x, y, z);
		glTranslatef(posx, posy, posz);
	}
	else {
		glTranslatef(posx, posy, posz);
		glRotatef(angle, x, y, z);
	}

	if (game.rm.models[id]->loaded) {
		if (billboard == 1) alBillboardBegin();
		game.rm.models[id]->glDraw();
		if (billboard == 1) alBillboardEnd();
	}
	glPopMatrix();
}

extern "C++" void alScaleModel(int id, float sx, float sy, float sz) {
	game.rm.models[id]->SetScale(sx, sy, sz);
}

extern "C++" void alDrawModel(int id, bool wireframe) {
	game.rm.models[id]->glDraw(wireframe);
}

extern "C++" void alTranslateRotate(float posx, float posy, float posz,
	float angle, float x, float y, float z) {
	glTranslatef(posx, posy, posz);
	glRotatef(angle, x, y, z);
}