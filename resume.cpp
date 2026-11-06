
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;

const int none = 0, resume = 1, restart = 2, main_menu = 3, exit_game = 4;

bool paused = false;
Font pauseFont;
Text pauseTitle(pauseFont, "GAME PAUSED", 40);
Text pauseOptions(pauseFont,"1. Resume Game\n""2. Restart Level\n""3. Main Menu\n""4. Exit Game", 25);

void pauseGame()
{
    paused = true;
}
int handlePauseInput(Keyboard::Key a)
{
    if (a == Keyboard::Key::P && !paused)
    {
        pauseGame();
    }

    if (paused)
    {
        if (a == Keyboard::Key::Num1)
        {
            paused = false;
            return resume;
        }

        if (a == Keyboard::Key::Num2)
            return restart;

        if (a == Keyboard::Key::Num3)
            return main_menu;

        if (a == Keyboard::Key::Num4)
            return exit_game;
    }

    return none;
}

void initializePauseMenu()
{
    if (!pauseFont.openFromFile("data/font.ttf"))
    {
        cout << "Font loading failed!" << endl;
        return;
    }

    pauseTitle.setFillColor(Color::Yellow);
    pauseTitle.setPosition(Vector2f(250, 150));

    pauseOptions.setFillColor(Color::White);
    pauseOptions.setPosition(Vector2f(250, 250));
}

void drawPauseMenu(RenderWindow& window)
{
    if (!paused)
        return;

    Vector2u windowSize = window.getSize();

    RectangleShape overlay(
        Vector2f(
            static_cast<float>(windowSize.x),
            static_cast<float>(windowSize.y)
        )
    );

    overlay.setFillColor(Color(0, 0, 0, 180));

    window.draw(overlay);
    window.draw(pauseTitle);
    window.draw(pauseOptions);
}
