//
// Created by Oliver Šmítek on 11.02.2026.
//

#ifndef HELLHOUND_H
#define HELLHOUND_H

#include "../../Managers/SpawnManager.h"
#include "../../Managers/EntityManager.h"


class Entity;

class HellHound : public Entity {

    int hp = 100;
    int attackBite = 10;

public:
    sf::Vector2f positionOfPlayer;

    HellHound (sf::Vector2f position, sf::Vector2f velocity, std::string name);

    void drawHitbox( sf::RenderWindow &window) override;

    void update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) override;

    void hellHoundAI();

    void hitBoxUpdateposition() override;

    void transformHitBoxAttack1() override;

    sf::Vector2f getPositionOfPlayer();
    sf::Vector2f getVelocityOfPlayer(EntityManager &entityManager);

    void movmentUpdate() override;
    void entityFallManagment() override;

    void cooldowns_and_unIntraptebulActions() override;

    void passivActionStandStill() override;
    void passivActionGetHit(std::string fecingDirection, int damage) override;
    void passivActionDie() override;
    void beeingHitFunc() override;



    void actionWalkLeft() override;
    void actionWalkRight() override;

    void actionJumpAttack();


};






#endif //HELLHOUND_H
