#include <stdio.h>
#include <conio.h>
#include "console.h"
#include <iostream>
using namespace std;

int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return key_none;
	}

	return key_none;
}


//-------------------------Screen-------------------------
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}


//screen: goto [x,y]
void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//screen: get [x]
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}


//screen: get [y]
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}


void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void loading(int x, int y)
{
	TextColor(10);
	VeKhungCH(x - 18, y - 1, 57, 2, true);
	int i, c, d;
	char a = 177, b = 219;
	gotoXY(x + 8, y);
	cout << "LOADING";
	gotoXY(x + 1, y);
	for (i = 0; i < 55; i++) {
		c = rand() % 40;
		Sleep(c);
		cout << "\r\r";
		cout << "\t\t\t\t";
	}
	for (i = 0; i < 56; i++) {
		cout << b;
		d = rand() % 20;
		Sleep(d);
	}
	system("cls");
}

void VeKhungCH(int x, int y, int width, int height, bool draw) {
	//vẽ khung chữ nhật
	if (draw) {
		//vẽ trước 4 góc
		//góc trên bên trái
		gotoXY(x, y);
		cout << char(218);
		//vẽ góc trên bên phải
		gotoXY(x + width, y);
		cout << char(191);
		//vẽ góc dưới bên trái
		gotoXY(x, y + height);
		cout << char(192);
		//vẽ góc dưới bên phải
		gotoXY(x + width, y + height);
		cout << char(217);

		//vẽ chiều ngang bên trên
		for (int i = x + 1; i < (x + width); i++) {
			gotoXY(i, y);
			cout << char(196);
		}
		//vẽ chiều ngang bên dưới
		for (int i = x + 1; i < (x + width); i++) {
			gotoXY(i, y + height);
			cout << char(196);
		}
		//vẽ chiều dọc bên trái
		for (int i = y + 1; i < (y + height); i++) {
			gotoXY(x, i);
			cout << char(179);
		}
		//vẽ chiều dọc bên phải
		for (int i = y + 1; i < (y + height); i++) {
			gotoXY(x + width, i);
			cout << char(179);
		}
	}
	else {
		//vẽ trước 4 góc
		//góc trên bên trái
		gotoXY(x, y);
		cout << " ";
		//vẽ góc trên bên phải
		gotoXY(x + width, y);
		cout << " ";
		//vẽ góc dưới bên trái
		gotoXY(x, y + height);
		cout << " ";
		//vẽ góc dưới bên phải
		gotoXY(x + width, y + height);
		cout << " ";

		//vẽ chiều ngang bên trên
		for (int i = x + 1; i < (x + width); i++) {
			gotoXY(i, y);
			cout << " ";
		}
		//vẽ chiều ngang bên dưới
		for (int i = x + 1; i < (x + width); i++) {
			gotoXY(i, y + height);
			cout << " ";
		}
		//vẽ chiều dọc bên trái
		for (int i = y + 1; i < (y + height); i++) {
			gotoXY(x, i);
			cout << " ";
		}
		//vẽ chiều dọc bên phải
		for (int i = y + 1; i < (y + height); i++) {
			gotoXY(x + width, i);
			cout << " ";
		}

	}
}