#include "Robot.hpp" 
#include "Labyrinth.hpp"

Robot::Robot(int x, int y, Labyrinth *labIn) : mXpos(x), mYpos(y), mLab(labIn)
{
}

Robot::~Robot()
{
}

int Robot::move(dir_t dir)
{
	switch(dir){
	case N:
		if(move(mXpos - 1, mYpos)) {
		}
		break;
	case E:
		if(move(mXpos, mYpos + 1)) {
		}
		break;
	case S:
		if(move(mXpos + 1, mYpos)) {
		}
		break;
	case W:
		if(move(mXpos, mYpos - 1)) {
		}
		break;
	}
	return 0;
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