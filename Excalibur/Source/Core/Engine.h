/*********************************************************************
 * @file   Engine.h
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

#include "Component/Transform.h"
#include "ECS.h"
#include "Object.h"

#include "Enums/DrawMode.h"
#include "framework.h"
#include "Resource.h"

#include <vector>
#include <string>

#define OBJECT_JIVE_SIZE 100

using std::vector;
using std::string;

class System;
//class Object;
class Message;
//class HWND;

class Mesh;
class Texture;
class Sound;
class Channel;

class Engine
{
private:

	Engine();

public:

	Engine(Engine const& rhs) = delete;

	Engine& operator=(Engine const& rhs) = delete;

	~Engine();

	static int Init(HINSTANCE const& HInstance);

	static int Update(double& dt);

	static void Render();

	static void Exit();

	static void HandleMessage(Message* message);

	static void Add(System* system);

	static Engine* GetSingleton();

	static auto const& GetSourceObject() { return objects; }

	static Object* AddObject(Object const& object);



	static void SetWindow(HWND const& WindowHandle);

	//void SetPlatform(Platform* Platform) { platform = Platform; }

	//static Mesh* LoadMesh(string const& Name);
	static Texture* LoadTexture(string const& Name, unsigned int const& Rows = 1, unsigned int const& Columns = 1);

	static void SetTextureOffset(Vector<2> const& offset);

	static void Draw(Mesh const* MeshToDraw, DrawMode const& Mode);

	static void SetTexture(Texture const* texture);

	static void SetScale(Vector<3> const& Scale);

	static void SetPosition(Vector<3> const& Position);

	static void SetRotation(float const& Rotation);

	static Sound* LoadSound(string const& Name);

	static void PlaySound(Sound const& sound, Channel* channel);

private:

	static Jive<Object, OBJECT_JIVE_SIZE> objects;

	static vector<System*> systems;

};
