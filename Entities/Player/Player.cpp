//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "Player.h"

#include <iostream>
#include <ostream>

#include "../../UIdirectory/UI/PlayerUIHP.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"


Player::Player(sf::Vector2f position, sf::Vector2f velocity) : Entity(position, velocity, std::string("Player")) {
    float x = 2.2f;
    float y = 2.2f;

    //Docasne:{
    sf::Texture hitboxTexture;
    if (!hitboxTexture.loadFromFile("../../textures/hitbox.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    hitBox.setTexture(hitboxTexture);


    sf::Texture hitboxTextureAttack;
    if (!hitboxTextureAttack.loadFromFile("../../textures/hitbox.png")) {
        throw std::runtime_error("Nelze načíst Idle texturu");
    }
    attackHitBox.setTexture(hitboxTextureAttack);

    //docasne}

    scale = sf::Vector2f(x, y);
    faceingDirection = "right";

}

void Player::update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) {
    if (!freez) {
        cooldowns_and_unIntraptebulActions();
        input();
    }
    hitBoxUpdateposition();
    if (!freez) {
        transformationSprite(currentTexture);
    }
    entityFallManagment();
    gravityAndGround(environmenAndPhysicsManager);
    if (!freez) {
        beeingHitFunc();
    }

    colisionDetectionEntityExtention(name);

    if (!freez) {
        movmentUpdate();
    }
    playerUIHP->getInstance().updateHPbar(hp, window);

    std::cout << velocity.x<<std::endl;



    drawEntity(window);
    drawHitbox(window);
}


void Player::hitBoxUpdateposition() {
    if (currentTexture == "SlideKnight") {
        hitboxScale = sf::Vector2f(0.2f, 0.2f);
        if (faceingDirection == "right") {
            hitBoxPosition.x = position.x;
        } else if (faceingDirection == "left") {
            hitBoxPosition.x = position.x;
        }
        hitBoxPosition.y = position.y + 70;
    } else {
        hitboxScale = sf::Vector2f(0.17f, 0.4f);
        if (faceingDirection == "right") {
            hitBoxPosition.x = position.x - 10;
        } else if (faceingDirection == "left") {
            hitBoxPosition.x = position.x + 10;
        }
        hitBoxPosition.y = position.y + 50;
    }


    if (currentTexture == "attackKnight") {
        attackHitboxScale = sf::Vector2f(0.45f, 0.55f);
        if (faceingDirection == "right") {
            attackHitBoxPosition.x = position.x + 70;
        } else if (faceingDirection == "left") {
            attackHitBoxPosition.x = position.x - 70;
        }
        attackHitBoxPosition.y = position.y + 40;
    }

    if (currentTexture == "SaccendAttackKnight") {
        attackHitboxScale = sf::Vector2f(0.55f, 0.45f);
        if (faceingDirection == "right") {
            attackHitBoxPosition.x = position.x + 25;
        } else if (faceingDirection == "left") {
            attackHitBoxPosition.x = position.x - 25;
        }
        attackHitBoxPosition.y = position.y + 40;
    }
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
    if (attackCooldawn.getElapsedTime().asMilliseconds() >= intervalBetwenAttacks) {
        coolDawnIsOff = true;
    }
    if (slideCooldawn.getElapsedTime().asMilliseconds() > intervelToSlide) {
        lastVelocytyY = 0;
    }

    if (invincClock.getElapsedTime().asMilliseconds() >= invincibilityTime) {
        invincibility = false;
    }


    //attack finish animacion
    if (unIntaraptebulAnimation) {
        if (spriteManager->getInstance().getIndexOfAnimation(&sprite) >= spriteManager->getInstance().
            getMaxIndexOfAnimation(&sprite) - 120) {
            unIntaraptebulAnimation = false;
            unIteraptebulAnimLowPriority = false;
            attackHitBoxIsActive = false;
            coolDawnIsOff = false;
            passivActionStandStill();
            attackCooldawn.restart();
        }
    }
    if (unIteraptebulAnimLowPriority) {
        if (spriteManager->getInstance().getIndexOfAnimation(&sprite) >= spriteManager->getInstance().
            getMaxIndexOfAnimation(&sprite) - 120) {
            unIteraptebulAnimLowPriority = false;
            }
    }


    if (velocity.x == 0) {
        slideIsActiove = false;
    } else {
        slideIsActiove = true;
    }
}

void Player::input() {
    if (!gotHit) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            passivActionStandStill();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && slideIsActiove) {
            actionSlide();
        } else if (isSliding) {
                setTexture("SlideTransitionEndKnight");
                isSliding = false;
                unIteraptebulAnimLowPriority = true;
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
        } else if (cancalJump) {
            if (velocity.y <= -10) {
                velocity.y = -10;
            }
            cancalJump = false;
        }

        passivActionStuck();
    }
}

void Player::entityFallManagment() {
    if (position.y + velocity.y + 1 < 704) {
        isInAir = true;
    } else {
        isInAir = false;
        isFalling = false;
        if (velocity.y != 0) {
            lastVelocytyY = velocity.y;
            slideCooldawn.restart();
        }
    }
    if (isInAir) {
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

//Action:
void Player::actionWalkRight() {

    if (!unIntaraptebulAnimation) {

            if (!isInAir) {
                if (!unIteraptebulAnimLowPriority) {
                    setTexture("runKnight");
                }
                faceingDirection = "right";
                if (velocity.x > 7) {
                    velocity.x--;
                } else {
                    velocity.x = 7;
                }
            } else {
                faceingDirection = "right";
                if (velocity.x <= 6) {
                    velocity.x++;
                }
            }
    }
}

void Player::actionWalkLeft() {
    if (!unIntaraptebulAnimation) {
            if (!isInAir) {
                setTexture("runKnight");
                faceingDirection = "left";
                if (velocity.x < -7) {
                    velocity.x++;
                } else {
                    velocity.x = -7;
                }
            } else {
                faceingDirection = "left";
                if (velocity.x >= -6) {
                    velocity.x--;
                }
            }
    }
}

void Player::actionAttack() {
    if (!unIntaraptebulAnimation) {
        if (coolDawnIsOff) {
            unIntaraptebulAnimation = true;
            setTexture("attackKnight");
            if (!isInAir) {
                velocity.x = 0;
            }
            SeccnadAttackIsActive = true;

            transformHitBoxAttack1();
        } else if (SeccnadAttackIsActive) {
            unIntaraptebulAnimation = true;
            setTexture("SaccendAttackKnight");
            SeccnadAttackIsActive = false;

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
                unIteraptebulAnimLowPriority = true;
            }

            velocity.y = -20;
            if (!unIteraptebulAnimLowPriority) {
                setTexture("JumpKnight");
            }
            cancalJump = true;
            unIteraptebulAnimLowPriority = true;
        }

}


void Player::actionSlide() {
    if (!unIntaraptebulAnimation) {
        if (!isInAir) {

            if (isSliding) {
                if (!unIteraptebulAnimLowPriority) {
                    setTexture("SlideKnight");
                }
            }

            if (!isSliding) {
                if (!unIteraptebulAnimLowPriority) {
                    setTexture("SlideTransitionStartKnight");
                    isSliding = true;
                    unIteraptebulAnimLowPriority = true;
                }
            }

            if (velocity.x < 0.3 && velocity.x > -0.3) {

                if (isSliding) {
                    if (!unIteraptebulAnimLowPriority) {
                        setTexture("SlideTransitionEndKnight");
                        isSliding = false;
                        unIteraptebulAnimLowPriority = true;
                    }
                }
                if (!unIteraptebulAnimLowPriority) {
                    setTexture("idleKnight");
                }
                lastVelocytyY = 0;
                velocity.x = 0;
            }

            if (faceingDirection == "right") {
                velocity.x = velocity.x + lastVelocytyY / 2.5;
            } else {
                velocity.x = velocity.x - lastVelocytyY / 2.5;
            }
            lastVelocytyY = 0;

            velocity.x = velocity.x / 1.02;
        }
    }
}

void Player::passivActionGetHit(std::string fecingDirection, int damage) {
    if (!invincibility) {
        if (!freez) {
            if (!gotHit) {
                attackHitBoxIsActive = false;
                unIntaraptebulAnimation = false;
                setTexture("HitKnight");
                if (fecingDirection == "right") {
                    velocity.x = -11;
                } else if (fecingDirection == "left") {
                    velocity.x = 11;
                }
                beeingHit.restart();
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

void Player::beeingHitFunc() {
    if (gotHit) {
        if (beeingHit.getElapsedTime().asMilliseconds() <= beeingHitPlayerIntervalKnight) {
            velocity.x = velocity.x / 1.1;
        } else {
            velocity.x = 0;
            gotHit = false;
        }
    }
}


//passiv Actions:
void Player::passivActionStandStill() {
    if (!unIteraptebulAnimLowPriority) {
        if (!isInAir) {
            if (!unIntaraptebulAnimation) {
                setTexture("idleKnight");
                velocity.x = 0;
            }
        }
    }
}

void Player::passivActionBetwenFalling() {
        if (!unIntaraptebulAnimation) {
            if (!unIteraptebulAnimLowPriority) {
                setTexture("JumpFallInbetweenKnight");
            }
            isFalling = true;
            unIteraptebulAnimLowPriority = true;
        }

}

void Player::passivActionFalling() {
    if (!unIteraptebulAnimLowPriority) {
        if (!unIntaraptebulAnimation) {
            setTexture("FallKnight");
        }
    }
}



void Player::movmentUpdate() {
    if (!isOnCornerOfTheMan) {
        position.x += velocity.x;
    }
    position.y += velocity.y;
}

void Player::cornerBoolSetTrue() {
    isOnCornerOfTheMan = true;
}

void Player::cornerBoolSetFalse() {
    isOnCornerOfTheMan = false;
}

bool Player::getBoolCorner() {
    if (isOnCornerOfTheMan) {
        return true;
    } else if (!(isOnCornerOfTheMan)) {
        return false;
    }
    return false;
}

void Player::drawHitbox(sf::RenderWindow &window) {
    spriteManager->getInstance().drawSprite(&hitBox, hitBoxPosition.x, hitBoxPosition.y, window);
    if (attackHitBoxIsActive) {
        spriteManager->getInstance().drawSprite(&attackHitBox, attackHitBoxPosition.x, attackHitBoxPosition.y, window);
    }
}
