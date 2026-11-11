#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void backgroundMusic(Music &music, int level)
{
    music.stop();

    if(level == 1 || level == 0)
    {
        if(!music.openFromFile("data/music/Bellhart.mp3"))
        {
            cout << "Nah lol1" << endl;
            return;
        }
    }

    if(level == 2)
    {
        if(!music.openFromFile("data/music/High-Halls.mp3"))
        {
            cout << "Nah lol2" << endl;
            return;
        }
    }
    
    if(level == 3)
    {
        if(!music.openFromFile("data/music/Choral-Chambers.mp3"))
        {
            cout << "Nah lol3" << endl;
            return;
        }
    }
    
    if(level == 4)
    {
        if(!music.openFromFile("data/music/Gestral-Party.mp3"))
        {   cout << "Nah lol4" << endl;
            return;
        }
    }
    if(level == 5)
    {
        if(!music.openFromFile("data/music/Devola&Popola.mp3"))
        {
            cout << "Nah lol5" << endl;
            return;
        }
    }
    music.setLooping(true);
    music.setVolume(15.0);
    music.play();
}

void gunSound(Sound &sound, int mode)
{
    bool shoot = Keyboard::isKeyPressed(Keyboard::Key::Q);

    if(mode == 2)
    {
        shoot = shoot || Keyboard::isKeyPressed(Keyboard::Key::RShift) || Keyboard::isKeyPressed(Keyboard::Key::LShift);
    }

    sound.setVolume(50.0);
    if(shoot  && sound.getStatus() != Sound::Status::Playing)
        sound.play();
}

void damageSound(Sound &sound)
{
    
    sound.setVolume(75.0);
    if(sound.getStatus() != Sound::Status::Playing)
        sound.play();
}

void idleSound(Sound &sound)
{
    sound.setVolume(50.0);
    if(sound.getStatus() != Sound::Status::Playing)
        sound.play();
}

void bosshurtSound(Sound &sound)
{
    sound.setVolume(25.0);
    //if(sound.getStatus() != Sound::Status::Playing)
        sound.play();
}

void mummiesHurtSound(Sound &sound)
{
    sound.setVolume(50.0);
    //if(sound.getStatus() != Sound::Status::Playing)
        sound.play();
}