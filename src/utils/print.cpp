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