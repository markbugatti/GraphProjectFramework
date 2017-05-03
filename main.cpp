#include "main.h"

HWND hWnd; // descriptor
HINSTANCE hInst;
WCHAR szTitleName[MAX_LOADSTRING];
WCHAR szMainClassName[MAX_LOADSTRING];

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
					_In_opt_ HINSTANCE hPrevInstance, 
					_In_ LPWSTR lpCmdLine, 
					_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitleName, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_GRAPHPROJECT, szMainClassName, MAX_LOADSTRING);

	MyRegisterClass(hInstance, MainWndProc, szMainClassName);
	// create window
	CreateMainWnd(hWnd, hInst, nCmdShow, szMainClassName, szTitleName);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDA_ACCELERATOR));
	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{ 
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}