//
//  main.m
//  planetsplus
//
//  Created by alex on 3/26/17.
//  Copyright © 2017 alex. All rights reserved.
//

#import <Cocoa/Cocoa.h>

int main(int argc, const char * argv[]) {
    // Build Executable using GPS
    // Copy from obj Directory and rename
    NSBundle* myBundle = [NSBundle mainBundle];
    NSString* myApp = [myBundle pathForResource:@"Planets" ofType:@""];
    
    NSString* myDir = [myBundle bundlePath];
    myDir = [myDir stringByAppendingString:@"/Contents/Resources"];
    
    NSTask *task = [[NSTask alloc] init];
    // See http://stackoverflow.com/questions/38132589/nstask-couldnt-posix-spawn-error-13-when-launching-app
  //  [task setLaunchPath:@"/usr/bin/open"];
  //  [task setArguments:@[ @"-a", myApp ]];
    [task setCurrentDirectoryPath:myDir];
    [task setLaunchPath:myApp];
    
 //   [task setStandardOutput:<#(id _Nullable)#>];
    @try {
        [task launch];
        [task waitUntilExit];
    } @catch (NSException *exception) {
        NSLog(@"exception");
    } @finally {
        
    }

    return EXIT_SUCCESS;
}
// http://stackoverflow.com/questions/27904552/sandboxed-child-process-launced-with-nstask-fails-silently
// https://developer.apple.com/library/content/documentation/Security/Conceptual/AppSandboxDesignGuide/AboutAppSandbox/AboutAppSandbox.html#//apple_ref/doc/uid/TP40011183-CH1-SW1
