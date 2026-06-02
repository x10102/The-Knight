//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef PLAYER_H
#define PLAYER_H


#include "../../Managers/EntityManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../Entity.h"


class Player : public Entity {

    int hp = 100;
    int attackSword = 20;

    float offSet;

  //protected:
    //std::unordered_map<std::string, sf::Texture*> uMOfTextures;
    //sf::Sprite* sprite; //ptr na Sprite
    //sf::Vector2f position;
    //sf::Vector2f velocity;

    float Dashspeed = 17;
    int dashNumOfUse = 2;
    float dashCuldownSecund = 4.0f;

public:




        bool cancalJump = false;
    bool isSliding = false;

        Player(sf::Vector2f position,sf::Vector2f velocity);
        void drawHitbox(sf::RenderWindow &window) override;
        void drawAdditions(sf::RenderWindow &window) override;
        void drawColisionHitBox(sf::RenderWindow &window) override;
        void update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager) override;
        void input();
        void cooldowns_and_unIntraptebulActions() override;
        void entityFallManagment() override;
        void movmentUpdate() override;

        void hitBoxUpdateposition() override;
        void transformHitBoxAttack1() override;
        void transformHitBoxAttack2() override;


    //Actions:

        void actionWalkRight() override;
        void actionWalkLeft() override;
        void actionJump() override;
        void actionAttack() override;
        void actionSlide() override;
        void beeingHitFunc() override;
        void actionDash() override;
        void dashIsActive();

        void passivActionStandStill() override;

        void passivActionBetwenFalling() override;
        void passivActionFalling() override;
        void passivActionGetHit(std::string fecingDirection, int damage) override;
        void passivActionDie() override;



        void shadowUpdate() override;

};



#endif //PLAYER_H
