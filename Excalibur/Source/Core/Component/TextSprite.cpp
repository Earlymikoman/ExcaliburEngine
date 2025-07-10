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

Mesh const* TextSprite::textMesh = ResourceLibrary<Mesh>::Get("TextMesh.txt");

TextSprite::TextSprite(Texture const* const& Font, string const& Text)
	: font(Font)
	, text(Text)
{

}

void TextSprite::Render()
{

}

void TextSprite::HandleMessage(Message* message)
{
	message;
}