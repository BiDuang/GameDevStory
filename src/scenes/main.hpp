#ifndef SCENES_HPP
#define SCENES_HPP

#include <iostream>
#include <fstream>
#include <windows.h>
#include "../console.hpp"
#include "../utils/main.hpp"
#include "../models/menu.hpp"
#include "../models/progress.hpp"

extern progress<int> openning(std::string version);
extern progress<int> main_menu();

#endif