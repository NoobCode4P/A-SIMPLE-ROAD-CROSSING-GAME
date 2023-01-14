#pragma once
#include "OBSTACLE.h"

#define MAXTRUCK 3

#define MiniTruck 0
#define Ambulance 1
#define ContainerTruck 2

class CTRUCK : public OBSTACLE {
private:
	const vector <pair <int, int>> TruckModel = { {4,15}, {6,24}, {5,38} };
	int type;

	void DesignModel(int);
public:
	CTRUCK(int x, int y, int type, bool direction);
	~CTRUCK();
	
	char **getShape();
	int getHeight() const;
	int getLength() const;
	string getCode() const;
	void makeSound();
};