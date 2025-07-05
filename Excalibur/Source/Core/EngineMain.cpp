/*********************************************************************
 * @file   main.cpp
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

#include "framework.h"
#include "Resource.h"

#include "Engine.h"
#include "WindowsPlatform.h"

#include "ECS.h"
#include "Message.h"
#include "Jive.h"
#include "Component/Physics.h"

#include <chrono>
#include <omp.h>
#include <fstream>
#include <iostream>
#include <string>

#pragma region Includes For Testing Only

#include "SaveFunctions.h"
#include "../../../SharedDependencies/Source/Stream.h"
#include "Object.h"
#include "Mesh.h"
#include "../DirectX/DirectXGraphics.h"

#pragma endregion Includes For Testing Only

using std::cout;
using std::endl;
using std::string;

class Transform;

void AttachConsoleWindow()//Courtesy of chatgpt.
{
	AllocConsole();  // Create a new console
	FILE* dummy;
	freopen_s(&dummy, "CONOUT$", "w", stdout);
	freopen_s(&dummy, "CONOUT$", "w", stderr);
	freopen_s(&dummy, "CONIN$", "r", stdin);
	std::cout.clear();
	std::cerr.clear();
	std::cin.clear();
}

void MessagesManagement(HINSTANCE hInstance, int* runningFlag);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	hInstance;
	hPrevInstance;
	lpCmdLine;
	nCmdShow;

	AttachConsoleWindow();

	Engine* mainEngine = Engine::GetSingleton();
	//mainEngine->SetPlatform(WindowsPlatform::GetInstance());

	int running = mainEngine->Init(hInstance);

	//Add Systems to the Engine here.
	mainEngine->Add(ECS<Physics>::GetInstance());
	//mainEngine->GetSourceObject()->AddComponent(Physics());

	auto previousTime = std::chrono::high_resolution_clock::now();








	::Stream newStream = ::Stream("Data/WriteTest.txt");
	string bufferString;

	Mesh testmesh = Mesh
	(
		"TestMesh"
		, vector<VertexData>
		{
			VertexData(-0.5f, -0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 0.0f, 1.0f)
			, VertexData(-0.5f, 0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 0.0f, 0.0f)
			, VertexData(0.5f, 0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 1.0f, 0.0f)
			, VertexData(-0.5f, -0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 0.0f, 1.0f)
			, VertexData(0.5f, 0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 1.0f, 0.0f)
			, VertexData(0.5f, -0.5f, 0.5f, 0.6f, 0.9f, 1.0f, 1.0f, 1.0f)
		}
	);

	testmesh.Serialize(&bufferString);

	newStream.Close();

	int a = 0;
	++a;






#pragma omp parallel sections
	{
#pragma omp section
		{
			MessagesManagement(hInstance, &running);
		}

#pragma omp section
		{
			while (running)
			{
				auto newTime = std::chrono::high_resolution_clock::now();
				double dt = (std::chrono::duration<double>(newTime - previousTime)).count();
				previousTime = newTime;

				running = mainEngine->Update(dt);

				mainEngine->Render();

				//running = 0;
			}
		}
	}

	mainEngine->Exit();

	return 0;
}

void MessagesManagement(HINSTANCE hInstance, int* runningFlag)
{
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EXCALIBURWINDOWS));

	MSG msg;

	while (*runningFlag && GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
