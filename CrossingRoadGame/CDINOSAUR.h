#pragma once
#include "OBSTACLE.h"

#define MAXDINO 3

#define Stegosaurus 0
#define Ceratosaurus 1
#define Pterodactyl 2

class CDINOSAUR : public OBSTACLE {
private:
	const vector <pair <int, int>> Dino = { {6,27}, {6,49}, {6,22} };
	int type;

	void formShape(int);
public:
	CDINOSAUR(int x, int y, int type, bool direction);
	~CDINOSAUR();

	char **getShape();
	int getHeight() const;
	int getLength() const;
	string getCode() const;
	void makeSound();
};