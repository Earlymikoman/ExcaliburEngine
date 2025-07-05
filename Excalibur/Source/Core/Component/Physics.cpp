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
	dt;

	cout << "Updated Physics" << endl;
}

void Physics::Render()
{

}
