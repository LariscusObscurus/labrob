#ifndef ROBOT_H
#define ROBOT_H

enum DIR {
	N,
	E,
	S,
	W
} dir_t;

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
