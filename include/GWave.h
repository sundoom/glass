/*
 *  GWave.h
 *  glare
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */

//////////////////////////////////////////////////////////////////////////

#ifndef __GWave__
#define __GWave__

//////////////////////////////////////////////////////////////////////////

#if defined __cplusplus

//////////////////////////////////////////////////////////////////////////

class GAudioBuffer;
class GAudioSource;

//////////////////////////////////////////////////////////////////////////

// this class provides an object-oriented GWave interface.
class GWave : public GReference
{
public:
	// constructor
	GWave();
	
	// destructor
	virtual ~GWave();

  // set/get the audio buffer
  VOID Buffer(const GAudioBuffer* buffer);
  const GAudioBuffer* Buffer() const;

  // set/get the priority
  VOID Priority(F32 p);
  F32 Priority() const;

  // set/get the duration
  VOID Duration(F32 d);
  F32 Duration() const;  

  // set/get the volume
  VOID Volume(F32 v);
  F32 Volume() const;

  // set/get the looping
  VOID Looping(BOOL b);
  BOOL Looping() const;

  // set/get the spatialization
  VOID Spatialization(BOOL b);
  BOOL Spatialization() const;

  // set/get the pitch
  VOID Pitch(F32 p);
  F32 Pitch() const;

  // set/get the velocity
  VOID Velocity(const F32* v);
  const F32* Velocity() const;

  // set/get the location
  VOID Location(const F32* v);
  const F32* Location() const;   

private:
  GPtr<GAudioBuffer>mBuffer;
  GAudioSource* mSource;
  F32   mPriority;
  F32   mDuration;
  F32   mVolume;
  BOOL  mLooping;    
  BOOL  mSpatialization;
  F32	  mPitch;    
  F32   mVelocity[3]; // unit : meters.
  F32   mLocation[3]; // unit : meters.
  F32   mPlaybackTime;

private:friend class GAudio;
};

//////////////////////////////////////////////////////////////////////////

typedef GPtr<GWave>GWavePtr;

//////////////////////////////////////////////////////////////////////////

#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif // __GWave__

//////////////////////////////////////////////////////////////////////////