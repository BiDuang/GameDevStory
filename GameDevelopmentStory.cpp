//ProjectAuthor: BiDuang<me@biduang.cn>, mr_cino<mr_cino@cinogama.net>
//Inspired by Kairosoft's game: ゲーム発展国

#include "src/console.hpp"
#include "src/scenes/main.hpp"

int main()
{
	openning();
	mainMenu("preRev 1.3");
	gameCycle();

	return 0;
}

// Thanks to mr_cino for the help with the code, he gives me tons of the C++ programming knowledge and lead
// me to the right way of programming.
// You can check his woolang compiler project here:
// 
// Woolang, the 4th generation of 'scene' programing language
// https://git.cinogama.net/cinogamaproject/woolang