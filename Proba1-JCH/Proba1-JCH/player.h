#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();
    void update(sf::Time deltaTime);
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    sf::Sprite getSprite() const;
    void setPosition(float x, float y);
    bool isMovingUp() const;
    bool isMovingDown() const;
    bool isMovingLeft() const;
    bool isMovingRight() const;

private:
    sf::Sprite mSprite;
    sf::Texture mTexture;
    float mSpeed;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
};

#endif // PLAYER_H