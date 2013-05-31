#include "RobotLeftHand.hpp"

RobotLeftHand::RobotLeftHand(int x, int y, Labyrinth* lab) : Robot(x, y, lab)
{
}

int RobotLeftHand::start()
{
	DIR view = S;
	while(!isFinish()){
		
	}
}

void RobotLeftHand::turnRight(DIR& view)
{
	switch(view){
	case N:
		view = E;
		break;
	case E:
		view = S;
		break;
	case S:
		view = W;
		break;
	case W:
		view = N;
		break;
	}
}

void RobotLeftHand::turnLeft(DIR& view)
{
	switch(view){
	case N:
		view = W;
		break;
	case E:
		view = N;
		break;
	case S:
		view = E;
		break;
	case W:
		view = S;
		break;
	}
}

bool RobotLeftHand::leftWall()
{
	
}
