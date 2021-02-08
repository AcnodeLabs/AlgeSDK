//
//  EAGLView.h
//  san-angeles-iphone
//
//  Created by Bilal on 11/11/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIApplication.h>
#import <iAD/iAD.h>
#import <QuartzCore/QuartzCore.h>
#import "AccelerometerFilter.h"
#import "ESRenderer.h"
#import "alge_iphoneAppDelegate.h"

// This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
// The view content is basically an EAGL surface you render your OpenGL scene into.
// Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
@interface EAGLView : UIView <UIAccelerometerDelegate, ADBannerViewDelegate>
{    
@private
	
	BOOL animating;
	BOOL displayLinkSupported;
	NSInteger animationFrameInterval;
	// Use of the CADisplayLink class is the preferred method for controlling your animation timing.
	// CADisplayLink will link to the main display and fire every vsync when added to a given run-loop.
	// The NSTimer class is used only as fallback when running on a pre 3.1 device where CADisplayLink
	// isn't available.
	id displayLink;
    NSTimer *animationTimer;
	NSTimer *toastTimer;
	UILabel *toast1;
	AccelerometerFilter* m_filter;
	float m_phi;
	float ax, ay, az;
 //   ADBannerView *banner;
    UIView *contentView;

@public
    id <ESRenderer> renderer;
    alge_iphoneAppDelegate* m1;
  }

- (void) YouTubeThumbInit:(NSString*)videoid frame:(CGRect)frame1;
- (void) YouTubeThumbReady:(NSString*)videoid frame:(CGRect)frame1;

@property (nonatomic, strong) IBOutlet UIPinchGestureRecognizer *pinchRecognizer;
@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;
//@property(nonatomic, retain) IBOutlet ADBannerView *banner;
@property(nonatomic, retain) IBOutlet UIView *contentView;

- (void) startAnimation;
- (void) stopAnimation;
- (void) drawView:(id)sender;
- (void) captureToPhotoAlbum;
- (void) setTextLabel:(NSString*)label;
@end
