#include "EnemyTank.h"



    EnemyTank::EnemyTank(sf::Texture& objectTexture)
    {

        objectSprite.setTexture(objectTexture);
        objectSprite.setTextureRect(sf::IntRect(0, 0, 371, 155));
        hitbox.setSize(sf::Vector2f(250, 100));

        centerShapeOrigign();




        objectSprite.setPosition(-350, -200);


        dead = false;

        dx = -1;
        dy = 0;
        speedscale = 350;
        shoot = false;

        objectSprite.setScale(-1, 1);



        timeshot = sf::seconds(1.0);
        shootTime = sf::seconds(0.1);
        timeBetweenShoots.restart();


    }

    void EnemyTank::input(sf::FloatRect speedRect, sf::RenderWindow& window)
    {
        float distance = objectSprite.getGlobalBounds().left - speedRect.left;
        // std::cout << distance << std::endl;
      //  if (distance > 50)
        {
            dx = -1;
            diraction = -1;
            objectSprite.setScale(-1.0f, 1.0f);
        }
        // else dx = 0;


    }

    void EnemyTank::bulletUpdate(sf::Texture& bulletTexture, sf::Sound & tankShotSound)
    {
        if ((timeBetweenShoots.getElapsedTime() >= timeshot) && !shoot)
        {

            objectSprite.setTextureRect(sf::IntRect(365, 0, 380, 152));
            tankShotSound.play();
            shoot = true;
            bullets.push_back(std::make_unique<TankBullet>(bulletTexture, objectSprite.getPosition().x - 100, objectSprite.getPosition().y - 20));
            ////////////////////////// 
            timeBetweenShoots.restart();

        }
        else if ((timeBetweenShoots.getElapsedTime() >= shootTime) && shoot)
        {
            objectSprite.setTextureRect(sf::IntRect(0, 0, 371, 152));
            shoot = false;
        }
    }

    void  EnemyTank:: update(float deltaTime, sf::RenderWindow& window)
    {



        centerShapeOrigign();

        sf::Vector2f offset{ dx * deltaTime * speedscale, 0 };
        objectSprite.move(offset);
        hitbox.setPosition(objectSprite.getPosition());


        size_t deadbul = -1;

        for (size_t i = 0; i < bullets.size(); i++)
        {
            if (bullets[i]->getDead())
            {
                deadbul = i;
            }

        }

        if (deadbul != -1)
        {
            bullets.erase(bullets.begin() + deadbul);
        }


        for (auto& i : bullets)
            i->update(deltaTime, window);

    }


    void EnemyTank::draw(sf::RenderWindow& window)
    {
        window.draw(objectSprite);

        for (auto& i : bullets)
        {
            window.draw(i->getObjectSprite());

        }
    }

    void EnemyTank::SetNewPosition()
    {
        position = rand() % 2;

        if (position)
            objectSprite.setPosition(sf::Vector2f(2400, 750));
        else  objectSprite.setPosition(sf::Vector2f(2400, 330));

        hitbox.setPosition(objectSprite.getPosition());
    }

    std::vector<std::unique_ptr<TankBullet>>& EnemyTank::getBullets()
    {
        return bullets;
    }

