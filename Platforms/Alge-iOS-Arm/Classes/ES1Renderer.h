//
//  ES1Renderer.h
//
//  Created by Bilal on 11/11/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "ESRenderer.h"
#import "EAGLView.h"
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <AVFoundation/AVAudioPlayer.h>
#import <MediaPlayer/MPMoviePlayerController.h>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

@interface ES1Renderer : NSObject <ESRenderer>
{
	
@public
	int backingWidth;
	int backingHeight;
	NSString *NSext;
    NSString *NSfname;
	float elapsedMillis;
	
@private
	EAGLContext *context;
	
	// The OpenGL names for the framebuffer and renderbuffer used to render to this view
	GLuint defaultFramebuffer, colorRenderbuffer , defaultDepthbuffer;
	AVAudioPlayer* audio[10];
	MPMoviePlayerController *video;
	NSString *szP1;
	UIAlertView *alert;
	NSError *outErr;
	CFURLRef *baseURL;
	EAGLView* eaglView;
	int ax100, ay100, az100;
	double OldTime;
}

- (void) YouTubeThumbReady:(NSString*)videoid frame:(CGRect)frame1;
- (void) render;
- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer;
//- (id) touch_event:(int)cmd:(CGPoint) location;
- (id) setEaglView:(EAGLView *)ea;
@end

