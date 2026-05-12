//
// Created by Oliver Šmítek on 25.11.2025.
//
#include "EntityManager.h"
#include "../Entities/Entity.h"

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

void EntityManager::cornerBoolSetFalsePlayer() {

    uMOfEntitys.at("Player")->cornerBoolSetFalse();
}

void EntityManager::cornerBoolSetTruePlayer() {
    uMOfEntitys.at("Player")->position.x = 735;
    uMOfEntitys.at("Player")->cornerBoolSetTrue();
}

bool EntityManager::getCornerBool() {
    return uMOfEntitys.at("Player")->getBoolCorner();
}

bool EntityManager::getAttacIsActiveBool(std::string nameOfEntity) {
    return uMOfEntitys.at(nameOfEntity)->attackHitBoxIsActive;
}


void EntityManager::checkEntityHitBox() {

    if (!gameIsFreezd) {
        for (auto &[nameOfEntity, entityAttacking]: uMOfEntitys) {


            sf::FloatRect attackBounds = entityAttacking->getAttackHitbox().getGlobalBounds();
            std::cout << "Attack hitbox: " << attackBounds.left << ", " << attackBounds.top << ", " << attackBounds.width << ", " << attackBounds.height << std::endl;

            if (uMOfEntitys.at("Player") != entityAttacking) {
                if (uMOfEntitys.at("Player")->getAttackHitboxIsActive() && entityAttacking->getAttackHitboxIsActive()) {
                    if (entityAttacking->getAttackHitbox().getGlobalBounds().intersects(
                        uMOfEntitys.at("Player")->getAttackHitbox().getGlobalBounds())) {
                        uMOfEntitys.at("Player")->setEntityAsInvincibul(40);
                        hitEntity(entityAttacking, uMOfEntitys.at("Player"), 2);

                    }
                }
            }

            if (entityAttacking->getAttackHitboxIsActive()) {
                for (auto &[nameOfEntity, entityReseving]: uMOfEntitys) {
                    if (entityAttacking != entityReseving) {
                        bool attackIsAttacking =
                                entityReseving->getHitbox().getGlobalBounds().intersects(
                                    entityAttacking->getAttackHitbox().getGlobalBounds()
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
                std::cout << "HI" << std::endl;
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
                forceToFreez = (forceToFreez - 15) * 4;
                if (forceToFreez < 0) {
                    forceToFreez = 0;
                }
            }
        }
    }

    if (gameIsFreezd) {
        std::cout << forceToFreez << std::endl;

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

        for (auto &[nameOfEntityInMOE, entityColided]: uMOfEntitys) {
            if (entityColading->name != entityColided->name) {
                if (entityColided->colidebul == true) {

                    if (entityColading->hitBox.getPosition().x + entityColading->velocity.x <= entityColided->hitBox.getPosition().x + entityColading->hitBox.getGlobalBounds().width
                        &&
                        entityColided->hitBox.getPosition().x <= entityColading->hitBox.getPosition().x + entityColading->hitBox.getGlobalBounds().width + entityColading->velocity.x
                        )
                        {
                        }
                }
            }
        }

}
