//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <map>

#include "SpriteManager.h"
#include "../Entities/Entity.h"
#include "../Managers/EnvironmenAndPhysicsManager.h"

class Entity;

class EntityManager {

private:
    int id;
    EntityManager() {}

    SpriteManager *spriteManager;
    TextureManager *textureManager;

public:
    static EntityManager& getInstance(){
        static EntityManager theInstance;
        return theInstance;
    }

    bool perry = false;
    std::string fecingDirectionOfAttackingEntity;

    bool attacked = false;


    std::map<std::string, Entity*> uMOfEntitys; //unoredred mapa všech entit ve hře
    std::map<std::string, Entity*> uMOfEntitysToKill;
    std::map<std::string, Entity*> uMOfDrawEntitys;


    void update(sf::RenderWindow &window, EnvironmenAndPhysicsManager &
                environmenAndPhysicsManager);
    sf::Vector2f getPositionOfEntity(std::string nameOfEntity);
    sf::Vector2f getVelocityOfEntity(std::string nameOfEntity);
    void cornerBoolSetFalsePlayer();
    void cornerBoolSetTruePlayer();
    bool getCornerBool();
    void attakeEntity(std::string nameOfEntity);
    void removeEntity(std::string nameOfEntity);
    void checkEntityHitBox();
    bool getAttacIsActiveBool(std::string nameOfEntity);
    void killEntity(std::string nameOfEntity, Entity* entityToKill);
    void killEntities();



    void freezTheGame(int damage);
    void unFreezTheGame();
    void chackHowLongToFreez();
    void timeTheHit(Entity &entityRes, Entity &entityAtc, int damage);
    sf::Clock timerFreez;
    bool gameIsFreezd = false;
    int freezTime =0;

    void hitEntity(Entity* entityResev,Entity* entityAttack, int parryMulitplayer);

    sf::Sprite *getSpriteOfEntity(std::string name);

    void colisionDetection(std::string nameOfEntity);

    void shadowColisionDetection(sf::Vector2f &shadowPos, std::string name, sf::Vector2f playerPosotion);

};


#endif //ENTITYMANAGER_H
