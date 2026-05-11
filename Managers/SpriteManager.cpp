//
// Created by Oliver Šmítek on 25.11.2025.
//

#include "SpriteManager.h"

#include <iostream>
#include <ostream>



void SpriteManager::drawSprite(sf::Sprite *sprite, float x, float y, sf::RenderWindow& window) {
    sprite->setPosition(x,y);
    window.draw(*sprite);
}

void SpriteManager::setTextureToSprite(sf::String nameOfTexture,sf::Sprite *sprite) {

        const sf::Texture* current = sprite->getTexture();
        const sf::Texture* wanted  = &textureManager->getInstance().textures.at(nameOfTexture);

        if (current != wanted) {
            textureManager->getInstance().setTexture(nameOfTexture, sprite);
            sf::IntRect rect =  sprite->getTextureRect();
            int sizeOftexture = sprite->getTexture()->getSize().x;
            int oneFrame = sizeOftexture / textureManager->getInstance().numOfFramesTextures.at(nameOfTexture);
            sprite->setTextureRect({0,rect.top,oneFrame,rect.height});
        }
}

void SpriteManager::setTextureToBackGroundSprite(std::string nameOfTexture, sf::Sprite *sprite) {
    textureManager->getInstance().setTexture(nameOfTexture, sprite);
}


void SpriteManager::switchSides(std::string direction, sf::Sprite *sprite) {

    sf::Vector2f scale = sprite->getScale();

    if (direction == "left")
        sprite->setScale(-std::abs(scale.x), scale.y);
    else if (direction == "right")
        sprite->setScale(std::abs(scale.x), scale.y);
}


void SpriteManager::transfomration(sf::Sprite *sprite, sf::Vector2f scale, std::string direction, std::string currentTexture) {
    animationUpdate(sprite, currentTexture);
    int hightNum = sprite->getTexture()->getSize().y;
    int hDel = -hightNum/ 16 + 7;
    sprite->setOrigin(sprite->getLocalBounds().width/2, sprite->getLocalBounds().height/hDel);
    sprite->setScale(scale.x, scale.y);
    switchSides(direction, sprite);
}

void SpriteManager::hitBoxTransformation(sf::Sprite *sprite, sf::Vector2f scale, sf::String direction) {
    sprite->setOrigin(sprite->getLocalBounds().width/2, sprite->getLocalBounds().height/2);
    sprite->setColor(sf::Color(255,255,255,0));
    sprite->setScale(scale.x, scale.y);
    switchSides(direction, sprite);

}

void SpriteManager::transformSpriteHPBar(sf::Sprite *sprite, sf::Vector2f scale, int hp) {
    sf::IntRect rect =  sprite->getTextureRect();
    sprite->setScale(scale.x, scale.y);
    int left = std::round((100 - hp)* 0.47) + 3;
    sprite->setTextureRect({left ,rect.top,50,rect.height});

}
void SpriteManager::transformDamageBar(sf::Sprite *sprite, sf::Vector2f scale, int pastHP, int hp, sf::Vector2f *locationDmgBar) {

    sf::IntRect rect = sprite->getTextureRect();
    sprite->setScale(scale.x, scale.y);

    int damage = pastHP - hp;
    int width = damage * 47 / 100;
    locationDmgBar->x = 67 + (hp * 213) / 100;
    sprite->setTextureRect({3, rect.top, width, rect.height});
}


void SpriteManager::markTextureAsHit(sf::Sprite *sprite) {
    sprite->setColor(sf::Color::Red);
}
void SpriteManager::markTextureAsNormal(sf::Sprite *sprite) {
    sprite->setColor(sf::Color(255,255,255,255));
}

void SpriteManager::animationUpdate(sf::Sprite *sprite, sf::String currentTexture) {

if (timer.getElapsedTime().asMilliseconds() >= intervalBetwenAnimations) {
        int sizeOftexture = sprite->getTexture()->getSize().x;
        int oneFrame = sizeOftexture / textureManager->getInstance().numOfFramesTextures.at(currentTexture);
        sf::IntRect rect =  sprite->getTextureRect();
        if (rect.left < sizeOftexture - oneFrame) {
            sprite->setTextureRect({rect.left + oneFrame,rect.top,oneFrame,rect.height});
        }
        else {
            sprite->setTextureRect({0,rect.top,oneFrame,rect.height});
        }
    }
}

void SpriteManager::resetAnimationTimer() {
    if (timer.getElapsedTime().asMilliseconds() >= intervalBetwenAnimations) {
    timer.restart();
    }
}


int SpriteManager::getIndexOfAnimation(sf::Sprite *sprite) {
    int indexOfAnimation =  sprite->getTextureRect().left;
    return indexOfAnimation;
}

int SpriteManager::getMaxIndexOfAnimation(sf::Sprite *sprite) {
    int sizeOftexture = sprite->getTexture()->getSize().x;
    return sizeOftexture;
}
void SpriteManager::rotateSprite(sf::Sprite *sprite, int angle) {
    sprite->setRotation(angle);
}
