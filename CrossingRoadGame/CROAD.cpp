#include "CROAD.h"

CROAD::CROAD() {}

CROAD::CROAD(int numOfLane, int fixedLaneWidth) {
	this->numOfLane = numOfLane;
	length = RIGHT_BOUND - LEFT_BOUND;
	this->fixedLaneWidth = fixedLaneWidth;
}

CROAD::CROAD(vector <int> laneWidth) {
	this->numOfLane = laneWidth.size();
	length = RIGHT_BOUND - LEFT_BOUND;
	this->fixedLaneWidth = 0;
	this->laneWidth = laneWidth;
}

CROAD::~CROAD() {}

vector <string> CROAD::getHorizontalLine() const {
	return horizontalLine;
}

vector <int> CROAD::getLaneWidth() const {
	return laneWidth;
}

void CROAD::buildAt(int x, int y) {
	if (fixedLaneWidth != 0) 
		Graphics::drawRoadWithFixedLaneWidth(x, y, length, numOfLane, fixedLaneWidth);
	else
		Graphics::drawRoadWithMultipleLaneWidths(x, y, length, laneWidth, horizontalLine);
}
