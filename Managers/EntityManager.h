//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <map>
#include <unordered_map>

#include "SpriteManager.h"
#include "../Managers/EnvironmenAndPhysicsManager.h"

class Entity;

class EntityManager {

private:
    EntityManager() {}

    SpriteManager *spriteManager;
    TextureManager *textureManager;

public:
    static EntityManager& getInstance(){
        static EntityManager theInstance;
        return theInstance;
    }

    bool gameIsFreezd = false;
    int forceToFreez;
    sf::Clock gameIsFreezdClock;
    sf::Clock gameCanBeFreezd;
    int intervalToFreez = 500;
    bool perry = false;
    bool goFreezTheGame = false;
    std::string fecingDirectionOfAttackingEntity;
    Entity* entityRes;
    Entity* entityAtc;
    bool attacked = false;


    std::map<std::string, Entity*> uMOfEntitys; //unoredred mapa všech entit ve hře
    std::map<std::string, Entity*> uMOfEntitysToKill;

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
    void gameFreez();
    void unFreezGame();

    void preperToFreezGame(int force, Entity *entityRese, std::string direc, Entity *entityAttack);

    void hitEntity(Entity* entityResev,Entity* entityAttack, int parryMulitplayer);
    void freezingGame();
    bool getFreezEntity(std::string nameOfEntity);

    sf::Sprite *getSpriteOfEntity(std::string name);

    void colisionDetection(std::string nameOfEntity);

};


#endif //ENTITYMANAGER_H
