/*
 *  GTransform.cpp
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

GTransform::GTransform()
{
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
}

GTransform::GTransform(const GTransform& other)
{
	m[0][0] = other.m[0][0];
	m[0][1] = other.m[0][1];
	m[0][2] = other.m[0][2];
	m[1][0] = other.m[1][0];
	m[1][1] = other.m[1][1];
	m[1][2] = other.m[1][2];
}

GTransform::GTransform(F32 m00, F32 m01, F32 m02, F32 m10, F32 m11, F32 m12)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
}

GTransform& GTransform::operator = (const GTransform& other)
{
	m[0][0] = other.m[0][0];
	m[0][1] = other.m[0][1];
	m[0][2] = other.m[0][2];
	m[1][0] = other.m[1][0];
	m[1][1] = other.m[1][1];
	m[1][2] = other.m[1][2];
	return *this;
}

BOOL GTransform::operator == (const GTransform& other) const
{
	return m[0][0] == other.m[0][0]
			&& m[0][1] == other.m[0][1]
			&& m[0][2] == other.m[0][2]
			&& m[1][0] == other.m[1][0]
			&& m[1][1] == other.m[1][1]
			&& m[1][2] == other.m[1][2];
}

BOOL GTransform::operator != (const GTransform& other) const
{
	return !operator == (other);
}

GTransform GTransform::operator * (const GTransform &other) const
{
	return GTransform(other.m[0][0] * m[0][0] + other.m[0][1] * m[1][0],
										other.m[0][0] * m[0][1] + other.m[0][1] * m[1][1],
										other.m[0][0] * m[0][2] + other.m[0][1] * m[1][2] + other.m[0][2],
										other.m[1][0] * m[0][0] + other.m[1][1] * m[1][0],
										other.m[1][0] * m[0][1] + other.m[1][1] * m[1][1],
										other.m[1][0] * m[0][2] + other.m[1][1] * m[1][2] + other.m[1][2]);
}

GPoint GTransform::operator * (const GPoint& pt) const
{
	return GPoint(m[0][0] * pt.X() + m[0][1] * pt.Y() + m[0][2],
								m[1][0] * pt.X() + m[1][1] * pt.Y() + m[1][2]);
}

GTransform GTransform::Invert() const
{
	F64 determinant = (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
	if (determinant != 0.0)
	{
		determinant = 1.0 / determinant;
		const F32 dst00 = (F32)( m[1][1] * determinant);
		const F32 dst10 = (F32)(-m[1][0] * determinant);
		const F32 dst01 = (F32)(-m[0][1] * determinant);
		const F32 dst11 = (F32)( m[0][0] * determinant);
		return GTransform(dst00, dst01, -m[0][2] * dst00 - m[1][2] * dst01,
											dst10, dst11, -m[0][2] * dst10 - m[1][2] * dst11);
	}
	else
	{
		return *this;
	}
}

GTransform GTransform::MakeScale(F32 sx, F32 sy)
{
	return GTransform(sx, 0, 0, 0, sy, 0);
}

GTransform GTransform::MakeTranslate(F32 x, F32 y)
{
	return GTransform(1.0f, 0, x, 0, 1.0f, y);
}

GTransform GTransform::MakeRotate(F32 angle)
{
	const F32 cosRad = ::cosf(angle);
	const F32 sinRad = ::sinf(angle);
	return GTransform(cosRad, -sinRad, 0, sinRad, cosRad, 0);
}

//////////////////////////////////////////////////////////////////////////