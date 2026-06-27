//
// Created by Oliver Šmítek on 30.04.2026.
//

#include "Platform.h"


Platform::Platform(sf::Vector2f position, std::string name) : Entity(position, {0,0}, name) {
    collidable = true;

    float x = 2.4f;
    float y = 2.4f;

    int randTextureNum = (rand() % 2) + 1;

    collisionHitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);

    setTexture("Plarform" + std::to_string(randTextureNum));

    this->name = name;
    scale = sf::Vector2f(x,y);

}


void Platform::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    transformationSprite(currentTexture);



    movmentUpdate();
    hitBoxUpdateposition();


}

void Platform::movmentUpdate() {
    position.x += velocity.x;
    position.y += velocity.y;
}


void Platform::hitBoxUpdateposition() {

    collisionHitboxScale = sf::Vector2f(0.6f, 0.175f);
    collisionBoxPosition.x = position.x;
    collisionBoxPosition.y = position.y;
    collisionHitBox.setPosition(collisionBoxPosition);

}


void Platform::drawColisionHitBox(sf::RenderWindow &window) {
    SpriteManager::getInstance().drawSprite(&collisionHitBox, collisionBoxPosition.x,  collisionBoxPosition.y, window);
}




