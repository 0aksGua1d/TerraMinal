#include <iostream>
#include "Screen.h"

Screen::Screen() {
	console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleDisplayMode(console_handle, CONSOLE_FULLSCREEN_MODE, NULL);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console_handle, &info);
	SetConsoleScreenBufferSize(console_handle, info.dwMaximumWindowSize);

	this->width = info.dwMaximumWindowSize.X;
	this->height = info.dwMaximumWindowSize.Y;
	size_t size = this->width * this->height;
	this->raw_char.resize(this->width * this->height);
	this->raw_attr.resize(this->width * this->height);

	for (size_t i = 0;i < this->width * this->height;++i) {
	    this->raw_char[i] = DEFAULT_CHAR;
	    this->raw_attr[i] = DEFAULT_ATTR;
	}

	this->board.resize(size);
}

void Screen::set_fullscreen()
{
	SetConsoleDisplayMode(console_handle, CONSOLE_FULLSCREEN_MODE, NULL);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console_handle, &info);
	SetConsoleScreenBufferSize(console_handle, info.dwMaximumWindowSize);
}

void Screen::draw()
{
	bool invalid_char = false;
	bool invalid_attr = false;
	for (size_t index : invalidated_letters) {
		auto& queue = board[index];
		WCHAR new_char = DEFAULT_CHAR;
		WORD new_attr = DEFAULT_ATTR;
		if (!queue.empty()) {
			auto letter = queue.front();
			new_char = letter.ch;
			new_attr = letter.attr;
		}

		if (raw_char[index] != new_char) {
			invalid_char = true;
			raw_char[index] = new_char;
		}
		if (raw_attr[index] != new_attr) {
			invalid_attr = true;
			raw_attr[index] = new_attr;
		}
	}
	invalidated_letters.clear();

	DWORD garbage_collector;
	if (invalid_attr) {
		WriteConsoleOutputAttribute(console_handle, raw_attr.data(), raw_attr.size(), { 0, 0 }, &garbage_collector);
	}
	if (invalid_char) {
		WriteConsoleOutputCharacterW(console_handle, raw_char.data(), raw_char.size(), { 0, 0 }, &garbage_collector);
	}
}

void Screen::addLetter(Letter l)
{
    if (0 > l.pos.x || width < l.pos.x || 0 > l.pos.y || height < l.pos.y) {
        return;
    }
	auto& queue = this->board[l.pos.x + l.pos.y * width];
	std::queue<Letter> helper;

	while (!queue.empty() && queue.front().pos.z < l.pos.z) {
		helper.push(queue.front());
		queue.pop();
	}
	queue.push(l);
	while (!helper.empty()) {
		queue.push(helper.front());
		helper.pop();
	}
	invalidated_letters.insert(l.pos.x + l.pos.y * this->width);
}

void Screen::removeLetter(size_t x, size_t y, unsigned long id)
{
    if (0 > x || width < x || 0 > y || height < y) {
        return;
    }
    auto& queue = this->board[x + y * width];
	std::queue<Letter> helper;

	while (!queue.empty() && queue.front().id != id) {
		helper.push(queue.front());
		queue.pop();
	}
	if (!queue.empty()) {
		queue.pop();
	}
	while (!helper.empty()) {
		queue.push(helper.front());
		helper.pop();
	}
	invalidated_letters.insert(x + y * this->width);
}

size_t Screen::getZ(size_t x, size_t y)
{
	auto& queue = this->board[x + y * width];
	if (queue.empty())
		return 0;
	return queue.front().pos.z;
}

COORD Screen::getSize()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(console_handle, &info);
	return info.dwSize;
}
