
//
//  Created by Bilal on 11/11/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "alge_iphoneAppDelegate.h"
#import "EAGLView.h"
#import "AdViewController.h"
#import <iAd/iAd.h>
#import "PlayYouTubeInWebViewController.h"
#import "UIViewController_RootViewController.h"

@implementation alge_iphoneAppDelegate


@synthesize window;
@synthesize glView;
@synthesize advc;
//@synthesize advb;
@synthesize webview;


- (void)embedYouTubeT:(NSString *)urlString frame:(CGRect)frame {
	NSString *embedHTML = @"\
    <html><head>\
	<style type=\"text/css\">\
	body {\
	background-color: transparent;\
	color: transparent;\
	}\
	</style>\
	</head><body style=\"margin:0\">\
    <h1>Hello</h1>\
    </body></html>";
	NSString *html = [NSString stringWithFormat:embedHTML, urlString, frame.size.width, frame.size.height];
	[webview loadHTMLString:html baseURL:nil];
}

- (void)embedYouTube2:(NSString *)urlString frame:(CGRect)frame {
	NSString *embedHTML = @"\
    <html><head>\
	<style type=\"text/css\">\
	body {\
	background-color: transparent;\
	color: transparent;\
	}\
	</style>\
	</head><body style=\"margin:0\">\
    <iframe class=\"youtube-player\" type=\"text/html\"\
    src=\"http://www.youtube.com/embed/%@\"\
	width=\"%0.0f\" height=\"%0.0f\" frameborder=\"0\"></iframe>\
    </body></html>";
	NSString *html = [NSString stringWithFormat:embedHTML, urlString, frame.size.width, frame.size.height];
	[webview loadHTMLString:html baseURL:nil];
}

- (void)embedYouTube:(NSString *)urlString frame:(CGRect)frame {
	NSString *embedHTML = @"\
    <html><head>\
	<style type=\"text/css\">\
	body {\
	background-color: transparent;\
	color: transparent;\
	}\
	</style>\
	</head><body style=\"margin:0\">\
    <embed id=\"yt\" src=\"%@\" type=\"application/x-shockwave-flash\" \
	width=\"%0.0f\" height=\"%0.0f\"></embed>\
    </body></html>";
	NSString *html = [NSString stringWithFormat:embedHTML, urlString, frame.size.width, frame.size.height];
	[webview loadHTMLString:html baseURL:nil];
    //[webview loadRequest:[NSURL URLWithString:urlString]];
}

CGRect youFrame;

- (void) webViewDidFinishLoad: (UIWebView *) webView {
    [webview setHidden:FALSE];
    [glView YouTubeThumbReady:@"any" frame:youFrame];
}

- (void) YouTubeThumbHide {
    [webview setHidden:TRUE];
}

- (void) YouTubeThumbInit:(NSString*)videoid frame:(CGRect)frame1 {
    [glView stopAnimation];
    [webview removeFromSuperview];
    [webview release];
    webview  = [[UIWebView alloc] initWithFrame:frame1];
    [webview setDelegate:self];
    NSString *youlink = @"https://youtube.com/watch?feature=player_detailpage&v=%@";
    NSString *lnk = [NSString stringWithFormat:youlink, videoid];
    [self embedYouTube:lnk frame:frame1];
    [self YouTubeThumbHide];
    [glView addSubview:webview];
    [glView startAnimation];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.

    [[UIApplication sharedApplication] setStatusBarHidden:YES];
    
    
    /* AD Code is depreciated by Apple
    bool ENABLE_ADS = true;
    
    if (ENABLE_ADS) {
    
	
    AdViewController* advc1 = [[AdViewController alloc] initWithNibName:@"AdViewController" bundle:nil];
        
    CGRect frame;
    NSString* contentSize = ADBannerContentSizeIdentifierPortrait;
    frame.size = [ADBannerView sizeFromBannerContentSizeIdentifier:contentSize];
    frame.origin = CGPointMake(0.0f, CGRectGetMaxY(glView.bounds));
    
        
    [advc1.view setFrame:frame];
    
    advc1.view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleTopMargin;
    
        ADBannerView* adbv1 = [[advc1.view subviews] objectAtIndex:0];
        //for (int i = 0; i < [[advc1.view subviews] count]; i++ ) {
        [adbv1 setDelegate:self];
        //}
    
        
    //[glView addSubview:advc1.view];
    //[advc1 becomeFirstResponder];
    [glView addSubview:advc1.view];
        advc = advc1;
    //    adbv = adbv1;
    }
     */
    
    [glView startAnimation];
    webview = NULL;
    glView->m1 = self;
    webview = [[UIWebView alloc] init ];// initWithFrame:CGRectMake(30, 30, 150, 150)];
    [webview setDelegate:(id) [[PlayYouTubeInWebViewController alloc] init]];
    [glView addSubview:webview];
    window.rootViewController = [[UIViewController_RootViewController alloc] init];
 //   [glView addGestureRecognizer: (UIPinchGestureRecognizer*) window.rootViewController];
    
    
    self.lpgr = [[UILongPressGestureRecognizer alloc] initWithTarget:window.rootViewController action:@selector(handleLongPressGestures:)];
    self.lpgr.minimumPressDuration = 1.0f;
    self.lpgr.allowableMovement = 100.0f;
    
    [window.rootViewController.view addGestureRecognizer:self.lpgr];
    
    return YES;
}

void appPushI(int,int, int);


- (void) handleLongPressGestures:(UIApplication *)application
{

}

- (void) applicationWillResignActive:(UIApplication *)application
{
	[glView stopAnimation];
}

- (void) applicationDidBecomeActive:(UIApplication *)application
{
	[glView startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	[glView stopAnimation];
}
    
- (UIInterfaceOrientationMask)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window
    {
        return UIInterfaceOrientationMaskLandscape;
}

- (void) dealloc
{
    if (webview) {
        webview.delegate = nil;
        [webview release];
    }
//	[adbv release];
 //   [advc release];
    [window release];
	[glView release];
	
    [_textLabel release];
	[super dealloc];
}


#pragma mark ADBannerViewDelegate methods

-(void) bannerState:(BOOL) isup
{
    if (!advc) return;
    CGRect frame;
    NSString* contentSize = ADBannerContentSizeIdentifierPortrait;
    frame.size = [ADBannerView sizeFromBannerContentSizeIdentifier:contentSize];
    int displacement = isup?frame.size.height:0;
    frame.origin = CGPointMake(0.0f, CGRectGetMaxY(glView.bounds) - displacement);
    advc.view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleTopMargin;
    [advc.view setFrame:frame];
    [glView layoutSubviews];
}

-(void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    if (!advc) return;
    [self bannerState:TRUE];
}

-(void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    if (!advc) return;
    [self bannerState:FALSE];
}

-(BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave
{
    [advc.view setHidden:TRUE];
    return YES;
}

-(void)bannerViewActionDidFinish:(ADBannerView *)banner
{
    [self bannerState:TRUE];
    [glView layoutSubviews];
    [advc.view setHidden:FALSE];
}

@end
