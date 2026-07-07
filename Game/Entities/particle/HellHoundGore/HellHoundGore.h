//
// Created by Oliver Šmítek on 11.02.2026.
//

#ifndef HELLHOUNDGORE_H
#define HELLHOUNDGORE_H

#include "../../../Managers/SpawnManager.h"
#include "../../../Managers/EntityManager.h"


class Entity;

class HellHoundGore : public Entity {

public:


    HellHoundGore(sf::Vector2f position, sf::Vector2f velocity, std::string name , std::string direction, std::string nameOfTexture);

    void update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) override;

    void killParicul();

    void movmentUpdate() override;

};



#endif //HELLHOUNDGORE_H
