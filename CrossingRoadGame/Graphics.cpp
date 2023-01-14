#include "Graphics.h"

void Graphics::switchDirection(char ** movingObject, int height, int length) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < length / 2; j++) {
			if (movingObject[i][j] == '\\')
				movingObject[i][j] = '/';
			else if (movingObject[i][j] == '/')
				movingObject[i][j] = '\\';
			else if (movingObject[i][j] == '(')
				movingObject[i][j] = ')';
			else if (movingObject[i][j] == ')')
				movingObject[i][j] = '(';
			else if (movingObject[i][j] == '\'')
				movingObject[i][j] = '`';
			else if (movingObject[i][j] == '`')
				movingObject[i][j] = '\'';
			else if (movingObject[i][j] == '<')
				movingObject[i][j] = '>';
			else if (movingObject[i][j] == '>')
				movingObject[i][j] = '<';
			else if (movingObject[i][j] == '[')
				movingObject[i][j] = ']';
			else if (movingObject[i][j] == ']')
				movingObject[i][j] = '[';

			int symmetPos = length - j - 1;
			if (movingObject[i][symmetPos] == '\\')
				movingObject[i][symmetPos] = '/';
			else if (movingObject[i][symmetPos] == '/')
				movingObject[i][symmetPos] = '\\';
			else if (movingObject[i][symmetPos] == '(')
				movingObject[i][symmetPos] = ')';
			else if (movingObject[i][symmetPos] == ')')
				movingObject[i][symmetPos] = '(';
			else if (movingObject[i][symmetPos] == '\'')
				movingObject[i][symmetPos] = '`';
			else if (movingObject[i][symmetPos] == '`')
				movingObject[i][symmetPos] = '\'';
			else if (movingObject[i][symmetPos] == '<')
				movingObject[i][symmetPos] = '>';
			else if (movingObject[i][symmetPos] == '>')
				movingObject[i][symmetPos] = '<';
			else if (movingObject[i][symmetPos] == '[')
				movingObject[i][symmetPos] = ']';
			else if (movingObject[i][symmetPos] == ']')
				movingObject[i][symmetPos] = '[';

			swap(movingObject[i][j], movingObject[i][symmetPos]);
		}
	}
	if (length & 1) {
		int j = length >> 1;
		for (int i = 0; i < height; i++) {
			if (movingObject[i][j] == '\\')
				movingObject[i][j] = '/';
			else if (movingObject[i][j] == '/')
				movingObject[i][j] = '\\';
			else if (movingObject[i][j] == '(')
				movingObject[i][j] = ')';
			else if (movingObject[i][j] == ')')
				movingObject[i][j] = '(';
			else if (movingObject[i][j] == '\'')
				movingObject[i][j] = '`';
			else if (movingObject[i][j] == '`')
				movingObject[i][j] = '\'';
			else if (movingObject[i][j] == '<')
				movingObject[i][j] = '>';
			else if (movingObject[i][j] == '>')
				movingObject[i][j] = '<';
			else if (movingObject[i][j] == '[')
				movingObject[i][j] = ']';
			else if (movingObject[i][j] == ']')
				movingObject[i][j] = '[';
		}
	}
}

void Graphics::drawBorder(int upperleftcornerX, int upperleftcornerY, int width, int Hpercell, int n) {
	int x = upperleftcornerX;
	int y = upperleftcornerY;

	for (int i = y; i <= y + Hpercell * n; i++) {
		if ((i - y) % Hpercell == 0) {
			if (i == y) {
				Controller::gotoXY(x, i);
				putchar(218);		//goc trai tren
				Controller::gotoXY(x + width, i);

				putchar(191);		//goc phai tren
			}
			else if (i < y + Hpercell * n) {
				Controller::gotoXY(x, i);
				putchar(195);		//nga 3 sang trai
				Controller::gotoXY(x + width, i);
				putchar(180);		//nga 3 sang phai
			}
			else {
				Controller::gotoXY(x, i);
				putchar(192);		//goc trai duoi
				Controller::gotoXY(x + width, i);
				putchar(217);		//goc phai duoi
			}
			Controller::gotoXY(x + 1, i);
			for (int j = x + 1; j < x + width; j++) {
				putchar(196);		//bien ngang
			}
		}
		else {
			Controller::gotoXY(x, i);
			putchar(179);			//bien doc
			Controller::gotoXY(x + width, i);
			putchar(179);
		}

	}
}

void Graphics::drawRoadWithFixedLaneWidth(int upperleftX, int upperleftY,  int length, int lane, int laneWidth) {
	int x = upperleftX, y = upperleftY;
	int width = lane * laneWidth;
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	for (int i = y; i <= y + width; i++) {
		if ((i - y) % laneWidth == 0) {
			if (i == y) {
				Controller::gotoXY(x, i);
				putchar(201);	//goc trai tren
				Controller::gotoXY(x + length + 1, i);
				putchar(187);	//goc phai tren

				Controller::gotoXY(x + 1, i);
				for (int j = x + 1; j <= x + length; j++) {
					putchar(178);	// =
					Sleep(10);
				}
			}
			else if (i == y + width) {
				Controller::gotoXY(x, i);
				putchar(200);	//goc trai duoi
				Controller::gotoXY(x + length + 1, i);
				putchar(188);	//goc phai duoi

				Controller::gotoXY(x + 1, i);
				for (int j = x + 1; j <= x + length; j++) {
					putchar(176);
					Sleep(10);
				}
			}
			else {
				Controller::gotoXY(x, i);
				putchar(186);	// ||
				Controller::gotoXY(x + length + 1, i);
				putchar(186);

				Controller::gotoXY(x + 1, i);
				for (int j = x + 1; j <= x + length; j++) {
					if (!(j & 1))
						putchar(196);	// -
					else
						putchar(' ');
					Sleep(20);
				}
			}
		}
		else {
			Controller::gotoXY(x, i);
			putchar(186);	// ||
			Controller::gotoXY(x + length + 1, i);
			putchar(186);
			Sleep(20);
		}
	}
}

void Graphics::drawRoadWithMultipleLaneWidths(int upperleftX, int upperleftY, int length, vector <int> laneWidth, vector <string>& line) {
	int x = upperleftX, y = upperleftY;
	int lane = laneWidth.size();
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	for (int n = 0, k = y; n < lane; k += laneWidth[n++]) {
		if (n == 0) {
			Controller::gotoXY(x, y);
			putchar(201);	//goc trai tren
			Controller::gotoXY(x + length + 1, y);
			putchar(187);	//goc phai tren
		}
		
		for (int i = k + (n == 0); i < k + laneWidth[n]; i++) {
			Controller::gotoXY(x, i);
			putchar(186);	// ||

			Controller::gotoXY(x + length + 1, i);
			putchar(186);

			Sleep(20);
		}
		
		string horizontalLine = "";
		Controller::gotoXY(x + 1, k);
		for (int j = x + 1; j <= x + length; j++) {
			if (n != 0) {
				if (!(j & 1)) {
					putchar(196);	// -
					horizontalLine += 196;
				}
				else {
					putchar(' ');
					horizontalLine += ' ';
				}
			}
			else {
				putchar(178);
				horizontalLine += 178;
				Sleep(5);
			}
			Sleep(20);
		}
		line.push_back(horizontalLine);

		if (n == lane - 1) {
			string startingLine = "";

			Controller::gotoXY(x, k + laneWidth[n]);
			putchar(200);	//goc trai duoi

			Controller::gotoXY(x + length + 1, k + laneWidth[n]);
			putchar(188);	//goc phai duoi

			Controller::gotoXY(x + 1, k + laneWidth[n]);
			for (int j = x + 1; j <= x + length; j++) {
				putchar(177);
				startingLine += 177;
				Sleep(20);
			}
			line.push_back(startingLine);
		}
	}

}

void Graphics::drawUtilityBoard(int x, int y, int height, int width) {
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	Controller::gotoXY(x, y);
	putchar(201);	//goc trai tren
	Controller::gotoXY(x + width, y);
	putchar(187);	//goc phai tren

	Controller::gotoXY(x, y + height);
	putchar(200);	//goc trai duoi
	Controller::gotoXY(x + width, y + height);
	putchar(188);	//goc phai duoi

	//*********Ve bien tren duoi*************
	for (int j = 1; j < width; j++) {
		Controller::gotoXY(x + j, y);
		putchar(205);	//=

		Controller::gotoXY(x + (width - j) , y + height);
		putchar(205);

		Sleep(30);
	}

	//********Ve bien 2 ben************
	for (int i = 1; i < height; i++) {
		Controller::gotoXY(x, y + (height - i));
		putchar(186);	//||

		Controller::gotoXY(x + width, y + i);
		putchar(186);

		Sleep(30);
	}

	unordered_map <string, string> mp;
	mp.insert({ "H:","HELP" });
	mp.insert({ "P:", "PAUSE" });
	mp.insert({ "G:", "SAVE GAME" });
	mp.insert({ "L:","LOAD GAME" });
		
	mp.insert({ "ESC:", "QUIT GAME" });

	vector <pair <int, int>> coords = {
		{x + 2, y + height - 1},
		{x + 2, y + height - 2},
		{x + 2, y + height - 3},
		{x + 2 + 18, y + height - 3},
		{x + 2 + 18, y + height - 2}
	};
	vector <int> color = {PURPLE, GREEN, LIGHT_RED, LIGHT_BLUE, YELLOW};
	int idx = 0;
	for (unordered_map <string, string>::iterator iter = mp.begin(); iter != mp.end() && idx < coords.size(); iter++, idx++) {
		Controller::setConsoleColor(BACKGROUND_COLOR, color[idx]);
		Controller::gotoXY(coords[idx].first, coords[idx].second);
		cout << iter->first;
		Controller::gotoXY(coords[idx].first + 5, coords[idx].second);
		cout << iter->second;
	}

	vector <string> player(4);
	player[0] = R"(   ___  __   _____  _________ )";
	player[1] = R"(  / _ \/ /  / _ \ \/ / __/ _ \)";
	player[2] = R"( / ___/ /__/ __ |\  / _// , _/)";
	player[3] = R"(/_/  /____/_/ |_|/_/___/_/|_| )";
                                
	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_AQUA);
	for (size_t i = 0; i < player.size(); i++) {
		Controller::gotoXY(x + (width >> 1) - (player[0].size() >> 1), y + 1 + i);
		cout << player[i];
	}

}

void Graphics::drawKeyboardMove(int x, int y, int Hpercell, int Wpercell, char up, char down, char right, char left){
	Controller::gotoXY(x + Wpercell, y);
	putchar(218);			//goc trai tren
	for (int i = x + Wpercell + 1; i <= x + (Wpercell << 1); i++) {
		if (i != x + (Wpercell << 1))
			putchar(196);		//bien ngang
		else
			putchar(191);		//goc phai tren
	}

	//tao bien phim len
	for (int i = y + 1; i < y + Hpercell; i++) {
		Controller::gotoXY(x + Wpercell, i);
		putchar(179);			//bien doc
	}

	for (int i = y + 1; i < y + Hpercell; i++) {
		Controller::gotoXY(x + (Wpercell << 1), i);
		putchar(179);			//bien doc
	}

	Controller::gotoXY(x, y + Hpercell);
	putchar(218);				//goc trai tren
	for (int i = x + 1; i <= x + Wpercell * 3; i++) {
		if (i == x + Wpercell * 3)
			putchar(191);		//goc phai tren
		else if ((i - x) % Wpercell == 0)
			putchar(197);		//goc nga 4
		else
			putchar(196);		//bien ngang
	}
	for (int k = 0; k <= 3; k++) {
		for (int i = y + Hpercell + 1; i < y + (Hpercell << 1); i++) {
			Controller::gotoXY(x + Wpercell * k, i);
			putchar(179);		//bien doc
		}
	}

	Controller::gotoXY(x, y + (Hpercell << 1));
	putchar(192);			//goc trai duoi
	for (int i = x + 1; i <= x + Wpercell * 3; i++) {
		if (i == x + Wpercell * 3)
			putchar(217);		//goc phai duoi
		else if ((i - x) % Wpercell == 0)
			putchar(193);		//goc nga 3
		else
			putchar(196);		//bien ngang
	}

	Controller::gotoXY(x + Wpercell + (Wpercell >> 1), y + (Hpercell >> 1));
	putchar(up);
	Controller::gotoXY(x + (Wpercell >> 1), y + Hpercell + (Hpercell >> 1));
	putchar(right);
	Controller::gotoXY(x + Wpercell + (Wpercell >> 1), y + Hpercell + (Hpercell >> 1));
	putchar(down);
	Controller::gotoXY(x + Wpercell * 2 + (Wpercell >> 1), y + Hpercell + (Hpercell >> 1));
	putchar(left);
}

void Graphics::drawReturnButton(int x, int y, string msg, int color) {
	Controller::setConsoleColor(BACKGROUND_COLOR, color);
	Graphics::drawBorder(x, y, msg.length() + 2, 2, 1);
	Controller::gotoXY(x + 1, y + 1);
	cout << "<" << msg;
}

void Graphics::drawBackgroundTitle() {
	int xTitle = 23, yTitle = 3;
	//Controller::setConsoleColor(BACKGROUND_COLOR, BLUE);
	Controller::gotoXY(xTitle, yTitle);
	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_RED);
	cout << " _____                     _____ _           ______                _ " << endl;
	Controller::gotoXY(xTitle, yTitle + 1);
	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_YELLOW);
	cout << "/  __ \\                   |_   _| |          | ___ \\              | |" << endl;
	Controller::gotoXY(xTitle, yTitle + 2);
	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_GREEN);
	cout << "| /  \\/_ __ ___  ___ ___    | | | |__   ___  | |_/ /___   __ _  __| |" << endl;
	Controller::gotoXY(xTitle, yTitle + 3);
	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_BLUE);
	cout << "| |   | '__/ _ \\/ __/ __|   | | | '_ \\ / _ \\ |    // _ \\ / _` |/ _` |" << endl;
	Controller::gotoXY(xTitle, yTitle + 4);
	Controller::setConsoleColor(BACKGROUND_COLOR, PURPLE);
	cout << "| \\__/\\ | | (_) \\__ \\__ \\   | | | | | |  __/ | |\\ \\ (_) | (_| | (_| |" << endl;
	Controller::gotoXY(xTitle, yTitle + 5);
	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_PURPLE);
	cout << " \\____/_|  \\___/|___/___/   \\_/ |_| |_|\\___| \\_| \\_\\___/ \\__,_|\\__,_|" << endl;
}

void Graphics::printValidPartOfObj(int x, int y, char**obj, int height, int length) {
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	for (int j = x; j < x + length; j++) {
		if (j > LEFT_BOUND && j < RIGHT_BOUND) {
			for (int i = y; i < y + height; i++) {
				Controller::gotoXY(j, i);
				putchar(obj[i - y][j - x]);
			}
		}
	}
}

void Graphics::removeObjAt(int x, int y, int height, int length) {
	for (int j = x; j < x + length; j++)
		if (j > LEFT_BOUND && j < RIGHT_BOUND) {
			for (int i = y; i < y + height; i++) {
				Controller::gotoXY(j, i);
				putchar(' ');
			}
		}
}

void Graphics::removePerson(const vector <string>& line, const vector <int>& laneWidth, int x, int y, int xPrint, int yPrint) {
	vector <int> Y (line.size());
	Y[0] = UPPER_BOUND;
	for (int i = 1; i < Y.size(); i++)
		Y[i] = Y[i - 1] + laneWidth[i - 1];

	int iter;
	for (iter = 0; iter < Y.size(); iter++)
		if (Y[iter] - 3 < y && y < Y[iter] + 3)
			break;
	
	Graphics::removeObjAt(xPrint, yPrint, 4, 4);

	if (iter == Y.size())
		return;

	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	for (int j = x - 2; j < x + 2; j++) {
		Controller::gotoXY(j, Y[iter]);
		cout << line[iter][j - LEFT_BOUND - 1];
	}
}

void Graphics::printCurLevel(int x, int y, int level) {
	//  __                      _
	// |  |                    | |
	// |  |        __    __    | |
	// |  |     ___\ \  / /___ | |
	// |  |___./ ^_\\ \/ // ^_\| |__
	// |______|\___] \__/ \___]|___/
	
	const char* Level[6];
	Level[0] = R"( __                      _   )";
	Level[1] = R"(|  |                    | |  )";
	Level[2] = R"(|  |        __    __    | |  )";
	Level[3] = R"(|  |     ___\ \  / /___ | |  )";
	Level[4] = R"(|  |___./ ^_\\ \/ // ^_\| |__)";
	Level[5] = R"(|______|\___] \__/ \___]|___/)";

	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_PURPLE);

	for (int i = 0; i < 6; i++) {
		Controller::gotoXY(x, y + i);
		cout << Level[i];
	}

	const char *num[6];

	switch (level) {
	case 1: {
		num[0] = R"(  __.  )";
		num[1] = R"( /  |  )";
		num[2] = R"(/_. |  )";
		num[3] = R"(  | |  )";
		num[4] = R"( _| |_ )";
		num[5] = R"(|_____|)";
		break;
	}
	case 2: {
		num[0] = R"( ______ )";
		num[1] = R"(/ __   ))";
		num[2] = R"(\/ /  / )";
		num[3] = R"(  /  /  )";
		num[4] = R"( /  /__ )";
		num[5] = R"((______))";
		break;
	}
	case 3: {
		num[0] = R"(_______ )";
		num[1] = R"(\___  / )";
		num[2] = R"(   / /  )";
		num[3] = R"(   \ \  )";
		num[4] = R"( /\_\ \ )";
		num[5] = R"(/______\)";
		break;
	}
	case 4: {
		num[0] = R"(   /|   )";
		num[1] = R"(  / |   )";
		num[2] = R"( //\|___)";
		num[3] = R"(/_   __/)";
		num[4] = R"(  | |   )";
		num[5] = R"(  |_|   )";
		break;
	}
	case 5: {
		num[0] = R"( _____ )";
		num[1] = R"(|  ___|)";
		num[2] = R"(| |___ )";
		num[3] = R"(|___  |)";
		num[4] = R"( ___| |)";
		num[5] = R"(|_____|)";
		break;
	}
		
	}
	Controller::setConsoleColor(BACKGROUND_COLOR, BLUE);
	for (int i = 0; i < 6; i++) {
		Controller::gotoXY(x + 30, y + i);
		cout << num[i];
	}
}

void Graphics::drawPopUpBorder(int x, int y, int height, int width) {
	if (width & 1) {
		Controller::gotoXY(x + width / 2, y);
		putchar(205);
	}

	for (int j = x + width / 2 - 1; j >= x; j--) {
		Controller::gotoXY(j, y);
		if (j > x)
			putchar(205);	// =
		else
			putchar(201);	// goc trai tren

		Controller::gotoXY(x + ((x + width) - j - 1), y);
		if (j > x)
			putchar(205);
		else
			putchar(187);	// goc phai tren

		Sleep(20);
	}

	for (int i = y + 1; i < y + height; i++) {
		Controller::gotoXY(x, i);
		putchar(186);	// ||

		Controller::gotoXY(x + width - 1, i);
		putchar(186);

		Sleep(20);
	}

	for (int j = x; j < x + width / 2; j++) {
		Controller::gotoXY(j, y + height - 1);
		if (j == x)
			putchar(200);	// goc trai duoi
		else
			putchar(205);

		Controller::gotoXY(x + ((x + width) - j - 1), y + height - 1);
		if (j == x)
			putchar(188);	// goc phai duoi
		else
			putchar(205);

		Sleep(20);
	}

	if (width & 1) {
		Controller::gotoXY(x + width / 2, y + height - 1);
		putchar(205);
	}
}

void Graphics::closePopUp(int x, int y, int height, int width) {
	for (int i = y; i < y + height; i++)
		for (int j = x; j < x + width; j++) {
			Controller::gotoXY(j, i);
			putchar(' ');
		}
}

void Graphics::popupHelpBoard(int x, int y) {
	int width = 35;
	int height = 10;
	
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	drawPopUpBorder(x, y, height, width);
	
	Controller::gotoXY(x + width/2 - 6, y + 1);
	Controller::setConsoleColor(BACKGROUND_COLOR, RED);
	cout << "INSTRUCTIONS";

	Controller::gotoXY(x + 2, y + 2);
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	cout << "Use either arrow keys or W,A,S,D";

	Controller::gotoXY(x + 2, y + 3);
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	cout << "to move the player. Cross the ";

	Controller::gotoXY(x + 2, y + 4);
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	cout << "road to complete the level.";

	Controller::gotoXY(x + 2, y + 5);
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	cout << "5 Completed Levels guarantee a";

	Controller::gotoXY(x + 2, y + 6);
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	cout << "victory. Being collided with any";

	Controller::gotoXY(x + 2, y + 7);
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	cout << "passing obstacles is gameover.";

	Controller::gotoXY(x + (width - 1) / 2 - 10, y + height - 1);
	Controller::setConsoleColor(BACKGROUND_COLOR, BLUE);
	cout << "Press Enter to resume";
}

void Graphics::popupPause(int x, int y){
	int height = 10;
	int width = 36;

	const char *pause[7];
	pause[0] = R"( ____          ._.  ._.._________ )";
	pause[1] = R"(|  _ ))   /\   | |  | ||  ____)__|)";
	pause[2] = R"(| | ) )) /  \  | |  | |\ \  | |__ )";
	pause[3] = R"(| |__\ \/ /\ \ | |  | | \ \ |  __|)";
	pause[4] = R"(| .___./ ___  \| |  | |  \ \| |__ )";
	pause[5] = R"(| |___/ /   \  | |__| |___) \ ___|)";
	pause[6] = R"(|_|____/     \_|______|______)    )";

	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	drawPopUpBorder(x, y, height, width);

	for (int i = 0; i < 7; i++) {
		Controller::gotoXY(x + 1, i + y + 1);
		Controller::setConsoleColor(BACKGROUND_COLOR, RED);
		cout << pause[i];
	}

	Controller::gotoXY(x + (width - 1) / 2 - 10, y + height - 1);
	Controller::setConsoleColor(BACKGROUND_COLOR, BLUE);
	cout << "Press Enter to resume";
}

void Graphics::popupSaveGame(int x, int y, string& saveName) {
	int height = 5;
	int width = 36;

	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	drawPopUpBorder(x, y, height, width);
	Controller::setConsoleColor(BACKGROUND_COLOR, RED);
	Controller::gotoXY(x + 1, y + 1);
	cout << "Enter a name to save your progress";

	Controller::showCursor(true);
	Controller::gotoXY(x + 1, y + 3);
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	getline(cin, saveName);
	Controller::showCursor(false);
}

void Graphics::printListOfSavedFiles(int x, int y, const vector <string> &savedfiles, int top, int bottom, string& selectedFile) {
	int n = savedfiles.size();
	if (n == 0) {
		Controller::gotoXY(x, y + 4);
		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		cout << "THERE IS CURRENTLY NO SAVED FILE!";
		Sleep(5000);
		return;
	}

	vector <int> tColor(n, BLACK);
	tColor[0] = RED;
	int curPos = 0;
	bool passTop = false, passBottom = false;
	bool selected = false, cancel = false;

	Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
	Controller::gotoXY(x, y + (bottom - top + 1) +  2);
	cout << "Press C to cancel.";
	
	if (n < bottom + 1) {
		while (!selected && !cancel) {
			for (size_t i = 0; i < n; i++) {
				Controller::setConsoleColor(BACKGROUND_COLOR, tColor[i]);
				Controller::gotoXY(x + 3, y + i + 1);
				cout << savedfiles[i];

				Controller::gotoXY(x + 1, y + i + 1);
				cout << " ";
			}

			Controller::gotoXY(x + 1, y + curPos + 1);
			Controller::setConsoleColor(BACKGROUND_COLOR, tColor[curPos]);
			cout << ">";

			int c = Controller::getConsoleInput();

			switch (c) {
			case UP:
				if (curPos > 0)
					curPos--;
				break;
			case DOWN:
				if (curPos < n - 1)
					curPos++;
				break;
			case ENTER: {
				selected = true;
				selectedFile = savedfiles[curPos];
				break;
			}
			case CANCEL:
				cancel = true;
				break;
			}

			for (int& color : tColor)
				color = BLACK;

			tColor[curPos] = RED;
		}
	}
	else {
		while (!selected && !cancel) {
			if (passTop) {
				for (size_t i = top; i <= bottom; i++) {
					string rmv(savedfiles[i + 1].length(), ' ');
					Controller::gotoXY(x + 3, y + i - top + 1);
					cout << rmv;
				}
			}
			else if (passBottom) {
				for (size_t i = top; i <= bottom; i++) {
					string rmv(savedfiles[i - 1].length(), ' ');
					Controller::gotoXY(x + 3, y + i - top + 1);
					cout << rmv;
				}
			}

			for (size_t i = top; i <= bottom; i++) {
				Controller::setConsoleColor(BACKGROUND_COLOR, tColor[i]);
				Controller::gotoXY(x + 3, y + i - top + 1);
				cout << savedfiles[i];

				Controller::gotoXY(x + 1, y + i - top + 1);
				cout << " ";
			}

			Controller::gotoXY(x + 1, y + curPos - top + 1);
			Controller::setConsoleColor(BACKGROUND_COLOR, tColor[curPos]);
			cout << ">";

			int c = Controller::getConsoleInput();
			passTop = passBottom = false;
			switch (c) {
			case UP: {
				if (curPos == top) {
					if (top > 0) {
						passTop = true;
						top--;
						bottom--;
						curPos--;
					}
				}
				else if (curPos > top)
					curPos--;
				break;
			}

			case DOWN: {
				if (curPos == bottom) {
					if (bottom < n - 1) {
						passBottom = true;
						top++;
						bottom++;
						curPos++;
					}
				}
				else if (curPos < bottom)
					curPos++;
				break;
			}
			case ENTER: {
				selected = true;
				selectedFile = savedfiles[curPos];
				break;
			}
			case CANCEL: {
				cancel = true;
				break;
			}
			}

			for (int& color : tColor)
				color = BLACK;

			tColor[curPos] = RED;

		}
	}

	if (selectedFile != "") {
		size_t posLastSlash = selectedFile.find_last_of('/');
		selectedFile = selectedFile.substr(posLastSlash + 1, selectedFile.find_last_of('.') - posLastSlash - 1);
	}
}

int Graphics::popup2Choices(int x, int y, int height, int width, string msg, string c1, string c2) {
	Graphics::drawBorder(x, y, width, height, 1);

	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_BLUE);
	Controller::gotoXY(x + (width >> 1) - (msg.length() >> 1), y + 1);
	cout << msg;

	Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
	string cancelMsg = "Press C to cancel";
	Controller::gotoXY(x + (width >> 1) - (cancelMsg.length() >> 1), y + height - 1);
	cout << cancelMsg;

	int xChoice1 = x + (width >> 2);
	int xChoice2 = x + ((3 * width) >> 2);
	int yChoice = y + (height >> 1);

	int tColor[2] = {GREEN, BLACK};
	bool curPos = 0;
	bool selected = false;
	bool cancel = false;
		
	while (!selected && !cancel) {
		Controller::setConsoleColor(BACKGROUND_COLOR, tColor[0]);
		Controller::gotoXY(xChoice1, yChoice);
		cout << c1;
		Controller::gotoXY(xChoice1 - 2, yChoice);
		cout << " ";
		Controller::gotoXY(xChoice1 + c1.length() + 1, yChoice);
		cout << " ";

		Controller::setConsoleColor(BACKGROUND_COLOR, tColor[1]);
		Controller::gotoXY(xChoice2, yChoice);
		cout << c2;
		Controller::gotoXY(xChoice2 - 2, yChoice);
		cout << " ";
		Controller::gotoXY(xChoice2 + c2.length() + 1, yChoice);
		cout << " ";

		Controller::setConsoleColor(BACKGROUND_COLOR, tColor[curPos]);
		Controller::gotoXY((curPos) ? xChoice2 - 2 : xChoice1 - 2, yChoice);
		cout << ">";
		Controller::gotoXY((curPos) ? (xChoice2 + c2.length() + 1) : (xChoice1 + c1.length() + 1), yChoice);
		cout << "<";

		int input = Controller::getConsoleInput();

		switch (input) {
		case LEFT: case RIGHT:
			curPos = !curPos;
			break;
		case ENTER:
			selected = true;
			break;
		case CANCEL: {
			cancel = true;
			break;
		}
		}
		tColor[0] = tColor[1] = BLACK;

		tColor[curPos] = (curPos) ? RED : GREEN;
	}
	
	return (!cancel) ? curPos + 1 : 0;
}

void Graphics::loseGameAnimation() {
	vector <string> sprintingMan(6);
	sprintingMan[0] = R"(    _     )";
	sprintingMan[1] = R"(   (_)    )";
	sprintingMan[2] = R"(   /|\/   )";
	sprintingMan[3] = R"(   `|__   )";
	sprintingMan[4] = R"( __/   \  )";
	sprintingMan[5] = R"(        ` )";

	vector <string> runningMan(6);
	runningMan[0] = R"(   _    )";
	runningMan[1] = R"(  (_)   )";
	runningMan[2] = R"( _/|\_, )";
	runningMan[3] = R"(   |    )";
	runningMan[4] = R"(  / \   )";
	runningMan[5] = R"( /  /   )";

	vector <string> standstillMan(6);
	standstillMan[0] = R"(   _   )";
	standstillMan[1] = R"(  (_)  )";
	standstillMan[2] = R"(  /|\  )";
	standstillMan[3] = R"( ' | ' )";
	standstillMan[4] = R"(  / \  )";
	standstillMan[5] = R"( /   \ )";


	vector <string> castle(33);
	castle[0]  = R"(                 !._                                              )";
	castle[1]  = R"(                 |.-`                                             )";
	castle[2]  = R"(                /\                                                )";
	castle[3]  = R"(               /^^\                                               )";
	castle[4]  = R"(              /^^^^\                                              )";
	castle[5]  = R"(             /^^^^^^\                                             )";
	castle[6]  = R"(            /________\  !._        !._                            )";
	castle[7]  = R"(       !._  |#  ##  #|  |.-`       |.-`                           )";
	castle[8]  = R"(       |.-` |#  ##  #| /\         /^\                             )";
	castle[9]  = R"(       /\   |________|/^^\       /^^^\                            )";
	castle[10] = R"(      /^^\   |#     |/^^^^\ !._ /_____\                           )";
	castle[11] = R"(     /^^^^\  |#     /______\|.-`|#    |        !._                )";
	castle[12] = R"(    /______\ |  ##  |# ## #|/\  |#    |        |.-`    !._        )";
	castle[13] = R"(    |# ## #| |  ##  |# ## #|^^\ |    #|       /^\      |.-`       )";
	castle[14] = R"(    |# ## #| |_____#|______|^^^\|____#|      /^^^\    /^\         )";
	castle[15] = R"(    |______|/________|    |_____/     \     /^^^^^\  /^^^\        )";
	castle[16] = R"(     |    | |        |   #|    /_______\   /^^^^^^^\/^^^^^\       )";
	castle[17] = R"(     |    | |        |   #|    |       |  /^^^^^^^^^\^^^^^^\      )";
	castle[18] = R"(     |    | U_U_U_U_U_U_U_U    |#     #|  [U_U_U_U_U]^^^^^^^\     )";
	castle[19] = R"(     |    /\[_____________]    |#     #|   \_______/^^^^^^^^^\    )";
	castle[20] = R"(     |   /^^\|           |     |       |    |#    |U_U_U_U_U_U    )";
	castle[21] = R"( U_U_U_U/____\           ||U_U_U_U_U_U_U_U_U|#    |__________/    )";
	castle[22] = R"( \______|#  #|           |[_________________|     |        #|     )";
	castle[23] = R"(  |     |____|     U_U_U_U_|#              #|     |        #|     )";
	castle[24] = R"(  |      |  U_U_U_U|       |#     ___      #|    #|         |     )";
	castle[25] = R"(  |      |  |      |       |    .'| |'.     |    #|         |     )";
	castle[26] = R"(  |      |  |      |       |  .'| | | |'.   |     |  .--.   |     )";
	castle[27] = R"(  lc_____|  |      |       |  |_|_|_|_|_|   |     |  |  |   |     )";
	castle[28] = R"(  ~"^"~"~|__|______|       |  |_________|   |#    |  |  |   |     )";
	castle[29] = R"(         ~"^"~"^"~^|_______|  | | | | | |   |#    |__|__|___|~"^"~)";
	castle[30] = R"(                   ~"^"~"^"|__|_|_|_|_|_|___|     |~^~   ~"^"~    )";
	castle[31] = R"(                           ~^~/        /~"^"|_____|               )";
	castle[32] = R"(                             /        /     ~"^"~"^               )";


	int y = 2;
	Controller::gotoXY(0, y);
	for (size_t i = 0; i < 80; i++)
		cout << "=";
	cout << ".";

	Controller::gotoXY(0, y + 24);
	for (size_t i = 0; i < 80; i++)
		cout << "=";
	cout << ".";

	for (size_t i = y + 1, j = 70; j >= 0 && i < y + 24; i++, j--) {
		Controller::gotoXY(j, i);
		cout << "/";
	}
	for (size_t i = y + 1, j = 16; i < y + 16 && j >= 0; i++, j--) {
		Controller::gotoXY(j, i);
		cout << "/";
	}

	for (size_t i = 0; i < 26; i++) {
		Controller::gotoXY(80, i);
		cout << "|";
	}
	
	auto humanRunHorizontally = [=](int oldX, int newX, int Y, int sleepTime, short steps) {
		Sound::playBreatheRunManSound();
		if (oldX < newX) {
			size_t count = 0;
			while (oldX < newX) {
				if (count & 1) {
					for (size_t i = 0; i < runningMan.size(); i++) {
						Controller::gotoXY(oldX, Y + i);
						for (size_t j = 0; j < runningMan[i].size(); j++)
							cout << " ";
					}

					oldX += steps;

					for (size_t i = 0; i < sprintingMan.size(); i++) {
						Controller::gotoXY(oldX, Y + i);
						cout << sprintingMan[i];
					}
				}
				else {
					for (size_t i = 0; i < sprintingMan.size(); i++) {
						Controller::gotoXY(oldX, Y + i);
						for (size_t j = 0; j < sprintingMan[i].size(); j++)
							cout << " ";
					}

					oldX += steps;

					for (size_t i = 0; i < runningMan.size(); i++) {
						Controller::gotoXY(oldX, Y + i);
						cout << runningMan[i];
					}
				}
				count++;
				Sleep(sleepTime);
			}
		}
		else if (oldX > newX) {
			size_t count = 0;
			while (oldX > newX) {
				if (count & 1) {
					for (size_t i = 0; i < runningMan.size(); i++) {
						Controller::gotoXY(oldX, Y + i);
						for (size_t j = 0; j < runningMan[i].size(); j++)
							cout << " ";
					}

					oldX -= steps;

					for (size_t i = 0; i < sprintingMan.size(); i++) {
						Controller::gotoXY(oldX, Y + i);
						cout << sprintingMan[i];
					}
				}
				else {
					for (size_t i = 0; i < sprintingMan.size(); i++) {
						Controller::gotoXY(oldX, Y + i);
						for (size_t j = 0; j < sprintingMan[i].size(); j++)
							cout << " ";
					}

					oldX += steps;

					for (size_t i = 0; i < runningMan.size(); i++) {
						Controller::gotoXY(oldX, Y + i);
						cout << runningMan[i];
					}
				}
				count++;
				Sleep(sleepTime);
			}
		}
	};
	
	humanRunHorizontally(10, 50, 10, 200, 2);

	system("cls");

	Sound::playTRexRoar();
	Sound::playCarCrashSound();
	
	Sound::playAAHsound();

	vector <string> aah(21);

	aah[0] =  R"(          _____                    _____                    _____          )";
	aah[1] =  R"(         /\    \                  /\    \                  /\    \         )";
	aah[2] =  R"(        /::\    \                /::\    \                /::\____\        )";
	aah[3] =  R"(       /::::\    \              /::::\    \              /:::/    /        )";
	aah[4] =  R"(      /::::::\    \            /::::::\    \            /:::/    /         )";
	aah[5] =  R"(     /:::/\:::\    \          /:::/\:::\    \          /:::/    /          )";
	aah[6] =  R"(    /:::/__\:::\    \        /:::/__\:::\    \        /:::/____/           )";
	aah[7] =  R"(   /::::\   \:::\    \      /::::\   \:::\    \      /::::\    \           )";
	aah[8] =  R"(  /::::::\   \:::\    \    /::::::\   \:::\    \    /::::::\    \   _____  )";
	aah[9] =  R"( /:::/\:::\   \:::\    \  /:::/\:::\   \:::\    \  /:::/\:::\    \ /\    \ )";
	aah[10] = R"(/:::/  \:::\   \:::\____\/:::/  \:::\   \:::\____\/:::/  \:::\    /::\____\)";
	aah[11] = R"(\::/    \:::\  /:::/    /\::/    \:::\  /:::/    /\::/    \:::\  /:::/    /)";
	aah[12] = R"( \/____/ \:::\/:::/    /  \/____/ \:::\/:::/    /  \/____/ \:::\/:::/    / )";
	aah[13] = R"(          \::::::/    /            \::::::/    /            \::::::/    /  )";
	aah[14] = R"(           \::::/    /              \::::/    /              \::::/    /   )";
	aah[15] = R"(           /:::/    /               /:::/    /               /:::/    /    )";
	aah[16] = R"(          /:::/    /               /:::/    /               /:::/    /     )";
	aah[17] = R"(         /:::/    /               /:::/    /               /:::/    /      )";
	aah[18] = R"(        /:::/    /               /:::/    /               /:::/    /       )";
	aah[19] = R"(        \::/    /                \::/    /                \::/    /        )";
	aah[20] = R"(         \/____/                  \/____/                  \/____/         )";

	for (size_t i = 0; i < aah.size(); i++) {
		Controller::gotoXY(20, 5 + i);
		cout << aah[i];
	}
	Sleep(1100);

	system("cls");

	auto humanMoveVertically = [standstillMan](int oldY, int newY, int X, int sleepTime, short steps) {
		Sound::playIsekaiSound();
		if (oldY < newY) {
			while (oldY < newY) {
				for (size_t i = 0; i < standstillMan.size(); i++) {
					Controller::gotoXY(X, oldY + i);
					for (size_t j = 0; j < standstillMan[i].size(); j++)
						cout << " ";
				}

				oldY += steps;

				for (size_t i = 0; i < standstillMan.size(); i++) {
					Controller::gotoXY(X, oldY + i);
					cout << standstillMan[i];
				}

				Sleep(sleepTime -= 100);
			}
		}
		else if (oldY > newY) {
			while (oldY > newY) {
				for (size_t i = 0; i < standstillMan.size(); i++) {
					Controller::gotoXY(X, oldY + i);
					for (size_t j = 0; j < standstillMan[i].size(); j++)
						cout << " ";
				}

				oldY -= steps;

				for (size_t i = 0; i < standstillMan.size(); i++) {
					Controller::gotoXY(X, oldY + i);
					cout << standstillMan[i];
				}

				Sleep(sleepTime -= 100);
			}
		}
	};

	humanMoveVertically(25, 10, 50, 520, 3);
	
	Sleep(1000);
	system("cls");
	short x = 1;
	y = 0;
	for (size_t i = y; i < y + castle.size(); i++){
		Controller::gotoXY(x, i);
		cout << castle[i - y];
	}
	Controller::setConsoleColor(BACKGROUND_COLOR, GREEN);
	Controller::gotoXY(0,y + castle.size());
	for (size_t j = 0; j < 100; j++)
		cout << "-";

	Controller::gotoXY(x + castle[23].size() - 3, y + 24);
	for (size_t j = 83; j < 130; j++)
		cout << "_";


	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	humanMoveVertically(10, 25, 83, 520, 3);

	Controller::setConsoleColor(BACKGROUND_COLOR, GREEN);
	Controller::gotoXY(x + castle[23].size() - 3, y + 24);
	for (size_t j = 83; j < 130; j++)
		cout << "_";

	Controller::setConsoleColor(BACKGROUND_COLOR, LIGHT_RED);
	vector <string> dragon(16);

	dragon[0]  = R"(                 ___====-_  _-====___                 )";
	dragon[1]  = R"(           _--^^^#####//      \\#####^^^--_           )";
	dragon[2]  = R"(        _-^##########// (    ) \\##########^-_        )";
	dragon[3]  = R"(       -############//  |\^^/|  \\############-       )";
	dragon[4]  = R"(     _/############//   (@::@)   \\############\_     )";
	dragon[5]  = R"(    /#############((     \\//     ))#############\    )";
	dragon[6]  = R"(   -###############\\    (oo)    //###############-   )";
	dragon[7]  = R"(  -#################\\  / VV \  //#################-  )";
	dragon[8]  = R"( -###################\\/      \//###################- )";
	dragon[9]  = R"(_#/|##########/\######(   /\   )######/\##########|\#_)";
	dragon[10] = R"(|/ |#/\#/\#/\/  \#/\##\  |  |  /##/\#/  \/\#/\#/\#| \|)";
	dragon[11] = R"(`  |/  V  V  `   V  \#\| |  | |/#/  V   '  V  V  \|  ')";
	dragon[12] = R"(   `   `  `      `   / | |  | | \   '      '  '   '   )";
	dragon[13] = R"(                    (  | |  | |  )                    )";
	dragon[14] = R"(                   __\ | |  | | /__                   )";
	dragon[15] = R"(                  (vvv(VVV)(VVV)vvv)                  )";


	for (size_t j = 0; j < dragon.size(); j++) {
		Controller::gotoXY(60, j);
		cout << dragon[j];
	}

}

void Graphics::farewellScreen() {
	system("cls");
	vector <string> helicopter(15);

	helicopter[0]  = R"(___________________________    __________________________                )";
	helicopter[1]  = R"(`--------------------------`()'--------------------------'               )";
	helicopter[2]  = R"(                            ||                                           )";
	helicopter[3]  = R"(                         __ ||                                        __ )";
	helicopter[4]  = R"(                         ] """"---...._                             .' / )";
	helicopter[5]  = R"(                   _,-"""==============`--.                       .'/)/  )";
	helicopter[6]  = R"(                 ,' ) ,--. .-----.         `.___________________.' ///_  )";
	helicopter[7]  = R"(               .'  / /___| |_____|                       _______  ()  _> )";
	helicopter[8]  = R"(              /   / /____| |__|__|             ,----"""""       `//  \   )";
	helicopter[9]  = R"(            .<`=='===========================.'                 (/`.  \  )";
	helicopter[10] = R"(           (  `.----------------------------/                       `._\ )";
	helicopter[11] = R"(            `-._\_                ____...--'                             )";
	helicopter[12] = R"(                  """--ii--'"""77"                                       )";
	helicopter[13] = R"(                 .____//______//___,                                     )";
	helicopter[14] = R"(                 `-----------------'                                     )";



	vector <string> train(30);

	train[0]  = R"(           _____   _  _     ___    _  _    _  __           __   __   ___    _   _  )";
	train[1]  = R"(    o O O |_   _| | || |   /   \  | \| |  | |/ /     o O O \ \ / /  / _ \  | | | | )";
	train[2]  = R"(   o        | |   | __ |   | - |  | .` |  | ' <     o       \ V /  | (_) | | |_| | )";
	train[3]  = R"(  TS__[O]  _|_|_  |_||_|   |_|_|  |_|\_|  |_|\_\   TS__[O]  _|_|_   \___/   \___/  )";
	train[4]  = R"( {======|_|"""""|_|"""""|_|"""""|_|"""""|_|"""""| {======|_| """ |_|"""""|_|"""""| )";
	train[5]  = R"(./o--000'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'./o--000'"`-0-0-'"`-0-0-'"`-0-0-  )";
	train[6]  = R"(             ___    ___     ___                                                    )";
	train[7]  = R"(    o O O   | __|  / _ \   | _ \                                                   )";
	train[8]  = R"(   o        | _|  | (_) |  |   /                                                   )";
	train[9]  = R"(  TS__[O]  _|_|_   \___/   |_|_\                                                   )";
	train[10] = R"( {======|_| """ |_|"""""|_|"""""|                                                  )";
	train[11] = R"(./o--000'"`-0-0-'"`-0-0-'"`-0-0-'                                                  )";
	train[12] = R"(             ___    _       ___   __   __   ___    _  _     ___                    )";
	train[13] = R"(    o O O   | _ \  | |     /   \  \ \ / /  |_ _|  | \| |   / __|                   )";
	train[14] = R"(   o        |  _/  | |__   | - |   \ V /    | |   | .` |  | (_ |                   )";
	train[15] = R"(  TS__[O]  _|_|_   |____|  |_|_|   _|_|_   |___|  |_|\_|   \___|                   )";
	train[16] = R"( {======|_| """ |_|"""""|_|"""""|_| """ |_|"""""|_|"""""|_|"""""|                  )";
	train[17] = R"(./o--000'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'                  )";
	train[18] = R"(            ___    _   _    ___                                                    )";
	train[19] = R"(    o O O  / _ \  | | | |  | _ \                                                   )";
	train[20] = R"(   o      | (_) | | |_| |  |   /                                                   )";
	train[21] = R"(  TS__[O]  \___/   \___/   |_|_\                                                   )";
	train[22] = R"( {======|_|"""""|_|"""""|_|"""""|                                                  )";
	train[23] = R"(./o--000'"`-0-0-'"`-0-0-'"`-0-0-'                                                  )";
	train[24] = R"(            ___     ___   __  __    ___                                            )";
	train[25] = R"(    o O O  / __|   /   \ |  \/  |  | __|                                           )";
	train[26] = R"(   o      | (_ |   | - | | |\/| |  | _|                                            )";
	train[27] = R"(  TS__[O]  \___|   |_|_| |_|__|_|  |___|                                           )";
	train[28] = R"( {======|_|"""""|_|"""""|_|"""""|_|"""""|                                          )";
	train[29] = R"(./o--000'"`-0-0-'"`-0-0-'"`-0-0-'"`-0-0-'                                          )";


	short y = 40;
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	for (size_t i = 0; i < helicopter.size(); i++) {
		Controller::gotoXY(20, y + i);
		cout << helicopter[i];
	}
	Controller::setConsoleColor(BACKGROUND_COLOR, RED);
	for (size_t i = 0; i < train.size(); i++) {
		Controller::gotoXY(16, y + helicopter.size() + i);
		cout << train[i];
	}
	int speed = 100;
	Sound::playHelicopterMemeSound();
	for (size_t i = 0; i < y + helicopter.size() + train.size() + 2; i++) {
		Controller::gotoXY(0, i);
		cout << " ";
		Sleep(speed);
	}

	Sound::playArigatouSound();
	
	Sleep(3000);
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	exit(EXIT_SUCCESS);
}