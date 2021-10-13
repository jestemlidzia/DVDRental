// Project_Lidia_Wisniewska.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
#include "functions.h"
#include <cwchar>
#include <windows.h>
#include <iomanip>

CONSOLE_FONT_INFOEX cfi;


int main()
{
	//ustawienia graficzne
	system("color F0");
	setlocale(LC_ALL,
		"pl_PL"); setlocale(LC_ALL, "polish");

	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DECORATIVE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);


	init();
}


