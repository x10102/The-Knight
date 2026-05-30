//
// Created by Oliver Šmítek on 25.11.2025.
//

#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H
#include <unordered_map>

#include "TextureManager.h"
#include "../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics/RenderWindow.hpp"
#include "../cmake-build-debug/_deps/sfml-src/include/SFML/Graphics/Sprite.hpp"



class SpriteManager{

    TextureManager *textureManager;

    SpriteManager() {}

    public:
        static SpriteManager& getInstance(){
            static SpriteManager theInstance;
            return theInstance;
        }

    const float intervalBetwenAnimations = 45.0f;
    sf::Clock timer;

    //Setap Sprite:
    void transfomration(sf::Sprite *sprite, sf::Vector2f scale, std::string direction, std::string currentTexture);
    void hitBoxTransformation(sf::Sprite *sprite, sf::Vector2f scale, sf::String direction);
    void switchSides(std::string direction, sf::Sprite *sprite);
    void drawSprite(sf::Sprite *sprite, float x, float y, sf::RenderWindow& window); //drawFunkce(Vlastní každá Entita či oběkt)
    void animationUpdate(sf::Sprite *sprite, sf::String currentTexture);
    void setTextureToSprite(sf::String nameOfTexture, sf::Sprite *sprite);
    void setTextureToBackGroundSprite(std::string nameOfTexture, sf::Sprite *sprite);
    void markTextureAsHit(sf::Sprite *sprite);
    void markTextureAsNormal(sf::Sprite *sprite);
    void transformSpriteHPBar(sf::Sprite *sprite, sf::Vector2f scale, int hp);
    void transformDamageBar(sf::Sprite *sprite, sf::Vector2f scale, int pastHP, int hp, sf::Vector2f *locationDmgBar);
    int getIndexOfAnimation(sf::Sprite *sprite);
    int getMaxIndexOfAnimation(sf::Sprite *sprite);
    void resetAnimationTimer();
    void rotateSprite(sf::Sprite *sprite, int angle);
    void shadowTransform(sf::Sprite *sprite, sf::Vector2f scale);

};





#endif //SPRITEMANAGER_H
