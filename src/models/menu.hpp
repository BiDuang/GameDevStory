// Author: BiDuang<me@biduang.cn>


#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>

/**
* @brief Class Menu
*
* @details This class contains a menu configuration.
*/
class Menu
{
public:
	std::vector<std::string> items;
	int y = 0;
	int selection = 0;
	bool hasReturn = false;
	std::string title;

	/**
	* @brief Construct a new Menu with full config.
	*
	* @param items User's selection.
	* @param y The y position of the menu. (Top)
	* @param selection The default selection, default is 0.
	* @param title The title of the menu, default is no title.
	* @param hasReturn If the menu has a return option, default is false.
	*/
	Menu(std::vector<std::string> items, int y, int selection = 0, std::string title = "", bool hasReturn = false) :
		items(items), y(y), selection(selection), title(title), hasReturn(hasReturn) {}

	/**
	* @brief Construct a new Menu with simplified config.
	*
	* @param items User's selection.
	* @param y The y position of the menu. (Top)
	* @param hasReturn If the menu has a return option, default is false.
	*/
	Menu(std::vector<std::string> items, int y, bool hasReturn) :
		items(items), y(y), hasReturn(hasReturn) {}
};

/**
* @brief Class TerminalSize
*
* @details This class contains the terminal size info.
*/
class TerminalSize {
public:
	int rows;
	int cols;

	TerminalSize(int c, int r) : cols(c), rows(r) {}
	~TerminalSize() = default;
};
#endif	//MENU_HPP
