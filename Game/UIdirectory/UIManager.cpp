//
// Created by Oliver Šmítek on 12.03.2026.
//
#include "UIManager.h"

#include "../Entities/Entity.h"
#include "../Managers/EntityManager.h"
#include "iostream"
#include "../Managers/BackGroundManager.h"
#include "../Managers/CameraManager.h"




UIManager::UIManager(int sorce, sf::Vector2f posOutLine, sf::Vector2f posInLine,sf::Vector2f posLine, const std::string &nameOfTextureOutLine, const std::string &nameOfTextureInLine, const std::string &nameOfTextureLine) {

  this->sorceMAX = sorce;
  this->posOutLine = posOutLine;
  this->posInLine = posInLine;
  pastSorce = sorceMAX;
  posBar = posLine;

  TextureManager::getInstance().setTexture(nameOfTextureOutLine, &BarOutline);
  TextureManager::getInstance().setTexture(nameOfTextureInLine, &Bar);
  TextureManager::getInstance().setTexture(nameOfTextureLine, &DecreseSorceBar);
  BarOutline.scale(4.5, 4.5);
  DecreseSorceBar.scale(4.5, 4.5);;
  Bar.scale(4.5, 4.5);
};


void UIManager::updateUIHPBar(sf::RenderWindow& window, int hp, sf::Vector2f scale) {
    posInLineDraw = posInLine.x + window.getView().getCenter().x - window.getSize().x / 2;
    posBarDraw = posBar.x + window.getView().getCenter().x - window.getSize().x / 2;
    posOutLineDraw  = posOutLine.x + window.getView().getCenter().x - window.getSize().x / 2;


  SpriteManager::getInstance().transformSpriteHPBar(&Bar,scale, hp);
  SpriteManager::getInstance().drawSprite(&Bar, posInLineDraw,posInLine.y, window);
  if(hp < pastSorce) {
    SpriteManager::getInstance().transformDamageBar(&DecreseSorceBar,{4.5,4.5},pastSorce,hp,&posBar);
    SpriteManager::getInstance().drawSprite(&DecreseSorceBar, posBarDraw,posBar.y, window);
    if (cooldownOnHit.getElapsedTime().asSeconds() > 0.8) {
      pastSorce = pastSorce - 1;
    }
  }
  else {
    cooldownOnHit.restart();
  }

  SpriteManager::getInstance().drawSprite(&BarOutline, posOutLineDraw ,posOutLine.y, window);

}
void UIManager::updateUIStaminaBar(int dashNumOfUse,sf::Clock timerStam, sf::RenderWindow &window) {

  for(int i = 0; i < maxDashes; i++) {

    posInLineDraw = (posInLine.x + window.getView().getCenter().x - window.getSize().x / 2) + i  * offSetOfDashesUIs;
    posBarDraw = (posBar.x + window.getView().getCenter().x - window.getSize().x / 2) + i  * offSetOfDashesUIs;
    posOutLineDraw  =(posOutLine.x + window.getView().getCenter().x - window.getSize().x / 2) + i  * offSetOfDashesUIs;



    bool drawFirstDash = dashNumOfUse >= 1;
    if (i == 0) {
      SpriteManager::getInstance().trimStaminaBarToFitInOutLines(&Bar, drawFirstDash);
      SpriteManager::getInstance().drawSprite(&Bar, posInLineDraw,posInLine.y, window);

      if (!drawFirstDash) {
        SpriteManager::getInstance().sorceBarTransformation(&DecreseSorceBar, timerStam.getElapsedTime().asSeconds());
        SpriteManager::getInstance().drawSprite(&DecreseSorceBar, posBarDraw,posBar.y, window);
      }
    }

    bool drawSecendDash = dashNumOfUse == 2;
    if (i == 1) {
      SpriteManager::getInstance().trimStaminaBarToFitInOutLines(&Bar, drawSecendDash);
      SpriteManager::getInstance().drawSprite(&Bar, posInLineDraw,posInLine.y, window);

      if (!drawSecendDash && drawFirstDash) {
        SpriteManager::getInstance().sorceBarTransformation(&DecreseSorceBar, timerStam.getElapsedTime().asSeconds());
        SpriteManager::getInstance().drawSprite(&DecreseSorceBar, posBarDraw,posBar.y, window);
      }
    }


    SpriteManager::getInstance().drawSprite(&BarOutline, posOutLineDraw,posOutLine.y, window);
  }

}


