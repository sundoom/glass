//
//  richView.h
//  rich
//
//  Created by sunjun on 12-9-2.
//  Copyright 2012 sunstdio. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <Glass.h>

// This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
// The view content is basically an EAGL surface you render your OpenGL scene into.
// Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
@interface richView : UIView
{
@private
  GImagePtr mImagePtr;
}

@end
