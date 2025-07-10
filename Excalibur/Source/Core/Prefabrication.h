/*********************************************************************
 * @file   Prefabrication.h
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
#include <unordered_map>

using std::string;
using std::unordered_map;

class Object;

class PrefabLibrary
{
private:

	PrefabLibrary();

	~PrefabLibrary();

	static void LoadPrefab(string const& Name);

	static void LoadAllPrefabs();

public:

	static void GetPrefab(string const& Name, Object* Output);

private:

	static unordered_map<string, Object*> prefabs;

};
