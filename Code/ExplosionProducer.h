#pragma once
#include "Explosion.h"

class ExplosionProducer
{
private:
    std::vector<std::unique_ptr<Explosion>> explosions;

    sf::Texture explosion1Texture;
    sf::Texture explosion2Texture;
    sf::Texture explosion3Texture;

public:

    ExplosionProducer();
 

    void update(float deltaTime, sf::RenderWindow& window);
   

    
    void addExplosion(sf::RenderWindow& window, float x, float y, bool isSmall, bool isVertical);
   


    void draw(sf::RenderWindow& window);
    

};
