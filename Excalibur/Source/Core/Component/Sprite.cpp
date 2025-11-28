/*********************************************************************
 * @file   Sprite.cpp
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

#include "Sprite.h"

#include "../Object.h"
#include "../Engine.h"
#include "Transform.h"
#include "../../../../SharedDependencies/Source/Vector.h"
#include "../Texture.h"

Sprite::Sprite(unsigned int const& FrameIndex, float const& Alpha, Texture const* const& Texture, Mesh const* const& Mesh)
	: frameIndex(FrameIndex)
	, alpha(Alpha)
	, texture(Texture)
	, mesh(Mesh)
{
}

void Sprite::Render()
{
	//cout << endl << endl << "rendered" << this << endl;

	Transform transform = parent->GetAdjustedTransform();

	cout << transform.GetPosition().X() << " " << transform.GetPosition().Y() << endl << endl/* << endl*/;

	Engine::SetPosition(transform.GetPosition());
	Engine::SetScale(transform.GetScale());
	Engine::SetRotation(transform.GetRotation());

	Engine::SetTexture(texture);

	unsigned int numCols = texture->GetColumns();
	float uSize = texture->GetUSize();
	float vSize = texture->GetVSize();

	Engine::SetTextureOffset(Vector<2>(uSize * (frameIndex % numCols), vSize * (frameIndex / numCols)));

	Engine::Draw(mesh, DrawMode::TEXTURE);
}

void Sprite::HandleMessage(Message* message)
{
	message;
}
