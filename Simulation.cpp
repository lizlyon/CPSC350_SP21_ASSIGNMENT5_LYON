#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Simulation.h"
#include "Student.h"
#include "Window.h"

using namespace std;

//constructor initializer list
Simulation::Simulation() : regWindow(NULL), numWindows(0){}

Simulation::~Simulation(){
	//while not empty
	while (!doneQueue.isEmpty()){
		//delete/deallocate if queue is not empty
		delete doneQueue.front();
		//pop the front of doneQueue
		doneQueue.pop();
	}
	//deallocate memory
	delete[] regWindow;
}

//runs the program and reads in the command line argument
void Simulation::run(const string& filename){
	ifstream inFile(filename);
	//read in the filename
	//first line is the number of windows
	inFile >> numWindows;
	//allocate new memory for regWindow
	regWindow = new Window[numWindows];
	//initialize variables
	int clockTime = 0, tick = 0, numStudents = 0, undergrad = 0;
	//set the student work time to true so the simulation can run
	bool work = true;

	while (work){
		//call method that increments the work time
		incrementWorkTime();
		//if the clock is 0 or the clock is greater than the tick count
		if (clockTime == 0 || clockTime > tick){
			if (!inFile.eof()){
        //read tick and extract white space
				inFile >> tick >> ws;
      }
		}
		//if the clock equals the tick count
		else if (clockTime == tick){
			if (!inFile.eof()){
        //read in the number of students
				inFile >> numStudents >> ws;
      }
			for (int i = 0; i < numStudents; i++){
				if (!inFile.eof()){
					//set the studentTime to 0
					int studentTime = 0;
          //read in time students needs for session
					inFile >> studentTime >> ws;
					//then push them to waitqueue
					waitQueue.push(new Student(++undergrad, studentTime));
				}
			}
		}

    //if the wait queue is not empty
		if (!waitQueue.isEmpty()){
      //assign window number the return value of method
			int windowNumber = checkForOpenWindow();

			//if the window number is not -1
			if (windowNumber != -1){
				regWindow[windowNumber].greetStudent(waitQueue.front());
				//pop what's in the waitQueue
				waitQueue.pop();
			}
		}

		//if the clock is greater than 0
		if (clockTime > 0){
			//call the incrementIdleAndWaitTimes method
			incrementIdleAndWaitTimes();

			//if the waitQueue is empty and all the windows are open
			if (waitQueue.isEmpty() && areAllWindowsOpen()){
				//then assign false to work
				work = false;
      }
		}
		//incremennt the clock
		clockTime++;
	}
	//call print method to output the metrics
	printMetrics();
}

//check all the windows
bool Simulation::areAllWindowsOpen(){
  //initialize variable
	int count = 0;
	for (int i = 0 ; i < numWindows; i++){
		//if not occupied
		if (!regWindow[i].occupied()){
			//increment the count
			count++;
		}
	}
	//return the count equal to number of windows
	return count == numWindows;
}

bool Simulation::isOccupied(){
  //initialize variable
	int count = 0;
	for (int i = 0; i < numWindows; i++){
		//if the window is occupied
		if (regWindow[i].occupied()){
			//then increment the count
			count++;
		}
	}
	//return the count equal to number of windows
	return count == numWindows;
}

//checks for an open window
int Simulation::checkForOpenWindow(){
	for (int i = 0; i < numWindows; i++){
		//if the window is not occupied
		if (!regWindow[i].occupied()){
			//return the open window
			return i;
		}
	}
	//if error occurs
	return -1;
}

void Simulation::incrementIdleAndWaitTimes(){
	//set unoccupied windows idle time
	for (int i = 0; i < numWindows; i++){
		if (!regWindow[i].occupied()){
			regWindow[i].setIdleTime();
		}
	}

	//set students wait time if they are waiting in wait queue
	if (waitQueue.size() == 1){
		waitQueue.front()->setWaitTime();
	}
	//otherwise
	else{
		for (int i = 0; i < waitQueue.size(); i++){
			Student* s = waitQueue.front();
			s->setWaitTime();
			//pop and push the waitQueue
			waitQueue.pop();
			waitQueue.push(s);
		}
	}
}

//keep track and increment the students work time in session
void Simulation::incrementWorkTime(){
	for (int i = 0; i < numWindows; i++){
		//if the register window is occupied
		if (regWindow[i].occupied()){
			//then isDone is the
			bool isDone = regWindow[i].registerStudent();

			if (isDone){
				//when students are done with their session push on the done queue
				doneQueue.push(regWindow[i].endSession());
				//call the goodByeStudent method to null them out
				regWindow[i].goodByeStudent();
			}
		}
	}
}

void Simulation::printMetrics(){
  //initialize variables
	int max = 0, sum = 0, studentID = 0, tenMinutesWait = 0;
	for (int i = 0; i < doneQueue.size(); i++){
		Student* s = doneQueue.front();
		//get the students wait time to find max
		if (s->getWaitTime() > max){
			max = s->getWaitTime();
			studentID = s->getStudentID();
    }

		//add up the studets waiting over 10 mins
		if (s->getWaitTime() > 10){
			tenMinutesWait++;
    }
		//sum up wait times for students
		sum += s->getWaitTime();
		//pop and push the students in doneQueue
		doneQueue.pop();
		doneQueue.push(s);
	}
	//compute the mean and median and cast them as doubles
	double mean = static_cast<double>(sum / static_cast<double>(doneQueue.size()));
	double median = static_cast<double>(sum / 2.0);

	//wait time console output with set percision
	cout << fixed << setprecision(2) << "\nStudent mean wait time: " << mean  << " minute(s)"<< endl;
	cout << fixed << setprecision(2) << "Student median wait time: " << median << " minute(s)" << endl;
	cout << "Student #" << studentID << " had the longest wait time of: " << max << " minute(s)" << endl;
	cout << "# of students waiting over 10 minutes: " << tenMinutesWait << " student(s)"<< endl;

	//reset the variables to 0 for future use
	max = sum = 0;
	//initialize new variables
	int	windowID = 0, fiveMinutesWait = 0;
	for (int i = 0; i < numWindows; i++){
		if (regWindow[i].getIdleTime() > max){
			//assing the max by calling the getIdleTime method for the regWindows
			max = regWindow[i].getIdleTime();
			//check the next window
			windowID = i + 1;
		}

		//check if any windows had idle times over 5 mins
		if (regWindow[i].getIdleTime() > 5){
			//incremenet variable if the idle time is greater than 5
			fiveMinutesWait++;
		}
		//sum up the idle times
		sum += regWindow[i].getIdleTime();
	}
	//compute the mean and cast the outcome as a double
	mean = static_cast<double>(sum / static_cast<double>(numWindows));
  //idle time console output
  cout << "---------------------------------------------------" << endl;
	cout << fixed << setprecision(2) << "Window mean idle time: " << mean  << " minute(s)"<< endl;
	cout << fixed << setprecision(2) << "Longest window idle time: " << max << " minute(s)" << endl;
	cout << "# of windows idle for over 5 minutes: " << fiveMinutesWait << " window(s)"<< endl << endl;
}
