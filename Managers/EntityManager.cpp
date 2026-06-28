//
// Created by Oliver Šmítek on 25.11.2025.
//
#include "EntityManager.h"
#include "../Entities/Entity.h"
#include "../Managers/EnvironmenAndPhysicsManager.h"
#include <cmath>


void EntityManager::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {

    for (auto &[nameOfEntity, entity]: uMOfEntitys) {
        entity->update(window, environmenAndPhysicsManager);
    }
    checkEntityHitBox();
    chackHowLongToFreez();
    SpriteManager::getInstance().resetAnimationTimer();
    killEntities();

}

sf::Vector2f EntityManager::getPositionOfEntity(std::string nameOfEntity) {
    return uMOfEntitys.at(nameOfEntity)->position;
}

sf::Vector2f EntityManager::getVelocityOfEntity(std::string nameOfEntity) {
    return uMOfEntitys.at(nameOfEntity)->getVelocity();
}


bool EntityManager::getAttacIsActiveBool(std::string nameOfEntity) {
    return uMOfEntitys.at(nameOfEntity)->attackHitBoxIsActive;
}

void EntityManager::checkEntityHitBox() {
    for (auto &[nameOfEntity, entityAttacking]: uMOfEntitys) {
        if (uMOfEntitys.at("Player") != entityAttacking) {
            if (uMOfEntitys.at("Player")->getAttackHitboxIsActive() && entityAttacking->getAttackHitboxIsActive()) {
                if (entityAttacking->getAttackHitbox()->getGlobalBounds().intersects(
                    uMOfEntitys.at("Player")->getAttackHitbox()->getGlobalBounds())) {
                    uMOfEntitys.at("Player")->setEntityAsInvincibul(40);
                    hitEntity(entityAttacking, uMOfEntitys.at("Player"), 2);
                }
            }
        }

        if (entityAttacking->getAttackHitboxIsActive()) {
            for (auto &[nameOfEntitySacend, entityReseving]: uMOfEntitys) {
                if (entityAttacking != entityReseving) {
                    bool attackIsAttacking =
                            entityReseving->getHitbox()->getGlobalBounds().intersects(
                                entityAttacking->getAttackHitbox()->getGlobalBounds()
                            );

                    if (attackIsAttacking) {
                        hitEntity(entityReseving, entityAttacking, 1);
                    }
                }
            }
        }
    }

}


void EntityManager::hitEntity(Entity *entityRes, Entity *entityAttacking, int parryMulitplayer) {
    int damage = entityAttacking->currentAttack;
    sf::Sprite spriteOfKnight = uMOfEntitys.at("Player")->sprite;
    std::string currentTexture = uMOfEntitys.at("Player")->currentTexture;
    int sizeOftexture = spriteOfKnight.getTexture()->getSize().x;

    if (entityAttacking->name == "Player") {
        sf::Vector2f velocityOfPlayer = entityAttacking->velocity;
        int force = velocityOfPlayer.x + velocityOfPlayer.y;

        force = 1 + std::abs(force / 15);
        damage = std::round((damage * force) * parryMulitplayer);

        if (spriteOfKnight.getTextureRect().left >= sizeOftexture /5) {
            entityRes->passivActionGetHit(entityAttacking->facingDirection, damage);
            if (damage > 30) {
                freezTheGame(damage * 2);
            }
        }

    } else {
        entityRes->passivActionGetHit(entityAttacking->facingDirection, damage);
    }
}

void EntityManager::freezTheGame(int damage) {
    if(gameIsFreezd) return;

    for (auto &[nameOfEntity, entity]: uMOfEntitys) {
        entity->freeze = true;
    }
    gameIsFreezd = true;
    timerFreez.restart();
    freezTime = damage;
}

void EntityManager::unFreezTheGame() {
    for (auto &[nameOfEntity, entity]: uMOfEntitys) {
        entity->freeze = false;
    }
    gameIsFreezd = false;
}

void EntityManager::chackHowLongToFreez() {
    if (gameIsFreezd) {
        if (timerFreez.getElapsedTime().asMilliseconds() > freezTime) {
            unFreezTheGame();
        }
    }
}

sf::Sprite *EntityManager::getSpriteOfEntity(std::string nameOfEntity) {
    return &uMOfEntitys.at(nameOfEntity)->getSpriteOfEntity();
}


void EntityManager::killEntity(std::string nameOfEntity, Entity *entityToKill) {
    uMOfEntitysToKill[nameOfEntity] = entityToKill;
}

void EntityManager::killEntities() {
    for (auto &[name, entityPtr]: uMOfEntitysToKill) {
        auto it = uMOfEntitys.find(name);
        if (it != uMOfEntitys.end()) {
            delete it->second; // uvolní paměť entity
            uMOfEntitys.erase(it);
        }
    }
    uMOfEntitysToKill.clear();
}




void EntityManager::colisionDetection(std::string nameOfEntity) {

    auto collidingEntity = uMOfEntitys.at(nameOfEntity);
    uMOfEntitys.at(nameOfEntity)->isCollidingWithPlatform = false;


    for (auto &[nameOfEntityInMOE, collidedEntity]: uMOfEntitys) {

        // Entity can't collide with itself
        if(collidingEntity->name.compare(collidedEntity->name) == 0) continue;

        // Can't collide with intangible entity
        if(collidedEntity->collidable == false) continue;

        auto &collidingHitbox = collidingEntity->collisionHitBox;
        auto &collidedHitbox = collidedEntity->collisionHitBox;

        if (collidingHitbox.getPosition().y - collidingHitbox.getGlobalBounds().height + collidingEntity->velocity.y <= collidedHitbox.getPosition().y
            &&
            collidedHitbox.getPosition().y - collidedHitbox.getGlobalBounds().height <= collidingHitbox.getPosition().y + collidingEntity->velocity.y) {


            if (collidingHitbox.getPosition().x - collidingHitbox.getGlobalBounds().width/2 <= collidedHitbox.getPosition().x + collidedHitbox.getGlobalBounds().width/2
                &&
                collidedHitbox.getPosition().x - collidedHitbox.getGlobalBounds().width/2 <= collidingHitbox.getPosition().x + collidingHitbox.getGlobalBounds().width/2 ){

                if ( collidingEntity->velocity.y > 0) {
                    collidingEntity->velocity.y -= EnvironmenAndPhysicsManager::getInstance().gravityPower;

                    uMOfEntitys.at(nameOfEntity)->setEntityOnFloor();
                    if (collidingEntity->velocity.y != 0) {
                        collidingEntity->lastVelocityY = collidingEntity->velocity.y;
                        collidingEntity->slideCooldown.restart();
                    }
                    collidingEntity->position.y = collidedEntity->position.y - collidedEntity->collisionHitBox.getGlobalBounds().height - 1;


                    collidingEntity->velocity.y = 0;

                    uMOfEntitys.at(nameOfEntity)->isCollidingWithPlatform = true;
                }
                else if (collidingEntity->velocity.y < 0) {
                    collidingEntity->velocity.y = 0;
                    collidingEntity->position.y = collidedEntity->position.y + collidingEntity->collisionHitBox.getGlobalBounds().height + 1;
                }
            }
        }


        if (collidingHitbox.getPosition().x - collidingHitbox.getGlobalBounds().width/2 + collidingEntity->velocity.x <= collidedHitbox.getPosition().x + collidedHitbox.getGlobalBounds().width/2
            &&
            collidedHitbox.getPosition().x - collidedHitbox.getGlobalBounds().width/2 <= collidingHitbox.getPosition().x + collidingHitbox.getGlobalBounds().width/2 + collidingEntity->velocity.x)
        {


            if (collidingHitbox.getPosition().y - collidingHitbox.getGlobalBounds().height <= collidedHitbox.getPosition().y
            &&
            collidedHitbox.getPosition().y - collidedHitbox.getGlobalBounds().height <= collidingHitbox.getPosition().y) {

               collidingEntity->velocity.x = 0;

            }
        }
    }

}


void EntityManager::shadowColisionDetection(sf::Vector2f  &shadowPos, std::string name, sf::Vector2f positionOfPlayer) {
    for (auto &[nameOfEntityInMOE, entityColided]: uMOfEntitys) {

        // Can't collide with itself
        if(name.compare(entityColided->name) == 0) continue;

        // Can't collide with intangible entity
        if(entityColided->collidable == false) continue;

        if (positionOfPlayer.y >= entityColided->collisionHitBox.getPosition().y) continue;
        
        if (shadowPos.x <= entityColided->collisionHitBox.getPosition().x + entityColided->collisionHitBox.getGlobalBounds().width/2
            &&
            entityColided->collisionHitBox.getPosition().x - entityColided->collisionHitBox.getGlobalBounds().width/2 <= shadowPos.x) {
            shadowPos.y = entityColided->position.y - entityColided->collisionHitBox.getGlobalBounds().height + 4;

            }
        }
}





