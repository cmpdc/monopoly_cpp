#include <algorithm>
#include <string>
#include <vector>
#include <windows.h>
#include "Utils.h"

using namespace std;

string Utils::str_UpperCase(string stringToConvert) {
	transform(stringToConvert.begin(), stringToConvert.end(), stringToConvert.begin(), ::toupper);
	return stringToConvert;
}

void Utils::pauseScreen() {system("pause");}

void Utils::changeWindowSize(int width, int height) {
	HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD sizeOfBuff;
	sizeOfBuff.X = width;
	sizeOfBuff.Y = height;
	SetConsoleScreenBufferSize(buff, sizeOfBuff);

	RECT r;
	HWND console = GetConsoleWindow(); // find the Console Window
	GetWindowRect(console, &r); // get the size of screen to the variable desktop
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void Utils::clearScreen() {system("cls");}