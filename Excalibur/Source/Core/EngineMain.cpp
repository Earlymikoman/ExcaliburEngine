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
#include "Component/Sprite.h"

#include <chrono>
#include <omp.h>
#include <fstream>
#include <iostream>
#include <string>

#pragma region Includes For Testing Only

#include "SaveFunctions.h"
#include "LoadFunctions.h"
#include "../../../SharedDependencies/Source/Stream.h"
#include "Object.h"
#include "Mesh.h"
#include "../DirectX/DirectXGraphics.h"
#include "ResourceLibrary.h"

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
	mainEngine->Add(ECS<Sprite>::GetInstance());
	//mainEngine->GetSourceObject()->AddComponent(Physics());

	auto previousTime = std::chrono::high_resolution_clock::now();








	::Stream objectStream = ::Stream("Data/TestObject.txt");
	::Stream spriteStream = ::Stream("Data/TestSprite.txt");
	string bufferString;

	//Sprite testSprite;

	//testSprite.Load(&spriteStream);

	Object* testObject = Engine::AddObject(Object());
	testObject->Load(&objectStream);
	//testObject->AddComponent(testSprite);
	//Transform* testTransform = testObject->GetTransform();
	//testTransform->SetScale(Vector<3>(10.0f, 10.0f));

	/*objectStream.Clear();
	testObject->Serialize(&bufferString);
	objectStream.Write(bufferString);*/

	spriteStream.Close();
	objectStream.Close();






	
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
