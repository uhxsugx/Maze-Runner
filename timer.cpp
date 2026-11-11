
#include "timer.h"

GameTimer::GameTimer(int seconds)
{
    totalSeconds = seconds;
    running = false;
}

void GameTimer::start()
{
    if (!running)
    {
        clock.start();
        running = true;
    }
}

void GameTimer::reset()
{
    clock.reset();
    running = false;
}

void GameTimer::stop()
{
    clock.stop();
    running = false;
}

int GameTimer::getRemainingSeconds() const
{
    int elapsed = static_cast<int>(
        clock.getElapsedTime().asSeconds()
        );

    int remaining = totalSeconds - elapsed;

    if (remaining < 0)
    {
        return 0;
    }

    return remaining;
}

bool GameTimer::isTimeUp() const
{
    return getRemainingSeconds() == 0;
}
