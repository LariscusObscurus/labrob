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
protected:
	virtual int move(dir_t dir);
	virtual int move(int x, int y);
	
	int getX() const { return mXpos; }
	int getY() const { return mYpos; }
	Labyrinth* getLabyrinth() const { return mLab; }
};
#endif 
