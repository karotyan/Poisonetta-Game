#pragma once

#include "Object.h"
#include "PlayerBullet.h"


class Player : public Object
    // controlled by player, using W A S D and Mouse Position + LMB
{
private:

    sf::Clock timeBetweenShoots;    // Time after last shot
    sf::Clock standingAnimation;    // Time after switching last standing frame
    sf::Clock runningAnimation;     // Time after switching last mooving frame

    sf::Time shootRate;             // Time between shots of player Gun
    sf::Time shootTime;             // Time of gun sprite with fire

    sf::Time standingShot;          // Framerate of standing position
    sf::Time runningShot;           // Framerate of mooving position

    bool shoot;                     // is true when gun sprite is on fire
    int diraction;                  // player mirror scale, depends on his and mouse position [-1 or 1]

    bool isMooving;                 // dx != 0, needed for swithcing frames
    bool isJumping;                 // dy != 0, needed for switching frames

    int standingPos;                // Number of current position (frame)
    int standingPosMax;             // Amount of different positions (frames)

    int runningPos;                 // Number of current position (frame)
    int runningPosMax;              // Amount of different positions (frames)

    sf::Sprite gunSprite;

    bool onPlatform;                // True whan it stands on platform

    /*
            There is no use of dy, because player works with gravitation
    */

    float jumpVelocity;     // when W is pressed, adds (in Oposite diraction) big speed
    float verticalVelocity; // player`s dy
    float gravity;          // permanently adds to player vertical speed

    int healPoints;

    const int maxX = 2500, minX = -500;     // If player leaves these borders, he will die

    sf::Vector2i mousePosition;         //keeps mouse X and Y


    sf::Time jumpRate;                  //  Player`s timer betwen jumps, so he can`t jump a lot of times in milliseconds and
    sf::Clock timeAfterJump;            //  fly to sky

    sf::Time damageRate;                // Timer after damage when player is invincible 
    sf::Clock timeAfterDamage;



    std::vector<std::unique_ptr<PlayerBullet>> bullets;     // Vector of player`s bullets

    virtual void centerShapeOrigign(); // Added centring of gun
   

    void gunInput(sf::RenderWindow& window);
   

    void produceBullet(sf::Texture& texture, sf::Sound& playerShootSound);
    


public:

    void updateJump(sf::Sound &jumpSound, float deltaTime);

    Player(sf::Texture& texture, sf::Texture& guntexture);
    


    virtual void input(sf::FloatRect speedRect, sf::RenderWindow& window);
   

    virtual void update(float deltaTime, sf::RenderWindow& window);
    


    void gunUpdate(sf::Texture& texture, sf::Sound &playerShootSound);
    

    void draw(sf::RenderWindow& window);
  



    sf::FloatRect getCaracterInfo(); // used by enemies to set mooving diraction
   


    std::vector<std::unique_ptr<PlayerBullet>>& getBullets();
 

    void getShot(sf::Sound &damageSound);


    void setOnplatform(bool input);

};

