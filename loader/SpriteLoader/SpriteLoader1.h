#pragma once

#include "SpriteLoaderBase.h"

class SpriteLoader1 : public SpriteLoaderBase {
public:
    std::map<std::wstring, std::shared_ptr<Sprite>> load_file(std::wifstream& file_stream) override;
    size_t get_version() override;
};
