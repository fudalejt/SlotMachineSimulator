#ifndef RESULT_CALCULATOR_H
#define RESULT_CALCULATOR_H

#include <vector>

#include "RewardTable.h"
#include "Payline.h"
#include "Report.h"


template<int reelsCount, int rowsCount>
class ResultCalculator
{
	static const float MAX_REWARD;

public:
	ResultCalculator();
	float calculateMachineStateValue(const std::array<std::array<Symbol, rowsCount>, reelsCount>& machineState, const float bet);
	const ReportSummary& getReport(float bet);

private:
	void addPayline(std::vector<Point> points);
	
	std::vector<Payline<reelsCount, rowsCount>> paylines;
	Report report;
};

template<int reelsCount, int rowsCount>
const float ResultCalculator<reelsCount, rowsCount>::MAX_REWARD = 305.f; // from the Hot Spot 777 Crown rules

template<int reelsCount, int rowsCount>
inline ResultCalculator<reelsCount, rowsCount>::ResultCalculator()
{
	addPayline(std::vector<Point>({ Point(0,1), Point(1,1), Point(2,1), Point(3,1), Point(4,1) }));	//line 1
	addPayline(std::vector<Point>({ Point(0,0), Point(1,0), Point(2,0), Point(3,0), Point(4,0) }));	//line 2
	addPayline(std::vector<Point>({ Point(0,2), Point(1,2), Point(2,2), Point(3,2), Point(4,2) }));	//line 3
	addPayline(std::vector<Point>({ Point(0,1), Point(1,1), Point(2,0), Point(3,1), Point(4,1) }));	//line 4
	addPayline(std::vector<Point>({ Point(0,0), Point(1,1), Point(2,2), Point(3,1), Point(4,0) }));	//line 5
	addPayline(std::vector<Point>({ Point(0,2), Point(1,1), Point(2,0), Point(3,1), Point(4,2) }));	//line 6
	addPayline(std::vector<Point>({ Point(0,1), Point(1,0), Point(2,1), Point(3,0), Point(4,1) }));	//line 7
	addPayline(std::vector<Point>({ Point(0,1), Point(1,2), Point(2,1), Point(3,2), Point(4,1) }));	//line 8
	addPayline(std::vector<Point>({ Point(0,0), Point(1,0), Point(2,1), Point(3,2), Point(4,2) }));	//line 9
	addPayline(std::vector<Point>({ Point(0,2), Point(1,2), Point(2,1), Point(3,0), Point(4,0) })); //line 10
	addPayline(std::vector<Point>({ Point(0,2), Point(1,1), Point(2,0), Point(3,1), Point(4,1) })); //line 11
	addPayline(std::vector<Point>({ Point(0,2), Point(1,1), Point(2,0), Point(3,0), Point(4,0) })); //line 12
	addPayline(std::vector<Point>({ Point(0,0), Point(1,1), Point(2,2), Point(3,2), Point(4,2) })); //line 13
	addPayline(std::vector<Point>({ Point(0,0), Point(1,1), Point(2,2), Point(3,1), Point(4,1) })); //line 14
	addPayline(std::vector<Point>({ Point(0,0), Point(1,1), Point(2,0), Point(3,1), Point(4,0) })); //line 15
	addPayline(std::vector<Point>({ Point(0,2), Point(1,1), Point(2,2), Point(3,1), Point(4,2) })); //line 16
	addPayline(std::vector<Point>({ Point(0,0), Point(1,0), Point(2,1), Point(3,1), Point(4,1) })); //line 17
	addPayline(std::vector<Point>({ Point(0,2), Point(1,2), Point(2,1), Point(3,1), Point(4,1) })); //line 18
	addPayline(std::vector<Point>({ Point(0,2), Point(1,2), Point(2,2), Point(3,1), Point(4,0) })); //line 19
	addPayline(std::vector<Point>({ Point(0,0), Point(1,0), Point(2,0), Point(3,1), Point(4,2) })); //line 20
}

template<int reelsCount, int rowsCount>
inline float ResultCalculator<reelsCount, rowsCount>::calculateMachineStateValue(const std::array<std::array<Symbol, rowsCount>, reelsCount>& machineState, const float bet)
{
	float finalResult = 0.f;
	float maxReward = MAX_REWARD * bet;

	//reward from Paylines		 
	int paylineIdx = 0;
	for (auto paylineIter = paylines.begin(); paylineIter < paylines.end(); ++paylineIter)
	{
		++paylineIdx;
		Symbol symbol = machineState[0][paylineIter->getRow(0)];
		if (symbol != Symbol::Scatter)
		{
			int occurences = 1;
			for (int reelIdx = 1; reelIdx < reelsCount; ++reelIdx)
			{
				if (machineState[reelIdx][paylineIter->getRow(reelIdx)] == symbol)
				{
					occurences += 1;
				}
				else
					break;
			}
			float delta = RewardTable::getReward(symbol, occurences) * bet;
			if (delta > 0)
			{
				finalResult += delta;
			}
			// include data about the symbol to the report summary
			report.addSymbolStats(symbol, occurences, delta);
		}		
	}
	//reward from Scatters
	int scattersCounter = 0;
	for (int reelIdx = 0; reelIdx < reelsCount; ++reelIdx)
	{
		for (int rowIdx = 0; rowIdx < rowsCount; ++rowIdx)
		{
			if (machineState[reelIdx][rowIdx] == Symbol::Scatter)
			{
				++scattersCounter;
				break;
			}
		}
	}	
	float delta = RewardTable::getScatterReward(scattersCounter) * bet;
	if (delta > 0)
	{
		finalResult += delta;
		//std::cout << "Scatters number : " << scattersCounter << ". Scatters value : " << delta << std::endl;
	}
	if(scattersCounter > 0)
		// include data about the symbol to the report summary
		report.addSymbolStats(Symbol::Scatter, scattersCounter, delta);

	// adjust to the max available reward value
	if (finalResult > maxReward)
		finalResult = maxReward;

	//refresh the report
	report.passFinalResult(finalResult);

	return finalResult;
}

template<int reelsCount, int rowsCount>
inline const ReportSummary& ResultCalculator<reelsCount, rowsCount>::getReport(float bet)
{
	return report.getReport(bet);
}

template<int reelsCount, int rowsCount>
inline void ResultCalculator<reelsCount, rowsCount>::addPayline(std::vector<Point> points)
{
	Payline<reelsCount, rowsCount> payline;
	for (auto iter = points.begin(); iter < points.end(); ++iter)
	{
		payline.addPoint(iter->x, iter->y);
	}
	paylines.push_back(payline);
}

#endif