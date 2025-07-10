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
	Transform* transform = parent->GetTransform();

	Engine::SetPosition(transform->GetPosition());
	Engine::SetScale(transform->GetScale());
	Engine::SetRotation(transform->GetRotation());

	Engine::SetTexture(texture);

	unsigned int numRows = texture->GetRows();
	unsigned int numCols = texture->GetColumns();
	float rowSize = texture->GetRowSize();
	float colSize = texture->GetColumnSize();

	Engine::SetTextureOffset(Vector<2>(rowSize * (frameIndex % numRows), colSize * (frameIndex / numCols)));

	Engine::Draw(mesh, DrawMode::TEXTURE);
}

void Sprite::HandleMessage(Message* message)
{
	message;
}
