//
//  PlayYouTubeInWebViewController.m
//  Alge-Project
//
//  Created by Bilal on 4/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "PlayYouTubeInWebViewController.h"
#import "alge_iphoneAppDelegate.h"

@interface PlayYouTubeInWebViewController (Private)
- (void)embedYouTube:(NSString*)urlString frame:(CGRect)frame;
@end



@implementation PlayYouTubeInWebViewController


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        
    }
    
    return self;
}


- (void)loadView
{
    // If you create your views manually, you MUST override this method and use it to create your views.
    // If you use Interface Builder to create your views, then you must NOT override this method.
}

- (UIButton*) findButtonInView: (UIView *) view {
    UIButton* button = nil;
    
    if ([view isMemberOfClass:[UIButton class]]) {
        return (UIButton*) view;
    }
    
    if (view.subviews && [view.subviews count]>0) {
        for (UIView *subview in view.subviews) {
            button = [self findButtonInView:subview];
            if (button) return button;
        }
    }
    return button;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
