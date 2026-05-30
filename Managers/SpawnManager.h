//
// Created by Oliver Šmítek on 02.12.2025.
//

#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include "../Entities/Entity.h"
#include "../Insertors/InsertEntity.h"

#include "../Entities/Player/Player.h"
#include "../Entities/Enemies/HellHound.h"
#include "../Entities/particle/BloodSplash.h"
#include "../Entities/Envirament/Platform.h"


#include <memory>

class SpawnManager {

    SpawnManager() {};

    InsertEntity* insertEntity;

    int id = 0;

public:

    static SpawnManager& getInstance(){
        static SpawnManager theInstance;
        return theInstance;
    }

  public:
    void spawnPlayer(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity);
    void spawnHellHound(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity);


    void spawnBloodSplash(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity, std::string direction, bool kill);
    void spawnHellHoundGore(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity, std::string direction, std::string nameOfTexture);
    void spawnPlatform(sf::Vector2f spawnPosition);
    void spawnEagOfPlatform(sf::Vector2f spawnPosition, std::string side);

};



#endif //SPAWNMANAGER_H
