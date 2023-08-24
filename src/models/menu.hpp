#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>

class Menu
{
public:
	std::vector<std::string> items;
	int row_items = 1;
	int x = 0;
	int y = 0;
	int selection = 0;

	Menu(std::vector<std::string> items, int row_items, int x, int y, int selection) :
		items(items), row_items(row_items), x(x), y(y), selection(selection) {}

	~Menu() {
		items.clear();
	}
};

class TerminalSize {
public:
	short rows;
	short cols;

	TerminalSize(short r, short c) : rows(r), cols(c) {}
	~TerminalSize() = default;

};

#endif
