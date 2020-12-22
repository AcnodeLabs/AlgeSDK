//
//  SMAppController.h
//  SolarSystemPlanets3D
//
//  Created by Bilal on 27/07/2017.
//  Copyright © 2017 alex. All rights reserved.
//
#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@interface SMAppController : NSObject <NSApplicationDelegate> {
    IBOutlet NSTextField *  _textField;
    
    AuthorizationRef        _authRef;
}
    
@end
