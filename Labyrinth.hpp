#ifndef LABYRINTHPARSER_H
#define LABYRINTHPARSER_H

#include <vector>
#include <fstream>
class Robot;

class Labyrinth
{
	int mWidth;
	int mHeight;
	int mEntry;
	int mExit;
	std::vector<char> mBuffer;
public:
	Labyrinth(std::ifstream& fileStream);
	~Labyrinth();

/* Ist die angegebene Position frei? 
 * Return Werte:
 * 	false -> Feld ist nicht frei
 * 	true -> Feld ist frei
 */
	bool isfree(int x, int y) const;

/* Ausgabe des Labyrinths */
	void display() const;

	std::vector<char> getBuffer() const;
	int getWidth() const;
	int getHeight() const;
	int getEntry() const;
	int getExit() const;
private:
	int locateStartEnd();
	int bothFound(int pos);
};

#endif
