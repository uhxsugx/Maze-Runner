#include<iostream>
#include "player.h"
#include "player2.h"
#include "sounds.h"
#include "resume.h"
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

    initializePauseMenu();

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

                int action = handlePauseInput(keyPressed->code);

                if (action == restart)
                {
                    initializePlayer();
                    initializePlayer2();
                    paused = false;
                }

                else if (action == main_menu)
                {
                    cout << "Main Menu selected!" << endl;
                }

                else if (action == exit_game)
                {
                    Gamewin.close();
                }
            }
        }

        Gamewin.clear();
        if (!paused)
        {
            movePlayer(width, length);
            movePlayer2(width, length);
        }
        DrawHealthBar(Gamewin);
        DrawHealthBarPlayer2(Gamewin);
        drawPlayer(Gamewin);
        drawPlayer2(Gamewin);
        if (paused)
        {
            drawPauseMenu(Gamewin);
        }

        Gamewin.display();
    }
}
