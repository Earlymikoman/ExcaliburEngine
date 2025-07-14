/*********************************************************************
 * @file   Mesh.cpp
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

#include "Mesh.h"

Mesh::Mesh(string const& Name)
	: name(Name)
	, vertexList(vector<VertexData>())
	, meshType(TRIANGLELIST)
{

}

Mesh::Mesh(string const& Name, vector<VertexData> const& Vertices, MeshMode const& MeshType)
	: name(Name)
	, vertexList(Vertices)
	, meshType(MeshType)
{
}

void Mesh::Allocate()
{
	
}

void Mesh::Deallocate()
{

}
