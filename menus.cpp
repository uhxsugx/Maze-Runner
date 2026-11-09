#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
using namespace Keyboard;

void showMainMenu(RenderWindow &window, int &mode)
{
    Font font;
    if (!font.openFromFile("data/fonts/ARIAL.ttf"))
    {
        cout << "Path data/fonts/ARIAL.ttf menus.cpp" << endl;
        return;
    }

    Text title(font, "The Maze Runner", 25);
    title.setFillColor(Color::Yellow);

    title.setPosition(Vector2f(250, 150));
    window.draw(title);

    if(Keyboard::isKeyPressed(Key::Num1) || Keyboard::isKeyPressed(Key::Numpad1))
    mode = 1;

    if(Keyboard::isKeyPressed(Key::Num2) || Keyboard::isKeyPressed(Key::Numpad2))
    mode = 2;


    Text players(font, "Mode: Solo", 20);
    if(mode == 2)
    players.setString("Mode: Co-op");
    players.setPosition(Vector2f(250, 250));
    window.draw(players);


    Text controls(font, "Controls: \nP1: WASD\t P2: Arrows\t Exit: Esc\t Pause: P\t Restart: R\nSolo: Num1\t Co-op: Num2", 20);
    controls.setPosition({250.f, 450.f});
    window.draw(controls);

    
   
    
    return;
}

void showGameOverScreen(RenderWindow &window)
{
    Font font;
    if(!font.openFromFile("data/fonts/ARIAL.ttf"))
    {
        cout << "Font dont open. menus.cpp" << endl;
        return;
    }

    Text text(font, "GAME OVER", 50);
    text.setFillColor(Color::Yellow);
    text.setPosition(Vector2f(250, 150));
    window.draw(text);

    Text retry_info(font, "Press R to retry and any other key to exit", 25);
    retry_info.setFillColor(Color::White);
    retry_info.setPosition({250.f, 250.f});
    window.draw(retry_info);

    return;
}

void pauseMenu(RenderWindow &window)
{
    Font font;
    if(!font.openFromFile("data/fonts/ARIAL.ttf"))
    {
        cout << "Font didnt open paseMenu";
        return;
    }

    Text title(font, "Game Paused", 50);
    title.setPosition({250.f, 150.f});
    title.setFillColor(Color::Yellow);
    window.draw(title);

    Text options(font, "1. Resume/Pause (P)\n 2. Restart (R)\n 3. Exit (Ecs.)", 25);
    options.setPosition({250.f, 250.f});
    window.draw(options);

    Text controls(font, "P1: WASD\t P2: Arrows\t", 20);
    controls.setPosition({250.f, 450.f});
    window.draw(controls);

    if(isKeyPressed(Keyboard::Key::R))
    {
        return;
    }
}

void winScreen(RenderWindow &window)
{
    Font font;
    if(!font.openFromFile("data/fonts/ARIAL.ttf"))
    {
        cout << "Font dont open. menus.cpp" << endl;
        return;
    }

    Text text(font, "YOU WIN!!", 50);
    text.setFillColor(Color::Yellow);
    text.setPosition(Vector2f(250, 150));
    window.draw(text);

    Text retry_info(font, "Press R to retry and any other key to exit", 25);
    retry_info.setFillColor(Color::White);
    retry_info.setPosition({250.f, 250.f});
    window.draw(retry_info);

    return;
}