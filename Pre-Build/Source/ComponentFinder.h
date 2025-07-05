/*********************************************************************
 * @file   ComponentFinder.h
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

#include <vector>
#include <string>

using std::vector;
using std::string;

void ReadDirectory(string* Output, string const& folderPath); //Largely provided by ChatGPT

void FindComponentNames(vector<string>* Output, string const& Data);
