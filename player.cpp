#include<SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
int playerX, playerY, playerHealth, playerSpeed;

void initializePlayer()
{
	playerX = 100;
	playerY = 100;
	playerHealth = 100;
	playerSpeed = 1;
	//playerTexture.loadFromFile("data/sprites/player.png");
	
}
void drawPlayer(RenderWindow & window)
{
	RectangleShape playerTexture({20.f, 20.f});
	float width =static_cast<float> (playerTexture.getSize().x);
	float length =static_cast<float> (playerTexture.getSize().y);
	//Sprite playerSprite(playerTexture);
	//playerSprite.setScale(Vector2f(80.f /width,85.f/length));
	playerTexture.setFillColor(Color::Green);
	playerTexture.setOutlineColor(Color::White);
	playerTexture.setOutlineThickness(1.f);
	playerTexture.setPosition(Vector2f(playerX, playerY));
	window.draw(playerTexture);
}
using namespace Keyboard;
void movePlayer(int windowWidth,int windowHeight)
{
	if (isKeyPressed(Key::D))
	{
		if (playerX + playerSpeed <=windowWidth)
		{
			playerX += playerSpeed;
		}
	}
	else if (isKeyPressed(Key::A))
	{
		if (playerX - playerSpeed >= 0)
		{
			playerX -= playerSpeed;
		}
	}
	else if (isKeyPressed(Key::W))
	{
		if (playerY - playerSpeed >= 0)
		{
			playerY -= playerSpeed;
		}
	}
	else if (isKeyPressed(Key::S))
	{
		if (playerY + playerSpeed <= windowHeight)
		{
			playerY += playerSpeed;
		}
	}
	
}

int takeDamage(int damage)
{
	if (playerHealth <= 0 || damage <= 0)
	{
		return playerHealth;
	}
	playerHealth -= damage;

	if (playerHealth < 0)
	{
		playerHealth = 0;
	}

	if(playerHealth > 100)
	{
		playerHealth = 100;
	}

	return playerHealth;
}
void DrawHealthBar(RenderWindow & w)
{
	RectangleShape healthBack;

	healthBack.setSize(Vector2f(200.f, 20.f));
	healthBack.setPosition(Vector2f(20.f, 20.f));
	healthBack.setFillColor(Color(80, 80, 80));

	w.draw(healthBack);
	RectangleShape currenthealth;

	float healthwidth = 200.f * playerHealth / 100.f;
	currenthealth.setSize(Vector2f(healthwidth, 20.f));
	currenthealth.setPosition(Vector2f(20.f, 20.f));
	currenthealth.setFillColor(Color::Green);

	w.draw(currenthealth);
}
