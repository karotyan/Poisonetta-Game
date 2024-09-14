#pragma once

#include "Player.h"
#include "EnemyTank.h"
#include "ExplosionProducer.h"
#include "EnemyBoss.h"
#include "Platform.h"
#include "Enemydemon.h"
#include "Enemybird.h"
#include "Label.h"



class ObjectProducer
{
private:

    sf::Music gameMusic;
    sf::Music menuMusic;

    sf::SoundBuffer winBuffer;
    sf::SoundBuffer looseBuffer;
    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer playerShootBuffer;
    sf::SoundBuffer damageBuffer;
    sf::SoundBuffer smallExplBuffer;
    sf::SoundBuffer tankShotBuffer;
    sf::SoundBuffer bossMissleBuffer;
    sf::SoundBuffer bigExplBuffer;


    sf::Sound winSound;
    sf::Sound looseSound;
    sf::Sound jumpSound;
    sf::Sound playerShootSound;
    sf::Sound damageSound;
    sf::Sound smallExplSound;
    sf::Sound tankShotSound;
    sf::Sound bossMissleSound;
    sf::Sound bigExplSound;

    int gameStep;
    bool playerDied;

    ExplosionProducer expProducer;

    sf::Texture playerTexture;
    sf::Texture bulletTexture;
    sf::Texture platformTexture;
    sf::Texture gunTexture;
    sf::Texture demonTexture;
    sf::Texture birdTexture;
    sf::Texture bombTexture;
    sf::Texture tankTexture;
    sf::Texture tankBulletTexture;
    sf::Texture bossTexture;
    sf::Texture missleTexture;

    sf::Texture bgSkyTexture;
    sf::Sprite bgSkySprite;

    sf::Texture bgGroundTexture;
    sf::Sprite bgGroundSprite;

    sf::Texture buttonTexture;

    sf::Texture winTexture;
    sf::Texture looseTexture;


    std::vector<std::unique_ptr<Platform>> platforms;
    std::vector<std::unique_ptr<EnemyDemon>> demons;
    std::vector<std::unique_ptr<EnemyBird>> birds;


    Player* player;
    EnemyTank* tank;
    EnemyBoss* bossin;
    Label* startButton;
    Label* wintext;
    Label* loosetext;

    sf::Time platformRate;
    sf::Clock timeAfterPlatform;

    sf::Time demonRate;
    sf::Clock timeAfterDemon;

    sf::Time birdRate;
    sf::Clock timeAfterBird;

    sf::Time tankRate;
    sf::Clock timeAfterTank;

    sf::Time stepTwo;
    sf::Clock timeAfterstepTwo;


public:

    ObjectProducer();



    void updatePlayerShots(sf::RenderWindow& window);
   

    void updateBoss(sf::RenderWindow& window);
   

    void input(sf::FloatRect speedRect, sf::RenderWindow& window);
   
    void playerInput(sf::FloatRect speedRect, sf::RenderWindow& window);
    

    void update(float deltaTime, sf::RenderWindow& window);
    

    void updateTank(float deltaTime, sf::RenderWindow& window);
    

    void updatePlatforms(float deltaTime, sf::RenderWindow& window);
    

    void addPlatform(sf::RenderWindow& window);
  

    void updateDemons(float deltaTime, sf::RenderWindow& window);
   

    void addDemon(sf::RenderWindow& window);
    

    void updateBirds(float deltaTime, sf::RenderWindow& window);
   

    void addBird(sf::RenderWindow& window);
   

    void checkOnPlatform();
    

    void backGroundUpdate(float deltaTime);
   

    void draw(sf::RenderWindow& window);
  


};

