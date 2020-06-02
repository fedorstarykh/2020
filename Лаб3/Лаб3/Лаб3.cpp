#include <Windows.h>
#include <iostream>
#include <commctrl.h>
#include "resource.h"
#include "resource.h"

#pragma once 

bool boob = false;
bool pyshka = false;
#define IDC_STATIC1 1111
#define IDC_STATIC2 2222
#define IDC_STATIC3 3333
#define IDM_BOOBLIK 4444
#define IDM_CLOSEBUTTON 5555
#define BOOBLIK_SIZE 200
#define IDM_PYSHKA 7777
#define PYSHKA_SIZE 200
#define IDM_DIALOGBUTTON 9999

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_INITDIALOG: {
		RECT ActualSize;
		GetClientRect(hWnd, &ActualSize);
		
		//int WINAPI GetWindowText(_In_   HWND hWnd, _Out_  LPTSTR HBRUSH, _In_   int nd);
		HWND hwndButton = CreateWindow(L"BUTTON", L"Close", WS_VISIBLE | WS_CHILD, ActualSize.right - 50, ActualSize.bottom - 75, 50, 50, hWnd, (HMENU)IDM_CLOSEBUTTON, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
		HWND hwndStatic1 = CreateWindow(L"STATIC", L"TEXT1", WS_VISIBLE | WS_CHILD | SS_CENTER, ActualSize.right - 150, ActualSize.bottom - 50, 50, 25, hWnd, (HMENU)IDC_STATIC1, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
		HWND hwndStatic2 = CreateWindow(L"STATIC", L"TEXT2", WS_VISIBLE | WS_CHILD | SS_CENTER, ActualSize.right - 250, ActualSize.bottom - 50, 50, 50, hWnd, (HMENU)IDC_STATIC2, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	}
		return 0;
	case WM_CTLCOLORSTATIC:
		if ((HWND)lParam == GetDlgItem(hWnd, IDC_STATIC1))
		{
			SetBkMode((HDC)wParam, GetSysColor(CTLCOLOR_DLG));
			SetTextColor((HDC)wParam, RGB(255, 0, 0));
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}
		else if ((HWND)lParam == GetDlgItem(hWnd, IDC_STATIC2))
		{
			SetBkMode((HDC)wParam, GetSysColor(CTLCOLOR_DLG));
			SetTextColor((HDC)wParam, RGB(48, 213, 200));
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}
		return 0;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDM_CLOSEBUTTON) {
			EndDialog(hWnd, 0);
		}
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return 0;

	}
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HBRUSH brown = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
	HBRUSH yellow = CreateSolidBrush(RGB(255, 191, 0));
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rectPlace;
	GetClientRect(hWnd, &rectPlace);

	switch (uMsg) {
	case WM_PAINT:
	{
		
		hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		EndPaint(hWnd, &ps);
		if (boob) {
			
			InvalidateRect(hWnd, NULL, false);
			hdc = BeginPaint(hWnd, &ps);

			SelectObject(hdc, brown);
			RECT ActualSize;
			GetClientRect(hWnd, &ActualSize);
			SelectObject(hdc, yellow);
			Rectangle(hdc, -1, -1, 1000, 1000);
			int n = rand() % 100 + 100;
			SelectObject(hdc, brown);
			Ellipse(hdc,
				(ActualSize.right / 2 - n),
				(ActualSize.bottom / 2 - n),
				(ActualSize.right / 2 + n),
				(ActualSize.bottom / 2 + n));
			
			SelectObject(hdc, yellow);
			Ellipse(hdc,
				(ActualSize.right / 2 - n / 2),
				(ActualSize.bottom / 2 - n / 2),
				(ActualSize.right / 2 + n / 2),
				(ActualSize.bottom / 2 + n / 2));
			DeleteObject(hdc);
			EndPaint(hWnd, &ps);
		
		}
		 if (pyshka) {
			 int n = rand() % 100 + 100;

			InvalidateRect(hWnd, NULL, false);
			hdc = BeginPaint(hWnd, &ps);
			RECT ActualSize;
			
			GetClientRect(hWnd, &ActualSize);
			SelectObject(hdc, yellow);
			Rectangle(hdc, -1, -1, 1000, 1000);
			std::cout << ActualSize.bottom << ActualSize.right;
			SelectObject(hdc, brown);
			Ellipse(hdc,
				(ActualSize.right / 2 - n),
				(ActualSize.bottom / 2 - n),
				(ActualSize.right / 2 + n),
				(ActualSize.bottom / 2 + n));
			DeleteObject(hdc);
			EndPaint(hWnd, &ps);
		}
		
	
	}

	case WM_LBUTTONDOWN:
	{
	}
	return 0;
	case WM_RBUTTONDOWN:
	{

	}
	return 0;
	case WM_CREATE:
	{
		RECT ActualSize;
		GetClientRect(hWnd, &ActualSize);
		HWND hwndButton = CreateWindow(L"BUTTON", L"Close", WS_VISIBLE | WS_CHILD, ActualSize.right - 50, ActualSize.top + 0, 50, 50, hWnd, (HMENU)IDM_CLOSEBUTTON, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
		HWND hwndDialogButton = CreateWindow(L"BUTTON", L"Dialog", WS_VISIBLE | WS_CHILD, ActualSize.right - 50, ActualSize.top + 50, 50, 50, hWnd, (HMENU)IDM_DIALOGBUTTON, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
		HMENU hMenubar = CreateMenu();
		HMENU hMenu = CreateMenu();
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu, L"Булочки");
		AppendMenu(hMenu, MF_STRING, IDM_BOOBLIK, L"Бублик");
		AppendMenu(hMenu, MF_STRING, IDM_PYSHKA, L"Пышка");
		SetMenu(hWnd, hMenubar);

	}
	return 0;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDM_BOOBLIK) {
			boob = true;
			pyshka = false;
	
			InvalidateRect(hWnd, NULL, false);
			
		}
		else if (LOWORD(wParam) == IDM_PYSHKA) {
			pyshka = true;
			boob = false;
			InvalidateRect(hWnd, NULL, false);
			
		}
		else if (LOWORD(wParam) == IDM_CLOSEBUTTON) {
			PostQuitMessage(0);
		}
		else if (LOWORD(wParam) == IDM_DIALOGBUTTON) {
			DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DlgProc), 0);
		}

	}
	return 0;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}
	return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
};



int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) {
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	HBRUSH turquoise = CreateSolidBrush(RGB(255, 191, 0));
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = turquoise;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Class";
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc)) {
		return EXIT_FAILURE;
	}
	hwnd = CreateWindow(wc.lpszClassName, L"Lab_3", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 0, 0, 900, 680, NULL, NULL, wc.hInstance, NULL);
	if (hwnd == INVALID_HANDLE_VALUE)
	{
		return EXIT_FAILURE;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}
