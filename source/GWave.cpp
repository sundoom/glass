/*
 *  GWave.cpp
 *  glare
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

GWave::GWave()
{
  mSource = NULL;    
  mPriority = 0.0f;
  mDuration = 0.0f;
  mVolume = 1.0f;
  mLooping = FALSE;
  mSpatialization = FALSE;
  mPitch = 1.0f;
  mPlaybackTime = 0.0f;
}

GWave::~GWave() 
{
  
}

//////////////////////////////////////////////////////////////////////////

/*
====================
Buffer
====================
*/
VOID GWave::Buffer(const GAudioBuffer* buffer)
{
	mBuffer = (GAudioBuffer*)buffer;
}

const GAudioBuffer* GWave::Buffer() const
{
	return mBuffer.Get();
}

/*
====================
Priority
====================
*/
VOID GWave::Priority(F32 p)
{
  mPriority = p;
}

F32 GWave::Priority() const
{
  return mPriority;
}

/*
====================
Duration
====================
*/
VOID GWave::Duration(F32 d)
{
  mDuration = d;
}

F32 GWave::Duration() const
{
  return mDuration;
}

/*
====================
Volume
====================
*/
VOID GWave::Volume(F32 v)
{
  mVolume = v;
}

F32 GWave::Volume() const
{
  return mVolume;
}

/*
====================
Looping
====================
*/
VOID GWave::Looping(BOOL b)
{
  mLooping = b;
}

BOOL GWave::Looping() const
{
  return mLooping;
}

/*
====================
Spatialization
====================
*/
VOID GWave::Spatialization(BOOL b)
{
  mSpatialization = b;
}

BOOL GWave::Spatialization() const
{
  return mSpatialization;
}

/*
====================
Pitch
====================
*/
VOID GWave::Pitch(F32 p)
{
  mPitch = p;
}

F32 GWave::Pitch() const
{
  return mPitch;
}

/*
====================
Velocity
====================
*/
VOID GWave::Velocity(const F32* v)
{
  mVelocity[0] = v[0];
  mVelocity[1] = v[1];
  mVelocity[2] = v[2];
}

const F32* GWave::Velocity() const
{
  return mVelocity;
}

/*
====================
Location
====================
*/
VOID GWave::Location(const F32* v)
{
  mLocation[0] = v[0];
  mLocation[1] = v[1];
  mLocation[2] = v[2];
}

const F32* GWave::Location() const
{
  return mLocation;
}

//////////////////////////////////////////////////////////////////////////