//
//  Toast.m
//  Mars
//
//  Created by Bilal on 05/11/2017.
//

#import "Toast.h"
#include <Foundation/Foundation.h>

@implementation Toast

@end

void ShowToast(char* msg) {
  //  NSUserNotification *userNotification = [[[NSUserNotification alloc] init] autorelease];
  //  userNotification.title = @"Mars3D Notice";
  //  userNotification.informativeText = [NSString stringWithUTF8String:msg];
    
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:@"Alert"];
    [alert setInformativeText:[NSString stringWithUTF8String:msg]];
    [alert addButtonWithTitle:@"Ok"];
    try {
        [alert runModal];
    } catch (...) {}
}
