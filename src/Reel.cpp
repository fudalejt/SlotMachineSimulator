#include "../include/Reel.h"


Reel::Reel()
{
}

Reel::Reel(Symbol symbolSet[], int symbolsCount)
{
    for (int i = 0; i < symbolsCount; ++i)
    {
        reelWheel.push_back(symbolSet[i]);
    }
}

Reel::Reel(std::vector<Symbol> symbolSet):
    reelWheel(symbolSet)
{
}

Symbol Reel::getSymbol(int index)
{
    if (index < reelWheel.size())
        return reelWheel[index];
    else
        return reelWheel[index % reelWheel.size()];
}

void Reel::setSymbols(Symbol symbolSet[], int symbolsCount)
{
    reelWheel.clear();
    for (int i = 0; i < symbolsCount; ++i)
    {
        reelWheel.push_back(symbolSet[i]);
    }
}
