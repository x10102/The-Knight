//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "../Managers/EnvironmenAndPhysicsManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include "../Managers/SpriteManager.h"
#include "../Managers/TextureManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../UIdirectory/UIManager.h"
#include "../UIdirectory/UI/PlayerUIHP.h"
#include <SFML/Window/Event.hpp>

class EntityManager;
class Soul;

class Entity {
public:



    EntityManager *entityManager;
    SpriteManager *spriteManager;
    TextureManager *textureManager;

    int hp;

    bool hasSoul = false;

    std::string name;

    int currentAttack;
    int colisionDamage;
    int angle;
    sf::Vector2f trueScale;

    bool gotHit = false;
    bool reatriting = false;
    bool isInAir = false;
    bool uninterruptableAnimation = false;
    bool uninterruptableAnimLowPriority = false;
    bool SecondAttackActive = false;
    bool ignoreFloor = false;
    bool collidable = false;
    bool isCollidingWithPlatform = false;


    int invincibilityTime;
    bool invincibility = false;
    sf::Clock invincClock;

    bool freeze =false;

    bool isHoveringInAir = false;
    bool isFalling = false;

    const float intervalBetweenAttacks = 250.0f;
    const float intervalToSlide = 50.0f;
    const float coolDownJumpInterval = 1500.0f;
    const float coolDownJumpInterval2 = 900.0f;
    const float beingHitPlayerIntervalKnight = 500.0f;
    const float beingHitPlayerIntervalHellHound = 300.0f;

    float offSet;


    sf::Clock attackCooldown;
    sf::Clock slideCooldown;
    sf::Clock cooldownJump;
    sf::Clock beingHit;
    sf::Clock retritingTimer;
    bool cooldownIsOffJump = true;
    bool coolDownIsOff = true;
    bool slideIsActive = false;
    bool dashIsActiveBool = false;
    sf::Clock dashIsActiveClock;
    sf::Clock dashIsActiveClockCooldown;

    std::vector<Soul*> absorbedSouls;

    Soul* soul;


    sf::Sprite sprite;
    std::string currentTexture;

    sf::Sprite hitBox;
    sf::Vector2f hitboxScale;
    sf::Texture hitBoxTexture;
    sf::Vector2f hitBoxPosition;

    sf::Sprite attackHitBox;
    sf::Vector2f attackHitboxScale;
    sf::Texture attackHitBoxTexture;
    sf::Vector2f attackHitBoxPosition;


    sf::Sprite collisionHitBox;
    sf::Vector2f collisionHitboxScale;
    sf::Texture colisionHitBoxTexture;
    sf::Vector2f collisionBoxPosition;
    float colisionHitBoxYOffSet;

    sf::Sprite shadow;
    sf::Vector2f shadowScale;
    sf::Texture shadowTexture;
    sf::Vector2f shadowPosition;

    float getColisionHitBoxYOffSet();

    bool attackHitBoxIsActive = false;

    std::string facingDirection;
    sf::Vector2f scale;
    sf::Vector2f position; //pozice entityq
    sf::Vector2f velocity; // velocity směr entity
    float lastVelocityY;


    virtual void update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager); //osobni Update Kazde Entity
    void drawEntity(sf::RenderWindow &window); // nakresli sam sebe
    virtual void drawHitbox(sf::RenderWindow &window);
    virtual void drawAdditions(sf::RenderWindow &window);
    virtual void drawColisionHitBox(sf::RenderWindow &window);

    void setTexture(std::string newNameOfTexture);// nastaví texturu
    virtual void gravityAndGround(EnvironmenAndPhysicsManager &environmenAndPhysicsManage);
    virtual void movmentUpdate();
    virtual void transformHitBoxAttack1();
    virtual void transformHitBoxAttack2();
    Soul* getSoul();

    void insertSoulInToAbsortionFeeld(Soul *soulToInsert);

    void setEntityAsInvincibul(int invincTime);


    virtual void hitBoxUpdateposition();

    virtual void entityFallManagment(EnvironmenAndPhysicsManager &environmenAndPhysicsManager);



    Entity(sf::Vector2f position, sf::Vector2f velocity, std::string name); //konstruktor Entity
    virtual ~Entity() = default;

    void transformationSprite(std::string currentTexture);
    virtual void cooldowns_and_unIntraptebulActions();

    virtual void beingHitFunc();

    //Actions:
    virtual void actionWalkRight();
    virtual void actionWalkLeft();
    virtual void actionJump();
    virtual void actionAttack();
    virtual void actionSlide();
    virtual void actionDash();

    virtual void passivActionStandStill();

    void freezEntity();
    void unFreezEntity();

    virtual void passivActionBetwenFalling();
    virtual void passivActionFalling();
    virtual void passivActionGetHit(std::string fecingDirection, int damage);
    virtual void passivActionDie();

    virtual void passivActionStuck();

    bool getBoolAttackIsActive();


    bool getAttackHitboxIsActive();
    sf::Sprite *getHitbox();

    sf::Sprite *getAttackHitbox();

    sf::Sprite &getSpriteOfEntity();

    void rotateSprite();

    void colisionDetectionEntityExtention(std::string nameOfEntity);

    void setVelocity(sf::Vector2f newVelocity);
    sf::Vector2f getVelocity();

  virtual void shadowUpdate();

    void setEntityOnFloor();
    void impactBound();
    bool boundEntity = false;
    float impactBand = 2.1f;
    bool retretBouncing = false;


};

#endif //ENTITY_H
