#include "main.hpp"

std::string& trim(std::string& s)
{
	if (s.empty())
	{
		return s;
	}

	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	s.erase(0, s.find_first_not_of("\t"));
	s.erase(s.find_last_not_of("\t") + 1);
	return s;
}

bool printAsciiImage(const std::string& path, bool is_utf8) {
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
		auto command = c.GetArrowCommand(m.hasReturn);
		switch (command) {
		case Console::up:
			m.selection--;
			break;
		case Console::down:
			m.selection++;
			break;
		case Console::enter:
			selected = true;
			c.Clear(0, m.y, 120, m.items.size() + 2 + (!m.title.empty()));
			return m.selection;
		case Console::backspace:
			selected = true;
			c.Clear(0, m.y, 120, m.items.size() + 2 + (!m.title.empty()));
			return m.items.size() - 1;
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