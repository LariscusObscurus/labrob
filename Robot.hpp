#ifndef ROBOT_H
#define ROBOT_H

enum dir_t {
	N,
	E,
	S,
	W
};

class Robot
{
	int xpos;
	int ypos;
public:
	Robot (int x, int y);
	~Robot ();
	int move(dir_t dir);
	int move(int x, int y);
private:
	
};
#endif 
