#include "../include/Report.h"
#include "../include/RewardTable.h"

// update statistics for one symbol with given occurency
void Report::addSymbolStats(Symbol symbol, int occurency, float reward)
{
	reportSummary.addSymbolStats(symbol, occurency, reward);
}

void Report::passFinalResult(float finalReward)
{
	++reportSummary.games;
	reportSummary.totalRewards += finalReward;
	if (finalReward > 0)
		++reportSummary.wins;
	else
		++reportSummary.lost;

	if (finalReward > reportSummary.theBiggestReward)
		reportSummary.theBiggestReward = finalReward;
}

const ReportSummary& Report::getReport(float bet)
{
	auto& summaryMap = reportSummary.summaryBySymbol;
	for (auto symbolIter = summaryMap.begin(); symbolIter != summaryMap.end(); ++symbolIter)
	{
		for (auto occurIter = symbolIter->second.begin(); occurIter != symbolIter->second.end(); ++occurIter)
		{
			const Symbol& symbol = symbolIter->first;
			int occurences = occurIter->first;
			SymbolStats &stats = occurIter->second;

			stats.multiplier = RewardTable::getReward(symbol, occurences) * bet;
			stats.rewardsPercent = 100.f * stats.totalRewards / reportSummary.totalRewards;
			stats.hitsPercent = 100.f * stats.hits / reportSummary.totalHitCases;
			stats.resultFrequency = (float)reportSummary.games / stats.hits;
			stats.winFrequency = (float)reportSummary.wins / stats.hits;
		}
	}

	return reportSummary;
}

ReportSummary::ReportSummary():
	totalRewards(0),
	theBiggestReward(0),
	games(0),
	wins(0),
	lost(0),
	totalHitCases(0)
{
}

void ReportSummary::addSymbolStats(Symbol symbol, int occurency, float reward)
{
	try
	{
		if (reward > 0)
		{
			auto& stats = this->summaryBySymbol[symbol][occurency];
			stats.hits++;
			stats.totalRewards += reward;
			this->totalHitCases++;
		}		
	}
	catch (std::out_of_range) 
	{}
}
