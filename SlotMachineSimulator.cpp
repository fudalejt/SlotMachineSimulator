#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <iomanip>
#include <memory>
#include <chrono>

#include "include/SlotMachine.h"
#include "include/Symbol.h"
#include "include/Payline.h"
#include "include/Range.h"
#include "include/ProgramParameters.h"
#include "include/SlotMachineConfig.h"

using namespace std;

typedef Range<float> RewardRange;


namespace SymbolHelper
{
	const std::map<Symbol, std::string> SYMBOL_NAMES = {
		  {Symbol::Scatter, "Scatter"},
		  {Symbol::Cherry, "Cherry"},
		  {Symbol::Grape, "Grape"},
		  {Symbol::Lemon, "Lemon"},
		  {Symbol::Orange, "Orange"},
		  {Symbol::Plum, "Plum"},
		  {Symbol::Watermelon, "Watermelon"},
		  {Symbol::Seven, "Seven"}
	};
}

template<int REELS, int ROWS>
void printMachineState(const std::array<std::array<Symbol, ROWS>, REELS>& state)
{
	for (int y = 0; y < ROWS; ++y)
	{
		for (int x = 0; x < REELS; ++x)
		{
			std::cout << state[x][y] << " ";
		}
		std::cout << std::endl;
	}
}

void prepareReportCategoryStatistics(const ReportSummary& report)
{
	int sum = 0;
	std::vector<std::pair<RewardRange, int>> categories;
	categories.push_back({ RewardRange(0, 0), 0 });
	categories.push_back({ RewardRange(0, 1), 0 });
	categories.push_back({ RewardRange(1, 5) , 0 });
	categories.push_back({ RewardRange(5, 10) , 0 });
	categories.push_back({ RewardRange(10, 20) , 0 });
	categories.push_back({ RewardRange(20, 50) , 0 });
	categories.push_back({ RewardRange(50, 150) , 0 });
	categories.push_back({ RewardRange(150, 250) , 0 });
	categories.push_back({ RewardRange(250, 300) , 0 });
	categories.push_back({ RewardRange(300, 306) , 0 });

	for (auto symbolIter = report.summaryBySymbol.begin(); symbolIter != report.summaryBySymbol.end(); ++symbolIter)
	{
		auto symbol = symbolIter->first;
		auto occurencesMap = symbolIter->second;
		for (auto occurIter = symbolIter->second.begin(); occurIter != symbolIter->second.end(); ++occurIter)
		{
			auto &stats = occurIter->second; 						 	
			for (int catIdx = 0; catIdx < categories.size(); ++catIdx)
			{
				if (categories[catIdx].first.isInRange(stats.multiplier))
				{
					categories[catIdx].second += stats.hits;
					sum += stats.hits;
					break;
				}
			}
		}
	}

	for (int i = 0; i < categories.size(); ++i)
	{
		std::cout << "Values in (" << categories[i].first.from << ", " << categories[i].first.to << ") : " << 100.f * categories[i].second / sum << "%" << std::endl;
	}
}

int main(int argc, char *argv[])
{	
	auto startTime = std::chrono::high_resolution_clock::now();

	try
	{
		srand(time(0));

		std::cout << "***********************************************" << std::endl;
		std::cout << "*** SlotMachineSimulator program is started *** " << std::endl;

		ProgramParameters parameters(argc, argv);

		//validate program parameters
		if (parameters.symbols && (parameters.gamesCount || parameters.startCredit || parameters.creditOutFile))
		{
			std::string errorMessage = "The program argument error: cannot use -symbols argument with ";
			errorMessage += (parameters.gamesCount != nullptr) ? "-gamesCount " : "";
			errorMessage += (parameters.startCredit != nullptr) ? "-startCredit " : "";
			errorMessage += (parameters.creditOutFile != nullptr) ? "-creditOutFile " : "";
			errorMessage += '.';
			throw std::invalid_argument(errorMessage);
		}

		const int ROWS = 3;
		const int REELS = 5;
		const int BET = (parameters.bet != nullptr) ? *parameters.bet : 1;

		const std::vector<std::vector<Symbol>> reelsConfig = configureReels();

		if (parameters.symbols)
		{
			auto& SYMBOLS = parameters.symbols;
			SlotMachine<REELS, ROWS> slotMachine(reelsConfig);
			slotMachine.setMachineState(SYMBOLS);
			float value = slotMachine.calculateResult(BET);
			auto state = slotMachine.getMachineState();
			printMachineState<REELS, ROWS>(state);
			std::cout << "Reward : " << value << std::endl << std::endl;
			if(*parameters.extendedOutput)
				std::cout <<"Bet rate : " << BET << std::endl;
		}
		else
		{
			int games_count = (parameters.gamesCount != nullptr) ? *parameters.gamesCount : 1;
			int startCredits = (parameters.startCredit != nullptr) ? *parameters.startCredit : 0;
			int credits = startCredits;

			std::ofstream creditOutFile;
			if(parameters.creditOutFile != nullptr)
				creditOutFile = std::ofstream(*parameters.creditOutFile);

			SlotMachine<REELS, ROWS> slotMachine(reelsConfig);

			// simulate a slot machine
			float resultsSum = credits;
			for (int i = 0; i < games_count; ++i)
			{
				slotMachine.pullTheHandle();
				std::array<std::array<Symbol, ROWS>, REELS>  state = slotMachine.getMachineState();
				float valueChange = slotMachine.calculateResult(BET) - BET;
				resultsSum += valueChange;
				if(parameters.extendedOutput)
				{
					printMachineState<REELS, ROWS>(state);
					std::cout << "REWARD : " << valueChange + BET << std::endl;
					std::cout << "Player credits : " << std::fixed << std::setprecision(1) << resultsSum << std::endl;
				}		
				if(creditOutFile)
					creditOutFile << std::fixed << std::setprecision(1) << resultsSum << std::endl;
			}

			// generate a report
			const ReportSummary& report = slotMachine.getReport(BET);

			// show a summary
			std::cout << std::fixed << std::setprecision(2);
			std::cout << " *** General report *** " << std::endl;
			std::cout << "Start credits : " << startCredits << std::endl;
			std::cout << "Bet rate : " << BET << std::endl;
			std::cout << "Played games : " << games_count << std::endl << std::endl;
			std::cout << "Wins : " << report.wins << std::endl;
			std::cout << "Looses : " << report.lost << std::endl;
			std::cout << "Sum of player rewards : " << report.totalRewards << " [money]" << std::endl;
			std::cout << "Sum of money placed in the bet : " << BET * games_count << " [money]" << std::endl;
			std::cout << "Final result : " << resultsSum << " [money]" << std::endl;
			std::cout << "Return To Player (RTP) : " << 100 * report.totalRewards / (BET * games_count) << "%" << std::endl;
			std::cout << "Hit Frequency (HF) : " << 100.f * report.wins / (report.wins + report.lost) << "%" << std::endl;
			std::cout << std::endl;

			//prepareReportCategoryStatistics(report);

			std::cout << std::endl;

			auto& summaryMap = report.summaryBySymbol;
			for (auto symbolIter = summaryMap.begin(); symbolIter != summaryMap.end(); ++symbolIter)
			{
				auto x = symbolIter->first;
				const std::string& symbolName = SymbolHelper::SYMBOL_NAMES.at(x);

				std::cout << " * Symbol: " << symbolName << std::endl;
				for (auto occurIter = symbolIter->second.begin(); occurIter != symbolIter->second.end(); ++occurIter)
				{
					const SymbolStats& stats = occurIter->second;
					std::cout << "Symbol: " << symbolName << " x " << occurIter->first << ", "
						<< "Multiplier = x" << stats.multiplier << ", "
						<< "Hits = " << stats.hits << ", "
						<< "Hits [%] = " << stats.hitsPercent << ", "
						<< "Total Rewards = " << stats.totalRewards << ", "
						<< "Rewards [%] = " << stats.rewardsPercent << ", "
						<< "Win Frequency = " << stats.winFrequency << ", "
						<< "Result Frequency = " << stats.resultFrequency << ", "
						<< std::endl;
				}
			}
			std::cout << std::endl;

			//close the output file
			if (creditOutFile.is_open())
			{
				creditOutFile.close();
			}			
		}
	}
	catch (std::exception& e)
	{
		std::cout << "The program execution fatal error:" << std::endl;
		std::cout << e.what() << std::endl;
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	std::cout << "SlotMachineSimulator has finished its work. Work time : " 
		<< std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms." << std::endl;
	
	return 0;
}
