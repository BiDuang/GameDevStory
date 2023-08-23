#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include "models/menu.hpp"

class console {

private:
	HANDLE handle_;

public:
	enum colors {
		black = 0,
		blue = 1,
		green = 2,
		cyan = 3,
		red = 4,
		magenta = 5,
		yellow = 6,
		white = 7,
		gray = 8,
		light_blue = 9,
		light_green = 10,
		light_cyan = 11,
		light_red = 12,
		light_magenta = 13,
		light_yellow = 14,
		bright_white = 15
	};

	enum arrow_commands {
		up = 72,
		down = 80,
		left = 75,
		right = 77,
		enter = 13,
		esc = 27
	};

	console() {
		handle_ = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	~console() {
		set_color();
		CloseHandle(handle_);
	}

	void clear() {
		COORD topLeft = { 0, 0 };
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;

		GetConsoleScreenBufferInfo(console, &screen);
		FillConsoleOutputCharacterA(
			console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
		FillConsoleOutputAttribute(
			console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
		SetConsoleCursorPosition(console, topLeft);
	}

	void set_color(const colors f_color, const colors bg_color = black) const {
		SetConsoleTextAttribute(handle_, f_color | bg_color << 4);
	}

	void set_color() const {
		SetConsoleTextAttribute(handle_, white | black << 4);
	}

	void menu_render(const menu m) {
		int row_rended = 0;
		for (auto& i : m.items)
		{
			if (row_rended == m.row_items) {
				std::wcout << std::endl;
				row_rended = 0;
			}
			if (row_rended == m.selection) {
				set_color(light_yellow);
				std::wcout << i;
				set_color();
			}
			else {
				std::wcout << i;
			}
			std::wcout << "    ";
			row_rended++;
		}
	}

	arrow_commands static get_arrow_command() {
		int ch = _getch();
		while (ch != esc) {
			switch (ch) {
			case up:
				return up;
			case down:
				return down;
			case left:
				return left;
			case right:
				return right;
			case enter:
				return enter;
			default:
				ch = _getch();
				break;
			}
		}
		return esc;
	}

};

#endif //CONSOLE_H
