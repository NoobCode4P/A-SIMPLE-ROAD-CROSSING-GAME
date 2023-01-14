#include "menu.h"

void Menu::mainMenu() {
	system("cls");
	Graphics::drawBackgroundTitle();
	int choice = setupMainOption();
	
	switch (choice) {
	case 0: {
		newGame();
		break;
	}
	case 1: {
		loadGame();
		break;
	}
	case 2: {
		tutorialPage();
		break;
	}
	case 3: {
		leaderboard();
		break;
	}
	case 4: {
		menuSetting();
		break;
	}
	case 5: {
		exitGame();
		break;
	}
	}
}

void Menu::newGame() {
	CGAME game;
	game.startGame();
}

void Menu::loadGame() {
	CGAME game;
	game.loadGame();
}

void Menu::tutorialPage() {
	system("cls");
	Graphics::drawReturnButton(1,0);

	int xText = 9;

	int yStartIntro = 3;

	Controller::setConsoleColor(BACKGROUND_COLOR, PURPLE);
	Graphics::drawPopUpBorder(xText - 2, yStartIntro, 10, 102);

	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_RED);
	Controller::gotoXY(53, yStartIntro);
	cout << "INTRODUCTION";

	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	Controller::gotoXY(xText + 33, yStartIntro + 1);
	cout << "WELCOME TO OUR \"CROSSING THE ROAD\"!";
	Controller::gotoXY(xText, yStartIntro + 2);
	cout << "AS THE NAME IMPLIES, THIS 2D GAME CHALLENGES YOU TO CROSS THE ROAD WITH MOVING OBSTACLES WHICH ARE";
	Controller::gotoXY(xText, yStartIntro + 3);
	cout << "DIVIDED INTO 2 CATEGORIES (VEHICLE AND ANIMAL). IN EACH ROAD, LANE OF THE FORMER HAS TRAFFIC LIGHT,";
	Controller::gotoXY(xText, yStartIntro + 4);
	cout << "WHICH MEANS YOU MAY PASS EASILY WHEN RED LIGHT IS ON. HOWEVER, ANIMALS' LANE DOES NOT HAVE ONE.";
	Controller::gotoXY(xText, yStartIntro + 6);
	cout << "BEING IMPACTED BY ANY OBSTACLES, YOU WILL LOSE.";
	Controller::gotoXY(xText, yStartIntro + 8);
	cout << "PASSING SUCCESSFULLY WILL GIVE YOU A LEVEL-UP. AND COMPLETE 5 LEVELS TO WIN.";

	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_RED);
	Controller::gotoXY(xText - 3, yStartIntro + 10);
	cout << "KEYBOARD CONTROLS";

	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	Controller::gotoXY(32, yStartIntro + 11);
	cout << "MOVE KEYS";

	Controller::gotoXY(35, yStartIntro + 15);
	cout << "OR";

	Graphics::drawKeyboardMove(14, yStartIntro + 13, 2, 4, 'W', 'S', 'A', 'D');

	Graphics::drawKeyboardMove(44, yStartIntro + 13, 2, 4, '^', 'v', '<', '>');

	//=======VERTICAL BAR=========
	Controller::setConsoleColor(BACKGROUND_COLOR, AQUA);
	for (int i = yStartIntro + 11; i < yStartIntro + 22; i++) {
		Controller::gotoXY(62, i);
		putchar(219);
	}
	//============================

	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	Controller::gotoXY(75, yStartIntro + 11);
	cout << "FUNCTION KEYS";

	int x = 67;
	int y = yStartIntro + 13;
	Graphics::drawBorder(x, y, 4, 2, 1);
	Controller::gotoXY(x + 2, y + 1);
	cout << "P";
	Controller::gotoXY(x + 6, y + 1);
	cout << "PAUSE GAME";

	x += 18;
	Graphics::drawBorder(x, y, 4, 2, 1);
	Controller::gotoXY(x + 2, y + 1);
	cout << "H";
	Controller::gotoXY(x + 6, y + 1);
	cout << "HELP";

	x -= 18;
	y += 3;
	Graphics::drawBorder(x, y, 4, 2, 1);
	Controller::gotoXY(x + 1, y + 1);
	cout << "ESC";
	Controller::gotoXY(x + 6, y + 1);
	cout << "QUIT GAME";

	x += 18;
	Graphics::drawBorder(x, y, 4, 2, 1);
	Controller::gotoXY(x + 2, y + 1);
	cout << "G";
	Controller::gotoXY(x + 6, y + 1);
	cout << "SAVE GAME";

	x -= 18;
	y += 3;
	Graphics::drawBorder(x, y, 4, 2, 1);
	Controller::gotoXY(x + 2, y + 1);
	cout << "L";
	Controller::gotoXY(x + 6, y + 1);
	cout << "LOAD GAME";

	Controller::setConsoleColor(BACKGROUND_COLOR, BLUE);
	Controller::gotoXY(xText + 7, yStartIntro + 23);
	cout << "\"Keep in mind that moving your character to an empty space does not guarantee";
	Controller::gotoXY(xText, yStartIntro + 25);
	cout << "                           an escape from collision with obstacles\"";

	int choice;
	do {
		choice = Controller::getConsoleInput();
	} while (choice != LEFT && choice != ESC);

	mainMenu();
}

void Menu::leaderboard() {
	system("cls");
	typedef pair <string, int> psi;
	ifstream in("listOfSavedFiles.txt");
	string pathFile;
	vector <psi> list;

	while (getline(in, pathFile)) {
		ifstream gather(pathFile);

		string name;
		int level;
		getline(gather, name);
		gather >> level;

		list.push_back(make_pair(name, level));

		gather.close();
	}
	
	in.close();
	
	Graphics::drawReturnButton(1, 0);

	vector <string> title(5);
	title[0] = R"(    __    _________    ____  __________  ____  ____  ___    ____  ____ )";
	title[1] = R"(   / /   / ____/   |  / __ \/ ____/ __ \/ __ )/ __ \/   |  / __ \/ __ \)";
	title[2] = R"(  / /   / __/ / /| | / / / / __/ / /_/ / __  / / / / /| | / /_/ / / / /)";
	title[3] = R"( / /___/ /___/ ___ |/ /_/ / /___/ _, _/ /_/ / /_/ / ___ |/ _, _/ /_/ / )";
	title[4] = R"(/_____/_____/_/  |_/_____/_____/_/ |_/_____/\____/_/  |_/_/ |_/_____/  )";
    
	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_BLUE);
	for (size_t i = 0; i < title.size(); i++) {
		Controller::gotoXY(25, 3 + i);
		cout << title[i];
	}

	int n = list.size();

	bool returnToMenu = false;
	if (n == 0) {
		Controller::gotoXY(40, 20);
		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		cout << "THERE IS CURRENTLY NO SAVED ACHIEVEMENT";
		int input;
		do {
			input = Controller::getConsoleInput();
		} while (input != ESC && input != LEFT);
		returnToMenu = true;
	}
	else {
		reverse(list.begin(), list.end());
		stable_sort(list.begin(), list.end(), [](const psi& a, const psi& b) {
			if (a.second > b.second)
				return true;
			return false;
		});

		if (n > 10) {	// top 10 highest rank
			list.erase(list.begin() + 10, list.end());
			n = list.size();
		}

		int y = 12, yCate = y - 2;
		int xRank = 15, xName = xRank + 30, xLevel = xRank + 60, xState = xRank + 84;
		
		Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
		Graphics::drawBorder(xRank - 5, yCate + 1, 101, 16, 1);

		Controller::gotoXY(xRank, yCate);
		cout << "RANK";

		string playerName = "PLAYER'S NAME";
		Controller::gotoXY(xName - (playerName.length() >> 1), yCate);
		cout << playerName;

		Controller::gotoXY(xLevel - 2, yCate);
		cout << "LEVEL";

		string state = "CURRENT STATE";
		Controller::gotoXY(xState - (state.length() >> 1), yCate);
		cout << state;

		vector <int> tColor(n, BLACK);
		tColor[0] = RED;
		int top = 0, bottom = 4;
		int curPos = 0;
		
		if (n < bottom + 1) {
			while (!returnToMenu) {
				for (size_t i = top, yLine = 0; i < n; i++, yLine += 2) {
					Controller::setConsoleColor(BACKGROUND_COLOR, tColor[i]);
					Controller::gotoXY(xRank, y + i - top + 1 + yLine);
					cout << i + 1;

					string name = list[i].first;
					Controller::gotoXY(xName - (name.length() >> 1), y + i - top + 1 + yLine);
					cout << name;

					Controller::gotoXY(xLevel, y + i - top + 1 + yLine);
					cout << (list[i].second < 6 ? list[i].second : 5);

					string state = list[i].second == 6 ? "COMPLETE" : "INCOMPLETE";
					Controller::gotoXY(xState - (state.length() >> 1), y + i - top + 1 + yLine);
					cout << state;
				}

				int choice = Controller::getConsoleInput();
				switch (choice) {
				case LEFT: case ESC:
					returnToMenu = true;
					break;

				case DOWN:
					if (curPos < n - 1)
						curPos++;
					break;

				case UP:
					if (curPos > 0)
						curPos--;
					break;

				}

				for (int& color : tColor)
					color = BLACK;

				tColor[curPos] = RED;
			}
		}
		else {
			bool passTop = false, passBottom = false;
			while (!returnToMenu) {
				if (passTop) {
					for (size_t i = top, yLine = 0; i <= bottom; i++, yLine += 2) {
						Controller::gotoXY(xRank, y + i - top + 1 + yLine);
						cout << "   ";

						string rmvName(list[i + 1].first.length(), ' ');
						Controller::gotoXY(xName - (list[i + 1].first.length() >> 1), y + i - top + 1 + yLine);
						cout << rmvName;

						Controller::gotoXY(xLevel, y + i - top + 1 + yLine);
						cout << ' ';

						string rmvState(10, ' ');
						Controller::gotoXY(xState - (rmvState.length() >> 1), y + i - top + 1 + yLine);
						cout << rmvState;

					}
				}
				else if (passBottom) {
					for (size_t i = top, yLine = 0; i <= bottom; i++, yLine += 2) {
						Controller::gotoXY(xRank, y + i - top + 1 + yLine);
						cout << "   ";

						string rmvName(list[i - 1].first.length(), ' ');
						Controller::gotoXY(xName - (list[i - 1].first.length() >> 1), y + i - top + 1 + yLine);
						cout << rmvName;

						Controller::gotoXY(xLevel, y + i - top + 1 + yLine);
						cout << ' ';

						string rmvState(10, ' ');
						Controller::gotoXY(xState - (rmvState.length() >> 1), y + i - top + 1 + yLine);
						cout << rmvState;

					}
				}

				for (size_t i = top, yLine = 0; i <= bottom; i++, yLine += 2) {
					Controller::setConsoleColor(BACKGROUND_COLOR, tColor[i]);
					Controller::gotoXY(xRank + 1, y + i - top + 1 + yLine);
					cout << i + 1;

					string name = list[i].first;
					Controller::gotoXY(xName - (name.length() >> 1), y + i - top + 1 + yLine);
					cout << name;

					Controller::gotoXY(xLevel, y + i - top + 1 + yLine);
					cout << (list[i].second < 6 ? list[i].second : 5);

					string state = list[i].second == 6 ? "COMPLETE" : "INCOMPLETE";
					Controller::gotoXY(xState - (state.length() >> 1), y + i - top + 1 + yLine);
					cout << state;
				}

				int choice = Controller::getConsoleInput();
				passBottom = passTop = false;

				switch (choice) {
				case ESC: case LEFT:
					returnToMenu = true;
					break;

				case DOWN: {
					if (curPos == bottom) {
						if (bottom < n - 1) {
							bottom++;
							top++;
							curPos++;
							passBottom = true;
						}
					}
					else if (curPos < bottom)
						curPos++;
					break;
				}

				case UP: {
					if (curPos == top) {
						if (top > 0) {
							top--;
							bottom--;
							curPos--;
							passTop = true;
						}
					}
					else if (curPos > top)
						curPos--;
					break;
				}
				}

				for (int& color : tColor)
					color = BLACK;

				tColor[curPos] = RED;
			}
		}
	}
	mainMenu();
}

void Menu::menuSetting() {
	system("cls");
	Graphics::drawBackgroundTitle();

	switch (Graphics::popup2Choices(40, 12, 10, 40, "BACKGROUND MUSIC", "ON", "OFF")) {
	case 1:
		Sound::backgroundMusic(true);
		break;
	case 2:
		Sound::backgroundMusic(false);
		break;
	}
	mainMenu();
}

void Menu::exitGame() {
	system("cls");

	Graphics::drawBackgroundTitle();
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	switch (Graphics::popup2Choices(36, 10, 7, 45, "ARE YOU SURE YOU WANT TO QUIT?")) {
	case 0: case 2:
		mainMenu();
		break;
	case 1:
		Graphics::farewellScreen();
		break;
	}
}

int Menu::setupMainOption() {
	int x = 50;
	int y = 12;
	int hPerCell = 2;
	int w = 16;
	int n = optionList.size();
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	Graphics::drawBorder(x, y, w, hPerCell, n);
	vector <int> tColor(n, BLACK);
	tColor[0] = RED;
	int curPos = 0;
	bool selected = false;

	while (!selected) {
		for (size_t i = 0; i < n; i++) {
			Controller::setConsoleColor(BACKGROUND_COLOR, tColor[i]);
			Controller::gotoXY(x + (w >> 1) - (optionList[i].length() >> 1), y + 1 + i * hPerCell);
			cout << optionList[i];
			Controller::gotoXY(x + 1, y + 1 + i * hPerCell);
			cout << " ";
		}
		Controller::setConsoleColor(BACKGROUND_COLOR, tColor[curPos]);
		Controller::gotoXY(x + 1, y + 1 + curPos * hPerCell);
		cout << ">";

		int c = Controller::getConsoleInput();

		switch (c) {
		case UP: {
			if (curPos == 0)
				curPos = n - 1;
			else
				curPos--;
			break;
		}
		case DOWN: {
			if (curPos == n - 1)
				curPos = 0;
			else
				curPos++;
			break;
		}
		case ENTER: {
			selected = true;
			break;
		}
		}

		for (int& color : tColor)
			color = BLACK;

		tColor[curPos] = RED;
	}
	return curPos;
}