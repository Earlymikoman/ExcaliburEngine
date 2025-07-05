/*********************************************************************
 * @file   ComponentLoadWriter.cpp
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

//WARNING: THIS FILE EDITS OTHER FILES AT COMPILE TIME. DO NOT EDIT WITHOUT EXPRESS KNOWLEDGE OF THIS FACT.

#include "ComponentLoadWriter.h"

#include "../../SharedDependencies/Source/Stream.h"
#include "../../SharedDependencies/Source/CustomStringFunctions.h"

#include <iostream>
#include <filesystem>
//#include <vector>
#include <cassert>

#define ENTRY_DELIMITER "#pragma region Pre-Build Editing Area"
#define EXIT_DELIMITER "#pragma endregion Pre-Build Editing Area"

//#define FILE_TO_READ "../../Excalibur/Source/Core/EngineMain.cpp"
#define FILE_TO_WRITE "../Excalibur/Source/Core/LoadFunctions.cpp"
#define COMPONENT_MAP_SKELETON_START "static unordered_map LoadingFunctionMap = unordered_map<string, void(*)(Object*, Stream*, const UpdateLayer&)>\n{"
#define COMPONENT_MAP_SKELETON_END "\n};"

namespace filesystem = std::filesystem;

using std::cout;
using std::endl;
//using std::vector;

class System;

void WriteComponentLoadMap(vector<string> const& ComponentNames)
{
	Stream writeStream = Stream(FILE_TO_WRITE);


	string bufferString = string();
	writeStream.Read(&bufferString);
	vector<string> splicedStrings;

	SplitString(&splicedStrings, bufferString, vector<string>{ENTRY_DELIMITER, EXIT_DELIMITER});

	assert(splicedStrings.size() /*>*/== 3/* && splicedStrings.size() % 2 == 1*/ && "You Messed Up The WriteComponentLoadMap() Markers. Aborting To Prevent Permanent Damage.");

	splicedStrings[1].clear();

	splicedStrings[1].append(string(ENTRY_DELIMITER) + "\n\n" + COMPONENT_MAP_SKELETON_START);
	assert(ComponentNames.size() > 0 && "Bro, How Are There Zero Components To Read? Something Ain't Right Here Pre-Build::WriteComponentLoadMap()).");
	splicedStrings[1].append("\n\t{ \"" + (ComponentNames)[0] + "\", &Load<" + (ComponentNames)[0] + "> }");
	for (int i = 1; i < ComponentNames.size(); ++i)
	{
		splicedStrings[1].append("\n\t, { \"" + (ComponentNames)[i] + "\", &Load<" + (ComponentNames)[i] + "> }");
	}
	splicedStrings[1].append(string(COMPONENT_MAP_SKELETON_END) + "\n\n" + EXIT_DELIMITER);

	bufferString.clear();
	for (int i = 0; i < splicedStrings.size(); ++i)
	{
		bufferString.append(splicedStrings[i]);
	}

	writeStream.Clear();
	writeStream.Write(bufferString);


	writeStream.Close();
}
