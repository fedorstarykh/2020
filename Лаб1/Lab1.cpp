//#include <stdafx.h>
#include <Windows.h>
#include <string>

using namespace std;


LPCWSTR s2ws()
{
	char let = rand() % 255;
	string s (1, let);
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	wstring r(buf);
	delete[] buf;
	LPCWSTR result = r.c_str();
	return result;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HBRUSH turquoise = CreateSolidBrush(RGB(8, 232, 222));//светло-бирюзовый цвет
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rectPlace;
	GetClientRect(hWnd, &rectPlace);
	static int d = 0;
	switch (uMsg) 
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);

		HFONT hFont = CreateFont(rand() % 150 + 50, 0, rand() % 180, 0, 0, 0, 0, 0,
			DEFAULT_CHARSET,
			0, 0, 0, 0,
			L"Times New Roman"//любой шрифт
		);

		SetTextColor(hdc, RGB(rand() % 155 + 100, rand() % 155 + 100, rand() % 155 + 100));
		SelectObject(hdc, hFont);
		rectPlace.top = rand() % 600 - 20; rectPlace.left = rand() % 600 - 20;

		if (d)
		{
			DrawText(hdc, s2ws(), 1, &rectPlace, NULL);
		}
		else d = 1;
		EndPaint(hWnd, &ps);
	}
	return 0;

	case WM_LBUTTONDOWN:
	{
		InvalidateRect(hWnd, &rectPlace, false);
	}
	return 0;
	case WM_RBUTTONDOWN:
	{

		hdc = GetDC(hWnd);
		RECT rectangle;
		GetClientRect(hWnd, &rectangle);
		FillRect(hdc, &rectangle, turquoise);
		ReleaseDC(hWnd, hdc);
	}
	return 0;
	case WM_CREATE:
	{

	}
	return 0;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	HBRUSH turquoise = CreateSolidBrush(RGB(8, 232, 222));

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = turquoise;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	{
		wc.lpszClassName = L"Class";
		wc.lpszMenuName = NULL;
		wc.style = CS_VREDRAW | CS_HREDRAW;

		if (!RegisterClassEx(&wc)) {
			return EXIT_FAILURE;
		}
		hwnd = CreateWindow(wc.lpszClassName, L"Старых Лаб 1", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, NULL, NULL, wc.hInstance, NULL);
		if (hwnd == INVALID_HANDLE_VALUE)
		{
			return EXIT_FAILURE;
		}
		ShowWindow(hwnd, nCmdShow);
		UpdateWindow(hwnd);

		while (GetMessage(&msg, nullptr, 0, 0)) {
			DispatchMessage(&msg);
		}
		return (int)(msg.wParam);
	}
}

