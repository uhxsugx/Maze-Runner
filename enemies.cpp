#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

double distance(int x1, int x2, int y1, int y2);

int bossX, bossY, bossHealth, bossSpeed;
float boss_size = 35.0;

void initializeBoss(int width, int length)
{
    bossX = width/2.0;
    bossY = length/2.0;
    bossHealth = 300;
    bossSpeed = 1;
}

void drawBoss(RenderWindow &window)
{
    CircleShape boss(boss_size);
    boss.setFillColor(Color(104, 0, 152));
    boss.setPosition(Vector2f(bossX, bossY));
    window.draw(boss);
}

void drawBossBar(RenderWindow &window)
{
    RectangleShape bossBar;

    int width = window.getSize().x;
    int length = window.getSize().y;
    bossBar.setSize({750.f, 20.f});
    bossBar.setPosition(Vector2f((width-400), 20.f));
    bossBar.setFillColor(Color(80, 80, 80));

    window.draw(bossBar);
    RectangleShape currentbossBar;

    float healthwidth = 200.f * bossHealth / 100.f;
    currentbossBar.setSize(Vector2f(healthwidth, 20.f));
    currentbossBar.setPosition(Vector2f((width-400), 20.f));
    currentbossBar.setFillColor(Color(104, 0, 152));

    window.draw(currentbossBar);
}

int bossDamage(int damage)
{
    if (bossHealth <= 0 || damage <= 0)
	{
		return bossHealth;
	}
	bossHealth -= damage;

	if (bossHealth < 0)
	{
		bossHealth = 0;
	}

	if(bossHealth > 100)
	{
		bossHealth = 100;
	}

    return bossHealth;
}

using namespace Keyboard;
int moveBoss(sf::RenderWindow &window, int player1X, int player1Y, int player2X, int player2Y, int mode)
{
    if(mode == 1)
    {
        player2X = player1X;
        player2Y = player1Y;
    }
    double dist1 = distance(bossX, player1X, bossY, player1Y);
    double dist2 = distance(bossX, player2X, bossY, player2Y);
    double track;
    int ishit = 0;
    if(dist1 > dist2)
    {
        if(bossX >= player2X)
        {
            bossX -= bossSpeed;
        }
        else if(bossX <= player2X)
        {
            bossX += bossSpeed;
        }
        else if(bossY >= player2Y)
        {
            bossY -= bossSpeed;
        }
        else if(bossY <= player2Y)
        {
            bossY += bossSpeed;
        }
    }

    else if(dist1 < dist2)
    {
        if(bossX >= player1X)
        {
            bossX -= bossSpeed;
        }
        else if(bossX <= player1X)
        {
            bossX += bossSpeed;
        }
        else if(bossY >= player1Y)
        {
            bossY -= bossSpeed;
        }
        else if(bossY <= player1Y)
        {
            bossY += bossSpeed;
        }
    }

    if(bossX == player1X && bossY == player1Y)
    {
        ishit = 1;
        cout << "yes" << endl;
    }

    else if (bossX == player2X && bossY == player2Y)
    ishit = 2;

    else
    ishit = 0;

    return ishit;

}

double distance(int x1, int x2, int y1, int y2)
{
    double distance = sqrt(pow((x2-x1), 2) - pow((y2-y1), 2));
    return distance;
}