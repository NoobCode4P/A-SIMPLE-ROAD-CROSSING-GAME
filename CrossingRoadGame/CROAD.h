#pragma once
#include "Controller.h"
#include "Graphics.h"

class CROAD {
	int length;
	int numOfLane;
	vector <int> laneWidth;
	int fixedLaneWidth;

	vector <string> horizontalLine;

public:
	CROAD();
	CROAD(int numOfLane, int fixedLaneWidth);
	CROAD(vector <int> laneWidth);
	~CROAD();

	vector <string> getHorizontalLine() const;
	vector <int> getLaneWidth() const;

	void buildAt(int x, int y);
};