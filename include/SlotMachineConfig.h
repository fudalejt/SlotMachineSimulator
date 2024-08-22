#ifndef SLOT_MACHINE_CONFIG_H
#define SLOT_MACHINE_CONFIG_H

#include <vector>
#include "Symbol.h"

/*
A configuration of a slot machine reels. It decides of the the characteristic of the machine.
*/

const std::vector<std::vector<Symbol>> configureReels()
{
	std::vector<std::vector<Symbol>> reelsConfig;
	std::vector<Symbol> reel1 =
	{
		Symbol::Scatter,
		Symbol::Cherry,
		Symbol::Lemon,
		Symbol::Orange,
		Symbol::Plum,
		Symbol::Grape,
		Symbol::Watermelon,
		Symbol::Seven,
		Symbol::Cherry,
		Symbol::Orange,
		Symbol::Plum ,
		Symbol::Grape,
		Symbol::Watermelon,
		Symbol::Cherry,
		Symbol::Lemon,
		Symbol::Orange,
		Symbol::Plum ,
		Symbol::Cherry,
		Symbol::Lemon,
		
	};
	reelsConfig.push_back(reel1);

	std::vector<Symbol> reel2 =
	{
		Symbol::Scatter,
		Symbol::Cherry,
		Symbol::Lemon, Symbol::Lemon,
		Symbol::Orange,	Symbol::Orange,
		Symbol::Plum, Symbol::Plum ,
		Symbol::Grape, Symbol::Grape,
		Symbol::Watermelon, Symbol::Watermelon,
		Symbol::Seven,
		Symbol::Cherry,
		Symbol::Lemon,Symbol::Lemon,
		Symbol::Orange,
		Symbol::Plum,
		Symbol::Seven,

	};
	reelsConfig.push_back(reel2);

	std::vector<Symbol> reel3 =
	{
		Symbol::Scatter,
		Symbol::Cherry,	 Symbol::Cherry,
		Symbol::Lemon,	 Symbol::Lemon,
		Symbol::Orange,
		Symbol::Plum,
		Symbol::Grape,
		Symbol::Watermelon,
		Symbol::Seven,
		Symbol::Lemon,
		Symbol::Orange,
		Symbol::Plum ,
		Symbol::Cherry,
		Symbol::Lemon,
		Symbol::Grape,
		Symbol::Watermelon,
		Symbol::Cherry,
		Symbol::Plum ,
		Symbol::Orange,
		Symbol::Seven,

	};
	reelsConfig.push_back(reel3);

	std::vector<Symbol> reel4 =

	{
		Symbol::Scatter,
		Symbol::Cherry, Symbol::Cherry,
		Symbol::Seven,
		Symbol::Lemon, Symbol::Lemon,
		Symbol::Orange,	Symbol::Orange,	
		Symbol::Plum, Symbol::Plum ,	Symbol::Plum ,
		Symbol::Grape, Symbol::Grape,
		Symbol::Watermelon, Symbol::Watermelon,
		Symbol::Seven,
	};
	reelsConfig.push_back(reel4);

	std::vector<Symbol> reel5 =
	{
		Symbol::Scatter,
		Symbol::Cherry,	 Symbol::Cherry, Symbol::Cherry,
		Symbol::Lemon, Symbol::Lemon,
		Symbol::Seven,
		Symbol::Orange,	Symbol::Orange,
		Symbol::Plum, Symbol::Plum ,	Symbol::Plum ,
		Symbol::Grape, Symbol::Grape,
		Symbol::Watermelon, Symbol::Watermelon,
		Symbol::Seven,
	};
	reelsConfig.push_back(reel5);

	return reelsConfig;
}

#endif