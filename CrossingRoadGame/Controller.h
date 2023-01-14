#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <conio.h>
#include <Random>
#include <iostream>
#pragma comment(lib, "Winmm.lib")

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

#define UpKey 72
#define LeftKey 75
#define RightKey 77
#define DownKey 80
#define EnterKey 13
#define ESCKey 27

#define ESC 1
#define UP 2
#define LEFT 3
#define RIGHT 4
#define DOWN 5
#define ENTER 6
#define HELP 7
#define PAUSE 8
#define SAVE 9
#define LOAD 10
#define FIND_FILENAME 11
#define CANCEL 12

#define BACKGROUND_COLOR 15

using namespace std;

class Controller
{
	static HWND consoleWindow;    //Con trỏ xử lí cửa sổ console
	static HANDLE consoleOutput;  //Con trỏ xử lí output console
public:
	static void setUpConsole();									//Thiết lập cửa sổ console
	static void gotoXY(int, int);								//Di chuyển con trỏ đến vị trí x,y
	static void setAndCenterWindow();							//Căn giữa và thiết lập độ phân giải màn hình console
	static void setConsoleColor(int background, int text);		//Thiết lập màu chữ và và màu nền
	static void hideScrollBars();								//Ẩn thanh cuộn
	static void setConsoleTitle();								//Cài đặt tiêu đề console
	static void disableMaximize();								//Vô hiệu hóa phóng to màn hình
	static void showCursor(bool);								//Ẩn hoặc hiện con trỏ
	static void setFontInfo(int, int);							//Cài đặt font chữ
	static void clearConsole();									//Xóa màn hình console
	static void disableMouseInput();							//Vô hiệu hóa chuột trong console
	static int getConsoleInput();								//Lấy lệnh từ bàn phím
	static void FixConsoleWindow();
};