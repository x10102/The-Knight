//
// Created by Oliver Šmítek on 11.02.2026.
//

#include "HellHound.h"

#include <iostream>


HellHound::HellHound(sf::Vector2f position, sf::Vector2f velocity, std::string name) : Entity(position, velocity, name) {
    float x = 2.4f;
    float y = 2.4f;

    //Set hitBox:

    colisionDamage = 10;

    hitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);
    attackHitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);
    colisionHitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);

    shadow.setTexture(TextureManager::getInstance().textures["shedowOfEntity"]);


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
    if (!freez) {
        transformationSprite(currentTexture);
    }

    entityFallManagment();


    if (!freez) {
        cooldowns_and_unIntraptebulActions();
    }

    gravityAndGround(environmenAndPhysicsManager);


    hitBoxUpdateposition();
    colisionDetectionEntityExtention(name);


    if (!freez) {
        movmentUpdate();
    }
    shadowUpdate();


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
    if (position.y + velocity.y + 1 < EnvironmenAndPhysicsManager::getInstance().floor) {
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
            velocity.x = 12;
        }
        else {
            velocity.x = -12;
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
                ParticalManager::getInstance().spawnBloodSplash({position.x ,position.y -40}, fecingDirection, false);
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
    ParticalManager::getInstance().spawnBloodSplash({position.x,position.y + 15}, faceingDirection, true);

    sf::Vector2f velocityGore = {0,0};
    if (faceingDirection == "left") {
        velocityGore.x = -5;
    }
    else {
        velocityGore.x = 5;
    }
    velocityGore.y = -5;


    ParticalManager::getInstance().spawnHellHoundGore({position.x - 40,position.y - 48},{static_cast<float>(velocity.x + velocityGore.x * 1.2),velocity.y- 3},faceingDirection, "GoreHellHound2");
    ParticalManager::getInstance().spawnHellHoundGore({position.x + 10,position.y - 40},{static_cast<float>(velocity.x + velocityGore.x * 1.2),velocity.y - 2},faceingDirection, "GoreHellHound5");
    ParticalManager::getInstance().spawnHellHoundGore({position.x,position.y - 42},{static_cast<float>(velocity.x + velocityGore.x * 1.2),velocity.y - 2},faceingDirection, "GoreHellHound1");



    entityManager->getInstance().killEntity(name,this);
}



void HellHound::hellHoundAI() {
        sf::Vector2f playrPos = getPositionOfPlayer();

        if (cooldownIsOffJump) {
            if (playrPos.x > position.x + 150) {
                actionWalkLeft();
            }
            else if(playrPos.x < position.x - 150){
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
        hitboxScale = sf::Vector2f(0.35f,0.3f);
        if (faceingDirection == "right") {
            hitBoxPosition.x = position.x - 10;

        }
        else if (faceingDirection == "left") {
            hitBoxPosition.x = position.x + 10;
        }
        hitBoxPosition.y = position.y;

        colisionHitboxScale = sf::Vector2f(0.1f, 0.4f);
        colisionBoxPosition.x = position.x;
        colisionBoxPosition.y = position.y;

    }
    else {
        hitboxScale = sf::Vector2f(0.35f,0.3f);
        if (faceingDirection == "right") {
            hitBoxPosition.x = position.x + 5;
        }
        else if (faceingDirection == "left") {
            hitBoxPosition.x = position.x - 5;
        }
        hitBoxPosition.y = position.y;


        colisionHitboxScale = sf::Vector2f(0.1f, 0.4f);
        colisionBoxPosition.x = position.x;
        colisionBoxPosition.y = position.y;



    }

    if (currentTexture == "HellHoundJump") {
        attackHitboxScale = sf::Vector2f(0.25f,0.28f);
        if (faceingDirection == "right") {
            attackHitBoxPosition.x = position.x - 35;

        }
        else if (faceingDirection == "left") {
            attackHitBoxPosition.x = position.x + 35;
        }
        attackHitBoxPosition.y = position.y;
    }


    colisionHitBox.setPosition(colisionBoxPosition);
    hitBox.setPosition(hitBoxPosition);
    attackHitBox.setPosition(attackHitBoxPosition);
}



void HellHound::movmentUpdate() {
    position.x += velocity.x;
    hitBoxPosition.x += velocity.x;
    attackHitBoxPosition.x += velocity.x;
    colisionBoxPosition.x += velocity.x;

    position.y += velocity.y;
    hitBoxPosition.y += velocity.y;
    attackHitBoxPosition.y += velocity.y;
    colisionBoxPosition.y += velocity.y;
}


void HellHound::drawHitbox(sf::RenderWindow &window) {
        spriteManager->getInstance().drawSprite(&hitBox, hitBoxPosition.x,  hitBoxPosition.y, window);

        if (attackHitBoxIsActive) {
            spriteManager->getInstance().drawSprite(&attackHitBox, attackHitBoxPosition.x,  attackHitBoxPosition.y, window);
        }
}

void HellHound::drawColisionHitBox(sf::RenderWindow &window) {
    SpriteManager::getInstance().drawSprite(&colisionHitBox, colisionBoxPosition.x,  colisionBoxPosition.y, window);
}

void HellHound::shadowUpdate() {
    if (faceingDirection == "right") {
        shadowPosition.x = position.x - 12;
    }
    else if (faceingDirection == "left") {
        shadowPosition.x = position.x + 12;
    }
    shadowPosition.y = EnvironmenAndPhysicsManager::getInstance().floor + 5;

    EntityManager::getInstance().shadowColisionDetection(shadowPosition,name, position);

    float heightOfShadow = EnvironmenAndPhysicsManager::getInstance().floor - position.y;

    float heightOfShadowNumY = 0.038;
    float heightOfShadowNumX = 0.23;
    if (heightOfShadow > 0) {
        heightOfShadowNumY = 0.038 - heightOfShadow / 25000 ;
        heightOfShadowNumX = 0.23 - heightOfShadow / 10000;
    }

    shadowScale = {heightOfShadowNumX, heightOfShadowNumY};
    SpriteManager::getInstance().shadowTransform(&shadow,shadowScale);

    shadow.setPosition(shadowPosition);
}

void HellHound::drawAdditions(sf::RenderWindow &window) {
    SpriteManager::getInstance().drawSprite(&shadow, shadowPosition.x, shadowPosition.y, window);
}
