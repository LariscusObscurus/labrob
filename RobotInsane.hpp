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
		
		struct Offshoot {
			int x;
			int y;
			MARKER marker;
		};
		std::list<Offshoot> offshoots;
	};
	typedef Node::Offshoot Offshoot;
	
	Labyrinth::Position mPreviousPos;
	std::list<Node> mNodes;
	int mCounter;
public:
	RobotInsane (int x, int y, Labyrinth* lab);
	virtual ~RobotInsane ();

	virtual int start();
	virtual std::string getName() { return "T3"; }
	
	typedef Labyrinth::Position Position;
private:
	DIR getNextDirection();
	
	bool nodesExist();
	void createNodes(const std::list<DIR>& dirs);
// 	void markLastRoute();
	DIR chooseRoute(const std::list<DIR>& dirs);
	
	DIR opposite(DIR dir);
	Position convertDir(DIR dir);
	DIR convertPos(Position pos);
};
