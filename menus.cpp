#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;
using namespace sf;
using namespace Keyboard;

void showMainMenu(RenderWindow &window, int &mode)
{
    Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("data/images/Ancient Egyptian Temple Maze.png"))
    {
        cout << "Image not found !" << endl;
        return;
    }

    if(Keyboard::isKeyPressed(Key::Num1) || Keyboard::isKeyPressed(Key::Numpad1))
    mode = 1;

    if(Keyboard::isKeyPressed(Key::Num2) || Keyboard::isKeyPressed(Key::Numpad2))
    mode = 2;

    if(mode == 2)
    {
	if(!backgroundTexture.loadFromFile("data/images/Ancient Egyptian Temple Maze 2.png"))
	{
		cout << "No" << endl;
		return;
	}
    }
    Sprite background(backgroundTexture);
    background.setScale({(float)window.getSize().x/backgroundTexture.getSize().x, (float)window.getSize().y/backgroundTexture.getSize().y});
    window.draw(background);
    return;
}

void loadingScreen(RenderWindow &window)
{
    sleep(seconds(5));
    Font font;
    if(!font.openFromFile("data/fonts/Minecraft.ttf"))
    {
	return;
    }

    Text text(font, "Loading....", 50);
    text.setFillColor(Color::White);
    text.setPosition({250, 150});
    window.draw(text);


}

void showGameOverScreen(RenderWindow &window)
{
    Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("data/images/Ancient Egyptian Temple Maze.png"))
    {
        cout << "Image not found !" << endl;
        return;
    }
    Sprite background(backgroundTexture);
    background.setScale({(float)window.getSize().x/backgroundTexture.getSize().x, (float)window.getSize().y/backgroundTexture.getSize().y});
    window.draw(background);
    Font font;
    if(!font.openFromFile("data/fonts/Minecraft.ttf"))
    {
        cout << "Font dont open. menus.cpp" << endl;
        return;
    }

    Text text(font, "GAME OVER", 50);
    text.setFillColor(Color::Yellow);
    text.setPosition(Vector2f(250, 150));
    window.draw(text);

    Text retry_info(font, "Press R to retry and Enter to exit", 25);
    retry_info.setFillColor(Color::White);
    retry_info.setPosition({250.f, 250.f});
    window.draw(retry_info);

    return;
}

void pauseMenu(RenderWindow &window)
{
    Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("data/images/Ancient Egyptian Temple Maze.png"))
    {
        cout << "Image not found !" << endl;
        return;
    }
    Sprite background(backgroundTexture);
    background.setScale({(float)window.getSize().x/backgroundTexture.getSize().x, (float)window.getSize().y/backgroundTexture.getSize().y});
    window.draw(background);
    Font font;
    if(!font.openFromFile("data/fonts/Minecraft.ttf"))
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
    Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("data/images/Ancient Egyptian Temple Maze.png"))
    {
        cout << "Image not found !" << endl;
        return;
    }
    Sprite background(backgroundTexture);
    background.setScale({(float)window.getSize().x/backgroundTexture.getSize().x, (float)window.getSize().y/backgroundTexture.getSize().y});
    window.draw(background);
    Font font;
    if(!font.openFromFile("data/fonts/Minecraft.ttf"))
    {
        cout << "Font dont open. menus.cpp" << endl;
        return;
    }

    Text text(font, "YOU WIN!!", 50);
    text.setFillColor(Color::Yellow);
    text.setPosition(Vector2f(250, 150));
    window.draw(text);

    Text retry_info(font, "Press R to retry and Enter to exit", 25);
    retry_info.setFillColor(Color::White);
    retry_info.setPosition({250.f, 250.f});
    window.draw(retry_info);

    return;
}
