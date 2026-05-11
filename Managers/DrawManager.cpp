//
// Created by Oliver Šmítek on 11.05.2026.
//

#include "DrawManager.h"


void DrawManager::drawGame(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    for (auto &[nameOfEntity, entity]: entityManager->uMOfEntitys) {
        entity->drawEntity(window);
        entity->drawHitbox(window);
    }

    for (auto &[nameOfEntity, entity]: entityManager->uMOfEntitys) {

    }
}
