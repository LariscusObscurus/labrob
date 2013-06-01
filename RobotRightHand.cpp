#include "RobotRightHand.hpp"
#include <iostream>

RobotRightHand::RobotRightHand(int x, int y, Labyrinth* lab) : Robot(x, y, lab)
{
}

RobotRightHand::~RobotRightHand()
{
}

int RobotRightHand::start()
{
	mCount = 0;
	while(!isFinish()){
		turnRight();
		algo();
		mCount++;
	}
	return mCount;
}

void RobotRightHand::algo()
{
	for(int i = 0; i < 4; i++) {
		if(!move(getView())) {
			turnLeft();
		} else {
			return;
		}
	}
}
