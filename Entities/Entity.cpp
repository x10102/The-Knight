//
// Created by Oliver Šmítek on 25.11.2025.
//
#include "Entity.h"
#include "../Managers/EntityManager.h"
#include <iostream>

//vytvor zasedne zkrze entitiyFactory!
Entity::Entity(sf::Vector2f position, sf::Vector2f velocity, std::string name) {
  this->position = position;
  this->velocity = velocity;

  hitBoxPosition = position;
  attackHitBoxPosition = position;


  this->name = name;
};

bool Entity::getAttackHitboxIsActive() {
  return attackHitBoxIsActive;
}
sf::Sprite *Entity::getHitbox() {
  return &hitBox;
}

sf::Sprite *Entity::getAttackHitbox() {
  return &attackHitBox;
}

bool Entity::getBoolAttackIsActive() {
  return attackHitBoxIsActive;
}

void Entity::drawEntity( sf::RenderWindow& window) {
    spriteManager->getInstance().drawSprite(&sprite, position.x,  position.y, window);
}
void Entity::drawHitbox( sf::RenderWindow &window) {};

void Entity::drawAdditions(sf::RenderWindow &window) {};

void Entity::drawColisionHitBox(sf::RenderWindow &window) {};


void Entity::setTexture(std::string newNameOfTexture) {
  spriteManager->getInstance().setTextureToSprite(newNameOfTexture,&sprite);
  currentTexture = newNameOfTexture;
}

void Entity::transformationSprite(std::string currentTexture) {
  spriteManager->getInstance().transfomration(&sprite, scale, faceingDirection, currentTexture);
  spriteManager->getInstance().hitBoxTransformation(&hitBox, hitboxScale, faceingDirection);
  spriteManager->getInstance().hitBoxTransformation(&attackHitBox, attackHitboxScale, faceingDirection);
  spriteManager->getInstance().hitBoxTransformation(&colisionHitBox, colisionHitboxScale, faceingDirection);


}

float Entity::getColisionHitBoxYOffSet() {
  return colisionHitBoxYOffSet;
}

void Entity::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {};

void Entity::cooldowns_and_unIntraptebulActions() {};

void Entity::entityFallManagment() {};


void Entity::freezEntity() {
  freez = true;
}
void Entity::unFreezEntity() {
  freez = false;
}


//Actions

void Entity::actionWalkRight() {};
void Entity::actionWalkLeft() {};
void Entity::actionJump() {};
void Entity::actionAttack() {};
void Entity::actionSlide() {};
void Entity::actionDash() {};

void Entity::transformHitBoxAttack1() {};
void Entity::transformHitBoxAttack2() {};

void Entity::passivActionStandStill() {};

void Entity::passivActionFalling() {};
void Entity::passivActionBetwenFalling() {};
void Entity::passivActionGetHit(std::string fecingDirection, int curentAttackDamage) {};

void Entity::movmentUpdate() {};
void Entity::hitBoxUpdateposition() {};
void Entity::beeingHitFunc() {}
void Entity::passivActionDie() {};
void Entity::passivActionStuck() {};

void Entity::setEntityAsInvincibul(int invincTime) {
  invincibility = true;
  invincibilityTime = invincTime;
  invincClock.restart();
}



sf::Sprite &Entity::getSpriteOfEntity() {
  return sprite;
}
void Entity::gravityAndGround(EnvironmenAndPhysicsManager &environmenAndPhysicsManage) {
  environmenAndPhysicsManage.groundeAndGravity(position, velocity, freez,ignoreFloor);
}
void Entity::rotateSprite() {
  spriteManager->getInstance().rotateSprite(&sprite, angle);
}

void Entity::colisionDetectionEntityExtention(std::string nameOfEntity) {
  entityManager->getInstance().colisionDetection(nameOfEntity);
}


sf::Vector2f Entity::getVelocity() {
  return velocity;
}

void Entity::setVelocity(sf::Vector2f newVelocity) {
  velocity = newVelocity;
}

void Entity::shadowUpdate() {}
