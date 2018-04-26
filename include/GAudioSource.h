/*
 *  GAudioSource.h
 *  glare
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */

//////////////////////////////////////////////////////////////////////////

#ifndef __GAudioSource__
#define __GAudioSource__

//////////////////////////////////////////////////////////////////////////

#if defined __cplusplus

//////////////////////////////////////////////////////////////////////////

// this class provides an object-oriented GAudioSource interface.
class GAudioSource
{
public:
	// constructor
	GAudioSource();
	
	// destructor
	virtual ~GAudioSource();

  // bind the wave
  VOID Bind(const GWave* wave);

  // update the data
  VOID Update();

  // play the current wave instance.
  VOID Play();

  // stops the current wave instance and detaches it from the source.	
  VOID Stop();

  // pauses playback of current wave instance.
  VOID Pause();

	// queries the status of the currently associated wave
	BOOL IsFinished();

private:
  ALuint mObject;
  BOOL mPlaying, mPaused;
  GWavePtr mWavePtr;

private:friend class GAudio;
}; 

//////////////////////////////////////////////////////////////////////////

#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif // __GAudioSource__

//////////////////////////////////////////////////////////////////////////