#include "Menu.h"

int main()
{
	Controller::setUpConsole();

	Sound::backgroundMusic(true);

	Menu game;
	game.mainMenu();
	
	return 0;
}

