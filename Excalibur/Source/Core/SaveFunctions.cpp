/*********************************************************************
 * @file   SaveFunctions.cpp
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

#include "SaveFunctions.h"

#include "../../../SharedDependencies/Source/Stream.h"
#include "FunctionLibrary.h"
#include "Object.h"
#include "Component/Component.h"
#include "Component/Transform.h"
#include "Component/Physics.h"
#include "Component/Sprite.h"
#include "Component/Button.h"
//#include "../../../SharedDependencies/Source/StringConvert.h"
#include "ECS.h"
#include "../../../SharedDependencies/Source/CustomStringFunctions.h"
#include "Mesh.h"
#include "Texture.h"

void SerializeVertexData(string* Output, VertexData const& Object)
{
	string& tempString = *Output;

	tempString.append("Vertex:\n");
	
	IncrementTab();

	tempString.append(Tab() + "Position: [");
	for (int i = 0; i < _countof(Object.Position); ++i)
	{
		tempString.append(std::to_string(Object.Position[i]) + "|");
	}
	tempString.pop_back();
	tempString.append("]\n");

	tempString.append(Tab() + "Color: [");
	for (int i = 0; i < _countof(Object.Color); ++i)
	{
		tempString.append(std::to_string(Object.Color[i]) + "|");
	}
	tempString.pop_back();
	tempString.append("]\n");

	tempString.append(Tab() + "UVCoord: [");
	for (int i = 0; i < _countof(Object.TexCoord); ++i)
	{
		tempString.append(std::to_string(Object.TexCoord[i]) + "|");
	}
	tempString.pop_back();
	tempString.append("]\n");

	IncrementTab(-1);
}

void ::Mesh::Serialize(string* Output) const
{
	string& tempString = *Output;

	tempString.append("Mesh:\n");
	IncrementTab();

	tempString.append(Tab() + "Name: " + name + "\n");

	tempString.append(Tab() + "Mesh Type: " + GetEnumName(meshType) + "\n");

	tempString.append(Tab() + "Vertexes: " + std::to_string(vertexList.size()) + ":\n");

	IncrementTab();

	for (int i = 0; i < vertexList.size(); ++i)
	{
		tempString.append(Tab());
		SerializeVertexData(&tempString, vertexList[i]);
	}

	IncrementTab(-1);

	IncrementTab(-1);
}

void Object::Serialize(string* Output) const
{
	string& tempString = *Output;

	tempString.append("Object: \n");
	IncrementTab(1);

	tempString.append(Tab());
	transform->Serialize(&tempString);
	
	tempString.append(Tab() + "Components: " + std::to_string(components.size()) + ":\n");
	IncrementTab(1);
	for (auto const& component : components)
	{
		tempString.append(Tab());

		((VirtualECS*)component.first)->Serialize(*component.second.GetPointer(), &tempString);
	}
	IncrementTab(-1);

	tempString.append(Tab() + "Children: " + std::to_string(children.size()) + ":\n");
	IncrementTab();
	for (int i = 0; i < children.size(); ++i)
	{
		tempString.append(Tab());

		children[i]->Serialize(&tempString);
	}
	IncrementTab(-1);
}
void Transform::Serialize(string* Output) const
{
	string tempString = string(/*"\n"*/);

	tempString.append("Transform:\n");
	IncrementTab();

	tempString.append(Tab() + "Position: ");
	position.Serialize(&tempString);
	tempString.append("\n");

	tempString.append(Tab() + "Rotation: ");
	rotation.Serialize(&tempString);
	tempString.append("\n");

	tempString.append(Tab() + "Scale: ");
	scale.Serialize(&tempString);
	tempString.append("\n");

	IncrementTab(-1);


	Output->append(tempString);
}

void Physics::Serialize(string* Output) const
{
	Output;
	string tempString = string("\n");
}

void Sprite::Serialize(string* Output) const
{
	string& tempString = *Output;

	tempString.append("Sprite:\n");
	IncrementTab();

	tempString.append(Tab() + "Frame Index: " + std::to_string(frameIndex) + "\n");
	
	tempString.append(Tab() + "Alpha: " + std::to_string(alpha) + "\n");

	tempString.append(Tab() + "Texture: " + texture->GetName() + "\n");

	tempString.append(Tab() + "Mesh: " + mesh->GetName() + "\n");

	IncrementTab(-1);
}

void Button::Serialize(string* Output) const
{
	string& tempString = *Output;

	tempString.append("Button:\n");
	IncrementTab();

	tempString.append(Tab() + "Function: " + function.GetName() + "\n");

	IncrementTab(-1);
}

void Save(string const& data, Stream* openStream)
{
	openStream->Write(data);
}
