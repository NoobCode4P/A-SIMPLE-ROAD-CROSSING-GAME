#pragma once
#include "Controller.h"
#include "Graphics.h"
#include "CGAME.h"

class Menu {
	const vector <string> optionList = { "NEW GAME", "LOAD GAME", "HOW TO PLAY", "LEADERBOARD", "SETTINGS", "EXIT" };
public:
	void mainMenu();
	void newGame();
	void loadGame();
	void tutorialPage();
	void leaderboard();
	void menuSetting();
	void exitGame();
	int setupMainOption();
};
