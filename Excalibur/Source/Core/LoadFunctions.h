/*********************************************************************
 * @file   LoadFunctions.h
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

class Stream;
class Object;
struct VertexData;

void LoadComponent(Object* Output, Stream* openStream);

void LoadVertexData(Stream* openStream, VertexData* Object);
