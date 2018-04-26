//
//  richViewController.h
//  rich
//
//  Created by sunjun on 12-11-1.
//  Copyright 2012 sunstdio. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@interface richViewController : UIViewController 
{
	BOOL animating;
	NSInteger animationFrameInterval;
	CADisplayLink *displayLink;
}

@property (readonly, nonatomic, getter=isAnimating) BOOL animating;
@property (nonatomic) NSInteger animationFrameInterval;

- (void)startAnimation;
- (void)stopAnimation;

@end

