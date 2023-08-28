#include "main.hpp"

GameData instance;

void gameCycle() {
	while (true) {
		studio();
	}
}

progress<int> beginning() {
	Console c = Console();

	while (true) {
		c.SetColor(Console::yellow);
		std::cout << "请为你的工作室想一个名字: ";
		c.SetColor();
		std::string name;
		std::cin >> name;
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
	}
}

progress<int> loadsave() {

	return progress<int>(true, false);
}


progress<int> studio() {
	auto c = Console();

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
	c.GotoXY(4, 10);
	if (instance.isDeveloping) {
		c.SetColor(Console::Colors::light_green);
		std::cout << "正在开发: " << instance.workingProduct.value().name;
	}
	else {
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
		c.GotoXY(93, 5);
		std::cout << "[ 作品名称 ] ";
		c.GotoXY(97, 6);
		std::cout << instance.workingProduct.value().name;
		c.GotoXY(93, 8);
		std::cout << "[ 开发进度 ] ";
		c.GotoXY(97, 9);
		std::cout << instance.GetDevProgress() << "%";
		c.GotoXY(93, 11);
		std::cout << "[ 作品数据 ] ";
		c.GotoXY(97, 12);
		std::cout << "趣味: " << instance.workingProduct.value().interesting;
		c.GotoXY(97, 13);
		std::cout << "画面: " << instance.workingProduct.value().graphics;
		c.GotoXY(97, 14);
		std::cout << "音乐: " << instance.workingProduct.value().sound;
		c.GotoXY(97, 15);
		std::cout << "玩法: " << instance.workingProduct.value().playability;
		c.GotoXY(97, 16);
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
	auto result = printMenu(Menu({ "下一回合","前往商店","前往人才市场","设置" }, 15, 0), c);
#pragma endregion
	return progress<int>(true, true, result);
}