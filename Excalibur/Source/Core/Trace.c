//------------------------------------------------------------------------------
//
// File Name:	Trace.c
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 6
// Course:		CS230S25
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "Trace.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <vadefs.h>

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const char* traceFileName = "Trace.log";
FILE* traceFile = 0;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

// TODO: Declare a private variable for storing a file handle.

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Tracing/Logging module.
// - Open "trace.log" for writing in text mode.
// - Perform error handling in the event that the file failed to open.
void TraceInit()
{
	// TODO: Open "trace.log" for writing (text mode).
	// fopen_s:
	// https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(stdio%2Ffopen_s);k(fopen_s);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true

	fopen_s(&traceFile, traceFileName, "wt");

	// Error handling (implementation details to be determined by the student):
	// https://msdn.microsoft.com/en-us/library/9t0e6085.aspx
	// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strerror-s-strerror-s-wcserror-s-wcserror-s?f1url=https%3A%2F%2Fmsdn.microsoft.com%2Fquery%2Fdev16.query%3FappId%3DDev16IDEF1%26l%3DEN-US%26k%3Dk(STRING%2Fstrerror_s);k(strerror_s);k(DevLang-C%2B%2B);k(TargetOS-Windows)%26rd%3Dtrue&view=vs-2019
	//traceFile = NULL;

	if (!traceFile)
	{	
		printf("XXX\nTrace File Could Not Be Opened!\nXXX\n");
	}
}

// Output a message to the Tracing/Logging file.
// - Print the given message to the file if it was opened successfully.
// - Every message must be printed on its own line.
// - There must be no blank lines between messages.
void TraceMessage(const char * formatString/**/, .../**/)
{
	formatString;

	// TODO: Write the message to the Tracing/Logging file using the variadic
	//   functions discussed during the Week 1 lectures.

	va_list arg_ptr;

	// Verify that the traceStream is valid.
	if (traceFile != NULL)
	{
		/**/va_start(arg_ptr, formatString);
		vfprintf_s(traceFile, formatString, arg_ptr);
		fprintf_s(traceFile, "\n");
		va_end(arg_ptr);/**/
		//fprintf(traceFile, formatString);
	}
}

// Shutdown the Tracing/Logging module.
// - Close the file if-and-only-if the file was opened successfully
void TraceShutdown()
{
	// TODO: Close "trace.log" if it has been opened successfully.

	if (traceFile)
	{
		fclose(traceFile);
	}
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

