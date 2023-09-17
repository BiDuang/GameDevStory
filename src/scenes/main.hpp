#ifndef SCENES_HPP
#define SCENES_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <windows.h>
#include "../console.hpp"
#include "../utils/main.hpp"
#include "../models/menu.hpp"
#include "../models/progress.hpp"
#include "../models/game.hpp"

extern void openning();
extern void mainMenu(const std::string& version);

extern Progress<int> beginning();
extern Progress<int> loadsave();

extern void gameCycle();
extern Progress<int> studio(Console& c);


#endif