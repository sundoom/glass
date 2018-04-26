/*
 *  UIComponent.cpp
 *  glass
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */
//////////////////////////////////////////////////////////////////////////

#include <Glass.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UIComponent::UIComponent() 
	: mParent(NULL)
	, mTransparency(0.0f)
	, mShow(FALSE)
	, mEnabled(FALSE)
{
}

UIComponent::UIComponent(const Str& name)
	: mParent(NULL)
	, mTransparency(0.0f)
	, mShow(FALSE)
	, mEnabled(FALSE)
{
	mName = name;
}

UIComponent::~UIComponent() 
{

}

/*
====================
SetName
====================
*/
VOID UIComponent::SetName(const Str& name)
{
	mName = name;
}

/*
====================
GetName
====================
*/
const Str& UIComponent::GetName() const
{
	return mName;
}

/*
====================
AddChild
====================
*/
VOID UIComponent::AddChild(UIComponent* child, I32 z_order)
{
	if (child != NULL && child->mParent != this)
	{
		if (child->mParent)
		{
			child->mParent->RemoveChild(child);
		}

		child->mParent = this;

		if (z_order < 0 || z_order > (I32)mChildren.size())
			z_order = mChildren.size();

		mChildren.insert((mChildren.begin() + z_order), child);
	}
}

/*
====================
RemoveChild
====================
*/
VOID UIComponent::RemoveChild(UIComponent* child)
{
	if(child == NULL) return;
	std::vector<UIComponent*>::iterator it = std::find(mChildren.begin(), mChildren.end(), child);
	if (it != mChildren.end())
	{
		mChildren.erase(it);
		child->mParent = NULL;
	}
}

/*
====================
SetParent
====================
*/
VOID UIComponent::SetParent(UIComponent*parent)
{
	if (mParent)
	{
		mParent->RemoveChild(this);
	}
	mParent = parent;
}

/*
====================
GetParent
====================
*/
UIComponent* UIComponent::GetParent() const
{
	return mParent;
}

/*
====================

====================
*/
VOID UIComponent::Show(BOOL visible)
{
	mShow = visible;
}

/*
====================

====================
*/
BOOL UIComponent::IsShow() const
{
	return mShow;
}

/*
====================

====================
*/
VOID UIComponent::Enabled(BOOL enabled)
{
	mEnabled = enabled;
}

/*
====================
IsEnabled
====================
*/
BOOL UIComponent::IsEnabled() const
{
	return mEnabled;
}

/*
====================
Settransparency
====================
*/
VOID UIComponent::SetTransparency(F32 t)
{
	mTransparency = t;
}

/*
====================
GetTransparency
====================
*/
F32 UIComponent::GetTransparency() const
{
	return mTransparency;
}

/*
====================
SetTransform
====================
*/
VOID UIComponent::SetTransform(const GTransform& transform, BOOL is_local)
{
	GTransform t = transform;
	if (!is_local)
	{
		if (mParent)
		{
			t = t * mParent->mWorld.Invert();
		}
	}

	BOOL is_update = FALSE;
	if (mLocal != t)
	{
		mLocal = t;
		is_update = TRUE;
	}
	if (is_update) UpdateTransform();
}

/*
====================
GetTransform
====================
*/
const GTransform& UIComponent::GetTransform(BOOL is_local) const
{
	if (is_local) return mLocal;
	return mWorld;
}

/*
====================
UpdateTransform
====================
*/
VOID UIComponent::UpdateTransform()
{
	if (mParent)
	{ 
		mWorld = mLocal * mParent->mWorld;
	} 
	else
	{
		mWorld = mLocal;
	}

	for (U32 i = 0; i < mChildren.size(); i++)
	{
		mChildren[i]->UpdateTransform();
	}
}

/*
====================
SetWidth
====================
*/
VOID UIComponent::SetWidth(F32 width)
{
	if (mWidth != width)
	{
		mWidth = width;
	}
}

/*
====================
GetWidth
====================
*/
F32 UIComponent::GetWidth() const
{
	return mWidth;
}

/*
====================
SetHeight
====================
*/
VOID UIComponent::SetHeight(F32 height)
{
	if (mHeight != height)
	{
		mHeight = height;
	}
}

/*
====================
GetHeight
====================
*/
F32 UIComponent::GetHeight() const
{
	return mHeight;
}

/*
====================
HitTest
====================
*/
BOOL UIComponent::HitTest(const GPoint& pt)
{
	return FALSE;
}

/*
====================
Contains
====================
*/
BOOL UIComponent::Contains(GPoint local_point)
{
	return FALSE;
}

/*
====================
At
====================
*/
UIComponent* UIComponent::At(const GPoint& pt)
{
	return NULL;
}

/*
====================
HandleInput
====================
*/
VOID UIComponent::HandleInput()
{

}

//////////////////////////////////////////////////////////////////////////