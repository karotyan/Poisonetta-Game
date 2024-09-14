#include "PlayerBullet.h"


    PlayerBullet::PlayerBullet(sf::Texture& texture, float angle, float startX, float startY, int diraction)
    {
        dead = false;

        dx = cos(angle * PI / 180) * diraction;
        dy = sin(angle * PI / 180) * diraction;

        speedscale = 2000;

        objectSprite.setTexture(texture);

        objectSprite.setScale(sf::Vector2f(1.0 * diraction, 1.0)); // sets if bullets looks left or right

        centerShapeOrigign();

        objectSprite.setPosition(startX + 100 * dx, startY + 100 * dy); // spawns in 100 pixels from centre of gun

        objectSprite.rotate(angle);
    }
    
        void PlayerBullet::input(sf::FloatRect speedRect, sf::RenderWindow & window)
        {

        }

        void PlayerBullet::update(float deltaTime, sf::RenderWindow & window)
        {


            sf::Vector2f offset{ dx * deltaTime * speedscale, dy * deltaTime * speedscale };

            objectSprite.move(offset);


            if (!dead) //check if left the screen
            {

                if (objectSprite.getGlobalBounds().left < minLeft) die();
                else if (objectSprite.getGlobalBounds().left > maxLeft) die();
                else if (objectSprite.getGlobalBounds().top < minTop) die();
                else if (objectSprite.getGlobalBounds().top > maxTop) die();

            }


        }