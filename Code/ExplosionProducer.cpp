#include "ExplosionProducer.h"



    ExplosionProducer::ExplosionProducer()
    {
        explosion1Texture.loadFromFile("Resources/bigbom.png");
        explosion2Texture.loadFromFile("Resources/smallbom.png");
        explosion3Texture.loadFromFile("Resources/verticalbom.png");
    }

    void ExplosionProducer::update(float deltaTime, sf::RenderWindow& window)
    {

        size_t deadbul = -1;

        for (size_t i = 0; i < explosions.size(); i++)
        {
            if (explosions[i]->getDead())
            {
                deadbul = i;
            }

        }

        if (deadbul != -1)
        {
            explosions.erase(explosions.begin() + deadbul);
        }


        for (auto& i : explosions)
            i->update(deltaTime);
    }

    // void addExplosion(int x, int y, bool isbullet)
    void ExplosionProducer::addExplosion(sf::RenderWindow& window, float x, float y, bool isSmall, bool isVertical)
    {
        if (isSmall)
            explosions.push_back(std::make_unique<Explosion>(explosion1Texture, x, y, isSmall));
        else
        {
            if (!isVertical) explosions.push_back(std::make_unique<Explosion>(explosion2Texture, x, y, isSmall));
            else  explosions.push_back(std::make_unique<Explosion>(explosion3Texture, x, y, isSmall));
        }

    }


    void ExplosionProducer::draw(sf::RenderWindow& window)
    {

        for (auto& i : explosions)
        {
            window.draw(i->getObjectSprite());

        }
    }
