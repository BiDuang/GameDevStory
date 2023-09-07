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
	bool hasReturn = false;
	std::string title;

	Menu(std::vector<std::string> items, int y, int selection = 0, std::string title = "", bool hasReturn = false) :
		items(items), y(y), selection(selection), title(title), hasReturn(hasReturn) {}

	Menu(std::vector<std::string> items, int y, bool hasReturn) :
		items(items), y(y), hasReturn(hasReturn) {}
};

class TerminalSize {
public:
	int rows;
	int cols;

	TerminalSize(int c, int r) : cols(c), rows(r) {}
	~TerminalSize() = default;

};

#endif
