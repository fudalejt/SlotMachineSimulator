#ifndef REPORT_H
#define REPORT_H

#include <map>
#include <stdexcept>

#include "Symbol.h"

struct SymbolStats
{
	SymbolStats(float multiplier=0) :
		hits(0),
		hitsPercent(0),
		totalRewards(0),
		rewardsPercent(0),
		resultFrequency(0),
		winFrequency(0),
		multiplier(multiplier)
	{}

	int hits; // how many times the result is achived
	float hitsPercent; // an occurency percent
	float totalRewards;	// unrelative reward value
	float rewardsPercent; // percent of total reward
	float resultFrequency; //how many times the result occured by total games number
	float winFrequency; // how many times the result occured by wins number
	float multiplier; // the value for given symbol with given occurency, from game reward table
};

struct ReportSummary
{

public:
	using OccurCount = int;
	using RewardValue = float;

	std::map<Symbol, std::map<OccurCount, SymbolStats>> summaryBySymbol;
	float totalRewards;
	float theBiggestReward;
	int games;
	int wins;
	int lost;
	int totalHitCases;

	ReportSummary();
	void addSymbolStats(Symbol symbol, int occurency, float reward);
};

class Report
{
public:
	void addSymbolStats(Symbol symbol, int occurency, float reward);
	void passFinalResult(float finalReward);
	const ReportSummary& getReport(float bet);

private:
	ReportSummary reportSummary;
};

#endif