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
		
		addVertex(directions);
		
		if (!directions.empty() && directions.size() > 2) {
			dir = getNextDirection(directions);
			updateVertex(getX(), getY(), dir);
			setView(dir);
			move(getView());
		} else if (!directions.empty() && directions.size() == 2) {
			updateVertex(getX(), getY(), directions.front());
			move(getView());
		} else if (!directions.empty() && directions.size() == 1) {
			updateVertex(getX(), getY(), directions.front());
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
}

DIR RobotInsane::checkMarkedDirection(const std::list<DIR>& freeDir, std::map<DIR, int>& visited)
{
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

void RobotInsane::addVertex(int x, int y, std::list<DIR>& directions)
{
	auto it = std::find_if(mVertices.begin(), mVertices.end(), [=](const Vertex& vertex){
		return (vertex.x == x && vertex.y == y);
	});
	
	if (it == mVertices.end()) {
		Vertex vertex = {x, y, std::map<DIR, int>(0)};
		auto& map = vertex.direction;
		mVertices.push_back(vertex);
		
		for (DIR it : directions) {
			map[it] = 0;
		}
	}
}