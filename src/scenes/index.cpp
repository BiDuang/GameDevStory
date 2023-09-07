#include "main.hpp"

void openning() {
	Console c;
	c.SetColor(Console::Colors::light_blue);
	printAsciiImage("src/ascii_images/author.txt");
	Sleep(3000);
	c.Clear();
	c.SetColor();
}

void mainMenu(const std::string& version) {
	Console c;
	c.SetColor(Console::Colors::cyan);
	printAsciiImage("src/ascii_images/title.txt");
	c.SetColor();
	std::cout << std::endl;
	c.SetColor(Console::Colors::yellow);
	std::cout << "Version: " << version << " | This is a development version!" << std::endl;
	std::cout << "    ";
	c.SetColor(Console::Colors::black, Console::Colors::white);
	auto result = printMenu(Menu({ "开始游戏", "加载游戏", "退出游戏" }, 11, 0), c);
	switch (result) {
	case 0:
		beginning();
		gameCycle();
		break;
	}
}