#include "CTRUCK.h"

CTRUCK::CTRUCK(int x, int y, int type, bool direction) : OBSTACLE(x,y, direction) {
	DesignModel(type);
	if (rightToLeft) {
		Graphics::switchDirection(shape, height, length);
		if (type == ContainerTruck) {
			string msg = "IT'S TIME TO ISEKAI!!!";
			for (int j = 0; j < msg.length(); j++) {
				shape[2][length - 4 - msg.length() + j] = msg[j];
			}
		}
	}
	this->type = type;
}

CTRUCK::~CTRUCK() {
	for (int i = 0; i < height; i++)
		delete[] shape[i];
	delete[] shape;
}

void CTRUCK::DesignModel(int type) {
	height = TruckModel[type].first;
	length = TruckModel[type].second;

	shape = new char*[height];
	for (int i = 0; i < height; i++)
		shape[i] = new char[length];

	int row = height;
	int col = length;

	if (type == MiniTruck) {
		//  ________   ___   
		// |        | |[_\\_
		// |________|_|_____|
		//   O    O		  O

		//=============Draw the container============
		
		int boxLength = (col >> 1) + 1;
		int posLeftWheel = boxLength / 3 - 1;
		int posRightWheel = boxLength - (boxLength / 3);
		for (int i = 0; i < row; i++)
			for (int j = 0; j < boxLength; j++) {
				if ((i == 0 || i == row - 2) && (1 <= j && j < boxLength - 1))
					shape[i][j] = '_';

				else if ((j == 0 || j == boxLength - 1) && (0 < i && i <= row - 2))
					shape[i][j] = '|';

				else if (i == row - 1 && (j == posLeftWheel || j == posRightWheel))
					shape[i][j] = 'O';

				else
					shape[i][j] = ' ';
			}
		

		//=============Draw truck's head=============
		int headLength = col - boxLength;
		int posFrontWheel = boxLength + (headLength >> 1) + 1;
		int ceilLength = headLength * 2 / 3;
		
		
		//*********The ceiling***********
		for (int j = boxLength; j < col; j++) {
			if (boxLength + 2 <= j && j < boxLength + ceilLength)
				shape[0][j] = '_';
			else
				shape[0][j] = ' ';
		}

		//*********The front wheel*********
		for (int j = boxLength; j < col; j++)
			shape[row - 1][j] = (j == posFrontWheel) ? 'O' : ' ';

		//*********The bottom of the truckroom******
		for (int j = boxLength; j < col; j++) {
			if (j == boxLength)
				shape[row - 2][j] = '_';
			else if (j == boxLength + 1 || j == col - 1)
				shape[row - 2][j] = '|';
			else
				shape[row - 2][j] = '_';
		}

		//********The glass************
		int glassHeight = row / 3;
		int glassWidth = ceilLength - 4;
		
		for (int i = 1; i < glassHeight + 1; i++) {
			for (int j = boxLength; j < col; j++) {
				
				if (j == boxLength)
					shape[i][j] = ' ';

				else if (j == boxLength + 1)
					shape[i][j] = '|';

				else if (j == boxLength + 2)
					shape[i][j] = '[';

				else if (boxLength + 2 < j && j <= boxLength + 2 + glassWidth || (i == glassHeight && j == col - 2))
					shape[i][j] = (i == glassHeight) ? '_' : ' ';

				else if (j == boxLength + 2 + glassWidth + 1 || j == boxLength + 2 + glassWidth + 2)
					shape[i][j] = '\\';

				else
					shape[i][j] = ' ';
				
			}
			glassWidth++;
		}

		//*******The side door*********
		for (int i = glassHeight + 1; i < row - 2; i++) {
			for (int j = boxLength; j < col; j++) {
				if (j == boxLength)
					shape[i][j] = ' ';
				else if (j == boxLength + 1 || j == col - 1)
					shape[i][j] = '|';
				else
					shape[i][j] = ' ';
			}
		}

	}

	else if (type == Ambulance) {
		//  _____________
		// |    _| |_    |_]o[_
		// |   |_   _|   | |___\__
		// |     |_|     |       '|
		// |___ _ _______|_ _ ____|
		//    `(0)'        `(0)'

		string line[6];
		line[0] = " _____________          ";
		line[1] = "|    _| |_    |_]o[_    ";
		line[2] = "|   |_   _|   | |___\\__ ";
		line[3] = "|     |_|     |       '|";
		line[4] = "|___ _ _______|__ _ ___|";
		line[5] = "   `(0)'        `(0)'   ";

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				shape[i][j] = line[i][j];
	}

	else if (type == ContainerTruck) {
		//  ___________________________   ___
		// |                           | |___\__
		// |   IT'S TIME TO ISEKAI!!!  | |     '|
		// |___________________________|=|______|
		//    (0)(0)(0) `-----' (0)(0)     (0)

		string line[5];
		line[0] = " ___________________________   ___    ";
		line[1] = "|                           | |___\\__ ";
		line[2] = "|   IT'S TIME TO ISEKAI!!!  | |     '|";
		line[3] = "|___________________________|=|______|";
		line[4] = "   (0)(0)(0) `-----' (0)(0)     (0)   ";

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				shape[i][j] = line[i][j];
	}

}

int CTRUCK::getHeight() const {
	return height;
}

int CTRUCK::getLength() const {
	return length;
}

char ** CTRUCK::getShape() {	
	char **tmp = new char*[height];
	for (int i = 0; i < height; i++)
		tmp[i] = new char[length];
	for (int i = 0; i < height; i++)
		for (int j = 0; j < length; j++)
			tmp[i][j] = shape[i][j];
	return tmp;
}

string CTRUCK::getCode() const {
	return "truck" + to_string(type);
}

void CTRUCK::makeSound() {
	switch (type) {
	case MiniTruck: case ContainerTruck:
		Sound::impactSound(truckHorn);
		break;
	case Ambulance:
		Sound::impactSound(ambulanceSound);
		break;
	}
}