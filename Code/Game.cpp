#include "Game.h"



    void Game::Handle_input()
    {
        sf::Event event;
        sf::FloatRect speedRect(0, 0, 0, 0);

        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  speedRect.width = 1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))  speedRect.height = 1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))  speedRect.top = 1;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))  speedRect.left = 1;

            producer.playerInput(speedRect, window);

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        producer.input(speedRect, window);

    }





    void Game::Update(float deltaTime)
    {
        producer.update(deltaTime, window);
    }


    void Game::Draw()
    {
        window.clear();
        producer.draw(window);
        window.display();
    }



    Game::Game()
        :window(WINDOW_SIZE, WINDOW_TITLE)
    {


    }



    void Game::Run()
    {


        sf::Image icon; //icon of window
        icon.loadFromFile("Resources/Icon.png");
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        sf::Image cursorImage; //ico of cursor
        cursorImage.loadFromFile("Resources/Cursor.png");
        sf::Vector2u clickspot(23, 23);
        sf::Cursor cursor;
        cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), clickspot);
        window.setMouseCursor(cursor);


        sf::Clock deltaTimeClock;


        while (window.isOpen())
        {
            sf::Time deltaTime = deltaTimeClock.restart();

            Handle_input();

            Update(deltaTime.asSeconds());

            Draw();
        }
    }


