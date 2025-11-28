/*********************************************************************
 * @file   Repulsor.cpp
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

#include "Repulsor.h"

#include "../Object.h"

#include <iostream>

#include <cmath>

#define MINIMUM_STRENGTH 0
#define MAXIMUM_STRENGTH 25000

using std::cout;
using std::endl;

Repulsor::Repulsor(Vector<4> const& Bounds, Object* const& RepulsionObject, float const& RepulsionStrength)
	: bounds(Bounds)
	, repulsionObject(RepulsionObject)
	, repulsionStrength(RepulsionStrength)
{
}

void Repulsor::Update(double& dt)
{
	auto thisPoint = this->GetParent()->GetAdjustedTransform().GetPosition();
	auto repulsePoint = repulsionObject->GetAdjustedTransform().GetPosition();
	auto repulsionVector = thisPoint;

	VectorSubtraction(repulsionVector, repulsePoint);

	float distance = VectorLength(repulsionVector);
	float totalStrength = repulsionStrength * powf(distance + 1, -1);

	/*cout << "Distance: " << distance << endl;
	cout << "TotalStrength: " << totalStrength << endl;
	cout << endl;*/

	if (totalStrength < MINIMUM_STRENGTH)
	{
		return;
	}

	if (totalStrength > MAXIMUM_STRENGTH)
	{
		totalStrength = MAXIMUM_STRENGTH;
	}

	VectorNormalize(repulsionVector);
	VectorScale(repulsionVector, totalStrength * (float)dt);

	VectorAddition(thisPoint, repulsionVector);



	Transform updatedTransform = this->GetParent()->GetAdjustedTransform();
	//Object* thisObject = this->GetParent();

	if (thisPoint.X() < bounds[0])
	{
		thisPoint.X() = bounds[0];
	}
		
	if (thisPoint.X() > bounds[1])
	{
		thisPoint.X() = bounds[1];
	}

	if (thisPoint.Y() < bounds[2])
	{
		thisPoint.Y() = bounds[2];
	}

	if (thisPoint.Y() > bounds[3])
	{
		thisPoint.Y() = bounds[3];
	}

	this->GetParent()->SetAdjustedPosition(thisPoint);
}

void Repulsor::Render()
{

}

void Repulsor::HandleMessage(Message* message)
{
	message;
}