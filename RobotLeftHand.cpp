#include "RobotLeftHand.hpp"
#include <iostream>

RobotLeftHand::RobotLeftHand(int x, int y, Labyrinth* lab) : Robot(x, y, lab)
{
	
}

RobotLeftHand::~RobotLeftHand()
{
}

int RobotLeftHand::start()
{
	mView = S;
	mCount = 0;
	while(!isFinish()){
	//for(int i= 0; i<10; i++){
		turnLeft();
		algo();
		mCount++;
		std::cout << "X: " << getX() << std::endl; 
		std::cout << "Y: " <<getY() << std::endl;
	}

	std::cout << "Success! " << mCount << std::endl;
	return 1;
}

void RobotLeftHand::algo()
{
	for(int i = 0; i < 4; i++) {
		if(!move(mView)) {
			turnRight();
		} else {
			return;
		}
	}
	std::cout << "???" << std::endl;
}

void RobotLeftHand::turnRight()
{
	switch(mView){
	case N:
		mView = E;
		break;
	case E:
		mView = S;
		break;
	case S:
		mView = W;
		break;
	case W:
		mView = N;
		break;
	}
}

void RobotLeftHand::turnLeft()
{
	switch(mView){
	case N:
		mView = W;
		break;
	case E:
		mView = N;
		break;
	case S:
		mView = E;
		break;
	case W:
		mView = S;
		break;
	}
}
