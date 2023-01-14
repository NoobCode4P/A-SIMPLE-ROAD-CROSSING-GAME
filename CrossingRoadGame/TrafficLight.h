#pragma once
#include "Controller.h"
#include <ctime>

#define Off 0
#define GreenLight 1
#define YellowLight 2
#define RedLight 3

class TrafficLight {
	char *Light;
	bool isActivated;
	bool red, green, yellow;
	int secForRed, secForGreen, secForYellow;

public:
	TrafficLight();
	TrafficLight(bool);
	~TrafficLight();
	void activate();
	void deactivate();

	void turnGreen();
	void turnYellow();
	void turnRed();
	void setColor(int);
	
	bool isOn();
	bool isGreen() const;
	bool isRed() const;
	bool isYellow() const;
	int getCurrentColor() const;

	int timeForRed();
	int timeForYellow();
	int timeForGreen();
	
	void switchLight();
	void printLight(int x, int y);

	void setMaximumDuration(int Green, int Yellow, int Red);

};
