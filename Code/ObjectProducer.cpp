#include "ObjectProducer.h"


    ObjectProducer::ObjectProducer()

    {
        gameStep = 1;
        playerDied = false;

        menuMusic.setLoop(true);
        gameMusic.setLoop(true);
        menuMusic.openFromFile("Resources/menumusic.mp3");
        menuMusic.play();
        gameMusic.openFromFile("Resources/gamemusic.mp3");
        looseBuffer.loadFromFile("Resources/loosesound.wav");
        winBuffer.loadFromFile("Resources/winsound.wav");
        jumpBuffer.loadFromFile("Resources/jump.mp3");
        playerShootBuffer.loadFromFile("Resources/playershoot.mp3");
        damageBuffer.loadFromFile("Resources/getdamage.mp3");
        bossMissleBuffer.loadFromFile("Resources/missle.mp3");

        smallExplBuffer.loadFromFile("Resources/smallexplosion.wav");
        tankShotBuffer.loadFromFile("Resources/tankshot.mp3");
        bigExplBuffer.loadFromFile("Resources/bigexplosion.mp3");

        looseSound.setBuffer(looseBuffer);
        winSound.setBuffer(winBuffer);
        jumpSound.setBuffer(jumpBuffer);
        playerShootSound.setBuffer(playerShootBuffer);
        damageSound.setBuffer(damageBuffer);
        smallExplSound.setBuffer(smallExplBuffer);
        tankShotSound.setBuffer(tankShotBuffer);
        bossMissleSound.setBuffer(bossMissleBuffer);
        bigExplSound.setBuffer(bigExplBuffer);

        ///
        tankShotSound.setVolume(50);
        menuMusic.setVolume(30);
        gameMusic.setVolume(30);
        jumpSound.setVolume(50);
        ///

        playerTexture.loadFromFile("Resources/poisonettastand.png");
        gunTexture.loadFromFile("Resources/gun.png");
        bulletTexture.loadFromFile("Resources/playerbullet.png");
        platformTexture.loadFromFile("Resources/platform.png");
        demonTexture.loadFromFile("Resources/enemy.png");
        birdTexture.loadFromFile("Resources/birdo.png");
        bombTexture.loadFromFile("Resources/bimba.png");
        tankTexture.loadFromFile("Resources/tank.png");
        tankBulletTexture.loadFromFile("Resources/tankbullet.png");
        bossTexture.loadFromFile("Resources/boss.png");
        missleTexture.loadFromFile("Resources/bossmissle.png");

        bgSkyTexture.loadFromFile("Resources/BGsky.png");
        bgSkySprite.setTexture(bgSkyTexture);

        bgGroundTexture.loadFromFile("Resources/BGground.png");
        bgGroundSprite.setTexture(bgGroundTexture);

        buttonTexture.loadFromFile("Resources/startbutton.png");

        winTexture.loadFromFile("Resources/won.png");
        looseTexture.loadFromFile("Resources/lost.png");


        stepTwo = sf::seconds(30);

        player = new Player(playerTexture, gunTexture);
        tank = new EnemyTank(tankTexture);
        bossin = new EnemyBoss(bossTexture);
        startButton = new Label(buttonTexture);
        wintext = new Label(winTexture);
        loosetext = new Label(looseTexture);

        platformRate = sf::seconds(5);
        timeAfterPlatform.restart();

        demonRate = sf::seconds(4);
        timeAfterDemon.restart();

        birdRate = sf::seconds(7);
        timeAfterBird.restart();

        tankRate = sf::seconds(10);
        timeAfterTank.restart();
    }


    void ObjectProducer::updatePlayerShots(sf::RenderWindow& window)
    {
        for (auto& i : player->getBullets())
        {
            for (auto& j : demons)
            {
                if (j->getObjectHitbox().getGlobalBounds().intersects(i->getObjectSprite().getGlobalBounds()))
                {
                    j->getShot();
                    i->die();
                    smallExplSound.play();
                    expProducer.addExplosion(window, i->getObjectSprite().getPosition().x, i->getObjectSprite().getPosition().y, true, false);

                }
            }
            for (auto& j : birds)
            {
                if (j->getObjectHitbox().getGlobalBounds().intersects(i->getObjectSprite().getGlobalBounds()))
                {
                    j->getShot();
                    i->die();
                    smallExplSound.play();
                    expProducer.addExplosion(window, i->getObjectSprite().getPosition().x, i->getObjectSprite().getPosition().y, true, false);

                }
            }

            if (tank!= nullptr)
            if (tank->getObjectHitbox().getGlobalBounds().intersects(i->getObjectSprite().getGlobalBounds()))
            {
                i->die();
                smallExplSound.play();
                expProducer.addExplosion(window, i->getObjectSprite().getPosition().x, i->getObjectSprite().getPosition().y, true, false);
            }

            if(bossin!=nullptr)
            if (bossin->getObjectHitbox().getGlobalBounds().intersects(i->getObjectSprite().getGlobalBounds()))
            {
                i->die();
                smallExplSound.play();
                bossin->getShot();
                expProducer.addExplosion(window, i->getObjectSprite().getPosition().x, i->getObjectSprite().getPosition().y, true, false);
            }
        }
        if (player != nullptr)
        {
            for (auto& j : demons)
            {
                if (j->getObjectHitbox().getGlobalBounds().intersects(player->getObjectHitbox().getGlobalBounds()))
                {
                    player->getShot(damageSound);
                  //  producer1.addExplosion(window, player->getObjectSprite().getPosition().x, player ->getObjectSprite().getPosition().y, true, false);

                }
            }
            for (auto& j : birds)
            {
                for (auto& i : j->getBombs())
                {
                    if (i->getObjectSprite().getGlobalBounds().intersects(player->getObjectHitbox().getGlobalBounds()))
                    {
                        player->getShot(damageSound);
                        i->die();
                        expProducer.addExplosion(window, player->getObjectSprite().getPosition().x, player->getObjectSprite().getPosition().y, false, true);
 
                    }
                }
            }
                    if(bossin!= nullptr)
                    for (auto& i : bossin->getBullets())
                    {
                        if (i->getObjectSprite().getGlobalBounds().intersects(player->getObjectHitbox().getGlobalBounds()))
                        {
                            player->getShot(damageSound);
                            i->die();
                            expProducer.addExplosion(window, player->getObjectSprite().getPosition().x, player->getObjectSprite().getPosition().y, true, false);

                        }
                    }

                    for (auto& i : tank->getBullets())
                    {
                        if (i->getObjectSprite().getGlobalBounds().intersects(player->getObjectHitbox().getGlobalBounds()))
                        {
                            player->getShot(damageSound);
                            i->die();
                            expProducer.addExplosion(window, player->getObjectSprite().getPosition().x, player->getObjectSprite().getPosition().y, true, false);
                            smallExplSound.play();
                        }
                    }


        }


        for (auto& i : birds)
        {
            for (auto& j : i->getBombs())
            {
                for (auto& k : platforms)
                {
                    if (j->getObjectSprite().getGlobalBounds().intersects(k->getObjectSprite().getGlobalBounds()))
                    {
                        j->die();
                        expProducer.addExplosion(window, j->getObjectSprite().getPosition().x, j->getObjectSprite().getPosition().y + 50, false, true);
                    }
                }

                if (j->getObjectSprite().getPosition().y > 750)
                {
                    j->die();
                    expProducer.addExplosion(window, j->getObjectSprite().getPosition().x, j->getObjectSprite().getPosition().y + 50, false, true);
                }



            }
        }


    }

    void ObjectProducer::updateBoss(sf::RenderWindow& window)
    {
        if(bossin != nullptr)
            if (bossin->getDead())
            {
                expProducer.addExplosion(window, bossin->getObjectSprite().getPosition().x, bossin->getObjectSprite().getPosition().y, false, false);
                bigExplSound.play();
                delete bossin;
                bossin = nullptr;
            }

    }

    void ObjectProducer::input(sf::FloatRect speedRect, sf::RenderWindow& window)
    {

        for (auto& i : demons)
        {
            i->input(player->getObjectSprite().getGlobalBounds(), window);
        }

        for (auto& i : birds)
        {
            i->input(player->getObjectSprite().getGlobalBounds(), window);
        }
        if (bossin != nullptr)
        bossin->input(player->getObjectSprite().getGlobalBounds(), window);
    }

    void ObjectProducer::playerInput(sf::FloatRect speedRect, sf::RenderWindow& window)
    {
        player->input(speedRect, window);
    }

    void ObjectProducer::update(float deltaTime, sf::RenderWindow& window)
    {
        if (!playerDied)
        {
            if (player != nullptr)
            {
                player->updateJump(jumpSound, deltaTime);
                player->update(deltaTime, window);
                player->gunUpdate(bulletTexture, playerShootSound);
                updatePlayerShots(window);

            }
        }
        switch (gameStep)
        {
        case(1):
        {
            timeAfterPlatform.restart();


            timeAfterDemon.restart();


            timeAfterBird.restart();


            timeAfterTank.restart();

            backGroundUpdate(deltaTime);

            updatePlatforms(deltaTime, window);
            updateDemons(deltaTime, window);
            updateBirds(deltaTime, window);
            if (tank != nullptr);
            updateTank(deltaTime, window);


            


            expProducer.update(deltaTime, window);

            for (auto& i : player->getBullets())
            {
                if (i->getObjectSprite().getGlobalBounds().intersects(startButton->getObjectSprite().getGlobalBounds()))
                {
                    gameStep++;
                    timeAfterstepTwo.restart();
                    i->die();
                    expProducer.addExplosion(window, startButton->getObjectSprite().getPosition().x, startButton->getObjectSprite().getPosition().y, false, false);
                    expProducer.addExplosion(window, i->getObjectSprite().getPosition().x, i->getObjectSprite().getPosition().y, true, false);
                    gameMusic.play();
                    menuMusic.stop();
                    smallExplSound.play();

                }

            }
            timeAfterPlatform.restart();


            timeAfterDemon.restart();


            timeAfterBird.restart();


            timeAfterTank.restart();

            break;
        }
        case(2):
        {
            backGroundUpdate(deltaTime);

            updatePlatforms(deltaTime, window);
            updateDemons(deltaTime, window);
            updateBirds(deltaTime, window);
            if (tank != nullptr);
            updateTank(deltaTime, window);


            


            expProducer.update(deltaTime, window);

            if (timeAfterstepTwo.getElapsedTime() > stepTwo)
            {
                gameStep++;
            }
            break;
        }
        case(3):
        {

            backGroundUpdate(deltaTime);

            updatePlatforms(deltaTime, window);
            updateDemons(deltaTime, window);
            updateBirds(deltaTime, window);
            if (tank != nullptr);
            updateTank(deltaTime, window);

            updateBoss(window);

            if (bossin != nullptr)
                bossin->updateAll(deltaTime, window, missleTexture, player->getObjectSprite().getPosition(), bossMissleSound);

         


            expProducer.update(deltaTime, window);

            if (bossin == nullptr)
            {
                gameStep++;
                gameMusic.stop();
                menuMusic.play();
                winSound.play();

            }
                
            break;
        }
        case(4):
        {
            
            timeAfterPlatform.restart();


            timeAfterDemon.restart();


            timeAfterBird.restart();


            timeAfterTank.restart();

            backGroundUpdate(deltaTime);

            updatePlatforms(deltaTime, window);
            updateDemons(deltaTime, window);
            updateBirds(deltaTime, window);
            if (tank != nullptr);
            updateTank(deltaTime, window);




            expProducer.update(deltaTime, window);


            break;
        }
        }


            if (player->getDead() && !playerDied)
            {
                player->getObjectSprite().move(-5000, -2000);
                playerDied = true;
                gameMusic.stop();
                menuMusic.play();
                looseSound.play();
                expProducer.addExplosion(window, player->getObjectSprite().getPosition().x, player->getObjectSprite().getPosition().y, false, false);
                bigExplSound.play();
            }


    }

    void ObjectProducer::updateTank(float deltaTime, sf::RenderWindow& window)
    {
        if (timeAfterTank.getElapsedTime() > tankRate)
        {
            float position = rand() % 2;

            tank->SetNewPosition();

            timeAfterTank.restart();

        }

        
        if (tank->getObjectSprite().getPosition().x > -200 && tank->getObjectSprite().getPosition().x < 2600)
        {
            tank->bulletUpdate(tankBulletTexture, tankShotSound);
            tank->update(deltaTime, window);
        }
        
    }

    void ObjectProducer::updatePlatforms(float deltaTime, sf::RenderWindow& window)
    {
        size_t deadbul = -1;

        for (size_t i = 0; i < platforms.size(); i++)
        {
            if (platforms[i]->getDead())
            {
                deadbul = i;
            }

        }

        if (deadbul != -1)
        {
            platforms.erase(platforms.begin() + deadbul);
        }


        for (auto& i : platforms)
            i->update(deltaTime, window);

        addPlatform(window);

        checkOnPlatform();
    }

    void ObjectProducer::addPlatform(sf::RenderWindow& window)
    {
        if (timeAfterPlatform.getElapsedTime() > platformRate)
        {
            platforms.push_back(std::make_unique<Platform>(platformTexture));
            timeAfterPlatform.restart();

        }

    }

    void ObjectProducer::updateDemons(float deltaTime, sf::RenderWindow& window)
    {

        size_t deadbul = -1;

        for (size_t i = 0; i < demons.size(); i++)
        {
            if (demons[i]->getDead())
            {
                deadbul = i;
            }

        }

        if (deadbul != -1)
        {
            expProducer.addExplosion(window, demons[deadbul]->getObjectSprite().getPosition().x, demons[deadbul]->getObjectSprite().getPosition().y, false, false);
            bigExplSound.play();

            demons.erase(demons.begin() + deadbul);
        }

        for (auto& i : demons)
            i->update(deltaTime, window);

        addDemon(window);
    }

    void ObjectProducer::addDemon(sf::RenderWindow& window)
    {
        if (timeAfterDemon.getElapsedTime() > demonRate)
        {
            demons.push_back(std::make_unique<EnemyDemon>(demonTexture));
            timeAfterDemon.restart();

        }
    }

    void ObjectProducer::updateBirds(float deltaTime, sf::RenderWindow& window)
    {
        size_t deadbul = -1;

        for (size_t i = 0; i < birds.size(); i++)
        {
            if (birds[i]->getDead())
            {
                deadbul = i;
            }

        }

        if (deadbul != -1)
        {
            expProducer.addExplosion(window, birds[deadbul]->getObjectSprite().getPosition().x, birds[deadbul]->getObjectSprite().getPosition().y, false, false);
            bigExplSound.play();

            birds.erase(birds.begin() + deadbul);
        }

        for (auto& i : birds)
        {
            i->update(deltaTime, window);
            i->updateBomb(bombTexture, bigExplSound);
        }


        addBird(window);
    }

    void ObjectProducer::addBird(sf::RenderWindow& window)
    {
        if (timeAfterBird.getElapsedTime() > birdRate)
        {
            birds.push_back(std::make_unique<EnemyBird>(birdTexture));
            timeAfterBird.restart();

        }
    }

    void ObjectProducer::checkOnPlatform()
    {
        bool onPlatform = false;
        for (auto &i : platforms)
        {
            if (i->getObjectSprite().getGlobalBounds().intersects(player->getObjectSprite().getGlobalBounds()))
                if (player->getObjectSprite().getPosition().y > 300 && player->getObjectSprite().getPosition().y < 310)
                    onPlatform = true;
        }
        player->setOnplatform(onPlatform);
    }

    void ObjectProducer::backGroundUpdate(float deltaTime)
    {
        bgGroundSprite.move(-350 * deltaTime, 0);
        if (bgGroundSprite.getPosition().x < -2259)  bgGroundSprite.setPosition(0, 0);

        bgSkySprite.move(-300 * deltaTime, 0);
        if (bgSkySprite.getPosition().x < -2259)  bgSkySprite.setPosition(0, 0);
    }

    void ObjectProducer::draw(sf::RenderWindow& window)
    {
        window.draw(bgSkySprite);
        window.draw(bgGroundSprite);

            switch (gameStep)
            {
            case(1):
            {
                window.draw(startButton->getObjectSprite());
                if (player != nullptr)
                    player->draw(window);

                break;
            }
            case(2):
            {

                break;
            }
            case(3):
            {

                break;
            }
            case(4):
            {
                window.draw(wintext->getObjectSprite());
                break;
            }
            }




        if (tank != nullptr)
        tank->draw(window);

        for (auto& i : platforms)
        {
            window.draw(i->getObjectSprite());

        }

        for (auto& i : demons)
        {
            i->draw(window);

        }

        for (auto& i : birds)
        {
            i->draw(window);

        }

        if (bossin != nullptr)
        bossin->draw(window);

        if (!playerDied) player->draw(window);
        else
            if(gameStep != 4)
                window.draw(loosetext->getObjectSprite());


        expProducer.draw(window);

    }
