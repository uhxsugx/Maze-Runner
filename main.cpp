
#include<iostream>
#include "player.h"
#include "player2.h"
#include "sounds.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
    VideoMode res = VideoMode::getDesktopMode();
    RenderWindow Gamewin(res, "Maze Runner", State::Fullscreen);

    int width = Gamewin.getSize().x;
    int length = Gamewin.getSize().y;

    initializePlayer();
    initializePlayer2();

    Music music;
    backgroundMusic(music, 1);

    while (Gamewin.isOpen())
    {
        while (optional<Event> event = Gamewin.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                Gamewin.close();
            }

            if (const auto* keyPressed = event->getIf<Event::KeyPressed>())
            {
                if (keyPressed->code == Keyboard::Key::Escape)
                {
                    Gamewin.close();
                }
            }
        }

        Gamewin.clear();

        movePlayer(width, length);
        movePlayer2(width, length);

        DrawHealthBar(Gamewin);
        DrawHealthBarPlayer2(Gamewin);

        drawPlayer(Gamewin);
        drawPlayer2(Gamewin);

        Gamewin.display();
    }
}
