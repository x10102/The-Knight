//
// Created by Oliver Šmítek on 14.04.2026.
//

#include "ParticalManager.h"
#include "SpawnManager.h"
#include <iostream>


void ParticalManager::spawnBloodSplash(sf::Vector2f spawnPos, std::string direction, bool kill) {

    SpawnManager::getInstance().spawnBloodSplash(spawnPos,{0,0}, direction, kill);
}
void ParticalManager::spawnHellHoundGore(sf::Vector2f spawnPos,sf::Vector2f spanwVel, std::string direction, std::string nameOfTexture) {
    SpawnManager::getInstance().spawnHellHoundGore(spawnPos,spanwVel, direction, nameOfTexture);
}
