#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include <random>

namespace RandomNumberGenerator
{ 
	
	int getRandomNumber(const int a, const int b)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(a, b);

		return dis(gen);
	}
}
#endif // !RANDOM_NUMBER_GENERATOR_H

