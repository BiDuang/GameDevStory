#include "main.hpp"

progress<int> openning(std::string version) {
	auto c = console();
	c.set_color(console::colors::light_blue);
	print_ascii_images("src/ascii_images/author.txt");
	Sleep(3000);
	c.clear();
	c.set_color();
	c.set_color(console::colors::cyan);
	print_ascii_images("src/ascii_images/title.txt");
	c.set_color();
	std::cout << std::endl;
	c.set_color(console::colors::yellow);
	std::cout << "Version: " << version << " | This is a development version!" << std::endl;

	return true;
}

progress<int> main_menu() {
	auto c = console();
	std::wcout << L"    ";
	c.set_color(console::colors::black, console::colors::white);
	auto m = menu({ L"开始游戏", L"加载游戏", L"退出游戏" }, 3, 0);
	auto result = progress<int>(false, true, 0);
	c.clear();
	while (true) {
		c.menu_render(m);
		auto command = c.get_arrow_command();
		switch (command) {
		case console::arrow_commands::left:
			m.selection--;
			break;
		case console::arrow_commands::right:
			m.selection++;
			break;
		case console::arrow_commands::enter:
			result.is_ok = true;
			result.info = m.selection;
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
		std::cout << m.selection;
	}
	return result;
}