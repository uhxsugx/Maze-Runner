// Traditional Include Guard
#ifndef MY_HEADER_H
#define MY_HEADER_H

// Header content here


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

void backgroundMusic(sf::Music &music, int level);
void gunSound(sf::Sound &sound, int mode);
void damageSound(sf::Sound &sound);
void bosshurtSound(sf::Sound &sound);
void mummiesHurtSound(sf::Sound &sound);

#endif // MY_HEADER_H
