/*********************************************************************
 * @file   ResourceLibrary.cpp
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

#include "ResourceLibrary.h"

#include "Engine.h"

#define MESHES_PATH "Data/Meshes/"
#define TEXTURES_PATH "Assets/Textures/"

template<>
static Texture* ResourceLibrary<Texture>::LoadResource(string const& Name)
{
	return Engine::LoadTexture(MESHES_PATH + Name);
}

template<>
static Mesh* ResourceLibrary<Mesh>::LoadResource(string const& Name)
{
	Name;
	//return Engine::LoadTexture(MESHES_PATH + Name);
	return nullptr;
}
