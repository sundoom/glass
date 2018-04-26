/*
 *  Audio.h
 *  glare
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */

//////////////////////////////////////////////////////////////////////////

#ifndef __GAudio__
#define __GAudio__

//////////////////////////////////////////////////////////////////////////

#if defined __cplusplus

//////////////////////////////////////////////////////////////////////////

#include <Glass.h>

//////////////////////////////////////////////////////////////////////////

// Length of sound in seconds to be considered as looping forever
#define INDEFINITELY_LOOPING_DURATION	10000.0f

//////////////////////////////////////////////////////////////////////////

// this class provides an object-oriented GAudio interface.
class GAudio
{
public:
  // query the instance of the audio
  static GAudio& Instance();

  // update the audio device.
  VOID Update(F32 delta_time);

  // set the listener
  VOID Listen(const F32* location, const F32* orientation);

  // clean the audio device.
  VOID Clean();

  // play the wave
  VOID Play(GWave* wave);

  // stops the wave
  VOID Stop(GWave* wave);

private:
  // constructor
  GAudio();

  // destructor
  ~GAudio();

private:
  ALCdevice* mDevice;
  ALCcontext*	mContext;
  GAudioSource* mChannels;
  std::list<GAudioSource*>mFrees;
  std::list<GWavePtr>mWaves;
  F32 mLocation[3];
  F32 mOrientation[3];
};

//////////////////////////////////////////////////////////////////////////

#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif // __GAudio__

//////////////////////////////////////////////////////////////////////////