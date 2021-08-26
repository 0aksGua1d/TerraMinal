#pragma once

#include <utility>

#include "GraphicBuffers.h"
#include "Renderable.h"
#include "../engine/Position.h"

class Frame : public Renderable {
public:
    Frame(std::shared_ptr<CharBuffer> chars, std::shared_ptr<AttrBuffer> attrs, COORD char_off, COORD attr_off) : chars(
            std::move(chars)), attrs(std::move(attrs)), char_off(char_off), attr_off(attr_off) {}

    [[nodiscard]] bool need_update(size_t dTimeMilli) const override;

    void update(size_t dTimeMilli) override;

    std::shared_ptr<Renderable> copy() override;

    void draw(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const override;

    void erase(std::shared_ptr<Screen> screen, Position pos, unsigned long id) const override;

private:
    std::shared_ptr<CharBuffer> chars;
    std::shared_ptr<AttrBuffer> attrs;
    //std::shared_ptr<HitMask> hitmask;
    COORD char_off;
    COORD attr_off;
    //COORD hitmask_off;
};