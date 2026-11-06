#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;
int playerX, playerY, playerHealth, playerSpeed;
Texture playerTexture;

void initializePlayer()
{
	playerX = 100;
	playerY = 100;
	playerHealth = 100;
	playerSpeed = 5;
	playerTexture.loadFromFile("assests_resources/player.png");
	
	
}
void drawPlayer(RenderWindow & window)
{
	float width =static_cast<float> (playerTexture.getSize().x);
	float length =static_cast<float> (playerTexture.getSize().y);
	Sprite playerSprite(playerTexture);
	playerSprite.setScale(Vector2f(80.f /width,85.f/length));
	playerSprite.setPosition(Vector2f(playerX, playerY));
	window.draw(playerSprite);
}
using namespace Keyboard;
void movePlayer(int windowWidth,int windowHeight)
{
	if (isKeyPressed(Key::D))
	{
		if (playerX+80+playerSpeed <=windowWidth)
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
		if (playerY + playerSpeed + 85 <= windowHeight)
		{
			playerY += playerSpeed;
		}
	}

	
}
void takeDamage(int damage)
{
	if (playerHealth <= 0 || damage <= 0)
	{
		return;
	}
	playerHealth -= damage;

	if (playerHealth < 0)
	{
		playerHealth = 0;
	}
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
bool GameOver()
{
	if (playerHealth <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}