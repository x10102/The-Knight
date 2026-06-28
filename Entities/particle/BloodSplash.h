//
// Created by Oliver Šmítek on 11.02.2026.
//

#ifndef BLOODSPLASH_H
#define BLOODSPLASH_H

#include "../../Managers/EntityManager.h"


class Entity;

class BloodSplash : public Entity {

    public:

    std::string nameOfTexture;

    BloodSplash(sf::Vector2f position, sf::Vector2f velocity, std::string name , std::string direction, bool kill);


    void update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) override;

    void cooldowns_and_unIntraptebulActions() override;

    void killParicul();

};



#endif //BLOODSPLASH_H
