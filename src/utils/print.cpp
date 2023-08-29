#include "main.hpp"


bool printAsciiImage(std::string path, bool is_utf8) {
	if (is_utf8) {
		std::locale::global(std::locale("en_US.UTF8"));
	}
	std::wifstream file(path);
	if (!file.is_open()) {
		std::cout << "Error opening file" << std::endl;
		return false;
	}
	std::wcout << file.rdbuf();
	file.close();
	std::locale::global(std::locale("C"));
	return true;
}

int printMenu(Menu m, Console& c) {
	bool selected = false;
	while (!selected) {
		c.MenuRender(m);
		auto command = c.GetArrowCommand();
		switch (command) {
		case Console::ArrowCommands::up:
			m.selection--;
			break;
		case Console::ArrowCommands::down:
			m.selection++;
			break;
		case Console::ArrowCommands::enter:
			selected = true;
			return m.selection;
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
}