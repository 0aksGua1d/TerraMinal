#pragma once
#include <set>
#include <vector>
#include <queue>
#include <windows.h>

#include "Letter.h"

const char DEFAULT_CHAR = ' ';
const char DEFAULT_ATTR = 0x1;

const COORD START_COORD = { 0, 0 };

class Screen
{
public:
	Screen();
	Screen(const Screen&) = delete;
	Screen& operator=(const Screen&) = delete;
	Screen(Screen&&) = delete;
	Screen& operator=(Screen&&) = delete;

	void set_fullscreen();

	void draw();

	void addLetter(Letter l);
	void removeLetter(size_t x, size_t y, unsigned long id);
	size_t getZ(size_t x, size_t y);

	COORD getSize();


private:
	size_t width, height;
	std::vector<WCHAR> raw_char;
	std::vector<WORD> raw_attr;
	std::vector<std::queue<Letter>> board;
	std::set<size_t> invalidated_letters;
	HANDLE console_handle;
};
