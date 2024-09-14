#pragma once
#include "Object.h"
#include "Bossmissle.h"


class EnemyBoss : public Object
{
private:


    int goalX;
    int goalY;

    bool isMoving;
    sf::Clock timeStanding;
    sf::Time standRate;

    int runningPos;
    int diraction;
    int numOfShots;

    int healPoints;


    std::vector<std::unique_ptr<BossMissle>> missles;

    sf::Clock runningAnimation;
    sf::Time runningShot;

public:

    EnemyBoss(sf::Texture& objectTexture);
    

    virtual void input(sf::FloatRect speedRect, sf::RenderWindow& window);
   

    virtual void update(float deltaTime, sf::RenderWindow& window);
   

    void updateAll(float deltaTime, sf::RenderWindow& window, sf::Texture& missleTexture, sf::Vector2f playerCoords, sf::Sound &missleSound);
       

    void getShot();
    

    void draw(sf::RenderWindow& window);
   

    std::vector<std::unique_ptr<BossMissle>>& getBullets();
    

};

