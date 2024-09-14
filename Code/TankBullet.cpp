#include "TankBullet.h"


    TankBullet::TankBullet(sf::Texture& objectTexture, float startX, float startY)
    {
        dead = false;
        dx = -1;
        dy = 0;

        speedscale = 1500;

        objectSprite.setTexture(objectTexture);
        objectSprite.setScale(sf::Vector2f(-1, 1.0));
        centerShapeOrigign();
        objectSprite.setPosition(startX + 100 * -1, startY - 20);

    }

    void TankBullet ::input(sf::FloatRect speedRect, sf::RenderWindow& window)
    {

    }


    void TankBullet::update(float deltaTime, sf::RenderWindow& window)
    {

        sf::Vector2f offset{ dx * deltaTime * speedscale, dy * deltaTime * speedscale };

        objectSprite.move(offset);


        if (!dead)
        {

            if (objectSprite.getGlobalBounds().left > maxLeft) die();
            else if (objectSprite.getGlobalBounds().left < minLeft) die();

        }

    }

