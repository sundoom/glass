/*
 *  GImage.h
 *  glass
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */

//////////////////////////////////////////////////////////////////////////

#ifndef __GImage__
#define __GImage__

//////////////////////////////////////////////////////////////////////////

#if defined __cplusplus

//////////////////////////////////////////////////////////////////////////

enum PIXEL_FORMAT
{
  PF_R8G8B8,
  PF_R8G8B8A8,
  PF_R5G6B5,
};

//////////////////////////////////////////////////////////////////////////

// this class provides an object-oriented base image interface.
class GImage : public GReference
{
private:
	// constructor
	GImage();

	// destructor
	virtual ~GImage();

public:
	// get the width of the image	
	U32 Width() const;

	// get the height of the image	
	U32 Height() const;

  // get the format of bits per pixel  
  U32 Format() const;

  // get the pixels of the image	
  const U8* Pixels() const;

public:
  // create a new image
  static GImage* Create(U32 w, U32 h, U32 f);

  // load the image
  static GImage* Load(const GData* data);

public:
	U32	mWidth, mHeight;
  U32 mFormat;
  std::vector<U8>mPixels;
};

//////////////////////////////////////////////////////////////////////////

typedef GPtr<GImage>GImagePtr;

//////////////////////////////////////////////////////////////////////////

#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif // __GImage__

//////////////////////////////////////////////////////////////////////////