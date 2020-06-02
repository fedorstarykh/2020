#include <stdafx.h>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <float.h>
#include <vector> 
#include <commctrl.h>

#pragma comment( lib, "comctl32.lib")

#pragma comment( linker, "/manifestdependency:\"type='win32' \
        name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
        processorArchitecture='*' publicKeyToken='6595b64144ccf1df' \
        language='*'\"")


#define TABLESIZE 10
#define TABLESTARTY 20
#define GRAPH_SIZE 400
#define NEW_GRAPH 144
#define MAXGRAPHS 1
#define WINDOWX 1600
#define WINDOWY 900
#define GOFFESET 400
#define CREATECOLLECTOR 1500
#define DELETECOLLECTOR 1501
#define CREATEDRAW 1600
#define DELETEDRAW 1601
HANDLE hThread1;
HANDLE hThread2;
DWORD WINAPI Thread1(LPVOID t);
DWORD WINAPI Thread2(LPVOID t);
BOOL thread1_working = false;
BOOL thread2_working = false;
int ActualGraph = 0, AmoutOfGraphs=0;
char buff[20];
bool Flag = false;
void swap(double* arr, double* arr2, int i, int minIndex)
{
	int tmp = arr[i];
	arr[i] = arr[minIndex];
	arr[minIndex] = tmp;

	tmp = arr2[i];
	arr2[i] = arr2[minIndex];
	arr2[minIndex] = tmp;
}

void selectionSort(double* arr, double* arr2, int length)
{
	int i, j, minIndex;
	int n = length;
	for (i = 0; i < n - 1; i++)
	{
		minIndex = i;

		for (j = i + 1; j < n; j++)
			if (arr[j] > arr[minIndex])
				minIndex = j;

		if (minIndex != i)
		{
			swap(arr, arr2, i, minIndex);
		}
	}
}


HWND NewData(HWND hwnd, int x, int y) {
	HWND New = CreateWindow(L"EDIT", L"100", WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, 50, 20, hwnd, NULL, NULL, NULL);
	HFONT font = CreateFont(-17, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"Times new Roman");
	SendMessage(New, WM_SETFONT, (WPARAM)font, MAKELPARAM(true, 0));
	return New;
}
double deshifr() {
	std::string parsed = "";
	int counter = 0;
	for (int i = 0; i < 10; i++) {
		if (buff[i] != '\0') {
			parsed += buff[i];
			counter++;
		}
	}
	try {
		stof(parsed);
	}
	catch (...) {
		MessageBox(NULL, L"Wrong Value", L"Wrong Value", MB_OK);
		return 0;
	}
	return stof(parsed);
}

HWND hwndDefault = NULL;


class Graph
{
private:
	

public:
	COLORREF Color = RGB(rand() % 155 + 100, rand() % 155 + 100, rand() % 155 + 100);
	int ActualRow,
		ActualColumn;
	HWND **TableHWnd = new HWND*[TABLESIZE];
	double **TableData = new double*[TABLESIZE];
	Graph(HWND hWnd) {
				int ActualColumn = 0, ActualRow = 0;
				for (int i = 0; i < TABLESIZE; i++) TableHWnd[i] = new HWND[TABLESIZE];
				for (int i = 0; i < TABLESIZE; i++) TableData[i] = new double[TABLESIZE];
				for (int i = 0; i < TABLESIZE; i++) {

					TableHWnd[ActualColumn][ActualRow] = NewData(hWnd, WINDOWX - 100 - 100 * AmoutOfGraphs,40 + ActualRow * 20);
					ActualColumn++;
					TableHWnd[ActualColumn][ActualRow] = NewData(hWnd, WINDOWX - 50 - 100 * AmoutOfGraphs,40 + ActualRow * 20);
					ActualRow++;

					ActualColumn--;
				}

			
	
				}
	void Sort() {
		selectionSort(TableData[0], TableData[1], 10);
	}
	double ResizeX = 1,
		   ResizeY = 1;
	int    OffsetX = 0,
		   OffsetY = 0;
	
	void getXresizeFactor() {
		double maxX = TableData[0][0],
			minX = TableData[0][0];
		for (int i = 0; i < 10; i++) {
			if (abs(TableData[0][i]) > maxX) {
				maxX = abs(TableData[0][i]);
			}
			if (abs(TableData[0][i]) < minX) {
				minX = abs(TableData[0][i]);
			}
		}
		OffsetX = minX;
		ResizeX = GRAPH_SIZE / abs(maxX);
	}

	void getYresizeFactor() {
		double
			maxY = TableData[1][0],
			minY = TableData[1][0];
		for (int i = 0; i < 10; i++) {
			if (abs(TableData[1][i]) > maxY) {
				maxY = abs(TableData[1][i]);
			}
			if (abs(TableData[1][i]) < minY) {
				minY = abs(TableData[1][i]);
			}

		}
		OffsetY = minY;
		ResizeY = GRAPH_SIZE / abs(maxY);
	}
};




std::vector<Graph> Graphs;




DWORD WINAPI Thread1(LPVOID t) {

		//DRAWING THREAD
	while(thread1_working){
	PAINTSTRUCT ps;
		
		HDC hdc = GetDC(HWND(t));
		RECT rect;
		rect.bottom = 800;
		rect.right = 800;
		FillRect(hdc, &rect, CreateSolidBrush(RGB(100, 200, 200)));
		Graphs[0].getYresizeFactor();
		double resizeFactorY = Graphs[0].ResizeY;
		Graphs[0].getXresizeFactor();
		double resizeFactorX = Graphs[0].ResizeX;
		for (ActualGraph = 0; ActualGraph < AmoutOfGraphs; ActualGraph++)
		{
			Graphs[ActualGraph].getYresizeFactor();
			Graphs[ActualGraph].getXresizeFactor();
			if (Graphs[ActualGraph].ResizeX < resizeFactorX) {
				resizeFactorX = Graphs[ActualGraph].ResizeX;
			}
			if (Graphs[ActualGraph].ResizeY < resizeFactorY) {
				resizeFactorY = Graphs[ActualGraph].ResizeY;
			}
		}


		for (ActualGraph = 0; ActualGraph < AmoutOfGraphs; ActualGraph++)
		{
			Graphs[ActualGraph].getYresizeFactor();
			Graphs[ActualGraph].getXresizeFactor();
			for (int i = 0; i < 10 - 1; i++) {
				HDC hdc = GetDC(HWND(t));
				BeginPaint(HWND(t), &ps);
				HPEN Pen = CreatePen(PS_DASH, 3, Graphs[ActualGraph].Color);
				HPEN Box = (HPEN)SelectObject(hdc, Pen);
				SelectObject(hdc, Pen);
				MoveToEx(hdc, (Graphs[ActualGraph].TableData[0][i] * resizeFactorX) + GOFFESET,
					400 - (Graphs[ActualGraph].TableData[1][i] * resizeFactorY), NULL);
				LineTo(hdc, (Graphs[ActualGraph].TableData[0][i + 1] * resizeFactorX) + GOFFESET,
					400 - (Graphs[ActualGraph].TableData[1][i + 1] * resizeFactorY));
				/*int a = Graphs[ActualGraph].TableData[0][i] * Graphs[ActualGraph].ResizeX,
					b = Graphs[ActualGraph].TableData[1][i] * Graphs[ActualGraph].ResizeY,
					c = Graphs[ActualGraph].TableData[0][i + 1] * Graphs[ActualGraph].ResizeX,
					d = Graphs[ActualGraph].TableData[1][i + 1] * Graphs[ActualGraph].ResizeY;*/

				ReleaseDC(HWND(t), hdc);

			}
			
			MoveToEx(hdc, 400, 0, NULL);
			LineTo(hdc, 400,
				800);
			MoveToEx(hdc, 0, 400, NULL);
			LineTo(hdc, 800,
				400);
			ReleaseDC(HWND(t), hdc);
		}
		thread2_working = false;
		Sleep(500);
	}
	return 0;
}



DWORD WINAPI Thread2(LPVOID t) {
	//COLLECTING THREAD
	while (thread1_working) {
		for (ActualGraph = 0; ActualGraph < AmoutOfGraphs; ActualGraph++) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 10; j++) {
					GetWindowText(Graphs[ActualGraph].TableHWnd[i][j], (LPWSTR)buff, 10);
					double a;
					a = deshifr();
					Graphs[ActualGraph].TableData[i][j] = deshifr();
					a = Graphs[ActualGraph].TableData[i][j];
				}
			}
			Graphs[ActualGraph].Sort();
		}
		Sleep(500);
	}
	return 0;
}




POINT Cursor;
bool fDraw = true;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*RECT rect;
	rect.bottom = 40;
	rect.top = 0;
	rect.left = WINDOWX - 200 - 100 * AmoutOfGraphs;
	rect.right = WINDOWX - 100 - 100 * AmoutOfGraphs;*/
	switch (uMsg) {

	case WM_PAINT:
	{
		/*PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		SetBkMode(hdc, TRANSPARENT);
		DrawText(hdc, L"Graph #", 10, &rect, NULL);
		EndPaint(hWnd, &ps);*/
	}

	return 0;

	case WM_MOUSELEAVE:
	{
		/*	if (1)
		{
				RECT rect;
				rect.bottom = 415;
				rect.top = 0;
				rect.right = 415;
				rect.left = 0;
			PAINTSTRUCT ps;
			HDC hdc = GetDC(hWnd);
			BeginPaint(hWnd, &ps);
			GetCursorPos(&Cursor);
			MoveToEx(hdc, Cursor.x, 0, NULL);
			LineTo(hdc, Cursor.x,
				415);
			MoveToEx(hdc, 0, Cursor.y, NULL);
			LineTo(hdc, 415,
				Cursor.y);
			ReleaseDC(hWnd, hdc);
			EndPaint(hWnd, &ps);
			InvalidateRect(hWnd, &rect, true);*/
	}
	case WM_CTLCOLORSTATIC:
	{
		if ((HWND)lParam == GetDlgItem(hWnd, 133))
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, Graphs[0].Color);
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}
		if ((HWND)lParam == GetDlgItem(hWnd, 266))
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, Graphs[1].Color);
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}
		if ((HWND)lParam == GetDlgItem(hWnd, 399))
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, Graphs[2].Color);
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}
		if ((HWND)lParam == GetDlgItem(hWnd, 133*4))
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, Graphs[3].Color);
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}
		if ((HWND)lParam == GetDlgItem(hWnd, 133*5))
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, Graphs[4].Color);
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}
		if ((HWND)lParam == GetDlgItem(hWnd, 133*6))
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, Graphs[5].Color);
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}
		if ((HWND)lParam == GetDlgItem(hWnd, 133*7))
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, Graphs[6].Color);
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}
		if ((HWND)lParam == GetDlgItem(hWnd, 133*8))
		{
			SetBkMode((HDC)wParam, TRANSPARENT);
			SetTextColor((HDC)wParam, Graphs[7].Color);
			return (BOOL)GetSysColorBrush(COLOR_MENU);
		}

	}
	return 0;
	case WM_COMMAND:
	{
		/*case 100:
		{
			thread1_working = true;
			hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
			break;

		}
		case 200:
		{
			thread2_working = true;
			hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);

			break;
		}
		case 300:
		{

			TerminateThread(hThread1, 0);
			thread1_working = false;
			break;
		}
		case 400:
		{
			TerminateThread(hThread2, 0);
			thread2_working = false;
			break;

		}*/
		if (LOWORD(wParam) == 120) {
			/*for (int i = 0; i < 2; i++) {
				for (int j = 0; j < ActualRow; j++) {
					GetWindowText(TableHWnd[i][j], (LPWSTR)buff, 10);
					double a;
					a = deshifr();
					TableData[i][j] = deshifr();
					a = TableData[i][j];
				}
			}*/
		}
		 if (LOWORD(wParam) == 2) {
			/*HDC hdc = GetDC(hWnd);
			MoveToEx(hdc, 1000, 1000, NULL);
			LineTo(hdc, 100, 100);
			ReleaseDC(hWnd, hdc);*/
		}
		 if (LOWORD(wParam) == NEW_GRAPH) {
			 if (AmoutOfGraphs < 7) {
				 AmoutOfGraphs++;
				 Graphs.push_back(Graph(hWnd));
				 LPWSTR portvalue = new TCHAR[100];
				 TCHAR TTTEXT[10] = { 'G','R','A','P','H','№',char('0' + AmoutOfGraphs) };
				 std::string LabelText = "Graph№" + AmoutOfGraphs;
				 HWND NewLabel = CreateWindow(L"STATIC", TTTEXT, WS_CHILD | WS_VISIBLE, WINDOWX - 200 - 100 * (AmoutOfGraphs - 1), 0, 100, 40, hWnd, (HMENU)(AmoutOfGraphs * 133), NULL, NULL);
				 HFONT font = CreateFont(-17, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"Times new Roman");
				 SendMessage(NewLabel, WM_SETFONT, (WPARAM)font, MAKELPARAM(true, 0));

				 UpdateWindow(hWnd);
			 }
		 }
		 if (LOWORD(wParam) == DELETEDRAW) {
			 TerminateThread(hThread1, 0);
			 thread1_working = false;

		 }
		 if (LOWORD(wParam) == DELETECOLLECTOR) {
			 TerminateThread(hThread2, 0);
			 thread2_working = false;
		 }
		 if (LOWORD(wParam) == CREATECOLLECTOR) {
			 thread2_working = true;
			 hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);
		 }
		 if (LOWORD(wParam) == CREATEDRAW) {
			 thread1_working = true;
			 hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
		 }

	}
	return 0;
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
	
		RECT Window;
		GetClientRect(hWnd, &Window);
		

		//HWND UpdateButton = CreateWindow(L"BUTTON", L"Update", WS_CHILD | WS_VISIBLE, Window.right - 100, 0, 100, 20, hWnd, (HMENU)120, NULL, NULL);
		HWND NewGraphButton = CreateWindow(L"BUTTON", L"Добавить", WS_CHILD | WS_VISIBLE, Window.right - 100, 0, 100, 20, hWnd, (HMENU)NEW_GRAPH, NULL, NULL);
		HWND CreateDButton = CreateWindow(L"BUTTON", L"Рисовать", WS_CHILD | WS_VISIBLE, Window.right - 100, 550, 100, 20, hWnd, (HMENU)CREATEDRAW, NULL, NULL);
		HWND CreateCButton = CreateWindow(L"BUTTON", L"Занести", WS_CHILD | WS_VISIBLE, Window.right - 100, 570, 100, 20, hWnd, (HMENU)CREATECOLLECTOR, NULL, NULL);
		HWND DeleteDButton = CreateWindow(L"BUTTON", L"Стоп", WS_CHILD | WS_VISIBLE, Window.right - 100, 590, 100, 20, hWnd, (HMENU)DELETEDRAW, NULL, NULL);
		HWND DeleteCButton = CreateWindow(L"BUTTON", L"Не заносить", WS_CHILD | WS_VISIBLE, Window.right - 100, 610, 100, 20, hWnd, (HMENU)DELETECOLLECTOR, NULL, NULL);
	//	HWND GraphButton = CreateWindow(L"BUTTON", L"Graph", WS_CHILD | WS_VISIBLE, Window.right - 200, 0, 100, 20, hWnd, (HMENU)2, NULL, NULL);
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
	HBRUSH turquoise = CreateSolidBrush(GetSysColor(CTLCOLOR_DLG));
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
	LoadLibrary(TEXT("Msftedit.dll"));
	if (!RegisterClassEx(&wc)) {
		return EXIT_FAILURE;
	}
	hwnd = CreateWindow(wc.lpszClassName, L"Lab_1", WS_OVERLAPPEDWINDOW, 0, 0, 1600, 900, NULL, NULL, wc.hInstance, NULL);
	if (hwnd == INVALID_HANDLE_VALUE)
	{
		return EXIT_FAILURE;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0)) {
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}

