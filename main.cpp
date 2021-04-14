#include <iostream>
#include "Student.h"
#include "Queue.h"
#include "Simulation.h"

using namespace std;

int main(int argc, char* argv[]){
	//instantiate object
	Simulation simulate;
	//call the run method
	simulate.run(argv[1]);

	return 0;
}
