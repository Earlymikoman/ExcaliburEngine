/*********************************************************************
 * @file   MeshMode.h
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

#include "../../DirectX/DirectXGraphics.h"

#include <string>

using std::string;

enum MeshMode
{
	TRIANGLELIST = D3D_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
};

string GetEnumName(MeshMode const& Enum);
