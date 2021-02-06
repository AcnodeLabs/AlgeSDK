//
//  UIViewController_RootViewController.m
//  _Alge-Project
//
//  Created by alex on 5/5/17.
//
//

#import <Foundation/Foundation.h>
#include "UIViewController_RootViewController.h"
#import "../../../SDKSRC/Base/CCommands.h"

void appPushI(int,int, int);

@implementation UIViewController_RootViewController

//PINCH DETECTION
//http://stackoverflow.com/questions/11183174/simplest-way-to-detect-a-pinch

int pinchDist;

- (void)handleLongPressGestures:(UILongPressGestureRecognizer *)sender
{
    if (sender.state == UIGestureRecognizerStateBegan)
    {
        appPushI(CMD_LONGPRESS,0, 0);
    }
}

- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch1 = [[[event allTouches] allObjects] objectAtIndex:0];
    CGPoint location = [touch1 locationInView:self.view];
    
  //  CGRect screenBounds = [[UIScreen mainScreen] bounds];
    CGFloat screenScale = [[UIScreen mainScreen] scale];
  //  CGSize screenSize = CGSizeMake(screenBounds.size.width * screenScale, screenBounds.size.height * screenScale);
    int lx = screenScale*(int)location.x;
    int ly = screenScale*(int)location.y;
    appPushI(CMD_TOUCH_START,lx, ly);
    location.x = lx;
    location.y = ly;
    
    
    if ([[event allTouches] count]==2) {
        UITouch *touch2 = [[[event allTouches] allObjects] objectAtIndex:1];
        CGPoint location2 = [touch2 locationInView:self.view];
        location2.x *= screenScale;
        location2.y *= screenScale;
        appPushI(CMD_TOUCH_START2,(int)location2.x, (int)location2.y);
        pinchDist = (int) sqrt((location.x-location2.x) * (location.x-location2.x) +
                  (location.y-location2.y) * (location.y-location2.y) );
        appPushI(CMD_PINCH_START,(int)pinchDist, 0);
    }
    

}


- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch1 = [[[event allTouches] allObjects] objectAtIndex:0];
    CGPoint location = [touch1 locationInView:self.view];
    
    if ([[event allTouches] count]==2) {
        UITouch *touch2 = [[[event allTouches] allObjects] objectAtIndex:1];
        CGPoint location2 = [touch2 locationInView:self.view];
        appPushI(CMD_TOUCHMOVE2,(int)location2.x, (int)location2.y);
        int pinchDistNow = (int) sqrt((location.x-location2.x) * (location.x-location2.x) +
                                  (location.y-location2.y) * (location.y-location2.y) );
        if (pinchDistNow>pinchDist)
        appPushI(CMD_PINCH_MOVE_OUT,(int)pinchDistNow, (int)(pinchDist));
        if (pinchDistNow<pinchDist)
        appPushI(CMD_PINCH_MOVE_IN,(int)pinchDistNow, (int)(pinchDist));
        pinchDist = pinchDistNow;
    }
    
    appPushI(CMD_TOUCHMOVE,(int)location.x, (int)location.y);
    printf("%.1f,%.1f\n", location.x
           ,location.y);
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch1 = [[[event allTouches] allObjects] objectAtIndex:0];
    CGPoint location = [touch1 locationInView:self.view];
    
    if ([[event allTouches] count]==2) {
        UITouch *touch2 = [[[event allTouches] allObjects] objectAtIndex:1];
        CGPoint location2 = [touch2 locationInView:self.view];
        appPushI(CMD_TOUCH_END2,(int)location2.x, (int)location2.y);
        int pinchDist = (int) sqrt((location.x-location2.x) * (location.x-location2.x) +
                                   (location.y-location2.y) * (location.y-location2.y) );
        appPushI(CMD_PINCH_END,(int)pinchDist, 0);
    }
    appPushI(CMD_TOUCH_END,(int)location.x, (int)location.y);
}
- (void)handleGesture
    {
        
    }
- (void)handleGesture:(UIGestureRecognizer *)gestureRecognizer
    {
    
    }
    
@end
