#include "TextureHolder.h"
#include <stdexcept>

TextureHolder& TextureHolder::getInstance()
{
    static TextureHolder instance;
    return instance;
}

void TextureHolder::loadTexture(const std::string& id, const std::string& filename)
{
    auto texture = std::make_unique<sf::Texture>();

    if (!texture->loadFromFile(filename)) {
        throw std::runtime_error("No se pudo cargar la textura: " + filename);
    }

    mTextures[id] = std::move(texture);
}

sf::Texture& TextureHolder::getTexture(const std::string& id)
{
    auto found = mTextures.find(id);
    if (found == mTextures.end()) {
        throw std::runtime_error("No se encontró la textura con ID: " + id);
    }

    return *found->second;
}