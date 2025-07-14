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
#include "Component/TextSprite.h"
#include "Component/Button.h"
#include "Component/AudioSource.h"

#pragma region Game Mains

#include "../JustPressStart!/JustPressStartMain.h"

#pragma endregion Game Mains

#include <chrono>
#include <omp.h>
#include <fstream>
#include <iostream>
#include <string>

/*
#pragma region Includes For Testing Only

#include "SaveFunctions.h"
#include "LoadFunctions.h"
#include "../../../SharedDependencies/Source/Stream.h"
#include "../../../SharedDependencies/Source/Matrix.h"
#include "Object.h"
#include "Mesh.h"
#include "../DirectX/DirectXGraphics.h"
#include "../FMOD/FMODAudio.h"
#include "ResourceLibrary.h"
//void ReportLiveDirectXObjects();

#pragma endregion Includes For Testing Only
*/

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

void InitGame()
{
	JustPressStartMain();
}

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
	mainEngine->Add(ECS<Sprite>::GetInstance());
	mainEngine->Add(ECS<TextSprite>::GetInstance());
	mainEngine->Add(ECS<Physics>::GetInstance());
	mainEngine->Add(ECS<Button>::GetInstance());
	mainEngine->Add(ECS<AudioSource>::GetInstance());

	auto previousTime = std::chrono::high_resolution_clock::now();

	InitGame();

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

//#include <dxgidebug.h>
//
//void ReportLiveDirectXObjects()
//{
//	// Load the debug interface
//	using DXGIGetDebugInterfaceFn = HRESULT(WINAPI*)(REFIID, void**);
//	HMODULE dxgidebug = LoadLibraryExW(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
//	if (!dxgidebug) return;
//
//	auto DXGIGetDebugInterface = reinterpret_cast<DXGIGetDebugInterfaceFn>(
//		GetProcAddress(dxgidebug, "DXGIGetDebugInterface"));
//	if (!DXGIGetDebugInterface)
//	{
//		FreeLibrary(dxgidebug);
//		return;
//	}
//
//	IDXGIDebug1* debug = nullptr;
//	if (SUCCEEDED(DXGIGetDebugInterface(__uuidof(IDXGIDebug1), (void**)&debug)))
//	{
//		// This prints all live DXGI and D3D11 objects to the debug output
//		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
//		debug->Release();
//	}
//
//	FreeLibrary(dxgidebug);
//}
