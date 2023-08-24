#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include "models/menu.hpp"

class Console {

private:
	HANDLE handle_;

public:
	enum Colors {
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

	enum ArrowCommands {
		up = 72,
		down = 80,
		left = 75,
		right = 77,
		enter = 13,
		esc = 27
	};

	Console() {
		handle_ = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	~Console() = default;

	void GotoXY(short x, short y) {
		COORD c = { x,y };
		SetConsoleCursorPosition(handle_, c);
	}

	TerminalSize GetTerminalSize() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(handle_, &csbi);
		return TerminalSize{ csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
	}

	void Clear() {
		COORD topLeft = { 0, 0 };
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;

		GetConsoleScreenBufferInfo(handle_, &screen);
		FillConsoleOutputCharacterA(
			handle_, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
		FillConsoleOutputAttribute(
			handle_, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
		SetConsoleCursorPosition(handle_, topLeft);
	}

	void SetColor(const Colors f_color, const Colors bg_color = black) const {
		SetConsoleTextAttribute(handle_, f_color | bg_color << 4);
	}

	void SetColor() const {
		SetConsoleTextAttribute(handle_, white);
	}

	void MenuRender(const Menu m) {
		GotoXY(0, m.y);
		for (int i = 0; i < 117; i++) {
			std::cout << "=";
		}
		auto colSize = GetTerminalSize().cols;
		GotoXY(m.x, m.y + 1);
		int row_rended = 0;
		for (auto& i : m.items)
		{
			if (row_rended == m.row_items) {
				std::cout << std::endl;
				row_rended = 0;
			}
			if (row_rended == m.selection) {
				SetColor(light_yellow);
				std::cout << i;
				SetColor();
			}
			else {
				std::cout << i;
			}
			std::cout << "    ";
			row_rended++;
		}
		GotoXY(0, m.y + 2);
		for (int i = 0; i < 117; i++) {
			std::cout << "=";
		}
	}

	ArrowCommands static GetArrowCommand() {
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
