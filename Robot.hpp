#ifndef ROBOT_H
#define ROBOT_H

class Labyrinth;

typedef enum DIR {
	N,
	E,
	S,
	W
} dir_t;

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
