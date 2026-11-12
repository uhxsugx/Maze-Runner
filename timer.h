
#pragma once

#include <SFML/System/Clock.hpp>

class GameTimer
{
private:
    sf::Clock clock;
    int totalSeconds;
    bool running;

public:
    GameTimer(int seconds);

    void start();
    void reset();
    void stop();

    int getRemainingSeconds() const;
    bool isTimeUp() const;
};
