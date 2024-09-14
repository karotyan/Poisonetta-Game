#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Label
{
private:
    sf::Sprite buttonSprite;
public:

    Label(sf::Texture& buttonTexture);
  
    sf::Sprite& getObjectSprite();
};
