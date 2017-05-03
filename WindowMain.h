#pragma once

#include "stdafx.h"
#include "resource.h"



class Functions
{
private:
	
public:
	Functions();
	void LoadName(HINSTANCE hInstance, UINT uID, LPSTR ClassName, int Length);
	ATOM MainRegisterClass(HINSTANCE hInstance, WNDPROC WndProc, WCHAR *szClassName);
	void MainInitClass(LPCWSTR ClassName, LPCWSTR TitleName, DWORD dwStyle, int x, int y,
		int nWidth, int nHeight, HWND *hWnd,HINSTANCE hInst, LPVOID lpParam);

	~Functions();
};

