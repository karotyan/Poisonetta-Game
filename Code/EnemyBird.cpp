#include "EnemyBird.h"


    EnemyBird::EnemyBird(sf::Texture& objectTexture)
    {

        objectSprite.setTexture(objectTexture);

        hitbox.setSize(sf::Vector2f(100, 180));


        runningPos = 1;
        runningPosMax = 4;
        objectSprite.setTextureRect(sf::IntRect(135, 0, 131, 235));


        centerShapeOrigign();
        hitbox.setPosition(sf::Vector2f(2000, 200));
        objectSprite.setPosition(sf::Vector2f(2000, 200));


        healPoints = 2;

        dx = 0;
        dy = 0;
        speedscale = 500;

        runningShot = sf::seconds(0.15);
        runningAnimation.restart();

        timeshot = sf::seconds(1.0);
        timeBetweenShoots.restart();


    }

     void EnemyBird::input(sf::FloatRect speedRect, sf::RenderWindow& window)
        // speedRect contains player`s global bounds
    {
        float distance = objectSprite.getGlobalBounds().left - speedRect.left;

        if (distance > 50)
        {
            dx = -1;
            diraction = -1;
            objectSprite.setScale(-1.0f, 1.0f);
        }
        else if (distance < -50)
        {
            dx = 1;
            diraction = 1;
            objectSprite.setScale(1.0f, 1.0f);
        }
        else dx = 0;

    }

     void EnemyBird::update(float deltaTime, sf::RenderWindow& window)
    {

        if (runningAnimation.getElapsedTime() >= runningShot)
        {
            switch (runningPos)
            {
            case 1:

                runningPos = 2;
                objectSprite.setTextureRect(sf::IntRect(13, 0, 275, 203));
                break;

            case 2:

                runningPos = 3;
                objectSprite.setTextureRect(sf::IntRect(280, 0, 275, 203));
                break;

            case 3:

                runningPos = 4;
                objectSprite.setTextureRect(sf::IntRect(550, 0, 275, 203));
                break;

            case 4:

                runningPos = 1;
                objectSprite.setTextureRect(sf::IntRect(280, 0, 275, 203));
                break;



            }
            runningAnimation.restart();

        }



        centerShapeOrigign();

        sf::Vector2f offset{ dx * deltaTime * speedscale - 350 * deltaTime, 0 };
        objectSprite.move(offset);

        hitbox.setPosition(objectSprite.getPosition());


        size_t deadbul = -1;

        for (size_t i = 0; i < bombs.size(); i++)
        {
            if (bombs[i]->getDead())
            {
                deadbul = i;
            }

        }

        if (deadbul != -1)
        {
            bombs.erase(bombs.begin() + deadbul);
        }


        for (auto& i : bombs)
            i->update(deltaTime, window);

    }

     void EnemyBird::updateBomb(sf::Texture& bombTexture, sf::Sound &explosionSound)
    {

        size_t deadbul = -1;

        for (size_t i = 0; i < bombs.size(); i++)
        {
            if (bombs[i]->getDead())
            {
                deadbul = i;
            }

        }

        if (deadbul != -1)
        {
            bombs.erase(bombs.begin() + deadbul);
            explosionSound.play();
        }


        if ((timeBetweenShoots.getElapsedTime() >= timeshot))
        {


            bombs.push_back(std::make_unique<BirdBomb>(bombTexture, objectSprite.getPosition().x, objectSprite.getPosition().y, diraction));


            timeBetweenShoots.restart();

        }
    }


    void EnemyBird::draw(sf::RenderWindow& window)
    {
        window.draw(objectSprite);

        for (auto& i : bombs)
        {
            window.draw(i->getObjectSprite());

        }
    }

    void EnemyBird::getShot()
    {
        healPoints--;
        if (healPoints <= 0)
        {
            die();
        }
    }

    std::vector<std::unique_ptr<BirdBomb>>& EnemyBird::getBombs()
    {
        return bombs;
    }
