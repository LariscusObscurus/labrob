#include <iostream>
#include "Labyrinth.hpp"

int main(int argc, char *argv[])
{
	if(argc < 1) {
		std::cout << "Verwendung: labyrinth DATEINAME [-t1] [-t2] ... [-tN] [-h]" << std::endl;
	}

	Labyrinth * lab = new Labyrinth();
	lab->readFile(argv[1]);
	lab->display();
	return 0;
}
