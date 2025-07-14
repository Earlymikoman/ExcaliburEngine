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
#include "../../../SharedDependencies/Source/CustomStringFunctions.h"
#include "Texture.h"

#define MESHES_PATH "Data/Meshes/"

template<typename Resource>
vector<Resource*> ResourceLibrary<Resource>::resources = vector<Resource*>();

template<>
static Texture* ResourceLibrary<Texture>::LoadResource(string const& Name)
{
	unsigned int rows = 1;
	unsigned int columns = 1;

	vector<string> buffer;

	SplitString(&buffer, Name, vector<string>{"{", "}"});

	if (buffer.size() >= 3)//Ew. Just ew.
	{
		vector<string> buffer2;

		SplitString(&buffer2, buffer[buffer.size() - 2/*Lord have mercy on my soul, that I'm using a size() - 2, and that that is somehow actually what I want to do.*/], vector<string>{"x", "X", "|"});

		assert(buffer2.size() == 2 && "{ and } in texture file names are EXCLUSIVELY reserved for row/column counts in the form {RxC}.");

		rows = std::stoi(buffer2[0]);
		columns = std::stoi(buffer2[1]);
	}

	auto newResource = Engine::LoadTexture(Name, rows, columns);

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

template<>
static Sound* ResourceLibrary<Sound>::LoadResource(string const& Name)
{
	Sound* newSound = Engine::LoadSound(Name);

	Add(newSound);

	return newSound;
}
