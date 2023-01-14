#include "Sound.h"

vector <const wchar_t*> Sound::impactSoundList = {
		L"SOUND/impactedStego",
		L"SOUND/impactedCeratosaurus",
		L"SOUND/impactedPterodactyl",
		L"SOUND/impactedBirdScreech",
		L"SOUND/impactedHummingBird",
		L"SOUND/carCrash",
		L"SOUND/truckHorn",
		L"SOUND/ambulanceSound"
};

bool Sound::impactSState = true;

void Sound::setImpactSState(bool state) {
	impactSState = state;
}

void Sound::impactSound(int i) {
	if (impactSState) {
		PlaySound(impactSoundList[i], NULL, SND_FILENAME | SND_SYNC);
		impactSState = false;
	}
}

void Sound::backgroundMusic(bool backgroundMusicState) {
	if (backgroundMusicState)
		PlaySound(TEXT("SOUND/SkyHigh_Elektronomia"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	else
		PlaySound(NULL, NULL, SND_ASYNC);
}

void Sound::playAAHsound() {
	PlaySound(TEXT("SOUND/aah_LOSE_ANIMATION"), NULL, SND_FILENAME | SND_ASYNC);
}

void Sound::playBreatheRunManSound() {
	PlaySound(TEXT("SOUND/breathingRunning_LOSE_ANIMATION"), NULL, SND_FILENAME | SND_ASYNC);
}

void Sound::playCarCrashSound() {
	PlaySound(TEXT("SOUND/carCrash_LOSE_ANIMATION"), NULL, SND_FILENAME | SND_SYNC);
}

void Sound::playTRexRoar() {
	PlaySound(TEXT("SOUND/t_rex_LOSE_ANIMATION"), NULL, SND_FILENAME | SND_SYNC);
}

void Sound::playIsekaiSound() {
	PlaySound(TEXT("SOUND/transition_LOSE_ANIMATION"), NULL, SND_FILENAME | SND_ASYNC);
}

void Sound::playHelicopterMemeSound() {
	PlaySound(TEXT("SOUND/helicopterMeme"), NULL, SND_FILENAME | SND_ASYNC);
}

void Sound::playArigatouSound() {
	PlaySound(TEXT("SOUND/arigatou"), NULL, SND_FILENAME | SND_SYNC);
}