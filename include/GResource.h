/*
 *  GResource.h
 *  glare
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */

//////////////////////////////////////////////////////////////////////////

#ifndef __GResource__
#define __GResource__

//////////////////////////////////////////////////////////////////////////

#if defined __cplusplus

//////////////////////////////////////////////////////////////////////////

// this class provides an object-oriented GResource interface.  
class GResource : public GReference
{
protected:
	// constructor
	GResource(const CHAR* name);
	
	// destructor
	virtual ~GResource();

	// load the data
	virtual VOID Load(const GData* data) = 0;

protected:
  Str mName;

public:
  template<typename T> 
  static T* Find(const CHAR* name)
  {
    CHECK(name);
    std::map<Str, GResource*>::iterator it = s_res_map.find(name);
    if(it != s_res_map.end()) return dynamic_cast<T*>(it->second);
    T*res = GNEW(T(name));
    res->Load((GData*)GLoad(name));
    return res;
  }
private:		
  static VOID Add(const CHAR* name, GResource* res);
  static VOID Remove(const CHAR* name);
private:
  static std::map<Str, GResource*>s_res_map;
};

//////////////////////////////////////////////////////////////////////////

#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif // __GResource__

//////////////////////////////////////////////////////////////////////////