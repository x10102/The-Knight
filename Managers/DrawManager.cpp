//
// Created by Oliver Šmítek on 11.05.2026.
//

#include "DrawManager.h"

#include <iostream>
#include <ostream>


void DrawManager::drawGame(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {

    BackGroundManager::getInstance().drawBackground(window);

    auto &entities = EntityManager::getInstance().uMOfEntitys;

    for (auto it = entities.rbegin(); it != entities.rend(); ++it) {
        auto &[nameOfEntity, entity] = *it;

        entity->drawEntity(window);
        entity->drawHitbox(window);
        entity->drawColisionHitBox(window);
        entity->drawAdditions(window);
    }


}
