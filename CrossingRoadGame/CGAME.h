#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Graphics.h"
#include "CROAD.h"
#include "Level.h"
#include "LANE.h"
#include "CPEOPLE.h"
#include "Menu.h"
#include <fstream>
#include <direct.h>

class CGAME {
	bool IS_RUNNING;
	bool IS_PAUSING;
	bool loadGameMode;

	int level;
	Level *Lvl;
	CROAD *road;
	vector <LANE*> lanes;

	string playerName = "";

	const int xToPopUp = RIGHT_BOUND + 5;
	const int yToPopUp = UPPER_BOUND + 14;
	
public:
	CGAME();
	~CGAME();
	void levelUp();
	void laneFlow(vector <thread>& tLane, const vector <int>& Lane);

	void setupLevelData();
	void clearData();
	void saveData(string fileName);
	void loadData(string fileName);
		
	void setupGame();
	void startGame();
	void processingGame();
	void pauseGame();
	void saveGame();
	void loadGame();
	void loseGame();
	void winGame();
	void popUpInstructions();
};