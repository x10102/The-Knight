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
    if (!gameIsFreezd) {
        for (auto &[nameOfEntity, entity]: uMOfEntitys) {
            entity->freeze = true;
        }
        gameIsFreezd = true;
        timerFreez.restart();
        freezTime = damage;

    }
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

    auto entityColading = uMOfEntitys.at(nameOfEntity);
    uMOfEntitys.at(nameOfEntity)->isCollidingWithPlatform = false;


    for (auto &[nameOfEntityInMOE, entityColided]: uMOfEntitys) {
        if (entityColading->name != entityColided->name) {
            if (entityColided->collidable == true) {
                if (entityColading->collisionHitBox.getPosition().y - entityColading->collisionHitBox.getGlobalBounds().height + entityColading->velocity.y <= entityColided->collisionHitBox.getPosition().y
                   &&
                   entityColided->collisionHitBox.getPosition().y - entityColided->collisionHitBox.getGlobalBounds().height <= entityColading->collisionHitBox.getPosition().y + entityColading->velocity.y) {


                    if (entityColading->collisionHitBox.getPosition().x - entityColading->collisionHitBox.getGlobalBounds().width/2 <= entityColided->collisionHitBox.getPosition().x + entityColided->collisionHitBox.getGlobalBounds().width/2
                        &&
                        entityColided->collisionHitBox.getPosition().x - entityColided->collisionHitBox.getGlobalBounds().width/2 <= entityColading->collisionHitBox.getPosition().x + entityColading->collisionHitBox.getGlobalBounds().width/2 ){

                        if ( entityColading->velocity.y > 0) {
                            entityColading->velocity.y -= EnvironmenAndPhysicsManager::getInstance().gravityPower;

                            uMOfEntitys.at(nameOfEntity)->setEntityOnFloor();
                            if (entityColading->velocity.y != 0) {
                                entityColading->lastVelocityY = entityColading->velocity.y;
                                entityColading->slideCooldown.restart();
                            }
                            entityColading->position.y = entityColided->position.y - entityColided->collisionHitBox.getGlobalBounds().height - 1;


                            entityColading->velocity.y = 0;

                            uMOfEntitys.at(nameOfEntity)->isCollidingWithPlatform = true;
                        }
                        else if (entityColading->velocity.y < 0) {
                            entityColading->velocity.y = 0;
                            entityColading->position.y = entityColided->position.y + entityColading->collisionHitBox.getGlobalBounds().height + 1;
                        }
                        }
                   }


                if (entityColading->collisionHitBox.getPosition().x - entityColading->collisionHitBox.getGlobalBounds().width/2 + entityColading->velocity.x <= entityColided->collisionHitBox.getPosition().x + entityColided->collisionHitBox.getGlobalBounds().width/2
                   &&
                   entityColided->collisionHitBox.getPosition().x - entityColided->collisionHitBox.getGlobalBounds().width/2 <= entityColading->collisionHitBox.getPosition().x + entityColading->collisionHitBox.getGlobalBounds().width/2 + entityColading->velocity.x)
                {


                    if (entityColading->collisionHitBox.getPosition().y - entityColading->collisionHitBox.getGlobalBounds().height  <= entityColided->collisionHitBox.getPosition().y
                    &&
                    entityColided->collisionHitBox.getPosition().y - entityColided->collisionHitBox.getGlobalBounds().height <= entityColading->collisionHitBox.getPosition().y   ) {

                        if (entityColading->facingDirection == "right") {
                            entityColading->velocity.x = 0;
                        }
                        if (entityColading->facingDirection == "left") {
                            entityColading->velocity.x = 0;
                        }

                    }
                }
            }

            }
        }
    }


void EntityManager::shadowColisionDetection(sf::Vector2f  &shadowPos, std::string name, sf::Vector2f positionOfPlayer) {
    for (auto &[nameOfEntityInMOE, entityColided]: uMOfEntitys) {

        if (name != entityColided->name) {
            if (entityColided->collidable == true){


                if (positionOfPlayer.y < entityColided->collisionHitBox.getPosition().y) {
                    if (shadowPos.x <= entityColided->collisionHitBox.getPosition().x + entityColided->collisionHitBox.getGlobalBounds().width/2
                        &&
                        entityColided->collisionHitBox.getPosition().x - entityColided->collisionHitBox.getGlobalBounds().width/2 <= shadowPos.x) {
                        shadowPos.y = entityColided->position.y - entityColided->collisionHitBox.getGlobalBounds().height + 4;

                        }
                }
            }
        }
    }
}





