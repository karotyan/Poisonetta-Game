#pragma once
#include "Object.h"

class BirdBomb : public Object
    // missle, created by Bird Enemy moves only dy down, explodes touching player/platform/floor
{
private:

    float rotation; // for bomb animation to smoothly switch form horrizontal to vertical position
    float diraction;

public:

    BirdBomb(sf::Texture& objectTexture, float startX, float startY, int diraction);


    virtual void input(sf::FloatRect speedRect, sf::RenderWindow& window);
    

    virtual void update(float deltaTime, sf::RenderWindow& window);
  

};

