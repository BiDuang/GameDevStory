#include <iostream>
#include "src/console.hpp"
#include "src/scenes/main.hpp"

int main()
{
	openning();
	mainMenu("preRev 1.3");
	gameCycle();

	return 0;
}

// Thanks to mr_cino for the help with the code, he gave me tons of the C++ programming knowledge and lead
// me to the right way of programming.
// You can check his own language compiler project here:
// 
// Woolang, the 4th generation of 'scene' programing language
// https://git.cinogama.net/cinogamaproject/woolang