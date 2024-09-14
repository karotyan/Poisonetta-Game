#include "Platform.h"


    Platform::Platform(sf::Texture& texture)
    {
        dead = false;
        dx = -1;
        dy = 0;


        speedscale = 350;

        objectSprite.setTexture(texture);
        centerShapeOrigign();
        objectSprite.setPosition(2500, 450);


    }

    void  Platform::input(sf::FloatRect speedRect, sf::RenderWindow& window)
    {

    }


    void  Platform::update(float deltaTime, sf::RenderWindow& window)
    {

        sf::Vector2f offset{ dx * deltaTime * speedscale, dy * deltaTime * speedscale };

        objectSprite.move(offset);

        if (!dead)
        {

            if (objectSprite.getGlobalBounds().left < minLeft) die();

        }

    }

