#ifndef WINDOW_H
#define WINDOW_H

//forward class declaration
class Student;

//window class
class Window{
public:
	Window(int id = 0);
	~Window();
	int getIdleTime();
	void setIdleTime();
	void greetStudent(Student* student);
	bool occupied();
	bool registerStudent();
	void goodByeStudent();
	Student* endSession(); 		//returns the student pointer

private:
	bool isOccupied;
	int id;
	int idleTime;			//variable for cumulative idle time
	int studentTime;	//student session time
	int workTime;			//time they are in advising session
	Student* student;	//Student class pointer
};
#endif
