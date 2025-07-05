/*********************************************************************
 * @file   ComponentFinder.cpp
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

#include "ComponentFinder.h"

#include "../../SharedDependencies/Source/Stream.h"
#include "../../SharedDependencies/Source/CustomStringFunctions.h"

#include <filesystem>
#include <cassert>
#include <stdlib.h>

#define ENTRY_DELIMITER "#pragma region Pre-Build Component Read Area"
#define EXIT_DELIMITER "#pragma endregion Pre-Build Component Read Area"

namespace filesystem = std::filesystem;

using std::ifstream;

void ReadDirectory(string* Output, string const& folderPath) //Largely provided by ChatGPT
{
	const filesystem::path folder = folderPath;  // change to your folder

	assert((filesystem::exists(folder) && filesystem::is_directory(folder)) && "Invalid Folder For ReadDirectory().");

	for (auto const& entry : filesystem::recursive_directory_iterator(folder))
	{
		if (!entry.is_regular_file())
			continue;  // skip subdirectories, symlinks, etc.

		if (entry.path().extension() == ".h")
		{
			//std::cout << "Found text file: " << entry.path().filename() << "\n";

			// e.g. open and read it:
			Stream fileStream(entry.path().string());

			fileStream.Read(Output);

			fileStream.Close();
		}
	}
}

void FindComponentNames(vector<string>* Output, string const& Data) //With thanks to ChatGPT
{
	vector<string> componentSections;

	SplitString(&componentSections, Data, vector<string>{ENTRY_DELIMITER, EXIT_DELIMITER});

	for (int i = (int)componentSections.size() - (1 + ((int)componentSections.size() + 1) % 2); i >= 0; i -= 2)
	{
		componentSections.erase(componentSections.begin() + i);
	}

	for (int i = 0; i < componentSections.size(); ++i)
	{
		Output->push_back(string());
	    FindStringByDelimiters(&(*Output)[Output->size() - 1], componentSections[i], { "class ", " :" });
	}
}
