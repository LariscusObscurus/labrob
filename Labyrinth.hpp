#ifndef LABYRINTHPARSER_H
#define LABYRINTHPARSER_H

#include <vector>
#include <fstream>

class Labyrinth
{
	std::vector<char> mBuffer;
	int mWidth;
	int mHeight;
	int mEntry;
	int mExit;
public:
	Labyrinth(std::ifstream& fileStream);
	~Labyrinth();

/* Ist die angegebene Position frei? 
 * Return Werte:
 * 	false -> Feld ist nicht frei
 * 	true -> Feld ist frei
 */
	bool isfree(int x, int y);

/* Ausgabe des Labyrinths */
	void display();

	std::vector<char> getBuffer();
	int getWidth();
	int getHeight();
	int getEntry();
	int getExit();
private:
	int locateStartEnd();
	int bothFound(int pos);
};

#endif
