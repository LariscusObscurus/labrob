#include "RobotInsane.hpp"

RobotInsane::RobotInsane(int x, int y, Labyrinth* lab) : Robot(x, y, lab)
{
}

RobotInsane::~RobotInsane()
{
}

int RobotInsane::start()
{
	while (!isFinish()) {
		
	}
	return 0;
}

std::list<DIR> RobotInsane::getFreeDirections()
{
	return std::list<DIR>(0);
}