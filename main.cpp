#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <functional>
#include <thread>
#include <mutex>
#include <future>
#include "Labyrinth.hpp"
#include "RobotInsane.hpp"
#include "RobotLeftHand.hpp"
#include "RobotRightHand.hpp"

struct robotResult{
	std::string name;
	int steps;
};

std::mutex gCoutM;
std::mutex gResultM;
Labyrinth gLab;
std::list<robotResult> gResults;

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

robotResult robotThreadFunction(bool showPath, Robot* robot)
{
	robotResult result;
	result.steps = robot->start();
	result.name = robot->getName();
	
	if(showPath) {
		gCoutM.lock();
		robot->showPath();
		gCoutM.unlock();
	}
	
	delete robot;
	gResultM.lock();
	gResults.push_back(result);
	gResultM.unlock();
	return result;
}

void handleRobot(int argc, char** argv, Robot* robot)
{
	std::future<robotResult> f = std::async(
		std::launch::async,
		&robotThreadFunction, 
		cmdOptionExists(argv, argv+argc, "-p"),
		robot
	);
	f.get();
}

int main(int argc, char *argv[])
{
	std::vector<std::string> args(0);
	
	if(argc <= 1) {
		std::cout 
		<< "Verwendung: labrob DATEINAME [-t1] [-t2] ... [-tN] [-p] [-h]" 
		<< std::endl;

		return -1;
	}
	
	if(cmdOptionExists(argv, argv+argc, "-h")) {
		std::cout 
		<< "Verwendung: labrob DATEINAME [-t1] [-t2] ... [-tN] [-p] [-h]" 
		<< std::endl;

		return 0;
	}

	getCmdOption(argv, argv+argc, "-t", args);

	if(args.empty()) {
		std::cout 
		<< "Fehler: Keine Roboter angegeben."
		<< std::endl
		<< "Verwendung: labrob DATEINAME [-t1] [-t2] ... [-tN] [-p] [-h]" 
		<< std::endl;
		return -1;
	}
	/* Datei einlesen */
	std::ifstream fileStream(argv[1]);
	fileStream.unsetf(std::ios_base::skipws);
	if(!fileStream) {
		std::cerr << "Datei konnte nicht geöffnet werden." << std::endl;
		return -1;
	}
	
	/* Labyrinth erstellen */
	gLab = Labyrinth(fileStream);
	gLab.showLabyrinth();
	Labyrinth::Position start = gLab.getEntry();
	
	/* Roboter erstellen */
	if(args.size() > 0) {
		for(auto it = args.begin(); it != args.end(); ++it) {
			if(it[0] == "-t1") {
				gCoutM.lock();
				std::cout 
					<< "-t1 gestartet." 
					<< std::endl;
				gCoutM.unlock();
				Robot* robot = new RobotLeftHand(
					start.x,
					start.y,
					&gLab
				);
				handleRobot(argc, argv, robot);
			} else if(it[0] == "-t2") {
				gCoutM.lock();
				std::cout 
					<< "-t2 gestartet." 
					<< std::endl;
				gCoutM.unlock();
				Robot* robot = new RobotRightHand(
					start.x,
					start.y,
					&gLab
				);
				handleRobot(argc, argv, robot);
			} else if(it[0] == "-t3") {
				gCoutM.lock();
				std::cout 
					<< "-t3 gestartet." 
					<< std::endl;
				gCoutM.unlock();
				Robot* robot = new RobotInsane(
					start.x,
					start.y,
					&gLab
				);
				handleRobot(argc, argv, robot);
			} else {
				gCoutM.lock();
				std::cout << it[0] 
					<< " unbekannter Roboter Typ" 
					<< std::endl;
				gCoutM.unlock();
			}
		}
	}
	
	for(auto& it: gResults) {
		std::cout << "Roboter: " << it.name 
			<< " Schritte: " << it.steps 
			<< std::endl;
	}
	return 0;
}
