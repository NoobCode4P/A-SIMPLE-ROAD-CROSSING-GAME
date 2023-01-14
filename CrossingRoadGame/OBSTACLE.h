#pragma once
#include "Controller.h"
#include "Graphics.h"
#include "CPEOPLE.h"
#include "Sound.h"

#define left_right true
#define right_left false

class OBSTACLE {
	int mX, mY;

protected:
	int height, length;
	char **shape;
	bool leftToRight, rightToLeft;

public:
	OBSTACLE() {};
	OBSTACLE(int x, int y, bool direction);
	OBSTACLE(int y, bool);
	virtual ~OBSTACLE() {};

	pair <int, int> getCoordinates() const;
	pair <int, int> getXYtoPrint() const;

	virtual int getHeight() const = 0;
	virtual int getLength() const = 0;
	virtual char ** getShape() = 0;
	virtual string getCode() const = 0;

	bool isLeftToRight();
	bool isRightToLeft();
	void setRightToLeft();
	void setLeftToRight();

	bool isImpact(const CPEOPLE&);

	void updatePos(int x, int y);
	void setPos(int x, int y);
	virtual void Move(int dX, int dY = 0);

	virtual void makeSound() = 0;
};
