/*********************************************************************
 * @file   Transform.cpp
 * @brief  .
 * 
 * Project: Excalibur
 * 
 * @author Xander Boosinger (xboosinger@gmail.com)
 * @date   April 2025
 * 
 *********************************************************************
/*
 *			*	/\
 *			   / /	*
 *		*	__/ /__
 *		      /	  *
 *			 /
 */

#include "Transform.h"

Transform& Transform::operator+=(Transform const& rhs)
{
	VectorAddition(position, rhs.position);
	rotation += rhs.rotation;
	VectorAddition(scale, rhs.scale);

	return *this;
}

char Transform::PointOver(Vector<3> const& point)
{
	if (
		point.X() > (position.X() - (scale.X() / 2))
		&& point.X() < (position.X() + (scale.X() / 2))
		&& point.Y() > (position.Y() - (scale.Y() / 2))
		&& point.Y() < (position.Y() + (scale.Y() / 2))
		)
	{
		return 1;
	}

	return 0;
}

void Transform::AddPosition(Vector<3> const& rhs)
{
	VectorAddition(position, rhs);
}

void Transform::AddRotation(float const& rhs)
{
	rotation += rhs;
}

void Transform::AddScale(Vector<3> const& rhs)
{
	VectorAddition(scale, rhs);
}

void Transform::MultiplyScale(Vector<3> const& rhs)
{
	VectorMultiply(scale, rhs);
}

void Transform::HandleMessage(Message* message)
{
	message;
}
