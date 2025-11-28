/*********************************************************************
 * @file   Repulsor.h
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
class Message;
class Transform;

#pragma region Pre-Build Component Read Area
class Repulsor : public ComponentWithType<cRepulsor>
{
public:

	Repulsor() = default;

	Repulsor(Vector<4> const& Bounds, Object* const& RepulsionObject, float const& RepulsionStrength);

	void Clone(Repulsor const& rhs) { Object* Parent = parent; *this = rhs; parent = Parent; }

	void Serialize(string* Output) const;

	void Load(Stream* openStream);

	void Update(double& dt);

	void Render();

	void HandleMessage(Message* message);

#pragma region Getters

	

#pragma endregion

#pragma region Setters

	

#pragma endregion

private:

	Vector<4> bounds;

	Object* repulsionObject;

	float repulsionStrength;

};
#pragma endregion Pre-Build Component Read Area

