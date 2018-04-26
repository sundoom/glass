/*
 *  GAudio.cpp
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

/*
====================
Instance
====================
*/ 
GAudio& GAudio::Instance()
{
  static GAudio s_audio;
	return s_audio;
}

//////////////////////////////////////////////////////////////////////////

// maximum number of channels
#define MAX_AUDIO_CHANNELS      64

//////////////////////////////////////////////////////////////////////////

GAudio::GAudio() : mDevice(NULL), mContext(NULL), mChannels(NULL)
{
  // open the device
  mDevice = alcOpenDevice(NULL);
  if(mDevice==NULL) GAssert("GAudio: could not open the al device!.");

  // create a context
  ALCint caps[] = 
  { 
    ALC_FREQUENCY, 44100,
    ALC_STEREO_SOURCES, 4, 
    0, 0
  };
  mContext = alcCreateContext(mDevice, caps);
  if(mContext==NULL) GAssert("GAudio: could not create a al context.");
  CHECK(alcMakeContextCurrent(mContext));

  // initialize channels.
  mChannels = GNEW(GAudioSource[MAX_AUDIO_CHANNELS]);
  CHECK(mChannels);
  for(U32 i = 0; i < MAX_AUDIO_CHANNELS; i++)
  {
    mFrees.push_back(&mChannels[i]);
  }

  // use our own distance model.
  alDistanceModel(AL_NONE);
}

GAudio::~GAudio() 
{
  // clean the device
  Clean();

  // push any pending data to the hardware
  if(mContext) alcProcessContext(mContext);

  // free all of the channels
  if(mChannels){GDELETE([]mChannels), mChannels = NULL;}

  // destroy the context
  if(mContext)
  {	
    alcDestroyContext(mContext);
    mContext = NULL;
  }

  // close the device
  if(mDevice)
  {	
    alcCloseDevice(mDevice);
    mDevice = NULL;
  }
}
//////////////////////////////////////////////////////////////////////////

static BOOL ComparePriority(const GWavePtr&a, const GWavePtr&b)
{
	return a->Priority() < b->Priority();
}

/*
====================
Update

  Update the audio device and calculates the cached inverse transform later
  on used for spatialization.
====================
*/
VOID GAudio::Update(F32 delta_time)
{
  // kill any sources that have finished
  for(U32 i = 0; i < MAX_AUDIO_CHANNELS; i++)
  {
    GAudioSource* source = &mChannels[i];
    if(source->IsFinished() && source->mWavePtr)
    {
      source->Stop();
			source->Bind(NULL);
      mFrees.push_back(source);
    }
  }

  // stop any waves that have finished
  std::list<GWavePtr>::iterator it = mWaves.begin();
  while(it != mWaves.end())
  {
    if((*it)->Duration() < INDEFINITELY_LOOPING_DURATION && (*it)->mPlaybackTime > (*it)->Duration())
    {
			if((*it)->mSource)
			{
				(*it)->mSource->Stop();
				(*it)->mSource->Bind(NULL);
				mFrees.push_back((*it)->mSource);
				(*it)->mSource = NULL;
			}
      it = mWaves.erase(it);
    }
    else
    {
      (*it)->mPlaybackTime += delta_time;
      it++;
    }
  }

  // sort all of the waves by priority
  mWaves.sort(ComparePriority);
  I32 FirstActiveIndex = MAX((I32)mWaves.size() - (I32)MAX_AUDIO_CHANNELS, 0);

  // update the waves
  I32 i = 0;
  for(it = mWaves.begin(); it != mWaves.end(); ++it)
  {
    GWavePtr& wave = *it;
    if(i < FirstActiveIndex)
    {
      // stop sources that need to be stopped
      if(wave->mSource)
      {
        wave->mSource->Stop();
				wave->mSource->Bind(NULL);
        mFrees.push_back(wave->mSource);
        wave->mSource = NULL;
      }
    }
    else
    {
      // start or update any sources that have a high enough priority to play
      if(wave->mSource == NULL)
      {
        CHECK(mFrees.size());
        wave->mSource = *mFrees.begin();
        mFrees.pop_front();

        // bind the wave buffer
        wave->mSource->Bind(wave.Get());         

        // playback might be deferred till the end of the update function on certain implementations.
        wave->mSource->Play();

        // update the source
        wave->mSource->Update();
      }
      else
      {
        // update the source
        wave->mSource->Update();
      }        
    }
    i++;
  }
  
  // set the listener
  alListenerfv(AL_POSITION, (ALfloat*)mLocation);
  alListenerfv(AL_ORIENTATION, (ALfloat*)mLocation);
  F32 velocity[3];
  velocity[0] = 0;
  velocity[1] = 0;
  velocity[2] = 0;
  alListenerfv(AL_VELOCITY, (ALfloat*)velocity);
}

/*
====================
Listen
====================
*/
VOID GAudio::Listen(const F32* location, const F32* orientation)
{
  mLocation[0] = location[0];
  mLocation[1] = location[1];
  mLocation[2] = location[2];
  mOrientation[0] = orientation[0];
  mOrientation[1] = orientation[1];
  mOrientation[2] = orientation[2];
}

/*
====================
Clean

  stop all the audio sources
====================
*/
VOID GAudio::Clean()
{
  mFrees.clear();
  for(U32 i = 0; i < MAX_AUDIO_CHANNELS; i++)
  {
    GAudioSource* source = &mChannels[i];
    source->Stop();
    source->Bind(NULL);
    mFrees.push_back(source);
  }
  mWaves.clear();
}

/*
====================
Play
====================
*/
VOID GAudio::Play(GWave* wave)
{
  CHECK(wave);
  mWaves.push_back(wave);
}

/*
====================
Stop
====================
*/
VOID GAudio::Stop(GWave* wave)
{
  CHECK(wave);
  std::list<GWavePtr>::iterator it = std::find(mWaves.begin(), mWaves.end(), wave);
  if(it != mWaves.end())
  {
		if((*it)->mSource)
		{
			(*it)->mSource->Stop();
			(*it)->mSource->Bind(NULL);
			mFrees.push_back((*it)->mSource);
			(*it)->mSource = NULL;
		}
    mWaves.erase(it);
  }    
}

//////////////////////////////////////////////////////////////////////////