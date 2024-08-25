#ifndef RESULT_CALCULATOR_H
#define RESULT_CALCULATOR_H

#include <vector>
#include <memory>

#include "RewardTable.h"
#include "Payline.h"
#include "Report.h"
#include "LineFlowGraph.h"

template<int REELS, int ROWS>
class ResultCalculator
{
	static const float MAX_REWARD;

public:
	ResultCalculator();
	float calculateMachineStateValue(const std::array<std::array<Symbol, ROWS>, REELS>& machineState, const float bet);
	const ReportSummary& getReport(float bet);

private:
	void addPayline(std::vector<Point> points);
	float calcResultForNode(Node<REELS, ROWS> *node, Symbol symbol, float bet, const std::array<std::array<Symbol, ROWS>, REELS>& machineState, int occurences=0);
	float calcResultChange(Node<REELS, ROWS> *node, Symbol symbol, float bet, int occurences); //calculate result change for given node in the line flow graph
	
	std::vector<Payline<REELS, ROWS>> paylines; // aggregated paylines path definition
	std::unique_ptr<LineFlowGraph<REELS, ROWS>> lineFlowGraph;
	Report report;
};


template<int REELS, int ROWS>
const float ResultCalculator<REELS, ROWS>::MAX_REWARD = 305.f; // from the Hot Spot 777 Crown rules

template<int REELS, int ROWS>
inline ResultCalculator<REELS, ROWS>::ResultCalculator()
{
	paylines.reserve(20); // there are 20 paylines in the game
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

	lineFlowGraph.reset(new LineFlowGraph<REELS, ROWS>(paylines));
}

template<int REELS, int ROWS>
inline float ResultCalculator<REELS, ROWS>::calculateMachineStateValue(const std::array<std::array<Symbol, ROWS>, REELS>& machineState, const float bet)
{
	float finalResult = 0.f;
	float maxReward = MAX_REWARD * bet;

	//reward from Paylines
	for(auto& child : lineFlowGraph->getRoot()->getChildren())
	{
		Symbol symbol = machineState[0][child->row];
		if(symbol != Symbol::Scatter)
			finalResult += calcResultForNode(child.get(), symbol, bet, machineState);
	}
	
	// //reward from Scatters
	int scattersCounter = 0;
	for (int reelIdx = 0; reelIdx < REELS; ++reelIdx)
	{
		for (int rowIdx = 0; rowIdx < ROWS; ++rowIdx)
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
	}
	if(scattersCounter > 0)
	{
		// include data about the symbol to the report summary
		report.addSymbolStats(Symbol::Scatter, scattersCounter, delta);
	}	

	// adjust to the max available reward value
	if (finalResult > maxReward)
		finalResult = maxReward;

	//refresh the report
	report.passFinalResult(finalResult);

	return finalResult;
}

template<int REELS, int ROWS>
inline const ReportSummary& ResultCalculator<REELS, ROWS>::getReport(float bet)
{
	return report.getReport(bet);
}

template<int REELS, int ROWS>
inline void ResultCalculator<REELS, ROWS>::addPayline(std::vector<Point> points)
{
	Payline<REELS, ROWS> payline;
	for (auto iter = points.begin(); iter < points.end(); ++iter)
	{
		payline.addPoint(iter->x, iter->y);
	}
	paylines.push_back(payline);
}


template<int REELS, int ROWS>
inline float ResultCalculator<REELS, ROWS>::calcResultForNode(Node<REELS, ROWS> *node, Symbol symbol, float bet, const std::array<std::array<Symbol, ROWS>, REELS>& machineState, int occurences)
{
	float result = 0.f;
	if(symbol == machineState[node->reel][node->row])
	{
		for(auto childNode = node->getChildren().begin(); childNode != node->getChildren().end(); ++childNode)
		{
			result += this->calcResultForNode((*childNode).get(), symbol, bet, machineState, occurences + 1);
		}
		if(result == 0)
		{
			result += calcResultChange(node, symbol, bet, occurences);
		}
	}
	else
	{
		result += calcResultChange(node, symbol, bet, occurences);
	}	

	return result;
}

template<int REELS, int ROWS>
inline float ResultCalculator<REELS, ROWS>::calcResultChange(Node<REELS, ROWS> *node, Symbol symbol, float bet, int occurences)
{
	float delta = RewardTable::getReward(symbol, occurences) * bet * node->getLinesCount();
	if(delta > 0)
	{				
		report.addSymbolStats(symbol, occurences, delta);
		return delta;
	}
	else
		return 0;
}

#endif