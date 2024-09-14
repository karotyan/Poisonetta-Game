#pragma once
#include "Object.h"

class Platform : public Object
    // floating island, player can cover under it from bombs or jump on it from demons
    //tank can spawn on it
{
private:
    const float  minLeft = -1000;

public:

    Platform(sf::Texture& texture);
   

    void input(sf::FloatRect speedRect, sf::RenderWindow& window);
   


    void update(float deltaTime, sf::RenderWindow& window);
    

};

