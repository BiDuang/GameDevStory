#include "main.hpp"
/**
* @brief Trim a string.
*
* @details This function removes the spaces and tabs(a.k.a unreadable char) from the beginning and end of a string.
*
* @param s The string to be trimmed.
*
* @return `std::string&` The trimmed string.
*/
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

/**
* @brief Print an ASCII image by reading from a file.
*
* @details Because the ASCII image is too large and write it in the code is not a good idea. So the image data stored in the file.
*
* @param path The path of the file.
* @param isUTF8 Whether the file is encoded in UTF-8(Some ASCII images are not encoded in UTF8).
* @return `bool` If the file is opened successfully, return true, otherwise, false.
*/
bool printAsciiImage(const std::string& path, bool isUTF8) {
	if (isUTF8) {
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

/**
* @brief Draw a command menu.
*
* @details This function processes the keyboard input, the rendering part is handled by the Console class.
*
* @param m A Menu object, it contains the menu data.
* @param c Console to render the menu.
*
* @return `int` User's selection.
*/
int printMenu(Menu m, Console& c) {
	bool selected = false;
	int selections = (int)m.items.size();
	while (!selected) {
		c.MenuRender(m);
		auto command = c.GetArrowCommand(m.hasReturn);
		switch (command) {
		case Console::Up:
			m.selection--;
			break;
		case Console::Down:
			m.selection++;
			break;
		case Console::Enter:
			selected = true;
			c.Clear(0, m.y, 120, selections + 2 + (!m.title.empty()));
			return m.selection;
		case Console::Backspace:
			selected = true;
			c.Clear(0, m.y, 120, selections + 2 + (!m.title.empty()));
			return selections - 1;
		default:
			break;
		}
		if (m.selection < 0) {
			m.selection = selections - 1;
		}
		else if (m.selection >= selections) {
			m.selection = 0;
		}
	}
	return 0;
}