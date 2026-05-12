//
// Created by Oliver Šmítek on 11.02.2026.
//

#include "HellHound.h"

#include <iostream>

#include "../../cmake-build-debug/_deps/sfml-src/extlibs/headers/glad/include/glad/gl.h"


HellHound::HellHound(sf::Vector2f position, sf::Vector2f velocity, std::string name) : Entity(position, velocity, name) {
    float x = 2.4f;
    float y = 2.4f;

    //Set hitBox:
    sf::Texture hitboxTexture;

    colisionDamage = 10;

    hitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);
    attackHitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);


    scale = sf::Vector2f(x,y);
    faceingDirection = "left";

}


void HellHound::cooldowns_and_unIntraptebulActions() {
    //cooldawns:

    //attack Cooldawn:
    srand(time(0));
    // Generate a random number between 0 and 100
    int randomNum = rand() % 201 + 1100;


    if(cooldownJump.getElapsedTime().asMilliseconds() >= randomNum) {
        cooldownIsOffJump = true;
    }
    if (retritingTimer.getElapsedTime().asMilliseconds() >= randomNum) {
        reatriting = false;
    }

    if (invincClock.getElapsedTime().asMilliseconds() >= invincibilityTime) {
        invincibility = false;
    }


    if (unIntaraptebulAnimation) {
        if (spriteManager->getInstance().getIndexOfAnimation(&sprite) >= spriteManager->getInstance().getMaxIndexOfAnimation(&sprite) - 64) {
            unIntaraptebulAnimation = false;
            attackHitBoxIsActive = false;
            if (faceingDirection == "left") {
                actionWalkLeft();
            }
            else if (faceingDirection == "right") {
                actionWalkRight();
            }
            attackCooldawn.restart();
        }
    }
}

void HellHound::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    if (!freez) {
        beeingHitFunc();
        hellHoundAI();
    }
    hitBoxUpdateposition();
    if (!freez) {
        transformationSprite(currentTexture);
    }
    entityFallManagment();
    movmentSinchronaz();
    if (!freez) {
        cooldowns_and_unIntraptebulActions();
    }
    gravityAndGround(environmenAndPhysicsManager);
    if (!freez) {
        movmentUpdate();
    }

}

void HellHound::passivActionStandStill() {
    if (!unIntaraptebulAnimation) {
        setTexture("HellHoundIdle");
        velocity.x = 0;
    }
}

void HellHound::actionWalkRight() {
    if (!unIntaraptebulAnimation) {
        setTexture("HellHoundRun");

        faceingDirection = "right";
        velocity.x = -11;
    }

}

void HellHound::actionWalkLeft() {
    if (!unIntaraptebulAnimation) {
        setTexture("HellHoundRun");

        faceingDirection = "left";
        velocity.x = 11;
    }
}


void HellHound::entityFallManagment() {
    if (position.y + velocity.y + 1 < 704) {
        isInAir = true;
    }
    else {
        isInAir = false;
    }
}


void HellHound::transformHitBoxAttack1() {
    currentAttack = attackBite;
    attackHitBoxIsActive = true;
}

void HellHound::actionJumpAttack() {


    if (!unIntaraptebulAnimation) {
        if (faceingDirection == "left") {
            velocity.x = 20;
        }
        else {
            velocity.x = -20;
        }
        if (!isInAir) {
            setTexture("HellHoundJump");
            velocity.y = -7;
        }


        transformHitBoxAttack1();
        unIntaraptebulAnimation = true;
        cooldownIsOffJump = false;
        cooldownJump.restart();
    }

}


sf::Vector2f HellHound::getPositionOfPlayer() {
    return entityManager->getInstance().getPositionOfEntity("Player");
}

sf::Vector2f HellHound::getVelocityOfPlayer(EntityManager &entityManager) {
    return entityManager.getVelocityOfEntity("Player");
}


void HellHound::beeingHitFunc() {

        if (gotHit) {
            if (beeingHit.getElapsedTime().asMilliseconds() <= beeingHitPlayerIntervalHellHound) {

                spriteManager->getInstance().markTextureAsHit(&sprite);
            }
            else {
                spriteManager->getInstance().markTextureAsNormal(&sprite);

                gotHit = false;
            }
        }
}

void HellHound::passivActionGetHit(std::string fecingDirection, int damage) {
        if (!freez) {
            if (!gotHit) {
                ParticalManager::getInstance().spawnBloodSplash({position.x ,position.y + 30}, fecingDirection, false);

                attackHitBoxIsActive = false;
                unIntaraptebulAnimation = false;
                setTexture("HellHoundHit");
                if (fecingDirection == "right") {
                    velocity.x = 0;
                }
                else if (fecingDirection == "left") {
                    velocity.x = 0;
                }
                beeingHit.restart();
                reatriting = true;
                gotHit = true;

                hp = hp - damage;

                if (hp <= 0) {
                    passivActionDie();
                }
            }
        }
}

void HellHound::passivActionDie() {
    ParticalManager::getInstance().spawnBloodSplash({position.x,position.y + 20}, faceingDirection, true);

    sf::Vector2f velocityGore = {0,0};
    if (faceingDirection == "left") {
        velocityGore.x = -4;
    }
    else {
        velocityGore.x = 4;
    }

    ParticalManager::getInstance().spawnHellHoundGore({position.x - 40,position.y},{static_cast<float>(velocity.x + velocityGore.x * 1.2),velocity.y- 3},faceingDirection, "GoreHellHound2");
    ParticalManager::getInstance().spawnHellHoundGore({position.x + 10,position.y},{static_cast<float>(velocity.x + velocityGore.x * 1.2),velocity.y - 2},faceingDirection, "GoreHellHound5");
    ParticalManager::getInstance().spawnHellHoundGore({position.x,position.y + 5},{static_cast<float>(velocity.x + velocityGore.x * 1.2),velocity.y - 2},faceingDirection, "GoreHellHound1");



    entityManager->getInstance().killEntity(name,this);
}



void HellHound::hellHoundAI() {
        sf::Vector2f playrPos = getPositionOfPlayer();

        if (cooldownIsOffJump) {
            if (playrPos.x > position.x + 200) {
                actionWalkLeft();
            }
            else if(playrPos.x < position.x - 200){
                actionWalkRight();
            }
            else  {
                actionJumpAttack();
            }
        }
        else if (reatriting) {
            if (playrPos.x < position.x) {
                actionWalkLeft();
            }
            else if(playrPos.x > position.x){
                actionWalkRight();
            }
        }

}



void HellHound::hitBoxUpdateposition() {

    if (currentTexture == "HellHoundJump") {
        hitboxScale = sf::Vector2f(0.25f,0.3f);
        if (faceingDirection == "right") {
            hitBoxPosition.x = position.x - 10;

        }
        else if (faceingDirection == "left") {
            hitBoxPosition.x = position.x + 10;
        }
        hitBoxPosition.y = position.y + 20;
    }
    else {
        hitboxScale = sf::Vector2f(0.25f,0.3f);
        if (faceingDirection == "right") {
            hitBoxPosition.x = position.x - 10;

        }
        else if (faceingDirection == "left") {
            hitBoxPosition.x = position.x + 10;
        }
        hitBoxPosition.y = position.y + 50;
    }

    if (currentTexture == "HellHoundJump") {
        attackHitboxScale = sf::Vector2f(0.32f,0.3f);
        if (faceingDirection == "right") {
            attackHitBoxPosition.x = position.x - 35;

        }
        else if (faceingDirection == "left") {
            attackHitBoxPosition.x = position.x + 35;
        }
        attackHitBoxPosition.y = position.y + 30;
    }


}



void HellHound::movmentUpdate() {
    position.x += velocity.x;
    position.y += velocity.y;

}


void HellHound::drawHitbox(sf::RenderWindow &window) {
        spriteManager->getInstance().drawSprite(&hitBox, hitBoxPosition.x,  hitBoxPosition.y, window);

        if (attackHitBoxIsActive) {
            spriteManager->getInstance().drawSprite(&attackHitBox, attackHitBoxPosition.x,  attackHitBoxPosition.y, window);
        }
}
