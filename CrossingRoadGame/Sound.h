#pragma once
#include "Controller.h"

#define impactStegosaurus 0
#define impactCeratosaurus 1
#define impactPterodactyl 2
#define impactBird 3
#define impactHummingBird 4
#define carCrash 5
#define truckHorn 6
#define ambulanceSound 7


class Sound {
	static vector <const wchar_t*> impactSoundList;
	static bool impactSState;
public:
	static void setImpactSState(bool isOn);
	static void impactSound(int number);
	static void backgroundMusic(bool backgroundMusicState);
	static void playAAHsound();
	static void playBreatheRunManSound();
	static void playTRexRoar();
	static void playCarCrashSound();
	static void playIsekaiSound();
	static void playHelicopterMemeSound();
	static void playArigatouSound();
};