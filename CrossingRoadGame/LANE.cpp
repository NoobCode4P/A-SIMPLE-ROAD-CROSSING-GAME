#include "LANE.h"

LANE::LANE() {

}

LANE::LANE(bool Direction, int y, int movingSteps, int msPerStep) {
	direction = Direction;
	this->y = y;
	this->movingSteps = movingSteps;
	this->msPerStep = msPerStep;

	for (int i = 0; i < 3; i++)
		lane.push_front(NULL);
}

LANE::LANE(bool Direction, int y, int movingSteps, int msPerStep, vector <OBSTACLE*> v) {
	direction = Direction;
	this->y = y;
	this->movingSteps = movingSteps;
	this->msPerStep = msPerStep;

	for (int idx = 0; idx < v.size(); idx++)
		lane.push_back(v[idx]);
}

LANE::~LANE() {
	while (!lane.empty()) {
		OBSTACLE *tmp = lane.front();
		lane.pop_front();
		delete tmp;
	}
}

vector <int> LANE::getListXCoords() const {
	vector <int> xcoords;
	for (int i = 0; i < lane.size(); i++)
		if (lane[i])
			xcoords.push_back(lane[i]->getCoordinates().first);
	return xcoords;
}

bool LANE::getDirection() const {
	return direction;
}

int LANE::getLightColor() const{
	return light.getCurrentColor();
}

int LANE::getSize() const {
	return lane.size();
}

int LANE::getNumOfObstacles() const {
	int count = 0;
	for (int i = 0; i < lane.size(); i++)
		if (lane[i] != NULL)
			count++;
	return count;
}

int LANE::getYCoord() const {
	return y;
}

vector <string> LANE::getListOfCode() const {
	vector <string> code;
	for (int i = 0; i < lane.size(); i++)
		if (lane[i])
			code.push_back(lane[i]->getCode());
	return code;
}

void LANE::setLightDuration(int green, int yellow, int red) {
	light.setMaximumDuration(green, yellow, red);
}

void LANE::setLightColor(int color) {
	light.setColor(color);
}

void LANE::start() {
	isCirculated = true;
}

void LANE::stop() {
	isCirculated = false;
}

void LANE::quitGame() {
	quit = true;
}

void LANE::printCurrentObstacle() {
	for (int i = 0; i < lane.size(); i++) {
		if (lane[i]) {
			int x = lane[i]->getXYtoPrint().first;
			int Y = lane[i]->getXYtoPrint().second;
			int height = lane[i]->getHeight();
			int length = lane[i]->getLength();
			Graphics::printValidPartOfObj(x, Y, lane[i]->getShape(), height, length);
		}
	}
}

void LANE::printLight() {
	light.printLight(RIGHT_BOUND + 2, this->y - 4);
}

void LANE::pushLeft(OBSTACLE * v) {
	lane.push_front(v);
	int size = lane.size();
	for (int i = size - 1; i >= 0; i--) {
		OBSTACLE *tmp = lane[i];
		if (i == size - 1 && tmp == NULL)
			lane.pop_back();
		else if (tmp) {
			int x = tmp->getCoordinates().first;
			int length = tmp->getLength();
			if (RIGHT_BOUND + length < x)
				lane.erase(lane.begin() + i);
			else return;
		}
		delete tmp;
	}
}

void LANE::pushRight(OBSTACLE * v) {
	lane.push_back(v);
	for (int i = 0; i < lane.size(); i++) {
		OBSTACLE* tmp = lane[i];
		if (i == 0 && tmp == NULL)
			lane.pop_front();
		else if (tmp) {
			int x = tmp->getCoordinates().first;
			int length = tmp->getLength();
			if (x < LEFT_BOUND - length)
				lane.erase(lane.begin() + i);
			else return;
		}
		delete tmp;
	}
}

void LANE::generateVehicleFromLeft() {
	srand(time(NULL));

	if (rand() % 2 == 1) {
		if (rand() % 2 == 1) {
			int type = rand() % MAXCAR;
			pushLeft(new CCAR(LEFT_BOUND - 1, y, type, left_right));
		}
		else {
			int type = rand() % MAXTRUCK;
			pushLeft(new CTRUCK(LEFT_BOUND - 1, y, type, left_right));
		}
	}
	else
		pushLeft(NULL);
}

void LANE::generateVehicleFromRight() {
	srand(time(NULL));
	if (rand() % 2 == 1) {
		if (rand() % 2 == 1) {
			int type = rand() % MAXCAR;
			pushRight(new CCAR(RIGHT_BOUND + 1, y, type, right_left));
		}
		else {
			int type = rand() % MAXTRUCK;
			pushRight(new CTRUCK(RIGHT_BOUND + 1, y, type, right_left));
		}
	}
	else
		pushRight(NULL);
}

void LANE::generateAnimalFromLeft() {
	srand(time(NULL));

	if (rand() % 2 == 1) {
		if (rand() % 2 == 1) {
			int species = rand() % MAXDINO;
			pushLeft(new CDINOSAUR(LEFT_BOUND - 1, y, species, left_right));
		}
		else {
			int type = rand() % MAXBIRD;
			pushLeft(new CBIRD(LEFT_BOUND - 1, y, type, left_right));
		}
	}
	else
		pushLeft(NULL);
}

void LANE::generateAnimalFromRight() {
	srand(time(NULL));

	if (rand() % 2 == 1) {
		if (rand() % 2 == 1) {
			int species = rand() % MAXDINO;
			pushRight(new CDINOSAUR(RIGHT_BOUND + 1, y, species, right_left));
		}
		else {
			int type = rand() % MAXBIRD;
			pushRight(new CBIRD(RIGHT_BOUND + 1, y, type, right_left));
		}
	}
	else
		pushRight(NULL);
}

void LANE::resettingCoordinatesOfTheFrontObj() {
	if (lane.front() != NULL) {
		int i = 1;
		int count0 = 0;
		while (i < lane.size() && lane[i] == NULL) {
			count0++;
			i++;
		}
		if (i < lane.size()) {
			int dist0 = (i == 1) ? 0 : (count0 * (lane[i]->getLength() - 1));
			int x = lane[i]->getCoordinates().first - lane[i]->getLength() / 2 - lane.front()->getLength() / 2 - 3 - dist0;
			lane.front()->setPos(x, lane[i]->getCoordinates().second);
		}
	}
}

void LANE::resettingCoordinatesOfTheBackObj() {
	if (lane.back() != NULL) {
		int i = lane.size() - 2;
		int count0 = 0;
		while (i >= 0 && lane[i] == NULL) {
			i--;
			count0++;
		}
		if (i >= 0) {
			int dist0 = (i == 1) ? 0 : (count0 * (lane[i]->getLength() + 1));
			int x = lane[i]->getCoordinates().first + lane[i]->getLength() / 2 + lane.back()->getLength() / 2 + 3 + dist0;
			lane.back()->setPos(x, lane[i]->getCoordinates().second);
		}
	}
}

void LANE::shiftRight_Vehicle(int unit) {
	
	generateVehicleFromLeft();

	//==========Resetting coordinates of the latest pushed vehicle======

	resettingCoordinatesOfTheFrontObj();
	
	//=========each vehicle moves to a new position========
	for (int i = lane.size() - 1; i >= 0 && !CPEOPLE::getInstance().isDead(); i--)
		if (lane[i] != NULL)
			lane[i]->Move(unit);
}

void LANE::shiftLeft_Vehicle(int unit) {

	generateVehicleFromRight();

	//==========Resetting coordinates of the latest pushed vehicle======
	
	resettingCoordinatesOfTheBackObj();

	//=========each vehicle moves to a new position========
	for (int i = 0; i < lane.size() && !CPEOPLE::getInstance().isDead(); i++)
		if (lane[i] != NULL)
			lane[i]->Move(unit);
}

void LANE::shiftRight_Animal(int unit) {
	
	generateAnimalFromLeft();

	//==========Resetting coordinates of the latest pushed animal======

	resettingCoordinatesOfTheFrontObj();

	//=========each animal moves to a new position========
	for (int i = lane.size() - 1; i >= 0 && !CPEOPLE::getInstance().isDead(); i--)
		if (lane[i] != NULL)
			lane[i]->Move(unit);
}

void LANE::shiftLeft_Animal(int unit) {
	
	generateAnimalFromRight();

	//==========Resetting coordinates of the latest pushed animal======

	resettingCoordinatesOfTheBackObj();

	//=========each animal moves to a new position========
	for (int i = 0; i < lane.size() && !CPEOPLE::getInstance().isDead(); i++)
		if (lane[i] != NULL)
			lane[i]->Move(unit);
}

bool LANE::checkImpact(const CPEOPLE& p) {
	for (int i = 0; i < lane.size(); i++)
		if (lane[i] && lane[i]->isImpact(p)) {
			lane[i]->makeSound();
			return true;
		}
	return false;
}

void LANE::lightOperation() {
	if (!light.isOn())
		light.activate();

	int X = RIGHT_BOUND + 2;
	int Y = this->y - 4;

	int red = light.timeForRed();
	int green = light.timeForGreen();
	int yellow = light.timeForYellow();

	while (isCirculated) {
		mtx.lock();
		light.printLight(X, Y);
		mtx.unlock();
		if (light.isGreen())
			sleep_for(seconds(green));
		else if (light.isYellow())
			sleep_for(seconds(yellow));
		else if (light.isRed())
			sleep_for(seconds(red));
		mtx.lock();
		light.switchLight();
		mtx.unlock();
	}
	light.deactivate();
}

void LANE::vehicleFlow() {
	if (direction == right_left) {
		while (isCirculated) {
			if (CPEOPLE::getInstance().isDead()){
				isCirculated = false;
				break;
			}

			mtx.lock();

			switch (light.getCurrentColor()) {
			case GreenLight: {
				shiftLeft_Vehicle(movingSteps);
				break;
			}
			case YellowLight:{
				shiftLeft_Vehicle(movingSteps - 4);
				break;
			}
			case RedLight: {
				break;
			}
			case Off:
				isCirculated = false;
				break;
			}

			if (checkImpact(CPEOPLE::getInstance()))
				CPEOPLE::getInstance().impacted();

			mtx.unlock();

			if (CPEOPLE::getInstance().isDead()) {
				isCirculated = false;
				break;
			}
			
			sleep_for(milliseconds(msPerStep));			
		}
	}
	else if (direction == left_right) {
		while (isCirculated) {
			if (CPEOPLE::getInstance().isDead()) {
				isCirculated = false;
				break;
			}

			mtx.lock();

			switch (light.getCurrentColor()) {
			case GreenLight: {
				shiftRight_Vehicle(movingSteps);
				break;
			}
			case YellowLight: {
				shiftRight_Vehicle(movingSteps - 4);
				break;
			}
			case RedLight: {
				break;
			}
			case Off:
				isCirculated = false;
				break;
			}

			if (checkImpact(CPEOPLE::getInstance()))
				CPEOPLE::getInstance().impacted();

			mtx.unlock();

			if (CPEOPLE::getInstance().isDead()) {
				isCirculated = false;
				break;
			}
			sleep_for(milliseconds(msPerStep));			
		}
	}
}

void LANE::animalFlow() {
	if (direction == right_left) {
		while (isCirculated) {
			if (CPEOPLE::getInstance().isDead()) {
				isCirculated = false;
				break;
			}
		
			mtx.lock();

			shiftLeft_Animal(movingSteps);

			if (checkImpact(CPEOPLE::getInstance()))
				CPEOPLE::getInstance().impacted();

			mtx.unlock();

			if (CPEOPLE::getInstance().isDead()){
				isCirculated = false;
				break;
			}
			sleep_for(milliseconds(msPerStep));
		}
	}
	else if (direction == left_right) {
		while (isCirculated) {
			if (CPEOPLE::getInstance().isDead()) {
				isCirculated = false;
				break;
			}

			mtx.lock();

			shiftRight_Animal(movingSteps);

			if (checkImpact(CPEOPLE::getInstance()))
				CPEOPLE::getInstance().impacted();

			mtx.unlock();

			if (CPEOPLE::getInstance().isDead()){
				isCirculated = false;
				break;
			}
			sleep_for(milliseconds(msPerStep));
		}
	}
}

void LANE::circulateV() {
	thread tLight([&] {
		while (!CPEOPLE::getInstance().isDead() && !CPEOPLE::getInstance().isFinish() && !quit)
			lightOperation(); 
	});
	thread tVehicle([&] {
		while (!CPEOPLE::getInstance().isDead() && !CPEOPLE::getInstance().isFinish() && !quit)
			vehicleFlow(); 
	});

	tLight.join();
	tVehicle.join();
}

void LANE::circulateA() {
	thread tAnimal([&] {
		while (!CPEOPLE::getInstance().isDead() && !CPEOPLE::getInstance().isFinish() && !quit)
			animalFlow(); 
	});

	tAnimal.join();
}
