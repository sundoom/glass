/*
 *  GData.cpp
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

GData::GData()
{

}

GData::GData(U32 size)
{
	mData.resize(size);
}

GData::GData(U32 size, U8 value)
{
	mData.resize(size, value);
}

GData::~GData()
{

}

//////////////////////////////////////////////////////////////////////////

/*
====================
Size
====================
*/
VOID GData::Size(U32 size)
{
	mData.resize(size);
}

VOID GData::Size(U32 size, U8 value)
{
	mData.resize(size, value);
}

U32 GData::Size() const
{
	return mData.size();
}

/*
====================
Get
====================
*/
VOID* GData::Get() const
{
	if(mData.size()) return (VOID*)&mData[0];
	return NULL;
}
	
//////////////////////////////////////////////////////////////////////////
