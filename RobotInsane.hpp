#include "Robot.hpp"
#include <list>
#include <map>

class RobotInsane : public virtual Robot
{
	
	enum MARKER {
		FREE,
		STOP,
		LAST,
		EXIST
	};
	
	struct Node {
		int x;
		int y;
		MARKER marker;
	};
	
	Labyrinth::Position mPreviousPos;
	std::list<Node> mNodes;
	int mCounter;
public:
	RobotInsane (int x, int y, Labyrinth* lab);
	virtual ~RobotInsane ();

	virtual int start();
	virtual std::string getName() { return "RobotInsane"; }
	
	typedef Labyrinth::Position Position;
private:
	DIR getNextDirection();
	std::list<DIR> getFreeDirections();
	
	bool nodesExist();
	void createNodes(const std::list<DIR>& dirs);
	void markLastRoute();
	DIR chooseRoute(const std::list<DIR>& dirs);
	
	DIR opposite(DIR dir);
	Position convertDir(DIR dir);
	DIR convertPos(Position pos);
	Position currentPos();
};
