#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>

class menu
{
public:
	std::vector<std::string> items;
	int row_items = 1;
	int selection = 0;

	menu(std::vector<std::string> items, int row_items, int selection) :
		items(items), row_items(row_items), selection(selection) {}

	~menu() {
		items.clear();
	}
};

#endif
