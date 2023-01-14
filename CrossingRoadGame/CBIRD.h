#pragma once
#include "OBSTACLE.h"

#define MAXBIRD 3

#define LongtailedBird 0
#define LargeHummingbird 1
#define Flamingo 2

class CBIRD :public OBSTACLE {
private:
	const vector <pair <int, int>> Bird = { {4,11}, {4,12}, {4,22} };
	int type;

	void formShape(int);
public:
	CBIRD(int x, int y, int type, bool direction);
	~CBIRD();

	char **getShape();
	int getHeight() const;
	int getLength() const;
	string getCode() const;
	void makeSound();
};