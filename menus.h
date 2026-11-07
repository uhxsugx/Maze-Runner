#pragma once

#include <SFML/Graphics.hpp>


bool showMainMenu(sf::RenderWindow &window, int widths, int lengths, int &mode);
void showGameOverScreen(sf::RenderWindow &window, int width, int length);
void pauseMenu(sf::RenderWindow &window, int width, int length);