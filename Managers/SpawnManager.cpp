//
// Created by Oliver Šmítek on 02.12.2025.
//

#include "SpawnManager.h"

#include "../Entities/Player/Player.h"
#include "../Entities/Envirament/Platform.h"
#include "../Entities/Envirament/PlatformEag.h"
#include "../Entities/Enemies/HellHound.h"
#include "../Entities/particle/HellHoundGore/HellHoundGore.h"
#include "../Entities/Particle/BloodSplash.h"


void SpawnManager::spawnPlayer(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity){
  Player* player = new Player(spawnPosition, spawnVelocity);
  insertEntity->getInstance().insertEntity("Player", player);
}

void SpawnManager::spawnHellHound(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity) {
    std::string name = "HellHound" + std::to_string(id);
    id++;

    HellHound* hellHound = new HellHound(spawnPosition,spawnVelocity, name);
    insertEntity->getInstance().insertEntity(name,hellHound);
}

void SpawnManager::spawnBloodSplash(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity, std::string direction, bool kill) {
    std::string name = "BloodSplash" + std::to_string(id);
    id++;

    BloodSplash* blood_splash = new BloodSplash(spawnPosition,spawnVelocity, name, direction,kill);
    insertEntity->getInstance().insertEntity(name,blood_splash);
}

void SpawnManager::spawnHellHoundGore(sf::Vector2f spawnPosition, sf::Vector2f spawnVelocity, std::string direction, std::string nameOfTexture) {
    std::string name = "GoreHellHound" + std::to_string(id);
    id++;

    HellHoundGore* hellHound_gore = new HellHoundGore(spawnPosition,spawnVelocity, name, direction, nameOfTexture);
    insertEntity->getInstance().insertEntity(name,hellHound_gore);
}
void SpawnManager::spawnPlatform(sf::Vector2f spawnPosition) {
    std::string name = "Xlatform" + std::to_string(id);
    id++;

    Platform* platformTerm = new Platform(spawnPosition, name);
    insertEntity->getInstance().insertEntity(name,platformTerm);
}

void SpawnManager::spawnEagOfPlatform(sf::Vector2f spawnPosition, std::string side) {
    std::string name = "XlatformEag" + std::to_string(id);
    id++;

    PlatformEag* platformEagTemp = new PlatformEag(spawnPosition, name, side);
    insertEntity->getInstance().insertEntity(name,platformEagTemp);
}