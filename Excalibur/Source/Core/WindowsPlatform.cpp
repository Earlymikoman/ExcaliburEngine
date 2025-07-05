/*********************************************************************
 * @file   WindowsPlatform.cpp
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

#include "WindowsPlatform.h"

//#include "Mesh.h"
#include "../DirectX/DirectXGraphics.h"
#include "Engine.h"
//#include "ResourceLibrary.h"

//#include "framework.h"
//#include "Resource.h"

#include <iostream>

#define MAX_LOADSTRING 100

WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

static LRESULT CALLBACK PlatformCallback(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam);
//BOOL InitWindow(HINSTANCE hInstance, int nCmdShow);

#pragma region WindowsPlatform Static Field Initialization

InputSystem<char> WindowsPlatform::inputSystem = InputSystem<char>();

HINSTANCE WindowsPlatform::mAppInstance = nullptr;

int WindowsPlatform::mShow = 0;

unsigned int WindowsPlatform::mWindowWidth = 0;
unsigned int WindowsPlatform::mWindowHeight = 0;

unsigned int WindowsPlatform::mMaxFrameRate = 0;

unsigned int WindowsPlatform::mClassStyle = 0;

unsigned int WindowsPlatform::mWindowStyle = 0;

const char* WindowsPlatform::mWindowTitle = nullptr;

BOOL WindowsPlatform::mCreateConsole = 0;

int WindowsPlatform::mWindowIcon = 0;

WNDPROC WindowsPlatform::pWindowsCallback = 0;

#pragma endregion

WindowsPlatform* WindowsPlatform::GetInstance()
{
    static WindowsPlatform instance;

    return &instance;
}

void WindowsPlatform::InitializeInstance(HINSTANCE hInstance)
{
    WindowsPlatform& platform = *WindowsPlatform::GetInstance();

    // Initialize any system-specific variables here:
    platform.mAppInstance = hInstance;

    // Initialize the DigiPen Graphics Library.
    platform.mAppInstance = platform.mAppInstance;

    platform.mShow = true; // Start with window hidden.

    platform.mWindowTitle = "Mod2 - LAST CONTACT";

    // Start the window with little to no resolution, this technically won't be seen as showing has been set to false.
    //! NOTE: Any smaller than these values and DGL will not start the game with the error: "Problem creating depth-stencil buffer. Error 0x80070057"
    platform.mWindowWidth = 50;
    platform.mWindowHeight = 50;

    platform.mMaxFrameRate = 120;

    platform.mClassStyle = CS_HREDRAW | CS_VREDRAW;
    #ifdef _DEBUG
    // Thin border with only a close button.
    platform.mWindowStyle = WS_CAPTION | WS_SYSMENU;
    platform.mCreateConsole = true;
    #else
    // Full screen type window.
    platform.mWindowStyle = WS_POPUPWINDOW;
    platform.mCreateConsole = false;
    #endif

    platform.pWindowsCallback = PlatformCallback;

    // Game window and taskbar icon.
    platform.mWindowIcon = IDI_EXCALIBURWINDOWS;

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EXCALIBURWINDOWS, szWindowClass, MAX_LOADSTRING);
    WindowsPlatform::GetInstance()->RegisterWindowsClass();
    WindowsPlatform::GetInstance()->InitWindow(hInstance, platform.mShow);

    WindowsPlatform::GetInstance()->GetInputSystem()->Init();
}

void WindowsPlatform::Update(double& dt)
{
	dt;

    inputSystem.SendMessages();
}

ATOM WindowsPlatform::RegisterWindowsClass()
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = mClassStyle;
    wcex.lpfnWndProc = pWindowsCallback;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = mAppInstance;
    wcex.hIcon = LoadIcon(mAppInstance, MAKEINTRESOURCE(mWindowIcon));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_EXCALIBURWINDOWS);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL WindowsPlatform::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    //HINSTANCE hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

	//graphicsEngine = new DirectXData(hWnd);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

	Engine::SetWindow(hWnd);

    return TRUE;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// This callback function is called every time the application receives a message from the OS.
static LRESULT CALLBACK PlatformCallback(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    HINSTANCE hInst = WindowsPlatform::GetInstance()->GetAppInstance();

    switch (message)
    {
    case WM_KEYDOWN:
    {
        if (!(((lParam >> 30) & 0x1) != 0))
        {
            WindowsPlatform::GetInstance()->GetInputSystem()->KeyDown((char)wParam);
        }

        break;
    }

    case WM_KEYUP:
    {
        WindowsPlatform::GetInstance()->GetInputSystem()->KeyReleased((char)wParam);

        break;
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        /*HDC hdc = */BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//Mesh* WindowsPlatform::LoadMesh(string const& Name, vector<VertexData> const& Vertices)
//{
//	return ResourceLibrary<Mesh>::Add(new Mesh(Name, Vertices));
//}
//
//Texture* WindowsPlatform::LoadTexture(string const& Name)
//{
//	return DirectX::Load
//}
