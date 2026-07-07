//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "TextureManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "SFML/Graphics/CircleShape.hpp"


class SpriteManager {

    TextureManager *textureManager;

    SpriteManager() {}

    public:
        static SpriteManager& getInstance(){
            static SpriteManager theInstance;
            return theInstance;
        }

    int intervalBetwenAnimations = 45;
    // 45 = 16
    //90 = 32

    sf::Clock timer;

    std::vector<std::pair<sf::Sprite, float>> oldPositionsOfPlayer;
    float blureShadow = 200;
    float timeBetweneBlure = 50;
    sf::Clock clockOfBlure;

    //Setap Sprite:
    void transfomration(sf::Sprite *sprite, sf::Vector2f scale, std::string direction, std::string currentTexture);
    void hitBoxTransformation(sf::Sprite *sprite, sf::Vector2f scale, sf::String direction);
    void switchSides(std::string direction, sf::Sprite *sprite);
    void drawSprite(sf::Sprite *sprite, float x, float y, sf::RenderWindow& window); //drawFunkce(Vlastní každá Entita či oběkt)
    void animationUpdate(sf::Sprite *sprite, std::string currentTexture);
    void setTextureToSprite(sf::String nameOfTexture, sf::Sprite *sprite);
    void setTextureToBackGroundSprite(std::string nameOfTexture, sf::Sprite *sprite);
    void markTextureAsHit(sf::Sprite *sprite);
    void markTextureAsNormal(sf::Sprite *sprite);
    void transformSpriteHPBar(sf::Sprite *sprite, sf::Vector2f scale, int hp);
    void transformDamageBar(sf::Sprite *sprite, sf::Vector2f scale, int pastHP, int hp, sf::Vector2f *locationDmgBar);
    void transformCircle(sf::CircleShape *circule);
    void sinchorizeIntervalBtwAnim();

    int getIndexOfAnimation(sf::Sprite *sprite);
    int getMaxIndexOfAnimation(sf::Sprite *sprite);
    void resetAnimationTimer();
    void rotateSprite(sf::Sprite *sprite, int angle);
    void shadowTransform(sf::Sprite *sprite, sf::Vector2f scale);
    void blureTransform(sf::Sprite *sprite, sf::Vector2f scale);
    void trimStaminaBarToFitInOutLines(sf::Sprite *sprite, bool used);

    void sorceBarTransformation(sf::Sprite *sprite, float sorce);


    //Effects:

    void speedBlurer(sf::Sprite *sprite, sf::RenderWindow &window, float numOfBlure, std::string direction, float velocityX, bool dashIsActiveBool);

};





#endif //SPRITEMANAGER_H
