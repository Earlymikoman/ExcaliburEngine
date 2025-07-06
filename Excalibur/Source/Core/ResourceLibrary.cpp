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
#include "../../../SharedDependencies/Source/Stream.h"
#include "Texture.h"

#define MESHES_PATH "Data/Meshes/"

template<typename Resource>
vector<Resource*> ResourceLibrary<Resource>::resources = vector<Resource*>();

template<>
static Texture* ResourceLibrary<Texture>::LoadResource(string const& Name)
{
	auto newResource = Engine::LoadTexture(Name);

	Add(newResource);

	return newResource;
}

template<>
static Mesh* ResourceLibrary<Mesh>::LoadResource(string const& Name)
{
	Stream newStream = Stream(MESHES_PATH + Name);

	Mesh* newMesh = new Mesh(Name);

	newMesh->Load(&newStream);

	newStream.Close();

	Add(newMesh);

	return newMesh;
}
