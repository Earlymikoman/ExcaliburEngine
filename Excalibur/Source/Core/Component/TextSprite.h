/*********************************************************************
 * @file   TextSprite.h
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

#include "Sprite.h"

#include <string>

using std::string;

class Mesh;
class Texture;

#pragma region Pre-Build Component Read Area
class TextSprite : public ComponentWithType<cTextSprite>
{
public:

	TextSprite() = default;

	TextSprite(Texture const* const& Font, string const& Text, float Alpha = 1);

	void Serialize(string* Output) const;

	void Load(Stream* openStream);

	void Update(double& dt) { dt; }

	void Render();

	void HandleMessage(Message* message);

private:

	static Mesh const* textMesh;

	float alpha;

	Texture const* font;

	string text;

};
#pragma endregion Pre-Build Component Read Area
