#include <Windows.h>

#include "Definitions.h"

constexpr int WINDOW_STARTING_WIDTH = 800;
constexpr int WINDOW_STARTING_HEIGHT = 600;

static LRESULT CALLBACK ProcessWindowMessage(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(windowHandle, &ps);
		EndPaint(windowHandle, &ps);
		return 0;
	}

	case WM_CLOSE:
		DestroyWindow(windowHandle);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}

	return DefWindowProc(windowHandle, message, wParam, lParam);
}

static HINSTANCE DefineWindowClass(const HINSTANCE& instanceHandle)
{
	WNDCLASS windowClass = {};

	windowClass.lpfnWndProc = ProcessWindowMessage;
	windowClass.hInstance = instanceHandle;
	windowClass.lpszClassName = APPLICATION_NAME;
	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

	RegisterClass(&windowClass);

	return instanceHandle;
}

static HWND InitializeWindow(const HINSTANCE& instanceHandle)
{
	HWND windowHandle = CreateWindowEx(
		0,
		APPLICATION_NAME,
		APPLICATION_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_STARTING_WIDTH,
		WINDOW_STARTING_HEIGHT,
		nullptr,
		nullptr,
		instanceHandle,
		nullptr
	);

	return windowHandle;
}

int WINAPI wWinMain(
	_In_ HINSTANCE instanceHandle,
	_In_opt_ HINSTANCE previousInstanceHandle,
	_In_ PWSTR arguments,
	_In_ int windowState)
{
	DefineWindowClass(instanceHandle);
	HWND windowHandle = InitializeWindow(instanceHandle);

	ShowWindow(windowHandle, windowState);
	UpdateWindow(windowHandle);

	MSG message = {};
	while (GetMessage(&message, nullptr, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnregisterClass(APPLICATION_NAME, instanceHandle);
	return 0;
}