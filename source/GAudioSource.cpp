/*
 *  GAudioSource.cpp
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

GAudioSource::GAudioSource() : mObject(0), mPlaying(FALSE), mPaused(FALSE)
{
  // create the al source.
  alGenSources(1, &mObject);
  CHECK(alGetError()==AL_NO_ERROR && "Could not create source");
}

GAudioSource::~GAudioSource() 
{
  // delete the al source.
  if(mObject)
  {
    alDeleteSources(1, &mObject);
    mObject = 0;
  }
}

//////////////////////////////////////////////////////////////////////////

/*
====================
Bind
====================
*/
VOID GAudioSource::Bind(const GWave* wave)
{ 
  mWavePtr = (GWave*)wave;
	if(mWavePtr)
	{
		// enable/disable spatialisation of sounds
		alSourcei(mObject, AL_SOURCE_RELATIVE, mWavePtr->Spatialization() ? AL_FALSE : AL_TRUE);

		// setting looping on a real time decompressed source suppresses the buffers processed message
		alSourcei(mObject, AL_LOOPING, (mWavePtr->Looping() ? AL_TRUE : AL_FALSE));

		// always queue up the first buffer
		alSourceQueueBuffers(mObject, 1, mWavePtr->Buffer()->mObjects);
	}
}

/*
====================
Update
====================
*/
VOID GAudioSource::Update()
{
  if(mWavePtr==NULL) return;
  
  F32 Volume = CLAMP(0.0f, mWavePtr->Volume(), 1.0f);
  F32 Pitch = CLAMP(0.4f, mWavePtr->Pitch(), 2.0f);

  // See file header for coordinate system explanation.
  F32 Location[3], Velocity[3];
  Location[0] = mWavePtr->Location()[0];
  Location[1] = mWavePtr->Location()[2]; // Z/Y swapped on purpose, see file header
  Location[2] = mWavePtr->Location()[1]; // Z/Y swapped on purpose, see file header
  Velocity[0] = mWavePtr->Velocity()[0];
  Velocity[1] = mWavePtr->Velocity()[2]; // Z/Y swapped on purpose, see file header
  Velocity[2] = mWavePtr->Velocity()[1]; // Z/Y swapped on purpose, see file header    

  // We're using a relative coordinate system for un- spatialized sounds.
  if(!mWavePtr->Spatialization())
  {
    Location[0] = 0.f;
    Location[1] = 0.f;
    Location[2] = 0.f;
  }

  alSourcef(mObject, AL_GAIN, Volume);	
  alSourcef(mObject, AL_PITCH, Pitch);	
  alSourcefv(mObject, AL_POSITION, (ALfloat*)&Location);
  alSourcefv(mObject, AL_VELOCITY, (ALfloat*)&Velocity);
}

//////////////////////////////////////////////////////////////////////////

/*
====================
Play
====================
*/
VOID GAudioSource::Play()
{
  alSourcePlay(mObject);
  mPaused = FALSE;
  mPlaying = TRUE;
}

/*
====================
Stop
====================
*/
VOID GAudioSource::Stop()
{
  alSourceStop(mObject);
  // This clears out any pending buffers that may or may not be queued or played
  alSourcei(mObject, AL_BUFFER, 0);
  mPaused = FALSE;
  mPlaying = FALSE;
}

/*
====================
Pause
====================
*/
VOID GAudioSource::Pause()
{
  alSourcePause(mObject);
  mPaused = TRUE;
}

/*
====================
IsFinished

	return TRUE if the wave instance/ source has finished 
	playback and FALSE if it is currently playing or paused.
====================
*/
BOOL GAudioSource::IsFinished()
{
  if(mWavePtr==NULL) return TRUE;

  ALint state = AL_STOPPED;
  alGetSourcei(mObject, AL_SOURCE_STATE, &state);
	if(state != AL_PLAYING && state != AL_PAUSED)
	{
		return TRUE;
	}
	else
	{
		// check to see if any complete buffers have been processed
		ALint BuffersProcessed;
		alGetSourcei(mObject, AL_BUFFERS_PROCESSED, &BuffersProcessed);
		switch(BuffersProcessed)
		{
		case 0: // No buffers need updating
			break;
		case 1: // Standard case of 1 buffer expired which needs repopulating
      {
        ALuint dequeued_buffer;
        // Unqueue the processed buffers
        alSourceUnqueueBuffers(mObject, 1, &dequeued_buffer);
        // Queue the same packet again for looping
        alSourceQueueBuffers(mObject, 1, mWavePtr->Buffer()->mObjects);
      }
			break;
		case 2: // Starvation case when the source has stopped 
      {
        ALuint dequeued_buffer;
        // Unqueue the processed buffers
        alSourceUnqueueBuffers(mObject, 1, &dequeued_buffer);
        // Queue the same packet again for looping
        alSourceQueueBuffers(mObject, 1, mWavePtr->Buffer()->mObjects);
        // Unqueue the processed buffers
        alSourceUnqueueBuffers(mObject, 1, &dequeued_buffer);
        // Queue the same packet again for looping
        alSourceQueueBuffers(mObject, 1, mWavePtr->Buffer()->mObjects);
        alSourcePlay(mObject);
      }
			break;
		}
	}
  return FALSE;
}

//////////////////////////////////////////////////////////////////////////