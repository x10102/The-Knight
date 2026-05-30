//
// Created by Oliver Šmítek on 28.05.2026.
//

#ifndef PLATFORMEAG_H
#define PLATFORMEAG_H

#include "../../Managers/SpawnManager.h"
#include "../../Managers/EntityManager.h"

class Entity;

class PlatformEag : public Entity {

    public:

    void hitBoxUpdateposition() override;

    PlatformEag(sf::Vector2f position, std::string name, std::string side);

    void update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) override;

    void movmentUpdate() override;

    void drawColisionHitBox(sf::RenderWindow &window) override;

};



#endif //PLATFORMEAG_H
