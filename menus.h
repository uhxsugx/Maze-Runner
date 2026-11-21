#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

void showMainMenu(sf::RenderWindow &window, int &mode);
void showGameOverScreen(sf::RenderWindow &window);
void pauseMenu(sf::RenderWindow &window);
void winScreen(sf::RenderWindow &window);
void loadingScreen(sf::RenderWindow &window);
void Credits(sf::RenderWindow &iwndow);
