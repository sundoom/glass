/*
 *  GPoint.h
 *  glass
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */

//////////////////////////////////////////////////////////////////////////

#ifndef __GPoint__
#define __GPoint__

//////////////////////////////////////////////////////////////////////////

#if defined __cplusplus

//////////////////////////////////////////////////////////////////////////

// this class provides an object-oriented GPoint interface.
class GPoint 
{
public:
	// constructor
	GPoint();

  // creates a copy of another point.
  GPoint(const GPoint& other);

  // creates a point from an (x, y) position.
  GPoint (F32 x, F32 y);

  // copies this point from another one.
  GPoint& operator= (const GPoint& other);

  BOOL operator== (const GPoint& other) const;
  BOOL operator!= (const GPoint& other) const;

  F32& X();
  F32& Y();

  F32 X() const;
  F32 Y() const;

  // adds two points together.
  GPoint operator+ (const GPoint& other) const;

  // adds another point's co-ordinates to this one.
  GPoint& operator+= (const GPoint& other);

  // subtracts one points from another.
  GPoint operator- (const GPoint& other) const;

  // subtracts another point's co-ordinates to this one.
  GPoint& operator-= (const GPoint& other);

  // returns a point whose coordinates are multiplied by a given value.
  GPoint operator* (F32 multiplier) const;

  // multiplies the point's co-ordinates by a value.
  GPoint& operator*= (F32 multiplier);

  // returns a point whose coordinates are divided by a given value.
  GPoint operator/ (F32 divisor) const;

  // divides the point's co-ordinates by a value.
  GPoint& operator/= (F32 divisor);

  // returns the inverse of this point.
  GPoint operator-() const;

  // returns the straight-line distance between this point and another one.
  F32 Distance(const GPoint& other) const;

private:
  F32 mX, mY;
};

//////////////////////////////////////////////////////////////////////////

#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif // __GPoint__

//////////////////////////////////////////////////////////////////////////