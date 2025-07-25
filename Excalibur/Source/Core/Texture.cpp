/*********************************************************************
 * @file   Texture.cpp
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

#include "Texture.h"

Texture::Texture(string const& FileName, ID3D11Resource* const& Resource, ID3D11ShaderResourceView* const& ResourceView, unsigned int const& Rows, unsigned int const& Columns)
	: fileName(FileName)
	, resource(Resource)
	, resourceView(ResourceView)
	, rows(Rows)
	, columns(Columns)
{
}
