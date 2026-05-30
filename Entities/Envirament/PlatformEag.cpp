//
// Created by Oliver Šmítek on 28.05.2026.
//

#include "PlatformEag.h"

PlatformEag::PlatformEag(sf::Vector2f position, std::string name, std::string side) : Entity(position, {0,0}, name) {
    colidebul = true;

    float x = 2.95f;
    float y = 2.95f;

    colisionHitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);
    if (side == "left") {
        setTexture("platformEagLeft");
    }
    else if (side == "right") {
        setTexture("platformEagRight");
    }

    this->name = name;
    scale = sf::Vector2f(x,y);

}

void PlatformEag::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    transformationSprite(currentTexture);

    movmentSinchronaz();

    movmentUpdate();
    hitBoxUpdateposition();
}


void PlatformEag::movmentUpdate() {
    position.x += velocity.x;
    position.y += velocity.y;
}


void PlatformEag::hitBoxUpdateposition() {
    colisionHitboxScale = sf::Vector2f(0.1f, 0.175f);
    colisionBoxPosition.x = position.x;
    colisionBoxPosition.y = position.y;
    colisionHitBox.setPosition(colisionBoxPosition);
}


void PlatformEag::drawColisionHitBox(sf::RenderWindow &window) {
    SpriteManager::getInstance().drawSprite(&colisionHitBox, colisionBoxPosition.x,  colisionBoxPosition.y, window);
}

