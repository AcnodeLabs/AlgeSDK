
//  Created by Bilal on 11/11/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <iAD/iAd.h>


@class EAGLView;
@class AdViewController;

@interface alge_iphoneAppDelegate : UIResponder <UIApplicationDelegate, UIWebViewDelegate, ADBannerViewDelegate > {
    UIWindow *window;
    EAGLView *glView;
    AdViewController *advc;
    UIWebView *webview;
//    ADBannerView *adbv;
}
@property (retain, nonatomic) IBOutlet UILabel *textLabel;

- (void) YouTubeThumbHide;
- (void) YouTubeThumbInit:(NSString*)videoid frame:(CGRect)frame1;
- (void) webViewDidFinishLoad: (UIWebView *) webView;

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet EAGLView *glView;
@property (nonatomic, retain) IBOutlet UIWebView *webview;
@property (nonatomic, retain) AdViewController* advc;
//@property (nonatomic, retain) ADBannerView* advb;
@property (nonatomic,strong) UILongPressGestureRecognizer *lpgr;

@end

