#include "../include/RewardTable.h"
#include <stdexcept>

const std::map<Symbol, RewardTable::RewardFromSymbols> RewardTable::rewardFuncsMap(
	{ 
		{Symbol::Scatter, RewardTable::getScatterReward},
		{Symbol::Cherry, RewardTable::getCherryReward},
		{Symbol::Lemon, RewardTable::getLemonReward},
		{Symbol::Orange, RewardTable::getOrangeReward},
		{Symbol::Plum, RewardTable::getPlumReward},
		{Symbol::Grape, RewardTable::getGrapeReward},
		{Symbol::Watermelon, RewardTable::getWatermelonReward},
		{Symbol::Seven, RewardTable::getSevenReward},
	});

float RewardTable::getScatterReward(int occurences)
{
	switch (occurences)
	{
	case 3:
		return 2.f;
	case 4:
		return 10.f;
	case 5:
		return 50.f;
	default:
		return 0.f;
	}
}

float RewardTable::getCherryReward(int occurences)
{
	switch (occurences)
	{
	case 2:
		return 0.25f;
	case 3:
		return 1.f;
	case 4:
		return 2.5f;
	case 5:
		return 10.f;
	default:
		return 0.f;
	}
}

float RewardTable::getLemonReward(int occurences)
{
	switch (occurences)
	{
	case 3:
		return 1.f;
	case 4:
		return 2.5f;
	case 5:
		return 10.f;
	default:
		return 0.f;
	}
}

float RewardTable::getOrangeReward(int occurences)
{
	switch (occurences)
	{
	case 3:
		return 1.f;
	case 4:
		return 2.5f;
	case 5:
		return 10.f;
	default:
		return 0.f;
	}
}

float RewardTable::getPlumReward(int occurences)
{
	switch (occurences)
	{
	case 3:
		return 1.f;
	case 4:
		return 2.5f;
	case 5:
		return 10.f;
	default:
		return 0.f;
	}
}

float RewardTable::getGrapeReward(int occurences)
{
	switch (occurences)
	{
	case 3:
		return 2.5f;
	case 4:
		return 10.f;
	case 5:
		return 25.f;
	default:
		return 0.f;
	}
}

float RewardTable::getWatermelonReward(int occurences)
{
	switch (occurences)
	{
	case 3:
		return 2.5f;
	case 4:
		return 10.f;
	case 5:
		return 25.f;
	default:
		return 0.f;
	}
}

float RewardTable::getSevenReward(int occurences)
{
	switch (occurences)
	{
	case 3:
		return 5.f;
	case 4:
		return 50.f;
	case 5:
		return 250.f;
	default:
		return 0.f;
	}
}

float RewardTable::getReward(Symbol symbol, int occurences)
{
	try
	{
		return rewardFuncsMap.at(symbol)(occurences);
	}
	catch (std::out_of_range)
	{
		return 0.0f;
	}
}
