/*
                         POISONETTA GAME

This is non-comercial project created by student to show his programming skills.

Design of characters was based on mobile game "Soul Knight", also there were
used some free textures from Internet.

It is simple Run&Gun level in 2D with gravitation.

Stack: C++, STL, SFML

Further updates:

- Add Interface (Healthbar for player and boss)
- Add more random for level
- Add some cutscenes/animations

SFML version used in developement: 2.6.1
*/


#include "Game.h"

    int main()
    {

        std::srand(std::time(0));
        Game game;
        game.Run();
        return 0;

    }

