#ifndef RANGE_H
#define RANGE_H

template<typename T>
class Range
{
public:
	Range(T from, T to);
	bool isInRange(T value);
	T from, to;
};

template<typename T>
inline Range<T>::Range(T from, T to):
	to(to),
	from(from)
{
}

template<typename T>
inline bool Range<T>::isInRange(T value)
{
	if ((value >= from && value < to) || value == from)
		return true;
	else 
		return false;
}

#endif