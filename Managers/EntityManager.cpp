//
// Created by Oliver Šmítek on 25.11.2025.
//
#include "EntityManager.h"
#include "../Entities/Entity.h"
#include "../Managers/EnvironmenAndPhysicsManager.h"


#include <iostream>


void EntityManager::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {

    for (auto &[nameOfEntity, entity]: uMOfEntitys) {
        entity->update(window, environmenAndPhysicsManager);
    }
    checkEntityHitBox();
    freezingGame();
    spriteManager->getInstance().resetAnimationTimer();
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

    if (!gameIsFreezd) {
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
                for (auto &[nameOfEntity, entityReseving]: uMOfEntitys) {
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
}


void EntityManager::hitEntity(Entity *entityRes, Entity *entityAttacking, int parryMulitplayer) {
    int damage = entityAttacking->currentAttack;

    if (entityAttacking->name == "Player") {
        if (!attacked) {
            sf::Vector2f velocityOfPlayer = entityAttacking->velocity;
            int force = velocityOfPlayer.x + velocityOfPlayer.y;

            force = 1 + std::abs(force / 15);

            damage = std::round((damage * force) * parryMulitplayer);
            if (gameCanBeFreezd.getElapsedTime().asMilliseconds() >= intervalToFreez) {
                preperToFreezGame(damage, entityRes, entityAttacking->faceingDirection, entityAttacking);
                attacked = true;
            }
        }
    } else {
        entityRes->passivActionGetHit(entityAttacking->faceingDirection, damage);
    }
}

void EntityManager::preperToFreezGame(int force, Entity *entityRese, std::string direc, Entity *entityAttack) {
    fecingDirectionOfAttackingEntity = direc;
    entityRes = entityRese;
    goFreezTheGame = true;
    forceToFreez = force;
    entityAtc = entityAttack;
}

sf::Sprite *EntityManager::getSpriteOfEntity(std::string nameOfEntity) {
    return &uMOfEntitys.at(nameOfEntity)->getSpriteOfEntity();
}

void EntityManager::freezingGame() {
    if (goFreezTheGame) {
        if (!gameIsFreezd) {
            if (spriteManager->getInstance().getIndexOfAnimation(getSpriteOfEntity("Player")) >=
                spriteManager->getInstance().getMaxIndexOfAnimation(getSpriteOfEntity("Player")) / 4) {
                entityRes->passivActionGetHit(fecingDirectionOfAttackingEntity, forceToFreez);
                gameFreez();
                attacked = false;
                forceToFreez = (forceToFreez - 15) * 3;
                if (forceToFreez < 0) {
                    forceToFreez = 0;
                }
            }
        }
    }

    if (gameIsFreezd) {

        if (gameIsFreezdClock.getElapsedTime().asMilliseconds() >= forceToFreez) {
            unFreezGame();
            gameCanBeFreezd.restart();
        } else {
        }
    }
}


void EntityManager::gameFreez() {
    for (auto &[nameOfEntity, entity]: uMOfEntitys) {
        entity->freezEntity();
    }
    gameIsFreezd = true;
    gameIsFreezdClock.restart();
}

void EntityManager::unFreezGame() {
    for (auto &[nameOfEntity, entity]: uMOfEntitys) {
        entity->unFreezEntity();
        entity->beeingHit.restart();
    }
    gameIsFreezd = false;
    goFreezTheGame = false;
}

void EntityManager::killEntity(std::string nameOfEntity, Entity *entityToKill) {
    uMOfEntitysToKill[nameOfEntity] = entityToKill;
}

void EntityManager::killEntities() {
    if (!gameIsFreezd) {
        for (auto &[name, entityPtr]: uMOfEntitysToKill) {
            auto it = uMOfEntitys.find(name);
            if (it != uMOfEntitys.end()) {
                delete it->second; // uvolní paměť entity
                uMOfEntitys.erase(it);
            }
        }
        uMOfEntitysToKill.clear();
    }
}

bool EntityManager::getFreezEntity(std::string nameOfEntity) {
    return uMOfEntitys.at(nameOfEntity)->freez;
}


void EntityManager::colisionDetection(std::string nameOfEntity) {

    auto entityColading = uMOfEntitys.at(nameOfEntity);
    uMOfEntitys.at(nameOfEntity)->isColidingWithAPlatform = false;


    for (auto &[nameOfEntityInMOE, entityColided]: uMOfEntitys) {
        if (entityColading->name != entityColided->name) {
            if (entityColided->colidebul == true) {
                if (entityColading->colisionHitBox.getPosition().y - entityColading->colisionHitBox.getGlobalBounds().height + entityColading->velocity.y <= entityColided->colisionHitBox.getPosition().y
                   &&
                   entityColided->colisionHitBox.getPosition().y - entityColided->colisionHitBox.getGlobalBounds().height <= entityColading->colisionHitBox.getPosition().y + entityColading->velocity.y) {


                    if (entityColading->colisionHitBox.getPosition().x - entityColading->colisionHitBox.getGlobalBounds().width/2 <= entityColided->colisionHitBox.getPosition().x + entityColided->colisionHitBox.getGlobalBounds().width/2
                        &&
                        entityColided->colisionHitBox.getPosition().x - entityColided->colisionHitBox.getGlobalBounds().width/2 <= entityColading->colisionHitBox.getPosition().x + entityColading->colisionHitBox.getGlobalBounds().width/2 ){

                        if ( entityColading->velocity.y > 0) {
                            entityColading->velocity.y -= EnvironmenAndPhysicsManager::getInstance().gravityPower;


                            uMOfEntitys.at(nameOfEntity)->isInAir = false;
                            uMOfEntitys.at(nameOfEntity)->isFalling = false;
                            if (entityColading->velocity.y != 0) {
                                entityColading->lastVelocytyY = entityColading->velocity.y;
                                entityColading->slideCooldawn.restart();
                            }
                            entityColading->position.y = entityColided->position.y - entityColided->colisionHitBox.getGlobalBounds().height - 1;


                            entityColading->velocity.y = 0;

                            uMOfEntitys.at(nameOfEntity)->isColidingWithAPlatform = true;
                        }
                        else if (entityColading->velocity.y < 0) {
                            entityColading->velocity.y = 0;
                            entityColading->position.y = entityColided->position.y + entityColading->colisionHitBox.getGlobalBounds().height + 1;


                        }
                        }



                   }


                if (entityColading->colisionHitBox.getPosition().x - entityColading->colisionHitBox.getGlobalBounds().width/2 + entityColading->velocity.x <= entityColided->colisionHitBox.getPosition().x + entityColided->colisionHitBox.getGlobalBounds().width/2
                   &&
                   entityColided->colisionHitBox.getPosition().x - entityColided->colisionHitBox.getGlobalBounds().width/2 <= entityColading->colisionHitBox.getPosition().x + entityColading->colisionHitBox.getGlobalBounds().width/2 + entityColading->velocity.x)
                {


                    if (entityColading->colisionHitBox.getPosition().y - entityColading->colisionHitBox.getGlobalBounds().height  <= entityColided->colisionHitBox.getPosition().y
                    &&
                    entityColided->colisionHitBox.getPosition().y - entityColided->colisionHitBox.getGlobalBounds().height <= entityColading->colisionHitBox.getPosition().y   ) {

                        if (entityColading->faceingDirection == "right") {
                            entityColading->velocity.x = 0;
                        }
                        if (entityColading->faceingDirection == "left") {
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
            if (entityColided->colidebul == true){


                if (positionOfPlayer.y < entityColided->colisionHitBox.getPosition().y) {
                    if (shadowPos.x <= entityColided->colisionHitBox.getPosition().x + entityColided->colisionHitBox.getGlobalBounds().width/2
                        &&
                        entityColided->colisionHitBox.getPosition().x - entityColided->colisionHitBox.getGlobalBounds().width/2 <= shadowPos.x) {
                        shadowPos.y = entityColided->position.y - entityColided->colisionHitBox.getGlobalBounds().height + 4;

                        }
                }
            }
        }
    }
}





