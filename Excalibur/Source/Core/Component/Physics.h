/*********************************************************************
 * @file   Physics.h
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

#pragma once

#include "Component.h"

#include "../../../../SharedDependencies/Source/Vector.h"

class Stream;

#pragma region Pre-Build Component Read Area
class Physics : public ComponentWithType<cPhysics>
{
public:

	Physics
	(
		Vector<3> const& OldTranslation = Vector<3>()
		, Vector<3> const& Acceleration = Vector<3>()
		, Vector<3> const& Velocity = Vector<3>()
		, float const& RotationalVelocity = 0
		, float const& Drag = 0
	);

	void Serialize(string* Output) const;

	void Load(Stream* openStream);

	void Update(double& dt);

	void Render();

#pragma region Getters

	Vector<3> const& GetOldTranslation() const { return oldTranslation; }

	Vector<3> const& GetAcceleration() const { return acceleration; }

	Vector<3> const& GetVelocity() const { return velocity; }

	float const& GetRotationalVelocity() const { return rotationalVelocity; }

	float const& GetDrag() const { return drag; }

#pragma endregion

#pragma region Setters

	void SetOldTranslation(Vector<3> const& OldTranslation) { oldTranslation = OldTranslation; }

	void SetAcceleration(Vector<3> const& Acceleration) { acceleration = Acceleration; }

	void SetVelocity(Vector<3> const& Velocity) { velocity = Velocity; }

	void SetRotationalVelocity(float const& RotationalVelocity) { rotationalVelocity = RotationalVelocity; }

	void SetDrag(float const& Drag) { drag = Drag; }

#pragma endregion

private:

	Vector<3> oldTranslation;

	Vector<3> acceleration;

	Vector<3> velocity;

	float rotationalVelocity;

	float drag;

};
#pragma endregion Pre-Build Component Read Area
