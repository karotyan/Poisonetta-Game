#include "Object.h"


     void Object:: centerShapeOrigign()
        // centers origin of object`s hitbox and sprite
    {
        objectSprite.setOrigin(objectSprite.getLocalBounds().width / 2, objectSprite.getLocalBounds().height / 2);
        hitbox.setOrigin(hitbox.getLocalBounds().width / 2, hitbox.getLocalBounds().height / 2);
    }


    /*Getters of object`s sprite and hitbox positions, required
    for checking intersection with other objects*/

    sf::Sprite&  Object:: getObjectSprite()
    {
        return objectSprite;
    }

    sf::RectangleShape& Object::getObjectHitbox()
    {
        return hitbox;
    }

    ////////////////////////////////

    void  Object::die()
    {
        dead = true;
    }

    bool  Object::getDead()
    {
        return dead;
    }
