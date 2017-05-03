#include "main.h"

INT top;	// top of windows stack
RECT WndRect; // window size

// Objects windows
Rectangles *Window = new Rectangles[MAX_FIGURES];


// dialog box
TCHAR buffEdtHeight[EDIT_BUFFSIZE], buffEdtWidth[EDIT_BUFFSIZE]; // text buffers to dialogbox
INT   valEdtHeight, valEdtWidth; // value of edits

// to draw
HPEN hWindowPen;
HDC  hdc;
PAINTSTRUCT ps;

// difference between pointer and [x,y] position of figure 
INT crntDiffX;
INT crntDiffY;

// it shows whether figure is captured or no
BOOL cptred = false;

// screen buffer buffer
HBITMAP hBuff = NULL;
HDC hMem = NULL;

POINT mousePt;    // current mouse pt
POINT mouseOldPt; // old mouse point to return figure in case 

ATOM MyRegisterClass(HINSTANCE hInstance, WNDPROC WndProc, WCHAR *szClassName) {
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
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDM_MENU);
	wcex.lpszClassName = szClassName; // WCHAR
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_GRAPHPROJECT_ICON));
	return RegisterClassExW(&wcex);
}

void CreateMainWnd(HWND &hWnd, HINSTANCE hInst, INT nCmdShow, LPWSTR ClassName, LPWSTR TitleName)
{
	hWnd = CreateWindowW(ClassName, TitleName, WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, nullptr);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
}

INT_PTR CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			GetWindowText(GetDlgItem(hWnd, IDC_EDIT1), buffEdtHeight, EDIT_BUFFSIZE);
			GetWindowText(GetDlgItem(hWnd, IDC_EDIT2), buffEdtWidth, EDIT_BUFFSIZE);
			EndDialog(hWnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hWnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &WndRect);
		top = -1; // no Window
		hdc = GetDC(hWnd);
		hMem = CreateCompatibleDC(hdc); // virtual dc, a buffer
		hBuff = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT); // bitmap
		SelectObject(hMem, hBuff);  // select Bitmap on virtual dc
		PatBlt(hMem, 0, 0, WndRect.right, WndRect.bottom, WHITENESS);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
			case IDM_FILE_CREATE:
				if (DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_NEW), hWnd, DialogProc) == IDOK) {
					valEdtHeight = _ttoi(buffEdtHeight);
					valEdtWidth = _ttoi(buffEdtWidth);
					if (!++top)
					{
						EnableMenuItem(GetMenu(hWnd), IDM_FILE_DELETE, MF_ENABLED);
					}
					if (valEdtHeight != 0 && valEdtWidth)
					{
						Window[top].setFrameWidth(2);
						Window[top].setColor(RGB(0, 0, 0));
				
						Window[top].setX(10);
						Window[top].setY(10);

						Window[top].setSy(valEdtHeight);
						Window[top].setSx(valEdtWidth);

						PatBlt(hMem, 0, 0, WndRect.right, WndRect.bottom, WHITENESS);
						ObjectDraw(hMem, top, hWindowPen, Window);
						InvalidateRect(hWnd, NULL, FALSE);
					}
				}
				break;
			case IDM_FILE_DELETE:
				if (--top == -1)
				{
					EnableMenuItem(GetMenu(hWnd), IDM_FILE_DELETE, MF_GRAYED);
				}
				PatBlt(hMem, 0, 0, WndRect.right, WndRect.bottom, WHITENESS);
				ObjectDraw(hMem, top, hWindowPen, Window);
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		mousePt.x = LOWORD(lParam);
		mousePt.y = HIWORD(lParam);
		if (top > 0)
		{
			for (int i = top; i >= 0; i--)
			{
				if (PtInRect(&Window[i].getPos(), mousePt))
				{
					Rectangles tmp;
					tmp = Window[i];
					for (int j = i; j < top; j++)
					{
						Window[j] = Window[j+1];
					}
					Window[top] = tmp;
					i = -1;
				}
			}
		}
		if (PtInRect(&Window[top].getPos(), mousePt))
		{
			SetCapture(hWnd);
			mouseOldPt.x = Window[top].getX();
			mouseOldPt.y = Window[top].getY();
			crntDiffX = mousePt.x - Window[top].getX();
			crntDiffY = mousePt.y - Window[top].getY();
			cptred = true;
		}

		break;
	case WM_LBUTTONUP:
		if(cptred) 
		{
			mousePt.x = LOWORD(lParam);
			mousePt.y = HIWORD(lParam);
			if (!PtInRect(&WndRect, mousePt))
			{
				Window[top].setX(mouseOldPt.x);
				Window[top].setY(mouseOldPt.y);
			}
			cptred = false;
			ReleaseCapture();
			PatBlt(hMem, 0, 0, WndRect.right, WndRect.bottom, WHITENESS);
			ObjectDraw(hMem, top, hWindowPen, Window);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_MOUSEMOVE:
		if (cptred)
		{
			mousePt.x = LOWORD(lParam);
			mousePt.y = HIWORD(lParam);
			Window[top].setX(mousePt.x - crntDiffX);
			Window[top].setY(mousePt.y - crntDiffY);
			PatBlt(hMem, 0, 0, WndRect.right, WndRect.bottom, WHITENESS);
			ObjectDraw(hMem, top, hWindowPen, Window);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &WndRect);
		PatBlt(hMem, 0, 0, WndRect.right, WndRect.bottom, WHITENESS);
		ObjectDraw(hMem, top, hWindowPen, Window);
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, WndRect.right, WndRect.bottom, hMem, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hMem);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}