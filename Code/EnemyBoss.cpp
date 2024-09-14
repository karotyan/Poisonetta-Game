#include "EnemyBoss.h"



    EnemyBoss:: EnemyBoss(sf::Texture& objectTexture)
    {

        runningPos = 1;
        objectSprite.setTexture(objectTexture);

        isMoving = true;
        hitbox.setSize(sf::Vector2f(100, 170));
        centerShapeOrigign();

        objectSprite.setPosition(2500, 400);



        speedscale = 500;

        healPoints = 50;

        standRate = sf::seconds(2.0);
        timeStanding.restart();

        runningAnimation.restart();
        runningShot = sf::seconds(0.3);






        goalX = std::rand() % 1520 + 200;
        goalY = std::rand() % 400 + 200;



        float way = sqrt(pow((goalX - objectSprite.getPosition().x), 2) + pow((goalY - objectSprite.getPosition().y), 2));





        dx = (goalX - objectSprite.getPosition().x) / way;
        dy = (goalY - objectSprite.getPosition().y) / way;




    }

    void  EnemyBoss:: input(sf::FloatRect speedRect, sf::RenderWindow& window)
    {
        float distance = objectSprite.getGlobalBounds().left - speedRect.left;
        // std::cout << distance << std::endl;

        objectSprite.setScale(-distance / fabs(distance), 1.0f);


    }

    void  EnemyBoss:: update(float deltaTime, sf::RenderWindow& window)
    {

        size_t deadbul = -1;

        for (size_t i = 0; i < missles.size(); i++)
        {
            if (missles[i]->getDead())
            {
                deadbul = i;
            }

        }

        if (deadbul != -1)
        {
            missles.erase(missles.begin() + deadbul);
        }


        for (auto& i : missles)
            i->update(deltaTime, window);

        if (runningAnimation.getElapsedTime() >= runningShot)
        {
            switch (runningPos)
            {
            case 1:

                runningPos = 2;
                objectSprite.setTextureRect(sf::IntRect(217, 0, 217, 267));
                break;

            case 2:

                runningPos = 1;
                objectSprite.setTextureRect(sf::IntRect(0, 0, 217, 267));
                break;



            }
            runningAnimation.restart();
            centerShapeOrigign();
            hitbox.setPosition(objectSprite.getPosition());
        }



    }

    void  EnemyBoss::updateAll(float deltaTime, sf::RenderWindow& window, sf::Texture& missleTexture, sf::Vector2f playerCoords, sf::Sound &missleSound)
    {
        // std::cout << fabs(objectSprite.getPosition().x - goalX )<< "\n";
        if (isMoving)
        {
            if (fabs(objectSprite.getPosition().x - goalX) < 10)
            {


                goalX = std::rand() % 1520 + 200;
                goalY = std::rand() % 400 + 200;
                timeStanding.restart();
                isMoving = false;
                numOfShots = 0;


                float way = sqrt(pow((goalX - objectSprite.getPosition().x), 2) + pow((goalY - objectSprite.getPosition().y), 2));



                dx = (goalX - objectSprite.getPosition().x) / way;
                dy = (goalY - objectSprite.getPosition().y) / way;




            }
            else
            {
                sf::Vector2f offset{ dx * deltaTime * speedscale, dy * deltaTime * speedscale };
                objectSprite.move(offset);
            }


        }
        else
        {
            for (int i = 0; i < 3; i++)
            {
                if (timeStanding.getElapsedTime() > sf::seconds(0.4 * i) && numOfShots <= i)
                {

                    missles.push_back(std::make_unique < BossMissle >(missleTexture, playerCoords.x, playerCoords.y, objectSprite.getPosition().x, objectSprite.getPosition().y));
                    numOfShots++;
                    missleSound.play();
                }
            }
            if (timeStanding.getElapsedTime() > standRate) isMoving = true;


        }
        update(deltaTime, window);
    }


    void  EnemyBoss::getShot()
    {
        healPoints--;
        if (healPoints <= 0) die();
    }

    void EnemyBoss::draw(sf::RenderWindow& window)
    {
        window.draw(objectSprite);
        for (auto& i : missles)
        {
            window.draw(i->getObjectSprite());

        }


    }

    std::vector<std::unique_ptr<BossMissle>>& EnemyBoss::getBullets()
    {
        return missles;
    }
