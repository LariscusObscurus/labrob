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
	DIR mView;
public:
	Robot (int x, int y, Labyrinth * labIn);
	virtual ~Robot ();
	virtual int start() = 0;
	virtual bool update() = 0;
protected:
	virtual bool move(dir_t dir);
	virtual int move(int x, int y);
	virtual bool isFinish() const;
	
	int getX() const { return mXpos; }
	int getY() const { return mYpos; }
	const Labyrinth* getLabyrinth() const { return mLab; }
	DIR getView() const { return mView; }
	void setView(DIR value) { mView = value; }
};
#endif 
