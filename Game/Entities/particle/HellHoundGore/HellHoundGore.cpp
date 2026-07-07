//
// Created by Oliver Šmítek on 24.04.2026.
//

#include "HellHoundGore.h"

HellHoundGore::HellHoundGore(sf::Vector2f position, sf::Vector2f velocity, std::string name,std::string direction, std::string textureName) : Entity(position, velocity, name) {
    float x = 2.4f;
    float y = 2.4f;

    ignoreFloor = true;

    setTexture(textureName);

    this->name = name;
    scale = sf::Vector2f(x,y);

    facingDirection = direction;
}

void HellHoundGore::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    transformationSprite(currentTexture);
    gravityAndGround(environmenAndPhysicsManager);


    rotateSprite();

    movmentUpdate();

}

void HellHoundGore::killParicul() {
    entityManager->getInstance().killEntity(name, this);
}

void HellHoundGore::movmentUpdate() {
    if (!freeze) {
        angle = angle + 5;
        position.x += velocity.x;
        position.y += velocity.y;
    }
}


