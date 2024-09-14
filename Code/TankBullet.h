#pragma once
#include "Object.h"

class TankBullet : public Object
    // Bullets, produced by EnemyTank, move only in dx, die when hit player/out of screen
{
private:

    const float  maxLeft = 1920, minLeft = 0;

public:

    TankBullet(sf::Texture& objectTexture, float startX, float startY);
   

   virtual void input(sf::FloatRect speedRect, sf::RenderWindow& window);



   virtual void update(float deltaTime, sf::RenderWindow& window);
   

};

