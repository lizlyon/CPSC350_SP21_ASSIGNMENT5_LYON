#ifndef SIMULATION_H
#define SIMULATION_H
#include <string>
#include "Queue.h"

using namespace std;

//forward class declarations
class Student;
class Window;

class Simulation{
public:
	Simulation();
	~Simulation();
	void run(const string& filename); 	//runs the simulation

private:
	bool areAllWindowsOpen();
	bool isOccupied();
	int checkForOpenWindow();						
	void incrementIdleAndWaitTimes();
	void incrementWorkTime();
	void printMetrics();

	Queue<Student*> waitQueue;		//wait time queue that stores Student pointers
	Queue<Student*> doneQueue;		//done queue for students who are done w their session
	Window* regWindow;						//Window class pointer
	int numWindows;								//tracks the numbr of windows
};
#endif
