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
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Yellow = 6,
		White = 7,
		Gray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		LightYellow = 14,
		BrightWhite = 15
	};

	enum ArrowCommands {
		Up = 72,
		Down = 80,
		Left = 75,
		Right = 77,
		Enter = 13,
		Backspace = 8,
		ESC = 27
	};

	Console() {
		handle_ = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void GotoXY() {
		COORD c = { 0,0 };
		SetConsoleCursorPosition(handle_, c);
	}

	void MoveX(short x) {
		COORD c{ x,GetCursorY() };
		SetConsoleCursorPosition(handle_, c);
	}

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

	void Clear(short x, short y, short dx, short dy) {
		COORD topLeft = { x, y };
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;

		GetConsoleScreenBufferInfo(handle_, &screen);
		FillConsoleOutputCharacterA(
			handle_, ' ', dx * dy, topLeft, &written
		);
		FillConsoleOutputAttribute(
			handle_, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			dx * dy, topLeft, &written
		);
		SetConsoleCursorPosition(handle_, topLeft);
	}

	void SetColor(const Colors f_color, const Colors bg_color = Black) const {
		SetConsoleTextAttribute(handle_, f_color | bg_color << 4);
	}

	void SetColor() const {
		SetConsoleTextAttribute(handle_, White);
	}

	void MenuRender(Menu m) {
		GotoXY(0, m.y);
		for (int i = 0; i < 117; i++) std::cout << "=";

		GotoXY(4, m.y + 1);
		if (m.title != "") {
			std::cout << m.title;
			m.y++;
			GotoXY(4, m.y + 1);
		}

		int total_rended = 0;
		for (auto& i : m.items)
		{
			if (total_rended == m.selection) {
				SetColor(Yellow, Gray);
				std::cout << " > " << i << " ";
				SetColor();
			}
			else {
				std::cout << " - " << i << " ";
			}

			GotoXY(4, m.y + 1 + (++total_rended));

		}
		GotoXY(0, m.y + 1 + total_rended);
		for (int i = 0; i < 117; i++) std::cout << "=";
	}

	int GetCursorY() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(handle_, &csbi);
		return csbi.dwCursorPosition.Y;
	}

	void Endl() {
		GotoXY(0, GetCursorY() + 1);
	}

	void Print(const std::string& text, Colors color = White, Colors bg_color = Black) {
		SetColor(color, bg_color);
		std::cout << text;
		SetColor();
	}

	void Pause() {
		auto _ = getchar();
	}

	ArrowCommands static GetArrowCommand(bool hasReturn = false) {
		int ch = _getch();
		while (ch != ESC) {
			switch (ch) {
			case Up:
				return Up;
			case Down:
				return Down;
			case Left:
				return Left;
			case Right:
				return Right;
			case Enter:
				return Enter;
			case Backspace:
				if (hasReturn)
					return Backspace;
				else
					ch = _getch();
				break;
			default:
				ch = _getch();
				break;
			}
		}
		return ESC;
	}
};

#endif //CONSOLE_H
