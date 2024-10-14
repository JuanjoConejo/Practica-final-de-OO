#include "Player.h"
#include <stdexcept>

Player::Player()
    : mSpeed(200.f), mIsMovingUp(false), mIsMovingDown(false), mIsMovingLeft(false), mIsMovingRight(false)
{
    if (!mTexture.loadFromFile("./SPRAY/player.png")) {
        throw std::runtime_error("No se pudo cargar la textura del jugador.");
    }

    mSprite.setTexture(mTexture);
    mSprite.setScale(0.1f, 0.1f); // Ajustar tamaño del jugador
    mSprite.setPosition(50.f, 50.f); // Posición inicial del jugador
}

void Player::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);

    if (mIsMovingUp) {
        movement.y -= mSpeed;
    }
    if (mIsMovingDown) {
        movement.y += mSpeed;
    }
    if (mIsMovingLeft) {
        movement.x -= mSpeed;
    }
    if (mIsMovingRight) {
        movement.x += mSpeed;
    }

    // Actualizo la posición del jugador
    mSprite.move(movement * deltaTime.asSeconds());

    // Obtengo los límites del sprite del jugador
    sf::FloatRect playerBounds = mSprite.getGlobalBounds();

    // Verifico los límites de la ventana para que el jugador no se salga
    if (playerBounds.left < 0.f) {
        mSprite.setPosition(0.f, playerBounds.top);
    }
    if (playerBounds.left + playerBounds.width > 1920.f) {
        mSprite.setPosition(1920.f - playerBounds.width, playerBounds.top);
    }
    if (playerBounds.top < 0.f) {
        mSprite.setPosition(playerBounds.left, 0.f);
    }
    if (playerBounds.top + playerBounds.height > 1080.f) {
        mSprite.setPosition(playerBounds.left, 1080.f - playerBounds.height);
    }
}

void Player::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W) {
        mIsMovingUp = isPressed;
    }
    if (key == sf::Keyboard::S) {
        mIsMovingDown = isPressed;
    }
    if (key == sf::Keyboard::A) {
        mIsMovingLeft = isPressed;
    }
    if (key == sf::Keyboard::D) {
        mIsMovingRight = isPressed;
    }
}

sf::Sprite Player::getSprite() const
{
    return mSprite;
}

void Player::setPosition(float x, float y)
{
    mSprite.setPosition(x, y);
}

bool Player::isMovingUp() const
{
    return mIsMovingUp;
}

bool Player::isMovingDown() const
{
    return mIsMovingDown;
}

bool Player::isMovingLeft() const
{
    return mIsMovingLeft;
}

bool Player::isMovingRight() const
{
    return mIsMovingRight;
}
