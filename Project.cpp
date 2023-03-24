#include <windows.h>
#include "Header.h"
#include "resource.h"
#include <string>

using namespace std;

int linenum(string str);
string select(string text, short int start, short int end);
string symbol_error(string symbol);
string encrypt(string word);
string decrypt(string word);
string check(string text, string select);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInt, LPSTR args, int ncmdshow) {
	WNDCLASS Software = Window((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_HAND), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)), 
	L"MainClass", ProcedureMain);
	if (!RegisterClassW(&Software)) { return -1; }
	MSG SoftwareMessage{ 0 };
	CreateWindow(L"MainClass", L"KGB", WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX, 500, 500, 500, 250, NULL, NULL, NULL, NULL);
	while (GetMessage(&SoftwareMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMessage);
		DispatchMessage(&SoftwareMessage);
	}
}
WNDCLASS Window(HBRUSH Color, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {
	WNDCLASS NWM = { 0 };
	NWM.hCursor = Cursor;
	NWM.hIcon = Icon;
	NWM.hInstance = hInst;
	NWM.lpszClassName = Name;
	NWM.hbrBackground = Color;
	NWM.lpfnWndProc = Procedure;
	return NWM;
}
LRESULT CALLBACK ProcedureMain(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	string Answer = "                                                                                                                   ";
	string end;
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case OnReadField:
			GetWindowTextA(hEditControl, Buffer, TextBuffer);
			break;
		case OnEncryptClicked:
			GetWindowTextA(hEditControl, const_cast<char*>(Answer.c_str()), GetWindowTextLength(hEditControl) + 1);
			Answer = check(Answer, "encrypt");
			SetWindowTextA(hEditControl, Answer.c_str());
			break;
		case OnDecryptClicked:
			GetWindowTextA(hEditControl, const_cast<char*>(Answer.c_str()), GetWindowTextLength(hEditControl) + 1);
			Answer = check(Answer, "decrypt");
			SetWindowTextA(hEditControl, Answer.c_str());
			break;
		case OnExit:
			PostQuitMessage(0);
			break;
		case OnClearField:
			SetWindowTextA(hEditControl, "");
			break;
		default:
			break;
		}
		break;
	case WM_CREATE:
		AddMenu(hWnd);
		AddWidget(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
void AddMenu(HWND hWnd) {
	HMENU RootMenu = CreateMenu();
	HMENU FileMenu = CreateMenu();

	AppendMenu(FileMenu, MF_STRING, OnClearField, L"Clear");
	AppendMenu(FileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(FileMenu, MF_STRING, OnEncryptClicked, L"Encrypt");
	AppendMenu(FileMenu, MF_STRING, OnDecryptClicked, L"Decrypt");
	AppendMenu(FileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(FileMenu, MF_STRING, OnExit, L"Exit");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)FileMenu, L"Menu");
	SetMenu(hWnd, RootMenu);
}
void AddWidget(HWND hWnd) {
	hEditControl = CreateWindowA("edit", "Enter message...", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 5, 40, 470, 60, hWnd, NULL, NULL, NULL);
	hStatic = CreateWindowA("static", "1. Do not use special characters.\n2. Enter everything in lower case.\n3. Use _ instead of a space.", WS_VISIBLE | WS_CHILD, 5, 100, 470, 60, hWnd, NULL, NULL, NULL);
	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 120, 30, hWnd, (HMENU)OnClearField, NULL, NULL);
	CreateWindowA("button", "Encrypt", WS_VISIBLE | WS_CHILD | ES_CENTER, 130, 5, 65, 30, hWnd, (HMENU)OnEncryptClicked, NULL, NULL);
	CreateWindowA("button", "Decrypt", WS_VISIBLE | WS_CHILD | ES_CENTER, 200, 5, 65, 30, hWnd, (HMENU)OnDecryptClicked, NULL, NULL);
	CreateWindowA("button", "Exit", WS_VISIBLE | WS_CHILD | ES_CENTER, 270, 5, 65, 30, hWnd, (HMENU)OnExit, NULL, NULL);
}
int linenum(string str) {
	return str.length() - 1;
}
string select(string text, short int start, short int end) {
	string itog = "";
	for (short int ip = start; ip < end; ip++) {
		itog = itog + text[ip];
	}
	return itog;
}
string symbol_error(string symbol) {
	return "Error: symbol" + symbol + " not allowed to user for encrypting message.";
}
string encrypt(string word) {
	string words[62] = {"крч_рсч", "ств_тсв", "луч_чул", "вст_твс", "ово_ит", "ево_но", "на_мс", "пр_рп", "се_ла", "ре_ом",
						"ка_ак", "ти_тит", "по_оп", "ме_ем", "ст_тс", "во_ов", "ро_ор", "ше_еш", "ня_ян", "то_от", "ра_ар",
						"ко_ок", "та_ат", "ма_ам", "го_ог", "ри_ир", "са_ас", "ни_ин", "ве_ев", "а_дя", "б_ха", "в_ып",
						"г_зо",
						"д_ми", "е_эф", "ё_ъ", "ж_ху", "з_от", "и_ва", "й_бт", "к_лм", "л_шо", "м_су", "н_ур", "о_из",
						"п_бр",
						"р_ды", "с_фе", "т_оа", "у_пу", "ф_ру", "х_цу", "ц_жа", "ч_рю", "ш_се", "щ_ь", "ъ_по", "ы_пе",
						"ь_пыр",
						"э_пи", "ю_ге", "я_га"};
	string words2[54] = {"ам_opy", "да_9gk", "ро_xxx", "ва_z", "ан_rf", "кн_ugh", "ма_bod", "ен_xc", "рс_ghs", "жи_org",
						 "ак_ejf", "ут_qah", "кк_giu", "ес_br", "от_kf", "ят_ga", "ум_za", "ол_olt", "аю_bbk",
						 "иг_shai",
						 "стр_x32", "а_lt", "б_io", "в_rgt", "г_meo", "д_84n", "е_0vik", "ё_hl3", "ж_mf5", "з_ln8",
						 "и_tp3",
						 "й_tvx", "к_kol", "л_poi", "м_nat", "н_vah", "о_nyh", "п_mza", "р_ole", "с_lb", "т_blm",
						 "у_fny",
						 "ф_qs", "х_ui", "ц_pfz", "ч_oji", "ш_ouf", "щ_vfi", "ъ_pbg", "ы_zpr", "ь_gp", "э_qse", "ю_skf",
						 "я_por"};
	for (short int i = 0; i < 62; i++) {
		string temp = words[i];
		short int find = temp.find("_");
		string temp_f = select(temp, 0, find);
		if (word.find(temp_f) != -1) {
			short int end = linenum(temp);
			string temp_fr = select(temp, find + 1, end + 1);
			word = word.replace(word.find(temp_f), temp_f.length(), temp_fr);
		}
	}
	for (short int i2 = 0; i2 < 54; i2++) {
		string temp2 = words2[i2];
		short int find2 = temp2.find("_");
		string temp_f2 = select(temp2, 0, find2);
		if (word.find(temp_f2) != -1) {
			short int end2 = linenum(temp2);
			string temp_fr2 = select(temp2, find2 + 1, end2 + 1);
			word = word.replace(word.find(temp_f2), temp_f2.length(), temp_fr2);
		}
	}
	return word;
}
string decrypt(string word) {
	string words_decrypt[62] = { "я_га", "ю_ге", "э_пи", "ь_пыр", "ы_пе", "ъ_по", "щ_ь", "ш_се", "ч_рю", "ц_жа", "х_цу", "ф_ру", "у_пу", "т_оа", "с_фе", "р_ды", "п_бр", "о_из", "н_ур", "м_су", "л_шо", "к_лм", "й_бт", "и_ва",
	"з_от", "ж_ху", "ё_ъ", "е_эф", "д_ми", "г_зо", "в_ып", "б_ха", "а_дя", "ве_ев", "ни_ин",
	"са_ас", "ри_ир", "го_ог", "ма_ам", "та_ат", "ко_ок", "ра_ар", "то_от", "ня_ян", "ше_еш",
	"ро_ор", "во_ов", "ст_тс", "ме_ем", "по_оп", "ти_тит", "ка_ак", "ре_ом", "се_ла", "пр_рп",
	"на_мс", "ево_но", "ово_ит", "вст_твс", "луч_чул", "ств_тсв", "крч_рсч" };
	string words_decrypt2[54] = { "я_por", "ю_skf", "э_qse", "ь_gp", "ы_zpr", "ъ_pbg", "щ_vfi", "ш_ouf", "ч_oji", "ц_pfz",
	"х_ui", "ф_qs", "у_fny", "т_blm", "с_lb", "р_ole", "п_mza", "о_nyh", "н_vah", "м_nat",
	"л_poi", "к_kol", "й_tvx", "и_tp3", "з_ln8", "ж_mf5", "ё_hl3", "е_0vik", "д_84n", "г_meo",
	"в_rgt", "б_io", "а_lt", "стр_x32", "иг_shai", "аю_bbk", "ол_olt", "ум_za", "ят_ga",
	"от_kf", "ес_br", "кк_giu", "ут_qah", "ак_ejf", "жи_org", "рс_ghs", "ен_xc", "ма_bod",
	"кн_ugh", "ан_rf", "ва_z", "ро_xxx", "да_9gk", "ам_opy" };
	for (short int d2 = 0; d2 < 54; d2++) {
		string temp2 = words_decrypt2[d2];
		short int find2 = temp2.find("_");
		short int end2 = linenum(temp2);
		string temp_f2 = select(temp2, find2 + 1, end2 + 1);
		if (word.find(temp_f2) != -1) {
			string temp_fr2 = select(temp2, 0, find2);
			word = word.replace(word.find(temp_f2), temp_f2.length(), temp_fr2);
		}
	}
	for (short int d = 0; d < 62; d++) {
		string temp = words_decrypt[d];
		short int find = temp.find("_");
		short int end = linenum(temp);
		string temp_f = select(temp, find + 1, end + 1);
		if (word.find(temp_f) != -1) {
			string temp_fr = select(temp, 0, find);
			word = word.replace(word.find(temp_f), temp_f.length(), temp_fr);
		}
	}
	return word;
}
string check(string text, string select) {
	if (text.find("!") != -1) {
		return symbol_error("!");
	}
	else if (text.find("?") != -1) {
		return symbol_error("?");
	}
	else if (text.find(".") != -1) {
		return symbol_error(".");
	}
	else if (text.find("/") != -1) {
		return symbol_error("/");
	}
	else if (text.find(",") != -1) {
		return symbol_error(",");
	}
	else if (text.find("$") != -1) {
		return symbol_error("$");
	}
	else if (text.find("*") != -1) {
		return symbol_error("*");
	}
	else if (text.find("#") != -1) {
		return symbol_error("#");
	}
	else if (text.find("%") != -1) {
		return symbol_error("%");
	}
	else if (text.find("@") != -1) {
		return symbol_error("@");
	}
	else if (text.find("№") != -1) {
		return symbol_error("№");
	}
	else {
		if (select == "encrypt") {
			return "Final decrypted word: " + encrypt(text);
		}
		else if (select == "decrypt") {
			return "Final encrypted word: " + decrypt(text);
		}
		else {
			return "Select " + select + " not found.";
		}
	}
}
	