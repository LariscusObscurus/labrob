#include "Robot.hpp"

class RobotRightHand : public virtual Robot
{
public:
	RobotRightHand (int x, int y, Labyrinth* lab);
	virtual ~RobotRightHand ();
	virtual int start();
	virtual std::string getName();

private:
	int mCount;
	void algo();
};
