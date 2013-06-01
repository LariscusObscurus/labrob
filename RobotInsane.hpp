#include "Robot.hpp"
#include <list>
#include <map>

class RobotInsane : public virtual Robot
{
	struct Vertex {
		int x;
		int y;
		std::map<DIR, int> direction;
	};
	std::list<Vertex> mVertices;
	DIR mCurrentDir;
public:
	RobotInsane (int x, int y, Labyrinth* lab);
	virtual ~RobotInsane ();

	virtual int start();
private:
	std::list<DIR> getFreeDirections();
	DIR getNextDirection(const std::list<DIR>& dir);
	DIR checkMarkedDirection(const std::list<DIR>& dir, std::map<DIR, int>& visited);
	void updateVertex(int x, int y, DIR dir);
	void addVertex(int x, int y, std::list<DIR>& directions);
};
