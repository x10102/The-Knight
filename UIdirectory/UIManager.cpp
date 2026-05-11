//
// Created by Oliver Šmítek on 12.03.2026.
//
#include "UIManager.h"


UIManager::UIManager(int hp, sf::Vector2f posOutLine, sf::Vector2f posInLine,sf::Vector2f posDamageLine, std::string nameOfTextureOutLine, std::string nameOfTextureInLine, std::string nameOfDamageLine) {

  this->hpMAX = hp;
  this->posOutLine = posOutLine;
  this->posInLine = posInLine;
  pastHP = hpMAX;
  posDamageBar = posDamageLine;

  TextureManager::getInstance().setTexture(nameOfTextureOutLine, &HPBarOutline);
  TextureManager::getInstance().setTexture(nameOfTextureInLine, &HPBar);
  TextureManager::getInstance().setTexture(nameOfDamageLine, &DamageBar);
  HPBarOutline.scale(4.5, 4.5);
  DamageBar.scale(4.5, 4.5);
};

void UIManager::updateUIHPBar(sf::RenderWindow& window, int hp, sf::Vector2f scale) {

  SpriteManager::getInstance().transformSpriteHPBar(&HPBar,scale, hp);
  SpriteManager::getInstance().drawSprite(&HPBar, posInLine.x,posInLine.y, window);
  if(hp < pastHP) {
    SpriteManager::getInstance().transformDamageBar(&DamageBar,{4.5,4.5},pastHP,hp,&posDamageBar);
    SpriteManager::getInstance().drawSprite(&DamageBar, posDamageBar.x,posDamageBar.y, window);
    if (cooldownOnHit.getElapsedTime().asSeconds() > 0.8) {
      pastHP = pastHP - 1;
    }
  }
  else {
    cooldownOnHit.restart();
  }

  SpriteManager::getInstance().drawSprite(&HPBarOutline, posOutLine.x,posOutLine.y, window);


  }



