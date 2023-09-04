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

enum GameType
{
	Action,
	Adventure,
	SLG,
	FPS,
	Music
};

class Product {
public:
	std::string name;
	int createDay;
	int publishDay = 0;
	int interesting = 0;
	int playability = 0;
	int graphics = 0;
	int sound = 0;
	int stability = 0;
	Platform platform;
	GameType gameType;

	unsigned long long sales = 0;
	unsigned long long profit = 0;
	unsigned long long gamePoint = 0;
	bool isFinished = false;
	bool inSale = false;

	Product(std::string name, int createDay, Platform platform, GameType gameType) :
		name(name), createDay(createDay), platform(platform), gameType(gameType) {}

	bool PublishProduct() {
		/*if (!isFinished || inSale) return false;*/
		inSale = true;

		switch (gameType)
		{
		case Action:
			gamePoint += (unsigned long long)(graphics + sound) * 2 + playability + stability + interesting;
			break;
		case Adventure:
			gamePoint += (unsigned long long)(interesting + playability) * 2 + graphics + stability + sound;
			break;
		case SLG:
			gamePoint += (unsigned long long)(playability + graphics) * 2 + interesting + stability + sound;
			break;
		case FPS:
			gamePoint += (unsigned long long)(stability + graphics) * 2 + interesting + playability + sound;
			break;
		case Music:
			gamePoint += (unsigned long long)(sound + interesting) * 2 + playability + stability + graphics;
			break;
		}
		return true;
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
	int program = 0;
	int art = 0;
	int audio = 0;
	int design = 0;
	int happiness = 0;
	int salary = 0;
	JobType job;

	Stuff(int id, int program, int art, int audio,
		int design, int happiness, int salary, JobType job) :
		id(id), program(program), art(art), audio(audio), design(design), happiness(happiness), salary(salary), job(job)
	{}

	Stuff(int day, JobType job, int stuffId) :job(job) {
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

	bool roundWork() {
		auto rand = randint(0, 5);
		if (happiness >= rand)
			happiness -= rand;
		else
			happiness = 0;
		return happiness != 0;
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
	int devProgress = 0;
public:
	int day = 0;
	short stage = 0;
	bool noConfirm = false;
	bool isAutoSave = true;
	bool isFastDev = false;
	bool isDeveloping = false;
	int money = 0;
	std::optional<Product> workingProduct = std::nullopt;
	std::optional<Studio> studio = std::nullopt;

	GameData() = default;

	GameData(std::string studioName) {
		studio = Studio(studioName);
		money = 50000;
	}

	Studio GetStudio() {
		if (!studio.has_value()) {
			throw std::exception("Studio is not initialized");
		}
		return studio.value();
	}

	bool TakeADayOff() {
		if (stage == 0) {
			for (auto& stuff : studio.value().stuffs) {
				if (stuff.happiness <= 65) stuff.happiness += 35;
				else stuff.happiness = 100;
			}
			day++;
			return true;
		}
		else return false;
	}

	void PublishProduct() {
		if (!(workingProduct.has_value()/* && workingProduct.value().isFinished*/)) return;
		workingProduct.value().PublishProduct();
		//TODO: finishedProducts didn't save a value, still empty
		GetStudio().finishedProducts.push_back(workingProduct.value());
		workingProduct = std::nullopt;
		devProgress = 0;
		isDeveloping = false;
	}


	void Selling() {
		for (auto& p : GetStudio().finishedProducts) {
			auto releasedDays = day - p.publishDay;
			if (releasedDays >= 45) { p.inSale = false; continue; }
			p.sales = (unsigned long long)(randint(p.gamePoint / 3.0, p.gamePoint * 10) * (1 - (releasedDays / 45.0)));


		}
	}

	bool RoundDev(Console& c) {
		stage++;
		if (isDeveloping) {

			if (devProgress >= 100) {
				if (!workingProduct.value().isFinished) {
					std::string s1 = workingProduct.value().name;
					printMenu(Menu({ "好的" }, 15, 0, "你的项目 \"" + s1 + "\" 已经制作完成了，你可以选择现在发布或者继续调试增加稳定性。"), c);
					workingProduct.value().isFinished = true;
				}
				for (auto& stuff : studio.value().stuffs) {
					if (!stuff.roundWork() || stuff.job != programmer) continue;
					workingProduct.value().stability += randint(0, stuff.program / 2);
				}
			}
			else {
				bool isWork = false;

				for (auto& stuff : studio.value().stuffs) {
					if (!stuff.roundWork()) continue;
					isWork = true;
					switch (stuff.job)
					{
					case programmer:
						workingProduct.value().graphics += randint(0, stuff.art / 2) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().playability += randint(0, stuff.design / 2) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().stability += randint(0, stuff.program / 2);
						break;
					case artist:
						workingProduct.value().graphics += randint(0, stuff.art / 2) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().playability += randint(0, stuff.design / 2);
						workingProduct.value().sound += randint(0, stuff.audio / 2);
						workingProduct.value().interesting += randint(0, stuff.design / 2);
						break;
					case musician:
						workingProduct.value().playability += randint(0, stuff.design / 2);
						workingProduct.value().sound += randint(0, stuff.audio / 2) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().interesting += randint(0, stuff.design / 2);
						break;
					case designer:
						workingProduct.value().graphics += randint(0, stuff.art / 2);
						workingProduct.value().playability += randint(0, stuff.design / 2) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().interesting += randint(0, stuff.design / 2) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().sound += randint(0, stuff.audio / 2);
						break;
					case almighty:
						workingProduct.value().graphics += randint(0, stuff.art / 2) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().playability += randint(0, stuff.design / 2) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().interesting += randint(0, stuff.design / 2) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().sound += randint(0, stuff.audio / 2) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().stability += randint(0, stuff.program / 2) * (stuff.happiness > 90 ? 2 : 1);
						break;
					}
				}
				if (isWork)
				{
					int basicProgress = randint(0, 2);
					devProgress += basicProgress * (isFastDev ? 2 : 1);
					if (devProgress >= 100) devProgress = 100;
				}
			}
		}
		if (stage > 3) {
			stage = 0;
			day++;
			Selling();
			return true;
		}
		return false;
	}

	int GetDevProgress() {
		return devProgress;
	}
};
#endif // !GAME_HPP
