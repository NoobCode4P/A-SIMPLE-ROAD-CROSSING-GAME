#include "CCAR.h"

CCAR::CCAR(int x, int y, int type, bool direction) : OBSTACLE(x, y, direction) {
	DesignModel(type);
	if (rightToLeft) {
		Graphics::switchDirection(shape, height, length);
	}
	this->type = type;
}

CCAR::~CCAR() {
	for (int i = 0; i < height; i++)
		delete[] shape[i];
	delete [] shape;
}

void CCAR::DesignModel(int type) {
	height = CarModel[type].first;
	length = CarModel[type].second;

	shape = new char*[height];
	for (int i = 0; i < height; i++)
		shape[i] = new char[length];

	int row = height;
	int col = length;

	if (type == Sedan) {
		//    ______
		//   /|_||_\`.__
		//  (   _    _  _\
		//	=`-(_)--(_)-'


		//===============Drawing the Last Row====================
		if (col & 1)
			shape[row - 1][col >> 1] = '-';

		//******Fixed wheel with 3 cells********
		int Mid_LeftWheel = col / 3;
		int Mid_RightWheel = col - (col / 3);
		int OpenPar_LeftWheel = Mid_LeftWheel - 1;
		int OpenPar_RightWheel = Mid_RightWheel - 1;
		int ClosePar_LeftWheel = Mid_LeftWheel + 1;
		int ClosePar_RightWheel = Mid_RightWheel + 1;

		for (int l = (col >> 1) - 1, r = (col & 1) ? ((col >> 1) + 1) : (col >> 1); 0 <= l && r < col; l--, r++) {
			if (l == Mid_LeftWheel)
				shape[row - 1][l] = '_';

			else if (l == ClosePar_LeftWheel)
				shape[row - 1][l] = ')';

			else if (l == OpenPar_LeftWheel)
				shape[row - 1][l] = '(';

			else {
				switch (l) {
				case 0:
					shape[row - 1][l] = '=';
					break;
				case 1:
					shape[row - 1][l] = '`';
					break;
				default:
					shape[row - 1][l] = '-';
				}
			}

			if (r == Mid_RightWheel)
				shape[row - 1][r] = '_';

			else if (r == OpenPar_RightWheel)
				shape[row - 1][r] = '(';

			else if (r == ClosePar_RightWheel)
				shape[row - 1][r] = ')';

			else {
				if (r == col - 2)
					shape[row - 1][r] = '\'';
				else if (r == col - 1)
					shape[row - 1][r] = ' ';
				else
					shape[row - 1][r] = '-';
			}
		}

		//===============Draw the second Last Row=====================
		for (int j = 0; j < col; j++) {
			if (j == 0)
				shape[row - 2][j] = '(';
			else if (j == Mid_LeftWheel || j == Mid_RightWheel || j == col - 2)
				shape[row - 2][j] = '_';
			else if (j == col - 1)
				shape[row - 2][j] = '\\';
			else
				shape[row - 2][j] = ' ';
		}

		//===================Draw the First Row=====================
		for (int j = 0; j < col; j++) {
			if (2 <= j && j <= OpenPar_RightWheel)
				shape[0][j] = '_';
			else
				shape[0][j] = ' ';
		}

		//===================Draw the Second Row====================
		for (int j = 0; j < col; j++) {
			if (j == 1)
				shape[1][j] = '/';
			else if (2 <= j && j < OpenPar_RightWheel) {	//Draw door glass
				if (j == 2 || j == Mid_LeftWheel || j == Mid_LeftWheel + 1)
					shape[1][j] = '|';
				else if (j == OpenPar_RightWheel - 1)
					shape[1][j] = '\\';
				else
					shape[1][j] = '_';
			}
			else if (j == Mid_RightWheel)
				shape[1][j] = '\\';
			else if (j == 0 || j == OpenPar_RightWheel || j == col - 1)
				shape[1][j] = ' ';
			else
				shape[1][j] = '_';
		}

	}
	
	else if (type == Convertible) {
	    //  _.-.___\__
		// |  _      _`-.
		// '-(_)----(_)--`

		string line[3];
		line[0] = " _.-.___\\__    ";
		line[1] = "|  _      _`-. ";
		line[2] = "'-(_)----(_)--`";

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				shape[i][j] = line[i][j];
	}

	else if (type == Limousine) {
		//     __________________
		//  __/___||________||___\____
		// |__________________________|
		//   (_)                (_)

		string line[4];
		line[0] = "    __________________      ";
		line[1] = " __/___||________||___\\____ ";
		line[2] = "|__________________________|";
		line[3] = "  (_)                (_)    ";

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				shape[i][j] = line[i][j];

	}
}

int CCAR::getHeight() const {
	return height;
}

int CCAR::getLength() const{
	return length;
}

char ** CCAR::getShape() {
	char **tmp = new char*[height];
	for (int i = 0; i < height; i++)
		tmp[i] = new char[length];
	
	for (int i = 0; i < height; i++)
		for (int j = 0; j < length; j++)
			tmp[i][j] = shape[i][j];

	return tmp;
}

string CCAR::getCode() const {
	return "car" + to_string(type);
}

void CCAR::makeSound() {
	Sound::impactSound(carCrash);
}