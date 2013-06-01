#include "RobotInsane.hpp"
#include <algorithm>

RobotInsane::RobotInsane(int x, int y, Labyrinth* lab) : Robot(x, y, lab)
{
}

RobotInsane::~RobotInsane()
{
}

int RobotInsane::start()
{
	int result = NO_ERROR;
	std::list<DIR> startView = getFreeDirections();
	setView(startView.front());
	
	while (!isFinish()) {
		std::list<DIR> directions = getFreeDirections();
		DIR dir = NONE;
		
		if (!directions.empty() && directions.size() > 2) {
			dir = getNextDirection(directions);
			updateVertex(getX(), getY(), dir);
			setView(dir);
			move(getView());
		} else if (!directions.empty() && directions.size() == 2) {
// 			updateVertex(getX(), getY(), directions.front());
			move(getView());
		} else if (!directions.empty() && directions.size() == 1) {
// 			updateVertex(getX(), getY(), directions.front());
			move(directions.front());
		} else {
			result = CRITICAL_ERROR;
			break;
		}
	}
	
	return result;
}

std::list<DIR> RobotInsane::getFreeDirections()
{
	Labyrinth* lab = getLabyrinth();
	std::list<DIR> result(0);
	
	if (lab->isFree(getX()+1, getY())) {
		result.push_back(E);
	}
	if (lab->isFree(getX()-1, getY())) {
		result.push_back(W);
	}
	if (lab->isFree(getX(), getY()+1)) {
		result.push_back(S);
	}
	if (lab->isFree(getX(), getY()-1)) {
		result.push_back(N);
	}
	
	return result;
}

DIR RobotInsane::getNextDirection(const std::list<DIR>& freeDir)
{
	auto it = find_if(mVertices.begin(), mVertices.end(), [=](const Vertex& v){
		return (getX() == v.x && getY() == v.y);
	});
	
	if (it != mVertices.end()) {
		return checkMarkedDirection(freeDir, it->direction);
	} else {
		Vertex& v = addVertex(getX(), getY(), freeDir);
		v.direction[freeDir.front()] += 1;
		return freeDir.front();
	}
}

DIR RobotInsane::checkMarkedDirection(const std::list<DIR>& freeDir, std::map<DIR, int>& visited)
{
	DIR result = NONE;
	std::pair<DIR, int> highest(NONE, 0);
	std::pair<DIR, int> lowest(NONE, 2);
	
	for (auto& it : visited) {
		if (!it.second) {
			it.second += 1;
			return it.first;
		} else {
			if (it.second > highest.second) {
				highest = it;
			}
			if (it.second < lowest.second) {
				lowest = it;
			}
		}
	}
	
	if (highest.second == lowest.second && highest.second == 2) {
		return opposite();
	} else {
		visited[lowest.first] += 1;
		return lowest.first;
	}
}

void RobotInsane::updateVertex(int x, int y, DIR dir)
{
	auto it = std::find_if(mVertices.begin(), mVertices.end(), [=](const Vertex& vertex){
		return (vertex.x == x && vertex.y == y);
	});
	
	if (it != mVertices.end()) {
		auto& map = it->direction;
		map[dir] += 1;
	}
}

Vertex& RobotInsane::addVertex(int x, int y, std::list<DIR>& directions)
{
	Vertex vertex = {x, y, std::map<DIR, int>(0)};
	auto& map = vertex.direction;
	mVertices.push_back(vertex);
	
	for (DIR it : directions) {
		map[it] = 0;
	}
	
	return mVertices.back();
}

DIR RobotInsane::opposite()
{
	switch (getView()) {
	case N:
		setView(S);
		return S;
	case E:
		setView(W);
		return W;
	case W:
		setView(E);
		return E;
	case S:
		setView(N);
		return N;
	}
	return NONE;
}