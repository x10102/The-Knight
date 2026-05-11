//
// Created by Oliver Šmítek on 30.04.2026.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#include "../../Managers/SpawnManager.h"
#include "../../Managers/EntityManager.h"

class Entity;

class Platform : public Entity {

    public:

    Platform(sf::Vector2f position, std::string name);

    void update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) override;

    void movmentUpdate() override;



};



#endif //PLATFORM_H
