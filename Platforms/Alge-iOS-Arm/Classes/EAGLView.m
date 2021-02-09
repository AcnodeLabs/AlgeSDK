//
//  EAGLView.m
//  san-angeles-iphone
//
//  Created by Bilal on 11/11/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "EAGLView.h"

#import "ES1Renderer.h"

#import "../../../SDKSRC/Base/CCommands.h"
#import "UIViewController_RootViewController.h"

@implementation EAGLView

@synthesize contentView;
@synthesize animating;
//@synthesize banner;
@dynamic animationFrameInterval;

// You must implement this method
+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

extern int gAppAlive;



// This method is invoked each time a banner loads a new advertisement. Once a banner has loaded an ad, 
// it will display that ad until another ad is available. The delegate might implement this method if 
// it wished to defer placing the banner in a view hierarchy until the banner has content to display.
- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{

}

- (void)setTextLabel:(NSString*) msg1
{
    [m1.textLabel setText:msg1];
}




// This method will be invoked when an error has occurred attempting to get advertisement content. 
// The ADError enum lists the possible error codes.
- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{

}

// This message will be sent when the user taps on the banner and some action is to be taken.
// Actions either display full screen content in a modal session or take the user to a different
// application. The delegate may return NO to block the action from taking place, but this
// should be avoided if possible because most advertisements pay significantly more when 
// the action takes place and, over the longer term, repeatedly blocking actions will 
// decrease the ad inventory available to the application. Applications may wish to pause video, 
// audio, or other animated content while the advertisement's action executes.
- (BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave
{
    // Reduce Memorey Usage
    // Pause App, Let it Hybernate
    return TRUE;
}

// This message is sent when a modal action has completed and control is returned to the application. 
// Games, media playback, and other activities that were paused in response to the beginning
// of the action should resume at this point.
- (void)bannerViewActionDidFinish:(ADBannerView *)banner
{
    //Resume 
}

-(void)createADBannerView
{
    // --- WARNING ---
    // If you are planning on creating banner views at runtime in order to support iOS targets that don't support the iAd framework
    // then you will need to modify this method to do runtime checks for the symbols provided by the iAd framework
    // and you will need to weaklink iAd.framework in your project's target settings.
    // See the iPad Programming Guide, Creating a Universal Application for more information.
    // http://developer.apple.com/iphone/library/documentation/general/conceptual/iPadProgrammingGuide/Introduction/Introduction.html
    // --- WARNING ---
    
    // Depending on our orientation when this method is called, we set our initial content size.
    // If you only support portrait or landscape orientations, then you can remove this check and
    // select either ADBannerContentSizeIdentifierPortrait (if portrait only) or ADBannerContentSizeIdentifierLandscape (if landscape only).
	
    /*
    NSString *contentSize;
	if (&ADBannerContentSizeIdentifierPortrait != nil)
	{
		contentSize = UIInterfaceOrientationIsPortrait(true) ? ADBannerContentSizeIdentifierPortrait : ADBannerContentSizeIdentifierLandscape;
	}
	else
	{
		// user the older sizes 
		contentSize = UIInterfaceOrientationIsPortrait(true) ? ADBannerContentSizeIdentifier320x50 : ADBannerContentSizeIdentifier480x32;
    }
	
    // Calculate the intial location for the banner.
    // We want this banner to be at the bottom of the view controller, but placed
    // offscreen to ensure that the user won't see the banner until its ready.
    // We'll be informed when we have an ad to show because -bannerViewDidLoadAd: will be called.
    CGRect frame;
    frame.size = [ADBannerView sizeFromBannerContentSizeIdentifier:contentSize];
    frame.origin = CGPointMake(0.0f, CGRectGetMaxY(self.bounds)-frame.size.height);
    
    // Now to create and configure the banner view
    ADBannerView *bannerView = [[ADBannerView alloc] initWithFrame:frame];
    // Set the delegate to self, so that we are notified of ad responses.
    bannerView.delegate = self;
    // Set the autoresizing mask so that the banner is pinned to the bottom
    bannerView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleTopMargin;
    // Since we support all orientations in this view controller, support portrait and landscape content sizes.
    // If you only supported landscape or portrait, you could remove the other from this set.
    
	bannerView.requiredContentSizeIdentifiers = (&ADBannerContentSizeIdentifierPortrait != nil) ?
    [NSSet setWithObjects:ADBannerContentSizeIdentifierPortrait, ADBannerContentSizeIdentifierLandscape, nil] : 
    [NSSet setWithObjects:ADBannerContentSizeIdentifier320x50, ADBannerContentSizeIdentifier480x32, nil];
    
    // At this point the ad banner is now be visible and looking for an ad.
    //[self.superview addSubview:bannerView];
    //UIButton *a = [[UIButton alloc] init ];
    //[self.superview addSubview:a.inputView];
    
//    self.banner = bannerView;
    [bannerView release];
     */
}


//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id) initWithCoder:(NSCoder*)coder
{    
    
    
    if ((self = [super initWithCoder:coder]))
	{
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = TRUE;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:FALSE], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
		
		gAppAlive = true;
		
		if (!renderer)
		{
			renderer = [[ES1Renderer alloc] init];
			
			if (!renderer)
			{
				[self release];
				return nil;
			}
			[ ((ES1Renderer*)renderer) setEaglView:self];
		}
        
		animating = FALSE;
		displayLinkSupported = FALSE;
		animationFrameInterval = 1;
		displayLink = nil;
		animationTimer = nil;
		
		// A system version of 3.1 or greater is required to use CADisplayLink. The NSTimer
		// class is used as fallback when it isn't available.
		NSString *reqSysVer = @"3.1";
		NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
		if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending)
			displayLinkSupported = TRUE;
		
    }
	
#if TARGET_IPHONE_SIMULATOR
	BOOL compassSupported = NO;
	BOOL accelSupported = NO;
#else
	BOOL compassSupported = NO; //Enable it Later
	BOOL accelSupported = YES;
#endif
	
    if (compassSupported) {}
    
	if (accelSupported) {	
            float updateFreq = 60.0f;
            m_filter = [[LowpassFilter alloc] initWithSampleRate:updateFreq cutoffFrequency:5.0];
            m_filter.adaptive = YES;
            [[UIAccelerometer sharedAccelerometer] setUpdateInterval:1.0/updateFreq];
            [[UIAccelerometer sharedAccelerometer] setDelegate:self];
        } else {		
	}
	
    //iAD
    //bvc = [[BannerViewController alloc] init ];
    //bvc.contentView = self;
    //[bvc viewDidLoad];
    
    //[self addSubview:bvc.banner];
    
    // banner = [[ADBannerView alloc ]init];
    //banner.delegate = self;
    
    [self createADBannerView];

    
//    [self addGestureRecognizer:self.pinchRecognizer];
    [self setUserInteractionEnabled:YES];
    
    return self;
}


/*
-(void) alertView:(UIAlertView*)alertView clickedButtonAtIndex:(NSInteger)b
{
	return;
}
 */

-(void) onToastTimeEnd
{
	[toast1 removeFromSuperview];
	//[toastTimer release];
}

- (void) Toast: (NSString*)text {
	short nlines = [text length]/ 25;
	if (nlines<2) nlines = 2;
	int width = 200;
	int height = nlines * 25;	
	toast1 = [[UILabel alloc] initWithFrame:CGRectMake(50, 300, width,height)];
	toast1.numberOfLines = nlines;
	toast1.text = text;
	toast1.textAlignment = UITextAlignmentCenter;
	toast1.backgroundColor = [UIColor colorWithWhite:0.2f alpha:0.72f];
	toast1.textColor = [UIColor whiteColor];
	toast1.highlightedTextColor = [UIColor blackColor];
	toast1.font = [UIFont systemFontOfSize:14];
	[self addSubview:toast1];
	toastTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)(4) target:self selector:@selector(onToastTimeEnd) userInfo:nil repeats:FALSE];
}


-(UIImage *) glToUIImage {
    NSInteger myDataLength = 320 * 480 * 4;
    
    // allocate array and read pixels into it.
    GLubyte *buffer = (GLubyte *) malloc(myDataLength);
    glReadPixels(0, 0, 320, 480, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    
    // gl renders "upside down" so swap top to bottom into new array.
    // there's gotta be a better way, but this works.
    GLubyte *buffer2 = (GLubyte *) malloc(myDataLength);
    for(int y = 0; y < 480; y++)
    {
        for(int x = 0; x < 320 * 4; x++)
        {
            buffer2[(479 - y) * 320 * 4 + x] = buffer[y * 4 * 320 + x];
        }
    }
    
    // make data provider with data.
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer2, myDataLength, NULL);
    
    // prep the ingredients
    int bitsPerComponent = 8;
    int bitsPerPixel = 32;
    int bytesPerRow = 4 * 320;
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    
    // make the cgimage
    CGImageRef imageRef = CGImageCreate(320, 480, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);
    
    // then make the uiimage from that
    UIImage *myImage = [UIImage imageWithCGImage:imageRef];
    return myImage;
}

-(void)captureToPhotoAlbum {
    UIImage *image = [self glToUIImage];
    UIImageWriteToSavedPhotosAlbum(image, self, nil, nil);
}


- (void) Msg: (NSString*)text : (NSString*) title {
	UIAlertView *alert = [[UIAlertView alloc] init] ;
	[alert setTitle:title];
	[alert setMessage:text];
	[alert setDelegate:self];
	[alert addButtonWithTitle:@"Ok"];
	[alert show];
	[alert release];
}

- (void) Title: (NSString*)text {
	UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 480,20)];
	label.numberOfLines = 1;
	label.text = text;
	label.backgroundColor = [UIColor grayColor];
	label.textColor = [UIColor whiteColor];
	label.highlightedTextColor = [UIColor blackColor];
	label.font = [UIFont systemFontOfSize:12];
	[self addSubview:label];
	[label release];
}

bool toastOn = false;
float m_timestamp;

- (void) YouTubeThumbInit:(NSString*)videoid frame:(CGRect)frame1 {
    [m1 YouTubeThumbInit:videoid frame:frame1];
}

- (void) YouTubeThumbReady:(NSString*)videoid frame:(CGRect)frame1 {
    //[renderer YouTubeThumbReady:videoid frame:frame1];
     [m1 YouTubeThumbInit:videoid frame:frame1];
}

- (void) drawView:(CADisplayLink*) displayLink
//- (void) drawView:(id)sender
{
	m_timestamp = displayLink.timestamp;
	[renderer render];
}

- (void) layoutSubviews
{
	[renderer resizeFromLayer:(CAEAGLLayer*)self.layer];
    [self drawView:nil];
}

- (NSInteger) animationFrameInterval
{
	return animationFrameInterval;
}

- (void) setAnimationFrameInterval:(NSInteger)frameInterval
{
	// Frame interval defines how many display frames must pass between each time the
	// display link fires. The display link will only fire 30 times a second when the
	// frame internal is two on a display that refreshes 60 times a second. The default
	// frame interval setting of one will fire 60 times a second when the display refreshes
	// at 60 times a second. A frame interval setting of less than one results in undefined
	// behavior.
	if (frameInterval >= 1)
	{
		animationFrameInterval = frameInterval;
		
		if (animating)
		{
			[self stopAnimation];
			[self startAnimation];
		}
	}
}

- (void) startAnimation
{
	if (!animating)
	{
		if (displayLinkSupported)
		{
			// CADisplayLink is API new to iPhone SDK 3.1. Compiling against earlier versions will result in a warning, but can be dismissed
			// if the system version runtime check for CADisplayLink exists in -initWithCoder:. The runtime check ensures this code will
			// not be called in system versions earlier than 3.1.

			displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(drawView:)];
			[displayLink setFrameInterval:animationFrameInterval];
			[displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		}
		else
			animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 600.0) * animationFrameInterval) target:self selector:@selector(drawView:) userInfo:nil repeats:TRUE];
		
		animating = TRUE;
	}
}

- (void)stopAnimation
{
	if (animating)
	{
		if (displayLinkSupported)
		{
			[displayLink invalidate];
			displayLink = nil;
		}
		else
		{
			[animationTimer invalidate];
			animationTimer = nil;
		}
		
		animating = FALSE;
	}
}





- (void) dealloc
{
    [renderer release];
	
    [super dealloc];
}






@end
