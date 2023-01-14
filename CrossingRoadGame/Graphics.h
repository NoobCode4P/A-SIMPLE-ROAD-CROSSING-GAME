#pragma once
#include "Controller.h"
#include <ctime>
#include "Sound.h"

#define LEFT_BOUND 1
#define RIGHT_BOUND 75
#define UPPER_BOUND 3
extern int LOWER_BOUND;

class Graphics {
public:
	static void switchDirection(char **movingObject, int height, int length);
	static void drawBorder(int upperleftX, int upperleftY, int width, int Hpercell, int soluong);
	static void drawRoadWithFixedLaneWidth(int upperleftX, int upperleftY, int length, int lane, int laneWidth);
	static void drawRoadWithMultipleLaneWidths(int upperleftX, int upperleftY, int length, vector <int> laneWidth, vector <string>& line);
	static void drawUtilityBoard(int upperleftX, int upperleftY, int height, int length);
	static void drawKeyboardMove(int x, int y, int Hpercell, int Wpercell, char up, char down, char right, char left);
	static void drawReturnButton(int upperLeftX, int upperLeftY, string msg = "BACK", int textcolor = GREEN);
	static void drawBackgroundTitle();

	static void printValidPartOfObj(int x, int y, char** obj, int height, int length);
	static void removeObjAt(int x, int y, int height, int length);
	static void removePerson(const vector <string> &line, const vector <int> &laneWidth, int x, int y, int xPrint, int yPrint);

	static void printCurLevel(int upperLeftX, int upperLeftY, int level);
	static void drawPopUpBorder(int upperLeftX, int upperLeftY, int height, int width);
	static void closePopUp(int upperLeftX, int upperLeftY, int height, int width);
	static void popupHelpBoard(int upperLeftX, int upperLeftY);
	static void popupPause(int upperLeftX, int upperLefY);
	static void popupSaveGame(int upperLeftX, int upperLeftY, string &saveName);

	static int popup2Choices(int upperLeftX, int upperLeftY, int height, int width, string message, string choice1 = "YES", string choice2 = "NO");

	static void printListOfSavedFiles(int upperLeftX, int upperLeftY, const vector <string>& list, int top, int bottom, string& selectedFile);

	static void loseGameAnimation();
	static void farewellScreen();
};
