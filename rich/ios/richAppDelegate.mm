//
//  richAppDelegate.m
//  rich
//
//  Created by sunjun on 12-11-1.
//  Copyright 2012 sunstdio. All rights reserved.
//

#import "richAppDelegate.h"
#import "richViewController.h"

@implementation richAppDelegate

@synthesize window;
@synthesize viewController;


#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // Override point for customization after app launch.
	
	// Set the view controller as the window's root view controller and display.
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];

	return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application 
{
	[self.viewController stopAnimation];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	[self.viewController startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	[self.viewController stopAnimation];
}

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application 
{
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}

- (void)dealloc 
{
    [viewController release];
    [window release];
    [super dealloc];
}


@end
