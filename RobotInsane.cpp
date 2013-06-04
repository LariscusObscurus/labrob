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
	savePos();
	while (!isFinish()) {
		DIR dir = getNextDirection();
		
		if (dir == NONE) {
			return CRITICAL_ERROR;
		}
		mCounter++;
		mPreviousPos = getPos();
		move(dir);
		savePos();
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
		return (node.x == pos.x && node.y == pos.y);
	});
	
	if (it != mNodes.end()) {
		result = true;
	}
	
	return result;
}
	
void RobotInsane::createNodes(const std::list<DIR>& dirs)
{
	Position pos = getPos();
	Node node = {pos.x, pos.y, std::list<Offshoot>(0)};
	
	for (DIR dir : dirs) {
		Position pos = convertDir(dir);
		Offshoot offshoot = {pos.x, pos.y, FREE};
		
		if (pos.x == mPreviousPos.x && pos.y == mPreviousPos.y) {
			offshoot.marker = LAST;
		}
		
		node.offshoots.push_back(offshoot);
	}
	mNodes.push_back(node);
}

DIR RobotInsane::chooseRoute(const std::list<DIR>& dirs)
{
	Position pos = getPos();
	DIR last = NONE;	
	auto it = find_if(mNodes.begin(), mNodes.end(), [=](const Node& node){
		return (node.x == pos.x && node.y == pos.y);
	});
	
	if (it == mNodes.end()) {
		return NONE;
	}
	
	for (DIR dir : dirs) {
		pos = convertDir(dir);
		
		auto offshoot = find_if(it->offshoots.begin(), it->offshoots.end(), [=, &last](const Offshoot& o){
			if (o.x == pos.x && o.y == pos.y && o.marker == LAST) {
				last = dir;
				return false;
			}
			return (o.x == pos.x && o.y == pos.y && o.marker == FREE);
		});
		
		if (offshoot != it->offshoots.end()) {
			offshoot->marker = STOP;
			return dir;
		}
	}
	
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
	Position currentPos = getPos();
	int adjX = currentPos.x - pos.x;
	int adjY = currentPos.y - pos.y;
	
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
