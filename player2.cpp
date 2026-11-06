
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
int player2X, player2Y, player2Health, player2Speed;
Texture player2Texture;

void initializePlayer2()
{
    player2X = 250;
    player2Y = 100;
    player2Health = 100;
    player2Speed = 5;

    player2Texture.loadFromFile("data/sprites/player.png");
}

void drawPlayer2(RenderWindow& window)
{
    float width = static_cast<float>(player2Texture.getSize().x);
    float length = static_cast<float>(player2Texture.getSize().y);

    Sprite player2Sprite(player2Texture);

    player2Sprite.setScale(Vector2f(80.f / width, 85.f / length));
    player2Sprite.setPosition(Vector2f(player2X, player2Y));

    window.draw(player2Sprite);
}

using namespace Keyboard;

void movePlayer2(int windowWidth, int windowHeight)
{
    if (isKeyPressed(Key::Right))
    {
        if (player2X + 80 + player2Speed <= windowWidth)
        {
            player2X += player2Speed;
        }
    }
    else if (isKeyPressed(Key::Left))
    {
        if (player2X - player2Speed >= 0)
        {
            player2X -= player2Speed;
        }
    }
    else if (isKeyPressed(Key::Up))
    {
        if (player2Y - player2Speed >= 0)
        {
            player2Y -= player2Speed;
        }
    }
    else if (isKeyPressed(Key::Down))
    {
        if (player2Y + player2Speed + 85 <= windowHeight)
        {
            player2Y += player2Speed;
        }
    }
}

void takeDamagePlayer2(int damage)
{
    if (player2Health <= 0 || damage <= 0)
    {
        return;
    }

    player2Health -= damage;

    if (player2Health < 0)
    {
        player2Health = 0;
    }
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
    currentHealth.setFillColor(Color::Green);

    window.draw(currentHealth);
}
