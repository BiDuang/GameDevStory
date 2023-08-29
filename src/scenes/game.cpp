#include "main.hpp"

GameData instance;

void gameCycle() {
	while (true) {
		auto result = studio();
		if (result.info == 0)
			instance.RoundDev();
	}
}

progress<int> beginning() {
	auto c = Console();
	c.Clear();
	while (true) {
		c.SetColor(Console::yellow);
		std::cout << "请为你的工作室决定一个名字: ";
		c.SetColor();
		std::string name;
		std::getline(std::cin, name);
		if (name.size() > 16) {
			c.Clear();
			c.SetColor(Console::red);
			std::cout << "工作室名称不能超过16个字符（每个汉字算 2 个字符），你的 \"" << name << "\" 超过了这一限制！" << std::endl;
			c.SetColor(Console::blue);
			std::cout << "请重试。" << std::endl;
			c.SetColor();
			continue;
		}
		instance = GameData(name);
		std::cout << "好的，你的工作室名称为: " << instance.GetStudio().name << std::endl;
		std::cout << "是这样吗？" << std::endl << std::endl;
		auto result = printMenu(Menu({ "是，就这个了","否，我再想想" }, 5, 0), c);
		if (result == 0) return progress<int>(true, false);
		else c.Clear();
	}
}

progress<int> loadsave() {

	return progress<int>(true, false);
}

progress<int> createGame() {
	auto c = Console();
	c.Clear();
	c.GotoXY(0, 0);

	std::string name;
	while (true) {
		c.SetColor(Console::yellow);
		std::cout << "为你的新游戏决定一个名字：";
		c.SetColor();
		std::getline(std::cin, name);
		if (name.size() > 16) {
			c.Clear();
			c.SetColor(Console::red);
			std::cout << "游戏名称不能超过16个字符（每个汉字算 2 个字符），你的 \"" << name << "\" 超过了这一限制！" << std::endl;
			c.SetColor(Console::blue);
			std::cout << "请重试。" << std::endl;
			c.SetColor();
		}
		else {
			c.Clear();
			c.GotoXY(0, 0);
			std::cout << "为你的新游戏决定一个名字：" << name;
			break;
		}
	}


	c.GotoXY(0, 1);
	c.SetColor(Console::yellow);
	std::cout << "为你的新游戏决定一个类型：";
	c.SetColor();
	auto gameType = printMenu(Menu({ "动作游戏","冒险游戏","养成游戏","射击游戏","音乐游戏" }, 2, 0), c);
	c.Clear(0, 1, 120, 20);
	c.GotoXY(0, 1);
	c.SetColor(Console::light_blue);
	switch (gameType)
	{
	case 0:
		std::cout << "你将开发一款动作游戏。";
		break;
	case 1:
		std::cout << "你将开发一款冒险游戏。";
		break;
	case 2:
		std::cout << "你将开发一款养成游戏。";
		break;
	case 3:
		std::cout << "你将开发一款射击游戏。";
		break;
	case 4:
		std::cout << "你将开发一款音乐游戏。";
		break;
	}
	c.SetColor();

	c.GotoXY(0, 3);
	c.SetColor(Console::yellow);
	std::cout << "你的游戏将在哪个平台上发售：";
	auto platform = printMenu(Menu({ "PC","Mobile","XCase","Zwitch","PS114514" }, 4, 0), c);
	c.Clear(0, 2, 120, 20);
	c.GotoXY(0, 2);
	c.SetColor(Console::light_blue);
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
		instance.RoundDev();
		instance.workingProduct = Product(name, instance.day, Platform(platform));
		instance.isDeveloping = true;
	}
	return progress<int>(true, false);
}


progress<int> studio() {
	auto c = Console();
	c.Clear();
#pragma region Sidebars
	for (int i = 0; i < 14; i++) {
		c.GotoXY(28, i);
		std::cout << "|";
	}
	for (int i = 0; i < 14; i++) {
		c.GotoXY(88, i);
		std::cout << "|";
	}
	c.GotoXY();
#pragma endregion

#pragma region DayPanel
	std::cout << "===========================" << std::endl;
	std::cout << "> Day ";
	c.SetColor(Console::Colors::cyan);
	std::cout << instance.day;
	c.SetColor();
	c.GotoXY(11, 1);
	std::cout << "|  ";

	for (int i = 0; i < 4; i++) {
		if (i != instance.stage) {
			c.SetColor(Console::Colors::gray);
			std::cout << "=  ";
		}
		else {
			c.SetColor(Console::Colors::light_yellow);
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
	std::cout << instance.GetStudio().name;
	c.GotoXY(18, 4);
	std::cout << " 工作室";
	c.GotoXY(0, 6);
	std::cout << "[ 资金 ] ";
	c.GotoXY(4, 7);
	c.SetColor(Console::Colors::yellow);
	std::cout << "$ " << instance.money;
	c.SetColor();
	c.GotoXY(0, 9);
	std::cout << "[ 工作室状态 ] ";
	c.GotoXY(2, 10);
	if (instance.isDeveloping) {
		c.SetColor(Console::Colors::light_green);
		std::cout << "正在开发:" << instance.workingProduct.value().name;
	}
	else {
		c.GotoXY(4, 10);
		c.SetColor(Console::Colors::gray);
		std::cout << "空闲中...";
	}
	c.SetColor();
	c.GotoXY(0, 12);
	std::cout << "[ 历史信息 ] ";
	c.GotoXY(4, 13);
	if (instance.GetStudio().finishedProducts.size() != 0) {
		c.SetColor(Console::Colors::light_magenta);
		std::cout << "已发布了 " << instance.GetStudio().finishedProducts.size() << "件作品";
	}
	else {
		c.SetColor(Console::Colors::gray);
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
	c.SetColor(Console::Colors::light_cyan);
	std::cout << "  编号    编程    美工    音乐    策划    心情    月薪  ";
	c.SetColor();
	if (instance.GetStudio().stuffs.size() == 0) {
		c.GotoXY(33, 7);
		c.SetColor(Console::gray);
		std::cout << "当前没有雇佣任何员工！";
		c.SetColor();
	}
	else {
		int i = 7;
		for (auto& stuff : instance.GetStudio().stuffs) {
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
	if (instance.isDeveloping)
	{
		c.GotoXY(93, 3);
		std::cout << "[ 作品名称 ] ";
		c.GotoXY(97, 4);
		std::cout << instance.workingProduct.value().name;
		c.GotoXY(93, 6);
		std::cout << "[ 开发进度 ] ";
		c.GotoXY(97, 7);
		std::cout << instance.GetDevProgress() << "%";
		c.GotoXY(93, 9);
		std::cout << "[ 作品数据 ] ";
		c.GotoXY(93, 10);
		std::cout << "趣味: " << instance.workingProduct.value().interesting;
		c.GotoXY(104, 10);
		std::cout << "画面: " << instance.workingProduct.value().graphics;
		c.GotoXY(93, 11);
		std::cout << "音乐: " << instance.workingProduct.value().sound;
		c.GotoXY(104, 11);
		std::cout << "玩法: " << instance.workingProduct.value().playability;
		c.GotoXY(97, 12);
		std::cout << "稳定: " << instance.workingProduct.value().stability;
	}
	else {
		c.GotoXY(93, 7);
		c.SetColor(Console::gray);
		std::cout << "当前没有正在开发的项目！";
		c.SetColor();
	}
#pragma endregion
#pragma region CommandPanel
	c.GotoXY(0, 14);
	auto result = printMenu(Menu({ "下一回合","项目管理","员工管理","设置菜单" }, 15, 0), c);
	c.Clear(0, 14, 120, 20);
	int subResult;
	switch (result) {
	case 0:
		if (instance.noConfirm) return progress<int>(true, true, 0);
		subResult = printMenu(Menu({ "是","否" }, 15, 0, "确定要进入下一回合吗？"), c);
		if (subResult == 0) return progress<int>(true, true, 0);
		return progress<int>(true, true, -1);
	case 1:
		subResult = printMenu(Menu({ "制作新游戏","调整项目计划","发布游戏","返回" }, 15, 0), c);
		switch (subResult)
		{
		case 0:
			createGame();
		}
		break;
	case 2:
		subResult = printMenu(Menu({ "人才市场","猎头挖角","员工菜单","返回" }, 15, 0), c);
		break;
	case 3:
		subResult = printMenu(Menu({ "保存游戏","游戏设置","退出游戏","返回" }, 15, 0), c);
		switch (subResult) {
		case 2:
			exit(0);
		}
	}
#pragma endregion
	return progress<int>(true, true, result);
}

