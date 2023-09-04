#ifndef SCENES_HPP
#define SCENES_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include "../console.hpp"
#include "../utils/main.hpp"
#include "../models/menu.hpp"
#include "../models/progress.hpp"
#include "../models/game.hpp"

extern void openning();
extern void mainMenu(std::string version);

extern progress<int> beginning();
extern progress<int> loadsave();

extern void gameCycle();
extern progress<int> studio(Console& c);


#endif