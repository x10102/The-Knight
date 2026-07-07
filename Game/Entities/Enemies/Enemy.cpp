//
// Created by Oliver Šmítek on 02.07.2026.
//

#include "Enemy.h"

#include "../../Managers/EntityManager.h"

Enemy::Enemy(sf::Vector2f position, sf::Vector2f velocity, std::string name, int hp, int primeryAttackDamage, Soul* soulOfEntity) : Entity(position, velocity, name) {
    float x = 2.4f;
    float y = 2.4f;
    this->hp = hp;
    this-> primeryAttackDamage = primeryAttackDamage;
    //Set hitBox:
    trueScale = sf::Vector2f(x, y);

    soul = soulOfEntity;

    hasSoul = true;
    colisionDamage = 10;

    hitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);
    attackHitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);
    collisionHitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);

    shadow.setTexture(TextureManager::getInstance().textures["shedowOfEntity"]);


    scale = sf::Vector2f(x,y);
    facingDirection = "left";
}


sf::Vector2f Enemy::getPositionOfPlayer() {
    return EntityManager::getInstance().getPositionOfEntity("Player");
}

sf::Vector2f Enemy::getVelocityOfPlayer() {
    return EntityManager::getInstance().getVelocityOfEntity("Player");
}

