/*********************************************************************
 * @file   main.cpp
 * @brief  .
 *
 * Project: Pre-Build
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

#ifdef _DEBUG

#include "Source/EnumNameWriter.h"
#include "Source/ComponentLoadWriter.h"
#include "Source/ComponentFinder.h"
//#include "../SharedDependencies/Source/CustomStringFunctions.h"

#include <string>
#include <vector>

#define COMPONENT_DATA_FOLDER R"(../Excalibur/Source/Core/Component)"

using std::string;
using std::vector;

#endif

int main()
{
#ifdef _DEBUG
	string megaData;
	vector<string> componentNames;

	ReadDirectory(&megaData, COMPONENT_DATA_FOLDER);
	FindComponentNames(&componentNames, megaData);

	WriteEnumMap();
	WriteComponentLoadMap(componentNames);
#endif
}
