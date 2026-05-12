//
// Created by Oliver Šmítek on 11.05.2026.
//

#include "DrawManager.h"

#include <iostream>
#include <ostream>


void DrawManager::drawGame(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {

    BackGroundManager::getInstance().drawBackground(window);

    for (auto &[nameOfEntity, entity]: entityManager->getInstance().uMOfEntitys) {
        entity->drawEntity(window);
        entity->drawHitbox(window);
        entity->drawAdditions(window);
    }



}
