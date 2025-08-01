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

	Transform& operator+=(Transform const& rhs);

	void AddPosition(Vector<3> const& posVector);
	void AddRotation(float const& posVector);
	void AddScale(Vector<3> const& posVector);
	void MultiplyScale(Vector<3> const& posVector);

	void Serialize(string* Output) const;

	//void Save(string const& filepath) const;

	void Load(Stream* openStream);

	void Update(double& dt) { dt; }

	void Render() {}

	void HandleMessage(Message* message);

	char PointOver(Vector<3> const& point);

	Vector<3> const& GetPosition() const { return position; }

	auto const& GetRotation() const { return rotation; }

	Vector<3> const& GetScale() const { return scale; }

	void SetPosition(Vector<3> const& Position) { position = Position; }

	void SetRotation(float const& Rotation) { rotation = Rotation; }

	void SetScale(Vector<3> const& Scale) { scale = Scale; }

private:

	Vector<3> position;

	float rotation;

	Vector<3> scale;

};
#pragma endregion Pre-Build Component Read Area
