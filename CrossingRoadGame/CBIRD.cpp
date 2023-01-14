#include "CBIRD.h"

CBIRD::CBIRD(int x, int y, int type, bool direction) : OBSTACLE(x,y,direction) {
	formShape(type);
	if (rightToLeft)
		Graphics::switchDirection(shape, height, length);
	this->type = type;
}

CBIRD::~CBIRD() {
	for (int i = 0; i < height; i++)
		delete[] shape[i];
	delete[] shape;
}

void CBIRD::formShape(int type) {
	height = Bird[type].first;
	length = Bird[type].second;

	shape = new char*[height];
	for (int i = 0; i < height; i++)
		shape[i] = new char[length];

	int row = height;
	int col = length;

	if (type == LongtailedBird) {
		//  ____   __
		//  \_  \ / /
		//    \_ \ /_
		//  <===\____'>

		string line[4];
		line[0] = "____   __  ";
		line[1] = "\\_  \\ / /  ";
		line[2] = "  \\_ \\ /_  ";
		line[3] = "<===\\____'>";

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				shape[i][j] = line[i][j];
	}

	else if (type == LargeHummingbird) {
		//      .
		//     /|
		//    / |__
		// +==____..`-- 

		string line[4];
		line[0] = "     .      ";
		line[1] = "    /|      ";
		line[2] = "   / |__    ";
		line[3] = "+==____..`--";

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				shape[i][j] = line[i][j];
	}

	else if (type == Flamingo) {
		//       ___    __
		//       \_ \  /_/
		//         \ \//_______
		// +========`__.-------'>

		string line[4];
		line[0] = "      ___    __       ";
		line[1] = "      \\_ \\  /_/       ";
		line[2] = "        \\ \\//_______  ";
		line[3] = "+========`__.-------'>";

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				shape[i][j] = line[i][j];
	}
}

int CBIRD::getHeight() const {
	return height;
}

int CBIRD::getLength() const {
	return length;
}

char ** CBIRD::getShape(){
	char **tmp = new char*[height];
	for (int i = 0; i < height; i++)
		tmp[i] = new char[length];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < length; j++)
			tmp[i][j] = shape[i][j];
	return tmp;
}

string CBIRD::getCode() const {
	return "bird" + to_string(type);
}

void CBIRD::makeSound() {
	switch (type) {
	case LongtailedBird: case Flamingo: {
		Sound::impactSound(impactBird);
		break;
	}
	case LargeHummingbird: {
		Sound::impactSound(impactHummingBird);
		break;
	}
	}
}