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

#pragma region Pre-Build Component Read Area
class Sprite : public ComponentWithType<cSprite>
{
public:

	Sprite() = default;

	void Serialize(string* Output) const;

	void Load(Stream* openStream);

	void Update(double& dt) { dt; }

	void Render();

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
