#pragma once

#include "CCAR.h"
#include "CTRUCK.h"
#include "CBIRD.h"
#include "CDINOSAUR.h"
#include "TrafficLight.h"
#include <deque>
#include <thread>
#include <mutex>
extern mutex mtx;
using namespace this_thread;
using namespace chrono;

#define left_right true
#define right_left false


class LANE {
private:
	deque <OBSTACLE*> lane;
	TrafficLight light;

	bool direction;
	int movingSteps;
	int msPerStep;
	
	int y;
	
	bool quit = false;
	bool isCirculated;

	void generateVehicleFromLeft();
	void generateVehicleFromRight();
	void generateAnimalFromLeft();
	void generateAnimalFromRight();

	void resettingCoordinatesOfTheFrontObj();
	void resettingCoordinatesOfTheBackObj();

public:
	LANE();
	~LANE();
	LANE(bool direction, int y, int movingSteps, int msPerStep);
	LANE(bool direction, int y, int movingSteps, int msPerStep, vector <OBSTACLE*>);

	vector <int> getListXCoords() const;
	bool getDirection() const;
	int getLightColor() const;
	int getSize() const;
	int getNumOfObstacles() const;
	int getYCoord() const;
	vector <string> getListOfCode() const;

	void setLightDuration(int G, int Y, int R);
	void setLightColor(int color);
	void start();
	void stop();
	void quitGame();
	void printCurrentObstacle();
	void printLight();

	void pushLeft(OBSTACLE *);
	void pushRight(OBSTACLE *);

	void shiftRight_Vehicle(int unit);
	void shiftLeft_Vehicle(int unit);

	void shiftRight_Animal(int unit);
	void shiftLeft_Animal(int unit);

	bool checkImpact(const CPEOPLE&);

	void lightOperation();
	void vehicleFlow();
	void animalFlow();

	void circulateV();
	void circulateA();

};