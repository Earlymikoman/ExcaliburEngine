/*********************************************************************
 * @file   SaveFunctions.h
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

class Stream;
struct VertexData;

using std::string;

//Dubious usefulness. Will never delete. LMAO. Check the cpp btw, has a buncha actually useful stuff that anyone would tell you should "absolutely be elsewhere".
void Save(string const& data, ::Stream* openStream);

void SerializeVertexData(string* Output, VertexData const& Object);
