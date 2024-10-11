#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <string>
#include <map>
#include <memory>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

template <typename T>
class AssetManager
{
protected:
    std::map<std::string, std::shared_ptr<T>> assets;

public:
    AssetManager(){};

    virtual void add(const std::string &key, const std::string &file_name) = 0;

    std::shared_ptr<T> get(const std::string &key) const
    {
        auto target = assets.find(key);

        if (target == assets.end())
        {
            throw std::invalid_argument("KEY NOT FOUND (unfound key = " + key + ")");
        }

        return target->second;
    }

    void delete_all()
    {
        assets.clear();
    }
};

class TextureManager : public AssetManager<sf::Texture>
{
public:
    TextureManager();

    void add(const std::string &key, const std::string &file_name) override;
};

class FontManager : public AssetManager<sf::Font>
{
public:
    FontManager();

    void add(const std::string &key, const std::string &file_name) override;
};

#endif