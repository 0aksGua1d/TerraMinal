#pragma once

#include <string>
#include <memory>
#include <map>
#include <fstream>

#include "renderable/Sprite.h"

class SpriteLoaderBase {
public:
    virtual std::map<std::wstring, std::shared_ptr<Sprite>> load_file(std::wifstream& file_stream) = 0;
    virtual size_t get_version() = 0;
};
