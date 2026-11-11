
#include <SFML/Graphics.hpp>
#include "map.h"
using namespace std;
using namespace sf;
int player2X, player2Y, player2Health, player2Speed;
float player2_size = 20.0;
RectangleShape playerTexture2({player2_size, player2_size});

void initializePlayer2()
{
    player2X = 60;
    player2Y = 30;
    player2Health = 100;
    player2Speed = 1;

}

void drawPlayer2(RenderWindow& window)
{
	float width =static_cast<float> (playerTexture2.getSize().x);
	float length =static_cast<float> (playerTexture2.getSize().y);
	playerTexture2.setFillColor(Color::Blue);
	playerTexture2.setOutlineColor(Color::White);
	playerTexture2.setOutlineThickness(1.f);
	playerTexture2.setPosition(Vector2f(player2X, player2Y));
	window.draw(playerTexture2);
}

using namespace Keyboard;

void movePlayer2(int windowWidth, int windowHeight, int &playerX2, int &playerY2)
{
    if (isKeyPressed(Key::Right))
    {
        if (player2X + player2Speed <= (windowWidth-player2_size) &&
            !mazeCollision(player2X + player2Speed, player2Y, player2_size, player2_size))
        {
            player2X += player2Speed;
        }
    }
    else if (isKeyPressed(Key::Left))
    {
        if (player2X - player2Speed >= 0 &&
            !mazeCollision(player2X - player2Speed, player2Y, player2_size, player2_size))
        {
            player2X -= player2Speed;
        }
    }
    else if (isKeyPressed(Key::Up))
    {
        if (player2Y - player2Speed >= 0 &&
            !mazeCollision(player2X, player2Y - player2Speed, player2_size, player2_size))
        {
            player2Y -= player2Speed;
        }
    }
    else if (isKeyPressed(Key::Down))
    {
        if (player2Y + player2Speed <= (windowHeight-player2_size) &&
            !mazeCollision(player2X, player2Y + player2Speed, player2_size, player2_size))
        {
            player2Y += player2Speed;
        }
    }
    playerX2 = player2X;
    playerY2 = player2Y;
}

int takeDamagePlayer2(int damage)
{
    if (player2Health <= 0 || damage <= 0)
    {
        return player2Health;
    }

    player2Health -= damage;

    if (player2Health < 0)
    {
        player2Health = 0;
    }

    if(player2Health > 100)
    {
        player2Health = 100;
    }
    return player2Health;
}

void DrawHealthBarPlayer2(RenderWindow& window)
{
    RectangleShape healthBack;

    healthBack.setSize(Vector2f(200.f, 20.f));
    healthBack.setPosition(Vector2f(250.f, 20.f));
    healthBack.setFillColor(Color(80, 80, 80));

    window.draw(healthBack);

    RectangleShape currentHealth;

    float healthWidth = 200.f * player2Health / 100.f;

    currentHealth.setSize(Vector2f(healthWidth, 20.f));
    currentHealth.setPosition(Vector2f(250.f, 20.f));
    currentHealth.setFillColor(Color::Blue);

    window.draw(currentHealth);
}
