// g++ main.cpp player.cpp player2.cpp enemies.cpp map.cpp sounds.cpp menus.cpp -std=c++17 -O2 -o MazeRunner.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <optional>
#include "player.h"
#include "sounds.h"
#include "menus.h"
#include "player2.h"
#include "enemies.h"
#include "map.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
    VideoMode res = VideoMode::getDesktopMode();
    RenderWindow Gamewin(res, "The Maze Runner", State::Fullscreen);

    int width = Gamewin.getSize().x;
    int length = Gamewin.getSize().y;

    initializePlayer();
    initializePlayer2();
    initializeBoss(width, length);
    initializeEnemies(width, length);
    initializeGun(2.0);

    int level = 1;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    generateMaze();

    Music music;
    backgroundMusic(music, level);

    SoundBuffer gun_buffer;
    if (!gun_buffer.loadFromFile("data/sounds/gunshot.mp3"))
        return -1;
    Sound gun_sound(gun_buffer);

    SoundBuffer damage_buffer;
    if (!damage_buffer.loadFromFile("data/sounds/takedamage.wav"))
        return -1;
    Sound damage_sound(damage_buffer);

    SoundBuffer boss_hurt_buffer;
    if (!boss_hurt_buffer.loadFromFile("data/sounds/bossDamage.wav"))
        return -1;
    Sound boss_hurt_sound(boss_hurt_buffer);

    SoundBuffer mummies_hurt_buffer;
    if (!mummies_hurt_buffer.loadFromFile("data/sounds/mummiesDamage.wav"))
        return -1;
    Sound mummies_hurt_sound(mummies_hurt_buffer);

    bool break_flag = false;
    int players = 1;
    int health1 = 100;
    int health2 = 100;
    int player1X = 30;
    int player1Y = 30;
    int player2X = 60;
    int player2Y = 30;
    int bossHealth = 750;
    bool isdead = false;
    bool iswin = false;
    bool ispaused = false;
    bool qHeld = false;
    int retry = 2;
    int paused = 0;

    while (Gamewin.isOpen())
    {
    gameLoop:
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

                if (keyPressed->code == Keyboard::Key::J)
                {
                    bossHealth = bossDamage(100);
                }

                if (keyPressed->code == Keyboard::Key::Q)
                {
                    if (!qHeld && break_flag && !ispaused && !isdead && !iswin)
                        shootGun(player1X, player1Y);

                    qHeld = true;
                }

                if (keyPressed->code == Keyboard::Key::T && break_flag == false)
                {
                    level = 4;
                    backgroundMusic(music, level);
                    break_flag = true;
                }

                if (keyPressed->code == Keyboard::Key::Enter)
                    break_flag = true;

                if (keyPressed->code == Keyboard::Key::R &&
                    (isdead || iswin || ispaused))
                {
                    retry = 1;
                }
                else if (keyPressed->code == Keyboard::Key::Enter &&
                         (isdead || iswin))
                {
                    retry = 0;
                }

                if (keyPressed->code == Keyboard::Key::P)
                    paused++;
            }

            if (const auto* keyReleased = event->getIf<Event::KeyReleased>())
            {
                if (keyReleased->code == Keyboard::Key::Q)
                    qHeld = false;
            }
        }

        if (!Gamewin.isOpen())
            break;

        if (health1 <= 0 || health2 <= 0)
            isdead = true;

        if (level == 5 && bossHealth <= 0)
            iswin = true;

        if (paused % 2 == 0)
            ispaused = false;
        else
            ispaused = true;

        if (retry == 1)
        {
            initializePlayer();
            initializePlayer2();
            initializeBoss(width, length);
            initializeEnemies(width, length);
            initializeGun(2.0f);

            level = 1;
            generateMaze();
            backgroundMusic(music, level);

            health1 = 100;
            health2 = 100;
            bossHealth = getBossHealth();
            player1X = 30;
            player1Y = 30;
            player2X = 60;
            player2Y = 30;
            retry = 2;
            isdead = false;
            iswin = false;
            ispaused = false;
            paused = 0;
            continue;
        }
        else if (retry == 0)
        {
            break;
        }

        Gamewin.clear();

        if (!break_flag && isdead == false && iswin == false)
        {
            showMainMenu(Gamewin, players);
        }
        else if (ispaused && break_flag && !isdead && iswin == false)
        {
            pauseMenu(Gamewin);
        }
        else if (break_flag && isdead == false && iswin == false)
        {
            if (level == 5)
            {
                makebossroom(Gamewin);
                drawBossBar(Gamewin);
                drawBoss(Gamewin);

                int bossHits = moveBoss(
                    Gamewin, player1X, player1Y, player2X, player2Y, players
                );

                if (bossHits == 1)
                {
                    health1 = takeDamage(10);
                    damageSound(damage_sound);
                }
                if (bossHits == 2)
                {
                    health2 = takeDamagePlayer2(10);
                    damageSound(damage_sound);
                }
                if (bossHits == 3)
                {
                    health1 = takeDamage(10);
                    health2 = takeDamagePlayer2(10);
                    damageSound(damage_sound);
                }
            }
            else
            {
                make_maze(Gamewin);
            }

            drawEnemies(Gamewin);
            DrawHealthBar(Gamewin);
            drawPlayer(Gamewin);

            if (!ispaused)
            {
                movePlayer(width, length, player1X, player1Y);
                gunSound(gun_sound, players);

                int enemyHits = moveEnemies(
                    player1X, player1Y, player2X, player2Y, players
                );

                moveGun(
                    Gamewin, boss_hurt_sound, mummies_hurt_sound,
                    player2X, player2Y, players
                );

                bossHealth = getBossHealth();

                if (enemyHits == 1)
                {
                    health1 = takeDamage(10);
                    damageSound(damage_sound);
                }
                if (enemyHits == 2)
                {
                    health2 = takeDamagePlayer2(10);
                    damageSound(damage_sound);
                }
                if (enemyHits == 3)
                {
                    health2 = takeDamagePlayer2(10);
                    health1 = takeDamage(10);
                    damageSound(damage_sound);
                }
            }

            if (players == 2)
            {
                drawPlayer2(Gamewin);
                DrawHealthBarPlayer2(Gamewin);

                if (!ispaused)
                {
                    movePlayer2(width, length, player2X, player2Y);
                }
            }

            bool completedMaze = level < 5 &&
                (mazeCompleted(player1X, player1Y, 20.0f, 20.0f) ||
                 (players == 2 &&
                  mazeCompleted(player2X, player2Y, 20.0f, 20.0f)));

            if (completedMaze)
            {
                level++;

                if (level > 5)
                {
                    iswin = true;
                }
                else
                {

                    if (level < 5)
                    {
                        generateMaze();
                    }

                    initializePlayer();
                    initializePlayer2();
                    initializeBoss(width, length);
                    initializeEnemies(width, length);
                    initializeGun(2.0f);

                    player1X = 30;
                    player1Y = 30;
                    player2X = 60;
                    player2Y = 30;
                    health1 = 100;
                    health2 = 100;
                    bossHealth = getBossHealth();

                    backgroundMusic(music, level);
                    goto gameLoop;
                }
            }
        }
        else if (isdead && iswin == false)
        {
            showGameOverScreen(Gamewin);
        }
        else if (iswin == true && !isdead)
        {
            winScreen(Gamewin);
        }

        Gamewin.display();
    }

    cout << width << " x " << length << endl;
}
