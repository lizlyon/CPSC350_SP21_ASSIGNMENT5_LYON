#include <iostream>
#include <string>
#include "Student.h"

//constructor initializer list
Student::Student(int id, int sessionTime) : id(id), sessionTime(sessionTime), waitTime(0){}

Student::~Student(){}

//returns the session time
int Student::getSessionTime(){
  return sessionTime;
}

//returns the student id to track them
int Student::getStudentID(){
  return id;
}

//returns student wait time
int Student::getWaitTime(){
  return waitTime;
}

//increments student wait time
void Student::setWaitTime(){
  waitTime++;
}
