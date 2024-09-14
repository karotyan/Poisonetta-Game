#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Explosion
    // class of explosion animation, swithces frames and then dies
{
private:

    sf::Sprite sprite;

    int i, j, sizX, sizY;       // need to move in spriteSheet of explosions
    bool dead;

    sf::Clock timeAfterRate;    // Timer to switch frames
    sf::Time framerate;

    void centerShapeOrigign();
   

public:

    Explosion(sf::Texture& texture, int x, int y, bool isbullet);
   

    void update(float deltaTime);
    

    sf::Sprite getObjectSprite();
    

    bool getDead();
   

};
