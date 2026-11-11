#include <SFML/Graphics.hpp>
#include "player.h"
#include "player2.h"
#include "map.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;
using namespace sf;

extern int playerX, playerY;
extern RectangleShape playerTexture2;
extern RectangleShape playerTexture;

double distance(float x1, float x2, float y1, float y2);

int bossHealth;
float bossX, bossY;
float bossSpeed;
float enemySpeed;
float boss_size = 35.0;
const int enemyCount = 10;
const float enemy_size = 15.0;
CircleShape enemy[enemyCount];
bool enemyActive[enemyCount];
bool enemyTouchingPlayer1[enemyCount];
bool enemyTouchingPlayer2[enemyCount];
bool bossTouchingPlayer1 = false;
bool bossTouchingPlayer2 = false;
float gunX, gunY;
float gunSpeed;
float gunTargetX, gunTargetY;
int gunTargetEnemy;
bool gunTargetsBoss;
bool gunActive;
bool gunReloading;
Clock gunReloadClock;

bool circleRectangleCollision(float circleX, float circleY, float radius, float rectangleX, float rectangleY, float rectangleWidth, float rectangleHeight)
{
    float nearestX = max(rectangleX, min(circleX, rectangleX + rectangleWidth));
    float nearestY = max(rectangleY, min(circleY, rectangleY + rectangleHeight));
    float differenceX = circleX - nearestX;
    float differenceY = circleY - nearestY;

    return differenceX * differenceX + differenceY * differenceY <= radius * radius;
}

bool circlesCollision(float circle1X, float circle1Y, float radius1, float circle2X, float circle2Y, float radius2)
{
    float differenceX = circle1X - circle2X;
    float differenceY = circle1Y - circle2Y;
    float radius = radius1 + radius2;

    return differenceX * differenceX + differenceY * differenceY <= radius * radius;
}

void initializeBoss(int width, int length)
{
    bossX = width / 2.0f - boss_size;
    bossY = length / 2.0f - boss_size;
    bossHealth = 750;
    bossSpeed = 0.5;
    bossTouchingPlayer1 = false;
    bossTouchingPlayer2 = false;
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
    bossBar.setPosition(Vector2f((width-770), 20.f));
    bossBar.setFillColor(Color(80, 80, 80));

    window.draw(bossBar);
    RectangleShape currentbossBar;

    float healthwidth = 750.f * bossHealth / 750.f;
    currentbossBar.setSize(Vector2f(healthwidth, 20.f));
    currentbossBar.setPosition(Vector2f((width-770), 20.f));
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

    return bossHealth;
}

int getBossHealth()
{
    return bossHealth;
}

using namespace Keyboard;
int moveBoss(sf::RenderWindow &window, int player1X, int player1Y, int player2X, int player2Y, int mode)
{
    float player1CenterX = player1X + 10.0f;
    float player1CenterY = player1Y + 10.0f;
    float player2CenterX = player2X + 10.0f;
    float player2CenterY = player2Y + 10.0f;
    float bossCenterX = bossX + boss_size;
    float bossCenterY = bossY + boss_size;
    float targetX = player1CenterX;
    float targetY = player1CenterY;

    if(mode != 1 && distance(bossCenterX, player2CenterX, bossCenterY, player2CenterY) < distance(bossCenterX, player1CenterX, bossCenterY, player1CenterY))
    {
        targetX = player2CenterX;
        targetY = player2CenterY;
    }

    float differenceX = targetX - bossCenterX;
    float differenceY = targetY - bossCenterY;
    float targetDistance = static_cast<float>(distance(bossCenterX, targetX, bossCenterY, targetY));

    if(targetDistance > 0.0f)
    {
        float moveX = differenceX / targetDistance * bossSpeed;
        float moveY = differenceY / targetDistance * bossSpeed;

        if(!mazeCollision(bossX + moveX, bossY, boss_size * 2.0f, boss_size * 2.0f))
            bossX += moveX;
        if(!mazeCollision(bossX, bossY + moveY, boss_size * 2.0f, boss_size * 2.0f))
            bossY += moveY;
    }

    bossCenterX = bossX + boss_size;
    bossCenterY = bossY + boss_size;
    bool hitPlayer1 = circleRectangleCollision(bossCenterX, bossCenterY, boss_size, player1X, player1Y, 20.0f, 20.0f);
    bool hitPlayer2 = mode != 1 && circleRectangleCollision(bossCenterX, bossCenterY, boss_size, player2X, player2Y, 20.0f, 20.0f);
    int hits = 0;

    if(hitPlayer1 && !bossTouchingPlayer1)
        hits = 1;
    if(hitPlayer2 && !bossTouchingPlayer2)
        hits = 2;
    if(hitPlayer1 && hitPlayer2)
        hits = 3;

    bossTouchingPlayer1 = hitPlayer1;
    bossTouchingPlayer2 = hitPlayer2;

    return hits;

}

double distance(float x1, float x2, float y1, float y2)
{
    double distance = sqrt(pow((x2-x1), 2) + pow((y2-y1), 2));
    return distance;
}

void initializeEnemies(int width, int length)
{
    enemySpeed = 0.25;

    for(int i = 0; i < enemyCount; i++)
    {
        enemy[i].setRadius(enemy_size);
        enemy[i].setFillColor(Color::Red);
        enemy[i].setOrigin(Vector2f(enemy_size, enemy_size));

        if(i % 4 == 0)
            enemy[i].setPosition(Vector2f((i + 1) * width / (enemyCount + 1), enemy_size));
        else if(i % 4 == 1)
            enemy[i].setPosition(Vector2f(width - enemy_size, (i + 1) * length / (enemyCount + 1)));
        else if(i % 4 == 2)
            enemy[i].setPosition(Vector2f((i + 1) * width / (enemyCount + 1), length - enemy_size));
        else
            enemy[i].setPosition(Vector2f(enemy_size, (i + 1) * length / (enemyCount + 1)));

        enemyActive[i] = true;
        enemyTouchingPlayer1[i] = false;
        enemyTouchingPlayer2[i] = false;
    }
}

void initializeGun(float speed)
{
    gunSpeed = speed;
    gunX = playerX + 10.0f;
    gunY = playerY + 10.0f;
    gunActive = false;
    gunReloading = false;
    gunTargetEnemy = -1;
    gunTargetsBoss = false;
}

void shootGun(int playerX, int playerY)
{
    if(gunActive || (gunReloading && gunReloadClock.getElapsedTime() < seconds(1.0)))
        return;

    gunX = playerX + 10.0f;
    gunY = playerY + 10.0f;
    float nearestDistance = numeric_limits<float>::max();
    gunActive = false;
    gunTargetEnemy = -1;
    gunTargetsBoss = false;

    if(bossHealth > 0)
    {
        gunTargetX = bossX + boss_size;
        gunTargetY = bossY + boss_size;
        nearestDistance = static_cast<float>(
            distance(gunX, gunTargetX, gunY, gunTargetY));
        gunTargetsBoss = true;
        gunActive = true;
    }

    for(int i = 0; i < enemyCount; i++)
    {
        if(!enemyActive[i])
            continue;

        Vector2f enemyPosition = enemy[i].getPosition();
        float targetDistance = static_cast<float>(
            distance(gunX, enemyPosition.x, gunY, enemyPosition.y));
        if(targetDistance < nearestDistance)
        {
            nearestDistance = targetDistance;
            gunTargetX = enemyPosition.x;
            gunTargetY = enemyPosition.y;
            gunTargetEnemy = i;
            gunTargetsBoss = false;
            gunActive = true;
        }
    }
}

void moveGun(RenderWindow &window)
{
    if(!gunActive)
        return;

    float targetRadius = 0.0f;
    if(gunTargetsBoss)
    {
        if(bossHealth <= 0)
        {
            gunActive = false;
            gunReloadClock.restart();
            gunReloading = true;
            return;
        }
        gunTargetX = bossX + boss_size;
        gunTargetY = bossY + boss_size;
        targetRadius = boss_size;
    }
    else
    {
        if(gunTargetEnemy < 0 || !enemyActive[gunTargetEnemy])
        {
            gunActive = false;
            gunReloadClock.restart();
            gunReloading = true;
            return;
        }
        Vector2f enemyPosition = enemy[gunTargetEnemy].getPosition();
        gunTargetX = enemyPosition.x;
        gunTargetY = enemyPosition.y;
        targetRadius = enemy_size;
    }

    float differenceX = gunTargetX - gunX;
    float differenceY = gunTargetY - gunY;
    float targetDistance = static_cast<float>(
        distance(gunX, gunTargetX, gunY, gunTargetY));

    if(targetDistance <= 0.0001f)
    {
        if(gunTargetsBoss)
            bossDamage(50);
        else
        {
            enemyActive[gunTargetEnemy] = false;
            enemyTouchingPlayer1[gunTargetEnemy] = false;
            enemyTouchingPlayer2[gunTargetEnemy] = false;
        }
        gunActive = false;
        gunReloadClock.restart();
        gunReloading = true;
        return;
    }

    float nextX = gunX + differenceX / targetDistance * gunSpeed;
    float nextY = gunY + differenceY / targetDistance * gunSpeed;

    if(!mazeCollision(nextX - 6.0f, nextY - 6.0f, 12.0f, 12.0f))
    {
        for(int i = 0; i < enemyCount; i++)
        {
            if(enemyActive[i] &&
               circlesCollision(nextX, nextY, 6.0f,
                                enemy[i].getPosition().x,
                                enemy[i].getPosition().y, enemy_size))
            {
                enemyActive[i] = false;
                enemyTouchingPlayer1[i] = false;
                enemyTouchingPlayer2[i] = false;
                gunActive = false;
                gunReloadClock.restart();
                gunReloading = true;
                return;
            }
        }

        if(bossHealth > 0 &&
           circlesCollision(nextX, nextY, 6.0f, bossX + boss_size,
                            bossY + boss_size, boss_size))
        {
            bossDamage(50);
            gunActive = false;
            gunReloadClock.restart();
            gunReloading = true;
            return;
        }

        if(targetDistance <= gunSpeed + targetRadius)
        {
            if(gunTargetsBoss)
                bossDamage(50);
            else
            {
                enemyActive[gunTargetEnemy] = false;
                enemyTouchingPlayer1[gunTargetEnemy] = false;
                enemyTouchingPlayer2[gunTargetEnemy] = false;
            }
            gunActive = false;
            gunReloadClock.restart();
            gunReloading = true;
            return;
        }

        gunX = nextX;
        gunY = nextY;

        ConvexShape diamond(4);
        diamond.setPoint(0, Vector2f(6.0f, 0.0f));
        diamond.setPoint(1, Vector2f(12.0f, 6.0f));
        diamond.setPoint(2, Vector2f(6.0f, 12.0f));
        diamond.setPoint(3, Vector2f(0.0f, 6.0f));
        diamond.setOrigin(Vector2f(6.0f, 6.0f));
        diamond.setPosition(Vector2f(gunX, gunY));
        diamond.setFillColor(Color::Yellow);
        window.draw(diamond);
    }
    else
    {
        gunActive = false;
        gunReloadClock.restart();
        gunReloading = true;
    }
}

void drawEnemies(RenderWindow &window)
{
    for(int i = 0; i < enemyCount; i++)
    {
        if(enemyActive[i])
            window.draw(enemy[i]);
    }
}

int moveEnemies(int player1X, int player1Y, int player2X, int player2Y, int mode)
{
    int hits = 0;

    for(int i = 0; i < enemyCount; i++)
    {
        if(!enemyActive[i])
            continue;

        Vector2f position = enemy[i].getPosition();
        float player1CenterX = player1X + 10.0f;
        float player1CenterY = player1Y + 10.0f;
        float player2CenterX = player2X + 10.0f;
        float player2CenterY = player2Y + 10.0f;
        bool usePlayer2 = mode != 1 && distance(position.x, player2CenterX, position.y, player2CenterY) < distance(position.x, player1CenterX, position.y, player1CenterY);
        float targetX = usePlayer2 ? player2CenterX : player1CenterX;
        float targetY = usePlayer2 ? player2CenterY : player1CenterY;
        float differenceX = targetX - position.x;
        float differenceY = targetY - position.y;
        float targetDistance = static_cast<float>(distance(position.x, targetX, position.y, targetY));

        if(targetDistance > 0.0f)
        {
            float moveX = differenceX / targetDistance * enemySpeed;
            float moveY = differenceY / targetDistance * enemySpeed;

            if(!mazeCollision(position.x - enemy_size + moveX,
                              position.y - enemy_size,
                              enemy_size * 2.0f, enemy_size * 2.0f))
                position.x += moveX;
            if(!mazeCollision(position.x - enemy_size,
                              position.y - enemy_size + moveY,
                              enemy_size * 2.0f, enemy_size * 2.0f))
                position.y += moveY;
            enemy[i].setPosition(position);
        }

        bool hitPlayer1 = circleRectangleCollision(position.x, position.y, enemy_size, player1X, player1Y, 20.0f, 20.0f);
        bool hitPlayer2 = mode != 1 &&
            circleRectangleCollision(position.x, position.y, enemy_size, player2X, player2Y, 20.0f, 20.0f);

        if(hitPlayer1 && !enemyTouchingPlayer1[i])
            hits = 1;
        if(hitPlayer2 && !enemyTouchingPlayer2[i])
            hits = 2;
        if(hitPlayer1 && hitPlayer2)
            hits = 3;

        enemyTouchingPlayer1[i] = hitPlayer1;
        enemyTouchingPlayer2[i] = hitPlayer2;
    }

    return hits;
}