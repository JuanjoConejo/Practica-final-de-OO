#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>

class TextureHolder
{
public:
    static TextureHolder& getInstance();
    void loadTexture(const std::string& id, const std::string& filename);
    sf::Texture& getTexture(const std::string& id);

private:
    TextureHolder() = default;
    TextureHolder(const TextureHolder&) = delete;
    TextureHolder& operator=(const TextureHolder&) = delete;

    std::map<std::string, std::unique_ptr<sf::Texture>> mTextures;
};

#endif // TEXTURE_HOLDER_H
