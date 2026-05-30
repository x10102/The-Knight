//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "../Managers/EnvironmenAndPhysicsManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "../Managers/SpriteManager.h"
#include "../Managers/TextureManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "../UIdirectory/UIManager.h"
#include "../UIdirectory/UI/PlayerUIHP.h"
#include "SFML/Window/Event.hpp"
#include "../Managers/ParticalManager.h"


class EntityManager;

class Entity {
public:


    EntityManager *entityManager;
    SpriteManager *spriteManager;
    PlayerUIHP *playerUIHP;
    TextureManager *textureManager;

    int hp;

    std::string name;

    int currentAttack;
    int colisionDamage;
    int angle;

    bool gotHit = false;
    bool reatriting = false;
    bool isInAir = false;
    bool unIntaraptebulAnimation = false;
    bool unIteraptebulAnimLowPriority = false;
    bool SeccnadAttackIsActive = false;
    bool ignoreFloor = false;
    bool colidebul = false;
    bool isColidingWithAPlatform = false;

    bool isOnCornerOfTheMan;

    int invincibilityTime;
    bool invincibility = false;
    sf::Clock invincClock;

    bool freez =false;

    bool isHaveringInTheAir = false;
    bool isFalling = false;

    const float intervalBetwenAttacks = 250.0f;
    const float intervelToSlide = 50.0f;
    const float coolDawnJumpInterval = 1500.0f;
    const float coolDawnJumpInterval2 = 900.0f;
    const float beeingHitPlayerIntervalKnight = 500.0f;
    const float beeingHitPlayerIntervalHellHound = 200.0f;

    float offSet;


    sf::Clock attackCooldawn;
    sf::Clock slideCooldawn;
    sf::Clock cooldownJump;
    sf::Clock beeingHit;
    sf::Clock retritingTimer;
    bool cooldownIsOffJump = true;
    bool coolDawnIsOff = true;
    bool slideIsActiove = false;


    sf::Sprite sprite;
    sf::String currentTexture;

    sf::Sprite hitBox;
    sf::Vector2f hitboxScale;
    sf::Texture hitBoxTexture;
    sf::Vector2f hitBoxPosition;

    sf::Sprite attackHitBox;
    sf::Vector2f attackHitboxScale;
    sf::Texture attackHitBoxTexture;
    sf::Vector2f attackHitBoxPosition;


    sf::Sprite colisionHitBox;
    sf::Vector2f colisionHitboxScale;
    sf::Texture colisionHitBoxTexture;
    sf::Vector2f colisionBoxPosition;
    float colisionHitBoxYOffSet;

    sf::Sprite shadow;
    sf::Vector2f shadowScale;
    sf::Texture shadowTexture;
    sf::Vector2f shadowPosition;

    float getColisionHitBoxYOffSet();

    bool attackHitBoxIsActive = false;

    sf::String faceingDirection;
    sf::Vector2f scale;
    sf::Vector2f position; //pozice entityq
    sf::Vector2f velocity; // velocity směr entity
    float lastVelocytyY;


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

    void setEntityAsInvincibul(int invincTime);


    virtual void hitBoxUpdateposition();

    virtual void entityFallManagment();

    void virtual cornerBoolSetTrue();
    void virtual cornerBoolSetFalse();

    Entity(sf::Vector2f position, sf::Vector2f velocity, std::string name); //konstruktor Entity

    void transformationSprite(std::string currentTexture);
    virtual void cooldowns_and_unIntraptebulActions();

    virtual void beeingHitFunc();

    //Actions:
    virtual void actionWalkRight();
    virtual void actionWalkLeft();
    virtual void actionJump();
    virtual void actionAttack();
    virtual void actionSlide();


    virtual void passivActionStandStill();

    void freezEntity();
    void unFreezEntity();

    virtual void passivActionBetwenFalling();
    virtual void passivActionFalling();
    virtual void passivActionGetHit(std::string fecingDirection, int damage);
    virtual void passivActionDie();

    virtual void passivActionStuck();

    bool getBoolAttackIsActive();


    virtual bool getBoolCorner();
    bool getAttackHitboxIsActive();
    sf::Sprite *getHitbox();

    sf::Sprite *getAttackHitbox();

    sf::Sprite &getSpriteOfEntity();

    void movmentSinchronaz();
    void rotateSprite();

    void colisionDetectionEntityExtention(std::string nameOfEntity);

    void setVelocity(sf::Vector2f newVelocity);
    sf::Vector2f getVelocity();

  virtual void shadowUpdate();

};

#endif //ENTITY_H
