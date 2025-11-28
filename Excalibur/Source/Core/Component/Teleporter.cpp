/*********************************************************************
 * @file   Teleporter.cpp
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

#include "Teleporter.h"

#include "../Object.h"
#include "Transform.h"
#include "Physics.h"
#include "../../../../SharedDependencies/Source/Random.h"
#include "../../../../SharedDependencies/Source/Matrix.h"

Teleporter::Teleporter(Vector<4> const& Bounds, array<Vector<4>, 4> const& ReappearanceBounds)
	: bounds(Bounds)
	, reappearanceBounds(ReappearanceBounds)
{
}

void Teleporter::Update(double& dt)
{
	dt;

	Transform adjustedTransform = this->GetParent()->GetAdjustedTransform();

	if (adjustedTransform.GetPosition().X() < bounds[0])
	{
		Teleport(2);
	}

	if (adjustedTransform.GetPosition().X() > bounds[1])
	{
		Teleport(0);
	}

	if (adjustedTransform.GetPosition().Y() < bounds[2])
	{
		Teleport(3);
	}

	if (adjustedTransform.GetPosition().Y() > bounds[3])
	{
		Teleport(1);
	}
}

void Teleporter::Render()
{
}

void Teleporter::HandleMessage(Message* message)
{
	message;
}

void Teleporter::Teleport(char const& bound)
{
	Physics* parentPhysics = this->GetParent()->GetComponent<Physics>();

	int direction = RandomRange(0, (int)reappearanceBounds.size());

	Matrix<4, 4> rotationMatrix;
	rotationMatrix.RotDeg(90.f * (direction - bound));

	Vector<4> curVelocity = Vector<4>({ parentPhysics->GetVelocity().X(), parentPhysics->GetVelocity().Y(), parentPhysics->GetVelocity().Z(), 0.f});

	Vector<4> newVelocity = rotationMatrix.VectorProduct(curVelocity);
	parentPhysics->SetVelocity(Vector<3>(newVelocity[0], newVelocity[1], newVelocity[2]));

	

	float portion = RandomRangeFloat(0, 1);

	Vector<2> nearPoint = Vector<2>(reappearanceBounds[direction][0], reappearanceBounds[direction][1]);
	Vector<2> farPoint = Vector<2>(reappearanceBounds[direction][2], reappearanceBounds[direction][3]);

	Vector<2> difference = farPoint;
	VectorSubtraction(difference, nearPoint);

	VectorScale(difference, portion);

	Vector<2> final = nearPoint;

	VectorAddition(final, difference);

	this->GetParent()->SetAdjustedPosition(Vector<3>(final[0], final[1]));
}
