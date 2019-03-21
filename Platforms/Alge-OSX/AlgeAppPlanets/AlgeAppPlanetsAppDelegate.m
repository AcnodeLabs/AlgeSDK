//
//  AlgeAppPlanetsAppDelegate.m
//  AlgeAppPlanets
//
//  Created by Bilal on 8/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "AlgeAppPlanetsAppDelegate.h"

@implementation AlgeAppPlanetsAppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    NSUserNotification *notification = [[NSUserNotification alloc] init];
    notification.title = @"Hello, World!";
    notification.informativeText = @"A notification";
    notification.soundName = NSUserNotificationDefaultSoundName;
    
    [[NSUserNotificationCenter defaultUserNotificationCenter] deliverNotification:notification];
}

@end
