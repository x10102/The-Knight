#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

#include "EntityManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "../Managers/SpriteManager.h"
#include "SFML/Graphics/RenderWindow.hpp"

class BackGroundManager;
static BackGroundManager *instance;

class BackGroundManager {
public:


  // Pointery na singletony
  EntityManager* entityManager;
  SpriteManager* spriteManager;

  BackGroundManager();

  static BackGroundManager& getInstance(){
    if (instance == nullptr) {
      instance = new BackGroundManager();
    }
    return *instance;
  }

  void logicOfBackground(sf::RenderWindow& window);
  void drawBackground(sf::RenderWindow& window);

  float positionXOfPlayer = 0.f;
  float positionYOfPlayer = 0.f;

public:
  // Pozice a vzdálenosti

  float frontGround = 0.f;
  float midGround = 0.f;
  float backGround = 0.f;
  float backGroundFull = 0.f;

  bool cornerBool = false;

  float backgroundCloudsDist = 0.f;
  float backgroundTownDist = 0.f;
  float backgroundHouse2ADist = 0.f;
  float backgroundHouse2BDist = 0.f;
  float backgroundHouse1Dist = 0.f;
  float floorDist = 0.f;


  float velocityOfPlayerX = 0.f;

  float xOfFloor = 0.f;

  bool crackedBrickIsPlased = false;

  // Sprity
  sf::Sprite backgroundClouds;
  sf::Sprite backgroundTown;
  sf::Sprite backgroundHouse1;
  sf::Sprite backgroundHouse2;
  sf::Sprite floor;
  sf::Sprite floor2;

  // Měřítka
  sf::Vector2f scaleOfMap = {2.5f, 2.5f};
  sf::Vector2f scaleOfMapBackGround = {4.5f, 4.5f};
};

#endif // BACKGROUNDMANAGER_H