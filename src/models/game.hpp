#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <list>
#include <map>
#include <numeric>
#include <fstream>
#include <time.h>
#include <filesystem>

#include <optional>

// TODO: 把函数写在这里实在是很难看，之后改一改
inline void WriteStringToFile(FILE* f, const std::string & str)
{
	size_t len = str.length();
	fwrite(&len, sizeof(len), 1, f);
	fwrite(str.c_str(), len * sizeof(char), 1, f);
}
inline std::string ReadStringFromFile(FILE* f)
{
	size_t strlength = 0;
	fread(&strlength, sizeof(strlength), 1, f);

	std::string str;
	str.resize(strlength);
	fread(str.data(), strlength * sizeof(char), 1, f);

	return str;
}

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
private:
	Product() = default;

	unsigned long long lastSales = 0;
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
	unsigned long long gamePoint = 0;
	bool isFinished = false;
	bool inSale = false;

	Product(const std::string& name, int createDay, Platform platform, GameType gameType) :
		name(name), createDay(createDay), platform(platform), gameType(gameType) {}

	static Product LoadImpl(FILE* f)
	{
		Product p;
		p.name = ReadStringFromFile(f);
		fread(&p.lastSales, sizeof(p.lastSales), 1, f);
		fread(&p.createDay, sizeof(p.createDay), 1, f);
		fread(&p.publishDay, sizeof(p.publishDay), 1, f);
		fread(&p.interesting, sizeof(p.interesting), 1, f);
		fread(&p.playability, sizeof(p.playability), 1, f);

		fread(&p.graphics, sizeof(p.graphics), 1, f);
		fread(&p.sound, sizeof(p.sound), 1, f);
		fread(&p.stability, sizeof(p.stability), 1, f);
		fread(&p.platform, sizeof(p.platform), 1, f);

		fread(&p.gameType, sizeof(p.gameType), 1, f);
		fread(&p.sales, sizeof(p.sales), 1, f);
		fread(&p.gamePoint, sizeof(p.gamePoint), 1, f);
		fread(&p.isFinished, sizeof(p.isFinished), 1, f);
		fread(&p.inSale, sizeof(p.inSale), 1, f);

		return p;
	}
	void SaveImpl(FILE* f)
	{
		WriteStringToFile(f, name);

		fwrite(&lastSales, sizeof(lastSales), 1, f);
		fwrite(&createDay, sizeof(createDay), 1, f);
		fwrite(&publishDay, sizeof(publishDay), 1, f);
		fwrite(&interesting, sizeof(interesting), 1, f);
		fwrite(&playability, sizeof(playability), 1, f);

		fwrite(&graphics, sizeof(graphics), 1, f);
		fwrite(&sound, sizeof(sound), 1, f);
		fwrite(&stability, sizeof(stability), 1, f);
		fwrite(&platform, sizeof(platform), 1, f);

		fwrite(&gameType, sizeof(gameType), 1, f);
		fwrite(&sales, sizeof(sales), 1, f);
		fwrite(&gamePoint, sizeof(gamePoint), 1, f);
		fwrite(&isFinished, sizeof(isFinished), 1, f);
		fwrite(&inSale, sizeof(inSale), 1, f);
	}

	unsigned long long GetSalesReport() const {
		return sales - lastSales;
	}

	bool PublishProduct() {
		if (!isFinished || inSale) return false;
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

	static std::vector<Product> GetInSaleProds(const std::vector<Product>& prods) {
		std::vector<Product> ret;
		for (auto& p : prods) {
			if (p.inSale)	ret.push_back(p);
		}
		return ret;
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

	Stuff() = default;

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
		salary = randint(200, (program + art + audio + design) > 100 ? ((program + art + audio + design) * 10) : 1000);
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

class FinancialReport {
public:
	int day = 0;
	std::map<std::string, unsigned long long> prodSales;
	std::map<int, int> stuffSalary;
	int otherCost = 0;

	FinancialReport() :prodSales({}), stuffSalary({}) {}
	FinancialReport(int day, const std::vector<Product>& prod, const std::vector<Stuff>& empy) :day(day) {
		for (auto& p : prod) {
			prodSales[p.name] = p.GetSalesReport();
		}
		for (auto& e : empy) {
			stuffSalary[e.id] = e.salary;
		}
	}

	void PrintReport(Console& c) {
		c.Clear();
		c.GotoXY();
		for (int i = 0; i < 117; i++) {
			std::cout << "=";
		}
		c.GotoXY(0, 1);
		c.SetColor(Console::light_yellow);
		std::cout << day / 7 << " 周财务报告";
		c.SetColor();
		c.GotoXY(0, 3);
		c.Print("[+] 游戏销售", Console::light_blue);
		if (prodSales.empty())
		{
			c.GotoXY(0, 2 + c.GetCursorY());
			c.Print("这周工作室没有卖出任何游戏", Console::gray);
		}
		else
		{
			for (auto& p : prodSales) {
				std::cout << p.first << "\t销量: " << p.second << std::endl;
			}
		}
		c.GotoXY(0, 2 + c.GetCursorY());

		c.Print("[-] 员工工资", Console::light_magenta);
		c.GotoXY(0, 1 + c.GetCursorY());
		if (stuffSalary.empty()) {
			c.GotoXY(0, 1 + c.GetCursorY());
			c.Print("这周工作室没有发放任何薪水", Console::gray);
		}
		else {
			for (auto& s : stuffSalary) {
				std::cout << "员工编号: " << s.first << "\t薪水: " << s.second << std::endl;
			}
		}
		c.GotoXY(0, 2 + c.GetCursorY());

		c.Print("[-] 其他开销", Console::light_magenta);
		c.GotoXY(0, 1 + c.GetCursorY());
		std::cout << "工作室运营基本资金, 平台授权费等: " << otherCost;
		c.GotoXY(0, 2 + c.GetCursorY());

		c.Print("[=] 总计", Console::light_green);
		c.GotoXY(0, 1 + c.GetCursorY());
		std::cout << "总收入: " << std::accumulate(prodSales.begin(), prodSales.end(), 0, [](int a, std::pair<std::string, int> b) {return a + b.second; }) << std::endl;
		std::cout << "总支出: " << std::accumulate(stuffSalary.begin(), stuffSalary.end(), 0, [](int a, std::pair<int, int> b) {return a + b.second; }) + otherCost << std::endl;
		std::cout << "总利润: " << std::accumulate(prodSales.begin(), prodSales.end(), 0, [](int a, std::pair<std::string, int> b) {return a + b.second; }) - std::accumulate(stuffSalary.begin(), stuffSalary.end(), 0, [](int a, std::pair<int, int> b) {return a + b.second; }) - otherCost;
		c.GotoXY(0, 2 + c.GetCursorY());
		for (int i = 0; i < 117; i++) {
			std::cout << "=";
		}
		c.GotoXY(0, 1 + c.GetCursorY());
		c.Print("按任意键离开报告页面...", Console::gray);
		c.Pause();
	}

	static FinancialReport LoadImpl(FILE* f)
	{
		FinancialReport p;
		fread(&p.day, sizeof(p.day), 1, f);

		size_t prod_sales_count = 0;
		fread(&prod_sales_count, sizeof(prod_sales_count), 1, f);
	
		for (size_t i = 0; i < prod_sales_count; ++i)
		{
			auto key = ReadStringFromFile(f);
			decltype(p.prodSales)::value_type::second_type val;
			fread(&val, sizeof(val), 1, f);
			p.prodSales[key] = val;
		}

		size_t stuff_salary_count = 0;
		fread(&stuff_salary_count, sizeof(stuff_salary_count), 1, f);

		for (size_t i = 0; i < stuff_salary_count; ++i)
		{
			decltype(p.stuffSalary)::key_type key;
			decltype(p.stuffSalary)::key_type val;

			fread(&key, sizeof(key), 1, f);
			fread(&val, sizeof(val), 1, f);

			p.stuffSalary[key] = val;
		}

		fread(&p.otherCost, sizeof(otherCost), 1, f);

		return p;
	}
	void SaveImpl(FILE* f)
	{
		fwrite(&day, sizeof(day), 1, f);
		
		size_t prod_sales_count = prodSales.size();
		fwrite(&prod_sales_count, sizeof(prod_sales_count), 1, f);

		for (auto& [key, val] : prodSales)
		{
			WriteStringToFile(f, key);
			fwrite(&val, sizeof(val), 1, f);
		}

		size_t stuff_salary_count = stuffSalary.size();
		fwrite(&stuff_salary_count, sizeof(stuff_salary_count), 1, f);

		for (auto& [key, val] : stuffSalary)
		{
			fwrite(&key, sizeof(key), 1, f);
			fwrite(&val, sizeof(val), 1, f);
		}

		fwrite(&otherCost, sizeof(otherCost), 1, f);
	}
};

class Studio {

	Studio(const Studio&) = delete;
	Studio& operator = (const Studio&) = delete;

public:
	std::string name;
	std::vector<Stuff> stuffs;
	std::vector<Product> finishedProducts;
	FinancialReport financialReport;

	Studio(const std::string& name) : name(name), financialReport() {
		stuffs = { Stuff(0,programmer,0), Stuff(0,artist,1), Stuff(0,musician,2), Stuff(0,designer,3) };
		finishedProducts = std::vector<Product>();
	}

	void LoadImpl(FILE* f)
	{
		name = ReadStringFromFile(f);

		size_t stuffs_len = 0;
		fread(&stuffs_len, sizeof(stuffs_len), 1, f);
		for (size_t i = 0; i < stuffs_len; ++i)
		{
			static_assert(std::is_standard_layout<Stuff>::value);
			stuffs.push_back({});

			fread(&stuffs.back(), sizeof(decltype(stuffs)::value_type), 1, f);
		}

		size_t prod_len = 0;
		fread(&prod_len, sizeof(prod_len), 1, f);
		for (size_t i = 0; i < prod_len; ++i)
		{
			finishedProducts.push_back(Product::LoadImpl(f));
		}
	}
	void SaveImpl(FILE* f)
	{
		WriteStringToFile(f, name);

		size_t stuffs_len = stuffs.size();
		fwrite(&stuffs_len, sizeof(stuffs_len), 1, f);
		for (auto& stuff : stuffs)
		{
			static_assert(std::is_standard_layout<Stuff>::value);
			fwrite(&stuff, sizeof(stuff), 1, f);
		}

		size_t prod_len = finishedProducts.size();
		fwrite(&prod_len, sizeof(prod_len), 1, f);
		for (auto& prod : finishedProducts)
		{
			prod.SaveImpl(f);
		}
	}
};

class GameData {
private:
	int devProgress = 0;
public:
	int day = 1;
	short stage = 0;
	bool noConfirm = false;
	bool isAutoSave = true;
	bool isFastDev = false;
	long long money = 0;
	std::optional<Product> workingProduct = std::nullopt;
	Studio studio;

	GameData() = delete;

	GameData(const std::string& studioName)
		: studio(studioName)
	{
		money = 50000;
	}

	enum class SavingResult
	{
		OK,
		FILE_EXIST,
		FAILED,
	};

	bool TryLoading(const std::filesystem::path& saving_file_path)
	{
		std::error_code ec = {};
		// NOTE: 使用error_code，不然如果文件系统库操作失败会丢异常，规避异常机制的使用
		if (std::filesystem::exists(saving_file_path, ec))
			return false;

		FILE* saving = fopen(saving_file_path.string().c_str(), "rb");
		if (saving == nullptr)
			// 无法打开文件以保存，返回错误
			return false;

		// 开写！
		fread(&devProgress, sizeof(devProgress), 1, saving);
		fread(&day, sizeof(day), 1, saving);
		fread(&stage, sizeof(stage), 1, saving);
		fread(&noConfirm, sizeof(noConfirm), 1, saving);
		fread(&isAutoSave, sizeof(isAutoSave), 1, saving);
		fread(&isFastDev, sizeof(isFastDev), 1, saving);
		fread(&money, sizeof(money), 1, saving);

		bool has_working_product = false;
		fread(&has_working_product, sizeof(has_working_product), 1, saving);
		if (has_working_product)
		{
			workingProduct = std::make_optional(Product::LoadImpl(saving));
		}
		studio.LoadImpl(saving);

		fclose(saving);

		return true;
	}

	SavingResult TrySaving(const std::filesystem::path& saving_file_path, bool force) 
	{
		std::error_code ec = {};
		// NOTE: 使用error_code，不然如果文件系统库操作失败会丢异常，规避异常机制的使用
		if (force == false && std::filesystem::exists(saving_file_path, ec))
			return SavingResult::FILE_EXIST;
	
		FILE* saving = fopen(saving_file_path.string().c_str(), "wb");
		if (saving == nullptr)
			// 无法打开文件以保存，返回错误
			return SavingResult::FAILED;

		// 开写！
		fwrite(&devProgress, sizeof(devProgress), 1, saving);
		fwrite(&day, sizeof(day), 1, saving);
		fwrite(&stage, sizeof(stage), 1, saving);
		fwrite(&noConfirm, sizeof(noConfirm), 1, saving);
		fwrite(&isAutoSave, sizeof(isAutoSave), 1, saving);
		fwrite(&isFastDev, sizeof(isFastDev), 1, saving);
		fwrite(&money, sizeof(money), 1, saving);

		bool has_working_product = workingProduct.has_value();
		fwrite(&has_working_product, sizeof(has_working_product), 1, saving);
		if (has_working_product)
		{
			workingProduct.value().SaveImpl(saving);
		}
		studio.SaveImpl(saving);

		fclose(saving);

		return SavingResult::OK;
	}

	bool TakeADayOff() {
		if (stage == 0) {
			for (auto& stuff : studio.stuffs) {
				if (stuff.happiness <= 65) stuff.happiness += 35;
				else stuff.happiness = 100;
			}
			day++;
			return true;
		}
		else return false;
	}

	void PublishProduct() {
		if (workingProduct.has_value() && !workingProduct.value().isFinished) return;
		workingProduct.value().PublishProduct();
		studio.finishedProducts.push_back(workingProduct.value());
		workingProduct = std::nullopt;
		devProgress = 0;
	}


	void Selling() {
		for (auto& p : studio.finishedProducts) {
			auto releasedDays = day - p.publishDay;
			if (releasedDays >= 45) { p.inSale = false; continue; }
			p.sales = (unsigned long long)(randint(p.gamePoint / 10.0, (p.gamePoint * (1 - (releasedDays / 45.0))) * (day / (14.0))));
			money += p.sales * 3 * ((long long)p.platform + 1);

		}
	}

	void WeekSet(Console& c) {
		money -= std::accumulate(studio.stuffs.begin(), studio.stuffs.end(), 0, [](int a, Stuff b) {return a + b.salary; });
		studio.financialReport = FinancialReport(day, Product::GetInSaleProds(studio.finishedProducts), studio.stuffs);
	}

	bool RoundDev(Console& c) {
		stage++;
		if (workingProduct.has_value()) {
			if (devProgress >= 100) {
				if (!workingProduct.value().isFinished) {
					std::string s1 = workingProduct.value().name;
					printMenu(Menu({ "好的" }, 15, 0, "你的项目 \"" + s1 + "\" 已经制作完成了，你可以选择现在发布或者继续调试增加稳定性。"), c);
					workingProduct.value().isFinished = true;
				}
				for (auto& stuff : studio.stuffs) {
					if (!stuff.roundWork() || stuff.job != programmer) continue;
					workingProduct.value().stability += randint(0, stuff.program / 2);
				}
			}
			else {
				bool isWork = false;

				for (auto& stuff : studio.stuffs) {
					if (!stuff.roundWork()) continue;
					isWork = true;
					switch (stuff.job)
					{
					case programmer:
						workingProduct.value().graphics += randint(0, stuff.art / 4) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().playability += randint(0, stuff.design / 4) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().stability += randint(0, stuff.program / 4);
						break;
					case artist:
						workingProduct.value().graphics += randint(0, stuff.art / 4) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().playability += randint(0, stuff.design / 4);
						workingProduct.value().sound += randint(0, stuff.audio / 4);
						workingProduct.value().interesting += randint(0, stuff.design / 4);
						break;
					case musician:
						workingProduct.value().playability += randint(0, stuff.design / 4);
						workingProduct.value().sound += randint(0, stuff.audio / 4) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().interesting += randint(0, stuff.design / 4);
						break;
					case designer:
						workingProduct.value().graphics += randint(0, stuff.art / 4);
						workingProduct.value().playability += randint(0, stuff.design / 4) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().interesting += randint(0, stuff.design / 4) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().sound += randint(0, stuff.audio / 4);
						break;
					case almighty:
						workingProduct.value().graphics += randint(0, stuff.art / 4) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().playability += randint(0, stuff.design / 4) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().interesting += randint(0, stuff.design / 4) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().sound += randint(0, stuff.audio / 4) * (stuff.happiness > 90 ? 2 : 1);
						workingProduct.value().stability += randint(0, stuff.program / 4) * (stuff.happiness > 90 ? 2 : 1);
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
