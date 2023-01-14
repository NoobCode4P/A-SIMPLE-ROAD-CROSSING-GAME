#include "CPEOPLE.h"

int LOWER_BOUND;

CPEOPLE CPEOPLE::instance;

CPEOPLE::CPEOPLE() {}

CPEOPLE::~CPEOPLE() {}

pair <int, int> CPEOPLE::getCoordinates() const {
	return make_pair(mX, mY);
}

pair <int, int> CPEOPLE::getXYtoPrint() const {
	int x = mX - 2;
	int y = mY - 2;
	return { x, y };
}

void CPEOPLE::setXY(int x, int y) {
	mX = x;
	mY = y;
}

int CPEOPLE::getHeight() const {
	return 4;
}

int CPEOPLE::getWidth() const {
	return 4;
}

void CPEOPLE::spawnPlayer() {
	mX = (RIGHT_BOUND - LEFT_BOUND) / 2;
	mY = LOWER_BOUND + 4;
	drawPlayer();
}

void CPEOPLE::drawPlayer() {
	int x = getXYtoPrint().first;
	int y = getXYtoPrint().second;
	Controller::setConsoleColor(BACKGROUND_COLOR, BLACK);
	for (int i = 4 - 1; i >= 0; i--) {
		if (y + i >= 0) {
			Controller::gotoXY(x, y + i);
			cout << playerRender[i] << endl;
		}
	}
}

void CPEOPLE::Up(int k) {
	if (mState && mY - k > UPPER_BOUND - 5)
		mY -= k;
}

void CPEOPLE::Left(int k) {
	if (mState && mX - k > LEFT_BOUND + 2)
		mX -= k;
}

void CPEOPLE::Right(int k) {
	if (mState && mX + k < RIGHT_BOUND - 1)
		mX += k;
}

void CPEOPLE::Down(int k) {
	if (mState && mY + k < LOWER_BOUND + 5)
		mY += k;
}

void CPEOPLE::updatePos(int direction, int steps) {
	switch (direction) {
	case UP: {
		Up(steps);
		break;
	}
		
	case DOWN: {
		Down(steps);
		break;
	}

	case LEFT: {
		Left(steps);
		break;
	}

	case RIGHT: {
		Right(steps);
		break;
	}
	}
}

void CPEOPLE::impacted() {
	mState = false;
}

void CPEOPLE::revive() {
	mState = true;
}

bool CPEOPLE::isFinish() {
	if (getXYtoPrint().second <= UPPER_BOUND - 4)
		return true;
	return false;
}

bool CPEOPLE::isDead() {
	return mState == false;
}

CPEOPLE& CPEOPLE::getInstance() {
	return instance;
}