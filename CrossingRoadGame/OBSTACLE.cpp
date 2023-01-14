#include "OBSTACLE.h"

OBSTACLE::OBSTACLE(int x, int y, bool direction) : mX(x), mY(y) {
	if (direction == left_right) {
		leftToRight = true;
		rightToLeft = false;
	}
	else {
		leftToRight = false;
		rightToLeft = true;
	}
}

OBSTACLE::OBSTACLE(int y, bool direction) {
	if (direction == left_right) {
		leftToRight = true;
		rightToLeft = false;
		mX = LEFT_BOUND - 1;
		mY = y;
	}
	else {
		leftToRight = false;
		rightToLeft = true;
		mX = RIGHT_BOUND + 1;
		mY = y;
	}
}

pair <int, int> OBSTACLE::getCoordinates() const {
	return make_pair(mX, mY);
}

pair <int, int> OBSTACLE::getXYtoPrint() const {
	int x = mX - length / 2;
	int y = mY - height / 2;
	return { x,y };
}

void OBSTACLE::updatePos(int x, int y) {	
	if (rightToLeft)
		mX -= x;
	else if (leftToRight)
		mX += x;
}

void OBSTACLE::setPos(int x, int y) {
	mX = x;
	mY = y;
}

bool OBSTACLE::isLeftToRight() {
	return leftToRight;
}

bool OBSTACLE::isRightToLeft() {
	return rightToLeft;
}

void OBSTACLE::setLeftToRight() {
	leftToRight = true;
	rightToLeft = false;
}

void OBSTACLE::setRightToLeft() {
	leftToRight = false;
	rightToLeft = true;
}

bool OBSTACLE::isImpact(const CPEOPLE& p) {
	int x = getXYtoPrint().first;
	int y = getXYtoPrint().second;

	int xP = p.getCoordinates().first;
	int yP = p.getCoordinates().second;
	int hP = p.getHeight();
	int wP = p.getWidth();

	if ((y - hP / 2 <= yP && yP <= y + height + hP / 2) && (x - wP / 2 <= xP && xP <= x + length + wP / 2))
		return true;
	return false;
}

void OBSTACLE::Move(int dX, int dY) {
	int x, y;
	x = getXYtoPrint().first;
	y = getXYtoPrint().second;

	Graphics::removeObjAt(x, y, height, length);

	updatePos(dX, dY);

	x = getXYtoPrint().first;
	y = getXYtoPrint().second;

	Graphics::printValidPartOfObj(x, y, shape, height, length);
}