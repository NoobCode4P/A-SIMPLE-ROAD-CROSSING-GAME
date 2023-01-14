#include "CDINOSAUR.h"

CDINOSAUR::CDINOSAUR(int x, int y, int type, bool direction) : OBSTACLE(x, y, direction) {
	formShape(type);
	if (rightToLeft)
		Graphics::switchDirection(shape, height, length);
	this->type = type;
}

CDINOSAUR::~CDINOSAUR() {
	for (int i = 0; i < height; i++)
		delete[] shape[i];
	delete[] shape;
}

void CDINOSAUR::formShape(int species) {
	height = Dino[species].first;
	length = Dino[species].second;

	shape = new char*[height];
	for (int i = 0; i < height; i++)
		shape[i] = new char[length];

	int row = height;
	int col = length;

	if (species == Stegosaurus) {
		//            /\/\/\         
		//        _/\/  \/  \^/\
		//       /              \
		//     _| (   \    (  \  \__ 
		//  __/ _/-|  |-----| |-----'
		// <___/   |__\     |_\      

		string line[6];

		line[0] = "           /\\/\\/\\          ";
		line[1] = "       _/\\/  \\/  \\^/\\      ";
		line[2] = "      /              \\     ";
		line[3] = "    _| (   \\    (  \\  \\___ ";
		line[4] = " __/ _/-|  |-----| |------'";
		line[5] = "<___/   |__\\     |_\\       ";

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				shape[i][j] = line[i][j];
	}

	else if (species == Ceratosaurus) {
		//                   _./\/\/\/\/\._       ____
		// --=====__^^^^^^^~'              `~____/   @``--^.
		//          ```.-----(   \____.   ( )____(_____vvvv
		//                    \   )\  \````\|
		//                    /  /  \  \
		//                   /___~~  \___~~

		string line[6];

		line[0] = "                  _./\\/\\/\\/\\/\\._       ____      ";
		line[1] = "--=====__^^^^^^^~'              `~____/   @``--^.";
		line[2] = "         ```.-----(   \\____.   ( )____(_____vvvv ";
		line[3] = "                   \\   )\\  \\````\\|               ";
		line[4] = "                   /  /  \\  \\                    ";
		line[5] = "                  /___~~  \\___~~                 ";

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				shape[i][j] = line[i][j];
	}

	else if (species == Pterodactyl) {
		//           .
		//          /|
		//         /+|
		//        / ||  _
		//    __./  ||__\\______
		// +===._____--.__.=====>
			
		string line[6];

		line[0] = "          .           ";
		line[1] = "         /|           ";
		line[2] = "        /+|           ";
		line[3] = "       / ||  _        ";
		line[4] = "   __./  ||__\\\\______ ";
		line[5] = "+===._____--.__.=====>";

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				shape[i][j] = line[i][j];
	}
}

int CDINOSAUR::getHeight() const{
	return height;
}

int CDINOSAUR::getLength() const {
	return length;
}

char ** CDINOSAUR::getShape() {
	char **tmp = new char*[height];
	for (int i = 0; i < height; i++)
		tmp[i] = new char[length];

	for (int i = 0; i < height; i++)
		for (int j = 0; j < length; j++)
			tmp[i][j] = shape[i][j];
	return tmp;
}

string CDINOSAUR::getCode() const {
	return "dino" + to_string(type);
}

void CDINOSAUR::makeSound() {
	switch (type) {
	case Stegosaurus:
		Sound::impactSound(impactStegosaurus);
		break;
	case Pterodactyl:
		Sound::impactSound(impactPterodactyl);
		break;
	case Ceratosaurus:
		Sound::impactSound(impactCeratosaurus);
		break;
	}
}
