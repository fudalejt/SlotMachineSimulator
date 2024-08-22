#include "../include/ProgramParameters.h"
#include <stdexcept>
#include <vector>

#include "../include/Utils.h"

ProgramParameters::ProgramParameters(int argc, char* argv[]) :
	gamesCount(nullptr),
	startCredit(nullptr),
	creditOutFile(nullptr),
	symbols(nullptr),
	extendedOutput(nullptr)
{
	for (int i = 0; i < argc; ++i)
	{
		std::string argInput = argv[i];
		if (argInput.size() > 0)
		{
			if (argInput == "-gamesCount")
			{
				try
				{
					std::string argValue = argv[i + 1];
					this->gamesCount = new int(stoi(argValue));
					i++;
				}
				catch (std::out_of_range)
				{
					throw std::invalid_argument("-gamesCount argument error: there isn't given a value for the argument");
				}
				catch (std::invalid_argument)
				{
					throw std::invalid_argument("-gamesCount argument error: the value is not a proper integer value");
				}
			}
			else if (argInput == "-startCredit")
			{
				try
				{
					std::string argValue = argv[i + 1];
					this->startCredit = new int(stoi(argValue));
					i++;
				}
				catch (std::out_of_range)
				{
					throw std::invalid_argument("-startCredit argument error: there isn't given a value for the argument");
				}
				catch (std::invalid_argument)
				{
					throw std::invalid_argument("-startCredit argument error: the value is not a proper integer value");
				}
			}
			else if (argInput == "-creditOutFile")
			{
				try
				{
					std::string argValue = argv[i + 1];
					this->creditOutFile = new std::string(argv[i + 1]);
					i++;
				}
				catch (std::out_of_range)
				{
					throw std::invalid_argument("-creditOutFile argument error: there isn't given a value for the argument");
				}
			}
			else if (argInput == "-extendedOutput")
			{
				try
				{
					this->extendedOutput = new bool(true);
				}
				catch (std::out_of_range)
				{
					throw std::invalid_argument("-extendedOutput argument error: there isn't given a value for the argument");
				}
			}
			else if (argInput == "-symbols")
			{
				try
				{
					std::string argValue = argv[i + 1];
					std::vector<std::string> splittedArgValue = splitString(argValue, ',');
					this->symbols = new int[splittedArgValue.size()];
					for (int i = 0; i < splittedArgValue.size(); ++i)
					{
						this->symbols[i] = stoi(splittedArgValue[i]);
					}
					i++;
				}
				catch (std::exception)
				{
					throw std::invalid_argument("-symbols argument error: the argument value problem on " + std::to_string(i) + " array position.");
				}
			}
		}		
	}
}



ProgramParameters::~ProgramParameters()
{
	if (gamesCount) 
		delete gamesCount;
	if (startCredit)
		delete startCredit;
	if (creditOutFile)
		delete creditOutFile;
	if (symbols)
		delete symbols;
	if (extendedOutput)
		delete extendedOutput;
}
