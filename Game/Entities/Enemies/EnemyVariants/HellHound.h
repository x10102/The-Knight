//
// Created by Oliver Šmítek on 11.02.2026.
//

#ifndef HELLHOUND_H
#define HELLHOUND_H


#include "../Enemy.h"
#include "../../../Managers/EntityManager.h"
#include "../../../Managers/EnvironmenAndPhysicsManager.h"


class Entity;

class HellHound : public Enemy {

    int attackBite = primeryAttackDamage;

public:
    sf::Vector2f positionOfPlayer;

    HellHound (sf::Vector2f position, sf::Vector2f velocity, std::string name);

    void drawHitbox( sf::RenderWindow &window) override;

    void drawColisionHitBox(sf::RenderWindow &window) override;

    void drawAdditions(sf::RenderWindow &window) override;

    void update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) override;

    void hellHoundAI();

    void hitBoxUpdateposition() override;

    void transformHitBoxAttack1() override;

    void movmentUpdate() override;
    void entityFallManagment(EnvironmenAndPhysicsManager &environmenAndPhysicsManager) override;

    void cooldowns_and_unIntraptebulActions() override;

    void passivActionStandStill() override;
    void passivActionGetHit(std::string fecingDirection, int damage) override;
    void passivActionDie() override;
    void beingHitFunc() override;


    void actionWalkLeft() override;
    void actionWalkRight() override;

    void actionJumpAttack();

    void shadowUpdate() override;


};






#endif //HELLHOUND_H
