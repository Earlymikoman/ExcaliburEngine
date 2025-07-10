/*********************************************************************
 * @file   ResourceLibrary.h
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

#include "Mesh.h"
#include "Texture.h"

#include <vector>
#include <string>
#include <cassert>

using std::vector;
using std::string;

template<typename Resource>
class ResourceLibrary
{
private:

	ResourceLibrary() = default;

	ResourceLibrary(ResourceLibrary const& rhs) = delete;

	ResourceLibrary& operator=(ResourceLibrary const& rhs) = delete;

	//Generally useless, but can be specialized in ResourceLibrary.cpp to allow for specialized loading of, in particular, meshes, textures, and sounds.
	static Resource* LoadResource(string const& Name);

public:

	~ResourceLibrary()
	{
		for (int i = 0; i < resources.size(); ++i)
		{
			resources[i]->Deallocate();
			delete resources[i];
		}
	}

	static ResourceLibrary* GetInstance()
	{
		static ResourceLibrary instance = ResourceLibrary();

		return &instance;
	}

	static vector<Resource*> const& GetResources() { return resources; }

	static Resource const* Get(string const& Name)
	{
		for (int i = 0; i < resources.size(); ++i)
		{
			if (resources[i]->GetName() == Name)
			{
				return resources[i];
			}
		}

		return LoadResource(Name);
	}

	static void Add(Resource* const& resource)
	{
		//assert(Get(resource->GetName()) && "Attempted to add two resources of the same name in ResourceLibrary<Unknown>. Check ResourceLibrary<Unknown>.Add().");

		resources.push_back(resource);
	}

private:

	static vector<Resource*> resources;

};
