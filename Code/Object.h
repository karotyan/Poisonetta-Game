#pragma once

const double PI = 3.141592653589793238;

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <ctime> 
#include <vector>
#include <cmath>

class Object // parent object for objects that interact with other
{
protected:

    sf::Sprite objectSprite;
    sf::RectangleShape hitbox; // Invisible rectangle, reacts for intersection with bullets/enemies !!! USED NOT EVERYWHERE

    bool dead; //trigger for objectProducer to delete object


    float dx; //normalized vector of horizontal movement
    float dy; // normalized vector of vertical movement

    float speedscale; // scale of horizontal movement



    virtual void centerShapeOrigign();
        // centers origin of object`s hitbox and sprite


public:

    virtual void input(sf::FloatRect speedRect, sf::RenderWindow& window) = 0;

    virtual void update(float deltaTime, sf::RenderWindow& window) = 0;

    ////////////////////////////////

    /*Getters of object`s sprite and hitbox positions, required
    for checking intersection with other objects*/

    sf::Sprite& getObjectSprite();
 
    sf::RectangleShape& getObjectHitbox();
 

    void die();
 
    bool getDead();

};

