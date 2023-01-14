#include "Level.h"

Level::Level(int level) {
	this->level = level;
	setup();
	generateRandomLane();
}

int Level::getCurrentLevel() const {
	return level;
}

void Level::level1() {
	totalLane = 2;
	animalLane = 0;
	vehicleLane = 2;

	vehicleSteps = 6;
	animalSteps = 0;
	msecPerStep = 800;

	maxRedDuration = 6;
	maxGreenDuration = 5;
	maxYellowDuration = 5;
}

void Level::level2() {
	totalLane = 2;
	animalLane = 1;
	vehicleLane = 1;

	vehicleSteps = 6;
	animalSteps = 6;
	msecPerStep = 700;

	maxRedDuration = 5;
	maxGreenDuration = 6;
	maxYellowDuration = 4;
}

void Level::level3() {
	totalLane = 2;
	animalLane = 2;
	vehicleLane = 0;

	vehicleSteps = 7;
	animalSteps = 8;
	msecPerStep = 600;

	maxRedDuration = 4;
	maxGreenDuration = 8;
	maxYellowDuration = 2;
}

void Level::level4() {
	totalLane = 3;
	animalLane = 2;
	vehicleLane = 1;

	vehicleSteps = 7;
	animalSteps = 8;
	msecPerStep = 400;

	maxRedDuration = 3;
	maxGreenDuration = 10;
	maxYellowDuration = 2;
}

void Level::level5() {
	totalLane = 3;
	animalLane = 3;
	vehicleLane = 0;

	vehicleSteps = 7;
	animalSteps = 9;
	msecPerStep = 400;

	maxRedDuration = 2;
	maxGreenDuration = 10;
	maxYellowDuration = 2;
}

void Level::setup() {
	switch (level) {
	case 1: {
		level1();
		break;
	}
	case 2: {
		level2();
		break;
	}
	case 3: {
		level3();
		break;
	}

	case 4: {
		level4();
		break;
	}

	case 5: {
		level5();
		break;
	}

	}
}

void Level::setLevel(int level) {
	this->level = level;
}

void Level::setlaneWidth(const vector <int> &laneWidth) {
	this->laneWidth = laneWidth;
}

void Level::setTypeLane(const vector <int> &type) {
	this->typeLane = type;
}

int Level::getTotalLane() const{
	return totalLane;
}

int Level::getNumALane() const {
	return animalLane;
}

int Level::getNumVLane() const {
	return vehicleLane;
}

int Level::getAnimalSteps() const {
	return animalSteps;
}

int Level::getVehicleSteps() const {
	return vehicleSteps;
}

int Level::getMSecPerSteps() const {
	return msecPerStep;
}

int Level::getRedDuration() const {
	return maxRedDuration;
}

int Level::getGreenDuration() const {
	return maxGreenDuration;
}

int Level::getYellowDuration() const {
	return maxYellowDuration;
}

vector <int> Level::getTypeLane() const {
	return typeLane;
}

vector <int> Level::getlaneWidth() const {
	return laneWidth;
}

void Level::generateRandomLane() {
	if (!typeLane.empty())
		typeLane.clear();
	if (!laneWidth.empty())
		laneWidth.clear();

	typeLane.resize(totalLane);
	laneWidth.resize(totalLane);

	int mp[2];
	mp[VEHICLECODE] = vehicleLane;
	mp[ANIMALCODE] = animalLane;

	srand(time(NULL));
	for (int i = 0; i < totalLane; i++) {
		int x = rand() % 2;
		while (mp[x] == 0)
			x = rand() % 2;

		typeLane[i] = x;
		if (x == VEHICLECODE) {
			laneWidth[i] = 7;
			mp[x]--;
		}
		else {
			laneWidth[i] = 8;
			mp[x]--;
		}
	}
}

void Level::updateLevel(int level) {
	this->level = level;
	setup();
	generateRandomLane();
}
