/*
 *  GAudioBuffer.h
 *  glare
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */

//////////////////////////////////////////////////////////////////////////

#ifndef __GAudioBuffer__
#define __GAudioBuffer__

//////////////////////////////////////////////////////////////////////////

#if defined __cplusplus

//////////////////////////////////////////////////////////////////////////

// this class provides an object-oriented GAudioBuffer interface.
class GAudioBuffer : public GReference
{
public:
  // constructor
  GAudioBuffer();

  // destructor
  virtual ~GAudioBuffer(); 

  // load the data
  VOID Load(U32 format, U32 rate, const VOID* data, U32 size);

private:
  ALuint mObjects[2];

private:friend class GAudioSource;
}; 

//////////////////////////////////////////////////////////////////////////

typedef GPtr<GAudioBuffer>GAudioBufferPtr;

//////////////////////////////////////////////////////////////////////////

#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif // __GAudioBuffer__

//////////////////////////////////////////////////////////////////////////