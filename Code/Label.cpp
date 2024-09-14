#include "Label.h"

Label:: Label(sf::Texture& buttonTexture)
{


    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setScale(2, 2);
    buttonSprite.setOrigin(buttonSprite.getLocalBounds().width / 2, buttonSprite.getLocalBounds().height / 2);
    buttonSprite.setPosition(sf::Vector2f(960, 150));
}

sf::Sprite& Label::getObjectSprite()
{
    return buttonSprite;
}