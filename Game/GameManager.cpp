//
// Created by Oliver Šmítek on 07.07.2026.
//

#include "GameManager.h"

#include "Managers/SpriteManager.h"

GameManager::GameManager() {}

void GameManager::changeTickRateTo(int slowTimeTo) {
    if (ticks != slowTimeTo) {
        ticks = slowTimeTo;
        updateTimeInFrames();
        updateAnimationTimer(SpriteManager::getInstance().intervalBetwenAnimations);
    }

}

void GameManager::resetColockForTicks() {
    tickClock.restart();
}

void GameManager::addToTicksMade() {
    ticksAllredyMade++;
}
void GameManager::resetTickRateToDef() {
    ticks = 60;
}
void GameManager::updateTimeInFrames() {
    timeInFrames = (1.f / ticks) * 1000.f;
}
void GameManager::updateAnimationTimer(int &timerBetwAnim) {
    timerBetwAnim = timerBetwAnim * (timeInFrames / 16);
    std::cout << "Time in frames: " << timerBetwAnim << std::endl;
}