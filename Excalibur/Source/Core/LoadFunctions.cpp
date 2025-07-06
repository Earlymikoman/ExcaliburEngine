/*********************************************************************
 * @file   LoadFunctions.cpp
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

//WARNING: THIS FILE IS EDITED AT BUILD TIME. DO NOT EDIT WITHOUT EXPRESS KNOWLEDGE OF THIS FACT.

#include "LoadFunctions.h"

#include "../../../SharedDependencies/Source/Stream.h"
#include "Object.h"
#include "Component/Component.h"
#include "Component/Transform.h"
#include "Component/Physics.h"
#include "Component/Sprite.h"
#include "Component/Button.h"
#include "ECS.h"
#include "Enums/EnumMappings.h"
#include "Engine.h"
#include "Mesh.h"
#include "../DirectX/DirectXGraphics.h"
#include "../../../SharedDependencies/Source/CustomStringFunctions.h"
#include "ResourceLibrary.h"

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

template<typename ComponentType>
void Load(Object* Output, Stream* openStream, UpdateLayer const& layer)
{
	auto component = Output->AddComponent(ComponentType(), layer);
	component->Load(openStream);
	//((ComponentType*)(ECS<ComponentType>::GetInstance()->AddComponent(ComponentType(), layer).GetPointer()))->Load(openStream);
}

void LoadVertexData(Stream* openStream, VertexData* Object)
{
	string buffer;
	vector<string> splitBuffer;
	string garbage;

	openStream->ReadToken(&garbage);

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	SplitString(&splitBuffer, buffer, vector<string>{"[", "|", "]"});
	for (int i = 0; i < _countof(Object->Position); ++i)
	{
		Object->Position[i] = std::stof(splitBuffer[i]);
	}
	splitBuffer.clear();
	
	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	SplitString(&splitBuffer, buffer, vector<string>{"[", "|", "]"});
	for (int i = 0; i < _countof(Object->Color); ++i)
	{
		Object->Color[i] = std::stof(splitBuffer[i]);
	}
	splitBuffer.clear();

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	SplitString(&splitBuffer, buffer, vector<string>{"[", "|", "]"});
	for (int i = 0; i < _countof(Object->TexCoord); ++i)
	{
		Object->TexCoord[i] = std::stof(splitBuffer[i]);
	}
	splitBuffer.clear();
}

void Mesh::Load(Stream* openStream)
{
	string buffer;
	string garbage;

	openStream->ReadToken(&garbage);

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	name = buffer;

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	meshType = (MeshMode)GetEnumValue(buffer);

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	buffer.pop_back();
	vertexList = vector<VertexData>(std::stoi(buffer));
	for (int i = 0; i < std::stoi(buffer); ++i)
	{
		LoadVertexData(openStream, &vertexList[i]);
	}
}

void Object::Load(Stream* openStream)
{
	string buffer;
	string garbage;

	int iterationCount;
	iterationCount;

	//openStream->ReadToken(&garbage);
	openStream->ReadToken(&garbage);

	transform->Load(openStream);

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	buffer.pop_back();
	iterationCount = std::stoi(buffer);

	for (int i = 0; i < iterationCount; ++i)
	{
		LoadComponent(this, openStream);
	}

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	buffer.pop_back();
	iterationCount = std::stoi(buffer);

	for (int i = 0; i < iterationCount; ++i)
	{
		Object* tempObject = Engine::AddObject(Object());

		tempObject->Load(openStream);

		AddChild(tempObject);
	}
}
void Transform::Load(Stream* openStream)
{
	string garbage;

	openStream->ReadToken(&garbage);

	openStream->ReadToken(&garbage);
	openStream->ReadType(&position);

	openStream->ReadToken(&garbage);
	openStream->ReadType(&rotation);

	openStream->ReadToken(&garbage);
	openStream->ReadType(&scale);
}
void Physics::Load(Stream* openStream)
{
	openStream;
	string fieldName = string();
}
void Sprite::Load(Stream* openStream)
{
	string buffer;
	string garbage;

	openStream->ReadToken(&garbage);

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	frameIndex = std::stoi(buffer);

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	alpha = std::stof(buffer);

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	texture = ResourceLibrary<Texture>::Get(buffer);

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	mesh = ResourceLibrary<Mesh>::Get(buffer);
}
void Button::Load(Stream* openStream)
{
	string buffer;
	string garbage;

	openStream->ReadToken(&garbage);

	openStream->ReadToken(&garbage);
	openStream->ReadToken(&buffer);
	function = NamedFunction(buffer, FunctionLibrary::Get(buffer));
}

#pragma region Pre-Build Editing Area

static unordered_map LoadingFunctionMap = unordered_map<string, void(*)(Object*, Stream*, const UpdateLayer&)>
{
	{ "Button", &Load<Button> }
	, { "Physics", &Load<Physics> }
	, { "Sprite", &Load<Sprite> }
	, { "Transform", &Load<Transform> }
};

#pragma endregion Pre-Build Editing Area

void LoadComponent(Object* Output, Stream* openStream)
{
	string componentName;
	string updateLayer = "AVERAGE";

	//openStream->ReadToken(&updateLayer);
	openStream->ReadToken(&componentName);
	openStream->ShiftSpot(-(int)componentName.length());

	componentName.pop_back();

	LoadingFunctionMap[componentName](Output, openStream, (UpdateLayer)GetEnumValue(updateLayer));
}
