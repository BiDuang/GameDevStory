#include <iostream>
#include "src/console.hpp"
#include "src/scenes/main.hpp"

int main()
{
	openning("dev 1.0");
	auto result = mainMenu();
	switch (result.info) {
	case 0:
		std::cout << "Start game" << std::endl;
		break;
	case 1:
		std::cout << "Load game" << std::endl;
		break;
	case 2:
		exit(0);
	}
	return 0;
}
