#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
public:
    Game();        // Constructor: inicializo el juego
    void run();    // Método principal para el bucle del juego

private:
    void processEvents();    // Procesa la entrada del usuario y los eventos
    void update(sf::Time deltaTime);  // Actualizo la lógica del juego
    void render();           // Renderizo la escena del juego

    bool checkCollision(const sf::RectangleShape& barrier, const sf::Sprite& player) const; // Comprobar colisiones

private:
    sf::RenderWindow mWindow;           // La ventana principal del juego
    Player mPlayer;                      // Objeto de la clase Player

    sf::RectangleShape mBarrierTop;     // Barrera en la parte superior
    sf::RectangleShape mBarrierMiddle;  // Nueva barrera en el medio
    sf::RectangleShape mBarrierBottom;  // Barrera en la parte inferior
    sf::RectangleShape mBarrierBottom2; // Segunda barrera inferior
    sf::Sprite mEnemy;                  // Sprite del enemigo
    sf::RectangleShape mGoal;            // Meta final del juego

    sf::Texture mBackgroundTexture;     // Textura del fondo
    sf::Sprite mBackgroundSprite;       // Sprite del fondo

    sf::Texture mEnemyTexture;          // Textura del enemigo

    float mEnemySpeed;                  // Velocidad del enemigo
    bool mEnemyMovingUp;                // Dirección del movimiento del enemigo
    float mEnemyMovementAmount;         // Distancia a la que el enemigo se mueve hacia arriba
    float mEnemyInitialY;               // Posición Y inicial del enemigo
};

#endif // GAME_H