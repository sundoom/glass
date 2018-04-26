/*
 *  GRect.h
 *  glass
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */

//////////////////////////////////////////////////////////////////////////

#ifndef __GRect__
#define __GRect__

//////////////////////////////////////////////////////////////////////////

#if defined __cplusplus

//////////////////////////////////////////////////////////////////////////

// this class provides an object-oriented GRect interface.
class GRect 
{
public:
	// constructor
	GRect();	

  GRect(const GRect& other);

  GRect(F32 x, F32 y, F32 width, F32 height);

  BOOL Valid() const;

  F32& X();
  F32& Y();

  F32 X() const;
  F32 Y() const;

  F32& Width();
  F32& Height();

  F32 Width() const;
  F32 Height() const;
  
  BOOL PtInRect(F32 x, F32 y) const;
  BOOL PtInRect(const GPoint& pt) const;
  
  BOOL Intersect(const GRect& other) const;
  BOOL Intersect(GRect& dst, const GRect& src) const;

  GRect& operator= (const GRect& other);

  GRect operator+ (const GPoint& pt) const;  
  GRect& operator+= (const GPoint& pt);
  GRect operator- (const GPoint& pt) const;  
  GRect& operator-= (const GPoint& pt);
  
  BOOL operator== (const GRect& other) const;
  BOOL operator!= (const GRect& other) const;

private:
  F32 mX, mY, mWidth, mHeight;
};

//////////////////////////////////////////////////////////////////////////

#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif // __GRect__

//////////////////////////////////////////////////////////////////////////