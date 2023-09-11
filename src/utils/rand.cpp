#include <random>

/**
* @brief Generate a random integer.
*
* @details If the maximum value is less than the minimum value, the minimum value will be returned(no random).
*
* @param `int min` The minimum value of the random integer.
* @param `int max` The maximum value of the random integer.
*
* @return `int` The random integer.
*/
int randint(int min, int max) {
	if (max <= min) return min;
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}