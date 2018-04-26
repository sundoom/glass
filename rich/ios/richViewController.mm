//
//  richViewController.m
//  rich
//
//  Created by sunjun on 12-11-1.
//  Copyright 2012 sunstdio. All rights reserved.
//

#import "richViewController.h"
#import "richView.h"

//////////////////////////////////////////////////////////////////////////

#include <Glass.h>

//////////////////////////////////////////////////////////////////////////

@interface richViewController ()
@property (nonatomic, assign) CADisplayLink *displayLink;
@end

@implementation richViewController

@synthesize animating, displayLink;

//////////////////////////////////////////////////////////////////////////

extern VOID GInitGame();
extern VOID GRunGame(F64 delta_time);
extern VOID GExitGame();

//////////////////////////////////////////////////////////////////////////

/*
 ====================
 GLoad
 ====================
 */
static Str s_app_dir;
const GData* GLoad(const CHAR* path)
{
	Str name = s_app_dir + path;
	GFile file;
	file.Open(name.c_str());
	U32 pos = file.Seek(0,FS_CUR);
	U32 size = file.Seek(0,FS_END);	
	file.Seek(pos,FS_SET);
	GData* data = GNEW(GData(size+1,0)); CHECK(data);
	CHECK(file.Read(data->Get(),data->Size())==size);
	file.Close();
	return data;
}

//////////////////////////////////////////////////////////////////////////

- (void)awakeFromNib
{
	// set the app dir
	s_app_dir = getenv("GPATH");
	s_app_dir += "/data/";
	
	// init the game
	GInitGame();
	
	// init the animation info
	animating = FALSE;
	animationFrameInterval = 1;
	self.displayLink = nil;
}

- (void)dealloc 
{
	// exit the game
	GExitGame();
	[super dealloc];
}

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad 
{
	[super viewDidLoad];
	self.view = [[richView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
}

- (void)viewDidUnload 
{
	[self.view release];
	[super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
	[self startAnimation];
	
	[super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[self stopAnimation];
	
	[super viewWillDisappear:animated];
}

// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation 
{
    return YES;
}

- (void)didReceiveMemoryWarning 
{
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

//////////////////////////////////////////////////////////////////////////


- (NSInteger)animationFrameInterval
{
	return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval
{
	/*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
	if (frameInterval >= 1)
	{
		animationFrameInterval = frameInterval;
		
		if (animating)
		{
			[self stopAnimation];
			[self startAnimation];
		}
	}
}

- (void)startAnimation
{
	if (!animating)
	{
		CADisplayLink *aDisplayLink = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(runFrame)];
		[aDisplayLink setFrameInterval:animationFrameInterval];
		[aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		self.displayLink = aDisplayLink;
		
		animating = TRUE;
	}
}

- (void)stopAnimation
{
	if (animating)
	{
		[self.displayLink invalidate];
		self.displayLink = nil;
		animating = FALSE;
	}
}

- (void)runFrame
{
	// get the frame time
	static F64 system_time = GSeconds();
	F64 current_time = GSeconds();
	F64 frame_time = current_time - system_time;
	if(frame_time == 0) return;
	system_time = current_time;
	
	// run the game
	GRunGame(frame_time);
	
	// update the view
	[self.view setNeedsDisplayInRect: [self.view bounds]];
}

//////////////////////////////////////////////////////////////////////////

@end
