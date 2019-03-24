#include "pch.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int nScreenWidth = 120;
int nScreenHeight = 40;


int main()
{
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwByteWriten = 0;
	return 0;

}

