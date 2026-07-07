//
// Created by Oliver Šmítek on 02.07.2026.
//

#ifndef ENEMY_H
#define ENEMY_H


#include "../Entity.h"

class Enemy : public Entity {

    public:

    int hp;
    int primeryAttackDamage;

    sf::Vector2f positionOfPlayer;




    Enemy(sf::Vector2f position, sf::Vector2f velocity, std::string name, int hp, int primeryAttackDamage,
          Soul *soulOfEntity);

    sf::Vector2f getPositionOfPlayer();
    sf::Vector2f getVelocityOfPlayer();
};



#endif //ENEMY_H
