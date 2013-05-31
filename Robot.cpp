#include "Robot.hpp" 
#include "Labyrinth.hpp"

Robot::Robot(int x, int y, Labyrinth *labIn) : mXpos(x), mYpos(y), mLab(labIn)
{
}

Robot::~Robot()
{
}

bool Robot::move(dir_t dir)
{
	bool result = 1;
	switch(dir){
	case N:
		if(move(mXpos - 1, mYpos)) {
		} else {
			result = 0;
		}
		break;
	case E:
		if(move(mXpos, mYpos + 1)) {
		} else {
			result = 0;
		}
		break;
	case S:
		if(move(mXpos + 1, mYpos)) {
		} else {
			result = 0;
		}
		break;
	case W:
		if(move(mXpos, mYpos - 1)) {
		} else {
			result = 0;
		}
		break;
	}
	return result;
}

int Robot::move(int x, int y)
{
	if(mLab->isfree(x, y)) {
		mXpos = x;
		mYpos = y;
		return 1;
	} else {
		return 0;
	}

}

bool Robot::isFinish() const
{
	Labyrinth::Position pos = mLab->getExit();
	return (pos.x == mXpos && pos.y == mYpos);
}
