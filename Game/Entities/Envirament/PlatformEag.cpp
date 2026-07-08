//
// Created by Oliver Šmítek on 28.05.2026.
//

#include "PlatformEag.h"

PlatformEag::PlatformEag(sf::Vector2f position, std::string name, Direction side) : Entity(position, {0,0}, name) {
    collidable = true;

    float x = 2.95f;
    float y = 2.95f;

    collisionHitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);
    if (side == Direction::LEFT) {
        setTexture("platformEagLeft");
    }
    else if (side == Direction::RIGHT) {
        setTexture("platformEagRight");
    }

    this->name = name;
    scale = sf::Vector2f(x,y);

}

void PlatformEag::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    transformationSprite(currentTexture);


    movmentUpdate();
    hitBoxUpdateposition();
}


void PlatformEag::movmentUpdate() {
    position.x += velocity.x;
    position.y += velocity.y;
}


void PlatformEag::hitBoxUpdateposition() {
    collisionHitboxScale = sf::Vector2f(0.1f, 0.175f);
    collisionBoxPosition.x = position.x;
    collisionBoxPosition.y = position.y;
    collisionHitBox.setPosition(collisionBoxPosition);
}


void PlatformEag::drawColisionHitBox(sf::RenderWindow &window) {
    SpriteManager::getInstance().drawSprite(&collisionHitBox, collisionBoxPosition.x,  collisionBoxPosition.y, window);
}

