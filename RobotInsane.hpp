#include "Robot.hpp"

class RobotInsane : public virtual Robot
{
public:
	RobotInsane (int x, int y, Labyrinth* lab);
	virtual ~RobotInsane ();

	virtual int start();
private:
	/* data */
};
