//
// Created by Oliver Šmítek on 11.05.2026.
//

#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H
#include "BackGroundManager.h"
#include "SpriteManager.h"
#include "TextureManager.h"
#include "../Entities/Entity.h"

class Entity;

class DrawManager {
private:
    DrawManager() {}


    SpriteManager *spriteManager;
    TextureManager *textureManager;
    BackGroundManager *backGroundManager;
    EntityManager *entityManager;


public:
    static DrawManager& getInstance(){
        static DrawManager theInstance;
        return theInstance;
    }


    void drawGame(sf::RenderWindow &window, EnvironmenAndPhysicsManager &environmenAndPhysicsManager);


};

#endif //DRAWMANAGER_H
