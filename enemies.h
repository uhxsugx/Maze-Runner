#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

void initializeBoss(int width, int length);
void drawBoss(sf::RenderWindow &window);
void drawBossBar(sf::RenderWindow &window);
int bossDamage(int damage);
int getBossHealth();
int moveBoss(sf::RenderWindow &window, int player1X, int player1Y, int player2X, int player2Y, int mode);
void initializeEnemies(int width, int length);
void drawEnemies(sf::RenderWindow &window);
int moveEnemies(int player1X, int player1Y, int player2X, int player2Y, int mode);
void initializeGun(float speed);
void shootGun(int playerX, int playerY);
void moveGun(sf::RenderWindow &window, sf::Sound &bossHurtSound, sf::Sound &mummiesHurtSound,
             int player2X, int player2Y, int mode);