#include "main.hpp"

std::unique_ptr<GameData> instance;

void gameCycle() {
	Console c;
	while (true) {
		auto result = studio(c);
		if (result.info == 0) {
			instance->RoundDev(c);
			if (instance->day % 7 == 0 && instance->stage == 0) instance->WeekSet(c);
		}

	}
}

progress<int> beginning() {
	Console c;
	c.Clear();
	while (true) {
		c.SetColor(Console::Yellow);
		std::cout << "��Ϊ��Ĺ����Ҿ���һ������: ";
		c.SetColor();
		std::string name;
		std::getline(std::cin, name);
		name = trim(name);
		if (name.empty()) {
			c.Clear();
			c.SetColor(Console::Red);
			std::cout << "���������Ʋ���Ϊ�գ�" << std::endl;
			c.SetColor(Console::Blue);
			std::cout << "�����ԡ�" << std::endl;
			c.SetColor();
			continue;
		}
		if (name.size() > 16) {
			c.Clear();
			c.SetColor(Console::Red);
			std::cout << "���������Ʋ��ܳ���16���ַ���ÿ�������� 2 ���ַ�������� \"" << name << "\" ��������һ���ƣ�" << std::endl;
			c.SetColor(Console::Blue);
			std::cout << "�����ԡ�" << std::endl;
			c.SetColor();
			continue;
		}
		instance = std::make_unique<GameData>(name);

		std::cout << "�õģ���Ĺ���������Ϊ: " << instance->studio.name << std::endl;
		std::cout << "��������" << std::endl << std::endl;
		auto result = printMenu(Menu({ "�ǣ��������","����������" }, 5, 0), c);
		if (result == 0) return progress<int>(true);
		else c.Clear();
	}
}

progress<int> loadsave() {
	instance = std::make_unique<GameData>(std::filesystem::path("save/1.save"));
	return progress<int>(true);
}

progress<int> createGame(Console& c) {
	c.Clear();
	c.GotoXY();

	std::string name;
	while (true) {
		c.SetColor(Console::Yellow);
		std::cout << "Ϊ�������Ϸ����һ�����֣�";
		c.SetColor();
		std::getline(std::cin, name);
		name = trim(name);
		if (name.empty()) {
			c.Clear();
			c.SetColor(Console::Red);
			std::cout << "��Ϸ���Ʋ���Ϊ�գ�" << std::endl;
			c.SetColor(Console::Blue);
			std::cout << "�����ԡ�" << std::endl;
			c.SetColor();
			continue;
		}
		if (name.size() > 16) {
			c.Clear();
			c.SetColor(Console::Red);
			std::cout << "��Ϸ���Ʋ��ܳ���16���ַ���ÿ�������� 2 ���ַ�������� \"" << name << "\" ��������һ���ƣ�" << std::endl;
			c.SetColor(Console::Blue);
			std::cout << "�����ԡ�" << std::endl;
			c.SetColor();
			continue;
		}
		break;

	}

	c.GotoXY(0, 1);
	c.SetColor(Console::Yellow);
	std::cout << "Ϊ�������Ϸ����һ�����ͣ�";
	c.SetColor();
	auto gameType = printMenu(Menu({ "������Ϸ","ð����Ϸ","������Ϸ","�����Ϸ","������Ϸ" }, 2, 0), c);
	c.Clear(0, 1, 120, 20);
	c.GotoXY(0, 1);
	c.SetColor(Console::LightBlue);
	switch (gameType)
	{
	case 0:
		std::cout << "�㽫����һ�� ������Ϸ��";
		break;
	case 1:
		std::cout << "�㽫����һ�� ð����Ϸ��";
		break;
	case 2:
		std::cout << "�㽫����һ�� ������Ϸ��";
		break;
	case 3:
		std::cout << "�㽫����һ�� �����Ϸ��";
		break;
	case 4:
		std::cout << "�㽫����һ�� ������Ϸ��";
		break;
	}
	c.SetColor();

	c.GotoXY(0, 3);
	c.SetColor(Console::Yellow);
	std::cout << "�����Ϸ�����ĸ�ƽ̨�Ϸ��ۣ�";
	auto platform = printMenu(Menu({ "PC","Mobile","XCase","Zwitch","PS114514" }, 4, 0), c);
	c.Clear(0, 2, 120, 20);
	c.GotoXY(0, 2);
	c.SetColor(Console::LightBlue);
	switch (platform)
	{
	case 0:
		std::cout << "��ѡ���� PCƽ̨ ���ۡ�";
		break;
	case 1:
		std::cout << "��ѡ���� �ƶ���ƽ̨ ���ۡ�";
		break;
	case 2:
		std::cout << "��ѡ���� XCaseƽ̨ ���ۡ�";
		break;
	case 3:
		std::cout << "��ѡ���� Zwitchƽ̨ ���ۡ�";
		break;
	case 4:
		std::cout << "��ѡ���� PS114514ƽ̨ ���ۡ�";
		break;
	}
	c.SetColor();

	auto confirm = printMenu(Menu({ "��","��" }, 4, 0, "ȷ��Ҫ��ʼ��������Ϸ��? �⽫���� $5000 ��Ϊ����ѡ�"), c);
	if (confirm == 0) {
		instance->RoundDev(c);
		instance->workingProduct = Product(name, instance->day, Platform(platform), GameType(gameType));
		instance->money -= 5000;
	}
	return progress<int>(true);
}

progress<int> setDevPlan(Console& c) {
	std::string s1 = "���������ٶ�", name;
	s1 += instance->isFastDev ? "Ϊ\"��ͨ����\"" : "Ϊ\"�Ӽ�����\"";
	switch (printMenu(Menu({ "������Ϸ����",s1,"����" }, 15, true), c))
	{
	case 0:
		c.Clear();
		c.GotoXY();
		while (true) {
			c.SetColor(Console::Yellow);
			std::cout << "Ϊ�㿪���е���Ϸ����һ�����֣�";
			c.SetColor();
			std::getline(std::cin, name);
			name = trim(name);
			if (name.empty()) {
				c.Clear();
				c.SetColor(Console::Red);
				std::cout << "��Ϸ���Ʋ���Ϊ�գ�" << std::endl;
				c.SetColor(Console::Blue);
				std::cout << "�����ԡ�" << std::endl;
				c.SetColor();
				continue;
			}
			if (name.size() > 16) {
				c.Clear();
				c.SetColor(Console::Red);
				std::cout << "��Ϸ���Ʋ��ܳ���16���ַ���ÿ�������� 2 ���ַ�������� \"" << name << "\" ��������һ���ƣ�" << std::endl;
				c.SetColor(Console::Blue);
				std::cout << "�����ԡ�" << std::endl;
				c.SetColor();
				continue;
			}
			break;
		}
		instance->workingProduct.value().name = name;
		break;
	case 1:
		if (instance->isFastDev) printMenu(Menu({ "�õ�" }, 15, 0, "�����ٶ��ѱ�����Ϊ��ͨ�ٶȡ�"), c);
		else printMenu(Menu({ "�õ�" }, 15, 0, "�����ٶ��ѱ�����Ϊ�Ӽ����⽫�ڼӿ���Ϸ�������̵�ͬʱ����Ʒ��"), c);
		instance->isFastDev = !instance->isFastDev;
		break;
	case 2:
		return progress<int>(true);
	}
	return progress<int>(true);
}

progress<int> jobFair(Console& c) {
	instance->isFairChecked = true;
	c.Clear();
	c.GotoXY();
	for (int i = 0; i < 117; i++) std::cout << "=";
	c.Endl();
	c.Print("�˲��г�", Console::Blue);
	c.Endl();
	for (int i = 0; i < 117; i++) std::cout << "=";
	c.Endl();
	std::vector<Stuff> jobSeekers = { Stuff(instance->day, JobType::Programmer, -1),Stuff(instance->day,JobType::Musician,-1),
		Stuff(instance->day,JobType::Artist,-1), Stuff(instance->day,JobType::Designer,-1) };
	if (randint(0, 100) < 15) jobSeekers[randint(0, 3)] = Stuff(instance->day, JobType::Almighty, -1);
	c.Print("��ÿ�������ѽ���һ���˲��г�Ѱ����ְ�ߣ�֮��ÿ�ν�����Ҫ֧�� $1000", Console::Yellow);
	c.Endl();
	c.Print("��Ĺ����������Թ��� 4 ��Ա��������Խ����е�Ա����������Ƹ�µ�Ա����");
	c.GotoXY(30, c.GetCursorY() + 2);
	c.SetColor(Console::Colors::Cyan);
	std::cout << "  ְҵ    ���    ����    ����    �߻�    ����    ��н  ";
	c.SetColor();
	for (auto& stuff : jobSeekers) {
		c.Endl();
		for (int i = 0; i < 109; i++) std::cout << "-";
		c.Endl();
		c.MoveX(32);
		switch (stuff.job) {
		case JobType::Programmer:
			c.Print("����", Console::LightCyan);
			break;
		case JobType::Musician:
			c.Print("����", Console::Blue);
			break;
		case JobType::Artist:
			c.Print("����", Console::Magenta);
			break;
		case JobType::Designer:
			c.Print("�߻�", Console::LightRed);
			break;
		case JobType::Almighty:
			c.Print("ȫ��", Console::Yellow);
			break;
		}
		c.MoveX(41);
		std::cout << stuff.program;
		c.MoveX(49);
		std::cout << stuff.art;
		c.MoveX(57);
		std::cout << stuff.audio;
		c.MoveX(65);
		std::cout << stuff.design;
		c.MoveX(73);
		std::cout << stuff.happiness;
		c.MoveX(81);
		std::cout << stuff.salary;
	}
	c.Endl();
	for (int i = 0; i < 109; i++) std::cout << "-";
	c.Endl();
	auto selection = printMenu(Menu({ "��Ƹ 1 ��", "��Ƹ 2 ��","��Ƹ 3 ��","��Ƹ 4 ��","�뿪�˲��г�" }, 15, 0, "��һ����ʲô��"), c);
	switch (selection) {
	case 0:
	case 1:
	case 2:
	case 3:
		printMenu(Menu({ "�õ�" }, 15, 0, instance->studio.HireStuff(jobSeekers[selection]) ? "��Ƹ�ɹ���" : "��Ƹʧ�ܣ���Ĺ�����������"), c);
		break;
	}
	return progress<int>(true);
}


progress<int> studio(Console& c) {
	c.Clear();
#pragma region Sidebars
	for (int i = 0; i < 15; i++) {
		c.GotoXY(28, i);
		std::cout << "|";
	}
	for (int i = 0; i < 15; i++) {
		c.GotoXY(88, i);
		std::cout << "|";
	}
	c.GotoXY();
#pragma endregion

#pragma region DayPanel
	std::cout << "===========================" << std::endl;
	std::cout << "> Day ";
	c.SetColor(Console::Colors::Cyan);
	std::cout << instance->day;
	c.SetColor();
	c.GotoXY(11, 1);
	std::cout << "|  ";

	for (int i = 0; i < 4; i++) {
		if (i != instance->stage) {
			c.SetColor(Console::Colors::Gray);
			std::cout << "=  ";
		}
		else {
			c.SetColor(Console::Colors::LightYellow);
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
	std::cout << instance->studio.name;
	c.GotoXY(18, 4);
	std::cout << " ������";
	c.GotoXY(0, 6);
	std::cout << "[ �ʽ� ] ";
	c.GotoXY(4, 7);
	c.SetColor(Console::Colors::Yellow);
	std::cout << "$ " << instance->money;
	c.SetColor();
	c.GotoXY(0, 9);
	std::cout << "[ ������״̬ ] ";
	c.GotoXY(2, 10);
	if (instance->workingProduct.has_value()) {
		c.SetColor(Console::Colors::LightGreen);
		std::cout << "���ڿ���:" << instance->workingProduct.value().name;
	}
	else {
		c.GotoXY(4, 10);
		c.SetColor(Console::Colors::Gray);
		std::cout << "������...";
	}
	c.SetColor();
	c.GotoXY(0, 12);
	std::cout << "[ ��ʷ��Ϣ ] ";
	c.GotoXY(4, 13);
	if (instance->studio.finishedProducts.size() != 0) {
		c.SetColor(Console::Colors::LightMagenta);
		std::cout << "�ѷ����� " << instance->studio.finishedProducts.size() << "����Ʒ";
	}
	else {
		c.SetColor(Console::Colors::Gray);
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
	c.SetColor(Console::Colors::LightCyan);
	std::cout << "  ���    ���    ����    ����    �߻�    ����    ��н  ";
	c.SetColor();
	if (instance->studio.stuffs.size() == 0) {
		c.GotoXY(33, 7);
		c.SetColor(Console::Gray);
		std::cout << "��ǰû�й�Ӷ�κ�Ա����";
		c.SetColor();
	}
	else {
		int i = 7;
		for (auto& stuff : instance->studio.stuffs) {
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
	if (instance->workingProduct.has_value())
	{
		c.GotoXY(93, 3);
		std::cout << "[ ��Ʒ���� ] ";
		c.GotoXY(97, 4);
		std::cout << instance->workingProduct.value().name;
		c.GotoXY(93, 6);
		std::cout << "[ �������� ] ";
		c.GotoXY(97, 7);
		std::cout << instance->GetDevProgress() << "%";
		if (instance->isFastDev) {
			c.GotoXY(103, 7);
			c.SetColor(Console::LightRed);
			std::cout << "�Ӽ�����";
			c.SetColor();
		}
		c.GotoXY(93, 9);
		std::cout << "[ ��Ʒ���� ] ";
		c.GotoXY(93, 10);
		std::cout << "Ȥζ: " << instance->workingProduct.value().interesting;
		c.GotoXY(104, 10);
		std::cout << "����: " << instance->workingProduct.value().graphics;
		c.GotoXY(93, 11);
		std::cout << "����: " << instance->workingProduct.value().sound;
		c.GotoXY(104, 11);
		std::cout << "�淨: " << instance->workingProduct.value().playability;
		c.GotoXY(97, 12);
		std::cout << "�ȶ�: " << instance->workingProduct.value().stability;
	}
	else {
		c.GotoXY(93, 7);
		c.SetColor(Console::Gray);
		std::cout << "��ǰû�����ڿ�������Ŀ��";
		c.SetColor();
	}
#pragma endregion
#pragma region CommandPanel
	c.GotoXY(0, 14);
	auto result = printMenu(Menu({ "��һ�غ�","��Ŀ����","Ա������","�����ҹ���","���ò˵�" }, 15), c);
	c.Clear(0, 14, 120, 20);
	int subResult;
	switch (result) {
	case 0:
		if (instance->noConfirm) return progress<int>(true, true, 0);
		if (printMenu(Menu({ "��","��" }, 15, 0, "ȷ��Ҫ������һ�غ���"), c) == 0) return progress<int>(true, true, 0);
		return progress<int>(true, true, -1);
	case 1:
		subResult = printMenu(Menu({ "��������Ϸ","������Ŀ�ƻ�","������Ϸ","����" }, 15, true), c);
		switch (subResult)
		{
		case 0:
			if (instance->workingProduct.has_value()) {
				printMenu(Menu({ "�õ�" }, 15, 0, "��ǰ�Ѿ���һ�����ڿ�������Ŀ��"), c);
				break;
			}
			createGame(c);
			break;
		case 1:
			if (instance->workingProduct.has_value())
				setDevPlan(c);
			else
				printMenu(Menu({ "�õ�" }, 15, 0, "��ǰû�����ڿ�������Ŀ��"), c);
			break;
		case 2:
			if (instance->workingProduct.has_value() && instance->workingProduct.value().isFinished)
			{
				instance->workingProduct.value().publishDay = instance->day;
				instance->PublishProduct();
			}
			else
				printMenu(Menu({ "�õ�" }, 15, 0, instance->workingProduct.has_value() ? "��Ϸ��û��������ɣ����ܷ��ۣ�" : "û���κ���Ϸ���Է��ۣ�"), c);
			break;
		}
		break;
	case 2:
		subResult = printMenu(Menu({ "�˲��г�","\"������Ч\"","����" }, 15, true), c);
		switch (subResult) {
		case 0:
			if (instance->isFairChecked) if (printMenu(Menu({ "֧�� $1000 �������볡","����" }, 15, 0, "���Ѿ�������˲��г��ˣ��Ƿ�Ҫ�����볡��"), c) == 0)
				instance->money -= 1000;
			else break;
			jobFair(c);
			break;
		case 1:
			if (instance->studio.stuffs.empty())
			{
				printMenu(Menu({ "�õ�" }, 15, 0, "��Ĺ������Ѿ�û���κ�Ա���ˣ�"), c);
				break;
			}
			std::vector<std::string> options;
			for (auto i = 1; i <= instance->studio.stuffs.size(); i++)
			{
				std::string str = "���� ";
				str += std::to_string(instance->studio.stuffs[i - 1].id) + " ��Ա��";
				options.push_back(str);
			}
			options.push_back("����");
			auto result = printMenu(Menu(options, 15, true), c);
			if (result != options.size() - 1) instance->studio.FireStuff(result);
			break;
		}
		break;
	case 3:
		subResult = printMenu(Menu({ "�ݼ�","���ܲƱ�","����������","����" }, 15, true), c);
		switch (subResult)
		{
		case 0:
			if (!printMenu(Menu({ "��","��" }, 15, 0, "ȷ��Ҫ�������ҷ�һ�������ΪÿλԱ���ָ�35�����顣"), c))
			{
				printMenu(Menu({ "�õ�" }, 15, 0,
					instance->TakeADayOff() ? "����������һ��٣�����Ա�����ú�Ъ��һ������" : "�����Ϲ����ˣ��Ѿ������ݼ��ˡ�"), c);
			}
			break;
		case 1:
			if (instance->day < 7) printMenu(Menu({ "�õ�" }, 15, 0, "��һ�ܽ�������вƱ�"), c);
			else instance->studio.financialReport.PrintReport(c);
			break;
		}
		break;
	case 4:
		subResult = printMenu(Menu({ "������Ϸ","��Ϸ����","�˳���Ϸ","����" }, 15, true), c);
		std::string s1, s2;
		auto flag = true;
		switch (subResult) {
		case 0:
			instance->TrySaving(std::filesystem::path("save/1.save"), true);
			break;
		case 1:

			while (flag) {
				s1 = "�Զ�ȷ�ϲ���: ", s2 = "ÿ���Զ�����: ";
				s1 += instance->noConfirm ? "��" : "��";
				s2 += instance->isAutoSave ? "��" : "��";
				switch (printMenu(Menu({ s1,s2,"����" }, 15, true), c))
				{
				case 0:
					instance->noConfirm = !instance->noConfirm;
					break;
				case 1:
					instance->isAutoSave = !instance->isAutoSave;
					break;
				case 2:
					flag = false;
					break;
				}
			}
			break;
		case 2:
			exit(0);
		}
	}
#pragma endregion
	return progress<int>(true, true, result);
}

