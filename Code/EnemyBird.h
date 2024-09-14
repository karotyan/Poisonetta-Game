#pragma once
#include "Object.h"
#include "BirdBomb.h"

class EnemyBird : public Object
    // Object, follows player in dx, launches bomb after timer
{

private:
    sf::Clock runningAnimation; // has flying frames
    sf::Time runningShot;

    sf::Clock timeBetweenShoots;
    sf::Time timeshot;

    int diraction;

    int runningPos;
    int runningPosMax;

    int healPoints;

    std::vector<std::unique_ptr<BirdBomb>> bombs;

public:

    EnemyBird(sf::Texture& objectTexture);
    

    virtual void input(sf::FloatRect speedRect, sf::RenderWindow& window);
        // speedRect contains player`s global bounds
    

    virtual void update(float deltaTime, sf::RenderWindow& window);
    

    void updateBomb(sf::Texture& bombTexture, sf::Sound &explosionSound);
   


    void draw(sf::RenderWindow& window);
   

    void getShot();
    

    std::vector<std::unique_ptr<BirdBomb>>& getBombs();
   

};

