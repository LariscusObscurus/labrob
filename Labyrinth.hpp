#ifndef LABYRINTHPARSER_H
#define LABYRINTHPARSER_H

#include <vector>
#include <fstream>
#include <mutex>

class Robot;

class Labyrinth
{
	int mWidth;
	int mHeight;
	int mEntry;
	int mExit;
	std::vector<char> mBuffer;
	std::mutex mMutexBuffer;
	std::mutex mMutexWidth;
	std::mutex mMutexHeight;
	std::mutex mMutexEntry;
	std::mutex mMutexExit;
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
	bool isfree(int x, int y);

	/**
	 * Ausgabe des Labyrinths
	 */
	void display();

	std::vector<char> getBuffer();
	int getWidth();
	int getHeight();
	Position getEntry();
	Position getExit();
private:
	int locateStartEnd();
	int bothFound(int pos);
};

#endif
