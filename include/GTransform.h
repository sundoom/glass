/*
 *  GTransform.h
 *  glass
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */

//////////////////////////////////////////////////////////////////////////

#ifndef __GTransform__
#define __GTransform__

//////////////////////////////////////////////////////////////////////////

#if defined __cplusplus

//////////////////////////////////////////////////////////////////////////

// this class provides an object-oriented GTransform interface.
class GTransform 
{
public:
	// constructor
	GTransform();

  // creates a copy of another point.
  GTransform(const GTransform& other);

	// creates a transform from a set of raw matrix values.
	GTransform(F32 m00, F32 m01, F32 m02, F32 m10, F32 m11, F32 m12);

	// copies from another transform object
	GTransform& operator = (const GTransform& other);

	// compares two transforms.
	BOOL operator == (const GTransform& other) const;

	// compares two transforms.
	BOOL operator != (const GTransform& other) const;

	// ret = other * this.
	GTransform operator * (const GTransform &other) const;

	// ret = pt * this.
	GPoint operator * (const GPoint& pt) const;

	// returns a transform which is the inverse operation of this one.
	GTransform Invert() const;

	// make a scale transform
	static GTransform MakeScale(F32 sx, F32 sy);

	// make a translate transform
	static GTransform MakeTranslate(F32 x, F32 y);

	// make a rotate transform
	static GTransform MakeRotate(F32 angle);

public:
	static const GTransform identity;

private: 
	F32 m[2][3];
};

//////////////////////////////////////////////////////////////////////////

#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif // __GTransform__

//////////////////////////////////////////////////////////////////////////