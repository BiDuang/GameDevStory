#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <random>
#include <vector>

#include <optional>

enum Platform {
	PC,
	Mobile,
	XCase,
	Zwitch,
	PS114514
};

class Product {
public:
	std::string name;
	unsigned int createDay;
	unsigned int interesting = 0;
	unsigned int playability = 0;
	unsigned int graphics = 0;
	unsigned int sound = 0;
	unsigned int stability = 0;
	Platform platform;

	unsigned long long sales;
	unsigned long long profit;

	Product(std::string name, unsigned int createDay, Platform platform) :
		name(name), createDay(createDay), platform(platform)
	{
		sales = 0;
		profit = 0;
	}
};

enum JobType {
	programmer,
	artist,
	musician,
	designer,
	almighty
};

class Stuff {
public:
	int id = 0;
	unsigned short program = 0;
	unsigned short art = 0;
	unsigned short audio = 0;
	unsigned short design = 0;
	unsigned int happiness = 0;
	unsigned int salary = 0;

	Stuff(int id, unsigned short program, unsigned short art, unsigned short audio,
		unsigned short design, unsigned int happiness, unsigned int salary) :
		id(id), program(program), art(art), audio(audio), design(design), happiness(happiness), salary(salary)
	{}

	Stuff(unsigned int day, JobType job, int stuffId) {
		id = stuffId;
		program = randint(1, (10 * (day / 5 + 1)));
		art = randint(1, (10 * (day / 5 + 1)));
		audio = randint(1, (10 * (day / 5 + 1)));
		design = randint(1, (10 * (day / 5 + 1)));

		switch (job)
		{
		case programmer:
			program *= 2;
			break;
		case artist:
			art *= 2;
			break;
		case musician:
			audio *= 2;
			break;
		case designer:
			design *= 2;
			break;
		case almighty:
			program *= 2;
			art *= 2;
			audio *= 2;
			design *= 2;
			break;
		}

		salary = randint(1500, (program + art + audio + design) > 15 ? ((program + art + audio + design) * 100) : 1600);
		happiness = 100;
	}

	void roundWork() {
		happiness -= randint(0, 3);
	}
};

class Studio {
public:
	std::string name;
	std::vector<Stuff> stuffs;
	std::vector<Product> finishedProducts;

	Studio(std::string name) : name(name) {
		stuffs = { Stuff(0,programmer,0), Stuff(0,artist,1), Stuff(0,musician,2), Stuff(0,designer,3) };
		finishedProducts = std::vector<Product>();
	}
};

class GameData {
private:
	unsigned short devProgress = 0;
public:
	unsigned int day = 0;
	short stage = 0;
	bool noConfirm = false;
	bool isFastDev = false;
	bool isDeveloping = false;
	int money = 0;
	std::optional<Product> workingProduct = std::nullopt;
	std::optional<Studio> studio = std::nullopt;

	GameData() = default;

	GameData(std::string studioName) {
		studio = Studio(studioName);
		money = 100000;
	}

	Studio GetStudio() {
		if (!studio.has_value()) {
			throw std::exception("Studio is not initialized");
		}
		return studio.value();
	}

	bool RoundDev() {
		stage++;
		if (isDeveloping) {
			unsigned short basicProgress = randint(1, 5);
			devProgress += basicProgress * isFastDev ? 2 : 1;
			if (devProgress >= 100) {
				isDeveloping = false;
			}
		}
		if (stage > 3) {
			stage = 0;
			day++;
			return true;
		}
		return false;
	}

	unsigned short GetDevProgress() {
		return devProgress;
	}
};
#endif // !GAME_HPP
