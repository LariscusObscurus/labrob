#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <list>
#include <functional>
#include <thread>
#include <mutex>
#include "Labyrinth.hpp"
#include "RobotInsane.hpp"
#include "RobotLeftHand.hpp"
#include "RobotRightHand.hpp"

std::mutex gCout;
Labyrinth gLab;

struct robotResult{
	std::string name;
	int steps;
};

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

void robotThreadFunction(bool showPath, Robot* robot)
{
	robotResult result;
	result.steps = robot->start();
	result.name = robot->getName();
	
	// save print to stdout
	gCout.lock();
	
	if(showPath) {
		robot->showPath();
	}
	std::cout << "Roboter: " << result.name 
		<< " Schritte: " << result.steps 
		<< std::endl;
	
	gCout.unlock();
	// end of save print
	
// 	delete robot;
}

int main(int argc, char *argv[])
{
	std::vector<std::string> args(0);
	/* übung 6
	std::list<Robot*> robots;
	std::list<robotResult> stepsPerRobot;
	*/
// 	std::list<std::thread> threads;
	
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
// 	Labyrinth * lab = new Labyrinth(fileStream);
	gLab = Labyrinth(fileStream);
// 	lab->showLabyrinth();
	gLab.showLabyrinth();
// 	Labyrinth::Position start = lab->getEntry();
	Labyrinth::Position start = gLab.getEntry();
	
	/* Roboter erstellen */
	if(args.size() > 0) {
		for(auto it = args.begin(); it != args.end(); ++it) {
			if(it[0] == "-t1") {
// 				threads.push_back(std::thread(
				Robot* robot = new RobotLeftHand(
					start.x,
					start.y,
					&gLab
				);
				std::thread t(
					&robotThreadFunction, 
					cmdOptionExists(argv, argv+argc, "-p"),
					std::ref(robot)
				);
// 				threads.back().join();
				t.join();
				/* übung 6
				Robot * robL = new RobotLeftHand(
							start.x, start.y, lab);
				robots.push_back(robL);
				*/
				gCout.lock();
				std::cout 
					<< "-t1 gestartet." 
					<< std::endl;
				gCout.unlock();
			} else if(it[0] == "-t2") {
// 				threads.push_back(std::thread(
				Robot* robot = new RobotRightHand(
					start.x,
					start.y,
					&gLab
				);
				std::thread t(
					&robotThreadFunction, 
					cmdOptionExists(argv, argv+argc, "-p"),
					robot
				);
// 				threads.back().join();
				t.join();
				/* übung 6
				Robot * robR = new RobotRightHand(
							start.x, start.y, lab);
				robots.push_back(robR);
				*/
				gCout.lock();
				std::cout 
					<< "-t2 gestartet." 
					<< std::endl;
				gCout.unlock();
			} else if(it[0] == "-t3") {
// 				threads.push_back(std::thread(
				Robot* robot = new RobotInsane(
					start.x,
					start.y,
					&gLab
				);
				std::thread t(
					&robotThreadFunction, 
					cmdOptionExists(argv, argv+argc, "-p"),
					robot
				);
// 				threads.back().join();
				t.join();
				/* übung 6
				Robot* robInsane = new RobotInsane(
							start.x, start.y, lab);
				robots.push_back(robInsane);
				*/
				gCout.lock();
				std::cout 
					<< "-t3 gestartet." 
					<< std::endl;
				gCout.unlock();
			} else {
				gCout.lock();
				std::cout << it[0] 
					<< " unbekannter Roboter Typ" 
					<< std::endl;
				gCout.unlock();
			}
		}
	}
	
	/* übung 6
	// roboter starten
	for(auto& it : robots) {
		robotResult result;
		result.steps = it->start();
		result.name = it->getName();
		if(cmdOptionExists(argv, argv+argc, "-p")) {
			it->showPath();
		}
		stepsPerRobot.push_back(result);
		delete it;
	}

	for(auto& it: stepsPerRobot) {
		std::cout << "Roboter: " << it.name 
		<< " Schritte: " << it.steps << std::endl;
	}
	*/
	return 0;
}
