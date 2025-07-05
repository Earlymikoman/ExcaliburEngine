/*********************************************************************
 * @file   Mesh.h
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

//#pragma warning(disable: 5046)//Was providing a warning which did not appear to actually be a thing. Something about internal linkage.

#include "../DirectX/DirectXGraphics.h"
#include "Enums/MeshMode.h"

#include <string>

class Stream;

using std::string;

class Mesh
{
public:

	Mesh(string const& Name, vector<VertexData> const& Vertices, MeshMode const& MeshType = TRIANGLELIST);

	string const& GetName() const { return name; }

	vector<VertexData> const& GetVertices() const { return vertexList; }

	MeshMode const& GetMeshType() const { return meshType; }

	void Serialize(string* Output) const;

	void Load(Stream* openStream);

private:

	string name;

	MeshMode meshType;

	//// The number of vertices in our single mesh
	//const int vertexCount;
	// The vertex data for our single mesh
	vector<VertexData> vertexList;

};
