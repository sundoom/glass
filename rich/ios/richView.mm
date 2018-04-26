//
//  richView.mm
//  rich
//
//  Created by sunjun on 12-9-2.
//  Copyright 2012 sunstdio. All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

#import "richView.h"

//////////////////////////////////////////////////////////////////////////

extern VOID GDrawGame(GGraph& graph);

//////////////////////////////////////////////////////////////////////////

@implementation richView

//////////////////////////////////////////////////////////////////////////

- (id)initWithFrame:(CGRect)frame
{
	self = [super initWithFrame:frame];
	return self;
}

-(void)drawRect:(CGRect)rect
{
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGContextSaveGState(context);
	CGColorSpaceRef colour_space = CGColorSpaceCreateDeviceRGB();
	
	CGContextConcatCTM(context, CGAffineTransformMake(1, 0, 0, -1, 0, rect.size.height));
	// CGContextConcatCTM(context, CGAffineTransformMake(1, 0, 0, -1, 0, [self bounds].size.height));
	
	if(mImagePtr == NULL || mImagePtr->Width() != rect.size.width || mImagePtr->Height() != rect.size.height)
	{
		mImagePtr = GImage::Create(rect.size.width, rect.size.height, PF_R8G8B8);
	}
	GGraph graph(mImagePtr.Get());
	GDrawGame(graph);

	CGDataProviderRef provider = CGDataProviderCreateWithData(0, mImagePtr->Pixels(), mImagePtr->Width() * mImagePtr->Height() * 3, 0);	
	CGImageRef image = CGImageCreate(
		mImagePtr->Width(),
		mImagePtr->Height(),
		8, 
		24, 
		mImagePtr->Width() * 3,
		colour_space,
		kCGImageAlphaNone, 
		provider,
		0, 
		true, 
		kCGRenderingIntentDefault );	
	CGDataProviderRelease(provider);	
	CGContextDrawImage(context, CGRectMake(0, 0, mImagePtr->Width(), mImagePtr->Height()), image);	
	CGImageRelease(image);
	
	CGColorSpaceRelease(colour_space);
	CGContextRestoreGState(context);
}

@end
