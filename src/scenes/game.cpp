#include "main.hpp"

GameData instance;

void gameCycle() {
	while (true) {
		studio();
	}
}

progress<int> beginning() {
	Console c = Console();

	while (true) {
		c.SetColor(Console::yellow);
		std::cout << "��Ϊ��Ĺ�������һ������: ";
		c.SetColor();
		std::string name;
		std::cin >> name;
		if (name.size() > 16) {
			c.Clear();
			c.SetColor(Console::red);
			std::cout << "���������Ʋ��ܳ���16���ַ���ÿ�������� 2 ���ַ�������� \"" << name << "\" ��������һ���ƣ�" << std::endl;
			c.SetColor(Console::blue);
			std::cout << "�����ԡ�" << std::endl;
			c.SetColor();
			continue;
		}
		instance = GameData(name);
		std::cout << "�õģ���Ĺ���������Ϊ: " << instance.GetStudio().name << std::endl;
		std::cout << "��������" << std::endl << std::endl;
		auto result = printMenu(Menu({ "�ǣ��������","����������" }, 5, 0), c);
		if (result == 0) return progress<int>(true, false);
	}
}

progress<int> loadsave() {

	return progress<int>(true, false);
}


progress<int> studio() {
	auto c = Console();

#pragma region Sidebars
	for (int i = 0; i < 14; i++) {
		c.GotoXY(28, i);
		std::cout << "|";
	}
	for (int i = 0; i < 14; i++) {
		c.GotoXY(88, i);
		std::cout << "|";
	}
	c.GotoXY();
#pragma endregion

#pragma region DayPanel
	std::cout << "===========================" << std::endl;
	std::cout << "> Day ";
	c.SetColor(Console::Colors::cyan);
	std::cout << instance.day;
	c.SetColor();
	c.GotoXY(11, 1);
	std::cout << "|  ";

	for (int i = 0; i < 4; i++) {
		if (i != instance.stage) {
			c.SetColor(Console::Colors::gray);
			std::cout << "=  ";
		}
		else {
			c.SetColor(Console::Colors::light_yellow);
			std::cout << "[=]  ";
		}
	}
	c.SetColor();
	c.GotoXY(0, 2);
	std::cout << "===========================";
	c.SetColor();
#pragma endregion

#pragma region StudioPanel
	c.GotoXY(0, 3);
	std::cout << "[ ���������� ] ";
	c.GotoXY(4, 4);
	std::cout << instance.GetStudio().name;
	c.GotoXY(18, 4);
	std::cout << " ������";
	c.GotoXY(0, 6);
	std::cout << "[ �ʽ� ] ";
	c.GotoXY(4, 7);
	c.SetColor(Console::Colors::yellow);
	std::cout << "$ " << instance.money;
	c.SetColor();
	c.GotoXY(0, 9);
	std::cout << "[ ������״̬ ] ";
	c.GotoXY(4, 10);
	if (instance.isDeveloping) {
		c.SetColor(Console::Colors::light_green);
		std::cout << "���ڿ���: " << instance.workingProduct.value().name;
	}
	else {
		c.SetColor(Console::Colors::gray);
		std::cout << "������...";
	}
	c.SetColor();
	c.GotoXY(0, 12);
	std::cout << "[ ��ʷ��Ϣ ] ";
	c.GotoXY(4, 13);
	if (instance.GetStudio().finishedProducts.size() != 0) {
		c.SetColor(Console::Colors::light_magenta);
		std::cout << "�ѷ����� " << instance.GetStudio().finishedProducts.size() << "����Ʒ";
	}
	else {
		c.SetColor(Console::Colors::gray);
		std::cout << "�ȴ������������ײ���Ʒ";
	}
	c.SetColor();
#pragma endregion

#pragma region StuffStatPanel
	c.GotoXY(30, 0);
	for (int i = 0; i < 57; i++)std::cout << "=";
	c.GotoXY(30, 1);
	std::cout << " Ա����Ϣ";
	c.GotoXY(30, 3);
	c.SetColor(Console::Colors::light_cyan);
	std::cout << "  ���    ���    ����    ����    �߻�    ����    ��н  ";
	c.SetColor();
	if (instance.GetStudio().stuffs.size() == 0) {
		c.GotoXY(33, 7);
		c.SetColor(Console::gray);
		std::cout << "��ǰû�й�Ӷ�κ�Ա����";
		c.SetColor();
	}
	else {
		int i = 7;
		for (auto& stuff : instance.GetStudio().stuffs) {
			c.GotoXY(33, i);
			std::cout << stuff.id;
			c.GotoXY(41, i);
			std::cout << stuff.program;
			c.GotoXY(49, i);
			std::cout << stuff.art;
			c.GotoXY(57, i);
			std::cout << stuff.audio;
			c.GotoXY(65, i);
			std::cout << stuff.design;
			c.GotoXY(73, i);
			std::cout << stuff.happiness;
			c.GotoXY(81, i);
			std::cout << stuff.salary;
			i++;
		}
	}

#pragma endregion

#pragma region ProductPanel
	c.GotoXY(90, 0);
	std::cout << "===========================";
	c.GotoXY(90, 1);
	std::cout << " ��Ʒ����";
	c.GotoXY(90, 3);
	if (instance.isDeveloping)
	{
		c.GotoXY(93, 5);
		std::cout << "[ ��Ʒ���� ] ";
		c.GotoXY(97, 6);
		std::cout << instance.workingProduct.value().name;
		c.GotoXY(93, 8);
		std::cout << "[ �������� ] ";
		c.GotoXY(97, 9);
		std::cout << instance.GetDevProgress() << "%";
		c.GotoXY(93, 11);
		std::cout << "[ ��Ʒ���� ] ";
		c.GotoXY(97, 12);
		std::cout << "Ȥζ: " << instance.workingProduct.value().interesting;
		c.GotoXY(97, 13);
		std::cout << "����: " << instance.workingProduct.value().graphics;
		c.GotoXY(97, 14);
		std::cout << "����: " << instance.workingProduct.value().sound;
		c.GotoXY(97, 15);
		std::cout << "�淨: " << instance.workingProduct.value().playability;
		c.GotoXY(97, 16);
		std::cout << "�ȶ�: " << instance.workingProduct.value().stability;
	}
	else {
		c.GotoXY(93, 7);
		c.SetColor(Console::gray);
		std::cout << "��ǰû�����ڿ�������Ŀ��";
		c.SetColor();
	}
#pragma endregion
#pragma region CommandPanel
	c.GotoXY(0, 14);
	auto result = printMenu(Menu({ "��һ�غ�","ǰ���̵�","ǰ���˲��г�","����" }, 15, 0), c);
#pragma endregion
	return progress<int>(true, true, result);
}