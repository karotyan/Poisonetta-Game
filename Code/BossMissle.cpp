#include "BossMissle.h"



     BossMissle::BossMissle(sf::Texture& objectTexture, float goalX, float goalY, float currentX, float currentY)
    {
        speedscale = 1200;
        objectSprite.setTexture(objectTexture);
        centerShapeOrigign();

        objectSprite.move(sf::Vector2f(currentX, currentY));
        float way = sqrt(pow((goalX - objectSprite.getPosition().x), 2) + pow((goalY - objectSprite.getPosition().y), 2));
        objectSprite.setScale(0.7, 0.7);

        dx = (goalX - objectSprite.getPosition().x) / way;
        dy = (goalY - objectSprite.getPosition().y) / way;
        dead = false;
    }

     void  BossMissle::input(sf::FloatRect speedRect, sf::RenderWindow& window)
    {
    }

     void  BossMissle::update(float deltaTime, sf::RenderWindow& window)
    {


        objectSprite.rotate(500 * dx * deltaTime / fabs(dx)); // added rotation animation
        objectSprite.move(dx * speedscale * deltaTime, dy * speedscale * deltaTime);

        if (!dead)
        {

            if (objectSprite.getGlobalBounds().left < minLeft) die();
            else if (objectSprite.getGlobalBounds().left > maxLeft) die();
            else if (objectSprite.getGlobalBounds().top < minTop) die();
            else if (objectSprite.getGlobalBounds().top > maxTop) die();

        }
    }
