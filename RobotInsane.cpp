#include "RobotInsane.hpp"
#include "Labyrinth.hpp"
#include <algorithm>

RobotInsane::RobotInsane(int x, int y, Labyrinth* lab) : Robot(x, y, lab)
{
	mPreviousPos = {x,y};
	mCounter = 0;
}

RobotInsane::~RobotInsane()
{
}

int RobotInsane::start()
{
	while (!isFinish()) {
		DIR dir = getNextDirection();
		
		if (dir == NONE) {
			return CRITICAL_ERROR;
		}
		mCounter++;
		savePos();
		mPreviousPos = getPos();
		move(dir);
	}
	
	return mCounter;
}

DIR RobotInsane::getNextDirection()
{
	std::list<DIR> dirs = getFreeDirections();
	// one way direction
	if (dirs.size() == 1) {
		return dirs.front();
	// passage
	} else if (dirs.size() == 2) {
		return opposite(convertPos(mPreviousPos)) == dirs.front() ? dirs.back() : dirs.front();
	// crossroad
	} else if (dirs.size() > 2) {
		if (nodesExist()) {
			DIR dir = chooseRoute(dirs);
			return dir;
		} else {
			createNodes(dirs);
			markLastRoute();
			DIR dir = chooseRoute(dirs);
			return dir;
		}
	}
	// error
	return NONE;
}

bool RobotInsane::nodesExist()
{
	bool result = false;
	Position pos = getPos();
	
	auto it = find_if(mNodes.begin(), mNodes.end(), [=](const Node& node){
		return (node.x == pos.x && node.y == pos.y && node.marker == EXIST);
	});
	
	if (it != mNodes.end()) {
		result = true;
	}
	
	return result;
}
	
void RobotInsane::createNodes(const std::list<DIR>& dirs)
{
	Position pos = getPos();
	Node node = {pos.x, pos.y, EXIST};
	mNodes.push_back(node);
	
	for (DIR dir : dirs) {
		Position pos = convertDir(dir);
		Node node = {pos.x, pos.y, FREE};
		mNodes.push_back(node);
	}
}

void RobotInsane::markLastRoute()
{
	auto it = find_if(mNodes.begin(), mNodes.end(), [=](const Node& node){
		return (node.x == mPreviousPos.x && node.y == mPreviousPos.y);
	});
	
	if (it != mNodes.end()) {
		it->marker = LAST;
	}
}

DIR RobotInsane::chooseRoute(const std::list<DIR>& dirs)
{
	Position pos = {0,0};
	DIR last = NONE;
	
	for (DIR dir : dirs) {
		pos = convertDir(dir);
		
		auto it = find_if(mNodes.begin(), mNodes.end(), [dir, pos, &last](const Node& node){
			if (node.x == pos.x && node.y == pos.y && node.marker == LAST) {
				last = dir;
				return false;
			}
			return (node.x == pos.x && node.y == pos.y && node.marker == FREE);
		});
		
		if (it != mNodes.end()) {
			it->marker = STOP;
			return dir;
		}
	}
	/*
	if (last != NONE) {
		auto it = find_if(mNodes.begin(), mNodes.end(), [pos](const Node& node){
			return (node.x == pos.x && node.y == pos.y && node.marker == LAST);
		});
		
		if (it != mNodes.end()) {
			it->marker = STOP;
		}
	}
	*/
	return last;
}

DIR RobotInsane::opposite(DIR dir)
{
	switch (dir) {
	case N:
		return S;
	case E:
		return W;
	case W:
		return E;
	case S:
		return N;
	default:
		break;
	}
	return NONE;
}

RobotInsane::Position RobotInsane::convertDir(DIR dir)
{
	Position result = getPos();
	switch (dir) {
	case N:
		result.y -= 1;
		break;
	case E:
		result.x += 1;
		break;
	case W:
		result.x -= 1;
		break;
	case S:
		result.y += 1;
		break;
	default:
		break;
	}
	return result;
}

DIR RobotInsane::convertPos(Position pos)
{
	DIR result = NONE;
	int adjX = getX() - pos.x;
	int adjY = getY() - pos.y;
	
	if (adjX == 1) {
		result = E;
	} else if (adjX == -1) {
		result = W;
	} else if (adjY == 1) {
		result = S;
	} else if (adjY == -1) {
		result = N;
	}
	
	return result;
}
