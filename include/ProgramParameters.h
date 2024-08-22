#ifndef PROGRAM_PARAMETERS_H
#define PROGRAM_PARAMETERS_H

#include <string>


/*
	ProgramParamters is used to handle input program parameters.
*/
class ProgramParameters
{
public:
	ProgramParameters(int argc, char* argv[]);
	~ProgramParameters();

	int* gamesCount;
	int* startCredit;
	std::string* creditOutFile;
	int* symbols;
	bool* extendedOutput; //print additional debug information about the machine simulation state
};				  

#endif

