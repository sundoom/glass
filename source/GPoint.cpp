/*
 *  GPoint.cpp
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

GPoint::GPoint()
{
  mX = mY = 0;
}

GPoint::GPoint(const GPoint& other)
{
  mX = other.mX;
  mY = other.mY;
}

GPoint::GPoint(F32 x, F32 y)
{
  mX = x;
  mY = y;
}

GPoint& GPoint::operator= (const GPoint& other)
{
  mX = other.mX; 
  mY = other.mY; 
  return *this;
}

BOOL GPoint::operator== (const GPoint& other) const
{
  return mX == other.mX && mY == other.mY;
}

BOOL GPoint::operator!= (const GPoint& other) const
{
  return mX != other.mX || mY != other.mY;
}

F32& GPoint::X()
{
  return mX;
}

F32& GPoint::Y()
{
  return mY;
}

F32 GPoint::X() const
{
  return mX;
}

F32 GPoint::Y() const
{
  return mY;
}

GPoint GPoint::operator+ (const GPoint& other) const
{
  return GPoint(mX + other.mX, mY + other.mY);
}

GPoint& GPoint::operator+= (const GPoint& other)
{
  mX += other.mX; 
  mY += other.mY; 
  return *this;
}

GPoint GPoint::operator- (const GPoint& other) const
{
  return GPoint(mX - other.mX, mY - other.mY);
}

GPoint& GPoint::operator-= (const GPoint& other)
{
  mX -= other.mX; 
  mY -= other.mY; 
  return *this;
}

GPoint GPoint::operator* (F32 multiplier) const
{
  return GPoint(mX * multiplier, mY * multiplier);
}

GPoint& GPoint::operator*= (F32 multiplier)
{
  mX *= multiplier; 
  mY *= multiplier; 
  return *this;
}

GPoint GPoint::operator/ (F32 divisor) const
{
  return GPoint(mX / divisor, mY / divisor);
}

GPoint& GPoint::operator/= (F32 divisor)
{
  mX /= divisor; 
  mY /= divisor; 
  return *this;
}

GPoint GPoint::operator-() const
{
  return GPoint (-mX, -mY);
}

F32 GPoint::Distance(const GPoint& other) const
{
#if _WIN32
  return static_cast<F32>(_hypot(mX - other.mX, mY - other.mY));
#else
  return static_cast<F32>(hypot(mX - other.mX, mY - other.mY));
#endif
}

//////////////////////////////////////////////////////////////////////////