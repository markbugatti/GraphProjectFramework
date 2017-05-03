#pragma once
#include "main.h"

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM MyRegisterClass(HINSTANCE hInstance, WNDPROC WndProc, WCHAR *szClassName);
void CreateMainWnd(HWND & hWnd, HINSTANCE hInst, INT nCmdShow, LPWSTR ClassName, LPWSTR TitleName);
INT_PTR CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);