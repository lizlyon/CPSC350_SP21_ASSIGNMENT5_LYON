#include <iostream>
#include "Window.h"
#include "Student.h"

//constructor initializer list
Window::Window(int id) : isOccupied(false), id(id), student(NULL){
	idleTime = studentTime = workTime = 0;
}

Window::~Window(){}

//returns window idle time
int Window::getIdleTime(){
	return idleTime;
}

//sets window idle time
void Window::setIdleTime(){
	idleTime++;
}

//returns if window is occupied
bool Window::occupied(){
	return isOccupied;
}

void Window::greetStudent(Student* student){
	//window is occupied by greeting the student
	isOccupied = true;
	//initialize member variable
	this->student = student;
	//assign the students session time
	studentTime = student->getSessionTime();
	//students not yet in advising session, so assign 0 to work time
	workTime = 0;
}

bool Window::registerStudent(){
	//increment the work time
	++workTime;
	//itterate until the work time equals the student time to register the student
	return workTime == studentTime;
}

//returns the student pointer
Student* Window::endSession(){
	//not occupied anymore
	isOccupied = false;
	//return the student to get their metrics
	return student;
}

void Window::goodByeStudent(){
	//when students are done(empty) in queue, assign null
	student = NULL;
}
