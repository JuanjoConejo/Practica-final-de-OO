#include "game.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

Game::Game()
    : mWindow(sf::VideoMode(1920, 1080), "Aplicación SFML"),
    mEnemySpeed(100.f), // velocidad del enemigo
    mEnemyMovingUp(true), // inicia moviéndose hacia arriba
    mEnemyMovementAmount(100.f) // distancia que el enemigo se mueve hacia arriba
{
    // Configuro la textura del enemigo
    if (!mEnemyTexture.loadFromFile("./SPRAY/Enemic.png")) {
        throw std::runtime_error("No se pudo cargar la textura del enemigo.");
    }

    mEnemy.setTexture(mEnemyTexture);
    mEnemy.setScale(0.10f, 0.10f); // Ajustar tamaño del enemigo
    mEnemy.setPosition(1795.f, 200.f);  // Ajustar posición inicial del enemigo
    mEnemyInitialY = mEnemy.getPosition().y; // guardar la posición inicial en Y

    // Barrera superior
    mBarrierTop.setSize(sf::Vector2f(100.f, 800.f));
    mBarrierTop.setFillColor(sf::Color::Red);
    mBarrierTop.setPosition(1000.f, 0.f); // Mover a la izquierda

    // Barrera en el medio
    mBarrierMiddle.setSize(sf::Vector2f(100.f, 700.f));
    mBarrierMiddle.setFillColor(sf::Color::Red);
    mBarrierMiddle.setPosition(250.f, -50.f); // Ajusta la posición

    // Barrera inferior
    mBarrierBottom.setSize(sf::Vector2f(100.f, 1050.f));
    mBarrierBottom.setFillColor(sf::Color::Red);
    mBarrierBottom.setPosition(1400.f, mWindow.getSize().y - 750.f);

    // Segunda barrera inferior
    mBarrierBottom2.setSize(sf::Vector2f(100.f, 1050.f));
    mBarrierBottom2.setFillColor(sf::Color::Red);
    mBarrierBottom2.setPosition(600.f, mWindow.getSize().y - 750.f); // Ajusta la posición

    // Configuro la textura de fondo
    if (!mBackgroundTexture.loadFromFile("./SPRAY/fondo.jpg")) {
        throw std::runtime_error("No se pudo cargar la textura de fondo.");
    }

    mBackgroundSprite.setTexture(mBackgroundTexture);

    // Configuración de la meta
    mGoal.setSize(sf::Vector2f(500.f, 100.f)); // Tamaño del cuadrado
    mGoal.setFillColor(sf::Color::Green); // Color del cuadrado
    mGoal.setPosition(1500.f, 1000.f);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;

        while (timeSinceLastUpdate > sf::seconds(1.f / 60.f))
        {
            timeSinceLastUpdate -= sf::seconds(1.f / 60.f);
            processEvents();
            update(sf::seconds(1.f / 60.f));
        }

        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            mPlayer.handleInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            mPlayer.handleInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

bool Game::checkCollision(const sf::RectangleShape& barrier, const sf::Sprite& player) const
{
    return player.getGlobalBounds().intersects(barrier.getGlobalBounds());
}

void Game::update(sf::Time deltaTime)
{
    // Actualizar la posición del jugador
    mPlayer.update(deltaTime);

    // Movimiento del enemigo
    if (mEnemyMovingUp)
    {
        mEnemy.move(0.f, -mEnemySpeed * deltaTime.asSeconds());
        // Si ha alcanzado la distancia deseada, cambia de dirección
        if (mEnemy.getPosition().y <= mEnemyInitialY - mEnemyMovementAmount)
        {
            mEnemyMovingUp = false; // Cambiar dirección a abajo
        }
    }
    else // Si se mueve hacia abajo
    {
        mEnemy.move(0.f, mEnemySpeed * deltaTime.asSeconds());
        // Si regresa a la posición inicial, cambia de dirección
        if (mEnemy.getPosition().y >= mEnemyInitialY)
        {
            mEnemyMovingUp = true; // Cambiar dirección a arriba
        }
    }

    // Verificar colisión con la meta
    if (checkCollision(mGoal, mPlayer.getSprite()))
    {
        mWindow.close(); // Cerrar la ventana si hay colisión con la meta
    }

    // Colisiones con las barreras (sin cambios)
    sf::FloatRect playerBounds = mPlayer.getSprite().getGlobalBounds();
    sf::FloatRect barrierTopBounds = mBarrierTop.getGlobalBounds();
    sf::FloatRect barrierMiddleBounds = mBarrierMiddle.getGlobalBounds();
    sf::FloatRect barrierBottomBounds = mBarrierBottom.getGlobalBounds();
    sf::FloatRect barrierBottom2Bounds = mBarrierBottom2.getGlobalBounds();

    // Colisión con la barrera superior
    if (checkCollision(mBarrierTop, mPlayer.getSprite()))
    {
        if (playerBounds.top < barrierTopBounds.top + barrierTopBounds.height &&
            playerBounds.top + playerBounds.height > barrierTopBounds.top)
        {
            if (mPlayer.isMovingUp())
            {
                mPlayer.setPosition(playerBounds.left, barrierTopBounds.top + barrierTopBounds.height);
            }
            else if (mPlayer.isMovingDown())
            {
                mPlayer.setPosition(playerBounds.left, barrierTopBounds.top - playerBounds.height);
            }
            else if (mPlayer.isMovingLeft())
            {
                mPlayer.setPosition(barrierTopBounds.left + barrierTopBounds.width, playerBounds.top);
            }
            else if (mPlayer.isMovingRight())
            {
                mPlayer.setPosition(barrierTopBounds.left - playerBounds.width, playerBounds.top);
            }
        }
    }

    // Colisión con la barrera del medio
    if (checkCollision(mBarrierMiddle, mPlayer.getSprite()))
    {
        if (playerBounds.top < barrierMiddleBounds.top + barrierMiddleBounds.height &&
            playerBounds.top + playerBounds.height > barrierMiddleBounds.top)
        {
            if (mPlayer.isMovingUp())
            {
                mPlayer.setPosition(playerBounds.left, barrierMiddleBounds.top + barrierMiddleBounds.height);
            }
            else if (mPlayer.isMovingDown())
            {
                mPlayer.setPosition(playerBounds.left, barrierMiddleBounds.top - playerBounds.height);
            }
            else if (mPlayer.isMovingLeft())
            {
                mPlayer.setPosition(barrierMiddleBounds.left + barrierMiddleBounds.width, playerBounds.top);
            }
            else if (mPlayer.isMovingRight())
            {
                mPlayer.setPosition(barrierMiddleBounds.left - playerBounds.width, playerBounds.top);
            }
        }
    }

    // Colisión con la barrera inferior
    if (checkCollision(mBarrierBottom, mPlayer.getSprite()))
    {
        if (playerBounds.top < barrierBottomBounds.top + barrierBottomBounds.height &&
            playerBounds.top + playerBounds.height > barrierBottomBounds.top)
        {
            if (mPlayer.isMovingUp())
            {
                mPlayer.setPosition(playerBounds.left, barrierBottomBounds.top + barrierBottomBounds.height);
            }
            else if (mPlayer.isMovingDown())
            {
                mPlayer.setPosition(playerBounds.left, barrierBottomBounds.top - playerBounds.height);
            }
            else if (mPlayer.isMovingLeft())
            {
                mPlayer.setPosition(barrierBottomBounds.left + barrierBottomBounds.width, playerBounds.top);
            }
            else if (mPlayer.isMovingRight())
            {
                mPlayer.setPosition(barrierBottomBounds.left - playerBounds.width, playerBounds.top);
            }
        }
    }

    // Colisión con la segunda barrera inferior
    if (checkCollision(mBarrierBottom2, mPlayer.getSprite()))
    {
        if (playerBounds.top < barrierBottom2Bounds.top + barrierBottom2Bounds.height &&
            playerBounds.top + playerBounds.height > barrierBottom2Bounds.top)
        {
            if (mPlayer.isMovingUp())
            {
                mPlayer.setPosition(playerBounds.left, barrierBottom2Bounds.top + barrierBottom2Bounds.height);
            }
            else if (mPlayer.isMovingDown())
            {
                mPlayer.setPosition(playerBounds.left, barrierBottom2Bounds.top - playerBounds.height);
            }
            else if (mPlayer.isMovingLeft())
            {
                mPlayer.setPosition(barrierBottom2Bounds.left + barrierBottom2Bounds.width, playerBounds.top);
            }
            else if (mPlayer.isMovingRight())
            {
                mPlayer.setPosition(barrierBottom2Bounds.left - playerBounds.width, playerBounds.top);
            }
        }
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mBackgroundSprite); // Dibuja el fondo
    mWindow.draw(mBarrierTop);
    mWindow.draw(mBarrierMiddle);
    mWindow.draw(mBarrierBottom);
    mWindow.draw(mBarrierBottom2);
    mWindow.draw(mEnemy); // Dibuja el enemigo
    mWindow.draw(mPlayer.getSprite()); // Dibuja el jugador
    mWindow.draw(mGoal); // Dibuja la meta
    mWindow.display();
}