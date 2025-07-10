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

#define TEXTURES_PATH "Assets/Textures/"

using std::string;

struct ID3D11Resource;
struct ID3D11ShaderResourceView;

class Texture
{
public:

	Texture(string const& FileName, ID3D11Resource* const& Resource, ID3D11ShaderResourceView* const& ResourceView, unsigned int const& Rows = 1, unsigned int const& Columns = 1);

	void Deallocate() {}

	ID3D11Resource* const& GetResource() const { return resource; }

	ID3D11ShaderResourceView* const& GetResourceView() const { return resourceView; }

	string const& GetName() const { return fileName; }

	unsigned int const& GetRows() const { return rows; }
	unsigned int const& GetColumns() const { return columns; }

	float GetRowSize() const { return 1.f / rows; };
	float GetColumnSize() const { return 1.f / columns; };

private:

	string const fileName;

	ID3D11Resource* resource;

	ID3D11ShaderResourceView* resourceView;

	unsigned int rows;

	unsigned int columns;

};
