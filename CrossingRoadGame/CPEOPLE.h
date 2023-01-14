#pragma once
#include "Graphics.h"

class CPEOPLE {
	int mX, mY;
	bool mState = true;
	string playerRender[4]{
		"  0 ",
		"-##-",
		" || ",
		"=  ="
	};

	static CPEOPLE instance;

public:
	CPEOPLE();
	~CPEOPLE();
	
	pair <int, int> getCoordinates() const;
	pair <int, int> getXYtoPrint() const;
	void setXY(int, int);

	int getHeight() const;
	int getWidth() const;

	void spawnPlayer();
	void drawPlayer();

	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	void updatePos(int direction, int steps);

	void impacted();
	void revive();
	bool isFinish();
	bool isDead();

	static CPEOPLE& getInstance();
};
