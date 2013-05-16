#ifndef LABYRINTHPARSER_H
#define LABYRINTHPARSER_H

#include <vector>

class Labyrinth
{
	std::vector<char> mBuffer;
	int mWidth;
	int mHeight;
	int mEntry;
	int mExit;
public:
	Labyrinth();
	~Labyrinth();

/* Datei einlesen und Vector befüllen 
 * Return Werte: 
 * 	0 -> OK
 * 	-1 -> Datei konnte nicht geöffnet werden
 */
	int readFile(const char* fileName);

/* Ist die angegebene Position frei? 
 * Return Werte:
 * 	false -> Feld ist nicht frei
 * 	true -> Feld ist frei
 */
	bool isfree(int x, int y);

/* Ausgabe des Labyrinths */
	void display();

	int newRobot();
	std::vector<char> getBuffer();
	int getWidth();
	int getHeight();
private:
	int locateStartEnd();
};

#endif
