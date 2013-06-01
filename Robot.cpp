#include "Robot.hpp" 
#include "Labyrinth.hpp"

Robot::Robot(int x, int y, Labyrinth *labIn) 
	: mLab(labIn), mView(S)
{
	mPos.x = x;
	mPos.y = y;
}

Robot::~Robot()
{
}

bool Robot::move(dir_t dir)
{
	bool result = 1;
	switch(dir){
	case N:
		if(move(mPos.x, mPos.y - 1)) {
		} else {
			result = 0;
		}
		break;
	case E:
		if(move(mPos.x + 1, mPos.y)) {
		} else {
			result = 0;
		}
		break;
	case S:
		if(move(mPos.x, mPos.y + 1)) {
		} else {
			result = 0;
		}
		break;
	case W:
		if(move(mPos.x - 1, mPos.y)) {
		} else {
			result = 0;
		}
		break;
	default:
		break;
	}
	return result;
}

int Robot::move(int x, int y)
{
	if(mLab->isfree(x, y)) {
		mPos.x = x;
		mPos.y = y;
		return 1;
	} else {
		return 0;
	}

}

bool Robot::isFinish() const
{
	Labyrinth::Position pos = mLab->getExit();
	return (pos.x == mPos.x && pos.y == mPos.y);
}

void Robot::turnRight()
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
	default:
		break;
	}
}

void Robot::turnLeft()
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
	default:
		break;
	}
}

void Robot::savePos()
{
	mPath.push_back(mPos);
}

void Robot::showPath()
{
	mLab->plotPath(mPath);
}
