#include "CGAME.h"
mutex mtx;

CGAME::CGAME() {
	IS_RUNNING = IS_PAUSING = false;
	
	Lvl = new Level(1);
	road = NULL;
}

CGAME::~CGAME() {
	delete Lvl;
	if (road != NULL)
		delete road;
	while (!lanes.empty()) {
		LANE* tmp = lanes.back();
		lanes.pop_back();
		delete tmp;
	}
}

void CGAME::setupLevelData() {
	road = new CROAD(Lvl->getlaneWidth());
	vector <int> type = Lvl->getTypeLane();
	vector <int> laneWidth = Lvl->getlaneWidth();

	int animalSteps = Lvl->getAnimalSteps();
	int vehicleSteps = Lvl->getVehicleSteps();
	int msPerStep = Lvl->getMSecPerSteps();

	int maxRedDur = Lvl->getRedDuration();
	int maxGreenDur = Lvl->getGreenDuration();
	int maxYellowDur = Lvl->getYellowDuration();

	int k = UPPER_BOUND;
	for (int i = 0; i < laneWidth.size(); k += laneWidth[i++]);

	LOWER_BOUND = k;

	srand(time(NULL));
	for (int i = 0, y = UPPER_BOUND + 4; i < type.size(); y += laneWidth[i++]) {
		bool randomDirection = rand() % 2;
		lanes.push_back(new LANE(randomDirection, y, (type[i] == ANIMALCODE) ? animalSteps : vehicleSteps, msPerStep));
		if (type[i] == VEHICLECODE)
			lanes.back()->setLightDuration(maxGreenDur, maxYellowDur, maxRedDur);
	}
}

void CGAME::clearData() {
	while (!lanes.empty()) {
		LANE* tmp = lanes.back();
		lanes.pop_back();
		delete tmp;
	}
	if (road != NULL) {
		delete road;
		road = NULL;
	}

	system("cls");
}

void CGAME::levelUp() {
	clearData();

	if (Lvl->getCurrentLevel() < 5) {
		mtx.lock();
		Lvl->updateLevel(Lvl->getCurrentLevel() + 1);
		mtx.unlock();
		startGame();
	}
	else {
		IS_RUNNING = false;
		Lvl->setLevel(6);
		system("cls");
		winGame();

		Controller::gotoXY(30, 17);
		cout << "PLAYER: " << playerName;

		switch (Graphics::popup2Choices(40, 20, 8, 30, "SAVE YOUR ACHIEVEMENT?")) {
		case 0: case 2:
			break;
		case 1:
			saveGame();
			break;
		}
	}
}

void CGAME::laneFlow(vector <thread> &tLane, const vector <int>& type) {
	if (IS_RUNNING) {
		if (IS_PAUSING) {
			mtx.lock();
			for (LANE *x : lanes)
				x->stop();

			for (size_t i = 0; i < lanes.size(); i++) {
				lanes[i]->printCurrentObstacle();
				if (type[i] == VEHICLECODE)
					lanes[i]->printLight();
			}
			
			mtx.unlock();
		}

		for (int index = 0; index < lanes.size(); ) {
			if (type[index] == VEHICLECODE) {
				mtx.lock();
				mtx.unlock();
				tLane.push_back(thread([&, index] {lanes[index]->circulateV(); }));
			}
			else if (type[index] == ANIMALCODE) {
				mtx.lock();
				mtx.unlock();
				tLane.push_back(thread([&, index] {lanes[index]->circulateA(); }));
			}
			mtx.lock();
			index++;
			mtx.unlock();
		}

	}
}

void CGAME::setupGame() {
	if (!loadGameMode)
		setupLevelData();

	road->buildAt(LEFT_BOUND, UPPER_BOUND);

	Graphics::drawUtilityBoard(xToPopUp, UPPER_BOUND + 3, 10, 35);
	Graphics::printCurLevel(RIGHT_BOUND + 5, 0, Lvl->getCurrentLevel());
	Controller::gotoXY(xToPopUp + (35 >> 1) - (playerName.length() >> 1), UPPER_BOUND + 8);
	cout << playerName;
		
	if (!loadGameMode)
		CPEOPLE::getInstance().spawnPlayer();
	else {
		CPEOPLE::getInstance().drawPlayer();
		loadGameMode = false;
	}
}

void CGAME::startGame() {
	if (Lvl->getCurrentLevel() == 1) {
		if (playerName == "") {
			string name;
			do {
				system("cls");
				Graphics::drawBackgroundTitle();
				Controller::gotoXY(10, 15);
				cout << "ENTER YOUR NAME(WITHIN 20 CHARACTERS): ";
				Controller::setConsoleColor(BACKGROUND_COLOR, BLUE);
				Controller::showCursor(true);
				getline(cin, name);
				Controller::showCursor(false);
			} while (name.length() > 20);
			playerName = name;
		}
	}
		
	system("cls");
	
	mtx.lock();
	setupGame();
	mtx.unlock();

	IS_RUNNING = true;
	CPEOPLE::getInstance().revive();
	Sound::setImpactSState(true);
	processingGame();
}

void CGAME::processingGame() {
	mtx.lock();
	for (LANE* lane : lanes)
		lane->start();
	mtx.unlock();
	vector <thread> tLane;
	laneFlow(tLane, Lvl->getTypeLane());

	while (IS_RUNNING) {
		if (IS_PAUSING) {
			mtx.lock();
			pauseGame();
			mtx.unlock();
		}
				
		int input = Controller::getConsoleInput();
		switch (input) {
		case ESC: {
			mtx.lock();
			IS_PAUSING = true;
			for (LANE* lane : lanes)
				lane->stop();

			int choice = Graphics::popup2Choices(xToPopUp, yToPopUp, 7, 30, "QUIT WITHOUT SAVING?");

			switch (choice) {
			case 0: {
				Graphics::closePopUp(xToPopUp, yToPopUp, 7 + 1, 30 + 1);

				IS_PAUSING = false;

				this_thread::sleep_for(seconds(2));

				for (LANE* lane : lanes)
					lane->start();
				break;
			}
			case 1: {
				IS_RUNNING = false;
				break;
			}
			case 2: {
				Graphics::closePopUp(xToPopUp, yToPopUp, 7 + 1, 30 + 1);
				
				saveGame();

				IS_RUNNING = false;

				break;
			}
			}
			if (!IS_RUNNING)
				for (LANE* lane : lanes)
					lane->quitGame();

			mtx.unlock();
			
			break;
		}

		case UP: case DOWN: case RIGHT: case LEFT: {
			mtx.lock();
			int x = CPEOPLE::getInstance().getCoordinates().first;
			int y = CPEOPLE::getInstance().getCoordinates().second;
			int xPrint = CPEOPLE::getInstance().getXYtoPrint().first;
			int yPrint = CPEOPLE::getInstance().getXYtoPrint().second;

			Graphics::removePerson(road->getHorizontalLine(), road->getLaneWidth(), x, y, xPrint, yPrint);
			CPEOPLE::getInstance().updatePos(input, 3);

			CPEOPLE::getInstance().drawPlayer();
			mtx.unlock();
			break;
		}

		case PAUSE: {
			IS_PAUSING = true;
			break;
		}

		case SAVE: {
			mtx.lock();
			IS_PAUSING = true;
			for (LANE* lane : lanes)
				lane->stop();

			saveGame();

			IS_PAUSING = false;
			for (LANE* lane : lanes)
				lane->start();

			mtx.unlock();
			break;
		}

		case LOAD: {
			mtx.lock();
			IS_PAUSING = true;
			for (LANE* lane : lanes)
				lane->stop();

			int choice = Graphics::popup2Choices(xToPopUp, yToPopUp, 7, 35, "SAVE BEFORE LOADING ANOTHER GAME?");
			bool load = false;
			switch (choice) {
			case 0: {
				Graphics::closePopUp(xToPopUp, yToPopUp, 7 + 1, 35 + 1);

				IS_PAUSING = false;

				this_thread::sleep_for(seconds(2));

				for (LANE* lane : lanes)
					lane->start();
				break;
			}
			case 1: {
				Graphics::closePopUp(xToPopUp, yToPopUp, 7 + 1, 35 + 1);

				saveGame();

				load = true;
				
				break;
			}
			case 2: {
				load = true;
				break;
			}
			}

			mtx.unlock();
			if (load) {
				IS_RUNNING = false;
				for (LANE* lane : lanes)
					lane->quitGame();

				for (int i = 0; i < tLane.size(); i++)
					if (tLane[i].joinable())
						tLane[i].join();
				clearData();

				loadGame();
			}
			break;
		}

		case HELP: {
			mtx.lock();
			popUpInstructions();
			mtx.unlock();
			break;
		}
		
		}

		mtx.lock();
		for (int i = 0; i < lanes.size(); i++)
			if (lanes[i]->checkImpact(CPEOPLE::getInstance())) {
				CPEOPLE::getInstance().impacted();
				IS_RUNNING = false;
				break;
			}
		mtx.unlock();
		if (CPEOPLE::getInstance().isDead()) {
			for (LANE* lane : lanes)
				lane->stop();
			IS_RUNNING = false;
			break;
		}

		if (CPEOPLE::getInstance().isFinish()) {
			for (LANE* lane : lanes)
				lane->stop();

			sleep_for(seconds(2));

			for (int i = 0; i < tLane.size(); i++)
				if (tLane[i].joinable())
					tLane[i].join();
					
			levelUp();
		}

	}

	for (int i = 0; i < tLane.size(); i++)
		if (tLane[i].joinable())
			tLane[i].join();

	if (CPEOPLE::getInstance().isDead()) {
		clearData();
		if (Lvl != NULL) {
			delete Lvl;
			Lvl = NULL;
		}
		loseGame();
	}

	else if (!IS_RUNNING) {
		clearData();
		if (Lvl != NULL) {
			delete Lvl;
			Lvl = NULL;
		}
		Menu menu;
		menu.mainMenu();
	}
}

void CGAME::saveGame() {
	string name;
	Graphics::popupSaveGame(xToPopUp, yToPopUp, name);

	saveData(name);

	Graphics::closePopUp(xToPopUp, yToPopUp, 5, 40);

	Controller::gotoXY(xToPopUp + 2, yToPopUp + 2);
	cout << "SAVE SUCCESSFULLY";

	this_thread::sleep_for(seconds(5));

	Controller::gotoXY(xToPopUp + 2, yToPopUp + 2);
	for (int j = 0; j < 17; j++)
		cout << " ";
}

void CGAME::loadGame() {
	system("cls");

	vector <string> savedfiles;
	ifstream gather("listofsavedfiles.txt");

	if (gather) {
		string file;
		while (getline(gather, file))
			savedfiles.push_back(file);
		gather.close();
	}

	vector <string> originalList(savedfiles);

	for (string &s : savedfiles) {
		size_t posLastSlash = s.find_last_of('/');
		s = s.substr(posLastSlash + 1, s.find_last_of('.') - posLastSlash - 1);
	}

	string selectedFile = "";

	int x = 15;
	int y = 5;

	Graphics::drawReturnButton(1, 0, "HOME");
	
	int n = savedfiles.size();
	if (n == 0) {
		Controller::gotoXY(23, 7);
		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		cout << "THERE IS CURRENTLY NO SAVED FILE!";
		int choice;
		do {
			choice = Controller::getConsoleInput();
		} while (choice != LEFT && choice != ESC);
		
		Menu menu;
		menu.mainMenu();

		return;
	}

	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	Graphics::drawBorder(x - 1, y, 80, 6, 1);

	Controller::gotoXY(x - 1, y - 1);
	cout << "CHOOSE YOUR SAVED FILENAME";

	Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
	Controller::gotoXY(x, y + 7);
	cout << "Press F to find your filename.";

	vector <int> tColor(n, BLACK);
	tColor[0] = RED;
	int top = 0;
	int bottom = 4;
	int curPos = 0;
	bool passTop = false, passBottom = false;
	bool selected = false;
	bool Return = false;
		
	if (n < bottom + 1) {
		while (!selected && !Return) {
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
			case LEFT: case ESC: {
				Return = true;
				break;
			}

			case UP:
				if (curPos > 0)
					curPos--;
				break;

			case DOWN:
				if (curPos < n - 1)
					curPos++;
				break;

			case ENTER:
				selected = true;
				selectedFile = savedfiles[curPos];
				break;

			case FIND_FILENAME: {
				vector <string> suggestionName;
				string searchName;
				int XtoFind = x;
				Controller::gotoXY(XtoFind, y + 9);
				cout << "ENTER FILENAME: ";
				Controller::showCursor(true);
				getline(cin, searchName);
				Controller::showCursor(false);

				for (string s : originalList) {
					if (s.find(searchName) != string::npos)
						suggestionName.push_back(s);
				}
				
				Controller::gotoXY(XtoFind + 25, y + 10);
				Controller::setConsoleColor(BACKGROUND_COLOR, AQUA);
				cout << "HERE ARE SOME FILENAME SUGGESTIONS.";
				Controller::setConsoleColor(BACKGROUND_COLOR, PURPLE);
				Graphics::drawBorder(XtoFind - 1, y + 11, 80, 5, 1);

				Graphics::printListOfSavedFiles(XtoFind, y + 11, suggestionName, 0, 3, selectedFile);

				if (selectedFile != "") {
					selected = true;
				}
				else
					Graphics::closePopUp(XtoFind - 1, y + 9, 10, 81);

				break;
			}

			}

			for (int& color : tColor)
				color = BLACK;

			tColor[curPos] = RED;
		}
	}
	else {
		while (!selected && !Return) {
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
			case LEFT: case ESC: {
				Return = true;
				break;
			}

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
			case FIND_FILENAME: {
				vector <string> suggestionName;
				string searchName;
				int XtoFind = x;
				Controller::gotoXY(XtoFind, y + 9);
				cout << "ENTER FILENAME: ";
				Controller::showCursor(true);
				getline(cin, searchName);
				Controller::showCursor(false);

				for (string s : originalList) {
					if (s.find(searchName) != string::npos)
						suggestionName.push_back(s);
				}
				Controller::gotoXY(XtoFind + 25, y + 10);
				Controller::setConsoleColor(BACKGROUND_COLOR, AQUA);
				cout << "HERE ARE SOME FILENAME SUGGESTIONS.";
				Controller::setConsoleColor(BACKGROUND_COLOR, PURPLE);
				Graphics::drawBorder(XtoFind - 1, y + 11, 80, 5, 1);
				Graphics::printListOfSavedFiles(XtoFind, y + 11, suggestionName, 0, 3, selectedFile);

				if (selectedFile != "") {
					selected = true;
				}
				else
					Graphics::closePopUp(XtoFind - 1, y + 9, 10, 81);

				break;
			}

			}

			for (int& color : tColor)
				color = BLACK;

			tColor[curPos] = RED;
		}
	}

	if (Return) {
		Menu menu;
		menu.mainMenu();
		return;
	}

	ifstream infile("gameData/" + selectedFile + ".txt");
	string tmp;
	getline(infile, tmp);
	int lvl;
	infile >> lvl;
	infile.close();

	if (lvl > 5) {
		Controller::gotoXY(25, 25);
		winGame();
		Controller::gotoXY(30, 17);
		cout << "PLAYER: " << tmp;

		switch (Graphics::popup2Choices(40, 20, 8, 30, "LOAD ANOTHER GAME?")) {
		case 0: case 1:
			loadGame();
		case 2: {
			Menu menu;
			menu.mainMenu();
		}
		}
	}
	else {
		loadData(selectedFile);

		loadGameMode = true;
		IS_RUNNING = true;
		IS_PAUSING = true;
		startGame();
	}
}

void CGAME::saveData(string name) {
	// playerName
	// [Level]
	// x y (of person)
	// [number of Lanes]
	// [list of lane type]
	// [list of yCoords]

	// [current color of the Light of this lane]
	// [direction] (RL/LR)
	// [number of obstacle in this lane]
	// ......(x coordinates of each obstacle in a lane)
	// ......(obstacle code)

	// ....
	// ....
	// ....
	// ....
	// ....

	if (_mkdir("gameData") == -1) {
		Controller::gotoXY(xToPopUp + 2, yToPopUp + 2);
		cerr << "Error: " << strerror(errno) << endl;
	}

	string filename = "gameData/" + name + ".txt";
	
	fstream store("listOfSavedFiles.txt", ios::in | ios::app);

	unordered_set <string> content;
	string path;
	while (store >> path)
		content.insert(path);
	store.clear();
	if (content.find(filename) == content.end())
		store << filename << endl;
	store.close();

	ofstream out(filename);
	int xP = CPEOPLE::getInstance().getCoordinates().first;
	int yP = CPEOPLE::getInstance().getCoordinates().second;

	out << playerName << endl;
	out << Lvl->getCurrentLevel() << endl;
	if (Lvl->getCurrentLevel() > 5) {
		out.close();
		return;
	}

	out << xP << " " << yP << endl;
	out << lanes.size() << endl;

	for (int i = 0; i < Lvl->getTypeLane().size(); i++)
		out << Lvl->getTypeLane()[i] << " ";
	out << endl;

	for (int i = 0; i < lanes.size(); i++)
		out << lanes[i]->getYCoord() << " ";
	out << endl << endl;

	for (int i = 0; i < lanes.size(); i++) {
		switch (lanes[i]->getLightColor()) {
		case GreenLight:
			out << "G" << endl;
			break;
		case YellowLight:
			out << "Y" << endl;
			break;
		case RedLight:
			out << "R" << endl;
			break;
		case Off:
			out << "Off" << endl;
			break;
		}

		out << ((lanes[i]->getDirection() == left_right) ? "LR" : "RL") << endl;

		out << lanes[i]->getNumOfObstacles() << endl;

		vector <int> listXCoords(lanes[i]->getListXCoords());
		for (int j = 0; j < listXCoords.size(); j++)
			out << listXCoords[j] << " ";
		out << endl;

		vector <string> listObjCode(lanes[i]->getListOfCode());
		for (int j = 0; j < listObjCode.size(); j++)
			out << listObjCode[j] << " ";
		out << endl << endl;
	}

	out.close();
}

void CGAME::loadData(string name) {
	// playerName
	// [Level]
	// x y (of person)
	// [number of Lanes]
	// [list of lane type]
	// [list of yCoords]

	// [current color of the Light of this lane]
	// [direction] (RL/LR)
	// [number of obstacle in this lane]
	// ......(x coordinates of each obstacle in a lane)
	// ......(obstacle code)

	// ....
	// ....
	// ....
	// ....
	// ....

	string filename = "gameData/" + name + ".txt";
	ifstream in(filename);

	int xP, yP;
	int curLvl;
	int totalLane;

	getline(in, playerName);
	in >> curLvl;
	in >> xP >> yP;
	CPEOPLE::getInstance().setXY(xP, yP);

	Lvl->setLevel(curLvl);
	Lvl->setup();
	int animalStep = Lvl->getAnimalSteps();
	int vehicleStep = Lvl->getVehicleSteps();
	int msPerStep = Lvl->getMSecPerSteps();
	int maxRedDur = Lvl->getRedDuration();
	int maxGreenDur = Lvl->getGreenDuration();
	int maxYellowDur = Lvl->getYellowDuration();

	in >> totalLane;

	vector <int> laneType;
	for (int i = 0; i < totalLane; i++) {
		int type;
		in >> type;
		laneType.push_back(type);
	}

	vector <int> yCoords;
	for (int i = 0; i < totalLane; i++) {
		int yLane;
		in >> yLane;
		yCoords.push_back(yLane);
	}
	
	for (int i = 0; i < totalLane; i++) {
		string lightColor;
		in >> lightColor;

		int lightState;
		if (lightColor == "G")
			lightState = GreenLight;
		else if (lightColor == "Y")
			lightState = YellowLight;
		else if (lightColor == "R")
			lightState = RedLight;
		else if (lightColor == "Off")
			lightState = Off;

		string direction;
		in >> direction;

		bool direct = (direction == "LR") ? left_right : right_left;

		int numOfObstacles;
		in >> numOfObstacles;

		vector <int> listXCoords;
		for (int j = 0; j < numOfObstacles; j++) {
			int x_coord;
			in >> x_coord;
			listXCoords.push_back(x_coord);
		}

		vector <string> listOfCode;
		for (int j = 0; j < numOfObstacles; j++) {
			string objCode;
			in >> objCode;
			listOfCode.push_back(objCode);
		}

		vector <OBSTACLE*> v;
		for (int j = 0; j < numOfObstacles; j++) {
			OBSTACLE* p = NULL;
			string s = listOfCode[j];
			string obj = s.substr(0, s.length() - 1);
			int type = stoi(s.substr(s.length() - 1));
			
			if (obj == "car") {
				p = new CCAR(listXCoords[j], yCoords[i], type, direct);
			}
			else if (obj == "truck") {
				p = new CTRUCK(listXCoords[j], yCoords[i], type, direct);
			}
			else if (obj == "bird") {
				p = new CBIRD(listXCoords[j], yCoords[i], type, direct);
			}
			else if (obj == "dino") {
				p = new CDINOSAUR(listXCoords[j], yCoords[i], type, direct);
			}

			v.push_back(p);
		}

		lanes.push_back(new LANE(direct, yCoords[i], (laneType[i] == VEHICLECODE) ? vehicleStep : animalStep, msPerStep, v));
		lanes.back()->setLightColor(lightState);
		if (laneType[i] == VEHICLECODE)
			lanes.back()->setLightDuration(maxGreenDur, maxYellowDur, maxRedDur);

	}
	in.close();

	vector <int> laneWidth;
	int k = UPPER_BOUND;
	for (int i = 0; i < laneType.size(); i++) {
		if (laneType[i] == VEHICLECODE)
			laneWidth.push_back(7);
		else if (laneType[i] == ANIMALCODE)
			laneWidth.push_back(8);
		k += laneWidth.back();
	}
	Lvl->setTypeLane(laneType);
	Lvl->setlaneWidth(laneWidth);
	road = new CROAD(laneWidth);
	LOWER_BOUND = k;
}

void CGAME::pauseGame() {
	for (LANE* lane : lanes)
		lane->stop();

	Graphics::popupPause(xToPopUp, yToPopUp);

	int input;
	do {
		input = Controller::getConsoleInput();
	}while (input != ENTER && input != HELP);

	Graphics::closePopUp(xToPopUp, yToPopUp, 10, 36);

	if (input == HELP) {
		popUpInstructions();
		return;
	}

	IS_PAUSING = false;

	this_thread::sleep_for(seconds(2));

	for (LANE* lane : lanes)
		lane->start();
}

void CGAME::popUpInstructions() {
	IS_PAUSING = true;
	for (LANE* lane : lanes)
		lane->stop();

	Graphics::popupHelpBoard(xToPopUp, yToPopUp);

	while (Controller::getConsoleInput() != ENTER);

	Graphics::closePopUp(xToPopUp, yToPopUp, 10, 35);

	IS_PAUSING = false;

	this_thread::sleep_for(seconds(2));

	for (LANE* lane : lanes)
		lane->start();
}

void CGAME::loseGame() {
	Graphics::loseGameAnimation();

	switch (Graphics::popup2Choices(72,16, 7, 30, "PLAY AGAIN?")) {
	case 0: case 1: {
		Menu menu;
		menu.mainMenu();
		break;
	}
	case 2: {
		Menu menu;
		menu.exitGame();
		break;
	}
	}
}

void CGAME::winGame() {
	system("cls");
	const char msg[] = R"(
	__     __                          ____       _____         U  ___ u       ____          __   __ 
	\ \   /"/u          ___         U /"___|     |_ " _|         \/"_ \/    U |  _"\ u       \ \ / / 
	 \ \ / //          |_"_|        \| | u         | |           | | | |     \| |_) |/        \ V /  
	 /\ V /_,-.         | |          | |/__       /| |\      .-,_| |_| |      |  _ <         U_|"|_u 
	U  \_/-(_/        U/| |\u         \____|     u |_|U       \_)-\___/       |_| \_\          |_|   
	  //           .-,_|___|_,-.     _// \\      _// \\_           \\         //   \\_     .-,//|(_  
	 (__)           \_)-' '-(_/     (__)(__)    (__) (__)         (__)       (__)  (__)     \_) (__) 
	)";

	Controller::setConsoleColor(BACKGROUND_COLOR, AQUA);
	Controller::gotoXY(2, 1);
	cout << msg;

	vector <string> congrat(6);
		
	congrat[0] = R"(   ______                             __        __      __  _           )";
	congrat[1] = R"(  / ____/___  ____  ____ __________ _/ /___  __/ /___ _/ /_(_)___  ____ )";
	congrat[2] = R"( / /   / __ \/ __ \/ __ `/ ___/ __ `/ __/ / / / / __ `/ __/ / __ \/ __ \)";
	congrat[3] = R"(/ /___/ /_/ / / / / /_/ / /  / /_/ / /_/ /_/ / / /_/ / /_/ / /_/ / / / /)";
	congrat[4] = R"(\____/\____/_/ /_/\__, /_/   \__,_/\__/\__,_/_/\__,_/\__/_/\____/_/ /_/ )";
	congrat[5] = R"(                 /____/                                                 )";


	for (size_t i = 0, color = BLACK; i < congrat.size(); i++, color++) {
		if (color == 14)
			color = BLACK;
		Controller::setConsoleColor(BACKGROUND_COLOR, color);
		Controller::gotoXY(25, 10 + i);
		cout << congrat[i];
	}
}