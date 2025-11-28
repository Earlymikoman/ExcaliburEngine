/*********************************************************************
 * @file   Engine.cpp
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

#include "Engine.h"

#include "Message.h"
#include "WindowsPlatform.h"
#include "../DirectX/DirectXGraphics.h"
#include "../FMOD/FMODAudio.h"
#include "Mesh.h"
#include "ResourceLibrary.h"

#include <iostream>

typedef WindowsPlatform EnginePlatform;
typedef DirectXData EngineGraphicsEngine;
typedef FMODAudio EngineAudioEngine;

//EngineGraphicsEngine::SetWindow(HWND const& windowHandle);

Jive<Object, OBJECT_JIVE_SIZE> Engine::objects = Jive<Object, OBJECT_JIVE_SIZE>(vector<Object>{});

vector<System*> Engine::systems = vector<System*>();

Object Engine::cursor = Object();

Engine::Engine()
	//: source(Object::CreateObject())
{

}

Engine::~Engine()
{
	//delete source;
}

int Engine::Init(HINSTANCE const& HInstance)
{
	EnginePlatform::InitializeInstance(HInstance);

	EngineGraphicsEngine::InitializeGraphics();

	EngineAudioEngine::InitializeAudio();



	return 1;
}

int Engine::Update(double& dt)
{
	dt;

	EnginePlatform::Update(dt);

	cursor.GetTransform()->SetPosition(EnginePlatform::GetCursorPosition());
	cout << "Cursor: " << cursor.GetTransform()->GetPosition().X() << " " << cursor.GetTransform()->GetPosition().Y() << endl << endl;

	for (int i = 0; i < systems.size(); ++i)
	{
		systems[i]->Update(dt);
	}

	return 1;
}

void Engine::Render()
{
	EngineGraphicsEngine::StartDrawing();

	for (int i = 0; i < systems.size(); ++i)
	{
		systems[i]->Render();
	}

	EngineGraphicsEngine::FinishDrawing();
}

void Engine::Exit()
{

}

void Engine::HandleMessage(Message* message)
{
	std::cout << message->GetTag() << std::endl;

	for (int i = 0; i < systems.size(); ++i)
	{
		systems[i]->HandleMessage(message);
	}
}

void Engine::Add(System* system)
{
	systems.push_back(system);
}

Object* Engine::AddObject(Object const& object)
{
	JiveIndex index = objects.Add(object);

	Object* realObject = &objects[index];
	realObject->SetEngineIndex(index);

	return realObject;
}

void Engine::RemoveObject(JiveIndex index)
{
	for (int i = (int)objects[index].GetChildren().size() - 1; i >= 0; --i)
	{
		RemoveObject(objects[index].GetChildren()[i]->GetEngineIndex());
	}

	if (objects[index].GetParent())
	{
		objects[index].GetParent()->RemoveChild(&objects[index]);
	}

	for (auto& componentPair : objects[index].GetComponents())
	{
		componentPair.first->RemoveComponent(componentPair.second);
	}

	objects[index].Deallocate();

	objects.Remove(index);
}

void Engine::SetWindow(HWND const& WindowHandle)
{
	EngineGraphicsEngine::SetWindow(WindowHandle);
}

HWND const& Engine::GetCurrentWindow()
{
	return EngineGraphicsEngine::GetCurrentWindow();
}

unsigned int Engine::GetWindowWidth()
{
	return EnginePlatform::GetWindowWidth();
}

unsigned int Engine::GetWindowHeight()
{
	return EnginePlatform::GetWindowHeight();
}

Engine* Engine::GetSingleton()
{
	static Engine instance = Engine();

	return &instance;
}

void Engine::Draw(Mesh const* MeshToDraw, DrawMode const& Mode)
{
	EngineGraphicsEngine::Draw(MeshToDraw, Mode);
}

void Engine::SetTexture(Texture const* texture)
{
	EngineGraphicsEngine::SetTexture(texture);
}

void Engine::SetScale(Vector<3> const& Scale)
{
	EngineGraphicsEngine::SetScale(Scale);
}

void Engine::SetPosition(Vector<3> const& Position)
{
	EngineGraphicsEngine::SetPosition(Position);
}

void Engine::SetRotation(float const& Rotation)
{
	EngineGraphicsEngine::SetRotation(Rotation);
}

Sound* Engine::LoadSound(string const& Name)
{
	return EngineAudioEngine::LoadSound(Name);
}

void Engine::PlaySound(Sound const& sound, Channel* channel)
{
	EngineAudioEngine::PlaySound(sound, channel);
}

void Engine::SetTextureOffset(Vector<2> const& offset)
{
	EngineGraphicsEngine::SetTextureOffset(offset);
}

#pragma region Resource Loading Functions

//Mesh* Engine::LoadMesh(string const& Name)
//{
//	return EngineGraphicsEngine::Load
//}
//
Texture* Engine::LoadTexture(string const& Name, unsigned int const& Rows, unsigned int const& Columns)
{
	return EngineGraphicsEngine::LoadTexture(Name, Rows, Columns);
}

#pragma endregion
