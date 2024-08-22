#ifndef SLOT_MACHINE_H
#define SLOT_MACHINE_H

#include <string>
#include <stdexcept>
#include <array>
#include <cstdlib>

#include "Reel.h"
#include "Symbol.h"
#include "ResultCalculator.h"
#include "Report.h"

template <int reelsCount, int rowsCount>
class SlotMachine
{
public:
	// typedefs
	typedef std::array<std::array<Symbol, rowsCount>, reelsCount> MachineState;

	// methods
	SlotMachine(const std::vector<std::vector<Symbol>>& reelsConfig);
	void pullTheHandle();
	MachineState getMachineState();
	void setMachineState(MachineState newState);
	void setMachineState(const int symbols[reelsCount * rowsCount]);
	float calculateResult(float bet);
	const ReportSummary& getReport(float bet);

private:
	//variables
	std::vector<Reel> reels;
	ResultCalculator<reelsCount, rowsCount> resultCalculator;
	MachineState machineState;
};

template<int reelsCount, int rowsCount>
inline SlotMachine<reelsCount, rowsCount>::SlotMachine(const std::vector<std::vector<Symbol>>& reelsConfig)
{
	if (reelsCount != reelsConfig.size())
	{
		throw std::invalid_argument("Invalid SlotMachine configuration. The number of reels (reelsCount) is different from 'reelsConfig' size. \n reelsCount == " + std::to_string(reelsCount) + ", reelsConfig.size == " + std::to_string(reelsConfig.size()));
	}
	for (auto it = reelsConfig.begin(); it < reelsConfig.end(); ++it)
	{
		reels.push_back(std::vector<Symbol>(*it));
	}
}

template<int reelsCount, int rowsCount>
inline void SlotMachine<reelsCount, rowsCount>::pullTheHandle()
{
	std::array<std::array<Symbol, rowsCount>, reelsCount> result;
	for (int reelIdx = 0; reelIdx < reelsCount; ++reelIdx)
	{
		int symbolIdx = rand();
		for (int rowIdx = 0; rowIdx < rowsCount; ++rowIdx)
		{
			result[reelIdx][rowIdx] = reels[reelIdx].getSymbol(symbolIdx + rowIdx); // getSymbol takes symbols from a reel circulary - returns to the start of reel if exceeds the reel size
		}
	}
	machineState = result;
}

template<int reelsCount, int rowsCount>
inline typename SlotMachine<reelsCount, rowsCount>::MachineState SlotMachine<reelsCount, rowsCount>::getMachineState()
{
	return machineState;
}

template<int reelsCount, int rowsCount>
inline void SlotMachine<reelsCount, rowsCount>::setMachineState(MachineState newState)
{
	machineState = newState;
}

template <int reelsCount, int rowsCount>
inline void SlotMachine<reelsCount, rowsCount>::setMachineState(const int symbols[reelsCount * rowsCount])
{
	std::array<std::array<Symbol, rowsCount>, reelsCount> state;
	int idx = 0;
	for (int rowsIdx = 0; rowsIdx < rowsCount; ++rowsIdx)
	{
		for (int reelsIdx = 0; reelsIdx < reelsCount; ++reelsIdx)
		{
			state[reelsIdx][rowsIdx] = (Symbol)symbols[idx];
			idx++;
		}
	}
	machineState = state;
}

template<int reelsCount, int rowsCount>
inline float SlotMachine<reelsCount, rowsCount>::calculateResult(float bet)
{
	return resultCalculator.calculateMachineStateValue(this->machineState, bet);
}

template<int reelsCount, int rowsCount>
inline const ReportSummary& SlotMachine<reelsCount, rowsCount>::getReport(float bet)
{
	return resultCalculator.getReport(bet);
}

#endif