#include "Robot.hpp"

class RobotLeftHand : public virtual Robot
{
public:
	RobotLeftHand (int x, int y, Labyrinth* lab);
	virtual ~RobotLeftHand ();
	virtual int start();
	virtual std::string getName();

private:
	int mCount;
	void algo();
};
