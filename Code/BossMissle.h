#pragma once
#include "Object.h"

class BossMissle : public Object
    // bullet, created by EnemyBoss, flies in a diraction of player`s coords at the time of creation, flies thru everything except player
{
private:

    const float minTop = -100, maxTop = 1180, minLeft = -100, maxLeft = 2020;

public:

    BossMissle(sf::Texture& objectTexture, float goalX, float goalY, float currentX, float currentY);
   
    virtual void input(sf::FloatRect speedRect, sf::RenderWindow& window);
   

    virtual void update(float deltaTime, sf::RenderWindow& window);
   
};