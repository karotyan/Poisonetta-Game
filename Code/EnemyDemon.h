#pragma once
#include "Object.h"

class EnemyDemon : public Object
    // object that moves by dy, can hurt player
{
private:
    sf::Clock runningAnimation; // Has frames for running
    sf::Time runningShot;

    int diraction;

    int runningPos;
    int runningPosMax;

    int healPoints;

public:

    EnemyDemon(sf::Texture& texture);
    

    virtual void input(sf::FloatRect speedRect, sf::RenderWindow& window);
   

    virtual void update(float deltaTime, sf::RenderWindow& window);  //frame update
    

    void getShot();
    

    void draw(sf::RenderWindow& window);
    
};


