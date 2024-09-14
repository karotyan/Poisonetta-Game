#pragma once
#include "Object.h"
#include "TankBullet.h"


class EnemyTank : public Object
{


private:

    sf::Clock timeBetweenShoots;
    sf::Time shootTime;
    sf::Time timeshot;

    int diraction;

    int position;


    std::vector<std::unique_ptr<TankBullet>> bullets;

    bool shoot;

public:

    EnemyTank(sf::Texture& objectTexture);
    

    virtual void input(sf::FloatRect speedRect, sf::RenderWindow& window);
   

    void bulletUpdate(sf::Texture& bulletTexture, sf::Sound& tankShotSound);
   

    virtual void update(float deltaTime, sf::RenderWindow& window);


    void draw(sf::RenderWindow& window);
    

    void SetNewPosition();
    

    std::vector<std::unique_ptr<TankBullet>>& getBullets();
    

};

