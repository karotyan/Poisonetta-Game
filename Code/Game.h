#pragma once

#include "ObjectProducer.h"

class Game
{
private:

    const sf::VideoMode WINDOW_SIZE = { 1920, 1080 };  // Size of window
    const sf::String WINDOW_TITLE = "Poisonetta"; // Name of window
    sf::RenderWindow window;

    ObjectProducer producer;


    void Handle_input();
   

    void Update(float deltaTime);

    void Draw();
 

public:

    Game();
       
 
    void Run();
    


};

