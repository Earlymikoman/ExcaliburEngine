/*********************************************************************
 * @file   Sprite.h
 * @brief  .
 * 
 * Project: Excalibur
 * 
 * @author Xander Boosinger (xboosinger@gmail.com), Aidan Hartman (aidan.hartman@digipen.edu), Elliot Orr (elliot.orr@digipen.edu), Ori Balashov (ori.balashov@digipen.edu)
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

class Mesh;
class Texture;
class Stream;
class Message;

#pragma region Pre-Build Component Read Area
class Sprite : public ComponentWithType<cSprite>
{
public:

	Sprite() = default;

	Sprite(unsigned int const& FrameIndex, float const& Alpha, Texture const* const& Texture, Mesh const* const& Mesh);

	void Clone(Sprite const& rhs) { Object* Parent = parent; *this = rhs; parent = Parent; }

	void Serialize(string* Output) const;

	void Load(Stream* openStream);

	void Update(double& dt) { dt; }

	void Render();

	void HandleMessage(Message* message);

#pragma region Setters

	void SetFrameIndex(unsigned int const& Index) { frameIndex = Index; }

	void SetMesh(Mesh const* const& Mesh) { mesh = Mesh; }

	void SetTexture(Texture const* const& Texture) { texture = Texture; }

#pragma endregion

#pragma region Getters

	Mesh const* const& GetMesh() { return mesh; }

#pragma endregion

private:

	// The frame currently being displayed (for sprite sheets).
	unsigned int frameIndex;

	// The alpha transparency to use when drawing the sprite.
	float alpha;

	// The sprite source used when drawing (NULL = simple colored mesh).
	const Texture* texture;

	// The mesh used to draw the sprite.
	const Mesh* mesh;

};
#pragma endregion Pre-Build Component Read Area
