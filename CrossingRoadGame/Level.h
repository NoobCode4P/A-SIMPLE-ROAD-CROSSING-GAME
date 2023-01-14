#pragma once
#include <vector>
#include <ctime>
using namespace std;

#define MAX_LEVEL 5
#define VEHICLECODE 0
#define ANIMALCODE 1


class Level {
	int level;
	int totalLane;
	int animalLane;
	int vehicleLane;
	vector <int> typeLane;
	vector <int> laneWidth;

	int vehicleSteps, animalSteps;
	int msecPerStep;
	int maxRedDuration, maxGreenDuration, maxYellowDuration;

	void level1();
	void level2();
	void level3();
	void level4();
	void level5();

public:
	Level() {};
	Level(int);
	int getCurrentLevel() const;
	void setup();
	void setLevel(int level);
	void setTypeLane(const vector <int> &type);
	void setlaneWidth(const vector <int> &laneWidth);

	int getTotalLane() const;
	int getNumALane() const;
	int getNumVLane() const;
	int getVehicleSteps() const;
	int getAnimalSteps() const;
	int getMSecPerSteps() const;

	int getRedDuration() const;
	int getGreenDuration() const;
	int getYellowDuration() const;

	vector <int> getTypeLane() const;
	vector <int> getlaneWidth() const;

	void generateRandomLane();

	void updateLevel(int level);
};