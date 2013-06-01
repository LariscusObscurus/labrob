#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include "Labyrinth.hpp"
#include "RobotInsane.hpp"
#include "RobotLeftHand.hpp"
#include "RobotRightHand.hpp"

int getCmdOption(char ** begin, char ** end, const std::string& option, 
		std::vector<std::string>& out)
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
	std::list<Robot*> robots;

	if(argc <= 1) {
		std::cout 
		<< "Verwendung: labyrinth DATEINAME [-t1] [-t2] ... [-tN] [-h]" 
		<< std::endl;

		return -1;
	}
	
	if(cmdOptionExists(argv, argv+argc, "-h")) {
		std::cout 
		<< "Verwendung: labyrinth DATEINAME [-t1] [-t2] ... [-tN] [-h]" 
		<< std::endl;

		return 0;
	}

	getCmdOption(argv, argv+argc, "-t", args);

	/* Datei einlesen */
	std::ifstream fileStream(argv[1]);
	fileStream.unsetf(std::ios_base::skipws);
	if(!fileStream) {
		std::cerr << "Could not open file!" << std::endl;
		return -1;
	}
	
	/* Labyrinth erstellen */
	Labyrinth * lab = new Labyrinth(fileStream);
	lab->display();
	Labyrinth::Position start = lab->getEntry();
	
	/* Roboter erstellen */
	if(args.size() > 0) {
		for(auto it = args.begin(); it != args.end(); ++it) {
			if(it[0] == "-t1") {
				Robot * robL = new RobotLeftHand(
							start.x, start.y, lab);
				robots.push_back(robL);
				std::cout 
				<< "-t1 gestartet." << std::endl;
			} else if(it[0] == "-t2") {
				Robot * robR = new RobotRightHand(
							start.x, start.y, lab);
				robots.push_back(robR);
				std::cout 
				<< "-t2 gestartet." << std::endl;
			} else if(it[0] == "-t3") {
				Robot* robInsane = new RobotInsane(
							start.x, start.y, lab);
				robots.push_back(robInsane);
				std::cout 
				<< "-t3 gestartet." << std::endl;
			} else {
				std::cout << it[0] 
				<< " unbekannter Roboter Typ" << std::endl;
			}
		}
	}
	
	/* Roboter starten */
	for(auto& it : robots) {
		it->start();
		delete it;
	}

	delete lab;
	return 0;
}
