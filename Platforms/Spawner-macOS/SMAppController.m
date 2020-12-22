//
//  SMAppController.m
//  SolarSystemPlanets3D
//
//  Created by Bilal on 27/07/2017.
//  Copyright © 2017 alex. All rights reserved.
//

#import "SMAppController.h"

#import <ServiceManagement/ServiceManagement.h>
#import <Security/Authorization.h>

@implementation SMAppController
    
- (void)applicationDidFinishLaunching:(NSNotification *)notification
    {
#pragma unused(notification)
        NSError *error = nil;
        
        OSStatus status = AuthorizationCreate(NULL, kAuthorizationEmptyEnvironment, kAuthorizationFlagDefaults, &self->_authRef);
        if (status != errAuthorizationSuccess) {
            /* AuthorizationCreate really shouldn't fail. */
            assert(NO);
            self->_authRef = NULL;
        }
        
        if (![self blessHelperWithLabel:@"com.acnodelabs.apps.mac.planetsada" error:&error]) {
            NSLog(@"Something went wrong! %@ / %d", [error domain], (int) [error code]);
        } else {
            /* At this point, the job is available. However, this is a very
             * simple sample, and there is no IPC infrastructure set up to
             * make it launch-on-demand. You would normally achieve this by
             * using XPC (via a MachServices dictionary in your launchd.plist).
             */
            NSLog(@"Helper is available!");
            
            [self->_textField setHidden:false];
        }
    }
    
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
    {
#pragma unused(sender)
        return YES;
    }
    
- (BOOL)blessHelperWithLabel:(NSString *)label error:(NSError **)errorPtr;
    {
        BOOL result = NO;
        NSError * error = nil;
        
        AuthorizationItem authItem		= { kSMRightBlessPrivilegedHelper, 0, NULL, 0 };
        AuthorizationRights authRights	= { 1, &authItem };
        AuthorizationFlags flags		=	kAuthorizationFlagDefaults				|
        kAuthorizationFlagInteractionAllowed	|
        kAuthorizationFlagPreAuthorize			|
        kAuthorizationFlagExtendRights;
        
        /* Obtain the right to install our privileged helper tool (kSMRightBlessPrivilegedHelper). */
        OSStatus status = AuthorizationCopyRights(self->_authRef, &authRights, kAuthorizationEmptyEnvironment, flags, NULL);
        if (status != errAuthorizationSuccess) {
            error = [NSError errorWithDomain:NSOSStatusErrorDomain code:status userInfo:nil];
        } else {
            CFErrorRef  cfError;
            
            /* This does all the work of verifying the helper tool against the application
             * and vice-versa. Once verification has passed, the embedded launchd.plist
             * is extracted and placed in /Library/LaunchDaemons and then loaded. The
             * executable is placed in /Library/PrivilegedHelperTools.
             */
            result = (BOOL) SMJobBless(kSMDomainSystemLaunchd, (__bridge CFStringRef)label, self->_authRef, &cfError);
            if (!result) {
                error = CFBridgingRelease(cfError);
            }
        }
        if ( ! result && (errorPtr != NULL) ) {
            assert(error != nil);
            *errorPtr = error;
        }
        
        return result;
    }
    
    @end
