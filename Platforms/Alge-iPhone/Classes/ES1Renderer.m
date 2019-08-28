//
//  ES1Renderer.m
//  san-angeles-iphone
//
//  Created by Bilal on 11/11/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "ES1Renderer.h"
#import "../../../SDKSRC/Base/CCommands.h"
#import <AVFoundation/AVAudioPlayer.h>
#import "app.h"

@implementation ES1Renderer


- (BOOL)createFramebuffer
{
    glGenFramebuffersOES(1, &defaultFramebuffer);
    glGenRenderbuffersOES(1, &colorRenderbuffer);
    
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
  //  [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, colorRenderbuffer);
    
   // glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &_backingWidth);
   // glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &_backingHeight);
    
    if (1) 
	{
        glGenRenderbuffersOES(1, &defaultDepthbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, defaultDepthbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, defaultDepthbuffer);
    }
    
    if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) 
	{
        NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
        return NO;
    }
    
    return YES;
}


// Create an ES 1.1 context
- (id) init
{
	if (self = [super init])
	{
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        
        if (!context || ![EAGLContext setCurrentContext:context])
		{
            [self release];
            return nil;
        }
		
		/*
		glGenFramebuffersOES(1, &defaultFramebuffer);
		glGenRenderbuffersOES(1, &colorRenderbuffer);
		
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
		//  [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
		glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, colorRenderbuffer);
		
		// glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &_backingWidth);
		// glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &_backingHeight);
		
		if (1) 
		{
			glGenRenderbuffersOES(1, &defaultDepthbuffer);
			glBindRenderbufferOES(GL_RENDERBUFFER_OES, defaultDepthbuffer);
			glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
			glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, defaultDepthbuffer);
		}
		
		if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) 
		{
			NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
			return NO;
		}
		
		*/
		
		// Create the frame buffer.
		glGenFramebuffersOES(1, &defaultFramebuffer);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
		
		// Create the depth buffer.
		glGenRenderbuffersOES(1, &defaultDepthbuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, defaultDepthbuffer);

		CGRect applicationFrame = [[UIScreen mainScreen] nativeBounds];
		
		glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
		glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);

		if (backingWidth==0) backingWidth = applicationFrame.size.width;
		if (backingHeight==0) backingHeight = applicationFrame.size.height;
		
        appSize(backingWidth, backingHeight);
        
		glRenderbufferStorageOES(GL_RENDERBUFFER_OES,GL_DEPTH_COMPONENT16_OES,backingWidth,backingHeight);
		
		// Create default framebuffer object. The backing will be allocated for the current layer in -resizeFromLayer
		glGenRenderbuffersOES(1, &colorRenderbuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
		
		
		glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES ,colorRenderbuffer);
		glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, defaultDepthbuffer);
		
		NSString * path1 = [[NSBundle mainBundle] pathForResource:  @"acnodelogo" ofType: @"tga"];
		char* sz = (char*) [path1 cStringUsingEncoding:1];		
		int l = (int)strlen(sz);
		if (l>14) sz[l-14] = 0;
		
		OldTime = CACurrentMediaTime();
        strcat(sz, "/Data/");
		appInit((char*)sz);
        
	}
		
//	baseURL = (CFURLRef) [NSURL alloc];
//	alert = [UIAlertView alloc];
//	outErr = [[NSError alloc] init];
	
	return self;
}

- (id) setEaglView:(EAGLView *)ea
{
	eaglView = ea;
    return self;
}

// Loads PNG texture 512x512

-(int)loadPng:(NSString*)pngfile :(GLuint)texid 
{	
	//int width = size;//Assume Square
	//int height = size;
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	/*
	 #ifdef USE_PVRTC_TEXTURE    
	 NSString *path = [[NSBundle mainBundle] pathForResource:@"ispark_head" ofType:@"pvr"];
	 NSData *texData = [[NSData alloc] initWithContentsOfFile:path];
	 
	 // This assumes that source PVRTC image is 4 bits per pixel and RGB not RGBA
	 // If you use the default settings in texturetool, e.g.:
	 //
	 // 		texturetool -e PVRTC -o texture.pvrtc texture.png
	 //
	 // then this code should work fine for you. Notice, the source image has had
	 // its y-axis inverted to deal with the t-axis inversion issue.
	 glCompressedTexImage2D(GL_TEXTURE_2D, 0, GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG, 512, 512, 0, [texData length], [texData bytes]);
	 #else 
	 */
	
    NSString *path = [[NSBundle mainBundle] pathForResource:pngfile ofType:@"png"];
	NSData *texData = [[NSData alloc] initWithContentsOfFile:path];
    UIImage *image = [[UIImage alloc] initWithData:texData];
    
    if (image == nil)
        NSLog(@"Do real error checking here");
    
 	GLuint width = (GLuint) CGImageGetWidth(image.CGImage);
    GLuint height = (GLuint) CGImageGetHeight(image.CGImage);
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    void *imageData = malloc( height * width * 4 );
    CGContextRef contxt = CGBitmapContextCreate( imageData, width, height, 8, 4 * width, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big );
	
    // Flip the Y-axis
    CGContextTranslateCTM (contxt, 0, height);
    CGContextScaleCTM (contxt, 1.0, -1.0);
    
    CGColorSpaceRelease( colorSpace );
    CGContextClearRect( contxt, CGRectMake( 0, 0, width, height ) );
    CGContextDrawImage( contxt, CGRectMake( 0, 0, width, height ), image.CGImage );
	
	glBindTexture(GL_TEXTURE_2D, texid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
    CGContextRelease(contxt);
    
	
    free(imageData);
    [image release];
    [texData release];
	//#endif
	return texid;
}

- (void) YouTubeThumbReady:(NSString*)videoid frame:(CGRect)frame1 {
    appPushI(CMD_YOUTUBE_READY, 0, 0);
}

- (void) render
{
  	// This application only creates a single context which is already set current at this point.
	// This call is redundant, but needed if dealing with multiple contexts.
    [EAGLContext setCurrentContext:context];
    
	
	// This application only creates a single default framebuffer which is already bound at this point.
	// This call is redundant, but needed if dealing with multiple framebuffers.
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
	
	double CurrentTime = CACurrentMediaTime();
	float elapsed     = CurrentTime - OldTime;
	
	CGRect applicationFrame = [[UIScreen mainScreen] applicationFrame];	
	
	appRender(elapsed, applicationFrame.size.width, applicationFrame.size.height+20,ax100,ay100,az100);
	
	OldTime = CurrentTime;
	bool more = true;
	int command;
	void* p1;
	void* p2;
	
		
	while (more) {
		command = appPull();
		p1 = appP1();
		p2 = appP2();
		
		if (command>0) {
            
            if (command==CMD_YOUTUBE_SHOW) {
                GLfloat x = *(GLfloat*)p2;
                GLfloat y = *((GLfloat*)(p2)+1);
                GLfloat w = *((GLfloat*)(p2)+2);
                GLfloat h = *((GLfloat*)(p2)+3);
                NSString *vidId = [NSString stringWithUTF8String:(const char*) p1];
                [eaglView YouTubeThumbInit:vidId frame:CGRectMake(x,y,w,h)];
            }
            
            if (command==CMD_YOUTUBE_CLOSE) {
                [eaglView->m1 YouTubeThumbHide];
            }
            
            if (command==CMD_SPAWN) {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:(const char*) p1]]];
            }
            
			if (command==CMD_BEGIN) 
			{
			}
			
			if (command==CMD_END) 
			{

			}
			
			if (command==CMD_LOG) 
			{
                NSLog(@"%@", [NSString stringWithUTF8String:(const char*) p1]);
			}
            
            //if (command==CMD_CAPTURE) {
            //    [eaglView captureToPhotoAlbum];
            //}
            if (command==CMD_MSG)
            {
                [eaglView setTextLabel:[NSString stringWithUTF8String:(const char*) p1]];
            }
            
		/*	if (command==CMD_MSG)
			{
				[eaglView Msg:[NSString stringWithUTF8String:(const char*) p1] : [NSString stringWithUTF8String:(const char*) p2?p2:"Message"]];
			}
		*/
            
			if (command==CMD_TOAST) 
			{
			//	[eaglView Toast:[NSString stringWithUTF8String:(const char*)p1]];
				
			}
			
			if (command==CMD_TITLE) 
			{
			//	if (p1)
			//	[eaglView Title:[NSString stringWithUTF8String:(const char*)p1]];
				
			}
			
			if (command>=CMD_SNDSET0 && command<=CMD_SNDSET0+9) {
				int index = command - CMD_SNDSET0;
				audio[index] = [[AVAudioPlayer alloc] init];
				
				char fname[32];memset(fname, 0, 32);
				char extension[4];memset(extension, 0, 4);
				
				if (p1) {
					char* dot = strchr(p1, '.');
					strncpy(fname, p1, (int) (char*)(dot-(char*)p1));
					strncpy(extension, dot+1, 3);
				}
				
				NSfname = [[NSString alloc] initWithUTF8String:fname];
				NSext = [[NSString alloc] initWithUTF8String:extension];
				
				/*
				 
				 id sndpath_bc = [[NSBundle mainBundle] pathForResource:@"bottomcross" ofType:@"wav" inDirectory:@"/"]; 
				 CFURLRef baseURL_bc = (CFURLRef) [[NSURL alloc] initFileURLWithPath:sndpath_bc];
				 
				 id vidpath = [[NSBundle mainBundle] pathForResource:@"Sparkit_3" ofType:@"mp4" inDirectory:@"/"]; 
				 CFURLRef baseURLvid = (CFURLRef) [[NSURL alloc] initFileURLWithPath:vidpath];
				 
				 [audio initWithContentsOfURL:baseURL error:&outErr];
				 [audio_bottomcross initWithContentsOfURL:baseURL_bc error:&outErr];
				 
				 */
				id sndpath_wu = [[NSBundle mainBundle] pathForResource:NSfname ofType:NSext inDirectory:@""]; 
                if (sndpath_wu != nil) {
				
				CFURLRef baseURL_wu = (CFURLRef) [[NSURL alloc] initFileURLWithPath:sndpath_wu];
				
                [audio[index] initWithContentsOfURL:(NSURL*)baseURL_wu error:&outErr];
                   
				
				//NSString* e ; e = [outErr localizedDescription];
				
				//int codel; codel = [outErr code];
				[audio[index] prepareToPlay];
				[(NSURL*)baseURL_wu dealloc];
                }
				
			}
			
			if (command>=CMD_SNDPLAY0 && command<=CMD_SNDPLAY0+9) {
				int index = command - CMD_SNDPLAY0;
                if (p2) {
                    int nLoops = *(int*)p2;
                    [audio[index] setNumberOfLoops:nLoops];
                }
              //  [audio[index] play];
			}
			
			if (command==CMD_SNDLOOP) {
			}
			
			if (command==CMD_VIDSET) {
				video = [MPMoviePlayerController alloc];	
				
				char fname[32];memset(fname, 0, 32);
				char extension[4];memset(extension, 0, 4);
				
				if (p1) {
					char* dot = strchr(p1, '.');
					strncpy(fname, p1, (int) (char*)(dot-(char*)p1));
					strncpy(extension, dot+1, 3);
				}
				
				NSString *NSfname = [[NSString alloc] initWithUTF8String:fname];
				NSString *NSext = [[NSString alloc] initWithUTF8String:extension];
				
				
				id vidpath = [[NSBundle mainBundle] pathForResource:NSfname ofType:NSext inDirectory:@"/"]; 
				CFURLRef baseURLvid = (CFURLRef) [[NSURL alloc] initFileURLWithPath:vidpath];	
				[video initWithContentURL:(NSURL*)baseURLvid];
				[NSfname dealloc];
				[NSext dealloc];
			}
			
			if (command==CMD_VIDPLAY) {
				[video play];
			}
			
		}
		if (command == 0) more = false;
	};
	
	// This application only creates a single color renderbuffer which is already bound at this point.
	// This call is redundant, but needed if dealing with multiple renderbuffers.
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
    [context presentRenderbuffer:GL_RENDERBUFFER_OES];
}


-(void) setAccel:(int)x :(int)y :(int)z
{
    ax100 = x;
    ay100 = y;
    az100 = z;
    return;
}
/*
-(id) touch_event:(int)cmd:(CGPoint) location
{
	appPushI(cmd,(int)location.x, (int)location.y);
}
*/
- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer
{	
	// Allocate color buffer backing based on the current layer size
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:layer];
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
	
    if (glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES)
	{
		NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
        return NO;
    }
    
	appPushI(CMD_SCREENSIZE, backingWidth, backingHeight);
	
    return YES;
}

-(int) width
{
	return backingWidth;
}

-(int) height
{
	return backingHeight;
}

- (void) dealloc
{
    [NSext dealloc];
    [NSfname dealloc];
	appDeinit();
	
	// Tear down GL
	if (defaultFramebuffer)
	{
		glDeleteFramebuffersOES(1, &defaultFramebuffer);
		defaultFramebuffer = 0;
	}
	
	if (colorRenderbuffer)
	{
		glDeleteRenderbuffersOES(1, &colorRenderbuffer);
		colorRenderbuffer = 0;
	}
	
	// Tear down context
	if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	
	[context release];
	context = nil;
	
	[super dealloc];
}

@end
