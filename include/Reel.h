#ifndef REEL_H
#define REEL_H

#include <vector>
#include "Symbol.h"

class Reel
{
public:
	Reel();
	Reel(Symbol symbolSet[], int symbolsCount);
	Reel(std::vector<Symbol> symbolSet);

	Symbol getSymbol(int index);
	void setSymbols(Symbol symbolSet[], int symbolsCount);

private:
	std::vector<Symbol> reelWheel;
};

#endif