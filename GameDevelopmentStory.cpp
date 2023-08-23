#include <iostream>
#include "src/console.hpp"
#include "src/scenes/main.hpp"

int main()
{
	/*auto command = console::get_arrow_command();
	while (command != console::esc)
	{
		std::cout << command << std::endl;
		command = console::get_arrow_command();
	}*/


	openning("dev 1.0");
	auto result = main_menu();
	std::cout << result.info << std::endl;

	return 0;
}
