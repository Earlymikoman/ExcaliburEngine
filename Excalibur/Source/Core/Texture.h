/*********************************************************************
 * @file   Texture.h
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

#include <string>

using std::string;

struct ID3D11Resource;
struct ID3D11ShaderResourceView;

class Texture
{
public:

	Texture(string const& FileName, ID3D11Resource* const& Resource, ID3D11ShaderResourceView* const& ResourceView);

	ID3D11Resource* const& GetResource() const { return resource; }

	ID3D11ShaderResourceView* const& GetResourceView() const { return resourceView; }

private:

	string const fileName;

	ID3D11Resource* resource;

	ID3D11ShaderResourceView* resourceView;

};
