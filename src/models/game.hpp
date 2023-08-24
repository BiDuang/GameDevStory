#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <random>
#include <vector>

#include <optional>

class Product {
public:
	std::string name;
	unsigned int createDay;
	unsigned int interesting;
	unsigned int playability;
	unsigned int graphics;
	unsigned int sound;
	unsigned int stability;

	unsigned long long sales;
	unsigned long long profit;

	Product(std::string name, unsigned int createDay, unsigned int interesting,
		unsigned int playability, unsigned int graphics, unsigned int sound, unsigned int stability) :
		name(name), createDay(createDay), interesting(interesting), playability(playability),
		graphics(graphics), sound(sound), stability(stability)
	{
		sales = 0;
		profit = 0;
	}
};

class Stuff {
public:
	unsigned short program;
	unsigned short art;
	unsigned short audio;
	unsigned short design;
	unsigned int happiness;
	unsigned int salary;

	Stuff(unsigned short program, unsigned short art, unsigned short audio,
		unsigned short design, unsigned int happiness, unsigned int salary) :
		program(program), art(art), audio(audio), design(design), happiness(happiness), salary(salary)
	{}

	Stuff(unsigned int day) {

	}
};

class Studio {
public:
	std::string name;
	std::vector<Stuff> stuffs;
	std::vector<Product> finishedProducts;
};

class GameData {
private:
	unsigned short devProgress = 0;
public:
	unsigned int day = 0;
	bool isDeveloping = false;
	int money = 0;
	std::optional<Product> workingProduct = std::nullopt;

	void RoundDev(double bonus) {
		unsigned short basicProgress = 1 + rand() % 5;
		devProgress += basicProgress * bonus;
		if (devProgress >= 100) {
			isDeveloping = false;
		}
	}

	unsigned short GetDevProgress() {
		return devProgress;
	}
};
#endif // !GAME_HPP
