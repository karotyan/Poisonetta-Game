#include "BirdBomb.h"


    BirdBomb::BirdBomb(sf::Texture& objectTexture, float startX, float startY, int diraction)
    {
        dead = false;
        dx = 0;
        dy = 1;

        this->diraction = diraction;


        speedscale = 1000;
        rotation = 120;

        objectSprite.setTexture(objectTexture);
        objectSprite.setScale(sf::Vector2f(1.0 * diraction, 1.0));
        centerShapeOrigign();
        objectSprite.setPosition(startX - 30 * diraction, startY + 100);



    }

    void BirdBomb::input(sf::FloatRect speedRect, sf::RenderWindow& window)
    {
    }
   


    void BirdBomb::update(float deltaTime, sf::RenderWindow& window)
    {

        sf::Vector2f offset{ dx * deltaTime * speedscale, dy * deltaTime * speedscale };

        objectSprite.move(offset);
        objectSprite.rotate(70 * diraction * deltaTime);

    }

