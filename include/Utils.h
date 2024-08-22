#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

std::vector<std::string> splitString(const std::string& inputString, const char delimiter)
{
	std::vector<std::string> splittedInput;
	std::string singleValue;
	for (int i = 0; i < inputString.size(); ++i)
	{
		const char& sign = inputString[i];
		if (sign == delimiter)
		{
			splittedInput.push_back(singleValue);
			singleValue.clear();
		}
		else if (sign != delimiter)
		{
			singleValue += sign;
		}
	}
	if (singleValue.size() > 0)
		splittedInput.push_back(singleValue);
	return splittedInput;
}

#endif