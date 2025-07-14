/*********************************************************************
 * @file   Stream.h
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

#include "StringConvert.h"

#include <fstream>
#include <string>

using std::fstream;
using std::string;

class Stream
{
public:

	Stream() = default;

	Stream(string const& Filename);

	void Open(string const& Filename, std::ios_base::openmode OpenMode = std::ios::in | std::ios::out | std::ios::app);

	void Close();

	void Write(string const& Data);

	void GetChar(char* const& Output);

	void Read(string* const& Output);

	void ReadLine(string* const& Output);

	void ReadToken(string* const& Output);

	void ReadFormatString(string* const& Output);

	void Reset();

	void Clear();

	void ShiftSpot(int Steps);

	template<typename T>
	char ReadType(T* Output)
	{
		string tempstring;

		ReadToken(&tempstring);

		if (tempstring == "")
		{
			return 0;
		}

		StringConvert(Output, tempstring);

		return 1;
	}

	static void FormatString(string* Output, string const& Data);

	string GetName() const { return filename; }

#ifdef _DEBUG
	auto const& IsOpen() const { return open; }
#endif

private:

	fstream stream;

	string filename;

#ifdef _DEBUG
	char open;
#endif

};
