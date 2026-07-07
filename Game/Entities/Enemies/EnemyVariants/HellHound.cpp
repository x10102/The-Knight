//
// Created by Oliver Šmítek on 11.02.2026.
//

#include "HellHound.h"
#include "../../../Managers/ParticalManager.h"
#include "../../souls/SoulsVariants/NarunSoul.h"

HellHound::HellHound(sf::Vector2f position, sf::Vector2f velocity, std::string name) :
Enemy(position, velocity, name, 25, 20, new NarunSoul()) {}

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


    if (!uninterruptableAnimation) {
        return;
    }

    if (spriteManager->getInstance().getIndexOfAnimation(&sprite) >= spriteManager->getInstance().getMaxIndexOfAnimation(&sprite) - 64) {
        uninterruptableAnimation = false;
        attackHitBoxIsActive = false;
        if (facingDirection == "left") {
            actionWalkLeft();
        }
        else if (facingDirection == "right") {
            actionWalkRight();
        }
        attackCooldown.restart();
    }
}

void HellHound::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {

    if (!freeze) {
        beingHitFunc();
        hellHoundAI();
    }
    if (!freeze) {
        transformationSprite(currentTexture);
    }
    entityFallManagment(environmenAndPhysicsManager);

    if (!freeze) {
        cooldowns_and_unIntraptebulActions();
    }


    hitBoxUpdateposition();
    colisionDetectionEntityExtention(name);

    if (!freeze) {
        movmentUpdate();
    }
    shadowUpdate();

}

void HellHound::passivActionStandStill() {
    if(uninterruptableAnimation) return;

    setTexture("HellHoundIdle");
    velocity.x = 0;
}

void HellHound::actionWalkRight() {
    if(uninterruptableAnimation) return;

    setTexture("HellHoundRun");

    facingDirection = "right";
    velocity.x = -11;
}

void HellHound::actionWalkLeft() {
    if(uninterruptableAnimation) return;

    setTexture("HellHoundRun");

    facingDirection = "left";
    velocity.x = 11;
}


void HellHound::entityFallManagment(EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    impactBound();
    if (position.y + velocity.y + 1 < EnvironmenAndPhysicsManager::getInstance().floor && isCollidingWithPlatform) {
        isInAir = true;
    }
    else {
        setEntityOnFloor();
    }
    gravityAndGround(environmenAndPhysicsManager);

}


void HellHound::transformHitBoxAttack1() {
    currentAttack = attackBite;
    attackHitBoxIsActive = true;
}

void HellHound::actionJumpAttack() {
    if(uninterruptableAnimation) return;

    if (facingDirection == "left") {
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
    uninterruptableAnimation = true;
    cooldownIsOffJump = false;
    cooldownJump.restart();
}


void HellHound::beingHitFunc() {
    if(!gotHit) return;

    if (beingHit.getElapsedTime().asMilliseconds() <= beingHitPlayerIntervalHellHound) {
        spriteManager->getInstance().markTextureAsHit(&sprite);
        attackHitBoxIsActive = false;
    }
    else {
        spriteManager->getInstance().markTextureAsNormal(&sprite);
        gotHit = false;
    }
}

void HellHound::passivActionGetHit(std::string fecingDirection, int damage) {
    if(freeze || gotHit) return;

    ParticalManager::getInstance().spawnBloodSplash({position.x ,position.y -40}, fecingDirection, false);
    attackHitBoxIsActive = false;
    uninterruptableAnimation = false;
    setTexture("HellHoundHit");
    if (fecingDirection == "right") {
        velocity.x = 0;
    }
    else if (fecingDirection == "left") {
        velocity.x = 0;
    }
    beingHit.restart();
    reatriting = true;
    gotHit = true;

    hp = hp - damage;

    if (hp <= 0) {
        passivActionDie();
    }
}

void HellHound::passivActionDie() {
    ParticalManager::getInstance().spawnBloodSplash({position.x,position.y + 15}, facingDirection, true);

    sf::Vector2f velocityGore = {0,0};
    if (facingDirection == "left") {
        velocityGore.x = -5;
    }
    else {
        velocityGore.x = 5;
    }
    velocityGore.y = -5;


    const float goreXVelocity = static_cast<float>(velocity.x + velocityGore.x * 1.2);

    ParticalManager::getInstance().spawnHellHoundGore({position.x - 40,position.y - 48},{goreXVelocity ,velocity.y- 3},facingDirection, "GoreHellHound2");
    ParticalManager::getInstance().spawnHellHoundGore({position.x + 10,position.y - 40},{goreXVelocity,velocity.y - 2},facingDirection, "GoreHellHound5");
    ParticalManager::getInstance().spawnHellHoundGore({position.x,position.y - 42},{goreXVelocity,velocity.y - 2},facingDirection, "GoreHellHound1");

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
        if (facingDirection == "right") {
            hitBoxPosition.x = position.x - 10;

        }
        else if (facingDirection == "left") {
            hitBoxPosition.x = position.x + 10;
        }
        hitBoxPosition.y = position.y;

        collisionHitboxScale = sf::Vector2f(0.1f, 0.4f);
        collisionBoxPosition.x = position.x;
        collisionBoxPosition.y = position.y;

    }
    else {
        hitboxScale = sf::Vector2f(0.35f,0.3f);
        if (facingDirection == "right") {
            hitBoxPosition.x = position.x + 5;
        }
        else if (facingDirection == "left") {
            hitBoxPosition.x = position.x - 5;
        }
        hitBoxPosition.y = position.y;


        collisionHitboxScale = sf::Vector2f(0.1f, 0.4f);
        collisionBoxPosition.x = position.x;
        collisionBoxPosition.y = position.y;



    }

    if (currentTexture == "HellHoundJump") {
        attackHitboxScale = sf::Vector2f(0.25f,0.28f);
        if (facingDirection == "right") {
            attackHitBoxPosition.x = position.x - 35;

        }
        else if (facingDirection == "left") {
            attackHitBoxPosition.x = position.x + 35;
        }
        attackHitBoxPosition.y = position.y;
    }


    collisionHitBox.setPosition(collisionBoxPosition);
    hitBox.setPosition(hitBoxPosition);
    attackHitBox.setPosition(attackHitBoxPosition);
}



void HellHound::movmentUpdate() {
    position.x += velocity.x;
    hitBoxPosition.x += velocity.x;
    attackHitBoxPosition.x += velocity.x;
    collisionBoxPosition.x += velocity.x;

    position.y += velocity.y;
    hitBoxPosition.y += velocity.y;
    attackHitBoxPosition.y += velocity.y;
    collisionBoxPosition.y += velocity.y;
}


void HellHound::drawHitbox(sf::RenderWindow &window) {
    spriteManager->getInstance().drawSprite(&hitBox, hitBoxPosition.x,  hitBoxPosition.y, window);

    if (attackHitBoxIsActive) {
        spriteManager->getInstance().drawSprite(&attackHitBox, attackHitBoxPosition.x,  attackHitBoxPosition.y, window);
    }
}

void HellHound::drawColisionHitBox(sf::RenderWindow &window) {
    SpriteManager::getInstance().drawSprite(&collisionHitBox, collisionBoxPosition.x,  collisionBoxPosition.y, window);
}

void HellHound::shadowUpdate() {
    if (facingDirection == "right") {
        shadowPosition.x = position.x - 12;
    }
    else if (facingDirection == "left") {
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
