#include "Player.h"


     void Player:: centerShapeOrigign() // Added centring of gun
    {
        objectSprite.setOrigin(objectSprite.getLocalBounds().width / 2, objectSprite.getLocalBounds().height / 2);
        hitbox.setOrigin(hitbox.getLocalBounds().width / 2, hitbox.getLocalBounds().height / 2);
        gunSprite.setOrigin(gunSprite.getLocalBounds().width / 2, gunSprite.getLocalBounds().height / 2);
    }

    void Player::gunInput(sf::RenderWindow& window)
    {
        mousePosition = sf::Mouse::getPosition(window);

    }

    void Player::produceBullet(sf::Texture& texture, sf::Sound& playerShootSound)
    {
        if ((timeBetweenShoots.getElapsedTime() >= shootRate) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !shoot)
        {

            gunSprite.setTextureRect(sf::IntRect(251, 0, 281, 90)); // frame of gun with fire
            shoot = true;
            playerShootSound.play();
            bullets.push_back(std::make_unique<PlayerBullet>(texture, gunSprite.getRotation(), gunSprite.getPosition().x, gunSprite.getPosition().y, diraction));
            timeBetweenShoots.restart();

        }
        else if ((timeBetweenShoots.getElapsedTime() >= shootTime) && shoot)
        {
            gunSprite.setTextureRect(sf::IntRect(0, 0, 217, 90));   // frame of gun without fire
            shoot = false;
        }

    }


    Player::Player(sf::Texture& texture, sf::Texture& guntexture)
    {


        dead = false;
        shoot = false;
        onPlatform = false;


        objectSprite.setTexture(texture);
        gunSprite.setTexture(guntexture);

        hitbox.setSize(sf::Vector2f(180, 180));
        gunSprite.setTextureRect(sf::IntRect(0, 0, 217, 90));


        standingPos = 1;
        runningPos = 1;
        runningPosMax = 4;
        standingPosMax = 2;
        healPoints = 5;
        objectSprite.setTextureRect(sf::IntRect(0, 0, 242, 243));

        centerShapeOrigign();

        dx = 0;
        dy = 0;

        speedscale = 900;

        shootRate = sf::seconds(0.2);
        shootTime = sf::seconds(0.1);
        standingShot = sf::seconds(0.3);
        runningShot = sf::seconds(0.15);
        jumpRate = sf::seconds(0.5);
        damageRate = sf::seconds(0.5);

        timeBetweenShoots.restart();
        standingAnimation.restart();
        runningAnimation.restart();
        timeAfterJump.restart();
        timeAfterDamage.restart();


        jumpVelocity = -1200.0f;
        verticalVelocity = 0;
        gravity = 1500.0f;

        objectSprite.setPosition(960, 400);


    }

    void Player::input(sf::FloatRect speedRect, sf::RenderWindow& window)
    {
        /*
            !!!ATTENTION!!!

        speedRect - is used as 4 different floats, needed to get some info

        In This situation, it translates pressed buttons from game

        WIDTH -> D
        LEFT -> A
        TOP -> W
        HEIGHT - > S

        each field might be 0 or 1 means not pressed or pressed
        */



        dx = speedRect.width - speedRect.left;

        dy = speedRect.top;

        isMooving = dx;

        gunInput(window);


    }

    void Player::updateJump(sf::Sound  &jumpSound, float deltaTime)
    {

        // gravity calculations
        verticalVelocity += gravity*deltaTime;
       

        // 710-730 is floor position for player
        if (dy && timeAfterJump.getElapsedTime() >= jumpRate && (objectSprite.getPosition().y >= 710 || onPlatform))
        {
            verticalVelocity = jumpVelocity;
            timeAfterJump.restart();
            isJumping = true;
            jumpSound.play();
        }
        else
        {
            if (objectSprite.getPosition().y >= 730 || (onPlatform) && verticalVelocity > 0)
            {
                isJumping = false;
                verticalVelocity = 0;
            }
        }
    }

    void Player::update(float deltaTime, sf::RenderWindow& window)
    {




        // Next block of code is swithcing player frames depending on timers and his movement
        if (isJumping)
        {
            objectSprite.setTextureRect(sf::IntRect(0, 252, 220, 243)); // frame where front leg is up
        }
        else
        {
            if (isMooving)
            {
                if (runningAnimation.getElapsedTime() >= runningShot)
                {
                    switch (runningPos)
                    {
                    case 1:

                        runningPos = 2;
                        objectSprite.setTextureRect(sf::IntRect(0, 252, 220, 243)); // frame where back leg is up
                        break;

                    case 2:

                        runningPos = 3;
                        objectSprite.setTextureRect(sf::IntRect(243, 0, 231, 243)); // frame standing
                        break;

                    case 3:

                        runningPos = 4;
                        objectSprite.setTextureRect(sf::IntRect(232, 262, 230, 243)); // frame where front leg is up
                        break;

                    case 4:

                        runningPos = 1;
                        objectSprite.setTextureRect(sf::IntRect(243, 0, 231, 243)); // frame standing
                        break;



                    }
                    runningAnimation.restart();
                }


            }
            else
                if (standingAnimation.getElapsedTime() >= standingShot)
                {
                    if (standingPos == 1)
                    {
                        standingPos = 2;
                        objectSprite.setTextureRect(sf::IntRect(243, 0, 231, 243)); // standing frame 2 (a bit down)
                    }
                    else if (standingPos == 2)
                    {
                        standingPos = 1;
                        objectSprite.setTextureRect(sf::IntRect(0, 0, 242, 243)); // standing frame 1
                    }
                    standingAnimation.restart();

                }


        }

        centerShapeOrigign();


        sf::Vector2f offset{ dx * deltaTime * (speedscale)-350 * deltaTime, verticalVelocity * deltaTime };
        objectSprite.move(offset);

        hitbox.setPosition(objectSprite.getPosition());

        // Scale to look in diraction of mouse
        if (mousePosition.x < objectSprite.getPosition().x)
        {
            diraction = -1;
            objectSprite.setScale(-1.0f, 1.0f);
            gunSprite.setScale(-1.0f, 1.0f);
        }
        else
        {
            diraction = 1;
            objectSprite.setScale(1.0f, 1.0f);
            gunSprite.setScale(1.0f, 1.0f);
        }


        // Next blocks update all the bullets in vector and clear dead bullets
        size_t deadbul = -1;

        for (size_t i = 0; i < bullets.size(); i++)
        {
            if (bullets[i]->getDead())
            {
                deadbul = i;
            }

        }

        if (deadbul != -1)
        {
            bullets.erase(bullets.begin() + deadbul);
        }

        for (auto& i : bullets)
            i->update(deltaTime, window);



        if (objectSprite.getPosition().x > maxX || objectSprite.getPosition().x < minX)
            die();

    }


    void Player::gunUpdate(sf::Texture& bullettexture, sf:: Sound& playerShootSound)
    {

        sf::Vector2f offset(60, 70); // random numbers of gun offset
        offset.x *= diraction;
        gunSprite.setPosition(offset + objectSprite.getPosition());

        float rotation;

        float deltax = fabs(mousePosition.x - gunSprite.getPosition().x);
        float deltay = mousePosition.y - gunSprite.getPosition().y;

        rotation = 180 * atan(deltay / deltax) / PI * diraction;


        gunSprite.setRotation(rotation);

        produceBullet(bullettexture, playerShootSound); //produces bullet if plessed LMB and timer enables


    }

    void Player::draw(sf::RenderWindow& window)
    {
        window.draw(objectSprite);
        window.draw(gunSprite);

        for (auto& i : bullets)
        {
            window.draw(i->getObjectSprite());
        }
    }



    sf::FloatRect Player::getCaracterInfo() // used by enemies to set mooving diraction
    {
        return objectSprite.getGlobalBounds();
    }


    std::vector<std::unique_ptr<PlayerBullet>>& Player::getBullets()
    {
        return bullets;
    }

    void Player::getShot(sf::Sound &damageSound)
    {
        if (timeAfterDamage.getElapsedTime() > damageRate)
        {
            healPoints--;
            timeAfterDamage.restart();
            damageSound.play();

        }
        if (healPoints <= 0)
        {
            die();
        }
    }

    void Player::setOnplatform(bool input)
    {
        onPlatform = input;
    }
