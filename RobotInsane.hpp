#include "Robot.hpp"
#include <list>

class RobotInsane : public virtual Robot
{
	struct Vertex {
		int x;
		int y;
		std::list<DIR> direction;
	};
	std::list<Vertex> mVertices;
public:
	RobotInsane (int x, int y, Labyrinth* lab);
	virtual ~RobotInsane ();

	virtual int start();
private:
	/* data */
};
