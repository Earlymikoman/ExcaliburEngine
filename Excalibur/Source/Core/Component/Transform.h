/*********************************************************************
 * @file   Transform.h
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

#pragma region Pre-Build Component Read Area
class Transform : public ComponentWithType<cTransform>
{
public:

	void Serialize(string* Output) const;

	//void Save(string const& filepath) const;

	void Load(Stream* openStream);

	void Update(double& dt) { dt; }

	void Render() {}

	void HandleMessage(Message* message);

	Vector<3> const& GetPosition() const { return position; }

	Vector<3> const& GetRotation() const { return rotation; }

	Vector<3> const& GetScale() const { return scale; }

	void SetPosition(Vector<3> const& Position) { position = Position; }

	void SetRotation(Vector<3> const& Rotation) { rotation = Rotation; }

	void SetScale(Vector<3> const& Scale) { scale = Scale; }

private:

	Vector<3> position;

	Vector<3> rotation;

	Vector<3> scale;

};
#pragma endregion Pre-Build Component Read Area
