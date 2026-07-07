//
// Created by Oliver Šmítek on 20.01.2026.
//
#include "../Managers/EnvironmenAndPhysicsManager.h"

#include <string>

#include "SpawnManager.h"


void EnvironmenAndPhysicsManager::gravity(sf::Vector2f &velocity, bool freez) {
    if (!freez) {
        velocity.y = velocity.y + gravityPower;
    }

}

void EnvironmenAndPhysicsManager::groundeAndGravity(sf::Vector2f &position, sf::Vector2f&velocity, bool freez , bool ignoreTheFloor, bool isColidingWithPlatform) {
    if (ignoreTheFloor) {
        gravity(velocity, freez);
    }
    else if (position.y + velocity.y + 1 < floor) {
        gravity(velocity, freez);
    }
    else {
        velocity.y = 0;
        position.y = floor;
    }

}

void EnvironmenAndPhysicsManager::platformGeneretion(sf::Vector2f position, std::string structure) {

    int offSetForLatform = 0;

    SpawnManager::getInstance().spawnEagOfPlatform({position.x - 89, position.y}, "left");

    for (int indexOfChar = 0; indexOfChar < structure.size(); indexOfChar++) {

        if (structure[indexOfChar] == '-') {
            SpawnManager::getInstance().spawnPlatform({offSetForLatform + position.x, position.y});
        }
        offSetForLatform += 150;
    }

    SpawnManager::getInstance().spawnEagOfPlatform({position.x + offSetForLatform - 150 + 89, position.y}, "right");

}

