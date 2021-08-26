#include "Loader.h"

Loader::Loader() : sprite_loader() {}

void Loader::load_sprites(const std::string& filename) {
    this->sprite_loader.load_file(filename);
}

std::shared_ptr<Sprite> Loader::get_sprite(const std::wstring& sprite_name) {
    return this->sprite_loader.get_sprite(sprite_name);
}
