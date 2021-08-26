#include "Frame.h"

bool Frame::need_update(size_t dTimeMilli) const { return false; }

void Frame::update(size_t dTimeMilli) {}

std::shared_ptr<Renderable> Frame::copy()
{
    return std::make_shared<Frame>(*this);
}

void Frame::draw(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const
{
	for (int y = 0; y < this->chars->size(); y++) {
		auto& line = this->chars->at(y - this->char_off.Y);
		auto& attr_line = this->attrs->at(y - this->attr_off.Y);
		for (int x = 0; x < line.size(); x++) {
			WCHAR ch = line[x - this->char_off.X];
			WORD attr = attr_line[x - this->attr_off.X];
			if (0x0 != attr) {
				Letter new_l = {
					ch,
					attr,
					{pos.x + x, pos.y + y, pos.z},
					id
				};
				screen->addLetter(new_l);
			}
		}
	}
}

void Frame::erase(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const
{
	for (size_t y = 0; y < this->chars->size(); y++) {
		auto& line = this->chars->at(y - this->char_off.Y);
		auto& attr_line = this->attrs->at(y - this->attr_off.Y);
		for (size_t x = 0; x < line.size(); x++) {
			WCHAR ch = line[x - this->char_off.X];
			DWORD attr = attr_line[x - this->attr_off.X];
			if (0x0 != attr) {
				screen->removeLetter(pos.x + x, pos.y + y, id);
			}
		}
	}
}
