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

	Menu(std::vector<std::string> items, int y, int selection) :
		items(items), y(y), selection(selection) {}

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
