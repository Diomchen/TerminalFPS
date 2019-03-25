#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <chrono>

using namespace std;


//设置屏幕大小
int nScreenWidth = 120;
int nScreenHeight = 40;

//设置人物坐标和视角角度
float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;

float fFov = 3.1415926 / 4.0;

//设置地图长和宽
int nMapWidth = 16;
int nMapHeight = 16;

float nDepth = 16.0f;




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
	map += L"#.....##.......#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#.......#####..#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"################";

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	while (1) {
		//利用时间减缓速度
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();


		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
			fPlayerA -= 0.8f*fElapsedTime;

		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
			fPlayerA += 0.8f*fElapsedTime;

		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
			fPlayerX += sinf(fPlayerA)*5.0f*fElapsedTime;
			fPlayerY += cosf(fPlayerA)*5.0f*fElapsedTime;
		}


		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
			fPlayerX -= sinf(fPlayerA)*5.0f*fElapsedTime;
			fPlayerY -= cosf(fPlayerA)*5.0f*fElapsedTime;
		}
		//根据宽比例计算角度，再从角度判断与墙的距离
		for (int i = 0 ; i<nScreenWidth ; i++) {
			float fPlayerAngle = (fPlayerA - fFov / 2.0) + ((float)i / (float)nScreenWidth)*fFov;

			float fDistanceToWall = 0.0f;
			bool hitWall = false;

			float fEyeX = sinf(fPlayerAngle);
			float fEyeY = cosf(fPlayerAngle);


			while (!hitWall && fDistanceToWall<nDepth) {
				fDistanceToWall += 0.1f; 
				
				int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
				int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

				if ((nTestX<0 || nTestX >= nMapWidth) || ( nTestY<0 || nTestY>= nMapHeight)) {
					hitWall = true;
					fDistanceToWall = nDepth;
				}
				else {
					if (map[nMapWidth*nTestY + nTestX] == '#') {
						hitWall = true;
					}
				}
			}

			//这里并没有什么可依据的，仅仅只是比列计算罢了
			int nCelling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
			int nFloor = nScreenHeight - nCelling;

			short nShade = ' ';
			short nShade0 = ' ';
			
			if (fDistanceToWall <= nDepth / 4.0f)
				nShade = 0x2588;
			else if (fDistanceToWall < nDepth / 3.0f)
				nShade = 0x2593;
			else if (fDistanceToWall < nDepth / 2.0f)
				nShade = 0x2592;
			else if (fDistanceToWall < nDepth)
				nShade = 0x2591;
			else
				nShade = ' ';


			for (int j = 0; j<nScreenHeight ; j++) {
				if (j < nCelling) {
					screen[j*nScreenWidth + i] = ' ';
				}
				else if (j>nCelling && j<= nFloor) {
					screen[j*nScreenWidth + i] = nShade;
				}
				else {
					float b = 1.0f - (((float)j - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
					if (b < 0.25)		nShade0 = '#';
					else if (b < 0.5)	nShade0 = 'x';
					else if (b < 0.75)	nShade0 = '.';
					else if (b < 0.9)	nShade0 = '-';
					else				nShade0 = ' ';
					screen[j*nScreenWidth + i] = nShade0;
				}

			}
			 
		}

		screen[nScreenWidth*nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth*nScreenHeight, { 0,0 }, &dwByteWriten);
	}
	
	return 0;

}

