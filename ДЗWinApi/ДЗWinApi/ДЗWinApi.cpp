// ДЗWinApi.cpp : Определяет точку входа для приложения.
//
#include "framework.h"
#include "ДЗWinApi.h"
#include <Windows.h>
#include <string>
#include <algorithm>
#include <float.h>
#include <vector> 
#include <commctrl.h>
#include <math.h>
#include <windowsx.h>
#include <string>
#include <stdio.h>
#include <vector>




#define QUALITY	1000000
#define M_PI 3.1415926535897932384 //сокращение константы пи
#define MINA -0.360
#define MAXA 0.360
#define TDIAP 14.0

HANDLE hThread1; //управление потоками 
HANDLE hThread2;
HANDLE hThread3;
HANDLE hThread4;
HANDLE hThread5;

float size = 1.75;

float* F(float t) {
	float massiv[2];
	massiv[0] = sin(8.0 * t + 2.0);
	massiv[1] = sin(9.0 * t);
	return massiv;
}

float Func(float t) {
	return sin(t);
}

COLORREF Color = RGB(0, 0, 0);

std::vector<POINT> Data(QUALITY);

int DeletedPoints = 0;
float maxY;
float maxX;

float T = 0;

DWORD WINAPI Thread2(LPVOID t) {			//функция для первого потока
	int pos = 0;

	for (pos = 0; pos < QUALITY; pos++)
	{
		T += 0.01;
		Data[pos].x = (sin(8.0 * T + 2.0) * 100) + 500;
		Data[pos].y = (sin(9.0 * T) * 100) + 500;
	}
	maxY = abs(Data[0].y);
	maxX = abs(Data[0].x);
	for (int pos = 0; pos < QUALITY; pos++) {
		if (abs(Data[pos].x) > abs(maxX)) maxX = abs(Data[pos].x);
		if (abs(Data[pos].y) > abs(maxY)) maxY = abs(Data[pos].y);
	}
	int a = Data.size();
	return 0;
}


DWORD WINAPI Thread1(LPVOID t) {  //функция ,выполняемая первым потоком 

	HDC hdc = GetDC((HWND)t);
	MoveToEx(hdc, 0, 500, NULL);
	LineTo(hdc, 1000, 500);
	MoveToEx(hdc, 500, 0, NULL);
	LineTo(hdc, 500, 1000);
	for (int i = -10; i < 10; i++) {
		MoveToEx(hdc, 490, 500 + (i * 20 * size), NULL);
		LineTo(hdc, 510, 500 + (i * 20 * size));
	}
	for (int i = -10; i < 10; i++) {
		MoveToEx(hdc, 500 + (i * 20 * size), 490, NULL);
		LineTo(hdc, 500 + (i * 20 * size), 510);
	}
	ReleaseDC((HWND)t, hdc);
	for (int i = 0; i < ((QUALITY - DeletedPoints) / 4); i++) {
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500, Data[i].y * size - (500 * size) + 500, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500, Data[i].y * size - (500 * size) + 501, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501, Data[i].y * size - (500 * size) + 500, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501, Data[i].y * size - (501 * size) + 500, Color);
	}
	return 0;
}
DWORD WINAPI Thread3(LPVOID t) {  //функция ,выполняемая первым потоком 
	HDC hdc = GetDC((HWND)t);
	for (int i = (QUALITY - DeletedPoints) / 4; i < (((QUALITY - DeletedPoints) * 2) / 4); i++) {
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500, Data[i].y * size - (500 * size) + 500, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500, Data[i].y * size - (500 * size) + 501, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501, Data[i].y * size - (500 * size) + 500, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501, Data[i].y * size - (501 * size) + 500, Color);

	}
	return 0;
}
DWORD WINAPI Thread4(LPVOID t) {  //функция ,выполняемая первым потоком 
	HDC hdc = GetDC((HWND)t);
	for (int i = ((QUALITY - DeletedPoints) * 2) / 4; i < (((QUALITY - DeletedPoints) * 3) / 4); i++) {
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500, Data[i].y * size - (500 * size) + 500, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500, Data[i].y * size - (500 * size) + 501, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501, Data[i].y * size - (500 * size) + 500, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501, Data[i].y * size - (501 * size) + 500, Color);
	}
	return 0;
}
DWORD WINAPI Thread5(LPVOID t) {  //функция ,выполняемая первым потоком 
	HDC hdc = GetDC((HWND)t);
	for (int i = (((QUALITY - DeletedPoints) * 3) / 4); i < (QUALITY - DeletedPoints); i++) {
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500, Data[i].y * size - (500 * size) + 500, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 500, Data[i].y * size - (500 * size) + 501, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501, Data[i].y * size - (500 * size) + 500, Color);
		SetPixelV(hdc, Data[i].x * size - (500 * size) + 501, Data[i].y * size - (501 * size) + 500, Color);
	}
	return 0;
}

void StartDrawing(HWND hWnd) {
	hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
	hThread3 = CreateThread(NULL, 0, Thread3, hWnd, 0, NULL);
	hThread4 = CreateThread(NULL, 0, Thread4, hWnd, 0, NULL);
	hThread5 = CreateThread(NULL, 0, Thread5, hWnd, 0, NULL);
}

void StopDrawing(HWND hWnd) {
	TerminateThread(hThread1, 0);
	TerminateThread(hThread3, 0);
	TerminateThread(hThread4, 0);
	TerminateThread(hThread5, 0);
}

LRESULT CALLBACK WindowProcess(HWND hWindow,
	UINT uMessage,
	WPARAM wParameter,
	LPARAM lParameter)
{

	switch (uMessage) {
	case WM_CREATE:
	{
		hThread2 = CreateThread(NULL, 0, Thread2, hWindow, 0, NULL);

	}
	return 0;
	case WM_LBUTTONDOWN: 
	{
		hThread1 = CreateThread(NULL, 0, Thread1, hWindow, 0, NULL);
	}
	 return 0;

	case WM_KEYDOWN:
	{
		switch (wParameter) {
		case VK_UP: {
			StopDrawing(hWindow);
			size += 0.25;
			RECT Window;
			HDC hdc = GetDC(hWindow);
			GetWindowRect(hWindow, &Window);
			FillRect(hdc, &Window, CreateSolidBrush(RGB(255, 255, 255)));
			StartDrawing(hWindow);
		}
					return 0;
		case VK_DOWN: {
			StopDrawing(hWindow);
			size -= 0.25;
			RECT Window;
			HDC hdc = GetDC(hWindow);
			GetWindowRect(hWindow, &Window);
			FillRect(hdc, &Window, CreateSolidBrush(RGB(255, 255, 255)));
			StartDrawing(hWindow);
		}
					  return 0;
		}
	}
	return 0;
	case WM_DESTROY:
		//StopDrawing(hWindow);
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
	}
	return NULL;
}

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow) {
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)); //изначальный цвет окна 
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;

	wc.lpfnWndProc = WindowProcess;
	wc.lpszClassName = L"DZ";
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	if (!RegisterClassEx(&wc)) {
		return EXIT_FAILURE;
	}
	hwnd = CreateWindow(wc.lpszClassName, L"DZ",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX /*запрет на изменение размера окна*/
		, 0, 0, 900, 9	00, NULL, NULL, wc.hInstance, NULL);
	if (hwnd == INVALID_HANDLE_VALUE)
	{
		return EXIT_FAILURE;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0)) 
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}