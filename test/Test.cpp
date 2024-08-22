#include <gtest/gtest.h>
#include <iostream>
#include "../include/SlotMachine.h"
#include "../include/SlotMachineConfig.h"


TEST(slotMachine, rewardScattersOnly)
{		
	// Scatters symbol doesn't need to be on winning lines, only the number of scatter symbols matters, 
	// but maximum one Scatter symbol per reel is counted, so maximum Scatter symbol multiplier is equal to reels number

	// *** prepare *** ///
	const int ROWS = 3;
	const int REELS = 5;
	const int BET = 1;
	const int SYMBOLS[] =
		{ 
			0,0,0,0,0,
			0,0,0,0,0,
			0,0,0,0,0,
		};
	const float expectedReward = 50.f; // reward for 5 x Scatter symbol

	// *** act *** ///
	// create Slot Machine instance
	const std::vector<std::vector<Symbol>> reelsConfig = configureReels();
	SlotMachine<REELS, ROWS> slotMachine(reelsConfig);
	
	// set Slot Machine assumed state to test
	slotMachine.setMachineState(SYMBOLS);
	float value = slotMachine.calculateResult(BET);

	// *** assert *** ///
	EXPECT_EQ(expectedReward, value);
}

TEST(slotMachine, rewardLemonOnly)
{
	// Because a one sign is present on every slot, every possible winning line will be score for maximum possible reward of the sign

	// *** prepare *** ///
	const int ROWS = 3;
	const int REELS = 5;
	const int BET = 1;
	const int SYMBOLS[] =
		{
			2,2,2,2,2,
			2,2,2,2,2,
			2,2,2,2,2
		};
	const float expectedReward = 20 * 10.f; //20 possible lines x 10 credits for 5 Lemons in a line

	// *** act *** ///
	// create Slot Machine instance
	const std::vector<std::vector<Symbol>> reelsConfig = configureReels();
	SlotMachine<REELS, ROWS> slotMachine(reelsConfig);
	
	// set Slot Machine assumed state to test
	slotMachine.setMachineState(SYMBOLS);
	float value = slotMachine.calculateResult(BET);

	// *** assert *** ///
	EXPECT_EQ(expectedReward, value);
}

TEST(slotMachine, rewardSevenOnly)
{
	// *** prepare *** ///
	const int ROWS = 3;
	const int REELS = 5;
	const int BET = 1;
	const int SYMBOLS[] = 
		{ 
			7,7,7,7,7,
			7,7,7,7,7,
			7,7,7,7,7,
		};
	const float expectedReward =  305.f; //20 possible lines x 250 credits for 5 Sevens in a line, but maximum reward for the game is 305 x bet rate

	// *** act *** ///
	// create Slot Machine instance
	const std::vector<std::vector<Symbol>> reelsConfig = configureReels();
	SlotMachine<REELS, ROWS> slotMachine(reelsConfig);
	
	// set Slot Machine assumed state to test
	slotMachine.setMachineState(SYMBOLS);
	float value = slotMachine.calculateResult(BET);

	// *** assert *** ///
	EXPECT_EQ(expectedReward, value);
}

TEST(slotMachine, loss)
{
	
	// *** prepare *** ///
	const int ROWS = 3;
	const int REELS = 5;
	const int BET = 1;
	const int SYMBOLS[] = 
		{ 
			2,5,2,6,7,
			3,6,3,6,0,
			4,6,4,7,1
		};

	// line no. | sign no.| reward
	// I          3         0
	// II         2         0
	// III        4         0
	// IV         2         0 
	// V          2         0
	// VI         4         0 
	// VII        3         0
	// VIII       3         0
	// IX         2         0
	// X          4         0
	// XI         4         0
	// XII        4         0
	// XIII       2         0
	// XIV        2         0
	// XV         2         0
	// XVI        4         0
	// XVII       2         0
	// XVIII      4         0
	// XIX        4         0
	// XX         2         0
	// SCATTER    0         0
	// SUM                  0


	const float expectedReward = 0.f; 
	
	// *** act *** ///
	// create Slot Machine instance
	const std::vector<std::vector<Symbol>> reelsConfig = configureReels();
	SlotMachine<REELS, ROWS> slotMachine(reelsConfig);
	
	// set Slot Machine assumed state to test
	slotMachine.setMachineState(SYMBOLS);
	float value = slotMachine.calculateResult(BET);

	// *** assert *** ///
	EXPECT_EQ(expectedReward, value);
}

TEST(slotMachine, payline_1)
{
	// Check the 1. payline scoring by the Orange symbol
	
	// *** prepare *** ///
	const int ROWS = 3;
	const int REELS = 5;
	const int BET = 1;
	const int SYMBOLS[] = 
		{ 
			1,2,1,1,1,
			3,3,3,3,3,
			1,2,1,1,1
		};
	const float expectedReward = 10.f; // 10 credits for 5 x Orange symbol

	// *** act *** ///
	// create Slot Machine instance
	const std::vector<std::vector<Symbol>> reelsConfig = configureReels();
	SlotMachine<REELS, ROWS> slotMachine(reelsConfig);
	
	// set Slot Machine assumed state to test
	slotMachine.setMachineState(SYMBOLS);
	float value = slotMachine.calculateResult(BET);

	// *** assert *** ///
	EXPECT_EQ(expectedReward, value);
}

TEST(slotMachine, payline_4_11_18)
{
	
	// *** prepare *** ///
	const int ROWS = 3;
	const int REELS = 5;
	const int BET = 1;
	const int SYMBOLS[] = 
		{ 
			4,5,5,1,6,
			5,5,6,2,6,
			6,6,7,2,7 
		};

	// line no. | sign no.| reward
	// I          5         0
	// II         4         0
	// III        6         0
	// IV         5         2.5 
	// V          4         0
	// VI         6         0 
	// VII        5         0
	// VIII       5         0
	// IX         4         0
	// X          6         0
	// XI         6         2.5
	// XII        6         0
	// XIII       4         0
	// XIV        4         0
	// XV         4         0
	// XVI        6         0
	// XVII       4         0
	// XVIII      6         2.5
	// XIX        6         0
	// XX         4         0
	// SCATTER    0         0
	// SUM                  7.5

	const float expectedReward = 7.5f; 
	
	// *** act *** ///
	// create Slot Machine instance
	const std::vector<std::vector<Symbol>> reelsConfig = configureReels();
	SlotMachine<REELS, ROWS> slotMachine(reelsConfig);
	
	// set Slot Machine assumed state to test
	slotMachine.setMachineState(SYMBOLS);
	float value = slotMachine.calculateResult(BET);

	// *** assert *** ///
	EXPECT_EQ(expectedReward, value);
}

TEST(slotMachine, payline_4_10_18)
{
	
	// *** prepare *** ///
	const int ROWS = 3;
	const int REELS = 5;
	const int BET = 1;
	const int SYMBOLS[] = 
		{ 
			4,5,5,6,6,
			5,5,6,6,6, 
			6,6,7,7,7 
		};

	// line no. | sign no.| reward
	// I          5         0
	// II         4         0
	// III        6         0
	// IV         5         2.5 
	// V          4         0
	// VI         6         0 
	// VII        5         0
	// VIII       5         0
	// IX         4         0
	// X          6         25
	// XI         6         0
	// XII        6         0
	// XIII       4         0
	// XIV        4         0
	// XV         4         0
	// XVI        6         0
	// XVII       4         0
	// XVIII      6         25
	// XIX        6         0
	// XX         4         0
	// SCATTER    0         0
	// SUM                  52.5

	const float expectedReward = 52.5f; 
	
	// *** act *** ///
	// create Slot Machine instance
	const std::vector<std::vector<Symbol>> reelsConfig = configureReels();
	SlotMachine<REELS, ROWS> slotMachine(reelsConfig);
	
	// set Slot Machine assumed state to test
	slotMachine.setMachineState(SYMBOLS);
	float value = slotMachine.calculateResult(BET);

	// *** assert *** ///
	EXPECT_EQ(expectedReward, value);
}

TEST(resultCalculator, reportSummary)
{	
	// Test corectness of a report summary generated by ResultCalculator class on given example of input Machine state.
	// The test analysis report members step by step to compare calculated results with expected ones.

	// *** prepare *** ///
	const int ROWS = 3;
	const int REELS = 5;
	const int BET = 2;
	const int SYMBOLS[] = 
		{ 
			4,5,5,6,6,
			5,5,6,6,6, 
			6,6,7,7,7 
		};
	const float expectedReward = 52.5f * BET; 
	int totalHits = 1 + 2; // 1 hit for Grape + 2 hits for Watermelon (see details below)
	
	// *** act *** ///
	// create Slot Machine instance
	const std::vector<std::vector<Symbol>> reelsConfig = configureReels();
	SlotMachine<REELS, ROWS> slotMachine(reelsConfig);
	
	// set Slot Machine assumed state to test
	slotMachine.setMachineState(SYMBOLS);
	float value = slotMachine.calculateResult(BET);
	auto report = slotMachine.getReport(BET);

	// *** assert *** ///
	auto &grapeReport = report.summaryBySymbol[Symbol::Grape][3]; // only 3 Grapes occurs in all paylines
	float GRAPE_REWARD = 2.5f; // reward multiplier for 3 Grapes 
	ASSERT_EQ(grapeReport.hits, 1); // check if 3 x Grape occured one time (IV line)
	ASSERT_EQ(grapeReport.hitsPercent, 100.f * grapeReport.hits / totalHits);
	ASSERT_EQ(grapeReport.multiplier, BET * GRAPE_REWARD); // bet rate * reward for 3 Grapes in the line (2.5 credits)
	ASSERT_EQ(grapeReport.totalRewards, 1 * BET * GRAPE_REWARD); // 1 hit per the reward
	ASSERT_EQ(grapeReport.rewardsPercent, 100.f * grapeReport.totalRewards / expectedReward); //percent of the total reward
	ASSERT_EQ(grapeReport.winFrequency, 1); // win frequency - the result occured in one won game, so frequency is 1
	ASSERT_EQ(grapeReport.resultFrequency, 1); // result frequency - the result occured in one of all games, so frequency is 1

	auto &watermelonReport = report.summaryBySymbol[Symbol::Watermelon][5]; // only 5 Watermelon occurs in all paylines
	float WATERMELON_REWARD = 25; // reward multiplier for 3 Grapes
	ASSERT_EQ(watermelonReport.hits, 2); // check if 5 x Watermelon occured two times (X, XVIII lines)
	ASSERT_EQ(watermelonReport.hitsPercent, 100.f * watermelonReport.hits / totalHits);
	ASSERT_EQ(watermelonReport.multiplier, BET * WATERMELON_REWARD); // bet rate * reward for 5 Watermelon in the line (25 credits)
	ASSERT_EQ(watermelonReport.totalRewards, 2 * BET * WATERMELON_REWARD); // 2 hit per the reward
	ASSERT_EQ(watermelonReport.rewardsPercent, 100.f * watermelonReport.totalRewards / expectedReward); //percent of the total reward
	ASSERT_EQ(watermelonReport.winFrequency, 0.5f); // win frequency - the result occured 2 times in one won game, so frequency is 0.5
	ASSERT_EQ(watermelonReport.resultFrequency, 0.5f); // result frequency - the result occured 2 times in one of all games, so frequency is 0.5
}

int main(int argc, char* argv[])
{
	std::cout << "Tests for SlotMachineSimulator program..." << std::endl;
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();    
}