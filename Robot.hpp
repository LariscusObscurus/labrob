#ifndef ROBOT_H
#define ROBOT_H

class Labyrinth;

enum dir_t {
	N,
	E,
	S,
	W
};

class Robot
{
	int mXpos;
	int mYpos;
	Labyrinth * mLab;
public:
	Robot (int x, int y, Labyrinth * labIn);
	virtual ~Robot ();
	virtual int start() = 0;
private:
	int move(dir_t dir);
	int move(int x, int y);
	
};
#endif 
