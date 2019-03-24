#include "pch.h"
#include <iostream>
#include <Windows.h>

using namespace std;


//设置屏幕大小
int nScreenWidth = 120;
int nScreenHeight = 40;

//设置人物坐标和视角角度
float fPlayerX = 0.0f;
float fPlayerY = 0.0f;
float fPlayerA = 0.0f;

float fFov = 3.1415926 / 4.0;

//设置地图长和宽
int nMapWidth = 16;
int nMapHeight = 16;




int main()
{
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ|GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwByteWriten = 0;

	wstring map;
	map += L"################";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"################";

	while (1) {
		//根据宽比例计算角度，再从角度判断与墙的距离
		for (int i = 0 ; i<nScreenWidth ; i++) {
			float fPlayerAngle = (fPlayerA - fFov / 2) + ((float)i / (float)nScreenWidth)*fFov;

			float fDistanceToWall = 0.0f;
			bool hitWall = false;

			while (!hitWall) {
				fDistanceToWall += 0.1f;
			}
			 
		}

		screen[nScreenWidth*nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth*nScreenHeight, { 0,0 }, &dwByteWriten);
	}
	
	return 0;

}

