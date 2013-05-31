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
	
	struct Position {
		int x;
		int y;
	};

	/**
	 * Ist die angegebene Position frei? 
	 * @param x position entlang der x-achse
	 * @param y position entlang der y-achse
	 * @return 'true' wenn das Feld frei ist
	 */
	bool isfree(int x, int y) const;

	/**
	 * Ausgabe des Labyrinths
	 */
	void display() const;

	std::vector<char> getBuffer() const;
	int getWidth() const;
	int getHeight() const;
	Position getEntry() const;
	Position getExit() const;
private:
	int locateStartEnd();
	int bothFound(int pos);
};

#endif
