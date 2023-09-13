// Author: BiDuang<me@biduang.cn>
// console.hpp is a lib for controlling the console terminal.
#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include "models/menu.hpp"


/**
 * @brief Class Console
 *
 * @details This class is used to manipulate the console.
 * @details It has methods to move the cursor, clear the screen, change the color of the text and background, and more.
*/
class Console {
private:
	HANDLE handle_;

public:
	enum Colors {	//Terminal Colors Enum
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

	enum ArrowCommands {	//Arrow Commands Enum
		Up = 72,
		Down = 80,
		Left = 75,
		Right = 77,
		Enter = 13,
		Backspace = 8,
		ESC = 27
	};

	~Console() = default; //Destructor with default implementation

	/**
	* @brief Construct a new Console object.
	*
	* @details When the object is created, it gets the handle of the console.
	*
	* @param `void`
	*/
	Console() {
		handle_ = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	/**
	* @brief Move the cursor to the position (0,0) of the console.
	*
	* @param void
	*
	* @return `void`
	*/
	void GotoXY() {
		COORD c = { 0,0 };
		SetConsoleCursorPosition(handle_, c);
	}

	/**
	* @brief Move the cursor to the position (x,y) of the console.
	*
	* @param x The x position of the cursor.
	* @param short The y position of the cursor.
	*
	* @return `void`
	*/
	void GotoXY(short x, short y) {
		COORD c = { x,y };
		SetConsoleCursorPosition(handle_, c);
	}

	/**
	* @brief Move the cursor to the position x of the console in the same screen line.
	*
	* @param x The x position of the cursor.
	*
	* @return `void`
	*/
	void MoveX(short x) {
		COORD c{ x,GetCursorY() };
		SetConsoleCursorPosition(handle_, c);
	}

	/**
	* @brief Get the terminal's size.
	*
	* @param void
	*
	* @return `TerminalSize` A TerminalSize object, it contains the terminal's rows and cols info.
	*/
	TerminalSize GetTerminalSize() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(handle_, &csbi);
		return TerminalSize{ csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
	}

	/**
	* @brief Clear the whole terminal screen.
	*
	* @param void
	*
	* @return `void`
	*/
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

	/**
	* @brief Clear a specific part of the terminal screen, the clear area is a rectangle.
	*
	* @details The rectangle is defined by the top left corner position, the width and the height.
	*
	* @param x The x position of the top left corner of the rectangle.
	* @param y The y position of the top left corner of the rectangle.
	* @param dx The width of the rectangle.
	* @param dy The height of the rectangle.
	*
	* @return `void`
	*/
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

	/**
	* @brief Reset the terminal's color to the default (white font with black background).
	*
	* @param void
	*
	* @return `void`
	*/
	void SetColor() const {
		SetConsoleTextAttribute(handle_, White);
	}

	/**
	* @brief Set the terminal's color.
	*
	* @param fontColor The color of the font.
	* @param bgColor The color of the background, if not specified, black.
	*
	* @return `void`
	*/
	void SetColor(const Colors fontColor, const Colors bgColor = Black) const {
		SetConsoleTextAttribute(handle_, fontColor | bgColor << 4);
	}

	/**
	* @brief Draw a selection menu.
	* @detail Recommanded to use with the printMenu function. This part is only for the menu rendering.
	*
	* @param m A Menu object, it contains the menu's title, items and selection.
	*
	* @return `void`
	*/
	void MenuRender(Menu m) {
		GotoXY(0, m.y);
		for (int i = 0; i < 117; i++) std::cout << "=";

		GotoXY(4, m.y + 1);
		if (m.title != "") {
			std::cout << m.title;
			m.y++;
			GotoXY(4, m.y + 1);
		}

		int totalRendered = 0;
		for (auto& i : m.items)
		{
			if (totalRendered == m.selection) {
				SetColor(Yellow, Gray);
				std::cout << " > " << i << " ";
				SetColor();
			}
			else {
				std::cout << " - " << i << " ";
			}

			GotoXY(4, m.y + 1 + (++totalRendered));

		}
		GotoXY(0, m.y + 1 + totalRendered);
		for (int i = 0; i < 117; i++) std::cout << "=";
	}

	/**
	* @brief Get the current cursor's y position.
	*
	* @param void
	*
	* @return `int` The y position of the cursor.
	*/
	short GetCursorY() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(handle_, &csbi);
		return csbi.dwCursorPosition.Y;
	}

	/**
	* @brief Make cursor go to the next line.
	*
	* @param void
	*
	* @return `void`
	*/
	void Endl() {
		GotoXY(0, GetCursorY() + 1);
	}

	/**
	* @brief Print a text with color infomation.
	*
	* @details The text color will be reset to the default (white font with black background) after printing.
	*
	* @param text The text to be printed.
	* @param color The color of the text, if not specified, white.
	* @param bgColor The color of the background, if not specified, black.
	*/
	void Print(const std::string& text, Colors color = White, Colors bgColor = Black) {
		SetColor(color, bgColor);
		std::cout << text;
		SetColor();
	}

	/**
	* @brief Make the program pause by waiting for a key press.
	*
	* @param void
	*
	* @return `void`
	*/
	void Pause() {
		auto _ = getchar();
	}

	/**
	* @brief Get the arrow command from the keyboard input.
	*
	* @details The Backspace key is available only when the `hasReturn` is set to true.
	*
	* @param hasReturn If the menu has a cancel option, set this to true, otherwise, false.
	*
	* @return `ArrowCommands` A ArrowCommands enum, it represents the arrow command.
	*/
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
