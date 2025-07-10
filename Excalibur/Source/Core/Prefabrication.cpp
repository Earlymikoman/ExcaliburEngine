/*********************************************************************
 * @file   Prefabrication.cpp
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

#include "Prefabrication.h"

#include "Object.h"
#include "../../../SharedDependencies/Source/Stream.h"
#include "../../../SharedDependencies/Source/CustomStringFunctions.h"

#include <filesystem>

#define PREFABS_FILEPATH "Data/Prefabs/"

namespace filesystem = std::filesystem;

unordered_map<string, Object*> PrefabLibrary::prefabs = unordered_map<string, Object*>();

PrefabLibrary::PrefabLibrary()
{
	LoadAllPrefabs();
}

PrefabLibrary::~PrefabLibrary()
{
	for (auto& prefab : prefabs)
	{
		delete prefab.second;
	}
}

void PrefabLibrary::LoadPrefab(string const& Name)
{
	prefabs.insert({ Name, new Object() });

	Stream prefabStream = Stream(PREFABS_FILEPATH + Name);

	prefabs[Name]->Load(&prefabStream);

	prefabStream.Close();
}

void PrefabLibrary::LoadAllPrefabs()
{
	const filesystem::path folder = PREFABS_FILEPATH;  // change to your folder

	assert((filesystem::exists(folder) && filesystem::is_directory(folder)) && "Invalid Folder For ReadDirectory().");

	for (auto const& entry : filesystem::recursive_directory_iterator(folder))
	{
		if (!entry.is_regular_file())
			continue;  // skip subdirectories, symlinks, etc.

		if (entry.path().extension() == ".txt")
		{
			string filepath = entry.path().string();
			vector<string> directories;

			SplitString(&directories, filepath, vector<string>{"/", "\\"});

			LoadPrefab(directories[directories.size() - 1]);
		}
	}
}

void PrefabLibrary::GetPrefab(string const& Name, Object* Output)
{
	auto pair = prefabs.find(Name);

	if (pair != prefabs.end())
	{
		LoadPrefab(Name);
		pair = prefabs.find(Name);
	}

	Output->Clone(*pair->second);
}
