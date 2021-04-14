#ifndef STUDENT_H
#define STUDENT_H

//student class
class Student{
public:
	Student(int id, int sessionTime);
	~Student();
	int getSessionTime();
	int getStudentID(); 	
	int getWaitTime(); 		//gets the wait time
	void setWaitTime();		//sets the wait time

private:
	int id;								//student id
	int sessionTime;			//time student is in their advising session
	int waitTime;					//time student is in the queue
};
#endif
