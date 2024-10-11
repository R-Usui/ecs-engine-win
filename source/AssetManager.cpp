#include <iostream>
#include <stdexcept>

#include "AssetManager.hpp"

TextureManager::TextureManager(){};

void TextureManager::add(const std::string &key, const std::string &file_name)
{
    auto path = "asset/texture/" + file_name;

    auto asset = std::make_shared<sf::Texture>();

    if (asset->loadFromFile(path))
    {
        assets[key] = asset;
    }
    else
    {
        throw std::invalid_argument("PATH NOT FOUND (unfound path = " + path + ")");
    }
}

//

FontManager::FontManager(){};

void FontManager::add(const std::string &key, const std::string &file_name)
{
    auto path = "asset/font/" + file_name;

    auto asset = std::make_shared<sf::Font>();

    if (asset->loadFromFile(path))
    {
        assets[key] = asset;
    }
    else
    {
        throw std::invalid_argument("PATH NOT FOUND (unfound path = " + path + ")");
    }
}
