/*********************************************************************
 * @file   Teleporter.h
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

#include <array>

using std::array;

class Stream;
class Message;

class Teleporter : public ComponentWithType<cTeleporter>
{
public:

	Teleporter() = default;

	Teleporter(Vector<4> const& Bounds, array<Vector<4>, 4> const& ReappearanceBounds);

	void Clone(Teleporter const& rhs) { Object* Parent = parent; *this = rhs; parent = Parent; }

	void Serialize(string* Output) const;

	void Load(Stream* openStream);

	void Update(double& dt);

	void Render();

	void HandleMessage(Message* message);

	void Teleport(char const& bound);

private:

	Vector<4> bounds;

	array<Vector<4>, 4> reappearanceBounds;

};
