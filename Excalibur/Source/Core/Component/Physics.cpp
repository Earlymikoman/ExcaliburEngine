/*********************************************************************
 * @file   Physics.cpp
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

#include "Physics.h"

#include "../Object.h"

#include <iostream>

using std::cout;
using std::endl;

Physics::Physics
(
	Vector<3> const& OldTranslation
	, Vector<3> const& Acceleration
	, Vector<3> const& Velocity
	, float const& RotationalVelocity
	, float const& Drag
)
	: oldTranslation(OldTranslation)
	, acceleration(Acceleration)
	, velocity(Velocity)
	, rotationalVelocity(RotationalVelocity)
	, drag(Drag)
{
}

void Physics::Update(double& dt)
{
	oldTranslation = this->GetParent()->GetTransform()->GetPosition();

	Vector<3> timedAcceleration = acceleration;
	Vector<3> timedVelocity = velocity;

	VectorScale(timedAcceleration, (float)dt);
	VectorAddition(velocity, timedAcceleration);

	VectorScale(timedVelocity, (float)dt);

	Vector<3> newPosition = oldTranslation;
	VectorAddition(newPosition, timedVelocity);

	this->GetParent()->GetTransform()->SetPosition(newPosition);
}

void Physics::Render()
{

}

void Physics::HandleMessage(Message* message)
{
	message;
}
