/*********************************************************************
 * @file   Stream.cpp
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

#include "Stream.h"

#include <cassert>
#include <filesystem>

Stream::Stream(string const& Filename)
	: filename(Filename)
	, stream(fstream(Filename, std::ios::in | std::ios::out | std::ios::app))
#ifdef _DEBUG
	, open(1)
#endif
{
	assert(stream.is_open() && "Failed To Open Stream");
}

void Stream::Open(string const& Filename, std::ios_base::openmode OpenMode)
{
	assert(!open && "Invalid Stream Open Attempt.");

	stream.open(Filename, OpenMode);

#ifdef _DEBUG
	open = 1;
#endif
}

void Stream::Close()
{
	assert(open && "Invalid Stream Close Attempt.");

	stream.close();

#ifdef _DEBUG
	open = 0;
#endif
}

void Stream::Write(string const& Data)
{
	assert(open && "Invalid Stream Access Attempt.");

	stream << Data;
}

void Stream::Read(string* const& Output)
{
	assert(open && "Invalid Stream Access Attempt.");

	Output->append
	(
		string
		(
			std::istreambuf_iterator<char>
			(
				stream
			)
			, std::istreambuf_iterator<char>()
		)
	);
}

void Stream::ReadLine(string* const& Output)
{
	assert(open && "Invalid Stream Access Attempt.");

	std::getline(stream, *Output);
}

void Stream::ReadToken(string* const& Output)
{
	assert(open && "Invalid Stream Access Attempt.");

	stream >> *Output;
}

void Stream::Reset()
{
	assert(open && "Invalid Stream Access Attempt.");

	// flush any buffered output
	stream.flush();

	// clear state and reposition
	stream.clear();      // clear EOF or fail bits
	stream.seekp(0);     // position write pointer at start
	stream.seekg(0);     // position read pointer at start
}

void Stream::Clear()
{
	assert(open && "Invalid Stream Access Attempt.");

	Reset();

	// truncate on disk
	std::filesystem::resize_file(filename, 0);
}

void Stream::ShiftSpot(int Steps)
{
	stream.seekp(Steps, std::ios::cur);
	stream.seekg(stream.tellp());
}
