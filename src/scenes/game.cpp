#include "main.hpp"

std::unique_ptr<GameData> instance;

void gameCycle() {
	Console c;
	while (true) {
		auto result = studio(c);
		if (result.info == 0) {
			instance->RoundDev(c);
			if (instance->day % 7 == 0 && instance->stage == 0) instance->WeekSet(c);
		}

	}
}

progress<int> beginning() {
	Console c;
	c.Clear();
	while (true) {
		c.SetColor(Console::Yellow);
		std::cout << "请为你的工作室决定一个名字: ";
		c.SetColor();
		std::string name;
		std::getline(std::cin, name);
		name = trim(name);
		if (name.empty()) {
			c.Clear();
			c.SetColor(Console::Red);
			std::cout << "工作室名称不能为空！" << std::endl;
			c.SetColor(Console::Blue);
			std::cout << "请重试。" << std::endl;
			c.SetColor();
			continue;
		}
		if (name.size() > 16) {
			c.Clear();
			c.SetColor(Console::Red);
			std::cout << "工作室名称不能超过16个字符（每个汉字算 2 个字符），你的 \"" << name << "\" 超过了这一限制！" << std::endl;
			c.SetColor(Console::Blue);
			std::cout << "请重试。" << std::endl;
			c.SetColor();
			continue;
		}
		instance = std::make_unique<GameData>(name);

		std::cout << "好的，你的工作室名称为: " << instance->studio.name << std::endl;
		std::cout << "是这样吗？" << std::endl << std::endl;
		auto result = printMenu(Menu({ "是，就这个了","否，我再想想" }, 5, 0), c);
		if (result == 0) return progress<int>(true);
		else c.Clear();
	}
}

progress<int> loadsave() {
	instance = std::make_unique<GameData>(std::filesystem::path("save/1.save"));
	return progress<int>(true);
}

progress<int> createGame(Console& c) {
	c.Clear();
	c.GotoXY();

	std::string name;
	while (true) {
		c.SetColor(Console::Yellow);
		std::cout << "为你的新游戏决定一个名字：";
		c.SetColor();
		std::getline(std::cin, name);
		name = trim(name);
		if (name.empty()) {
			c.Clear();
			c.SetColor(Console::Red);
			std::cout << "游戏名称不能为空！" << std::endl;
			c.SetColor(Console::Blue);
			std::cout << "请重试。" << std::endl;
			c.SetColor();
			continue;
		}
		if (name.size() > 16) {
			c.Clear();
			c.SetColor(Console::Red);
			std::cout << "游戏名称不能超过16个字符（每个汉字算 2 个字符），你的 \"" << name << "\" 超过了这一限制！" << std::endl;
			c.SetColor(Console::Blue);
			std::cout << "请重试。" << std::endl;
			c.SetColor();
			continue;
		}
		break;

	}

	c.GotoXY(0, 1);
	c.SetColor(Console::Yellow);
	std::cout << "为你的新游戏决定一个类型：";
	c.SetColor();
	auto gameType = printMenu(Menu({ "动作游戏","冒险游戏","养成游戏","射击游戏","音乐游戏" }, 2, 0), c);
	c.Clear(0, 1, 120, 20);
	c.GotoXY(0, 1);
	c.SetColor(Console::LightBlue);
	switch (gameType)
	{
	case 0:
		std::cout << "你将开发一款 动作游戏。";
		break;
	case 1:
		std::cout << "你将开发一款 冒险游戏。";
		break;
	case 2:
		std::cout << "你将开发一款 养成游戏。";
		break;
	case 3:
		std::cout << "你将开发一款 射击游戏。";
		break;
	case 4:
		std::cout << "你将开发一款 音乐游戏。";
		break;
	}
	c.SetColor();

	c.GotoXY(0, 3);
	c.SetColor(Console::Yellow);
	std::cout << "你的游戏将在哪个平台上发售：";
	auto platform = printMenu(Menu({ "PC","Mobile","XCase","Zwitch","PS114514" }, 4, 0), c);
	c.Clear(0, 2, 120, 20);
	c.GotoXY(0, 2);
	c.SetColor(Console::LightBlue);
	switch (platform)
	{
	case 0:
		std::cout << "你选择在 PC平台 发售。";
		break;
	case 1:
		std::cout << "你选择在 移动端平台 发售。";
		break;
	case 2:
		std::cout << "你选择在 XCase平台 发售。";
		break;
	case 3:
		std::cout << "你选择在 Zwitch平台 发售。";
		break;
	case 4:
		std::cout << "你选择在 PS114514平台 发售。";
		break;
	}
	c.SetColor();

	auto confirm = printMenu(Menu({ "是","否" }, 4, 0, "确认要开始制作新游戏吗? 这将花费 $5000 作为立项经费。"), c);
	if (confirm == 0) {
		instance->RoundDev(c);
		instance->workingProduct = Product(name, instance->day, Platform(platform), GameType(gameType));
		instance->money -= 5000;
	}
	return progress<int>(true);
}

progress<int> setDevPlan(Console& c) {
	std::string s1 = "调整开发速度", name;
	s1 += instance->isFastDev ? "为\"普通开发\"" : "为\"加急开发\"";
	switch (printMenu(Menu({ "更改游戏名称",s1,"返回" }, 15, true), c))
	{
	case 0:
		c.Clear();
		c.GotoXY();
		while (true) {
			c.SetColor(Console::Yellow);
			std::cout << "为你开发中的游戏更换一个名字：";
			c.SetColor();
			std::getline(std::cin, name);
			name = trim(name);
			if (name.empty()) {
				c.Clear();
				c.SetColor(Console::Red);
				std::cout << "游戏名称不能为空！" << std::endl;
				c.SetColor(Console::Blue);
				std::cout << "请重试。" << std::endl;
				c.SetColor();
				continue;
			}
			if (name.size() > 16) {
				c.Clear();
				c.SetColor(Console::Red);
				std::cout << "游戏名称不能超过16个字符（每个汉字算 2 个字符），你的 \"" << name << "\" 超过了这一限制！" << std::endl;
				c.SetColor(Console::Blue);
				std::cout << "请重试。" << std::endl;
				c.SetColor();
				continue;
			}
			break;
		}
		instance->workingProduct.value().name = name;
		break;
	case 1:
		if (instance->isFastDev) printMenu(Menu({ "好的" }, 15, 0, "开发速度已被调整为普通速度。"), c);
		else printMenu(Menu({ "好的" }, 15, 0, "开发速度已被调整为加急，这将在加快游戏开发进程的同时牺牲品质"), c);
		instance->isFastDev = !instance->isFastDev;
		break;
	case 2:
		return progress<int>(true);
	}
	return progress<int>(true);
}

progress<int> jobFair(Console& c) {
	instance->isFairChecked = true;
	c.Clear();
	c.GotoXY();
	for (int i = 0; i < 117; i++) std::cout << "=";
	c.Endl();
	c.Print("人才市场", Console::Blue);
	c.Endl();
	for (int i = 0; i < 117; i++) std::cout << "=";
	c.Endl();
	std::vector<Stuff> jobSeekers = { Stuff(instance->day, JobType::Programmer, -1),Stuff(instance->day,JobType::Musician,-1),
		Stuff(instance->day,JobType::Artist,-1), Stuff(instance->day,JobType::Designer,-1) };
	if (randint(0, 100) < 15) jobSeekers[randint(0, 3)] = Stuff(instance->day, JobType::Almighty, -1);
	c.Print("你每天可以免费进入一次人才市场寻找求职者，之后每次进入需要支付 $1000", Console::Yellow);
	c.Endl();
	c.Print("你的工作室最多可以雇用 4 名员工，你可以将已有的员工辞退以招聘新的员工。");
	c.GotoXY(30, c.GetCursorY() + 2);
	c.SetColor(Console::Colors::Cyan);
	std::cout << "  职业    编程    美工    音乐    策划    心情    周薪  ";
	c.SetColor();
	for (auto& stuff : jobSeekers) {
		c.Endl();
		for (int i = 0; i < 109; i++) std::cout << "-";
		c.Endl();
		c.MoveX(32);
		switch (stuff.job) {
		case JobType::Programmer:
			c.Print("程序", Console::LightCyan);
			break;
		case JobType::Musician:
			c.Print("音乐", Console::Blue);
			break;
		case JobType::Artist:
			c.Print("美术", Console::Magenta);
			break;
		case JobType::Designer:
			c.Print("策划", Console::LightRed);
			break;
		case JobType::Almighty:
			c.Print("全能", Console::Yellow);
			break;
		}
		c.MoveX(41);
		std::cout << stuff.program;
		c.MoveX(49);
		std::cout << stuff.art;
		c.MoveX(57);
		std::cout << stuff.audio;
		c.MoveX(65);
		std::cout << stuff.design;
		c.MoveX(73);
		std::cout << stuff.happiness;
		c.MoveX(81);
		std::cout << stuff.salary;
	}
	c.Endl();
	for (int i = 0; i < 109; i++) std::cout << "-";
	c.Endl();
	auto selection = printMenu(Menu({ "招聘 1 号", "招聘 2 号","招聘 3 号","招聘 4 号","离开人才市场" }, 15, 0, "下一步做什么？"), c);
	switch (selection) {
	case 0:
	case 1:
	case 2:
	case 3:
		printMenu(Menu({ "好的" }, 15, 0, instance->studio.HireStuff(jobSeekers[selection]) ? "招聘成功。" : "招聘失败，你的工作室已满！"), c);
		break;
	}
	return progress<int>(true);
}


progress<int> studio(Console& c) {
	c.Clear();
#pragma region Sidebars
	for (int i = 0; i < 15; i++) {
		c.GotoXY(28, i);
		std::cout << "|";
	}
	for (int i = 0; i < 15; i++) {
		c.GotoXY(88, i);
		std::cout << "|";
	}
	c.GotoXY();
#pragma endregion

#pragma region DayPanel
	std::cout << "===========================" << std::endl;
	std::cout << "> Day ";
	c.SetColor(Console::Colors::Cyan);
	std::cout << instance->day;
	c.SetColor();
	c.GotoXY(11, 1);
	std::cout << "|  ";

	for (int i = 0; i < 4; i++) {
		if (i != instance->stage) {
			c.SetColor(Console::Colors::Gray);
			std::cout << "=  ";
		}
		else {
			c.SetColor(Console::Colors::LightYellow);
			std::cout << "[=]  ";
		}
	}
	c.SetColor();
	c.GotoXY(0, 2);
	std::cout << "===========================";
	c.SetColor();
#pragma endregion

#pragma region StudioPanel
	c.GotoXY(0, 3);
	std::cout << "[ 工作室名称 ] ";
	c.GotoXY(4, 4);
	std::cout << instance->studio.name;
	c.GotoXY(18, 4);
	std::cout << " 工作室";
	c.GotoXY(0, 6);
	std::cout << "[ 资金 ] ";
	c.GotoXY(4, 7);
	c.SetColor(Console::Colors::Yellow);
	std::cout << "$ " << instance->money;
	c.SetColor();
	c.GotoXY(0, 9);
	std::cout << "[ 工作室状态 ] ";
	c.GotoXY(2, 10);
	if (instance->workingProduct.has_value()) {
		c.SetColor(Console::Colors::LightGreen);
		std::cout << "正在开发:" << instance->workingProduct.value().name;
	}
	else {
		c.GotoXY(4, 10);
		c.SetColor(Console::Colors::Gray);
		std::cout << "空闲中...";
	}
	c.SetColor();
	c.GotoXY(0, 12);
	std::cout << "[ 历史信息 ] ";
	c.GotoXY(4, 13);
	if (instance->studio.finishedProducts.size() != 0) {
		c.SetColor(Console::Colors::LightMagenta);
		std::cout << "已发布了 " << instance->studio.finishedProducts.size() << "件作品";
	}
	else {
		c.SetColor(Console::Colors::Gray);
		std::cout << "等待发布工作室首部作品";
	}
	c.SetColor();
#pragma endregion

#pragma region StuffStatPanel
	c.GotoXY(30, 0);
	for (int i = 0; i < 57; i++)std::cout << "=";
	c.GotoXY(30, 1);
	std::cout << " 员工信息";
	c.GotoXY(30, 3);
	c.SetColor(Console::Colors::LightCyan);
	std::cout << "  编号    编程    美工    音乐    策划    心情    周薪  ";
	c.SetColor();
	if (instance->studio.stuffs.size() == 0) {
		c.GotoXY(33, 7);
		c.SetColor(Console::Gray);
		std::cout << "当前没有雇佣任何员工！";
		c.SetColor();
	}
	else {
		int i = 7;
		for (auto& stuff : instance->studio.stuffs) {
			c.GotoXY(33, i);
			std::cout << stuff.id;
			c.GotoXY(41, i);
			std::cout << stuff.program;
			c.GotoXY(49, i);
			std::cout << stuff.art;
			c.GotoXY(57, i);
			std::cout << stuff.audio;
			c.GotoXY(65, i);
			std::cout << stuff.design;
			c.GotoXY(73, i);
			std::cout << stuff.happiness;
			c.GotoXY(81, i);
			std::cout << stuff.salary;
			i++;
		}
	}

#pragma endregion

#pragma region ProductPanel
	c.GotoXY(90, 0);
	std::cout << "===========================";
	c.GotoXY(90, 1);
	std::cout << " 产品进度";
	c.GotoXY(90, 3);
	if (instance->workingProduct.has_value())
	{
		c.GotoXY(93, 3);
		std::cout << "[ 作品名称 ] ";
		c.GotoXY(97, 4);
		std::cout << instance->workingProduct.value().name;
		c.GotoXY(93, 6);
		std::cout << "[ 开发进度 ] ";
		c.GotoXY(97, 7);
		std::cout << instance->GetDevProgress() << "%";
		if (instance->isFastDev) {
			c.GotoXY(103, 7);
			c.SetColor(Console::LightRed);
			std::cout << "加急开发";
			c.SetColor();
		}
		c.GotoXY(93, 9);
		std::cout << "[ 作品数据 ] ";
		c.GotoXY(93, 10);
		std::cout << "趣味: " << instance->workingProduct.value().interesting;
		c.GotoXY(104, 10);
		std::cout << "画面: " << instance->workingProduct.value().graphics;
		c.GotoXY(93, 11);
		std::cout << "音乐: " << instance->workingProduct.value().sound;
		c.GotoXY(104, 11);
		std::cout << "玩法: " << instance->workingProduct.value().playability;
		c.GotoXY(97, 12);
		std::cout << "稳定: " << instance->workingProduct.value().stability;
	}
	else {
		c.GotoXY(93, 7);
		c.SetColor(Console::Gray);
		std::cout << "当前没有正在开发的项目！";
		c.SetColor();
	}
#pragma endregion
#pragma region CommandPanel
	c.GotoXY(0, 14);
	auto result = printMenu(Menu({ "下一回合","项目管理","员工管理","工作室管理","设置菜单" }, 15), c);
	c.Clear(0, 14, 120, 20);
	int subResult;
	switch (result) {
	case 0:
		if (instance->noConfirm) return progress<int>(true, true, 0);
		if (printMenu(Menu({ "是","否" }, 15, 0, "确定要进入下一回合吗？"), c) == 0) return progress<int>(true, true, 0);
		return progress<int>(true, true, -1);
	case 1:
		subResult = printMenu(Menu({ "制作新游戏","调整项目计划","发布游戏","返回" }, 15, true), c);
		switch (subResult)
		{
		case 0:
			if (instance->workingProduct.has_value()) {
				printMenu(Menu({ "好的" }, 15, 0, "当前已经有一个正在开发的项目了"), c);
				break;
			}
			createGame(c);
			break;
		case 1:
			if (instance->workingProduct.has_value())
				setDevPlan(c);
			else
				printMenu(Menu({ "好的" }, 15, 0, "当前没有正在开发的项目！"), c);
			break;
		case 2:
			if (instance->workingProduct.has_value() && instance->workingProduct.value().isFinished)
			{
				instance->workingProduct.value().publishDay = instance->day;
				instance->PublishProduct();
			}
			else
				printMenu(Menu({ "好的" }, 15, 0, instance->workingProduct.has_value() ? "游戏还没有制作完成，不能发售！" : "没有任何游戏可以发售！"), c);
			break;
		}
		break;
	case 2:
		subResult = printMenu(Menu({ "人才市场","\"降本增效\"","返回" }, 15, true), c);
		switch (subResult) {
		case 0:
			if (instance->isFairChecked) if (printMenu(Menu({ "支付 $1000 以重新入场","返回" }, 15, 0, "你已经进入过人才市场了，是否要重新入场？"), c) == 0)
				instance->money -= 1000;
			else break;
			jobFair(c);
			break;
		case 1:
			if (instance->studio.stuffs.empty())
			{
				printMenu(Menu({ "好的" }, 15, 0, "你的工作室已经没有任何员工了！"), c);
				break;
			}
			std::vector<std::string> options;
			for (auto i = 1; i <= instance->studio.stuffs.size(); i++)
			{
				std::string str = "开除 ";
				str += std::to_string(instance->studio.stuffs[i - 1].id) + " 号员工";
				options.push_back(str);
			}
			options.push_back("返回");
			auto result = printMenu(Menu(options, 15, true), c);
			if (result != options.size() - 1) instance->studio.FireStuff(result);
			break;
		}
		break;
	case 3:
		subResult = printMenu(Menu({ "休假","上周财报","工作室设置","返回" }, 15, true), c);
		switch (subResult)
		{
		case 0:
			if (!printMenu(Menu({ "是","否" }, 15, 0, "确定要给工作室放一天假吗？这为每位员工恢复35点心情。"), c))
			{
				printMenu(Menu({ "好的" }, 15, 0,
					instance->TakeADayOff() ? "工作室休了一天假，所有员工都好好歇了一口气。" : "今天上过班了，已经不算休假了。"), c);
			}
			break;
		case 1:
			if (instance->day < 7) printMenu(Menu({ "好的" }, 15, 0, "第一周结束后才有财报"), c);
			else instance->studio.financialReport.PrintReport(c);
			break;
		}
		break;
	case 4:
		subResult = printMenu(Menu({ "保存游戏","游戏设置","退出游戏","返回" }, 15, true), c);
		std::string s1, s2;
		auto flag = true;
		switch (subResult) {
		case 0:
			instance->TrySaving(std::filesystem::path("save/1.save"), true);
			break;
		case 1:

			while (flag) {
				s1 = "自动确认操作: ", s2 = "每日自动保存: ";
				s1 += instance->noConfirm ? "是" : "否";
				s2 += instance->isAutoSave ? "是" : "否";
				switch (printMenu(Menu({ s1,s2,"返回" }, 15, true), c))
				{
				case 0:
					instance->noConfirm = !instance->noConfirm;
					break;
				case 1:
					instance->isAutoSave = !instance->isAutoSave;
					break;
				case 2:
					flag = false;
					break;
				}
			}
			break;
		case 2:
			exit(0);
		}
	}
#pragma endregion
	return progress<int>(true, true, result);
}

