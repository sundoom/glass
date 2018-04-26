/*
 *  GRect.cpp
 *  glass
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */
//////////////////////////////////////////////////////////////////////////

#include <Glass.h>

//////////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////////

GRect::GRect()
{
  mX = mY = mWidth = mHeight = 0;
}

GRect::GRect(const GRect& other)
{
  mX = other.mX;
  mY = other.mY;
  mWidth = other.mWidth;
  mHeight = other.mHeight;
}

GRect::GRect(F32 x, F32 y, F32 width, F32 height)
{
  mX = x;
  mY = y;
  mWidth = width;
  mHeight = height;
}

BOOL GRect::Valid() const
{
  return mWidth > 0 && mHeight > 0;
}

F32& GRect::X()
{
  return mX;
}

F32& GRect::Y()
{
  return mY;
}

F32 GRect::X() const
{
  return mX;
}

F32 GRect::Y() const
{
  return mY;
}

F32& GRect::Width()
{
  return mWidth;
}

F32& GRect::Height()
{
  return mHeight;
}

F32 GRect::Width() const
{
  return mWidth;
}

F32 GRect::Height() const
{
  return mHeight;
}

BOOL GRect::PtInRect(F32 x, F32 y) const
{
  return  x >= mX && 
          y >= mY && 
          x < mX + mWidth && 
          y < mY + mHeight;
}

BOOL GRect::PtInRect(const GPoint& pt) const
{
  return  pt.X() >= mX && 
          pt.Y() >= mY && 
          pt.X() < mX + mWidth && 
          pt.Y() < mY + mHeight;
}

BOOL GRect::Intersect(const GRect& other) const
{
  return  Valid() && 
          mX + mWidth > other.mX && 
          mY + mHeight > other.mY && 
          mX < other.mX + other.mWidth && 
          mY < other.mY + other.mHeight;
}

BOOL GRect::Intersect(GRect& dst, const GRect& src) const
{
  dst.mX      = MAX(mX, src.mX);
  dst.mY      = MAX(mY, src.mY);
  dst.mWidth  = MIN(mX + mWidth,  src.mX + src.mWidth)  - dst.mX;
  dst.mHeight = MIN(mY + mHeight, src.mY + src.mHeight) - dst.mY;
  return dst.Valid();
}

GRect& GRect::operator= (const GRect& other)
{
  mX      = other.mX;
  mY      = other.mY;
  mWidth  = other.mWidth; 
  mHeight = other.mHeight;
  return *this;
}

GRect GRect::operator+ (const GPoint& pt) const
{
  return GRect(mX + pt.X(), mY + pt.Y(), mWidth, mHeight);
}

GRect& GRect::operator+= (const GPoint& pt)
{
  mX += pt.X();
  mY += pt.Y();
  return *this;
}

GRect GRect::operator- (const GPoint& pt) const
{
  return GRect(mX - pt.X(), mY - pt.Y(), mWidth, mHeight);
}

GRect& GRect::operator-= (const GPoint& pt)
{
  mX -= pt.X();
  mY -= pt.Y();
  return *this;
}

BOOL GRect::operator== (const GRect& other) const
{
  return mX == other.mX && mY == other.mY && mWidth == other.mWidth && mHeight == other.mHeight;
}

BOOL GRect::operator!= (const GRect& other) const
{
  return mX != other.mX || mY != other.mY || mWidth != other.mWidth || mHeight != other.mHeight;
}

//////////////////////////////////////////////////////////////////////////