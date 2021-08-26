#pragma once

#include <string>
#include <memory>
#include <map>

#include "renderable/Sprite.h"
#include "SpriteLoaderBase.h"
#include "SpriteLoader1.h"

const std::vector<std::shared_ptr<SpriteLoaderBase>> SPRITE_LOADERS({
    std::dynamic_pointer_cast<SpriteLoaderBase>(std::make_shared<SpriteLoader1>()),
                                                                 });

class SpriteLoader {
public:
    SpriteLoader();
    void load_file(const std::string& filename);
    std::shared_ptr<Sprite> get_sprite(const std::wstring& sprite_name);

private:
    std::map<std::wstring, std::shared_ptr<Sprite>> loaded_sprites;
    std::map<size_t, std::shared_ptr<SpriteLoaderBase>> loaders;
};
