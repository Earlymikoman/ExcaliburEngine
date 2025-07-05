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

#include "../SharedDependencies/Source/Stream.h"

#include <iostream>

#define FILE_TO_READ "../Excalibur/Source/Core/EngineMain.cpp"
#define FILE_TO_WRITE "../Excalibur/Source/Core/LoadFunctions.h"

using std::cout;
using std::endl;

#pragma message("Serializable")
class System;

int main()
{
	Stream reflectionStreamTest = Stream(string(FILE_TO_READ));
	Stream writeTest = Stream(FILE_TO_WRITE);

	string tempString = string();

	reflectionStreamTest.Read(&tempString);

	writeTest.Close();
	reflectionStreamTest.Close();
}
