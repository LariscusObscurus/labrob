#include <iostream>
#include "LabyrinthParser.hpp"

int main(int argc, char *argv[])
{
	LabyrinthParser * parser = new LabyrinthParser(argv[1]);
	std::vector<char> buf = parser->getBuffer();
	for (int i = 0; i <= buf.size(); i++) {
		if((i % parser->getWidth()) == 0) {
			std::cout << std::endl << buf[i];
		} else {
			std::cout << buf[i];
		}
	}
	std::cout << parser->getWidth();
	return 0;
}
