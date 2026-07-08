//
// Created by Oliver Šmítek on 14.04.2026.
//

#include "ParticalManager.h"
#include "SpawnManager.h"

void ParticalManager::spawnBloodSplash(sf::Vector2f spawnPos, Direction direction, bool kill) {

    SpawnManager::getInstance().spawnBloodSplash(spawnPos,{0,0}, direction, kill);
}
void ParticalManager::spawnHellHoundGore(sf::Vector2f spawnPos,sf::Vector2f spanwVel, Direction direction, std::string nameOfTexture) {
    SpawnManager::getInstance().spawnHellHoundGore(spawnPos,spanwVel, direction, nameOfTexture);
}
