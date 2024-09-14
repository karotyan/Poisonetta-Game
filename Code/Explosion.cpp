#include "Explosion.h"



   void Explosion::centerShapeOrigign()
    {
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    }



   Explosion::Explosion(sf::Texture& texture, int x, int y, bool isbullet)
    {
        framerate = sf::milliseconds(7);
        timeAfterRate.restart();
        dead = false;
        i = 0;
        j = 0;
        sizX = 100;
        sizY = 100;

        // if explosion is not from bullet, it is bigger 

        if (!isbullet)
            sprite.setScale(3, 3);
        else sprite.setScale(1.5, 1.5);


        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect{ i, j, sizX, sizY });

        sprite.setPosition(x, y);
        centerShapeOrigign();


    }

    void Explosion::update(float deltaTime)
    {
        if (!dead && timeAfterRate.getElapsedTime() > framerate)
        {
            timeAfterRate.restart();
            i++;
            if (i > 9)
            {
                i = 0;
                j++;
                sprite.setTextureRect(sf::IntRect{ i * sizX, j * sizY, sizX, sizY });

            }

            centerShapeOrigign();

            if (j >= 4 && i >= 9)
            {
                dead = true;
            }
        }

        sprite.move(-350 * deltaTime, 0); // sprite moves with map
    }

    sf::Sprite Explosion::getObjectSprite()
    {
        return sprite;
    }

    bool Explosion::getDead()
    {
        return dead;
    }

