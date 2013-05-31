#include "Robot.hpp"

class RobotLeftHand : public virtual Robot
{
public:
	RobotLeftHand (int x, int y, Labyrinth* lab);
	virtual ~RobotLeftHand ();
	virtual int start();

private:
	/* data */
};
