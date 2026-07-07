//
// Created by Oliver Šmítek on 07.07.2026.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "SFML/System/Clock.hpp"


class GameManager {
    public:
    GameManager();

    static GameManager& getInstance(){
        static GameManager theInstance;
        return theInstance;
    }

    sf::Clock tickClock;
    int ticks = 60;
    //def = 60
    float timeInFrames = (1.f / ticks) * 1000.f;
    long ticksAllredyMade = 0;
    bool updateOfTickRateHappend = false;

    void changeTickRateTo(int slowTimeTo);
    void resetColockForTicks();
    void addToTicksMade();
    void resetTickRateToDef();
    void updateTimeInFrames();
    void updateAnimationTimer(int &timerBetwAnim);
};



#endif //GAMEMANAGER_H
