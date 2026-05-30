//
// Created by Oliver Šmítek on 20.01.2026.
//

#ifndef ENVIRONMENANDPHYSICSMANAGER_H
#define ENVIRONMENANDPHYSICSMANAGER_H

#include "../Managers/EnvironmenAndPhysicsManager.h"

#include "SFML/Graphics/Sprite.hpp"


class EnvironmenAndPhysicsManager {


    EnvironmenAndPhysicsManager() {}

    public:
    static EnvironmenAndPhysicsManager& getInstance(){
        static EnvironmenAndPhysicsManager theInstance;
        return theInstance;
    }

    public:

    double gravityPower = 1;
    double floor = 797;
    void gravity(sf::Vector2f &velocity, bool freez);

    void groundeAndGravity(sf::Vector2f &position, sf::Vector2f &velocity, bool freez, bool ignoreTheFloor);

    void platformGeneretion(sf::Vector2f position, std::string structure);
};



#endif //ENVIRONMENANDPHYSICSMANAGER_H
