//
//  UIViewController_RootViewController.h
//  _Alge-Project
//
//  Created by alex on 5/5/17.
//
//

#import <UIKit/UIKit.h>

@interface UIViewController_RootViewController : UIViewController <UIGestureRecognizerDelegate>
- (void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void) touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;



@end
