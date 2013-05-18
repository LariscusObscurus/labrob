#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "Labyrinth.hpp"

int getCmdOption(char ** begin, char ** end, const std::string& option, std::vector<std::string>& out)
{
	int result = -1;
	for (char ** it = begin; it != end; ++it) {
		std::string tmp = *it;	
		if(tmp.find(option) != std::string::npos) {
			out.push_back(tmp);
			result = 0;
		}
	}
	return result;
}

bool cmdOptionExists(char ** begin, char ** end, const std::string& option)
{
	return std::find(begin, end, option) != end;
}

int main(int argc, char *argv[])
{
	std::vector<std::string> args(0);
	if(argc <= 1) {
		std::cout << "Verwendung: labyrinth DATEINAME [-t1] [-t2] ... [-tN] [-h]" << std::endl;
		return -1;
	}
	
	if(cmdOptionExists(argv, argv+argc, "-h")) {
		std::cout << "Verwendung: labyrinth DATEINAME [-t1] [-t2] ... [-tN] [-h]" << std::endl;
		return 0;
	}
	getCmdOption(argv, argv+argc, "-t", args);

	std::cout << "Gestartete Roboter: ";
	for(auto it = args.begin(); it != args.end(); ++it) {
		std::cout << it[0];
	}
	std::cout << std::endl;

	Labyrinth * lab = new Labyrinth();

	if(lab->readFile(argv[1]) == -1) {
		return -1;
	}

	lab->display();
	return 0;
}