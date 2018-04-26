/*
 *  GAudioBuffer.cpp
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

GAudioBuffer::GAudioBuffer()
{
  // create the al buffer.
  alGenBuffers(1, mObjects);
  CHECK(alGetError() == AL_NO_ERROR && "Could not create buffers");
}

GAudioBuffer::~GAudioBuffer() 
{
  // delete al buffer.
  alDeleteBuffers(1, mObjects);
}

//////////////////////////////////////////////////////////////////////////

/*
====================
Load
====================
*/
VOID GAudioBuffer::Load(U32 format, U32 rate, const VOID* data, U32 size)
{
  CHECK(data);
  alBufferData(mObjects[0], format, data, size, rate);
}

//////////////////////////////////////////////////////////////////////////