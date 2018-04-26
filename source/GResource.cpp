/*
 *  GResource.cpp
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
  
GResource::GResource(const CHAR* name)
{
  CHECK(name);
  mName = name;
  Add(name, this);
}

GResource::~GResource()
{
  Remove(mName.c_str());
}

//////////////////////////////////////////////////////////////////////////

std::map<Str, GResource*> GResource::s_res_map;

//////////////////////////////////////////////////////////////////////////  

/*
====================
add
====================
*/  
VOID GResource::Add(const CHAR* name, GResource* res)
{
  CHECK(name);
  if(s_res_map.find(name) != s_res_map.end()) GAssert(VA("The resource(%s) is existent already!", name));
  s_res_map.insert(std::make_pair(name, res));
}

/*
====================
remove
====================
*/
VOID GResource::Remove(const CHAR* name)
{
	CHECK(name);
  std::map<Str, GResource*>::iterator it = s_res_map.find(name);
  if(it == s_res_map.end()) GAssert(VA("Can`t find the resource : %s.", name));
  s_res_map.erase(it);
}
	
//////////////////////////////////////////////////////////////////////////