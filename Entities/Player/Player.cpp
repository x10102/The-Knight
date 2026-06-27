//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "Player.h"

#include <iostream>
#include <ostream>

#include "../../Managers/BackGroundManager.h"
#include "../../Managers/SpawnManager.h"
#include "../../UIdirectory/UI/PlayerUIHP.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"


Player::Player(sf::Vector2f position, sf::Vector2f velocity) : Entity(position, velocity, std::string("Player")) {
    float x = 2.2f;
    float y = 2.2f;

    trueScale = sf::Vector2f(x, y);
    //Docasne:{

    hitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);

    attackHitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);

    collisionHitBox.setTexture(TextureManager::getInstance().textures["hitbox"]);

    shadow.setTexture(TextureManager::getInstance().textures["shedowOfEntity"]);

    //docasne}

    scale = sf::Vector2f(x, y);
    facingDirection = "right";

}

void Player::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    entityFallManagment(environmenAndPhysicsManager);

    if (!freeze) {
        cooldowns_and_unIntraptebulActions();
        input();
        transformationSprite(currentTexture);
    }
    if (!freeze) {
        beingHitFunc();
        dashIsActive();
    }

    hitBoxUpdateposition();
    colisionDetectionEntityExtention(name);

    if (!freeze) {
        movmentUpdate();
    }
    shadowUpdate();

}


void Player::hitBoxUpdateposition() {

    if (currentTexture == "SlideKnight") {
        hitboxScale = sf::Vector2f(0.2f, 0.3);
        if (facingDirection == "right") {
            hitBoxPosition.x = position.x;
        } else if (facingDirection == "left") {
            hitBoxPosition.x = position.x;
        }
        hitBoxPosition.y = position.y;

        collisionHitboxScale = sf::Vector2f(0.12f, 0.2f);
        collisionBoxPosition.x = position.x;
        collisionBoxPosition.y = position.y;

    } else {
        hitboxScale = sf::Vector2f(0.12f, 0.35f);
        if (facingDirection == "right") {
            hitBoxPosition.x = position.x - 12;
        } else if (facingDirection == "left") {
            hitBoxPosition.x = position.x + 12;
        }
        hitBoxPosition.y = position.y;

        collisionHitboxScale = sf::Vector2f(0.1f, 0.4f);
        collisionBoxPosition.x = position.x;
        collisionBoxPosition.y = position.y;
    }

    if (currentTexture == "attackKnight") {
        attackHitboxScale = sf::Vector2f(0.45f, 0.55f);
        if (facingDirection == "right") {
            attackHitBoxPosition.x = position.x + 70;
        } else if (facingDirection == "left") {
            attackHitBoxPosition.x = position.x - 70;
        }
        attackHitBoxPosition.y = position.y;
    }

    if (currentTexture == "SaccendAttackKnight") {
        attackHitboxScale = sf::Vector2f(0.55f, 0.45f);
        if (facingDirection == "right") {
            attackHitBoxPosition.x = position.x + 25;
        } else if (facingDirection == "left") {
            attackHitBoxPosition.x = position.x - 25;
        }
        attackHitBoxPosition.y = position.y;
    }


    collisionHitBox.setPosition(collisionBoxPosition);
    hitBox.setPosition(hitBoxPosition);
    attackHitBox.setPosition(attackHitBoxPosition);
}

void Player::transformHitBoxAttack1() {
    currentAttack = attackSword;
    attackHitBoxIsActive = true;
}

void Player::transformHitBoxAttack2() {
    currentAttack = attackSword;
    attackHitBoxIsActive = true;
}


void Player::cooldowns_and_unIntraptebulActions() {
    //cooldawns:

    //attack Cooldawn:
    if (attackCooldown.getElapsedTime().asMilliseconds() >= intervalBetweenAttacks) {
        coolDownIsOff = true;
    }
    if (slideCooldown.getElapsedTime().asMilliseconds() > intervalToSlide) {
        lastVelocityY = 0;
    }

    if (invincClock.getElapsedTime().asMilliseconds() >= invincibilityTime) {
        invincibility = false;
    }

    if (dashIsActiveClockCooldown.getElapsedTime().asSeconds() >= dashCuldownSecund) {
        if (dashNumOfUse < 2) {
            dashNumOfUse++;
            dashIsActiveClockCooldown.restart();
        }
    }


    //attack finish animacion
    if (uninterruptableAnimation) {
        if (spriteManager->getInstance().getIndexOfAnimation(&sprite) >= spriteManager->getInstance().
            getMaxIndexOfAnimation(&sprite) - 120) {
            uninterruptableAnimation = false;
            uninterruptableAnimLowPriority = false;
            attackHitBoxIsActive = false;
            coolDownIsOff = false;
            passivActionStandStill();
            attackCooldown.restart();
        }
    }
    if (uninterruptableAnimLowPriority) {
        if (spriteManager->getInstance().getIndexOfAnimation(&sprite) >= spriteManager->getInstance().
            getMaxIndexOfAnimation(&sprite) - 120) {
            uninterruptableAnimLowPriority = false;
            }
    }


    if (velocity.x == 0) {
        slideIsActive = false;
    } else {
        slideIsActive = true;
    }
}

void Player::input() {
    if (!gotHit) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            passivActionStandStill();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && slideIsActive) {
            actionSlide();
        } else if (isSliding) {
                setTexture("SlideTransitionEndKnight");
                isSliding = false;
                uninterruptableAnimLowPriority = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && dashNumOfUse > 0) {
            actionDash();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            actionWalkLeft();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            actionWalkRight();
        } else {
            passivActionStandStill();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            actionAttack();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            actionJump();
        } else if (cancelJump) {
            if (velocity.y <= -10) {
                velocity.y = -10;
            }
            cancelJump = false;
        }
        passivActionStuck();
    }
}

void Player::entityFallManagment(EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    if (!dashIsActiveBool) {
        impactBound();
        if (position.y + velocity.y + 1 < EnvironmenAndPhysicsManager::getInstance().floor) {
            isInAir = true;
        } else {
            setEntityOnFloor();
            if (velocity.y != 0) {
                lastVelocityY = velocity.y;
                slideCooldown.restart();
            }
        }
        if (isCollidingWithPlatform) {
            isInAir = false;
        }

        if (isInAir) {
            if (!isCollidingWithPlatform) {
                if (!gotHit) {
                    if (!isFalling) {
                        passivActionBetwenFalling();
                    }
                    if (isFalling) {
                        passivActionFalling();
                    }
                }
            }
        }
    }
    gravityAndGround(environmenAndPhysicsManager);

}

//Action:
void Player::actionWalkRight() {

    if (!uninterruptableAnimation) {

            if (!isInAir) {
                if (!uninterruptableAnimLowPriority) {
                    setTexture("runKnight");
                }
                facingDirection = "right";
                if (velocity.x > 7) {
                    velocity.x = velocity.x - 0.8;
                } else {
                    velocity.x = 7;
                }
            } else {
                facingDirection = "right";
                if (velocity.x <= 6) {
                    velocity.x++;
                }
            }
    }
}

void Player::actionWalkLeft() {
    if (!uninterruptableAnimation) {
            if (!isInAir) {
                setTexture("runKnight");
                facingDirection = "left";
                if (velocity.x < -7) {
                    velocity.x = velocity.x + 0.8;
                } else {
                    velocity.x = -7;
                }
                std::cout << isCollidingWithPlatform << std::endl;

            } else {
                facingDirection = "left";
                if (velocity.x >= -6) {
                    velocity.x--;
                }
            }
    }
}

void Player::actionAttack() {
    if (!uninterruptableAnimation) {
        if (coolDownIsOff) {
            uninterruptableAnimation = true;
            setTexture("attackKnight");
            if (!isInAir) {
                velocity.x = 0;
            }
            SecondAttackActive = true;

            transformHitBoxAttack1();
        } else if (SecondAttackActive) {
            uninterruptableAnimation = true;
            setTexture("SaccendAttackKnight");
            SecondAttackActive = false;

            if (!isInAir) {
                velocity.x = 0;
            }
            transformHitBoxAttack1();
        }
    }
}


void Player::actionJump() {
        if (!isInAir) {

            if (isSliding) {
                setTexture("SlideTransitionEndKnight");
                isSliding = false;
                uninterruptableAnimLowPriority = true;
            }

            velocity.y = -20;
            if (!uninterruptableAnimLowPriority) {
                setTexture("JumpKnight");
            }
            cancelJump = true;
            uninterruptableAnimLowPriority = true;
        }

}


void Player::actionSlide() {
    if (!uninterruptableAnimation) {
        if (!isInAir) {

            if (isSliding) {
                if (!uninterruptableAnimLowPriority) {
                    setTexture("SlideKnight");
                }
            }

            if (!isSliding) {
                if (!uninterruptableAnimLowPriority) {
                    setTexture("SlideTransitionStartKnight");
                    isSliding = true;
                    uninterruptableAnimLowPriority = true;
                }
            }

            if (velocity.x < 0.3 && velocity.x > -0.3) {

                if (isSliding) {
                    if (!uninterruptableAnimLowPriority) {
                        setTexture("SlideTransitionEndKnight");
                        isSliding = false;
                        uninterruptableAnimLowPriority = true;
                    }
                }
                if (!uninterruptableAnimLowPriority) {
                    setTexture("idleKnight");
                }
                lastVelocityY = 0;
                velocity.x = 0;
            }

            if (facingDirection == "right") {
                velocity.x = velocity.x + lastVelocityY / 2.5;
            } else {
                velocity.x = velocity.x - lastVelocityY / 2.5;
            }
            lastVelocityY = 0;

            velocity.x = velocity.x / 1.02;
        }
    }
}

void Player::actionDash() {
    std::cout << "actionDash called" << std::endl;
    if (!dashIsActiveBool) {
        if (facingDirection == "right") {
            if (isInAir) {
                velocity.x = Dashspeed;
            }
            else {
                velocity.x = Dashspeed * 1.2;
            }
        }
        else if (facingDirection == "left") {
            if (isInAir) {
                velocity.x = - Dashspeed ;
            }
            else {
                velocity.x = - (Dashspeed * 1.2);
            }
        }
        dashIsActiveBool = true;
        dashIsActiveClock.restart();
        dashNumOfUse = dashNumOfUse - 1;
    }
}

void Player::dashIsActive() {

        if (dashIsActiveBool) {
                if (dashIsActiveClock.getElapsedTime().asMilliseconds() <= 130){
                    velocity.y = 0;

                    setTexture("dashKnight");
                    uninterruptableAnimation = true;
                    invincibility = true;
                }
                else {
                    dashIsActiveBool =false;
                    invincibility = false;
                }
            }

}

void Player::passivActionGetHit(std::string fecingDirection, int damage) {
    if (!invincibility) {
        if (!freeze) {
            if (!gotHit) {
                attackHitBoxIsActive = false;
                uninterruptableAnimation = false;
                setTexture("HitKnight");
                if (fecingDirection == "right") {
                    velocity.x = -11;
                } else if (fecingDirection == "left") {
                    velocity.x = 11;
                }
                beingHit.restart();
                gotHit = true;


                hp = hp - damage;

                if (hp <= 0) {
                    passivActionDie();
                }
            }
        }
    }
}

void Player::passivActionDie() {
}

void Player::beingHitFunc() {
    if (gotHit) {
        if (beingHit.getElapsedTime().asMilliseconds() <= beingHitPlayerIntervalKnight) {
            velocity.x = velocity.x / 1.1;
        } else {
            velocity.x = 0;
            gotHit = false;
        }
    }
}


//passiv Actions:
void Player::passivActionStandStill() {
    if (!uninterruptableAnimLowPriority) {
        if (!isInAir) {
            if (!uninterruptableAnimation) {
                if (!dashIsActiveBool) {
                    setTexture("idleKnight");
                    velocity.x = 0;
                }
            }
        }
    }
}

void Player::passivActionBetwenFalling() {
        if (!uninterruptableAnimation) {
            if (!uninterruptableAnimLowPriority) {
                setTexture("JumpFallInbetweenKnight");
            }
            isFalling = true;



            uninterruptableAnimLowPriority = true;
        }

}

void Player::passivActionFalling() {
    if (!uninterruptableAnimLowPriority) {
        if (!uninterruptableAnimation) {
            setTexture("FallKnight");
        }
    }
}



void Player::movmentUpdate() {
    position.x += velocity.x;
    hitBoxPosition.x += velocity.x;
    attackHitBoxPosition.x += velocity.x;
    collisionBoxPosition.x += velocity.x;

    position.y += velocity.y;
    hitBoxPosition.y += velocity.y;
    attackHitBoxPosition.y += velocity.y;
    collisionBoxPosition.y += velocity.y;
}


void Player::drawHitbox(sf::RenderWindow &window) {
    spriteManager->getInstance().drawSprite(&hitBox, hitBoxPosition.x,  hitBoxPosition.y, window);

    if (attackHitBoxIsActive) {
        spriteManager->getInstance().drawSprite(&attackHitBox, attackHitBoxPosition.x,  attackHitBoxPosition.y, window);
    }
}

void Player::drawAdditions(sf::RenderWindow &window) {
    playerUIHP->getInstance().updateHPbar(hp, window);

    SpriteManager::getInstance().speedBlurer(&sprite, window, 4, facingDirection, velocity.x,dashIsActiveBool );

    SpriteManager::getInstance().drawSprite(&shadow, shadowPosition.x, shadowPosition.y, window);
}

void Player::drawColisionHitBox(sf::RenderWindow &window) {
    SpriteManager::getInstance().drawSprite(&collisionHitBox, collisionBoxPosition.x,  collisionBoxPosition.y, window);
}

void Player::shadowUpdate() {
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
    float heightOfShadowNumX = 0.18;
    if (heightOfShadow > 0) {
        heightOfShadowNumY = 0.038 - heightOfShadow / 25000 ;
        heightOfShadowNumX = 0.18 - heightOfShadow / 10000;
    }

    shadowScale = {heightOfShadowNumX, heightOfShadowNumY};
    SpriteManager::getInstance().shadowTransform(&shadow,shadowScale);

    shadow.setPosition(shadowPosition);
}