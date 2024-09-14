#pragma once
#include "Object.h"



class PlayerBullet : public Object
    // Bullet that is produced by Player
    //  hits enemies,
    //  moves in dx and dy
{
private:

    // if bullet is out of these coordinates, it dies
    const float minTop = -100, maxTop = 1180, minLeft = -100, maxLeft = 2020;


public:

    PlayerBullet(sf::Texture& texture, float angle, float startX, float startY, int diraction);
   

   virtual void input(sf::FloatRect speedRect, sf::RenderWindow& window);
  

    virtual void update(float deltaTime, sf::RenderWindow& window);
   

};

