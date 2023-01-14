#pragma once
#include "OBSTACLE.h"

#define MAXCAR 3

#define Sedan 0
#define Convertible 1
#define Limousine 2

class CCAR : public OBSTACLE {
private:
	const vector <pair <int, int>> CarModel = { {4,14} , {3,15}, {4,28} };
	int type;

	void DesignModel(int);
public:
	CCAR(int x, int y, int type, bool direction);
	~CCAR();

	char **getShape();
	int getHeight() const;
	int getLength() const;
	string getCode() const;
	void makeSound();
};