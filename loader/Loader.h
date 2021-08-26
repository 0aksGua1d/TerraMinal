#pragma once
#include "SpriteLoader/SpriteLoader.h"

class Loader {
public:
    Loader();

    void load_sprites(const std::string& filename);
    std::shared_ptr<Sprite> get_sprite(const std::wstring& sprite_name);

private:
    SpriteLoader sprite_loader;
};
