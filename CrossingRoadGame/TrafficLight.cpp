#include "TrafficLight.h"

TrafficLight::TrafficLight() {
	Light = new char[3];
	Light[0] = Light[1] = Light[2] = 254;
	isActivated = false;
	green = yellow = red = false;

	secForRed = 6;
	secForGreen = 10;
	secForYellow = 3;
}

TrafficLight::TrafficLight(bool state) {
	Light = new char[3];
	Light[0] = Light[1] = Light[2] = 254;

	if (state == true)
		activate();
	else {
		isActivated = false;
		red = yellow = green = false;
	}

	secForRed = 6;
	secForGreen = 10;
	secForYellow = 3;
}

TrafficLight::~TrafficLight(){
	delete[] Light;
}

void TrafficLight::activate() {
	isActivated = true;
	red = true;
	green = yellow = false;
}

void TrafficLight::deactivate() {
	isActivated = false;
	red = green = yellow = false;
}

void TrafficLight::turnGreen() {
	green = true;
	red = yellow = false;
}

void TrafficLight::turnYellow() {
	yellow = true;
	green = red = false;
}

void TrafficLight::turnRed() {
	red = true;
	green = yellow = false;
}

void TrafficLight::setColor(int color) {
	switch (color) {
	case GreenLight:
		turnGreen();
		break;
	case YellowLight:
		turnYellow();
		break;
	case RedLight:
		turnRed();
		break;
	}
}

bool TrafficLight::isOn() {
	return isActivated == true;
}

bool TrafficLight::isGreen() const {
	return (green == true && red == false && yellow == false);
}

bool TrafficLight::isYellow() const {
	return (yellow == true && red == false && green == false);
}

bool TrafficLight::isRed() const  {
	return (red == true && green == false && yellow == false);
}

int TrafficLight::getCurrentColor() const{
	if (isGreen())
		return GreenLight;
	else if (isYellow())
		return YellowLight;
	else if (isRed())
		return RedLight;
	return Off;
}

void TrafficLight::switchLight() {
	if (isGreen())
		turnYellow();
	else if (isYellow())
		turnRed();
	else if (isRed())
		turnGreen();
}

void TrafficLight::printLight(int x, int y) {
	if (isGreen()) {
		Controller::setConsoleColor(BACKGROUND_COLOR, GREEN);
		Controller::gotoXY(x, y);
		putchar(Light[0]);

		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		Controller::gotoXY(x + 1, y);
		putchar(Light[1]);

		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		Controller::gotoXY(x + 2, y);
		putchar(Light[2]);
	}
	else if (isYellow()) {
		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		Controller::gotoXY(x, y);
		putchar(Light[0]);

		Controller::setConsoleColor(BACKGROUND_COLOR, YELLOW);
		Controller::gotoXY(x + 1, y);
		putchar(Light[1]);

		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		Controller::gotoXY(x + 2, y);
		putchar(Light[2]);
	}
	else if (isRed()) {
		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		Controller::gotoXY(x, y);
		putchar(Light[0]);

		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		Controller::gotoXY(x + 1, y);
		putchar(Light[1]);

		Controller::setConsoleColor(BACKGROUND_COLOR, RED);
		Controller::gotoXY(x + 2, y);
		putchar(Light[2]);
	}
	else {
		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		Controller::gotoXY(x, y);
		putchar(Light[0]);

		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		Controller::gotoXY(x + 1, y);
		putchar(Light[1]);

		Controller::setConsoleColor(BACKGROUND_COLOR, GRAY);
		Controller::gotoXY(x + 2, y);
		putchar(Light[2]);
	}
}

int TrafficLight::timeForGreen() {
	return secForGreen;
}

int TrafficLight::timeForRed() {
	return secForRed;
}

int TrafficLight::timeForYellow() {
	return secForYellow;
}

void TrafficLight::setMaximumDuration(int Green, int Yellow, int Red) {
	int minG = 5;
	int minY = 1;
	int minR = 1;
	
	secForGreen = rand() % (Green - minG + 1) + minG;
	secForYellow = rand() % (Yellow - minY + 1) + minY;
	secForRed = rand() % (Red - minR + 1) + minR;
}
