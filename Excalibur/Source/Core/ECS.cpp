/*********************************************************************
 * @file   ECS.cpp
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

#include "ECS.h"

ComponentAccessInfo::ComponentAccessInfo(Component* const& Pointer, UpdateLayer const& Layer, JiveIndex const& Index)
	: pointer(Pointer)
	, layer(Layer)
	, index(Index)
{

}
