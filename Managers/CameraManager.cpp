//
// Created by Oliver Šmítek on 30.05.2026.
//

#include "CameraManager.h"

#include "EntityManager.h"
#include "../Entities/Entity.h"

CameraManager::CameraManager() {

}


void CameraManager::CameraUpdate(sf::RenderWindow& window) {
    float posOfPlayerX = EntityManager::getInstance().uMOfEntitys.at("Player")->position.x;
    view = sf::View(sf::FloatRect({posOfPlayerX, 0.f}, {window.getView().getSize().x, window.getView().getSize().y}));
}