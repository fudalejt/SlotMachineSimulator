#ifndef REWARD_TABLE_H
#define REWARD_TABLE_H

#include <map>

#include "Symbol.h"

class RewardTable
{
public:
	static float getScatterReward(int occurences);
	static float getCherryReward(int occurences);
	static float getLemonReward(int occurences);
	static float getOrangeReward(int occurences);
	static float getPlumReward(int occurences);
	static float getGrapeReward(int occurences);
	static float getWatermelonReward(int occurences);
	static float getSevenReward(int occurences);

	static float getReward(Symbol symbol, int occurences);

private:
	typedef float (*RewardFromSymbols)(int);
	static const std::map<Symbol, RewardFromSymbols> rewardFuncsMap;
};

#endif