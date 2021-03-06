#ifndef ROBOT_H
#define ROBOT_H

#include "Labyrinth.hpp"
#include <string>
#include <list>

#define CRITICAL_ERROR 0xffffffff
#define NO_ERROR       0x0

typedef enum DIR {
	NONE,
	N,
	E,
	S,
	W
} dir_t;

class Robot
{
	Labyrinth::Position mPos;
	Labyrinth * mLab;
	DIR mView;
	std::list<Labyrinth::Position> mPath;

public:
	Robot (int x, int y, Labyrinth * labIn);
	virtual ~Robot ();
	virtual int start() = 0;
	virtual std::string getName() = 0;
	virtual void showPath();
protected:
	virtual void savePos();
	virtual bool move(dir_t dir);
	virtual int move(int x, int y);
	virtual bool isFinish() const;
	
	Labyrinth::Position getPos() const { return mPos; }
	Labyrinth* getLabyrinth() { return mLab; }
	DIR getView() const { return mView; }

	void turnRight();
	void turnLeft();

	std::list<DIR> getFreeDirections();
};
#endif 
