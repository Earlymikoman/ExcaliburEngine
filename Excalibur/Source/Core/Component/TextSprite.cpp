/*********************************************************************
 * @file   TextSprite.cpp
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

#include "TextSprite.h"

#include "../ResourceLibrary.h"
#include "../Object.h"
#include "../Engine.h"
#include "Transform.h"
#include "../../../../SharedDependencies/Source/Vector.h"
#include "../Texture.h"

Mesh const* TextSprite::textMesh = ResourceLibrary<Mesh>::Get("TextMesh.txt");

TextSprite::TextSprite(Texture const* const& Font, string const& Text, float Alpha)
	: alpha(Alpha)
	, font(Font)
	, text(Text)
{

}

void TextSprite::Render()
{
	Transform* transform = parent->GetTransform();

	Vector<3> position = transform->GetPosition();
	Vector<3> scale = transform->GetScale();

	Engine::SetTexture(font);

	Engine::SetScale(scale);
	Engine::SetRotation(transform->GetRotation());

	//unsigned int numRows = font->GetRows();
	unsigned int numCols = font->GetColumns();
	float uSize = font->GetUSize();
	float vSize = font->GetVSize();

	unsigned int frameIndex = 0;

	for (int i = 0; i < text.length(); ++i)
	{
		frameIndex = text[i] - ' ';

		Engine::SetPosition(position);
		VectorAddition(position, Vector<3>(scale.X(), 0, 0));

		Engine::SetTextureOffset(Vector<2>(uSize * (frameIndex % numCols), vSize * (frameIndex / numCols)));

		Engine::Draw(textMesh, DrawMode::TEXTURE);
	}
}

void TextSprite::HandleMessage(Message* message)
{
	message;
}