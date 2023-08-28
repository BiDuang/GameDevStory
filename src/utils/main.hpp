#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "../models/menu.hpp"
#include "../console.hpp"

extern bool printAsciiImage(std::string path, bool is_utf8 = false);
extern int randint(int min, int max);
extern int printMenu(Menu m, Console& c);

#endif