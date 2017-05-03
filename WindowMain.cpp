#include "WindowMain.h"
#include "Window.h"

Functions::Functions()
{
}
ATOM Functions::MainRegisterClass(HINSTANCE hInstance,  WNDPROC WndProc, WCHAR *szClassName) {
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; // WNDPROC
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; // HINSTANCE
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPHPROJECT_ICON));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GRAPHPROJECT);
	wcex.lpszClassName = szClassName; // WCHAR
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_GRAPHPROJECT_ICON));
	return RegisterClassExW(&wcex);
}

void Functions::MainInitClass(LPCWSTR ClassName, LPCWSTR TitleName, DWORD dwStyle,
	int x, int y, int nWidth, int nHeight, HWND *hWnd, HINSTANCE hInst, LPVOID lpParam)
{
	*hWnd = CreateWindowW(ClassName, TitleName, dwStyle, x, y, nWidth, nHeight, nullptr, nullptr, hInst, nullptr);
}

void Functions::LoadName(HINSTANCE hInstance, UINT uID, LPSTR ClassName, int Length) {

}

//LRESULT CALLBACK Functions::MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//}

Functions::~Functions()
{
}
