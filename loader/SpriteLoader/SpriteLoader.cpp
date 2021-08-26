#include <fstream>
#include <regex>

#include "logger/Logger.h"
#include "utils/string_converter.h"
#include "SpriteLoader.h"

const std::wstring SPRITE_START_LINE(L"TerraMinalSprite");
const std::wregex VERSION_REGEX(L"^version:(\\d+)$", std::wregex::optimize);

SpriteLoader::SpriteLoader() : loaders() {
    for (const auto& loader : SPRITE_LOADERS) {
        this->loaders[loader->get_version()] = loader;
    }
}

void SpriteLoader::load_file(const std::string& filename) {
    std::wifstream file(filename);
    if (!file.good()) {
        Logger::error("Failed to read file", {{"filename", filename}});
        return;
    }
    std::wstring line;
    if(!std::getline(file, line)) {
        Logger::error("Failed to read version line", {{"filename", filename}});
        return;
    }
    if (SPRITE_START_LINE != line) {
        Logger::error("Failed to read sprite init line", {{"filename", filename}});
        return;
    }
    if(!std::getline(file, line)) {
        Logger::error("Failed to read sprite version line", {{"filename", filename}});
        return;
    }
    std::wsmatch match;
    if(!std::regex_match(line, match, VERSION_REGEX)) {
        Logger::error("Bad sprite version line", {{"filename", filename},
                                                  {"line",  string_converter.to_bytes(line)}});
        return;
    }
    std::wstringstream stream;
    stream << match[1];
    size_t version;
    stream >> version;

    auto loader_ptr = this->loaders.find(version);
    if (this->loaders.end() == loader_ptr) {
        Logger::error("Version not supported", {{"filename", filename}, {"version", std::to_string(version)}});
        return;
    }
    auto sprites = loader_ptr->second->load_file(file);
    for (auto&[name, sprite] : sprites) {
        this->loaded_sprites[name] = sprite;
    }
}

std::shared_ptr<Sprite> SpriteLoader::get_sprite(const std::wstring& sprite_name) {
    return std::dynamic_pointer_cast<Sprite>(this->loaded_sprites.at(sprite_name)->copy());
}

