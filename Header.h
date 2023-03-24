#pragma once
#define OnEncryptClicked 1
#define OnDecryptClicked 2
#define OnExit 4
#define OnClearField 5
#define OnReadField 6
#define TextBuffer 1024
#include <string>

char Buffer[TextBuffer];
HWND hEditControl;
HWND hStatic;
HWND hWnd;
HFONT font;

LRESULT CALLBACK ProcedureMain(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS Window(HBRUSH Color, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void AddMenu(HWND hWnd);
void AddWidget(HWND hWnd);

