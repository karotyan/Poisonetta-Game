#include "EnemyDemon.h"



   EnemyDemon:: EnemyDemon(sf::Texture& texture)
    {
        dead = false;

        objectSprite.setTexture(texture);

        hitbox.setSize(sf::Vector2f(100, 150));
        centerShapeOrigign();


        runningPos = 1;
        runningPosMax = 4;
        objectSprite.setTextureRect(sf::IntRect(135, 0, 131, 235));


        dx = 0;
        dy = 0;
        speedscale = 500;

        runningShot = sf::seconds(0.15);
        runningAnimation.restart();
        objectSprite.setPosition(2000, 730);
        hitbox.setPosition(2000, 730);

        healPoints = 3;
    }

     void EnemyDemon::input(sf::FloatRect speedRect, sf::RenderWindow& window)
    {
        // speedRect here is player`s sprite global bounds

        float distance = objectSprite.getGlobalBounds().left - speedRect.left;

        if (distance > 50)
        {
            dx = -1;
            objectSprite.setScale(-1.0f, 1.0f);
        }
        else if (distance < -50)
        {
            dx = 1;
            objectSprite.setScale(1.0f, 1.0f);
        }
        else dx = 0;


    }

     void EnemyDemon::update(float deltaTime, sf::RenderWindow& window)  //frame update
    {

        if (dx != 0)
        {
            if (runningAnimation.getElapsedTime() >= runningShot)
            {
                switch (runningPos)
                {
                case 1:

                    runningPos = 2;
                    objectSprite.setTextureRect(sf::IntRect(0, 0, 135, 235));   // standing
                    break;

                case 2:

                    runningPos = 3;
                    objectSprite.setTextureRect(sf::IntRect(135, 0, 131, 235)); // front leg up
                    break;

                case 3:

                    runningPos = 4;
                    objectSprite.setTextureRect(sf::IntRect(0, 0, 135, 235)); // standing
                    break;

                case 4:

                    runningPos = 1;
                    objectSprite.setTextureRect(sf::IntRect(270, 0, 133, 235)); // back leg up
                    break;



                }
                runningAnimation.restart();
            }

        }
        else
        {
            objectSprite.setTextureRect(sf::IntRect(0, 0, 135, 235));   //standing
        }


        centerShapeOrigign();

        sf::Vector2f offset{ dx * deltaTime * speedscale - 350 * deltaTime, 0 };
        objectSprite.move(offset);

        hitbox.setPosition(objectSprite.getPosition());

    }

    void EnemyDemon::getShot()
    {
        healPoints--;
        if (healPoints <= 0)
        {
            die();
        }
    }

    void EnemyDemon::draw(sf::RenderWindow& window)
    {
        window.draw(objectSprite);

    }

