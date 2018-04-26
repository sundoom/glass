/*
 *  UIComponent.h
 *  glass
 *
 *  Created by sunjun on 11-6-14.
 *  Copyright 2011 sunstdio. All rights reserved.
 *
 */
//////////////////////////////////////////////////////////////////////////

#ifndef __UIComponent__
#define __UIComponent__

//////////////////////////////////////////////////////////////////////////

#if defined __cplusplus

//////////////////////////////////////////////////////////////////////////

#include <Glass.h>

//////////////////////////////////////////////////////////////////////////

// this class provides an object-oriented UIComponent interface.
class UIComponent
{
public:		
	// constructor
	UIComponent();

	// constructor
	explicit UIComponent(const Str& name);

	// destructor
	virtual ~UIComponent();

	// set/get the name of this component.
	virtual VOID SetName(const Str& name);
	const Str& GetName() const;

	// add/remove a child component to this one.
	VOID AddChild(UIComponent* child, I32 z_order = -1);		
	VOID RemoveChild(UIComponent* child);

	// set/get the parent component
	VOID SetParent(UIComponent* parent);
	UIComponent* GetParent() const;

	// show the component visible or invisible.
	virtual VOID Show(BOOL visible);
	BOOL IsShow() const;

	// enables or disables this component.
	VOID Enabled(BOOL enabled);
	BOOL IsEnabled() const;

	// set/get the component's current transparancy level.
	VOID SetTransparency(F32 t);
	F32 GetTransparency() const;	

	// set/get the component's transform.
	VOID SetTransform(const GTransform& transform, BOOL is_local = TRUE);
	const GTransform& GetTransform(BOOL is_local = TRUE) const;

	// set/get the width and the height
	VOID SetWidth(F32 width);
	F32 GetWidth() const;
	VOID SetHeight(F32 height);
	F32 GetHeight() const;

	// tests whether a given point inside the component.
	virtual BOOL HitTest(const GPoint& pt);

	// returns true if a given point lies within this component or one of its children.
	BOOL Contains(GPoint local_point);

	// returns the component at a certain point within this one.
	UIComponent* At(const GPoint& pt);

	// handle the input event
	virtual VOID HandleInput();

protected:
	VOID UpdateTransform();

protected:
	Str mName;
	UIComponent* mParent;
	std::vector<UIComponent*>mChildren;
	F32 mTransparency;
	BOOL mShow;
	BOOL mEnabled;
	GTransform mLocal, mWorld;
	F32 mWidth, mHeight;
};

//////////////////////////////////////////////////////////////////////////

#endif // __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif

//////////////////////////////////////////////////////////////////////////