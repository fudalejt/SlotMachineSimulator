#ifndef PAYLINE_H
#define PAYLINE_H

#include <array>
#include <string>
#include <stdexcept>
#include <cstdlib>

#include "Point.h"

template<int reelsCount, int rowsCount>
class Payline
{
public:
	Payline();
	void addPoint(int x, int y);
	int getRow(int x);

protected:
	std::array<int, reelsCount> line;
};

template<int reelsCount, int rowsCount>
inline Payline<reelsCount, rowsCount>::Payline()
{
}

template<int reelsCount, int rowsCount>
inline void Payline<reelsCount, rowsCount>::addPoint(int x, int y)
{
	if (x < 0 || x >= reelsCount)
		throw std::invalid_argument("'x' value is invalid! x == " + std::to_string(x) + ".");
	if (y < 0 || y >= rowsCount)
		throw std::invalid_argument("'y' value is invalid! y == " + std::to_string(y) + ".");

	line[x] = y;
}
template<int reelsCount, int rowsCount>
inline int Payline<reelsCount, rowsCount>::getRow(int x)
{
	return line[x];
};

#endif 
