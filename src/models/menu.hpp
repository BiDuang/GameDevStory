#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>

class Menu
{
public:
	std::vector<std::string> items;
	int y = 0;
	int selection = 0;
	std::string title;

	Menu(std::vector<std::string> items, int y, int selection, std::string title = "") :
		items(items), y(y), selection(selection), title(title) {}

	~Menu() {
		items.clear();
	}
};

class TerminalSize {
public:
	short rows;
	short cols;

	TerminalSize(short c, short r) : cols(c), rows(r) {}
	~TerminalSize() = default;

};

#endif
