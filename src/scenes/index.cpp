#include "main.hpp"

progress<int> openning(std::string version) {
	auto c = Console();
	c.SetColor(Console::Colors::light_blue);
	printAsciiImage("src/ascii_images/author.txt");
	Sleep(3000);
	c.Clear();
	c.SetColor();
	c.SetColor(Console::Colors::cyan);
	printAsciiImage("src/ascii_images/title.txt");
	c.SetColor();
	std::cout << std::endl;
	c.SetColor(Console::Colors::yellow);
	std::cout << "Version: " << version << " | This is a development version!" << std::endl;

	return true;
}

progress<int> mainMenu() {
	auto c = Console();
	std::cout << "    ";
	c.SetColor(Console::Colors::black, Console::Colors::white);
	auto m = Menu({ "开始游戏", "加载游戏", "退出游戏" }, 3, 43, 11, 0);
	auto result = progress<int>(false, true, 0);
	while (true) {
		c.MenuRender(m);
		auto command = c.GetArrowCommand();
		switch (command) {
		case Console::ArrowCommands::left:
			m.selection--;
			break;
		case Console::ArrowCommands::right:
			m.selection++;
			break;
		case Console::ArrowCommands::enter:
			result.is_ok = true;
			result.info = m.selection;
			c.Clear();
			return result;

		default:
			break;
		}
		if (m.selection < 0) {
			m.selection = m.items.size() - 1;
		}
		else if (m.selection >= m.items.size()) {
			m.selection = 0;
		}
	}
	return result;
}